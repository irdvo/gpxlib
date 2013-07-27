#ifndef RTE_H
#define RTE_H

//==============================================================================
//
//                RTE - the Route class in the GPX library
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
#include "gpx/Unsigned.h"
#include "gpx/Link.h"
#include "gpx/Extensions.h"
#include "gpx/WPT.h"


namespace gpx
{
  ///
  /// @class RTE
  ///
  /// @brief The route class of the gpx library.
  ///
  
  class RTE : public Node
  {
    public:

    ///
    /// Constructor
    ///
    /// @param  parent     the parent node
    /// @param  name       the name of the attribute or element
    /// @param  mandatory  is the attribute or element mandatory ?
    ///
    RTE(Node *parent, const char *name, bool mandatory = false);

    ///
    /// Deconstructor
    ///
    virtual ~RTE();
    
    ///
    /// Get name
    ///
    /// @return the name object
    ///
    String  &name() { return _name; };

    ///
    /// Get cmt
    ///
    /// @return the cmt object
    ///
    String  &cmt() { return _cmt; };

    ///
    /// Get desc
    ///
    /// @return the desc object
    ///
    String  &desc() { return _desc; };

    ///
    /// Get src
    ///
    /// @return the src object
    ///
    String  &src() { return _src; };

    ///
    /// Get link
    ///
    /// @return the link objects
    ///
    std::list<Node*> link();

    ///
    /// Get number
    ///
    /// @return the number object
    ///
    Unsigned  &number() { return _number; };

    ///
    /// Get type
    ///
    /// @return the type object
    ///
    String  &type() { return _type; };

    ///
    /// Get extensions
    ///
    /// @return the extensions object
    ///
    Extensions  &extensions() { return _extensions; };

    ///
    /// Get rtept
    ///
    /// @return the rtept objects
    ///
    std::list<Node*> rtept();

    // Methods
    
    ///
    /// Build the element
    ///
    /// @param  name    the name of the element
    /// @param  report  the optional report stream
    ///
    /// @return the node (or 0 if not found)
    ///
    virtual Node *buildElement(const char *name, std::ostream *report = 0);


    private:
    
    // Members
    String     _name;
    String     _cmt;
    String     _desc;
    String     _src;
    Unsigned   _number;
    String     _type;
    Extensions _extensions;

    // Disable copy constructors
    RTE(const RTE &);
    RTE& operator=(const RTE &);  
  };
  
}

#endif

