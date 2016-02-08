//==============================================================================
//
//                gpxwpt - the gpxwpt example
//
//               Copyright (C) 2013  Dick van Oudheusden
//--
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
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
#include <string>
#include <sstream>

#include "gpx/Parser.h"
#include "gpx/Writer.h"

using namespace std;

const string test_file = "test.gpx";

using namespace std;

void doCount(gpx::Node *node, int &attributes, int &elements)
{
  for (list<gpx::Node*>::iterator current = node->getAttributes().begin(); current != node->getAttributes().end(); ++current)
  {
    attributes++;

    doCount((*current), attributes, elements);
  }

  for (list<gpx::Node*>::iterator current = node->getElements().begin(); current != node->getElements().end(); ++current)
  {
    elements++;

    doCount((*current), attributes, elements);
  }
}

void getCounters(gpx::Node *node, int &attributes, int &elements)
{
  attributes = 0;
  elements   = 0;

  if (node != 0)
  {
    doCount(node, attributes, elements);
  }

  // cout << "Attributes:" << attributes << " Elements:" << elements << endl;
}



int main(int argc, char *argv[])
{
  ifstream stream(test_file.c_str());

  if (stream.is_open())
  {
      gpx::Parser parser(&cerr);

      gpx::GPX *root = parser.parse(stream);

      if (root == 0)
      {
        cerr << "Parsing of " << test_file << " failed due to " << parser.errorText() << " on line " << parser.errorLineNumber() << " and column " << parser.errorColumnNumber() << endl;
      }
      else
      {
        int attributes = 0;
        int elements   = 0;

        getCounters(root, attributes, elements);

        cout << endl << "Tests:" << endl << endl;

        cout << "Initial count of attributes and elements: ";
        if ((attributes == 41) || (elements == 67))
        {
          cout << "Ok." << endl;
        }
        else
        {
          cout << "Failed." << endl;
        }

        {
          stringstream stream;

          root->version().add(&stream);

          cout << "Add already present attribute: ";
          if (stream.str().find("Warning") != string::npos)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << stream.str() << endl;
          }
        }

        {
          stringstream stream;

          root->add("version", gpx::Node::ATTRIBUTE, &stream);

          cout << "Add already present attribute by name: ";
          if (stream.str().find("Warning") != string::npos)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << stream.str() << endl;
          }
        }

        {
          stringstream stream;

          root->metadata().add(&stream);

          cout << "Add already present element: ";
          if (stream.str().find("Warning") != string::npos)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << stream.str() << endl;
          }
        }

        {
          stringstream stream;

          root->add("metadata", gpx::Node::ELEMENT, &stream);

          cout << "Add already present element by name: ";
          if (stream.str().find("Warning") != string::npos)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << stream.str() << endl;
          }
        }

        cout << "Count of attributes and elements after adding already present nodes: ";
        getCounters(root, attributes, elements);
        if ((attributes == 41) || (elements == 67))
        {
          cout << "Ok." << endl;
        }
        else
        {
          cout << "Failed." << endl;
        }


        gpx::WPT *wpt1;
        {
          stringstream stream;

          wpt1 = dynamic_cast<gpx::WPT*>(root->wpts().add(&stream));

          cout << "Add new list element: ";
          if (stream.str().find("Warning") == string::npos)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << stream.str() << endl;
          }
        }

        gpx::WPT *wpt2;
        {
          stringstream stream;

          wpt2 = dynamic_cast<gpx::WPT*>(root->add("wpt", gpx::Node::ELEMENT, &stream));

          cout << "Add new list element by name: ";
          if (stream.str().find("Warning") == string::npos)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << stream.str() << endl;
          }
        }

        cout << "Count of attributes and elements after adding list elements: ";
        getCounters(root, attributes, elements);
        if ((attributes == 41) || (elements == 69))
        {
          cout << "Ok." << endl;
        }
        else
        {
          cout << "Failed." << endl;
        }



        {
          stringstream stream;

          wpt1->lat().add(&stream);

          cout << "Add new attribute: ";
          if (stream.str().find("Warning") == string::npos)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << stream.str() << endl;
          }
        }

        gpx::Longitude *lon2;

        {
          stringstream stream;

          lon2 = dynamic_cast<gpx::Longitude*>(wpt2->add("lon", gpx::Node::ATTRIBUTE, &stream));

          cout << "Add new attribute by name: ";
          if (stream.str().find("Warning") == string::npos)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << stream.str() << endl;
          }
        }

        cout << "Count of attributes and elements after adding attributes: ";
        getCounters(root, attributes, elements);
        if ((attributes == 43) || (elements == 69))
        {
          cout << "Ok." << endl;
        }
        else
        {
          cout << "Failed." << endl;
        }


        {
          stringstream stream;

          root->metadata().author().add(&stream);

          cout << "Add new element: ";
          if (stream.str().find("Warning") == string::npos)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << stream.str() << endl;
          }
        }

        {
          stringstream stream;

          root->metadata().add("keywords", gpx::Node::ELEMENT, &stream);

          cout << "Add new element by name: ";
          if (stream.str().find("Warning") == string::npos)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << stream.str() << endl;
          }
        }

        cout << "Count of attributes and elements after adding elements: ";
        getCounters(root, attributes, elements);
        if ((attributes == 43) || (elements == 71))
        {
          cout << "Ok." << endl;
        }
        else
        {
          cout << "Failed." << endl;
        }


        {
          cout << "Initial attribute value: ";
          if (lon2->getValue() == "")
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << lon2->getValue() << endl;
          }

          lon2->setValue("50.8343");

          cout << "Setting attribute value: ";
          if (wpt2->lon().getValue() == "50.8343")
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << wpt2->lon().getValue() << endl;
          }
        }

        {
          cout << "Initial element value: ";
          if (root->metadata().keywords().getValue() == "")
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << root->metadata().keywords().getValue() << endl;
          }

          root->metadata().keywords().setValue("Official");

          cout << "Setting element value: ";
          if (root->metadata().keywords().getValue() == "Official")
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << root->metadata().keywords().getValue() << endl;
          }
        }

        cout << "Count of attributes and elements after setting values: ";
        getCounters(root, attributes, elements);
        if ((attributes == 43) || (elements == 71))
        {
          cout << "Ok." << endl;
        }
        else
        {
          cout << "Failed." << endl;
        }


        {
          cout << "Count elements of list element: ";
          if (root->wpts().list().size() == 4)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << root->wpts().list().size() << endl;
          }
        }


        {
          stringstream stream;

          cout << "Delete missing attribute: ";
          wpt2->remove(&wpt2->lat(), &stream);

          if (stream.str().find("Warning") != string::npos)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << stream.str() << endl;
          }
        }

        {
          stringstream stream;

          cout << "Delete missing element: ";
          wpt2->remove(&wpt2->name(), &stream);

          if (stream.str().find("Warning") != string::npos)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << stream.str() << endl;
          }
        }

        cout << "Count of attributes and elements after removing missing nodes: ";
        getCounters(root, attributes, elements);
        if ((attributes == 43) || (elements == 71))
        {
          cout << "Ok." << endl;
        }
        else
        {
          cout << "Failed." << endl;
        }


        {
          stringstream stream;

          cout << "Delete present attribute: ";
          wpt2->remove(&wpt2->lon(), &stream);

          if (stream.str().find("Warning") == string::npos)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << stream.str() << endl;
          }
        }

        {
          stringstream stream;

          cout << "Delete present element: ";
          root->remove(&root->metadata(), &stream);

          if (stream.str().find("Warning") == string::npos)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << stream.str() << endl;
          }
        }

        cout << "Count of attributes and elements after removing missing nodes: ";
        getCounters(root, attributes, elements);
        if ((attributes == 37) || (elements == 66))
        {
          cout << "Ok." << endl;
        }
        else
        {
          cout << "Failed." << endl;
        }

        /// ToDo: Delete present list element


        {
          stringstream stream;

          cout << "Add deleted element: ";
          root->metadata().add(&stream);

          if (stream.str().find("Warning") == string::npos)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << stream.str() << endl;
          }

          cout << "Count of attributes and elements after readding node: ";
          getCounters(root, attributes, elements);
          if ((attributes == 37) || (elements == 67))
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed." << endl;
          }
        }
      }

      stream.close();
  }
  else
  {
    cerr << "Test file: " << test_file << " not found." << endl;
  }

  exit(0);
}
