//==============================================================================
//
//                PT - the Point class in the GPX library
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

#include "gpx/PT.h"


using namespace std;

namespace gpx
{
  PT::PT(Node *parent, const char *name, bool mandatory) :
    Node(parent, name, mandatory),
    _lat(this, "lat", true),
    _lon(this, "lon", true),
    _ele(this, "ele",  false),
    _time(this, "time", false)
  {
    attributes().push_back(&_lat);
    attributes().push_back(&_lon);
    
    elements()  .push_back(&_ele);
    elements()  .push_back(&_time);
  }

  PT::~PT()
  {
  }
  
}
