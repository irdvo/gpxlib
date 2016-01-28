#ifndef META_DATA_H
#define META_DATA_H

//==============================================================================
//
//             Metadata - the Metadata class in the gpx library
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
#include "gpx/Person.h"
#include "gpx/Copyright.h"
#include "gpx/LinkList.h"
#include "gpx/DateTime.h"
#include "gpx/Bounds.h"
#include "gpx/Extensions.h"

namespace gpx
{
  ///
  /// @class Metadata
  ///
  /// @brief The metadata from another schema's class.
  ///
  
  class Metadata : public Node
  {
    public:

    ///
    /// Constructor
    ///
    /// @param  parent     the parent node
    /// @param  name       the name of the attribute or element
    /// @param  mandatory  is the attribute or element mandatory ?
    ///
    Metadata(Node *parent, const char *name, bool mandatory = false);

    ///
    /// Deconstructor
    ///
    virtual ~Metadata();
    
    ///
    /// Get name
    ///
    /// @return the name object
    ///
    String  &name() { return _name; }
    
    ///
    /// Get desc
    ///
    /// @return the desc object
    ///
    String  &desc() { return _desc; }
    
    ///
    /// Get author
    ///
    /// @return the author object
    ///
    Person  &author() { return _author; }
    
    ///
    /// Get copyright
    ///
    /// @return the copyright object
    ///
    Copyright  &copyright() { return _copyright; }
    
    ///
    /// Get link
    ///
    /// @return the link object
    ///
    /// @todo return link
    ///
    std::list<Link*> &link() {_links.list();}
    
    ///
    /// Get time
    ///
    /// @return the time object
    ///
    DateTime  &time() { return _time; }
    
    ///
    /// Get keywords
    ///
    /// @return the keywords object
    ///
    String  &keywords() { return _keywords; }
    
    ///
    /// Get bounds
    ///
    /// @return the bounds object
    ///
    Bounds  &bounds() { return _bounds; }
    
    ///
    /// Get extensions
    ///
    /// @return the extensions object
    ///
    Extensions  &extensions() { return _extensions; }
    
    private:
    
    // Members
    String     _name;
    String     _desc;
    Person     _author;
    Copyright  _copyright;
    DateTime   _time;
    String     _keywords;
    Bounds     _bounds;
    Extensions _extensions;
    LinkList   _links;
    
    // Disable copy constructors
    Metadata(const Metadata &);
    Metadata& operator=(const Metadata &);  
  };
  
}

#endif
