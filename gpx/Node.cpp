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
//  $Date: 2013-03-11 20:15:40 +0100 (Mon, 11 Mar 2013) $ $Revision: 7 $
//
//==============================================================================

#include <strings.h>

#include "gpx/Node.h"

using namespace std;

namespace gpx
{
  Node::Node(Node *parent, const char *name, gpx::Node::Type type, bool mandatory) :
    _parent(parent),
    _name(name),
    _type(type),
    _mandatory(mandatory),
    _interfaces(),
    _attributes(),
    _elements()
  {
  }

  Node::~Node()
  {
  }

  Node *Node::add(std::ostream *report)
  {
    if (_parent != 0)
    {
      if (used())
      {
        if (report != 0)
        {
          *report << "Warning: " << _name << " is already present, skipped." << std::endl;
        }
      }
      else
      {
        if (_type == ATTRIBUTE)
        {
          _parent->getAttributes().push_back(this);
        }
        else if (_type == ELEMENT)
        {
          _parent->getElements().push_back(this);
        }
      }
    }

    return this;
  }

  Node *Node::add(const char *name, Type type, std::ostream *report)
  {
    for (list<Node*>::iterator iter = _interfaces.begin(); iter != _interfaces.end(); ++iter)
    {
      if (strcasecmp(name, (*iter)->getName().c_str()) == 0)
      {
        return (*iter)->add();
      }
    }

    if ((report != 0) && (!isExtension()))
    {
      *report << "Warning: Unknown attribute " << name << " for " << _name << ", added." << endl;
    }

    Node *node = new Node(this, name, type, false);

    if (type == ATTRIBUTE)
    {
      _attributes.push_back(node);
    }
    else if (type == ELEMENT)
    {
      _elements.push_back(node);
    }

    return node;
  }
  
  bool Node::validate(std::ostream *report) const
  {
    bool ok = true;
    
    if (_mandatory)
    {
      if (*report != 0)
      {
        *report << "Missing: " << _name << endl;
      }
      ok = false;
    }

    {
      list<Node*>::const_iterator iter = _attributes.begin();
      list<Node*>::const_iterator end  = _attributes.end();
      
      while (iter != end)
      {
        ok &= (*iter)->validate(report);
        
        ++iter;
      }
    }

    {
      list<Node*>::const_iterator iter = _elements.begin();
      list<Node*>::const_iterator end  = _elements.end();
      
      while (iter != end)
      {
        ok &= (*iter)->validate(report);
        
        ++iter;
      }
    }
    
    return ok;
  }

  bool Node::write(ostream &output, int level) const
  {
    indent(output, level);

    // Start of tag
    output << '<' << getName();

    // attributes
    for (list<Node*>::const_iterator iter = _attributes.begin(); iter != _attributes.end(); ++iter)
    {
      output << ' ' << (*iter)->getName() << "=\"" << (*iter)->getValue() << '"';
    }

    // End of tag
    output << '>';

    if ((hasElements()) && (level >= 0))
    {
      output << endl;
    }
    
    // child tags
    int next = (level >= 0 ? level+1 : level);

    for (list<Node*>::const_iterator iter = _elements.begin(); iter != _elements.end(); ++iter)
    {
      (*iter)->write(output, next);
    }

    // Value
    output << getValue();

    // Close tag
    if ((hasElements()) && (level >= 0))
    {
      indent(output, level);
    }

    output << "</" << getName() << '>';

    if (level >= 0)
    {
      cout << endl;
    }

    return true;
  }

  void Node::indent(std::ostream &output, int level) const
  {
    while (level > 0)
    {
      output << ' ';

      level--;
    }
  }

  int Node::count() const
  {
    int count = 0;

    if (_parent != 0)
    {
      list<Node*> &nodes = (_type == ATTRIBUTE ? _parent->getAttributes() : _parent->getElements());

      for (list<Node*>::const_iterator iter = nodes.begin(); iter != nodes.end(); ++iter)
      {
        if (strcasecmp(_name.c_str(), (*iter)->getName().c_str()) == 0)
        {
          count++;
        }
      }
    }

    return count;
  }

  bool Node::used() const
  {
    if (_parent != 0)
    {
      list<Node*> &nodes = (_type == ATTRIBUTE ? _parent->getAttributes() : _parent->getElements());

      for (list<Node*>::const_iterator iter = nodes.begin(); iter != nodes.end(); ++iter)
      {
        if (strcasecmp(_name.c_str(), (*iter)->getName().c_str()) == 0)
        {
          return true;
        }
      }
    }

    return false;
  }

  
  bool Node::isExtension() const
  {
    const Node *node = this;
    
    while (node != 0)
    {
      if (strcasecmp(node->getName().c_str(), "extensions") == 0)
      {
        return true;
      }
      
      node = node->getParent();
    }
    
    return false;
  }

  bool Node::hasElements() const
  {
    return (!_elements.empty());
  }
}

