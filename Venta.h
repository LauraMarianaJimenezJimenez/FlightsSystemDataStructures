#ifndef __Venta__h__
#define __Venta__h__

#include "Fecha.h"
#include "Hora.h"
#include <string>

namespace PUJ
{
	class Venta
	{

	public:
		typedef Venta Self;
		typedef std::string String;
		friend std::ostream& operator<<( std::ostream& os, const Self& v )
  	    {
  	    	os << "IDENTIFICADOR: " << v.identificador << std::endl;
  	    	os << "CODIGO VUELO: " << v.cod_vuelo << std::endl;
  	    	os << "NOMBRE: " << v.apellidos << ", " << v.nombres << std::endl;
  	    	os << "FECHA DE VUELO: " << v.fecha_vuelo.getFecha() << std::endl;
  	    	os << "FECHA DE LA VENTA: " << v.fecha_venta.getFecha() << " - " << v.hora_venta.getTiempo() << std::endl;
  	    	return(os);
  	    }

	private:
		unsigned int identificador;
		std::string cod_vuelo;
		std::string num_identificacion;
		std::string apellidos;
		std::string nombres;
		PUJ::Fecha fecha_vuelo;
		PUJ::Fecha fecha_venta;
		PUJ::Hora hora_venta;
	public:

		Venta();
		Venta(unsigned int identificador, String cod_vuelo, String num_identificacion,	String apellidos, String nombres, String fecha_vuelo, String fecha_venta, String hora_venta);
		virtual ~Venta();

		unsigned int getIdentificador();
		std::string getCodVuelo();
		std::string getNumIdentificacion();
		std::string getApellidos();
		std::string getNombres();
		PUJ::Fecha getFechaVuelo();
		PUJ::Fecha getFechaVenta();
		PUJ::Hora getHoraVenta();
		void setIdentificador( unsigned int identificador);
	};
}

//#include "Venta.hxx"

#endif
