//#ifndef __Venta__hxx__
//#define __Venta__hxx__

#include <iostream>
#include <string>
#include "Venta.h"

/*	\!brief: Constructor vacio de la clase Venta
*/
PUJ::Venta::
Venta()
{

}
/*	\!brief: Constructor de la Venta con los datos recibidos
*	\!param: Toda la información de una venta
*/
PUJ::Venta::
Venta(unsigned int identificador, String cod_vuelo, String num_identificacion,	String apellidos, String nombres, String fecha_vuelo, String fecha_venta, String hora_venta)
{
	this->identificador = identificador;
	this->cod_vuelo = cod_vuelo;
	this->num_identificacion = num_identificacion;
	this->apellidos = apellidos;
	this->nombres = nombres;
	this->fecha_vuelo.setFecha(fecha_vuelo);
	this->fecha_venta.setFecha(fecha_venta);
	this->hora_venta.setHora(hora_venta);
}
/*	\!brief: Destructor de la clase Venta
*/
PUJ::Venta::
~Venta()
{

}



unsigned int PUJ::Venta::
getIdentificador()
{
	return(this->identificador);
}

std::string PUJ::Venta::
getCodVuelo()
{
	return(this->cod_vuelo);
}

std::string PUJ::Venta::
getNumIdentificacion()
{
	return(this->num_identificacion);
}

std::string PUJ::Venta::
getApellidos()
{
	return(this->apellidos);
}

std::string PUJ::Venta::
getNombres()
{
	return(this->nombres);
}

PUJ::Fecha PUJ::Venta::
getFechaVuelo()
{
	return(this->fecha_vuelo);
}

PUJ::Fecha PUJ::Venta::
getFechaVenta()
{
	return(this->fecha_venta);
}

PUJ::Hora PUJ::Venta::
getHoraVenta()
{
	return(this->hora_venta);
}

void PUJ::Venta::
setIdentificador( unsigned int identificador)
{
	this->identificador = identificador;
}


//#endif
