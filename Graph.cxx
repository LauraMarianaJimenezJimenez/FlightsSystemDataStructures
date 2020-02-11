
#include "Graph.h"
#include <algorithm>
#include <queue>
#include <sstream>
#include <limits>
#include <vector>
#include <list>
#include <map>
#include "Ruta_Aerea.h"
#include "Fecha.h"

PUJ::Graph::Graph()
{

}

PUJ::Graph::~Graph()
{

}

long PUJ::Graph::
AddNode(TValue value)
{
	typename Vertices::iterator it = std::find(this->m_Vertices.begin(), this->m_Vertices.end(), value);

	if(it == this->m_Vertices.end())
	{
		this->m_Vertices.push_back( value );
		return this->m_Vertices.size() - 1;
	}
	else return (it - this->m_Vertices.begin());
}


void PUJ::Graph::
AddArc (long a, long b, Ruta_Aerea costo)
{
	if( !this->HasArc(a,b) )
	{
		(this->m_Matrix[a][b]).push_back(costo);
	}
}


bool PUJ::Graph::
HasArc(long a, long b)
{
	typename Costs::iterator mIt = this->m_Matrix.find( a );

	if( mIt != this->m_Matrix.end())
	{
		typename std::map<long, TCost>::iterator mIt2 = (mIt->second).find( b );
		if( mIt2 != (mIt->second).end() )
			return true;
	}

	return false;
}


std::string PUJ::Graph::
GetNode(long a)
{
	if(a>=0 && a < this->m_Vertices.size())
	{
		return this->m_Vertices[a];
	}
}


std::deque < std::string > PUJ::Graph::
GetShortestPath ( long a, long b, char criterio)
{
	std::deque< std::string > ret;
	long copB = -1;
	if( a >= 0 && b >= 0 && a < this->m_Vertices.size() && b < this->m_Vertices.size())
	{
		copB = b;
		std::vector<long> camino;
		if( criterio == 'T' )
			camino = this->GetDijkstra(a, true);
		if( criterio == 'D' )
			camino = this->GetDijkstra(a, false);
		if( criterio == 'R' )
			camino = this->GetDijkstraDirect( a );
		// std::cout << "H  P\n";
		// for(int i = 0; i < camino.size() ; i++)
		// {
		// 	std::cout << i << "  " << camino[i] << "\n";
		// }

		while(copB != -1 && camino[copB] != copB)
		{
			ret.push_front( this->m_Vertices[copB] );
			copB = camino[copB];
		}
		ret.push_front( this->m_Vertices[a] );

	}
	std::deque< std::string > retorno;
	if(copB == -1)
		return (retorno);
	else
		return (ret);
}

std::deque < std::string > PUJ::Graph::
GetShortestPath ( TValue a, TValue b, char criterio )
{
	long v_a, v_b;
	v_a = v_b = -1;
	for( int i = 0; i < this->m_Vertices.size(); i++ )
	{
		if( this->m_Vertices[i] == a)
		{
			v_a = i;
		}
		if( this->m_Vertices[i] == b)
		{
			v_b = i;
		}
	}
	return ( this->GetShortestPath(v_a, v_b, criterio) );
}



