//#ifndef __Agencia__hxx__
//#define __Agencia__hxx__

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <ctime>

#include "Agencia.h"

typedef std::string String;


/*	\!brief: Constructor de la clase Agencia
*/
PUJ::Agencia::
Agencia()
{

}

/*	\!brief: Constructor de la clase Agencia con los parámetros dados
*	\!param: Nombre y contraseña de la agencia
*/
PUJ::Agencia::
Agencia(PUJ::Agencia::String nombre, PUJ::Agencia::String contrasena)
{
	this->nombre = nombre;
	this->contrasena = contrasena;
}

/*	\!brief: Destructor de la clase Agencia
*/
PUJ::Agencia::
~Agencia()
{

}

/*	\!brief: Agrega una venta a la lista de ventas
*	\!param: Todos los datos de una venta
*	\!return: Venta creada
*/
PUJ::Venta* PUJ::Agencia::
agregar_venta(unsigned int identificador, String cod_vuelo, String num_identificacion,	String apellidos, String nombres, String fecha_vuelo, String fecha_venta, String hora_venta)
{
	PUJ::Venta newVenta(identificador, cod_vuelo, num_identificacion, apellidos, nombres, fecha_vuelo, fecha_venta, hora_venta );
	this->ventas.push_back(newVenta);
	return (&(this->ventas.back()));
}

/*	\!brief: Genera un vector de listas con las ventas discriminadas por normales, modificadas y canceladas
*	\!return: Vector de listas de ventas
*/
std::vector<PUJ::Agencia::Ventas> PUJ::Agencia::
imprimir_ventas()
{
	//Inicialización del vector retorno
	std::vector<Ventas> ventasRetorno;
	ventasRetorno.resize(3); //0 normales, 1 modificados, 2 cancelados

	//Se genera una copia de las ventas para trabajar sobre ella
	Ventas ventasCopia = this->ventas;
	Ventas::iterator itV = ventasCopia.begin();

	//Se irá eliminando los datos de la copia conforme se ingresan al vector retorno
	while(!ventasCopia.empty())
	{
		Ventas::iterator itV2 = itV;
		bool encontro = false;

		//Se recorre la copia buscando modificaciones o cancelaciones de la venta actual (en itV)
		while(itV2!=ventasCopia.end())
		{
			//Si encuentra una venta, se observa si es modificada o cancelada
			if(itV2->getIdentificador() == itV->getIdentificador())
			{
				if(itV2->getCodVuelo().empty())
				{
					//CANCELADOS
					ventasRetorno[2].push_back(*itV2);
					itV2 = ventasCopia.erase(itV2);
					encontro = true;
				}
				else
				{
					//MODIFICADOS
					bool mod = false;
					if(itV2->getFechaVenta() > itV->getFechaVenta()) mod = true;
					else if(itV->getFechaVenta() > itV2->getFechaVenta()) mod = false;
					else if (itV2->getHoraVenta() > itV->getHoraVenta()) mod = true;

					if(!itV2->getCodVuelo().empty() && mod == true)
					{
						ventasRetorno[1].push_back(*itV2);
						itV2 = ventasCopia.erase(itV2);
						encontro = true;
					}
					else itV2++;
				}
			} //fi
			//Si no, avanzo
			else itV2++;
		}
		//SIN CAMBIOS
		if(!encontro)
		{
			ventasRetorno[0].push_back(*itV);
		}
		ventasCopia.erase(itV);
		//Se reinicia siempre el iterador para no salirse de la lista o obtener un Segmentation Fault
		itV = ventasCopia.begin();
	}
	return(ventasRetorno);
}

PUJ::Agencia::String PUJ::Agencia::
getNombre()
{
	return (this->nombre);
}

PUJ::Agencia::String PUJ::Agencia::
getContrasena()
{
	return (this->contrasena);
}

/*	\!brief: Retorna el último identificador de venta de la lista
*	\!return: Último identificador de las ventas o 0 si no hay ventas
*/
unsigned int PUJ::Agencia::
getUltimoIdentificador()
{
	unsigned int max = 0;
	PUJ::Agencia::Ventas::iterator it = this->ventas.begin();
	for(; it != this->ventas.end(); it++)
	{
		if(it->getIdentificador() > max)
			max = it->getIdentificador();
	}

	return(max);
}

