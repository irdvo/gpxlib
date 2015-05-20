#ifndef WPT_H
#define WPT_H

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
//  $Date$ $Revision$
//
//==============================================================================

#include "gpx/Node.h"

#include "gpx/String.h"
#include "gpx/Decimal.h"
#include "gpx/Unsigned.h"
#include "gpx/DateTime.h"
#include "gpx/Latitude.h"
#include "gpx/Longitude.h"
#include "gpx/Degrees.h"
#include "gpx/Link.h"
#include "gpx/Fix.h"
#include "gpx/DGPSStation.h"
#include "gpx/Extensions.h"


namespace gpx
{
  ///
  /// @class WPT
  ///
  /// @brief The waypoint class of the gpx library.
  ///
  
  class WPT : public Node
  {
    public:

    ///
    /// Constructor
    ///
    /// @param  parent     the parent node
    /// @param  name       the name of the attribute or element
    /// @param  mandatory  is the attribute or element mandatory ?
    ///
    WPT(Node *parent, const char *name, bool mandatory = false);

    ///
    /// Deconstructor
    ///
    virtual ~WPT();

    // Properties
    
    ///
    /// Get lat
    ///
    /// @return the lat object
    ///
    Latitude  &lat() { return _lat; }

    ///
    /// Get lon
    ///
    /// @return the lon object
    ///
    Longitude  &lon() { return _lon; }

    ///
    /// Get ele
    ///
    /// @return the ele object
    ///
    Decimal  &ele() { return _ele; }

    ///
    /// Get time
    ///
    /// @return the time object
    ///
    DateTime  &time() { return _time; }

    ///
    /// Get magvar
    ///
    /// @return the magvar object
    ///
    Degrees  &magvar() { return _magvar; }

    ///
    /// Get geoidheight
    ///
    /// @return the geoidheight object
    ///
    Decimal  &geoidheight() { return _geoidheight; }

    ///
    /// Get name
    ///
    /// @return the name object
    ///
    String  &name() { return _name; }

    ///
    /// Get &cmt
    ///
    /// @return the &cmt object
    ///
    String  &cmt() { return _cmt; }

    ///
    /// Get desc
    ///
    /// @return the desc object
    ///
    String  &desc() { return _desc; }

    ///
    /// Get src
    ///
    /// @return the src object
    ///
    String  &src() { return _src; }

    ///
    /// Get sym
    ///
    /// @return the sym object
    ///
    String  &sym() { return _sym; }

    ///
    /// Get type
    ///
    /// @return the type object
    ///
    String  &type() { return _type; }

    ///
    /// Get fix
    ///
    /// @return the fix object
    ///
    Fix  &fix() { return _fix; }

    ///
    /// Get sat
    ///
    /// @return the sat object
    ///
    Unsigned  &sat() { return _sat; }

    ///
    /// Get hdop
    ///
    /// @return the hdop object
    ///
    Decimal  &hdop() { return _hdop; }

    ///
    /// Get vdop
    ///
    /// @return the vdop object
    ///
    Decimal  &vdop() { return _vdop; }

    ///
    /// Get pdop
    ///
    /// @return the pdop object
    ///
    Decimal  &pdop() { return _pdop; };

    ///
    /// Get ageofdgpsdata
    ///
    /// @return the ageofdgpsdata object
    ///
    Decimal  &ageofdgpsdata() { return _ageofdgpsdata; }

    ///
    /// Get dgpsid
    ///
    /// @return the dgpsid object
    ///
    DGPSStation  &dgpsid() { return _dgpsid; }

    ///
    /// Get link
    ///
    /// @return the link objects
    ///
    std::list<Node*> link();

    // Methods
    
    ///
    /// Build the node
    ///
    /// @param  name    the name of the node
    /// @param  report  the optional report stream
    ///
    /// @return the node (or 0 if not found)
    ///
    virtual Node *buildElement(const char *name, std::ostream *report);

    
    private:
    
    // Members
    Latitude      _lat;
    Longitude     _lon;
    Decimal       _ele;
    DateTime      _time;
    Degrees       _magvar;
    Decimal       _geoidheight;
    String        _name;
    String        _cmt;
    String        _desc;
    String        _src;
    String        _sym;
    String        _type;
    Fix           _fix;
    Unsigned      _sat;
    Decimal       _hdop;
    Decimal       _vdop;
    Decimal       _pdop;
    Decimal       _ageofdgpsdata;
    DGPSStation   _dgpsid;
    
    // Disable copy constructors
    WPT(const WPT &);
    WPT& operator=(const WPT &);  

  };
  
}

#endif