std::vector< long > PUJ::Graph::
GetDijkstra( long seed, bool criterio ) //true=tiempo, false=dinero
{
	std::vector < long > ret(this->m_Vertices.size( ), -1);
	std::vector< bool > marks( this->m_Vertices.size( ), false );

	std::vector < Triple > triples;

	Triple nueva;
	nueva.father = seed;
	nueva.son = seed;
	nueva.cost = 0;
	nueva.horaLlegada.setHora("2400");
	Fecha f;
	nueva.dia = -1;//f.getDiaSemanaNum( f.getDiaSemanaHoy() );

	triples.push_back(nueva);

	while( !triples.empty( ) )
	{
		std::pop_heap(triples.begin(),triples.end(), comparador());

		Triple last = triples.back();

		triples.pop_back();

		if( marks[ last.son ] )
			continue;
		marks[ last.son ] = true;

		typename Costs::iterator mIt = this->m_Matrix.find( last.son );
		if( mIt != this->m_Matrix.end())
		{
			typename std::map<long, TCost>::iterator rIt = mIt->second.begin();
			for( ; rIt != mIt->second.end(); rIt++)
			{
				Triple conec;
				conec.father = last.son;
				conec.son = rIt->first;

				std::vector<PUJ::Ruta_Aerea>::iterator ruIt = (rIt->second).begin();
				for( ; ruIt != (rIt->second).end(); ruIt++)
				{
					bool cuenta = false;
					if(last.horaLlegada.getHoras() == 24 )
					{
						conec.dia = f.getDiaSemanaNum( ruIt->getDia() );
						cuenta = true;
					}
					else if( last.dia == f.getDiaSemanaNum( ruIt->getDia() ) )
					{
						if(( (ruIt->getHoraVuelo() - last.horaLlegada) >= 7200 ) && (last.horaLlegada < ruIt->getHoraVuelo()))
						{
							cuenta = true;
							conec.dia = last.dia;
						}
					}
					else if( (last.dia+1)%7 == f.getDiaSemanaNum( ruIt->getDia() ) )
					{
						if(( (ruIt->getHoraVuelo() - last.horaLlegada) >= 7200 ))
						{
							cuenta = true;
							conec.dia = (last.dia+1)%7;
						}
					}

					if(cuenta)
					{
						unsigned int tiempoEspera = (last.horaLlegada.getHoras() == 24)?0:(ruIt->getHoraVuelo() - last.horaLlegada);
						if( criterio == true)
							conec.cost = last.cost + ruIt->getDuracion() + tiempoEspera;
						else
							conec.cost = last.cost + ruIt->getCostoSilla();
						conec.horaLlegada = (ruIt->getHoraVuelo()).addSeconds(ruIt->getDuracion());

						triples.push_back( conec );
						std::push_heap( triples.begin(), triples.end(), comparador() );
					}

				}

			}

		}
		ret[ last.son ] = last.father;
	}

	return ret;
}

std::vector< long > PUJ::Graph::
GetDijkstraDirect( long seed )
{
	std::vector < long > ret(this->m_Vertices.size( ), -1);
	std::vector< bool > marks( this->m_Vertices.size( ), false );

	std::vector < Triple > triples;

	Triple nueva;
	nueva.father = seed;
	nueva.son = seed;
	nueva.cost = 0;
	nueva.horaLlegada.setHora("2400");
	Fecha f;
	nueva.dia = -1;//f.getDiaSemanaNum( f.getDiaSemanaHoy() );

	triples.push_back(nueva);

	while( !triples.empty( ) )
	{
		std::pop_heap(triples.begin(),triples.end(), comparador());

		Triple last = triples.back();

		triples.pop_back();

		if( marks[ last.son ] )
			continue;
		marks[ last.son ] = true;

		typename Costs::iterator mIt = this->m_Matrix.find( last.son );
		if( mIt != this->m_Matrix.end())
		{
			typename std::map<long, TCost>::iterator rIt = mIt->second.begin();
			for( ; rIt != mIt->second.end(); rIt++)
			{
				Triple conec;
				conec.father = last.son;
				conec.son = rIt->first;

				std::vector<PUJ::Ruta_Aerea>::iterator ruIt = (rIt->second).begin();
				for( ; ruIt != (rIt->second).end(); ruIt++)
				{
					bool cuenta = false;
					if(last.horaLlegada.getHoras() == 24 )
					{
						conec.dia = f.getDiaSemanaNum( ruIt->getDia() );
						cuenta = true;
					}
					else if( last.dia == f.getDiaSemanaNum( ruIt->getDia() ) )
					{
						if(( (ruIt->getHoraVuelo() - last.horaLlegada) >= 7200 ) && (last.horaLlegada < ruIt->getHoraVuelo()))
						{
							cuenta = true;
							conec.dia = last.dia;
						}
					}
					else if( (last.dia+1)%7 == f.getDiaSemanaNum( ruIt->getDia() ) )
					{
						if(( (ruIt->getHoraVuelo() - last.horaLlegada) >= 7200 ))
						{
							cuenta = true;
							conec.dia = (last.dia+1)%7;
						}
					}

					if(cuenta)
					{
						unsigned int tiempoEspera = (last.horaLlegada.getHoras() == 24)?0:(ruIt->getHoraVuelo() - last.horaLlegada);

						conec.cost = last.cost + 1;//;ruIt->getCostoSilla();
						conec.horaLlegada = (ruIt->getHoraVuelo()).addSeconds(ruIt->getDuracion());

						triples.push_back( conec );
						std::push_heap( triples.begin(), triples.end(), comparador() );
					}


				}

			}

		}
		ret[ last.son ] = last.father;
	}

	return ret;
}


