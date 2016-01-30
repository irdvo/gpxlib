//==============================================================================
//
//               TRK - the track class in the GPX library
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

#include "gpx/TRK.h"

using namespace std;

namespace gpx
{
  TRK::TRK(Node *parent, const char *name, Node::Type type, bool mandatory) :
    Node(parent, name, type, mandatory),
    _name(this, "name", Node::ELEMENT, false),
    _cmt(this, "cmt",  Node::ELEMENT, false),
    _desc(this, "desc", Node::ELEMENT, false),
    _src(this, "src",  Node::ELEMENT, false),
    _number(this, "number", Node::ELEMENT, false),
    _type(this, "type",   Node::ELEMENT, false),
    _extensions(this, "extensions", Node::ELEMENT, false),
    _trksegs(this, "trkseg", Node::ELEMENT, false),
    _links(this, "link", Node::ELEMENT, false)
  {
    interfaces().push_back(&_name);
    interfaces().push_back(&_cmt);
    interfaces().push_back(&_desc);
    interfaces().push_back(&_src);
    interfaces().push_back(&_number);
    interfaces().push_back(&_type);
    interfaces().push_back(&_extensions);
    interfaces().push_back(&_trksegs);
    interfaces().push_back(&_links);
  }

  TRK::~TRK()
  {
  }
}

