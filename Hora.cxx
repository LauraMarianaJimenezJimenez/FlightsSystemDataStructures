//#ifndef __Hora__hxx__
//#define __Hora__hxx__

#include "Hora.h"
#include <string>

/*\!brief: Constructor de la clase Hora
*/
PUJ::Hora::
Hora()
{

}
/*\!brief: Desctrutor de la clase Hora
*/
PUJ::Hora::
~Hora()
{

}

void PUJ::Hora::setHora(std::string hora)
{

	this->hora = std::stoi( hora.substr(0,2) );
	this->minuto = std::stoi( hora.substr(2,2) );
}

/*	\!brief: Modifica una hora agregando 0 cuando el minuto es menor a 9
	\!return: Retorna la hora modificada en una variable tipo string
*/
std::string PUJ::Hora::
getTiempo() const
{
	std::string retorno="";
	retorno += std::to_string(this->hora)+":";
	if(this->minuto < 10)
	{
		retorno += '0';
	}
	retorno += std::to_string(this->minuto);

	return(retorno);
}

/*	\!brief: Genera la hora en formato HHMM
	\!return: hora en formato HHMM tipo string
*/
std::string PUJ::Hora::
getHora() const
{
	std::string retorno = "";
	retorno += ((this->hora<10)? "0" + std::to_string(this->hora): std::to_string(this->hora)) + ((this->minuto<10)? "0" + std::to_string(this->minuto): std::to_string(this->minuto));
	return (retorno);
}
/*	\!brief: Sobrecarga el operador mayor para comparar dos horas
    \!param: Horas a ser comparadas
	\!return: verdadero si la hora 1 es mayor a la 2, falso si ocurre lo contrario
*/
bool PUJ::Hora::operator>(const Self& right) const
{
	if(this->hora > right.hora)
		return true;
	else if(this->hora == right.hora && this->minuto > right.minuto)
		return true;
	else return false;
}

//  05:04  12:10   00:00		00:40		13:00
// -04:03  11:30   22:45		22:20		12:10
//-------------------------------------------------
//	1  1   1 -20   24-22=2 -45	24-22 20	1 -10
long PUJ::Hora::operator-(const Self& right) const //LO DEVUELVE EN SEGUNDOS
{
	long difMin = this->minuto - right.minuto;
	long difHor = this->hora - right.hora;
	long ret = 0;

	if(difHor>=0)
	{
		ret = difHor*60 + difMin;
	}
	else
	{
		difHor = 24+difHor;
		ret = difHor*60 + difMin;
	}
	return ret*60;
}

bool PUJ::Hora::operator<(const Self& right) const
{
	if(this->hora < right.hora)
		return true;
	else if(this->hora == right.hora)
	{
		if(this->minuto < right.minuto)
			return true;
		else return false;
	}
	else return false;
}


PUJ::Hora PUJ::Hora::addSeconds( unsigned int seconds )
{
	PUJ::Hora ret = *this;

	unsigned int tot_mins = seconds / 60;
	unsigned int horas = tot_mins / 60;

	ret.minuto += (tot_mins%60);
	ret.hora += horas;

	if(ret.minuto >= 60 )
	{
			unsigned int excHors = ret.minuto / 60;
			ret.minuto = ret.minuto % 60;
			ret.hora += excHors;
	}
	if(ret.hora >= 24)
	{
		ret.hora = ret.hora % 24;
	}

	return ret;
}

unsigned int PUJ::Hora::getHoras()
{
		return this->hora;
}

unsigned int PUJ::Hora::getMinutos()
{
	return this->minuto;
}

//#endif
