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
#include "gpx/Writer.h"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc > 2)
  {
    cerr << "Usage: gpxi file" << endl;
    exit(1);
  }

  // Create the root node
  gpx::GPX *root = new gpx::GPX();

  root->version().add(&cerr)->setValue("1.1");
  root->creator().add(&cerr)->setValue("gpxi");

  gpx::Node *current = root;

  char choice = ' ';

  while (choice != 'q')
  {
    char menu = 'a';

    do
    {
      menu = 'a';

      cout << endl << "Menu:" << current->getName() << endl;

      for (list<gpx::Node*>::const_iterator iter = current->getInterfaces().begin(); iter != current->getInterfaces().end(); ++iter)
      {
        string str;

        if ((*iter)->getType() == gpx::Node::ATTRIBUTE)
        {
          str = " attribute:";
        }
        else if ((*iter)->getType() == gpx::Node::ELEMENT)
        {
          str = " element:";
        }
        else
        {
          str = " unknown:";
        }
        cout << menu++ << str << (*iter)->getName() << endl;
      }

      cout << "q exit" << endl;
      cout << endl;

      cout << "Choice:";
      cin >> choice;
    }
    while ((choice != 'q') && ((choice < 'a') || (choice >= menu)));
  }

  root->added();


  gpx::Writer writer;

  if (argc == 1)
  {
    writer.write(cout, root, true);
  }
  else
  {
    ofstream stream(argv[1]);

    if (stream.is_open())
    {
      writer.write(stream, root, true);

      stream.close();
    }
    else
    {
      cerr << "File: " << argv[1] << " could not be created." << endl;
    }
  }

  exit(0);
}
