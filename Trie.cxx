//#ifndef __TRIE__HXX__
//#define __TRIE__HXX__

#include "Trie.h"

#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>


PUJ::Trie::Node::
Node( )
{
	this->m_Trie = NULL;
	this->m_Value = "";
}

PUJ::Trie::Node::
~Node( )
{
  typename TChildren::iterator cIt = this->m_Children.begin( );
  for( ; cIt != this->m_Children.end( ); cIt++ )
  {
    //std::cout << "Erasing ...\n";
    delete *cIt;
  }
  this->m_Children.clear();

  if( this->m_Trie != NULL)
  	delete this->m_Trie;
}

const std::string& PUJ::Trie::Node::
GetValue( ) const
{
	return ( this->m_Value );
}

const typename PUJ::Trie* PUJ::Trie::Node::
GetTrie() const
{
	return ( this->m_Trie );
}

void PUJ::Trie::Node::
SetValue( const std::string& v )
{
	this->m_Value = v;
}

void PUJ::Trie::Node::
AddChild( const std::string& v )
{
	Node* newNode = new Node();
	newNode->SetValue(v);
	this->m_Children.push_back( newNode );
}

bool PUJ::Trie::Node::
IsLeaf( ) const
{
	if(this->m_Children.size() == 0)
		return true;
	return false;
}

unsigned int PUJ::Trie::Node::
Weight() const
{
  unsigned int childWeight, treeWeight;
  childWeight = treeWeight = 0;
  typename TChildren::const_iterator itC = this->m_Children.cbegin();
  for(; itC != this->m_Children.cend(); itC++)
  {
    childWeight = (*itC)->Weight();
    treeWeight += childWeight;
  }
  return (1 + treeWeight);
}

bool PUJ::Trie::Node::
Insert( const std::string& v, int a )
{
	if(v.size() == a)
	{
		this->m_Trie = new Trie();
		return true;
	}

	bool encontre = false;

	std::string val = v.substr(0,a+1);

	typename TChildren::const_iterator itC = this->m_Children.cbegin();
	for(; itC != this->m_Children.cend(); itC++)
	{
		if( (*itC)->GetValue() == val)
		{
			encontre = true;
			(*itC)->Insert( v, a+1 );
		}
	}

	if(!encontre)
	{
		this->AddChild( val );
		this->m_Children.back()->Insert( v, a+1 );
	}
}

bool PUJ::Trie::Node::
InsertInto( const std::string& v ) const
{
	return ( this->m_Trie->Insert( v ) );
}

const std::string PUJ::Trie::Node::
Find( const std::string& v, std::string& v2, std::vector<std::string>& retorno, int a ) const
{
	std::string ss;
	if( v.size() <= a)
	{
		if(this->IsLeaf())
		{
			std::string ret = this->m_Value;
			retorno.push_back( ret );
			v2.erase(0,1);
			return ( ret );
		}
		else if ( this->m_Children.size() == 1)
		{
			v2.erase(0,1);
			std::string ret = this->m_Children.front()->Find(v,v2,retorno,a+1);

			return ( ret );
		}
		else
		{
			v2.erase(0,1);

			typename TChildren::const_iterator itC = this->m_Children.cbegin();
			for(; itC != this->m_Children.cend(); itC++)
			{
				std::string sum = ((*itC)->Find(v,v2,retorno,a+1));
				//retorno.push_back( sum );
			}

			return ( this->m_Value );
		}
	}

	std::string val = v.substr(0,a+1);

	typename TChildren::const_iterator itC = this->m_Children.cbegin();
	for(; itC != this->m_Children.cend(); itC++)
	{
		if( (*itC)->GetValue() == val)
		{
			v2.erase(0,1);
			std::string ret2 = ((*itC)->Find(v,v2,retorno,a+1));

			return ( ret2 );
		}

	}
	return ( v );
}

