#ifndef BOUNDS_H
#define BOUNDS_H

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
//  $Date$ $Revision$
//
//==============================================================================

#include "gpx/Node.h"

#include "gpx/Latitude.h"
#include "gpx/Longitude.h"

namespace gpx
{
  ///
  /// @class Bounds
  ///
  /// @brief The extent of an element class.
  ///
  
  class Bounds : public Node
  {
    public:

    ///
    /// Constructor
    ///
    /// @param  parent     the parent node
    /// @param  name       the name of the attribute or element
    /// @param  mandatory  is the attribute or element mandatory ?
    ///

    Bounds(Node *parent, const char *name, bool mandatory = false);

    ///
    /// Deconstructor
    ///
    virtual ~Bounds();
    
    // Properties
    
    ///
    /// Get minlat
    ///
    /// @return the minlat object
    ///
    Latitude  &minlat() { return _minlat; };
    
    ///
    /// Get minlon
    ///
    /// @return  the minlon object
    ///
    Longitude &minlon() { return _minlon; };
    
    ///
    /// Get maxlat
    ///
    /// @return  the maxlat object
    ///
    Latitude  &maxlat() { return _maxlat; };
    
    ///
    /// Get maxlon
    ///
    /// @return  the maxlon object
    ///
    Longitude &maxlon() { return _maxlon; };
    
    private:
    
    // Members
    Latitude  _minlat;
    Longitude _minlon;
    Latitude  _maxlat;
    Longitude _maxlon;

    
    // Disable copy constructors
    Bounds(const Bounds &);
    Bounds& operator=(const Bounds &);  

  };
  
}

#endif

