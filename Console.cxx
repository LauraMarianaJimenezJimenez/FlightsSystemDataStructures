//#ifndef __Console__hxx__
//#define __Console__hxx__


// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include "Console.h"

#include <fstream>
#include <string>
#include <sstream>


// -------------------------------------------------------------------------
Console::
Console( )
  : Superclass( )
{
  //this->sistema = NULL;
}

// -------------------------------------------------------------------------
Console::
Console( const std::string& prompt)
  : Superclass( prompt )
{
  leerArchivos(this->sistema);
  //this->sistema = sistema;
}

// -------------------------------------------------------------------------
Console::
~Console( )
{
}

// -------------------------------------------------------------------------
int Console::
trigger( const std::string& linea )
{
  std::string comando;
  std::string dato1;
  std::string dato2;
  std::string dato3;

    std::cout << "---------------------------------------\n";
    std::stringstream ss(linea);
    getline(ss,comando,' ');
    if(comando=="login")
    {
      if(this->sistema.getSesion_Activa() == NULL)
      {
        getline(ss,dato1);
        std::string password;
        std::cout<< "Ingrese contrasena por favor: ";
        std::cin>>password;
        std::cin.ignore();
            bool ingresado = this->sistema.hacer_login(dato1,password);
          if(ingresado)
          {
            std::cout << "Sesion iniciada correctamente." << std::endl;
          }
          else
              std::cout << "Usuario o contrasena invalidas. Intente de nuevo." << std::endl;
      }
      else
        std::cout << "Error. Ya existe una sesion activa." << std::endl;

      return( 1 );

    }
    else if(comando=="logout")
    {
      bool cerrado = this->sistema.hacer_logout();
      if(cerrado)
      {
        std::cout<<"Sesion cerrada correctamente" << std::endl;
      }
      else
        std::cout<<"No hay sesion activa" << std::endl;
      return ( 1 );
    }

    else if(comando=="report")
    {
      ss >> comando;
      if(comando == "flights")
      {
        PUJ::Sistema_Agencias::Rutas rutaImprimir;
        if(ss>>dato1)
        {
          if(ss>>dato2)
          {
            rutaImprimir = this->sistema.reportar_vuelos(dato1, dato2);
          }
          else
          {
            rutaImprimir = this->sistema.reportar_vuelos(dato1);
          }

        }
        else
        {
           rutaImprimir = this->sistema.reportar_vuelos();
        }
        std::cout << "--------------------------------\n";
        std::cout << "---REPORTE VUELOS DISPONIBLES---\n";
        std::cout << "--------------------------------\n\n";

        for(int i=0; i<rutaImprimir.size(); i++)
        {
          std::cout << rutaImprimir[i] << std::endl;
        }
        if(rutaImprimir.empty())
        {
          std::cout << "No existen vuelos con las espeficaciones dadas.\n\n";
        }
      }
      else if(comando == "inventory")
      {
        if(this->sistema.getSesion_Activa() == NULL)
          std::cout << "NO HAY SESION ACTIVA." << std::endl;
        else
        {
          std::vector<PUJ::Agencia::Ventas> ventasImprimir;
          ventasImprimir = this->sistema.reportar_ventas();

          if(ventasImprimir[0].size() + ventasImprimir[1].size() + ventasImprimir[2].size() != 0)
          {
            std::vector<PUJ::Agencia::Ventas>::iterator itV = ventasImprimir.begin();
            std::cout << "REPORTE DE VENTAS\n";
            for(int i = 0; itV!=ventasImprimir.end(); itV++, i++)
            {
              if(i==0) std::cout << "----VENTAS SIN MODIFICACIONES----" << std::endl;
              if(i==1) std::cout << "----VENTAS MODIFICADAS----" << std::endl;
              if(i==2) std::cout << "----VENTAS CANCELADAS----" << std::endl;
              PUJ::Agencia::Ventas::iterator itV2 = itV->begin();
              if(!itV->empty())
              {
                for( ; itV2 != itV->end(); itV2++)
                {
                  std::cout << (*itV2) << std::endl;
                }
              }
              else
                std::cout << "No existen ventas en esta seccion." << std::endl;
              std::cout << std::endl;

            }
          }
          else
            std::cout << "No existen ventas en esta agencia." << std::endl;
        }
      }
      else if(comando == "money")
      {
        if(this->sistema.getSesion_Activa() == NULL)
          std::cout << "NO HAY SESION ACTIVA." << std::endl;
        else
        {
          this->sistema.reportar_dinero();
        }
      }
      else
        std::cout << "El comando no existe" << std::endl;
    }
    else if(comando=="sell")
    {
      ss >> dato1;
      ss >> dato2;
      std::cout << "Ingrese su documento de identificacion en formato CC12345678: ";
      std::string identificacion;
      std::cin >> identificacion;
      std::cin.ignore();
      std::string nombres, apellidos;
      std::cout << "Ingrese sus apellidos: ";
      getline(std::cin, apellidos);
      std::cout << "Ingrese sus nombres: ";
      getline(std::cin, nombres);

      try
      {
        PUJ::Venta* ventaR = this->sistema.vender_vuelo_sencillo(dato1, dato2, identificacion, nombres, apellidos);
        std::cout << "Venta realizada exitosamente." << std::endl;
        guardarVenta(this->sistema.getSesion_Activa()->getNombre(), *ventaR);
      }
      catch(std::exception& error)
      {
        std::cout << "Error: " << error.what() << std::endl;
      }
    }
    else if(comando == "path")
    {
      ss >> dato1;
      ss >> dato2;
      std::vector< std::deque<std::string> > ret = this->sistema.GetPaths(dato1, dato2);
      if(ret[0].size() != 0)
      {

      std::cout << "Ruta recomendada mas rapida:" << std::endl;
      for(int i = 0; i < ret[0].size(); i++)
      {
        std::cout << ret[0][i];
        if( i+1 != ret[0].size() )
          std::cout << ", ";
      }
      std::cout << std::endl;
      std::cout << "Ruta recomendada mas barata:" << std::endl;
      for(int i = 0; i < ret[1].size(); i++)
      {
        std::cout << ret[1][i];
        if( i+1 != ret[1].size() )
          std::cout << ", ";
      }
      std::cout << std::endl;

      std::cout << "Ruta recomendada mas directa:" << std::endl;
      for(int i = 0; i < ret[2].size(); i++)
      {
        std::cout << ret[2][i];
        if( i+1 != ret[2].size() )
          std::cout << ", ";
      }
      std::cout << std::endl;
    }else
    {
      std::cout << "No hay vuelos disponibles de " << dato1 << " a " << dato2 << std::endl;
    }

  }
  else if(comando == "change")
  {
    ss >> dato1;
    ss >> dato2;
    ss >> dato3;
    std::string fechaV;
    std::cout << "Ingrese la nueva fecha de vuelo (YYYYMMDD): ";
    std::cin >> fechaV;
    std::cin.ignore();
    try
    {
      float difPrecio = 0;
      PUJ::Venta* ventaR = this->sistema.cambiarVuelo(dato1, dato2, dato3, fechaV, difPrecio);
      std::cout << "Venta modificada exitosamente." << std::endl;
      std::cout << "La diferencia en precio es de $" << difPrecio << std::endl;
      guardarVenta(this->sistema.getSesion_Activa()->getNombre(), *ventaR);
    }
    catch(std::exception& error)
    {
      std::cout << "Error: " << error.what() << std::endl;
    }
  }
  else if(comando=="help")
    {
      if(getline(ss,dato1))
      {
        PUJ::Comando* comando_imprimir = this->sistema.buscar_comando(dato1);
        if(comando_imprimir != NULL)
        {
          std::cout << "Nombre: "  << comando_imprimir->getNombre() << std::endl << std::endl;
          std::cout << comando_imprimir->getParametros() << std::endl;
        }
        else
          std::cout << "El comando no existe" << std::endl;
      }
      else
      {
        PUJ::Sistema_Agencias::Comandos comandos_imprimir = this->sistema.getComandos();
        PUJ::Sistema_Agencias::Comandos::iterator itC = comandos_imprimir.begin();
        for( ; itC!=comandos_imprimir.end(); itC++)
        {
          std::cout<< itC->getNombre() << std::endl;
        }
        std::cout << "Si quiere informacion de un comando escriba: help <comando>" << std::endl << std::endl;
      }

    }
    else if(comando == "exit")
    {
      this->quit( );
      return( 1 );
    }
    else if(comando == "cancel")
    {
      if(this->sistema.getSesion_Activa() != NULL)
      {
        std::string datoCancel;
        ss >> datoCancel;
        PUJ::Venta* ret = this->sistema.cancelar_venta(datoCancel);
        if(ret->getNumIdentificacion() != "")
        {
          PUJ::Agencia* ag = this->sistema.getSesion_Activa();
          guardarVenta(ag->getNombre(), *ret);
          std::cout << "La venta fue cancelada exitosamente\n";
        }
        else std::cout << "La venta no pudo ser cancelada.\n";
      }
      else std::cout << "NO HAY SESION ACTIVA.\n";
    }
    else if(comando == "consolidate")
    {
      if(this->sistema.getSesion_Activa() != NULL)
      {
        this->sistema.consolidate();
        std::cout << "La base de datos ha sido consolidada\n";
      }
      else std::cout << "NO HAY SESION ACTIVA.\n";
    }
    else if(comando == "echo")
    {
      std::string datoEcho;
      getline(ss,datoEcho);
      std::cout << datoEcho << std::endl;
    }
    else
      std::cout << "El comando no existe" << std::endl;


    return( 0 );
}

