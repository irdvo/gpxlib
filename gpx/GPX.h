#ifndef GPX_H
#define GPX_H

//==============================================================================
//
//                   GPX - the GPX class
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
#include "gpx/Metadata.h" 
#include "gpx/RTEList.h"
#include "gpx/TRKList.h"
#include "gpx/Extensions.h"
#include "gpx/WPTList.h"

///
/// @namespace gpx
///
/// @brief The namespace of the gpx library
///

namespace gpx
{
  ///
  /// @class GPX
  ///
  /// @brief The main class of the gpx library.
  ///

  class GPX : public Node
  {
  public:

    ///
    /// Constructor
    ///
    /// @param  parent     the parent node
    /// @param  name       the name of the attribute or element
    /// @param  mandatory  is the attribute or element mandatory ?
    ///
    GPX(Node *parent, const char *name, bool mandatory = false);

    ///
    /// Deconstructor
    ///
    virtual ~GPX();
    
    ///
    /// Get version
    ///
    /// @return the version object
    ///
    String  &version() { return _version; }

    ///
    /// Get creator
    ///
    /// @return the creator object
    ///
    String  &creator() { return _creator; }

    ///
    /// Get metadata
    ///
    /// @return the metadata object
    ///
    Metadata  &metadata() { return _metadata; }

    ///
    /// Get wpt
    ///
    /// @return the list of wpt objects
    ///
    /// @todo Use list as parameter to prevent coping
    ///
    std::list<WPT*> &wpt() {_wpts.list();}

    ///
    /// Get rte
    ///
    /// @return the list of rte objects
    ///
    std::list<RTE*> &rte() {return _rtes.list();}

    ///
    /// Get trk
    ///
    /// @return the list of trk objects
    ///
    std::list<TRK*> &trk() {return _trks.list();}

    ///
    /// Get extensions
    ///
    /// @return the extensions object
    ///
    Extensions  &extensions() { return _extensions; }

  private:

    // Members

    String      _version;
    String      _creator;
    Metadata    _metadata;
    Extensions  _extensions;
    WPTList     _wpts;
    RTEList     _rtes;
    TRKList     _trks;

    // Disable copy constructors
    GPX(const GPX &);
    GPX& operator=(const GPX &);  
  };
}


#endif

