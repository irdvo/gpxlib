//==============================================================================
//
//                WPT - the Waypoint class in the GPX library
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

#include "gpx/WPT.h"


using namespace std;

namespace gpx
{
  WPT::WPT(Node *parent, const char *name, bool mandatory) :
    Node(parent, name, mandatory),
    _lat(this, "lat", true),
    _lon(this, "lon", true),
    _ele(this, "ele", false),
    _time(this, "time", false),
    _magvar(this, "magvar", false),
    _geoidheight(this, "geoidheight", false),
    _name(this, "name", false),
    _cmt(this, "cmt", false),
    _desc(this, "desc", false),
    _src(this, "src", false),
    _sym(this, "sym", false),
    _type(this, "type", false),
    _fix(this, "fix", false),
    _sat(this, "sat", false),
    _hdop(this, "hdop", false),
    _vdop(this, "vdop", false),
    _pdop(this, "pdop", false),
    _ageofdgpsdata(this, "ageofdgpsdata", false),
    _dgpsid(this, "dgpsid", false)
  {
    attributes().push_back(&_lat);
    attributes().push_back(&_lon);
    
    elements().push_back(&_ele);
    elements().push_back(&_time);
    elements().push_back(&_magvar);
    elements().push_back(&_geoidheight);
    elements().push_back(&_name);
    elements().push_back(&_cmt);
    elements().push_back(&_desc);
    elements().push_back(&_src);
    elements().push_back(&_sym);
    elements().push_back(&_type);
    elements().push_back(&_fix);
    elements().push_back(&_sat);
    elements().push_back(&_hdop);
    elements().push_back(&_vdop);
    elements().push_back(&_pdop);
    elements().push_back(&_ageofdgpsdata);
    elements().push_back(&_dgpsid);
  }
  
  WPT::~WPT()
  {
  }

  Node *WPT::buildElement(const char *name, std::ostream *report)
  {
    Node *node = 0;

    if (strcasecmp(name, "link") == 0)
    {
      node = new Link(this, "link", false);
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
  
  std::list<Node*> WPT::link()
  {
    list<Node*> nodes;
    
    filter("link", nodes);
    
    return nodes;
  }
}

