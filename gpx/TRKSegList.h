#ifndef TRKSEGLIST_H
#define TRKSEGLIST_H

//==============================================================================
//
//           TRKSegList - the TRKSeg list class in the GPX library
//
//               Copyright (C) 2016  Dick van Oudheusden
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

#include "gpx/TRKSeg.h"


namespace gpx
{
  ///
  /// @class TRKSegList
  ///
  /// @brief The TRKSeg list class of the gpx library.
  ///
  
  class TRKSegList : public Node
  {
    public:

    ///
    /// Constructor
    ///
    /// @param  parent     the parent node
    /// @param  name       the name of the attribute or element
    /// @param  mandatory  is the attribute or element mandatory ?
    ///
    TRKSegList(Node *parent, const char *name, bool mandatory = false);

    ///
    /// Deconstructor
    ///
    virtual ~TRKSegList();

    // Properties

    std::list<TRKSeg*> &list() { return _list;}

    // Methods
    
    ///
    /// Make the node
    ///
    /// @param  name    the name of the node
    /// @param  report  the optional report stream
    ///
    /// @return the node (or 0 if not found)
    ///
    virtual Node *make(const char *name, std::ostream *report);

    
    private:
    
    // Members
    std::list<TRKSeg *> _list;
    
    // Disable copy constructors
    TRKSegList(const TRKSegList &);
    TRKSegList& operator=(const TRKSegList &);
  };
  
}

#endif

