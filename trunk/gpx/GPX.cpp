//==============================================================================
//
//                GPX - the main class in the GPX library
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
#include <cstring>

#include "gpx/GPX.h"


using namespace std;

namespace gpx
{

  GPX::GPX(Node *parent, const char *name, bool mandatory) :
    Node(parent, name, mandatory),
    _version(this, "version", true),
    _creator(this, "creator", true),
    _metadata(this, "metadata", false),
    _extensions(this, "extensions", false)
  {
    attributes().push_back(&_version);
    attributes().push_back(&_creator);

    elements().push_back(&_metadata);
    elements().push_back(&_extensions);
  }

  GPX::~GPX()
  {
  }

  // Building

  Node *GPX::buildElement(const char *name, std::ostream *report)
  {
    Node *node = 0;

    if (strcasecmp(name, "wpt") == 0)
    {
      node = new WPT(this, name, false);
    }
    else if (strcasecmp(name, "rte") == 0)
    {
      node = new RTE(this, name, false);
    }
    else if (strcasecmp(name, "trk") == 0)
    {
      node = new TRK(this, name, false);
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

  // Properties

  list<Node*> GPX::wpt()
  {
    list<Node*> nodes;

    filter("wpt", nodes);

    return nodes;
  }

  list<Node*> GPX::rte()
  {
    list<Node*> nodes;

    filter("rte", nodes);

    return nodes;
  }

  list<Node*> GPX::trk()
  {
    list<Node*> nodes;

    filter("trk", nodes);

    return nodes;
  }
}
