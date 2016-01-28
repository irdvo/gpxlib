#ifndef PTLIST_H
#define PTLIST_H

//==============================================================================
//
//           PTList - the Point list class in the GPX library
//
//               Copyright (C) 2016  Dick van Oudheusden
//  
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, odynamic_cast<gpx::TRKSeg*> (at your option) any later version.
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

#include "gpx/PT.h"


namespace gpx
{
  ///
  /// @class PTList
  ///
  /// @brief The point list class of the gpx library.
  ///
  
  class PTList : public Node
  {
    public:

    ///
    /// Constructor
    ///
    /// @param  parent     the parent node
    /// @param  name       the name of the attribute or element
    /// @param  mandatory  is the attribute or element mandatory ?
    ///
    PTList(Node *parent, const char *name, bool mandatory = false);

    ///
    /// Deconstructor
    ///
    virtual ~PTList();

    // Properties

    std::list<PT*> &list() { return _list;}

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
    std::list<PT *> _list;
    
    // Disable copy constructors
    PTList(const PTList &);
    PTList& operator=(const PTList &);
  };
  
}

#endif

