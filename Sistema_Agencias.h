#ifndef __Sistema_Agencias__h__
#define __Sistema_Agencias__h__

#include "Agencia.h"
#include "Ruta_Aerea.h"
#include "Comando.h"
#include "Graph.h"
#include "Trie.h"
#include <vector>
#include <list>

namespace PUJ
{
	class Sistema_Agencias
	{

	public:
		typedef Sistema_Agencias Self;
		typedef std::vector<PUJ::Ruta_Aerea> Rutas;
		typedef std::list<PUJ::Comando> Comandos;
		typedef std::list<PUJ::Agencia> Agencias;
		typedef std::string String;


	private:
		Rutas rutas;
		Comandos comandos;
		Agencias agencias;
		PUJ::Agencia* sesion_Activa;
		PUJ::Trie autocomplete;
		PUJ::Graph grafoRutas;

	public:
		Sistema_Agencias();
		virtual ~Sistema_Agencias();
		bool hacer_login(String nombre, String contrasena);
		bool hacer_logout();
		Rutas reportar_vuelos();
		Rutas reportar_vuelos(String dato);
		Rutas reportar_vuelos(String origen, String fecha);
		PUJ::Venta* vender_vuelo_sencillo(String id_vuelo, String fecha, String num_identificacion, String nombre, String apellidos);
		PUJ::Ruta_Aerea* buscar_ruta_aerea(String id_vuelo);
		void agregar_vuelo(String codigo, String dia, String ciudad_origen, String ciudad_destino, String hora_vuelo, unsigned int duracion, unsigned int sillas_disponibles, unsigned int costo_silla);
		void agregar_agencia(String nombre, String contrasena);

		std::vector<String> fillWord(String datoP, String datoH);

		void consolidate();
		void reportar_dinero();

		PUJ::Venta* cancelar_venta(String iden);
		PUJ::Venta* cambiarVuelo(String id_pasajero, String id_vuelo_original, String id_vuelo_nuevo, String fecha_vuelo, float& difPrecio);
		void agregar_venta(String id, String id_vuelo, String apellidos, String nombre, String identificacion, String fecha_vuelo, String fecha_venta, String hora_venta);
		Rutas& getRutas();
		Comandos& getComandos();
		Agencias& getAgencias();
		Agencia* getSesion_Activa();
		void setSesion_Activa(Agencia*);
		std::vector<PUJ::Agencia::Ventas> reportar_ventas();
		void agregar_comando(String comando, String parametro);
		void llenarArbol();

		std::vector<std::deque<std::string> > GetPaths( std::string ciudad_origen, std::string ciudad_destino );
		void llenarGrafo();

		PUJ::Comando* buscar_comando(String comando);
	};
}

//#include "Sistema_Agencias.hxx"

#endif