PUJ::Agencia::Ventas PUJ::Agencia::
getVentas()
{
	return(this->ventas);
}

void PUJ::Agencia::
consolidate()
{

	//Algoritmo para hallar la fecha actual
	std::time_t fechaActual;
	struct tm * timeinfo;
	char fechaV [10];

	time (&fechaActual);
	timeinfo = localtime (&fechaActual);
	strftime (fechaV,10,"%Y%m%e",timeinfo);
	std::string strFecha(fechaV);

	PUJ::Fecha fechaHoy;
	fechaHoy.setFecha(strFecha);

	Ventas ven = this->ventas;

	Ventas::iterator it = ven.begin();

	while(it != ven.end())
	{
		if( (*it).getFechaVuelo() < fechaHoy )
		{
			std::string cod = this->nombre;
			cod = cod + "_" + std::to_string((*it).getIdentificador());
			eraseFromFile( cod, (*it).getFechaVuelo().getString() );

			it = ven.erase(it);
		}
		else it++;
	}


	this->ventas = ven;

}

void PUJ::Agencia::
eraseFromFile( std::string identificador, std::string fechaVuelo)
{
	std::ifstream archivo("tickets.txt");

	std::ofstream archivoNew("ticketsNew.txt");

	if(archivo && archivoNew)
	{
		std::string linea;
		while(std::getline(archivo, linea))
		{
			std::string datos[8];
			int i = 0;
			std::stringstream tokens(linea);
			std::string token;
			while(std::getline(tokens, token, ';'))
			{
				if(i==2)
				{
				std::stringstream tokenNombre(token);
			    std::getline(tokenNombre, datos[i], ',');
			    i++;
			    std::getline(tokenNombre, datos[i], ',');
				}
				else
					datos[i] = token;
				i++;
			}

			      	//Elimina el CR embebido de los saltos de línea si existe
			if(datos[7][ datos[7].size() - 1 ] == '\r')
				datos[7].erase(datos[7].size() - 1 );
			datos[3].erase(0,1); //Erase the space at beginning of the name

			if(datos[0] != identificador || datos[5] != fechaVuelo) // ¬(p^q) <=> ¬p v ¬q
			{
				std::string retorno;
				retorno = datos[0] + ";" + datos[1] +";" + datos[2] + ", " +
					datos[3] + ";" + datos[4] + ";" + datos[5] + ";" + datos[6] + ";" + datos[7] +"\n";
	    		archivoNew << retorno;
			}
		}

	}
	archivo.close();
	archivoNew.close();

	remove("tickets.txt");
	rename("ticketsNew.txt","tickets.txt");
}

PUJ::Venta* PUJ::Agencia::
buscar_venta(unsigned int id)
{
	PUJ::Venta* ret = NULL;

	PUJ::Agencia::Ventas::iterator itV = this->ventas.begin();

	for(; itV != this->ventas.end(); itV++)
	{
		if(itV->getIdentificador() == id)
			ret = &(*itV);
	}

	return ( ret );
}

PUJ::Venta* PUJ::Agencia::
buscar_venta(std::string id_pasajero, std::string id_vuelo_original)
{
	PUJ::Venta* ret = NULL;

	PUJ::Agencia::Ventas::iterator itV = this->ventas.begin();

	for(; itV != this->ventas.end(); itV++)
	{
		if(itV->getNumIdentificacion() == id_pasajero && itV->getCodVuelo() == id_vuelo_original)
			ret = &(*itV);
	}

	return ( ret );
}

PUJ::Venta* PUJ::Agencia::
buscar_cedula(std::string id)
{
	PUJ::Venta* ret = NULL;

	Ventas::iterator itV = this->ventas.begin();

	for(; itV != this->ventas.end(); itV++)
	{
		if(itV->getNumIdentificacion() == id)
			ret = &(*itV);
	}

	return ( ret );
}


//#endif
