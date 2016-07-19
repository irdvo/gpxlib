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
#include <iomanip>

#include "gpx/GPX.h"
#include "gpx/Parser.h"
#include "gpx/Writer.h"
#include "gpx/ReportCerr.h"

using namespace std;

void createGPX(ostream &stream)
{
  gpx::ReportCerr report;

  gpx::GPX *root = new gpx::GPX();

  gpx::Node *current = root;

  int choice = -1;

  while (choice != 0)
  {
    int menu = 1;

    // Show the menu with reflection

    cout << endl << "Menu:" << current->getName() << endl << endl;

    for (list<gpx::Node*>::const_iterator iter = current->getInterfaces().begin(); iter != current->getInterfaces().end(); ++iter)
    {
      cout << left << setw(4) << menu++ << ((*iter)->getType() == gpx::Node::ATTRIBUTE ? "attribute:" : "element:") << (*iter)->getName() << endl;
    }

    cout << left << setw(4) << menu++ << "validate" << endl;
    cout << left << setw(4) << menu << "value" << endl;
    cout << left << setw(4) << 0 << (current == root ? "exit" : "back") << endl;
    cout << endl;

    string value;

    cout << "Choice:";
    getline(cin, value);

    choice = atoi(value.c_str());

    // Process the choice made
    if (choice == menu)
    {
      cout << "Value for " << current->getName() << ":";
      getline(cin, value);

      current->setValue(value);
    }
    else if (choice == menu-1)
    {
      if (current->validate(&report))
      {
        cout << endl << "Validation succesfull" << endl;
      }
      else
      {
        cout << endl << "Validation failed" << endl;
      }
    }
    else if (choice == 0) // Go to the parent in the gpx document
    {
      if (current != root)
      {
        current = current->getParent();

        choice = -1;
      }
    }
    else // Add the menu choice to the gpx document
    {
      menu = 1;

      for (list<gpx::Node*>::const_iterator iter = current->getInterfaces().begin(); iter != current->getInterfaces().end(); ++iter)
      {
        if (menu == choice)
        {
          current = (*iter)->add(&report);
          break;
        }

        menu++;
      }
    }
  }

  gpx::Writer writer;

  writer.write(stream, root, true);
}


void iterateGPX(istream &stream)
{
  gpx::ReportCerr report;

  gpx::Parser parser(&report);

  gpx::GPX *root = parser.parse(stream);

  if (root == 0)
  {
    cerr << "Parsing failed due to " << parser.errorText() << " on line " << parser.errorLineNumber() << " and column " << parser.errorColumnNumber() << endl;
  }
  else
  {
    gpx::Node *current = root;

    int choice = -1;

    while (choice != 0)
    {
      int menu = 1;

      // Show the menu with reflection

      cout << endl << "Menu:" << current->getName() << endl << endl;

      for (list<gpx::Node*>::const_iterator iter = current->getAttributes().begin(); iter != current->getAttributes().end(); ++iter)
      {
        cout << left << setw(4) << menu++ << "attribute:" << (*iter)->getName() << " (" << (*iter)->getValue() << ")" << endl;
      }

      for (list<gpx::Node*>::const_iterator iter = current->getElements().begin(); iter != current->getElements().end(); ++iter)
      {
        cout << left << setw(4) << menu++ << "element:" << (*iter)->getName() << " (" << (*iter)->getValue() << ")" << endl;
      }

      cout << left << setw(4) << menu << "validate" << endl;
      cout << left << setw(4) << 0 << (current == root ? "exit" : "back") << endl;
      cout << endl;

      string value;

      cout << "Choice:";
      getline(cin, value);

      choice = atoi(value.c_str());

      // Process the choice made
      if (choice == 0) // Go to the parent in the gpx document
      {
        if (current != root)
        {
          current = current->getParent();

          choice = -1;
        }
      }
      else if (choice == menu) // Validation of the current node
      {
        if (current->validate(&report))
        {
          cout << endl << "Validation succesfull" << endl;
        }
        else
        {
          cout << endl << "Validation failed" << endl;
        }
      }
      else // Add the menu choice to the gpx document
      {
        menu = 1;

        for (list<gpx::Node*>::const_iterator iter = current->getAttributes().begin(); iter != current->getAttributes().end(); ++iter)
        {
          if (menu == choice)
          {
            current = (*iter);
            break;
          }

          menu++;
        }

        for (list<gpx::Node*>::const_iterator iter = current->getElements().begin(); iter != current->getElements().end(); ++iter)
        {
          if (menu == choice)
          {
            current = (*iter);
            break;
          }

          menu++;
        }
      }
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc > 2)
  {
    cerr << "Usage: gpxi [file]" << endl;
    exit(1);
  }

  fstream stream;

  if (argc == 2)
  {
    stream.open(argv[1], ios_base::in);

    if (stream.is_open())
    {
      iterateGPX(stream);

      stream.close();
    }
    else
    {
      stream.open(argv[1], ios_base::out);

      if (stream.is_open())
      {
        createGPX(stream);

        stream.close();
      }
      else
      {
        createGPX(cout);
      }
    }
  }
  else
  {
    createGPX(cout);
  }

  exit(0);
}
