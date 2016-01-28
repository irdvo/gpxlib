//==============================================================================
//
//              Bounds - the Bounds class in the GPX library
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

#include "gpx/Metadata.h"


using namespace std;

namespace gpx
{
  Metadata::Metadata(Node *parent, const char *name, bool mandatory) :
    Node(parent, name, mandatory),
    _name(this, "name", false),
    _desc(this, "desc", false),
    _author(this, "author", false),
    _copyright(this, "copyright", false),
    _time(this, "time", false),
    _keywords(this, "keywords", false),
    _bounds(this, "bounds", false),
    _extensions(this, "extensions", false),
    _links(this, "link", false)
  {
    elements().push_back(&_name);
    elements().push_back(&_desc);
    elements().push_back(&_author);
    elements().push_back(&_copyright);
    elements().push_back(&_time);
    elements().push_back(&_keywords);
    elements().push_back(&_bounds);
    elements().push_back(&_extensions);
    elements().push_back(&_links);
  }

  Metadata::~Metadata()
  {
  }
}
