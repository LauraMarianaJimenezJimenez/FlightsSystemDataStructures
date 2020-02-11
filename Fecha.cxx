//#ifndef __Fecha__hxx__
//#define __Fecha__hxx__

#include "Fecha.h"
#include <string>
#include <ctime>
/*	\!brief: Constructor de la clase Fecha
*/
PUJ::Fecha::
Fecha()
{

}
/*	\!brief: Destructor de la clase Fecha
*/
PUJ::Fecha::
~Fecha()
{

}
/*	\!brief: Fracciona una fecha string en tres datos enteros, el primero el correspondiente al anno, el segundo al mes y el tercero al dia.
	\!param: Una fecha tipo String
*/
void PUJ::Fecha::setFecha(std::string fecha)
{
	this->anno = std::stoi( fecha.substr(0,4) );
	this->mes = std::stoi( fecha.substr(4,2) );
	this->dia = std::stoi( fecha.substr(6,2) );
}
/*	\!brief: Convierte una fecha tipo int en una fecha string bajo el formato yyyy/mm/dd
*	\!return: fecha tipo string
*/
std::string PUJ::Fecha::getFecha() const
{
	return (std::to_string(this->anno) + " / " + std::to_string(this->mes) + " / " + std::to_string(this->dia));
}
/*	\!brief: Convierte la fecha en una fecha string bajo el formato yyyymmdd
*	\!return: fecha tipo string
*/
std::string PUJ::Fecha::getString() const
{
	return (std::to_string(this->anno) + ((this->mes <10)? "0" + std::to_string(this->mes): std::to_string(this->mes) )+  ((this->dia <10)? "0" + std::to_string(this->dia): std::to_string(this->dia) ));
}

unsigned int PUJ::Fecha::getDia()
{
	return(this->dia);
}

unsigned int PUJ::Fecha::getMes()
{
	return(this->mes);
}

unsigned int PUJ::Fecha::getAnno()
{
	return(this->anno);
}

/*	\!brief: Convierte una fecha en el dia de la semana que les corresponde
	\!return: Día de la semana en formato string
*/
std::string PUJ::Fecha::getDiaSemana()
{
	std::tm time_in = { 0, 0, 0, (int)this->dia, (int)this->mes-1, (int)this->anno - 1900 }; // 1-based day, 0-based month, year since 1900

	std::time_t time_temp = std::mktime(&time_in);

  	//Note: Return value of localtime is not threadsafe, because it might be
  	// (and will be) reused in subsequent calls to std::localtime!
  	const std::tm * time_out = std::localtime(&time_temp);
	int dia = time_out -> tm_wday;
	std::string diaS;
	if(dia == 0) diaS = "Domingo";
  	if(dia == 1) diaS = "Lunes";
  	if(dia == 2) diaS = "Martes";
  	if(dia == 3) diaS = "Miercoles";
  	if(dia == 4) diaS = "Jueves";
  	if(dia == 5) diaS = "Viernes";
  	if(dia == 6) diaS = "Sabado";
  	return (diaS);
}

int PUJ::Fecha::getDiaSemanaNum( std::string dia )
{
	if(dia == "Domingo") return 0;
	if(dia == "Lunes") return 1;
	if(dia == "Martes") return 2;
	if(dia == "Miercoles") return 3;
	if(dia == "Jueves") return 4;
	if(dia == "Viernes") return 5;
	if(dia == "Sabado") return 6;
	else return -1;
}


std::string PUJ::Fecha::getDiaSemanaHoy()
{

	std::time_t time_temp = std::time(0);

  	//Note: Return value of localtime is not threadsafe, because it might be
  	// (and will be) reused in subsequent calls to std::localtime!
  	const std::tm * time_out = std::localtime(&time_temp);
	int dia = time_out -> tm_wday;
	std::string diaS;
	if(dia == 0) diaS = "Domingo";
  	if(dia == 1) diaS = "Lunes";
  	if(dia == 2) diaS = "Martes";
  	if(dia == 3) diaS = "Miercoles";
  	if(dia == 4) diaS = "Jueves";
  	if(dia == 5) diaS = "Viernes";
  	if(dia == 6) diaS = "Sabado";
  	return (diaS);
}

/*	\!brief: Sobrecarga el operador mayor para comparar dos fechas
    \!param: Fechas a ser comparadas
	\!return: Verdadero si la la fecha 1 es mayor a la 2, falso si ocurre lo contrario
*/
bool PUJ::Fecha::operator>(const Self& right) const
{
	if(this->anno > right.anno)
		return true;
	else if(this->anno == right.anno)
	{
		if(this->mes > right.mes)
			return true;
		else if(this->mes == right.mes)
		{
			if(this->dia > right.dia)
				return true;
			else
				return false;
		}
		else return false;
	}
	else return false;
}

bool PUJ::Fecha::operator<(const Self& right) const
{
	if(this->anno < right.anno)
		return true;
	else if(this->anno == right.anno)
	{
		if(this->mes <right.mes)
			return true;
		else if(this->mes == right.mes)
		{
			if(this->dia < right.dia)
				return true;
			else
				return false;

		}
		else return false;
	}
	else return false;
}
