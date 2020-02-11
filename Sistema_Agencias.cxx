//#ifndef __Sistema_Agencias__hxx__
//#define __Sistema_Agencias__hxx__

#include <vector>
#include <list>
#include <ctime>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "Sistema_Agencias.h"
#include "Agencia.h"
#include "Venta.h"
#include "Ruta_Aerea.h"
#include "Graph.h"

typedef std::string String;

/*	\!brief: Constructor del sistema de Agencias, inicia sin sesión activa
*/
PUJ::Sistema_Agencias::
Sistema_Agencias()
{
	this->setSesion_Activa(NULL);
}

/*	\!brief: Destructor del sistema de Agencias
*/
PUJ::Sistema_Agencias::
~Sistema_Agencias()
{

}

/*	\!brief: Inicia sesión de una agencia si existe
*	\!param: Dos strings con el nombre y la contraseña de la agencia
*	\!return: true si se inició la sesión, false si no se pudo
*/
bool PUJ::Sistema_Agencias::
hacer_login(String nombre, String contrasena)
{
	Agencias::iterator itA = this->agencias.begin();
	for( ; itA!=this->agencias.end(); itA++)
	{
		if(itA->getNombre() == nombre && itA->getContrasena() == contrasena)
		{
			this->setSesion_Activa(&(*itA));
			return true;
		}
	}
	return false;
}

/*	\!brief: Cierra la sesión de la agencia si está iniciada
*	\!return: bool si se cerró la sesión, false si la sesión no está iniciada
*/
bool PUJ::Sistema_Agencias::
hacer_logout()
{
	if(this->sesion_Activa != NULL)
	{
		this->sesion_Activa = NULL;
		return true;
	}
	return false;
}

/*	\!brief: Genera una lista de vuelos disponibles (que tengan sillas disponibles mayor a 0)
*	\!return: Lista de vuelos disponibles
*/
PUJ::Sistema_Agencias::Rutas PUJ::Sistema_Agencias::
reportar_vuelos()
{
	PUJ::Sistema_Agencias::Rutas rutasRetorno;
	Rutas::iterator itR = this->rutas.begin();
	for( ; itR!=this->rutas.end(); itR++)
	{
		if(itR->getSillasDisponibles() > 0)
		{
			rutasRetorno.push_back(*itR);

		}

	}
	return(rutasRetorno);
}

/*	\!brief: Reportar vuelos disponibles que coincidan con el dato ingresado.
			 El dato puede ser ciudad de origen o fecha de vuelo
*	\!param: dato a buscar en los vuelos
*	\!return: Lista de vuelos disponibles que coincidan con el parámetro de búsqueda
*/
PUJ::Sistema_Agencias::Rutas PUJ::Sistema_Agencias::
reportar_vuelos(String dato)
{
	PUJ::Sistema_Agencias::Rutas rutasRetorno;
	Rutas::iterator itR = this->rutas.begin();
	PUJ::Fecha fecha;
	//Evalúa si lo que le llegó es una fecha, esto por medio de buscar algún número dentro del string
	if(dato.find("0")!=std::string::npos  ||
		dato.find("1")!=std::string::npos ||
		dato.find("2")!=std::string::npos ||
		dato.find("3")!=std::string::npos ||
		dato.find("4")!=std::string::npos ||
		dato.find("5")!=std::string::npos ||
		dato.find("6")!=std::string::npos ||
		dato.find("7")!=std::string::npos ||
		dato.find("8")!=std::string::npos ||
		dato.find("9")!=std::string::npos)
	{
		fecha.setFecha(dato);
		String diaSemana = fecha.getDiaSemana();
		for( ; itR!=this->rutas.end(); itR++)
		{
			if(itR->getSillasDisponibles() > 0 && itR->getDia() == diaSemana)
			{
				rutasRetorno.push_back(*itR);
			}

		} //rof
	} //fi
	else
	{
		for( ; itR!=this->rutas.end(); itR++)
		{
			if(itR->getSillasDisponibles() > 0 && itR->getCiudadOrigen() == dato)
			{
				rutasRetorno.push_back(*itR);
			}

		}
	} //esle
	return(rutasRetorno);
}

