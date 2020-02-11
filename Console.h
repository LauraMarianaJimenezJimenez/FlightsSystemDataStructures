// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __Console__h__
#define __Console__h__

#include "PUJ/Console.h"
#include "Sistema_Agencias.h"

/**
 */
class Console
  : public PUJ::Console
{
public:
  typedef Console      Self;
  typedef PUJ::Console Superclass;

public:
  Console( );
  Console( const std::string& prompt);
  virtual ~Console( );

  virtual int trigger( const std::string& linea ) override;
  virtual int hotkeys( char c ) override;

 protected:
 	PUJ::Sistema_Agencias sistema;
};

void guardarVenta(std::string, PUJ::Venta ventaR);
void leerArchivos(PUJ::Sistema_Agencias& sistema);

//#include "Console.hxx"

#endif // __Console__h__

// eof - Console.h
