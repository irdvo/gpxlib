//==============================================================================
//
//           Decimal - the Decimal simple type in the GPX library
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

#include "gpx/Decimal.h"

using namespace std;

namespace gpx
{
  Decimal::Decimal(Node *parent, const char *name, Node::Type type, bool mandatory) :
    Node(parent, name, type, mandatory)
  {
  }

  Decimal::~Decimal()
  {
  }
  
  bool Decimal::validate(Report *report) const
  {
    bool ok = Node::validate(report);
    
    if (ok)
    {
      float value = 0.0F;

      if (!convert(value))
      {
        if (report != 0)
        {
          report->report(this, Report::INCORRECT_VALUE, this->getValue());
        }
        ok = false;
      }
    }

    return ok;
  }

  bool Decimal::convert(float &value) const
  {
    int   length   = getValue().length();
    int   i        = 0;
    bool  negative = false;
    float fraction = 0.1F;

    value = 0.0F;

    while ((i < length) && (isspace(getValue().at(i))))
    {
      i++;
    }

    if ((i < length) && ((getValue().at(i) == '+') || (getValue().at(i) == '-')))
    {
      negative = (getValue().at(i) == '-');

      i++;
    }

    while ((i < length) && (isdigit(getValue().at(i))))
    {
      value = value * 10.0F + (float)(getValue().at(i) - '0');

      i++;
    }

    if ((i < length) && (getValue().at(i) == '.'))
    {
      i++;
    }

    while ((i < length) && (isdigit(getValue().at(i))))
    {
      value    += fraction * (float)(getValue().at(i) - '0');
      fraction *= 0.1F;

      i++;
    }

    while ((i < length) && (isspace(getValue().at(i))))
    {
      i++;
    }

    if (negative)
    {
      value = -value;
    }

    return (i == length);
  }
}