/*	\!brief: Reportar vuelos disponibles que coincidan con los datos de búsqueda ingresados
*	\!param: Ciudad de Origen y Fecha de Vuelo
*	\!return: Lista de vuelos disponibles que coincidan con los parámetros de búsqueda
*/
PUJ::Sistema_Agencias::Rutas PUJ::Sistema_Agencias::
reportar_vuelos(String origen, String fecha)
{
	PUJ::Sistema_Agencias::Rutas rutasRetorno;
	bool found = false;
	Rutas::iterator itR = this->rutas.begin();
	PUJ::Fecha fechaV;
	fechaV.setFecha(fecha);
	for( ; itR!=this->rutas.end(); itR++)
	{
		if(itR->getSillasDisponibles() > 0 && itR->getDia() == fechaV.getDiaSemana() && itR->getCiudadOrigen() == origen)
		{
			rutasRetorno.push_back(*itR);
		}
	}
	return(rutasRetorno);
}

/*	\!brief: Vende un vuelo sencillo, creando una venta con los parámetros dados y la fecha y hora actuales
*	\!param: String con los datos de una venta, a excepción del nombre de la agencia, identificador y fecha y hora de venta
*	\!return: Lista de vuelos disponibles que coincidan con los parámetros de búsquedo
*/
PUJ::Venta* PUJ::Sistema_Agencias::
vender_vuelo_sencillo(String id_vuelo, String fecha, String num_identificacion, String nombres, String apellidos)
{
	if(this->sesion_Activa != NULL)
	{
		PUJ::Ruta_Aerea* rutaEncontrada = this->buscar_ruta_aerea(id_vuelo);
		if(rutaEncontrada != NULL)
		{
			if(rutaEncontrada->getSillasDisponibles() > 0)
			{
				//Algoritmo para hallar la fecha y hora actual
				std::time_t fechaActual;
				struct tm * timeinfo;
		 		char fechaV [10];
				char horaV [10];
		 		time (&fechaActual);
		 		timeinfo = localtime (&fechaActual);

		 		strftime (fechaV,10,"%Y%m%e",timeinfo);
		 		strftime (horaV,10,"%H%M",timeinfo);

		 		//std::cout << fechaV << " " << horaV << std::endl;

		 		std::string strFecha(fechaV);
		 		std::string strHora(horaV);

		 		PUJ::Fecha fechaValid;
		 		fechaValid.setFecha(fecha);
		 		if(fechaValid.getDiaSemana() == rutaEncontrada->getDia())
		 		{
		 			unsigned int ultIdent = this->sesion_Activa->getUltimoIdentificador();
					PUJ::Venta* ventaR = this->sesion_Activa->agregar_venta(ultIdent+1, id_vuelo, num_identificacion, apellidos, nombres, fecha, strFecha, strHora);
					rutaEncontrada->disminuirSillas();

					this->autocomplete.InsertInto("change",num_identificacion);

					Rutas::iterator itr = this->rutas.begin();
					for( ; itr!= this->rutas.end(); itr++)
					{
						this->autocomplete.InsertInto(num_identificacion, itr->getCodigo());
							Rutas::iterator itr2 = this->rutas.begin();
							for( ; itr2!= this->rutas.end(); itr2++)
							{
									this->autocomplete.InsertInto(itr->getCodigo(), itr2->getCodigo());
							}
					}

					return(ventaR);

		 		}
		 		else throw std::runtime_error("El vuelo seleccionado no opera en esta fecha.");
			}
			else throw std::runtime_error("La ruta aerea no tiene sillas disponibles.");
		}
		else throw std::runtime_error( "La ruta aerea no existe." );
	}
	else throw std::runtime_error( "La sesion no esta activa." );

}

/*	\!brief: Busca una ruta aérea dado el código de vuelo
*	\!param: Código de vuelo a buscar
*	\!return: Apuntador a la ruta aérea encontrada
*/
PUJ::Ruta_Aerea* PUJ::Sistema_Agencias::
buscar_ruta_aerea(String id_vuelo)
{
	Rutas::iterator itR = this->rutas.begin();
	for( ; itR!=this->rutas.end();itR++)
	{
		if(itR->getCodigo() == id_vuelo)
			return &(*itR);
	}
	return NULL;
}


