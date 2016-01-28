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
  Node::Node(Node *parent, const char *name, bool mandatory) :
    _name(name),
    _mandatory(mandatory),
    _used(false),
    _attributes(),
    _elements(),
    _parent(parent)
  {
  }

  Node::~Node()
  {
  }
  
  Node *Node::buildAttribute(const char *name, std::ostream *report)
  {
    {
      list<Node*>::const_iterator iter = _attributes.begin();
      list<Node*>::const_iterator end  = _attributes.end();
      
      while (iter != end)
      {
        if (strcasecmp(name, (*iter)->name().c_str()) == 0)
        {
          return (*iter);
        }
        
        ++iter;
      }
    }
    
    if ((report != 0) && (!isExtension()))
    {
      *report << "Unexpected attribute " << name << " for " << this->name() << endl;
    }
    
    Node *node = new Node(this, name, false);
    
    _attributes.push_back(node);
    
    return node;
  }
  
  Node *Node::buildElement(const char *name, std::ostream *report)
  {
    {
      list<Node*>::const_iterator iter = _elements.begin();
      list<Node*>::const_iterator end  = _elements.end();
      
      while (iter != end)
      {
        if (strcasecmp(name, (*iter)->name().c_str()) == 0)
        {
          return (*iter);
        }
        
        ++iter;
      }
    }

    if (report != 0)
    {
      *report << "Unexpected element " << name << " for " << this->name() << endl;
    }

    Node *node = new Node(this, name, false);
    
    _elements.push_back(node);
    
    return node;
  }

  bool Node::validate(std::ostream *report) const
  {
    bool ok = true;
    
    if ((_mandatory) && (_used))
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
    output << '<' << name();

    // attributes
    list<Node*>::const_iterator iter  = _attributes.begin();
    list<Node*>::const_iterator end   = _attributes.end();

    while (iter != end)
    {
      if ((*iter)->used())
      {
        output << ' ' << (*iter)->name() << "=\"" << (*iter)->value() << '"';
      }

      ++iter;
    }

    // End of tag
    output << '>';

    if ((hasUsedElements()) && (level >= 0))
    {
      output << endl;
    }
    
    // child tags
    int next = (level >= 0 ? level+1 : level);

    iter = _elements.begin();
    end  = _elements.end();

    while (iter != end)
    {
      if ((*iter)->used())
      {
        (*iter)->write(output, next);
      }

      ++iter;
    }

    // Value
    if (used())
    {
      output << value();
    }

    // Close tag
    indent(output, level);

    output << "</" << name() << '>';

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
  
  void Node::insert(const char *name, Node *node)
  {
    list<Node*>::      iterator iter = elements().begin();
    list<Node*>::const_iterator end  = elements().end();
    list<Node*>::      iterator last = elements().end();
      
    while (iter != end)
    {
      if (strcasecmp(name, (*iter)->name().c_str()) == 0)
      {
        last = iter;
      }
        
      ++iter;
    }
      
    if (last != end)
    {
      ++last;
    }
      
    if (last == end)
    {
      elements().push_back(node);
    }
    else
    {
      elements().insert(last, node);
    }
  }

  void Node::filter(const char *name, list<Node*> &nodes)
  {
    {
      list<Node*>::const_iterator iter = _attributes.begin();
      list<Node*>::const_iterator end  = _attributes.end();
      
      while (iter != end)
      {
        if (strcasecmp(name, (*iter)->name().c_str()) == 0)
        {
          nodes.push_back(*iter);
        }
        
        ++iter;
      }
    }

    {
      list<Node*>::const_iterator iter = _elements.begin();
      list<Node*>::const_iterator end  = _elements.end();
      
      while (iter != end)
      {
        if (strcasecmp(name, (*iter)->name().c_str()) == 0)
        {
          nodes.push_back(*iter);
        }
        
        ++iter;
      }
    }
  }
  
  bool Node::isExtension()
  {
    Node *node = this;
    
    while (node != 0)
    {
      if (strcasecmp(node->name().c_str(), "extensions") == 0)
      {
        return true;
      }
      
      node = node->parent();
    }
    
    return false;
  }

  bool Node::hasUsedElements() const
  {
    list<Node*>::const_iterator iter = _elements.begin();
    list<Node*>::const_iterator end  = _elements.end();

    while (iter != end)
    {
      if ((*iter)->used())
      {
        return true;
      }

      ++iter;
    }

    return false;
  }
}