//login

//P = ""
//H = "login"
//ES= "login"

// -------------------------------------------------------------------------
int Console::
hotkeys( char c )
{
  if( c == Superclass::TAB )
  {
    std::stringstream linea( this->getBuffer() );
    std::string leidoP, leidoH, leidoES;// = this->getBuffer();
    leidoP = leidoH = leidoES = "";

    int a = 0;
    while( linea >> leidoH )
    {
      if(a != 0)
        leidoP = leidoES;

      leidoES = leidoH;
      a++;
    }
    //leidoH = leidoES;

    // int a = leido.size()-1;
    // while(leido[a] == ' ' && a >= 0)
    // {
    //   leido.erase(a,1);
    //   a--;
    // }

    std::vector < std::string > opciones = this->sistema.fillWord(leidoP,leidoH);

    // for(int i = 0; i < opciones.size() ; i++)
    // {
    //   std::cout << " ! " << opciones[i] << ", ";
    // }
    // std::cout << std::endl;

    this->setBuffer(this->getBuffer() + opciones.back() + " ");
    std::cout << "\r$ " << this->getBuffer();

    if(opciones.size() > 2)
    {
      std::cout << std::endl;
      for(int i = 0; i < opciones.size()-1 ; i++)
      {
        std::string opcion = opciones[i];
        std::cout << opcion << "\t";
      }
      std::cout << std::endl;
      std::cout << "$ " << this->getBuffer();
    }

  }
  else
    return( 0 );
}