/*	\!brief: Agrega un vuelo a la lista de rutas aéreas dados los parámetros
*	\!param: Todos los datos de una ruta aérea
*/
void PUJ::Sistema_Agencias::
agregar_vuelo(String codigo, String dia, String ciudad_origen, String ciudad_destino, String hora_vuelo, unsigned int duracion, unsigned int sillas_disponibles, unsigned int costo_silla)
{
	PUJ::Ruta_Aerea newRuta(codigo, dia, ciudad_origen, ciudad_destino, hora_vuelo, duracion, sillas_disponibles, costo_silla);
	this->rutas.push_back(newRuta);
}

/*	\!brief: Agrega una agencia a la lista de agencias dados los parámetros
*	\!param: Nombre y contraseña de una agencia
*/
void PUJ::Sistema_Agencias::
agregar_agencia(String nombre, String contrasena)
{
	PUJ::Agencia newAgencia(nombre, contrasena);
	this->agencias.push_back(newAgencia);
}

/*	\!brief: Agrega una venta a la lista de ventas de la agencia correspondiente dados los parámetros
*	\!param: Todos los datos de una venta (En id se encuentra el nombre de la agencia y el identificador de forma "nombre_id")
*/
void PUJ::Sistema_Agencias::
agregar_venta(String id, String id_vuelo, String apellidos, String nombre, String identificacion, String fecha_vuelo, String fecha_venta, String hora_venta)
{
	std::stringstream tokens(id);
	String nombreAgencia, identificador;
	std::getline(tokens, nombreAgencia, '_');
	std::getline(tokens, identificador);

	Agencias::iterator itA = this->agencias.begin();
	//Busca la agencia por nombre
	for( ; itA!=this->agencias.end();itA++)
	{
		if(itA->getNombre() == nombreAgencia)
		{
			break;
		}
	}

	if(itA!=this->agencias.end())
	{
		//Busca la ruta aérea y solo agrega la venta si existe o
		//si el id de vuelo está vacío (este caso corresponde que la venta esté cancelada)
		PUJ::Ruta_Aerea* rutaEncontrada = this->buscar_ruta_aerea(id_vuelo);
		if((rutaEncontrada != NULL && rutaEncontrada->getSillasDisponibles() != 0) || id_vuelo.empty())
		{
			if(!id_vuelo.empty())
				rutaEncontrada->disminuirSillas();
			itA->agregar_venta(std::stoi(identificador), id_vuelo, identificacion, apellidos, nombre, fecha_vuelo, fecha_venta, hora_venta);
		}
	}
}

/*	\!brief: Reporta las ventas de la agencia activa
*	\!return: Vector de lista de ventas con las ventas normales, modificadas y canceladas separadas
*/
std::vector<PUJ::Agencia::Ventas> PUJ::Sistema_Agencias::
reportar_ventas()
{
	std::vector<PUJ::Agencia::Ventas> ventasRetorno;
	if(this->sesion_Activa != NULL)
	{
		ventasRetorno = this->sesion_Activa->imprimir_ventas();
	}
	return (ventasRetorno);
}

/*	\!brief: Agrega un comando a la lista de comandos
*	\!param:  Nombre del comando e información de parámetros
*/
void PUJ::Sistema_Agencias::
agregar_comando(String comando, String parametro)
{
	PUJ::Comando newComando(comando,parametro);
	this->comandos.push_back(newComando);
}

