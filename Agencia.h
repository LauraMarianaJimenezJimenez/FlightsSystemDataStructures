#ifndef __Agencia__h__
#define __Agencia__h__

#include "Venta.h"
#include <list>
#include <vector>

namespace PUJ
{
	class Agencia
	{
	public:
		typedef Agencia Self;
		typedef std::list<Venta> Ventas;
		typedef std::string String;
	private:
		Ventas ventas;
		String nombre;
		String contrasena;
	public:
		Agencia();
		Agencia(String nombre, String contrasena);
		virtual ~Agencia();
		PUJ::Venta* agregar_venta(unsigned int identificador, String cod_vuelo, String num_identificacion, String apellidos, String nombres, String fecha_vuelo, String fecha_venta, String hora_venta);
		std::vector<Ventas> imprimir_ventas();
		String getNombre();
		String getContrasena();
		unsigned int getUltimoIdentificador();
		Ventas getVentas();
		void consolidate();
		void eraseFromFile( std::string identificador, std::string fechaVuelo);

		PUJ::Venta* buscar_venta(unsigned int id);
		PUJ::Venta* buscar_venta(std::string id_pasajero, std::string id_vuelo_original);

		PUJ::Venta* buscar_cedula(std::string id);

	};

}

//#include "Agencia.hxx"

#endif
