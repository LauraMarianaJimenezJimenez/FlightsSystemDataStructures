#ifndef __Hora__h__
#define __Hora__h__

#include <string>

namespace PUJ
{
	class Hora
	{
	private:
		unsigned int hora;
		unsigned int minuto;
	public:
		typedef Hora Self;
		Hora();
		virtual ~Hora();
		void setHora(std::string hora);
		std::string getTiempo() const;
		std::string getHora() const;
		bool operator>(const Self& right) const;
		bool operator<(const Self& right) const;
		long operator-(const Self& right) const;
		PUJ::Hora addSeconds( unsigned int seconds );
		unsigned int getHoras();
		unsigned int getMinutos();
	};
}

//#include "Hora.hxx"

#endif