void PUJ::Sistema_Agencias::
llenarArbol()
{
	this->autocomplete.Insert("change");
	this->autocomplete.Insert("login");
	this->autocomplete.Insert("logout");
	this->autocomplete.Insert("change");
	this->autocomplete.Insert("exit");
	this->autocomplete.Insert("path");
	this->autocomplete.Insert("report");
	this->autocomplete.InsertInto("report", "flights");
	this->autocomplete.InsertInto("report","money");
	this->autocomplete.InsertInto("report","inventory");
	this->autocomplete.Insert("sell");

	this->autocomplete.Insert("cancel");

	this->autocomplete.Insert("consolidate");

	this->autocomplete.Insert("help");
	Agencias::iterator ita = this->agencias.begin();
	for(; ita != this->agencias.end(); ita++)
	{
	std::list<PUJ::Venta> ventas = ita->getVentas();
	std::list<PUJ::Venta>::iterator itv = ventas.begin();
	for(; itv != ventas.end(); itv++)
	{
			this->autocomplete.InsertInto("change",itv->getNumIdentificacion());

			Rutas::iterator itr = this->rutas.begin();
			for( ; itr!= this->rutas.end(); itr++)
			{
				this->autocomplete.InsertInto(itv->getNumIdentificacion(), itr->getCodigo());
					Rutas::iterator itr2 = this->rutas.begin();
					for( ; itr2!= this->rutas.end(); itr2++)
					{
							this->autocomplete.InsertInto(itr->getCodigo(), itr2->getCodigo());
					}
			}



	}
	}


	Rutas::iterator itR = this->rutas.begin();
	std::vector<std::string> ciudades;
	for(; itR != this->rutas.end(); itR++)
	{
		std::vector<std::string>::iterator it = std::find(ciudades.begin(), ciudades.end(), itR->getCiudadOrigen());
		if( it == ciudades.end())
		{
			ciudades.push_back(itR->getCiudadOrigen());
		}
		it = std::find(ciudades.begin(), ciudades.end(), itR->getCiudadDestino());
		if( it == ciudades.end())
		{
			ciudades.push_back(itR->getCiudadDestino());
		}

	}
	for(int i = 0; i < ciudades.size(); i++)
	{
		this->autocomplete.InsertInto("flights",(ciudades[i]));
		this->autocomplete.InsertInto("path",(ciudades[i]));
		//this->autocomplete.InsertInto("path",(itR->getCiudadDestino()));
		Rutas::iterator itR2 = this->rutas.begin();
		for(int j = 0; j < ciudades.size(); j++)
		{
			this->autocomplete.InsertInto(ciudades[i],ciudades[j]);
		}
	}

	Agencias::iterator itA = this->agencias.begin();
	for(; itA != this->agencias.end(); itA++)
		this->autocomplete.InsertInto("login",(itA->getNombre()));

	itR = this->rutas.begin();
	for(; itR != this->rutas.end(); itR++)
		this->autocomplete.InsertInto("sell",(itR->getCodigo()));

	Comandos::iterator itC = this->comandos.begin();
	for(; itC != this->comandos.end(); itC++)
		this->autocomplete.InsertInto("help",(itC->getNombre()));


	//this->autocomplete.PrintAsPNG("trie.png");
}

void PUJ::Sistema_Agencias::
llenarGrafo()
{
	PUJ::Fecha f;
	std::string diaHoy = f.getDiaSemanaHoy();
	for(int i = 0; i < this->rutas.size(); i++)
	{
		//if(this->rutas[i].getDia() == diaHoy)
		//{
			//std::cout << rutas[i].getCiudadOrigen() << "->" << rutas[i].getCiudadDestino() << "\n";
			long idOrigen = (this->grafoRutas).AddNode(this->rutas[i].getCiudadOrigen());
			long idDestino = (this->grafoRutas).AddNode(this->rutas[i].getCiudadDestino());
			//std::cout << idOrigen << "->" << idDestino << " "  << rutas[i].getCiudadOrigen() << "->" << rutas[i].getCiudadDestino() << "\n";
			(this->grafoRutas).AddArc(idOrigen,idDestino,this->rutas[i]);
		//}
	}
	//(this->grafoRutas).PrintAsPNG("rutas.png");
}

std::vector<std::deque<std::string> > PUJ::Sistema_Agencias::
GetPaths( std::string ciudad_origen, std::string ciudad_destino )
{
	std::vector< std::deque<std::string> > ret;
	std::deque< std::string > vTiempo = this->grafoRutas.GetShortestPath(ciudad_origen, ciudad_destino, 'T');
	std::deque< std::string > vDinero = this->grafoRutas.GetShortestPath(ciudad_origen, ciudad_destino, 'D');
	std::deque< std::string> vDirecto = this->grafoRutas.GetShortestPath(ciudad_origen, ciudad_destino, 'R');

	ret.push_back(vTiempo);
	ret.push_back(vDinero);
	ret.push_back(vDirecto);

	return ret;

}


/*	\!brief: Busca un comando dado el nombre
*	\!param: Nombre del comando a buscar
*	\!return: Apuntador al comando encontrado o NULL si no lo encuentra
*/
PUJ::Comando* PUJ::Sistema_Agencias::
buscar_comando(String comando)
{
	PUJ::Sistema_Agencias::Comandos::iterator itC = this->comandos.begin();
	for ( ; itC!=this->comandos.end(); itC++)
	{
		if(itC->getNombre()==comando)
		{
			return &(*itC);
		}
	}

	return NULL;
}


