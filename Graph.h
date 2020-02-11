#ifndef __PUJ__GRAPH__H__
#define __PUJ__GRAPH__H__

#include <vector>
#include <list>
#include <map>
#include <deque>

#include "Ruta_Aerea.h"

namespace PUJ
{
	class Graph
	{
		public:
			typedef std::string TValue;
			typedef std::vector<Ruta_Aerea> TCost;
			typedef Graph Self;
			typedef std::vector < TValue > Vertices;
			typedef std::map< long, std::map< long, TCost > > Costs;

		public:
			Graph();
			virtual ~Graph();

			long AddNode(TValue value);
			void AddArc (long a, long b, Ruta_Aerea costo);
			bool HasArc(long a, long b);
			std::string GetNode(long a);
			std::vector< long > GetDijkstra( long seed, bool criterio );
			std::vector< long > GetDijkstraDirect( long seed );
			std::deque < std::string > GetShortestPath ( long a, long b, char criterio);
			std::deque < std::string > GetShortestPath ( TValue a, TValue b, char criterio);
			std::list < long > PrintLevels( long seed );
			long GetSize();

			void PrintAsPNG( std::string file );
			//bool esValidaTeoria();

		private:
			Vertices m_Vertices;
			Costs m_Matrix;
	};



	struct Triple
	{
		long father;
		long son;
		float cost;
		PUJ::Hora horaLlegada;
		int dia;
	};

	struct comparador
	{
    	bool operator()(const Triple& a,const Triple& b) const
   		{
        	return a.cost > b.cost;
    	}
    };
}

//#include "Graph.hxx"

#endif
