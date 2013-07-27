#ifndef TRK_SEG_H
#define TRK_SEG_H

//==============================================================================
//
//             TRKSeg - the track segment class in the GPX library
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

#include "gpx/Extensions.h"
#include "gpx/WPT.h"


namespace gpx
{
  ///
  /// @class TRKSeg
  ///
  /// @brief The list of track points class of the gpx library.
  ///
  
  class TRKSeg : public Node
  {
    public:

    ///
    /// Constructor
    ///
    /// @param  parent     the parent node
    /// @param  name       the name of the attribute or element
    /// @param  mandatory  is the attribute or element mandatory ?
    ///
    TRKSeg(Node *parent, const char *name, bool mandatory = false);

    ///
    /// Deconstructor
    ///
    virtual ~TRKSeg();

    ///
    /// Get trkpt
    ///
    /// @return the trkpt objects
    ///
    std::list<Node*>  trkpt();

    ///
    /// Get extensions
    ///
    /// @return the extensions object
    ///
    Extensions  &extensions() { return _extensions; };

    // Methods
    
    ///
    /// Build the element
    ///
    /// @param  name    the name of the element 
    /// @param  report  the optional report stream
    ///
    /// @return the node (or 0 if not found)
    ///
    Node *buildElement(const char *name, std::ostream *report);

    private:
    
    // Members
    Extensions  _extensions;

    // Disable copy constructors
    TRKSeg(const TRKSeg &);
    TRKSeg& operator=(const TRKSeg &);  
  };
}

#endif