PUJ::Venta* PUJ::Sistema_Agencias::
cancelar_venta(std::string iden)
{
	try
	{
		unsigned int id = std::stoul(iden);
		PUJ::Venta* ret;
		PUJ::Venta* ventaEncontrada = this->sesion_Activa->buscar_venta(id);

		if(ventaEncontrada != NULL && ventaEncontrada->getCodVuelo() != "")
		{
			unsigned int iden = id;
			std::string numiden = ventaEncontrada->getNumIdentificacion();
			std::string apellidos = ventaEncontrada->getApellidos();
			std::string nombres = ventaEncontrada->getNombres();
			std::string fechaVu = ventaEncontrada->getFechaVuelo().getString();
			//Algoritmo para hallar la fecha y hora actual
			std::time_t fechaActual;
			struct tm * timeinfo;
			char fechaV [10];
			char horaV [10];
			time (&fechaActual);
			timeinfo = localtime (&fechaActual);

			strftime (fechaV,10,"%Y%m%e",timeinfo);
			strftime (horaV,10,"%H%M",timeinfo);

			//std::cout << fechaV << " " << horaV << std::endl;

			std::string strFecha(fechaV);
			std::string strHora(horaV);

			ret = this->sesion_Activa->agregar_venta(iden, "", numiden, apellidos, nombres, fechaVu, strFecha, strHora);
		}

		return ( ret );
	}
	catch (std::exception& error)
	{
		PUJ::Venta* ret;
		PUJ::Venta* ventaEncontrada = this->sesion_Activa->buscar_cedula(iden);

		if(ventaEncontrada != NULL && ventaEncontrada->getCodVuelo() != "")
		{
			unsigned int iden = ventaEncontrada->getIdentificador();
			std::string numiden = ventaEncontrada->getNumIdentificacion();
			std::string apellidos = ventaEncontrada->getApellidos();
			std::string nombres = ventaEncontrada->getNombres();
			std::string fechaVu = ventaEncontrada->getFechaVuelo().getString();
			//Algoritmo para hallar la fecha y hora actual
			std::time_t fechaActual;
			struct tm * timeinfo;
			char fechaV [10];
			char horaV [10];
			time (&fechaActual);
			timeinfo = localtime (&fechaActual);

			strftime (fechaV,10,"%Y%m%e",timeinfo);
			strftime (horaV,10,"%H%M",timeinfo);

			//std::cout << fechaV << " " << horaV << std::endl;

			std::string strFecha(fechaV);
			std::string strHora(horaV);

			ret = this->sesion_Activa->agregar_venta(iden, "", numiden, apellidos, nombres, fechaVu, strFecha, strHora);
		}

		return ( ret );
	}
}

PUJ::Venta* PUJ::Sistema_Agencias::
cambiarVuelo(std::string id_pasajero, std::string id_vuelo_original, std::string id_vuelo_nuevo,  std::string fecha_vuelo, float& difPrecio)
{
	PUJ::Venta ret;
	PUJ::Venta* ventaEncontrada = this->sesion_Activa->buscar_venta(id_pasajero, id_vuelo_original);
	PUJ::Ruta_Aerea* rutaVieja = buscar_ruta_aerea(id_vuelo_original);
	PUJ::Ruta_Aerea* rutaNueva = buscar_ruta_aerea(id_vuelo_nuevo);
	if(ventaEncontrada != NULL)
	{
		if( rutaNueva != NULL && rutaVieja != NULL)
		{
			PUJ::Venta* nueva = vender_vuelo_sencillo(id_vuelo_nuevo, fecha_vuelo, id_pasajero, ventaEncontrada->getNombres(), ventaEncontrada->getApellidos());
			nueva->setIdentificador( ventaEncontrada->getIdentificador() );
			difPrecio = rutaNueva->getCostoSilla() - rutaVieja->getCostoSilla();
			return nueva;
		}
		else throw std::runtime_error("No se encontro una de las rutas especificadas");
	}
	else throw std::runtime_error("No se encontro una venta de este usuario en el vuelo especificado");
}

void PUJ::Sistema_Agencias::
consolidate()
{
	this->sesion_Activa->consolidate();
}

