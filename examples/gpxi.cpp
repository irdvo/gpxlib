//==============================================================================
//
//              gpxi - the gpx interactive build example
//
//               Copyright (C) 2015  Dick van Oudheusden
//--
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free
// Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//==============================================================================
//-
//  $Date: 2013-03-10 12:02:27 +0100 (Sun, 10 Mar 2013) $ $Revision: 5 $
//
//==============================================================================
//

#include <fstream>
#include <iostream>
#include <cstdlib>

#include "gpx/Node.h"
#include "gpx/GPX.h"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc > 2)
  {
    cerr << "Usage: gpxi file" << endl;
    exit(1);
  }

  // Create the root node
  gpx::Node *root = new gpx::GPX(0, "gpx", true);

  gpx::Node *current = root;
  current = current->buildAttribute("version", &cerr);
  current->value("1.1");
  current = current->built();

  current = current->buildAttribute("creator", &cerr);
  current->value("gpxi");
  current = current->built();

  char choice = ' ';

  while (choice != 'q')
  {
    char menu = 'a';

    do
    {
      menu = 'a';

      cout << "Menu:" << current->name() << endl;

      // Attributes
      list<gpx::Node*>::const_iterator iter = current->attributes().begin();
      list<gpx::Node*>::const_iterator end  = current->attributes().end();

      while (iter != end)
      {
        cout << menu++ << " attribute:" << (*iter)->name() << endl;

        ++iter;
      }

      // Elements
      iter = current->elements().begin();
      end  = current->elements().end();

      while (iter != end)
      {
        cout << menu++ << " element:" << (*iter)->name() << endl;

        ++iter;
      }

      cout << "q exit" << endl;
      cout << endl;

      cout << "Choice:";
      cin >> choice;
    }
    while ((choice != 'q') && ((choice < 'a') || (choice >= menu)));
  }

  root->built();


  if (argc == 1)
  {
    root->write(cout, 0);
  }
  else
  {
    ofstream stream(argv[1]);

    if (stream.is_open())
    {
      root->write(stream, 0);

      stream.close();
    }
    else
    {
      cerr << "File: " << argv[1] << " could not be created." << endl;
    }
  }

  exit(0);
}
