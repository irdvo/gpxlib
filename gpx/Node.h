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
  /// @brief The base class.
  ///
  
  class Node
  {
    public:
    
    ///
    /// Constructor
    ///
    /// @param  parent     the parent node
    /// @param  name       the name of the attribute or element
    /// @param  mandatory  is the attribute or element mandatory ?
    ///
    Node(Node *parent, const char *name, bool mandatory);

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
    bool        mandatory() const { return _mandatory; }
    
    ///
    /// Is the node used ?  
    ///
    /// @return is it ?
    ///
    bool        used() const { return _used; }

    
    ///
    /// Set the attribute or element used
    ///
    /// @param  value  is it used ?
    ///
    void        used(bool value) { _used = value; }

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
    Node        *parent() const { return _parent; }

    ///
    /// Get the attributes list
    ///
    /// @return the parent node (or 0)
    ///
    std::list<Node*>   &attributes() { return _attributes; }
    
    ///
    /// Get the elements list
    ///
    /// @return the parent node (or 0)
    ///
    std::list<Node*>   &elements() { return _elements; }
        
    // Methods
    
    ///
    /// Build an attribute node 
    ///
    /// @param  name    the name of the attribute
    /// @param  report  the optional report stream
    ///
    /// @return the node (or 0 if not found)
    ///
    virtual Node *makeAttribute(const char *name, std::ostream *report = 0);

    ///
    /// Build an element node 
    ///
    /// @param  name    the name of the element
    /// @param  report  the optional report stream
    ///
    /// @return the node (or 0 if not found)
    ///
    virtual Node *makeElement(const char *name, std::ostream *report = 0);

    ///
    /// Make the node
    ///
    /// @param  name    the name of the element
    /// @param  report  the optional report stream
    ///
    /// @return the node (or 0 if not found)
    ///
    virtual Node *make(const char *name, std::ostream *report = 0);

    ///
    /// Done building the node
    ///
    /// @return the parent node (or 0 if not found)
    ///
    virtual Node *made() { return _parent; }

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
   
    protected:
      
    ///
    /// Insert a repeating node
    ///
    /// @param  name    the name of the node
    /// @param  node    the node to be inserted
    ///
    void insert(const char *name, Node *node);

    ///
    /// Filter the attributes and elements for a node name
    ///
    /// @param  name    the name of the node
    /// @param  nodes   the destination list for the nodes
    ///
    void filter(const char *name, std::list<Node*> &nodes);
    
    ///
    /// Check if this node or one of its parents is an extension node
    ///
    /// @return is it ?
    ///
    
    bool isExtension();

  private:

    ///
    /// Check if this node has at least one used element
    ///
    /// @return has it ?
    ///

    bool hasUsedElements() const;

    private:
    
    std::string        _name;
    std::string        _value;
    std::list<Node*>   _attributes;
    std::list<Node*>   _elements;
    bool               _mandatory;
    bool               _used;
    Node              *_parent;
    
    // Do not implement
    Node(const Node &);
    Node& operator=(const Node &);
  };
  
}


#endif