/*  \!brief: reposita las ventas realizadas en un archivo de texto
* \!param: Un string con el nombre de la agencia y una venta a ser repositada
*/
void guardarVenta(std::string nombreAgencia, PUJ::Venta ventaR)
{
  std::ofstream out("tickets.txt", std::ofstream::app);
  if(out)
  {
    std::string retorno;
    retorno = nombreAgencia + "_" + std::to_string(ventaR.getIdentificador()) + ";" + ventaR.getCodVuelo()+";" +
    ventaR.getApellidos() + ", " + ventaR.getNombres() + ";" + ventaR.getNumIdentificacion() + ";" +
    ventaR.getFechaVuelo().getString() + ";" + ventaR.getFechaVenta().getString() + ";" + ventaR.getHoraVenta().getHora()+"\n";
    out << retorno;
    out.close();
  }
}


void leerArchivos(PUJ::Sistema_Agencias& sistema)
{
  std::ifstream inputRutas("flights.txt");
  if(inputRutas)
  {
    std::string linea;
    while(std::getline(inputRutas, linea)) //inputRutas >> linea
    {
      std::string datos[8];
      int i = 0;
      std::stringstream tokens(linea);
      std::string token;
      while(std::getline(tokens, token, ';'))
      {
        datos[i] = token;
        i++;
      }

      //Elimina el CR embebido de los saltos de línea si existe
      if(datos[7][ datos[7].size() - 1 ] == '\r')
        datos[7].erase(datos[7].size() - 1 );
      sistema.agregar_vuelo( datos[0], datos[1], datos[2], datos[3], datos[4], std::stoi(datos[5]), std::stoi(datos[6]), std::stoi(datos[7]) );

    }
    inputRutas.close();
  }

  std::ifstream inputAgencias("passwords.txt");
  if(inputAgencias)
  {
    std::string linea;
    while(std::getline(inputAgencias, linea)) //inputRutas >> linea
    {
      std::string datos[2];
      int i = 0;
      std::stringstream tokens(linea);
      std::string token;

      //Tokeniza cada línea leída
      while(std::getline(tokens, token, ';'))
      {
        datos[i] = token;
        i++;
      }

      //Elimina el CR embebido de los saltos de línea si existe
      if(datos[1][ datos[1].size() - 1 ] == '\r')
        datos[1].erase(datos[1].size() - 1 );

      sistema.agregar_agencia( datos[0], datos[1] );

    }
    inputAgencias.close();
  }

  std::ifstream inputVentas("tickets.txt");
  if(inputVentas)
  {
    std::string linea;
    while(std::getline(inputVentas, linea)) //inputVentas >> linea
    {
      std::string datos[8];
      int i = 0;
      std::stringstream tokens(linea);
      std::string token;
      while(std::getline(tokens, token, ';'))
      {
        if(i==2)
        {
          std::stringstream tokenNombre(token);
          std::getline(tokenNombre, datos[i], ',');
          i++;
          std::getline(tokenNombre, datos[i], ',');
        }
        else
          datos[i] = token;
        i++;
      }

      //Elimina el CR embebido de los saltos de línea si existe
      if(datos[7][ datos[7].size() - 1 ] == '\r')
        datos[7].erase(datos[7].size() - 1 );
      datos[3].erase(0,1); //Erase the space at beginning of the name

      sistema.agregar_venta( datos[0], datos[1], datos[2], datos[3], datos[4], datos[5], datos[6], datos[7] );

    }
    inputVentas.close();
  }


  sistema.agregar_comando("login", "Ingresa a una sesión.\nComo usarlo: login <id_agencia>");
  sistema.agregar_comando("logout", "Cierra una sesión activa.\nComo usarlo: logout");
  sistema.agregar_comando("exit", "Finaliza el programa.\nComo usarlo: exit");
  sistema.agregar_comando("report flights", "Reporta una lista de vuelos disponibles, se puede especificar origen y/o fecha.\nComo usarlo: report flights [origen] [fecha]");
  sistema.agregar_comando("report inventory", "Reporta todas la ventas que han sido vendidas, canceladas o cambiadas.\nComo usarlo: report inventory");
  sistema.agregar_comando("report money", "Reporta las ventas de la agencia y el dinero pagado y recibido según modificaciones o cancelaciones.\nComo usarlo: report money");
  sistema.agregar_comando("sell", "Vende un unico vuelo sencillo.\nComo usarlo: sell <id_vuelo> <fecha>");
  sistema.agregar_comando("cancel", "Cancela un vuelo.\nComo usarlo: cancel <id_venta>");
  sistema.agregar_comando("path", "Recomienda tres rutas entre dos ciudades.\nComo usarlo: path <ciudad_origen> <ciudad_destino>");
    sistema.agregar_comando("change", "Cambia un vuelo una venta.\nComo usarlo: change <id_pasajero> <id_vuelo_original> <id_vuelo_nuevo>");

  sistema.llenarArbol();
  sistema.llenarGrafo();
  	std::cout<<"BIENVENIDO, INGRESE POR FAVOR UN COMANDO"<< std::endl;

}


//#endif

// eof - Console.cxx
