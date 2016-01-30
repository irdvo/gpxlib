#ifndef LIST_H
#define LIST_H

//==============================================================================
//
//             List - the template list class in the GPX library
//
//               Copyright (C) 2016  Dick van Oudheusden
//  
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free
// Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//==============================================================================
// 
//  $Date$ $Revision$
//
//==============================================================================

#include <list>

#include "gpx/Node.h"


namespace gpx
{
  ///
  /// @class List
  ///
  /// @brief The list of nodes template.
  ///
  
  template<class T>
  class List : public Node
  {
    public:

    ///
    /// Constructor
    ///
    /// @param  parent     the parent node
    /// @param  name       the name of the attribute or element
    /// @param  type       the node type (ATTRIBUTE or ELEMENT)
    /// @param  mandatory  is the attribute or element mandatory ?
    ///
    List(Node *parent, const char *name, Node::Type type, bool mandatory = false) :
      Node(parent, name, type, mandatory)
    {

    }

    ///
    /// Deconstructor
    ///
    virtual ~List()
    {
      while (!_list.empty())
      {
        delete _list.back();

        _list.pop_back();
      }
    }

    // Properties

    ///
    /// Return the node list
    ///
    /// @return the list
    ///
    std::list<T*> &list() { return _list;}


    // Methods
    
    ///
    /// Add the node
    ///
    /// @param  report  the optional report stream
    ///
    /// @return the node
    ///
    virtual Node *add(std::ostream *report)
    {
      T *node = new T(parent(), name().c_str(), type(), mandatory());

      if (parent() != 0)
      {
        if (type() == ATTRIBUTE)
        {
          parent()->attributes().push_back(this);
        }
        else if (type() == ELEMENT)
        {
          parent()->elements().push_back(this);
        }
      }

      _list.push_back(node);

      return node;
    }

    private:
    
    // Members
    std::list<T*> _list;
    
    // Disable copy constructors
    List(const List &);
    List& operator=(const List &);
  };
}

#endif

