//==============================================================================
//
//               Degrees - the Degrees type  in the GPX library
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

#include <stdlib.h>

#include "gpx/Degrees.h"

using namespace std;

namespace gpx
{
  Degrees::Degrees(Node *parent, const char *name, bool mandatory) :
    Decimal(parent, name, mandatory)
  {
  }

  Degrees::~Degrees()
  {
  }
  
  bool Degrees::validate(std::ostream *report) const
  {
    bool ok = Decimal::validate(report);
    
    if (used())
    {
      float val = atof(value().c_str());
      
      if ((val < 0.0) || (val > 360.0))
      {
        if (report != 0)
        {
          *report << "Degrees: " << value() << " invalid." << endl;
        }
        ok = false;
      }
    }
    return ok;
  }

}

