#ifndef NODE_H
#define NODE_H

//==============================================================================
//
//                   Node - the gpx node class
//
//               Copyright (C) 2013  Dick van Oudheusden
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

#include <string>
#include <iostream>
#include <list>

namespace gpx
{
  ///
  /// @class Node
  ///
  /// @brief The base node class.
  ///
  
  class Node
  {
    public:

    ///
    /// Node type
    ///
    enum Type
    {
      ATTRIBUTE,
      ELEMENT
    };
    
    ///
    /// Constructor
    ///
    /// @param  parent     the parent node
    /// @param  name       the name of the attribute or element
    /// @param  type       the node type (ATTRIBUTE or ELEMENT)
    /// @param  mandatory  is the attribute or element mandatory ?
    ///
    Node(Node *parent, const char *name, Type type, bool mandatory);

    ///
    /// Deconstructor
    ///
    virtual ~Node();
    
    
    // Properties
    
    ///
    /// Return the name
    ///
    /// @return the name of the attribute or element
    ///
    const std::string &name() const { return _name; }

    ///
    /// Return the type
    ///
    /// @return the name of the attribute or element
    ///
    Node::Type type() const { return _type; }

    ///
    /// Return the value
    ///
    /// @return the value of the attribute or element
    ///
    virtual const std::string &value() const { return _value; }

    ///
    /// Is mandatory
    ///
    /// @return is the attribute or element mandatory
    ///
    bool mandatory() const { return _mandatory; }
    
    ///
    /// Set the value
    ///
    /// @param value   the value of the attribute or element
    ///
    virtual void value(std::string value) { _value = value; }
    
    ///
    /// Get the parent node of this node
    ///
    /// @return the parent node (or 0)
    ///
    Node *parent() const { return _parent; }

    ///
    /// Get the interfaces list
    ///
    /// @return the parent node (or 0)
    ///
    ///
    std::list<Node*> &interfaces() { return _interfaces; }

    ///
    /// Get the attributes list
    ///
    /// @return the parent node (or 0)
    ///
    std::list<Node*> &attributes() { return _attributes; }
    
    ///
    /// Get the elements list
    ///
    /// @return the parent node (or 0)
    ///
    std::list<Node*> &elements() { return _elements; }
        
    // Methods
    
    ///
    /// Add this node
    ///
    /// @param  report  the optional report stream
    ///
    /// @return the node (or 0 if not found)
    ///

    virtual Node *add(std::ostream *report = 0);

    ///
    /// Add a node by name
    ///
    /// @param  name    the name of the node
    /// @param  type    the type of the node
    /// @param  report  the optional report stream
    ///
    /// @return the node (or 0 if not found)
    ///
    virtual Node *add(const char *name, Type type, std::ostream *report = 0);

    ///
    /// Done building the node
    ///
    /// @return the parent node (or 0 if not found)
    ///
    virtual Node *added() { return _parent; }

    ///
    /// Validate the object
    ///
    /// @param  report  the optional report stream
    ///
    /// @return is validation succesfull
    ///
    virtual bool validate(std::ostream *report = 0) const;
    
    ///
    /// Write the gpx object to a stream
    ///
    /// @param  output  the output stream
    /// @param  level   the indent level (or <0 for disabled)
    ///
    /// @return is the writting succesfull
    ///
    virtual bool write(std::ostream &output, int level) const;
    
    ///
    /// Indent the current output
    ///
    /// @param  output  the output stream
    /// @param  level  the indent level
    ///
    
    void indent(std::ostream &output, int level) const;
      
    ///
    /// Count the number of occurences of this node in its parent
    ///
    /// @return the number of occurences
    ///
    int count() const;

    ///
    /// Check if this node is used by its parent
    ///
    /// @return the number of occurences
    ///
    bool used() const;

  protected:

    ///
    /// Check if this node or one of its parents is an extension node
    ///
    /// @return is it ?
    ///
    
    bool isExtension() const;

  private:

    ///
    /// Check if this node has at least one element
    ///
    /// @return has it ?
    ///

    bool hasElements() const;

    private:
    
    std::string        _name;
    Type               _type;
    std::string        _value;
    std::list<Node*>   _interfaces;
    std::list<Node*>   _attributes;
    std::list<Node*>   _elements;
    bool               _mandatory;
    Node              *_parent;
    
    // Do not implement
    Node(const Node &);
    Node& operator=(const Node &);
  };
}


#endif