const typename PUJ::Trie::Node* PUJ::Trie::Node::
Find(const std::string &v, int a)
{
	const Node* ret = NULL;
	const Node* retH = NULL;
	if(v == this->m_Value && this->IsLeaf())
		return ( this );

	std::string val = v.substr(0,a+1);

	typename TChildren::const_iterator itC = this->m_Children.cbegin();
	for(; itC != this->m_Children.cend(); itC++)
	{
		//if( (*itC)->GetValue() == val)
		//{
		const Node* retH = (*itC)->Find(v,a+1);
		if(retH != NULL && ret == NULL)
			ret = retH;
		//}
	}

	if(ret == NULL && this->m_Trie != NULL && this->m_Trie->Weight() > 1)
	{
		retH = this->m_Trie->m_Root->Find(v, 0);
		if(retH != NULL)
			ret = retH;
	}

	return ( ret );
}

std::string PUJ::Trie::Node::
PrintAsPNG( ) const
{
  std::stringstream str;
  std::string a = this->m_Value;
  replace(a.begin(), a.end(), ' ', '0');
  if(a=="") a="0";
  if( !this->IsLeaf( ) )
  {
    for(
      typename TChildren::const_iterator cIt = this->m_Children.begin( );
      cIt != this->m_Children.end( );
      ++cIt
      )
    {

    std::string b = ( *cIt )->GetValue( );
    replace(b.begin(), b.end(), ' ', '0');
    if(b=="") b="0";

      str << (unsigned long)this << "->" << (unsigned long)(*cIt) << " ";
      str << (unsigned long)this << " [label="<< a << "]; ";
      str << (unsigned long)( *cIt ) << " [label="<< b << "]; ";
      str << ( *cIt )->PrintAsPNG( );

    } // rof
  }
  else
  {
  	if(this->m_Trie != NULL)
  	{
  		str << (unsigned long)this << "->" << (unsigned long)(this->m_Trie->m_Root) << " [color=red] ";
  		str << this->m_Trie->m_Root->PrintAsPNG();
  	}
    str << (unsigned long)this << " [label=" << a << "]; ";

  }
  return( str.str( ) );
}


//---------------------------------
//TREE
//---------------------------------

PUJ::Trie::
Trie( )
{
	this->m_Root = new Node();
}

PUJ::Trie::
~Trie( )
{
	if(this->m_Root != NULL)
		delete this->m_Root;
}

unsigned int PUJ::Trie::
Weight( ) const
{
  if( this->m_Root != NULL )
    return( this->m_Root->Weight( ) );
  else
    return( 0 );
}

bool PUJ::Trie::
Insert(const std::string& v)
{
	if(this->m_Root != NULL)
	{
		return ( this->m_Root->Insert( v, 0 ) );
	}
	else return false;
}

bool PUJ::Trie::
InsertInto(const std::string& key, const std::string& v)
{
	bool inserted = false;
	if(this->m_Root != NULL)
	{
		const Node* ret = this->m_Root->Find( key , 0);

		if( ret != NULL)
		{
			inserted = ret->InsertInto( v );
		}
	}
	return inserted;
}

//"", login

std::vector<std::string> PUJ::Trie::
Find( const std::string& vP, const std::string& vH ) const
{
	std::vector<std::string> retorno;
	if(this->m_Root != NULL)
	{
		bool isParent = true;
		const Node* reto = this->m_Root->Find( vP , 0);
		if(reto == NULL)
		{
			isParent = false;
			reto = this->m_Root->Find( vH , 0);
		}

		if(reto != NULL && reto->GetTrie() != NULL)
		{

			if(!isParent)
				retorno = reto->GetTrie()->Find( vP , "" );
			else
				retorno = reto->GetTrie()->Find( vP , vH );
			return ( retorno );
		}
		else
		{
			std::string v2 = vH;
			std::string ret = this->m_Root->Find( vH, v2, retorno, 0 );
			if(v2.size() != 0)
			{
				retorno.push_back( "" );
				return ( retorno );
			}
			else
			{
				ret.replace(ret.find(vH),vH.length(),"");

				retorno.push_back( ret );

				return ( retorno );
			}
		}
	}
	else return ( retorno );
}

void PUJ::Trie::
PrintAsPNG( const std::string& filename ) const
{
  std::stringstream str;
  str << "echo \"digraph  G{";
  if( this->m_Root != NULL )
    str << this->m_Root->PrintAsPNG( );
  str << " } \" | dot -Tpng -Gcharset=latin1 > " << filename;
  //std::cout << "\n!!" << str.str().c_str() << "!!\n";
  std::system( str.str( ).c_str( ) );
}


//#endif
