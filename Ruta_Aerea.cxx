//#ifndef __Ruta_Aerea__hxx__
//#define __Ruta_Aerea__hxx__

#include "Ruta_Aerea.h"

#include <string>

/*	\!brief: Constructor vacío de la Ruta Aérea
*/
PUJ::Ruta_Aerea::
Ruta_Aerea()
{

}

/*	\!brief: Constructor de la Ruta Aérea con los datos recibidos
*	\!param: Toda la información de una ruta aérea
*/
PUJ::Ruta_Aerea::
Ruta_Aerea(String codigo, String dia, String ciudad_origen, String ciudad_destino, PUJ::Ruta_Aerea::String hora_vuelo, unsigned int duracion, unsigned int sillas_disponibles, unsigned int costo_silla)
{
	this->codigo = codigo;
	this->dia = dia;
	this->ciudad_origen = ciudad_origen;
	this->ciudad_destino = ciudad_destino;

	this->hora_vuelo.setHora(hora_vuelo);

	this->duracion = duracion;
	this->sillas_disponibles = sillas_disponibles;
	this->costo_silla = costo_silla;


}

/*	\!brief: Destructor de la clase Ruta Aérea
*/
PUJ::Ruta_Aerea::
~Ruta_Aerea()
{

}

/*	\!brief: Disminuye en 1 el número de sillas disponibles del vuelo
*/
void PUJ::Ruta_Aerea::
disminuirSillas()
{
	this->sillas_disponibles -= 1;
}

PUJ::Ruta_Aerea::String PUJ::Ruta_Aerea::
getCodigo()
{
	return(this->codigo);
}

PUJ::Ruta_Aerea::String PUJ::Ruta_Aerea::
getDia()
{
	return(this->dia);
}

PUJ::Ruta_Aerea::String PUJ::Ruta_Aerea::
getCiudadOrigen()
{
	return(this->ciudad_origen);
}

PUJ::Ruta_Aerea::String PUJ::Ruta_Aerea::
getCiudadDestino()
{
	return(this->ciudad_destino);
}


PUJ::Hora PUJ::Ruta_Aerea::
getHoraVuelo()
{
	return(this->hora_vuelo);
}

float PUJ::Ruta_Aerea::
getDuracion() const
{
	return(this->duracion);
}

unsigned int PUJ::Ruta_Aerea::
getSillasDisponibles()
{
	return(this->sillas_disponibles);
}


float PUJ::Ruta_Aerea::
getCostoSilla()
{
	return(this->costo_silla);
}

//#endif
