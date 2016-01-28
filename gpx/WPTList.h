#ifndef WPTLIST_H
#define WPTLIST_H

//==============================================================================
//
//           WPTList - the Waypoint list class in the GPX library
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

#include <list>

#include "gpx/WPT.h"


namespace gpx
{
  ///
  /// @class WPTList
  ///
  /// @brief The waypoint list class of the gpx library.
  ///
  
  class WPTList : public Node
  {
    public:

    ///
    /// Constructor
    ///
    /// @param  parent     the parent node
    /// @param  name       the name of the attribute or element
    /// @param  mandatory  is the attribute or element mandatory ?
    ///
    WPTList(Node *parent, const char *name, bool mandatory = false);

    ///
    /// Deconstructor
    ///
    virtual ~WPTList();

    // Properties

    std::list<WPT*> &list() { return _list;}

    // Methods
    
    ///
    /// Build the node
    ///
    /// @param  name    the name of the node
    /// @param  report  the optional report stream
    ///
    /// @return the node (or 0 if not found)
    ///
    virtual Node *make(const char *name, std::ostream *report);

    
    private:
    
    // Members
    std::list<WPT *> _list;
    
    // Disable copy constructors
    WPTList(const WPTList &);
    WPTList& operator=(const WPTList &);
  };
  
}

#endif

