//==============================================================================
//
//                RTE - the Route class in the GPX library
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
//  $Date: 2013-03-10 12:02:27 +0100 (Sun, 10 Mar 2013) $ $Revision: 5 $
//
//==============================================================================

#include <strings.h>

#include "gpx/RTE.h"


using namespace std;

namespace gpx
{
  RTE::RTE(Node *parent, const char *name, bool mandatory) :
    Node(parent, name, mandatory),
    _name(this, "name", false),
    _cmt(this, "cmt", false),
    _desc(this, "desc", false),
    _src(this, "src", false),
    _number(this, "number", false),
    _type(this, "type",   false),
    _extensions(this, "extensions", false)
  {
    elements().push_back(&_name);
    elements().push_back(&_cmt);
    elements().push_back(&_desc);
    elements().push_back(&_src);
    elements().push_back(&_number);
    elements().push_back(&_type);
    elements().push_back(&_extensions);
  }
  
  RTE::~RTE()
  {
  }

  Node *RTE::buildElement(const char *name, std::ostream *report)
  {
    Node *node = 0;

    if (strcasecmp(name, "link") == 0)
    {
      node = new Link(this, "link", false);
    }
    else if (strcasecmp(name, "rtept") == 0)
    {
      node = new WPT(this, "rtept", false);
    } 
    
    if (node != 0)
    {
      insert(name, node);
    }
    else
    {
      node = Node::buildElement(name, report);
    }
    
    return node;
  }

  list<Node*> RTE::link()
  {
    list<Node*> nodes;
    
    filter("link", nodes);
    
    return nodes;
  }
  
  list<Node*> RTE::rtept()
  {
    list<Node*> nodes;
    
    filter("rtept", nodes);
    
    return nodes;
  }
}

