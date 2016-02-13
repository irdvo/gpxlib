//==============================================================================
//
//         ReportCerr - the report on cerr class in the GPX library
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
//  $Date: 2013-03-10 12:02:27 +0100 (Sun, 10 Mar 2013) $ $Revision: 5 $
//
//==============================================================================

#include <iostream>

#include "gpx/ReportCerr.h"
#include "gpx/Node.h"

using namespace std;

namespace gpx
{
  ReportCerr::ReportCerr()
  {
  }
  
  ReportCerr::~ReportCerr()
  {
  }

  void ReportCerr::report(const Node *node, Report::Warning warning,  const std::string &extra)
  {
    if (node != 0)
    {
      cerr << (node->getType() == Node::ATTRIBUTE ? "Attribute " : "Element ") << node->getName() << " : ";
    }

    switch(warning)
    {
      case Report::ADD_ALREADY_PRESENT_NODE : cerr << "Trying to add an already present node, ignored"; break;
      case Report::ADD_UNKNOWN_NODE         : cerr << "Unknown child node added"; break;
      case Report::MISSING_MANDATORY_NODE   : cerr << "Mandatory node is missing"; break;
      case Report::REMOVE_UNKNOWN_CHILD     : cerr << "Trying to remove an unknown child node, ignored"; break;
      case Report::INCORRECT_VALUE          : cerr << "Node has an incorrect value"; break;
      case Report::DOUBLE_GPX               : cerr << "GPX source contains a double gpx element"; break;
      case Report::MISSING_GPX              : cerr << "GPX source contains no gpx element"; break;
      case Report::MISFORMED_GPX            : cerr << "GPX source has a misformed layout"; break;
      default                               : cerr << "Unknown warning"; break;
    }

    if (!extra.empty())
    {
      cerr << ": " << extra;
    }

    cerr << "." << endl;
  }
}