std::list < long > PUJ::Graph::
PrintLevels( long seed )
{
	std::list < long > ret;
	std::vector< bool > marks( this->m_Vertices.size( ), false );
	std::queue< long > q;
	q.push( seed );

	while( !q.empty( ) )
	{
		long node = q.front( );
		q.pop( );
		if( marks[ node ] )
			continue;
		marks[ node ] = true;
		for( long neigh = 0; neigh < this->m_Vertices.size( ); ++neigh )
		{
			if( this->HasArc( node, neigh ) )
			{
				q.push( neigh );
			}
		}
		ret.push_back( node );
	}
	return ret;
}

long PUJ::Graph::
GetSize()
{
	return ( this->m_Vertices.size() );
}

void PUJ::Graph::
PrintAsPNG( std::string file )
{
	std::stringstream str;
	str << "echo \"digraph G{";

	if(this->m_Vertices.size() == 1)
	{
		str << "\"" << this->m_Vertices[0] << "\"";
	}
	else
	{
		for(long i = 0; i < this->m_Vertices.size(); i++)
		{
			str << i << " [label=" << this->m_Vertices[i] << "]; ";
		}
		typename Costs::iterator mIt = this->m_Matrix.begin();

		long i, j;
		i = j = 0;
		std::vector<std::pair<long, long> > pairs;

		for( ; mIt != this->m_Matrix.end(); mIt++)
		{
			i = (mIt->first);
			typename std::map<long, TCost>::iterator mIt2 = (mIt->second).begin();
			for( ; mIt2 != (mIt->second).end(); mIt2++)
			{
				j = (mIt2->first);
				std::pair<long, long> pair(i,j);
				pairs.push_back(pair);
			}
		}

		mIt = this->m_Matrix.begin();

		for( ; mIt != this->m_Matrix.end(); mIt++)
		{
			i = (mIt->first);
			typename std::map<long, TCost>::iterator mIt2 = (mIt->second).begin();
			for( ; mIt2 != (mIt->second).end(); mIt2++)
			{
				j = (mIt2->first);
				std::pair<long, long> pareja(i,j);
				std::pair<long, long> swap;

				swap.first = pareja.second;
				swap.second = pareja.first;

				std::vector<std::pair<long, long> >::iterator it = std::find(pairs.begin(), pairs.end(), pareja);
				std::vector<std::pair<long, long> >::iterator itS = std::find(pairs.begin(), pairs.end(), swap);

				if(it!=pairs.end() && itS!=pairs.end())
				{
					pairs.erase(it);
					std::vector<std::pair<long, long> >::iterator itS = std::find(pairs.begin(), pairs.end(), swap);
					pairs.erase(itS);
					std::vector<PUJ::Ruta_Aerea>::iterator ruIt = (mIt2->second).begin();
					for( ; ruIt != (mIt2->second).end(); ruIt++)
					{
						str << i << " -> " << j << " [dir=none, label=" << *ruIt << "]; ";
					}
				}
				else if(it!=pairs.end() || itS!=pairs.end())
				{
					std::vector<PUJ::Ruta_Aerea>::iterator ruIt = (mIt2->second).begin();
					for( ; ruIt != (mIt2->second).end(); ruIt++)
					{
						str << i << " -> " << j << " [label=" << *ruIt << "]; ";
					}
				}
			}
		}
	}
	str << "}\" | dot -Tpng > " << file;

	std::system( str.str( ).c_str( ) );
}
