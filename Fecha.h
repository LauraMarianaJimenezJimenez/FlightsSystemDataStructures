#ifndef __Fecha__h__
#define __Fecha__h__

#include <string>

namespace PUJ
{
	class Fecha
	{
	private:
		unsigned int dia;
		unsigned int mes;
		unsigned int anno;
	public:
		typedef Fecha Self;
		Fecha();
		virtual ~Fecha();
		void setFecha(std::string fecha);
		std::string getFecha() const;
		std::string getString() const;
		unsigned int getDia();
		unsigned int getMes();
		unsigned int getAnno();
		std::string getDiaSemana();
		std::string getDiaSemanaHoy();
		int getDiaSemanaNum( std::string dia );
		bool operator>(const Self&) const;
		bool operator<(const Self&) const;
	};
}

//#include "Fecha.hxx"

#endif
