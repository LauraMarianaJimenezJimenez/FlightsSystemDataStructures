#ifndef __Ruta_Aerea__h__
#define __Ruta_Aerea__h__

#include "Hora.h"

#include <iostream>

namespace PUJ
{
	class Ruta_Aerea
	{

	public:
		typedef Ruta_Aerea Self;
		typedef std::string String;
		friend std::ostream& operator<<( std::ostream& os, const Self& r )
  	    {
  	    	os << "CODIGO: " << r.codigo << std::endl;
  	    	os << "DIA: " << r.dia << std::endl;
  	    	os << "TRAYECTO: " << r.ciudad_origen << " -> " << r.ciudad_destino << std::endl;
  	    	os << "HORA: " << r.hora_vuelo.getTiempo() << std::endl;
  	    	os << "SILLAS DISPONIBLES: " << r.sillas_disponibles << std::endl;
  	    	os << "COSTO DE LA SILLA: " << r.costo_silla << std::endl;
  	    	os << "----------------------------------------------------" << std::endl;
					//os << r.dia[0] << r.dia[1] << r.duracion;
  	    	return( os );
        }

	private:
		String codigo;
		String dia;
		String ciudad_origen;
		String ciudad_destino;
		PUJ::Hora hora_vuelo;
		float duracion;
		unsigned int sillas_disponibles;
		float costo_silla;


	public:
		Ruta_Aerea();
		Ruta_Aerea(String codigo, String dia, String ciudad_origen, String ciudad_destino, String hora_vuelo, unsigned int duracion, unsigned int sillas_disponibles, unsigned int costo_silla);
		virtual ~Ruta_Aerea();
		void disminuirSillas();
		String getCodigo();
		String getDia();
		String getCiudadOrigen();
		String getCiudadDestino();
		PUJ::Hora getHoraVuelo();
		float getDuracion() const;
		unsigned int getSillasDisponibles();
		float getCostoSilla();

	};
}

//#include "Ruta_Aerea.hxx"

#endif
