#ifndef __Comando__h__
#define __Comando__h__

#include <string>

namespace PUJ
{
	class Comando
	{
	private:
		std::string nombre;
		std::string parametros;
	public:
		typedef Comando Self;
		Comando(std::string comando, std::string parametro);
		virtual ~Comando();
		std::string getNombre();
		std::string getParametros();
	};
}

//#include "Comando.hxx"

#endif
