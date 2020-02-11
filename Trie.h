#ifndef __PUJ__TRIE__H__
#define __PUJ__TRIE__H__

#include <list>
#include <vector>
#include <string>
#include <utility>

namespace PUJ
{
  /**
   */
  class Trie
  {
  public:
    typedef Trie Self;

  protected:
    class Node
    {
    public:
      typedef std::list< Node* > TChildren;

    public:
      Node( );
      virtual ~Node( );

      const std::string& GetValue( ) const;
      const PUJ::Trie* GetTrie() const;
      void SetValue( const std::string& v );
      
      void AddChild( const std::string& v );

      bool IsLeaf( ) const;
      unsigned int Weight() const;

      bool Insert( const std::string& v, int a );
      bool InsertInto( const std::string& v ) const;

      std::string PrintAsPNG( ) const;

      const std::string Find( const std::string& v, std::string& v2, std::vector<std::string>& retorno, int a ) const;
      const Node* Find(const std::string &v, int a);

    protected:
      std::string     m_Value;
      TChildren       m_Children;
      PUJ::Trie*      m_Trie;
      
    };

  public:
    Trie( );
    virtual ~Trie( );

    unsigned int Weight() const;

    bool Insert(const std::string& v);
    bool InsertInto(const std::string& key, const std::string& v);

    std::vector<std::string> Find( const std::string& vP, const std::string& vH ) const;

    void PrintAsPNG( const std::string& filename ) const;

  protected:
    Node* m_Root;
  };

} // ecapseman

//#include "Trie.hxx"

#endif // __PUJ__TRIE__H__

// eof - Trie.h