void PUJ::Sistema_Agencias::
reportar_dinero()
{

	std::vector<PUJ::Agencia::Ventas> ventasImprimir;

	ventasImprimir = this->sesion_Activa->imprimir_ventas();


	if(ventasImprimir[0].size() + ventasImprimir[1].size() + ventasImprimir[2].size() != 0)
	{
		std::vector<PUJ::Agencia::Ventas>::iterator itV = ventasImprimir.begin();
		std::cout << "REPORTE DE VENTAS Y DINERO\n";
		for(int i = 0; itV!=ventasImprimir.end(); itV++, i++)
		{
			if(i==0) std::cout << "----VENTAS SIN MODIFICACIONES----" << std::endl;
			if(i==1) std::cout << "----VENTAS MODIFICADAS----" << std::endl;
			if(i==2) std::cout << "----VENTAS CANCELADAS----" << std::endl;
			PUJ::Agencia::Ventas::iterator itV2 = itV->begin();
			if(!itV->empty())
			{
				for( ; itV2 != itV->end(); itV2++)
				{
					std::cout << (*itV2) << std::endl;
				}
			}
			else
				std::cout << "No existen ventas en esta seccion." << std::endl;
			std::cout << std::endl;

		}
	}
	else
		std::cout << "No existen ventas en esta agencia." << std::endl;

	bool modificado = false;
	bool cancelado = false;
	double totalP = 0;
	double totalR = 0;
	PUJ::Agencia::Ventas ventas = this->sesion_Activa->getVentas();
	PUJ::Agencia::Ventas::iterator it1 = ventas.begin();
	PUJ::Agencia::Ventas::iterator it2 = ventas.begin();

	for (; it1 != ventas.end(); it1++)
	{
		PUJ::Agencia::Ventas::iterator it2 = ventas.begin();
		for (; it2 != ventas.end(); it2++)
	    {
	    	if(it1->getIdentificador() == it2->getIdentificador())
	    	{
	    		bool mod = false;

	    		if(it2->getFechaVenta() > it1->getFechaVenta()) mod = true;
					else if(it1->getFechaVenta() > it2->getFechaVenta()) mod = false;
						else if (it2->getHoraVenta() > it1->getHoraVenta()) mod = true;


	    		if(it2->getCodVuelo().empty() && mod)
				{
					cancelado = true;
					break;
				}

	    		if( mod )
				{
					modificado = true;
					break;
				}
	    	}

	    }


	    if(modificado)
	    {
	    	unsigned int precio1 = buscar_ruta_aerea((*it1).getCodVuelo())->getCostoSilla();
	    	unsigned int precio2 = buscar_ruta_aerea((*it2).getCodVuelo())->getCostoSilla();

	    	unsigned int diff = precio2 - precio1;

	    	if(diff > 0)
	    		totalR += diff;
	    	else if(diff < 0)
	    		totalP += diff;
	    	modificado = false;
	    }
	    else if(cancelado)
	    {
	    	unsigned int precio1 = buscar_ruta_aerea((*it1).getCodVuelo())->getCostoSilla();
	    	totalP += (double)precio1*0.85;
	    	cancelado = false;
	    }

	}

	std::cout<<"Dinero pagado por la agencia : $" << totalP << std::endl;
	std::cout<<"Dinero recibido por la agencia : $" << totalR << std::endl;


}

std::vector<std::string> PUJ::Sistema_Agencias::
fillWord(String datoP, String datoH)
{
	return ( autocomplete.Find(datoP, datoH) );
}

PUJ::Sistema_Agencias::Rutas&
PUJ::Sistema_Agencias::
getRutas()
{
	return((this->rutas));
}


PUJ::Sistema_Agencias::Comandos& PUJ::Sistema_Agencias::
getComandos()
{
	return((this->comandos));
}

PUJ::Sistema_Agencias::Agencias& PUJ::Sistema_Agencias::
getAgencias()
{
	return((this->agencias));
}

PUJ::Agencia* PUJ::Sistema_Agencias::
getSesion_Activa()
{
	return((this->sesion_Activa));
}


void PUJ::Sistema_Agencias::
setSesion_Activa(PUJ::Agencia* sesion)
{
	this->sesion_Activa = sesion;
}


//#endif
