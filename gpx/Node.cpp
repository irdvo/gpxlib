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

#include <cstring>

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

  Node *Node::add(Report *report)
  {
    return insert(0, report);
  }

  Node *Node::add(const char *name, Type type, Report *report)
  {
    return insert(0, name, type, report);
  }

  Node *Node::insert(Node *before, Report *report)
  {
    if (_parent != 0)
    {
      if (used())
      {
        if (report != 0)
        {
          report->report(this, Report::ADD_ALREADY_PRESENT_NODE, "");
        }
      }
      else
      {
        insert(before, (_type == ATTRIBUTE ? _parent->getAttributes() : _parent->getElements()), report);
      }
    }

    return this;
  }

  Node *Node::insert(Node *before, const char *name, Type type, Report *report)
  {
    for (list<Node*>::iterator iter = _interfaces.begin(); iter != _interfaces.end(); ++iter)
    {
      if (strcasecmp(name, (*iter)->getName().c_str()) == 0)
      {
        return (*iter)->insert(before, report);
      }
    }

    if ((report != 0) && (!isExtension()))
    {
      report->report(this, Report::ADD_UNKNOWN_NODE, name);
    }

    Node *node = new Node(this, name, type, false);

    node->insert(before, report);

    return node;
  }


  void Node::copy(Node *source, Report *report)
  {
    setValue(source->getValue());

    for (std::list<gpx::Node*>::iterator node = source->getAttributes().begin(); node != source->getAttributes().end(); ++node)
    {
      gpx::Node *attribute = add((*node)->getName().c_str(), gpx::Node::ATTRIBUTE, report);

      (*node)->copy(attribute, report);
    }

    for (std::list<gpx::Node*>::iterator node = source->getElements().begin(); node != source->getElements().end(); ++node)
    {
      gpx::Node *element = add((*node)->getName().c_str(), gpx::Node::ELEMENT, report);

      (*node)->copy(element, report);
    }
  }

  
  bool Node::validate(Report *report) const
  {
    bool ok = true;

    for (list<Node*>::const_iterator iter = _interfaces.begin(); iter != _interfaces.end(); ++iter)
    {
      if (((*iter)->isMandatory()) && (!(*iter)->used()))
      {
        if (report != 0)
        {
          report->report(this, Report::MISSING_MANDATORY_NODE, "");
        }
        ok = false;
      }
    }
    
    for (list<Node*>::const_iterator iter = _attributes.begin(); iter != _attributes.end(); ++iter)
    {
      ok &= (*iter)->validate(report);
    }

    for (list<Node*>::const_iterator iter = _elements.begin(); iter != _elements.end(); ++iter)
    {
      ok &= (*iter)->validate(report);
    }
    
    return ok;
  }

  bool Node::remove(Node *child, Report *report)
  {
    bool removed = false;

    list<Node*>::iterator iter;

    iter = _attributes.begin();
    while (iter != _attributes.end())
    {
      if ((child == 0) || (child == (*iter)))
      {
        (*iter)->setValue("");

        iter = _attributes.erase(iter);

        removed = true;
      }
      else
      {
        ++iter;
      }
    }

    iter = _elements.begin();
    while (iter != _elements.end())
    {
      if ((child == 0) || (child == (*iter)))
      {
        (*iter)->setValue("");

        (*iter)->remove(0);

        iter = _elements.erase(iter);

        removed = true;
      }
      else
      {
        ++iter;
      }
    }

    for (iter = _interfaces.begin(); iter != _interfaces.end(); ++iter)
    {
      (*iter)->removeAsChild(child);
    }

    if ((!removed) && (child != 0))
    {
      if (report != 0)
      {
        report->report(this, Report::REMOVE_UNKNOWN_CHILD, child->getName());
      }
    }

    return removed;
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

  void Node::insert(Node *before, list<Node*> &nodes, Report *report)
  {
    if (before != 0)
    {
      list<Node*>::iterator node = nodes.begin();

      for (; node != nodes.end(); ++node)
      {
        if ((*node) == before)
        {
          nodes.insert(node, this);
          break;
        }
      }

      if (node == nodes.end())
      {
        report->report(this, Report::INSERT_BEFORE_NODE_NOT_FOUND, "");

        before = 0;
      }
    }

    if (before == 0)
    {
      nodes.push_back(this);
    }
  }

  bool Node::removeAsChild(Node *)
  {
    return false;
  }


}

