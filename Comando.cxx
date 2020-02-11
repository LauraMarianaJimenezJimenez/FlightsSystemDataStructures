//#ifndef __Comando__hxx__
//#define __Comando__hxx__

#include "Comando.h"
#include <string>


/*	\!brief: Constructor de la clase Comando con los datos recibidos 
	\!param: Toda la información de un comando
*/
PUJ::Comando::
Comando(std::string comando, std::string parametro)
{
	this->nombre= comando;
	this->parametros=parametro;

}
/*	\!brief: Destructor de la clase Comando
*/
PUJ::Comando::
~Comando()
{

}

std::string PUJ::Comando::
getNombre()
{
    return(this->nombre);
}

std::string PUJ::Comando::
getParametros()
{
    return(this->parametros);
}

//#endif 	