/* PROYECTO REALIZADO POR:
*		Sergio Andrés Mejía Tovar
*		Sebastián Gutierrez Zambrano
*		Laura Mariana Jiménez Jiménez
*/

/* Warning: Compile with C++11 standard or above */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Console.h"




/*	\!brief: Función principal del sistema que ejecuta todo los comandos, funcionalidades e impresiones del sistema
*	\!param: un arreglo que recibe parametros por consola y el tamaño del arreglo
*	\!return: 0 si se ejecutó perfectamente
*/
int main(int argc, char** argv)
{



	std::cout<<"CARGANDO, POR FAVOR ESPERE"<< std::endl;
	Console console( "$ ");
 	console.run( );

	std::cout<<"Gracias por usar el sistema de Agencias de Viajes, hasta pronto\n";
	return(0);

} //END OF MAIN
