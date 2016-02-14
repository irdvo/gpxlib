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
#include "gpx/ReportCerr.h"

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

class ReportTest : public gpx::Report
{
public:
  ReportTest() : _warning(gpx::Report::NO_WARNING) {}
  ~ReportTest() {}

  virtual void report(const gpx::Node *, gpx::Report::Warning warning, const string &)
  {
    _warning = warning;
  }

  gpx::Report::Warning warning()
  {
    gpx::Report::Warning temp = _warning;

    _warning = gpx::Report::NO_WARNING;

    return temp;
  }

  gpx::Report::Warning _warning;
};


int main(int argc, char *argv[])
{
  ifstream stream(test_file.c_str());

  if (stream.is_open())
  {
      ReportTest report;

      gpx::Report::Warning warning;

      gpx::Parser parser(&report);

      gpx::GPX *root = parser.parse(stream);

      if (root == 0)
      {
        cerr << "Parsing of " << test_file << " failed due to " << parser.errorText() << " on line " << parser.errorLineNumber() << " and column " << parser.errorColumnNumber() << endl;
      }
      else if (report.warning() != gpx::Report::NO_WARNING)
      {
        cout << "Warnings during parsing" << endl;

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


        cout << "Add already present attribute: ";
          root->version().add(&report);
          warning = report.warning();
          if (warning == gpx::Report::ADD_ALREADY_PRESENT_NODE)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
          }


        cout << "Add already present attribute by name: ";
          root->add("version", gpx::Node::ATTRIBUTE, &report);
          warning = report.warning();
          if (warning == gpx::Report::ADD_ALREADY_PRESENT_NODE)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
          }


        cout << "Add already present element: ";
          root->metadata().add(&report);
          warning = report.warning();
          if (warning == gpx::Report::ADD_ALREADY_PRESENT_NODE)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
          }


        cout << "Add already present element by name: ";
          root->add("metadata", gpx::Node::ELEMENT, &report);
          warning = report.warning();
          if (warning == gpx::Report::ADD_ALREADY_PRESENT_NODE)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
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

        cout << "Add new list element: ";
          wpt1 = dynamic_cast<gpx::WPT*>(root->wpts().add(&report));
          warning = report.warning();
          if (warning == gpx::Report::NO_WARNING)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
          }

        gpx::WPT *wpt2;

        cout << "Add new list element by name: ";
          wpt2 = dynamic_cast<gpx::WPT*>(root->add("wpt", gpx::Node::ELEMENT, &report));
          warning = report.warning();
          if (warning == gpx::Report::NO_WARNING)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
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



        cout << "Add new attribute: ";
          wpt1->lat().add(&report);
          warning = report.warning();
          if (warning == gpx::Report::NO_WARNING)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
          }

        gpx::Longitude *lon2;

        cout << "Add new attribute by name: ";
          lon2 = dynamic_cast<gpx::Longitude*>(wpt2->add("lon", gpx::Node::ATTRIBUTE, &report));
          warning = report.warning();
          if (warning == gpx::Report::NO_WARNING)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
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


        cout << "Add new element: ";
          root->metadata().author().add(&report);
          warning = report.warning();
          if (warning == gpx::Report::NO_WARNING)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
          }

        cout << "Add new element by name: ";
          root->metadata().add("keywords", gpx::Node::ELEMENT, &report);
          warning = report.warning();
          if (warning == gpx::Report::NO_WARNING)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
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


        cout << "Initial attribute value: ";
          if (lon2->getValue() == "")
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << lon2->getValue() << endl;
          }

        cout << "Setting attribute value: ";
          lon2->setValue("50.8343");
          if (wpt2->lon().getValue() == "50.8343")
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << wpt2->lon().getValue() << endl;
          }

        cout << "Initial element value: ";
          if (root->metadata().keywords().getValue() == "")
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << root->metadata().keywords().getValue() << endl;
          }

        cout << "Setting element value: ";
          root->metadata().keywords().setValue("Official");
          if (root->metadata().keywords().getValue() == "Official")
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << root->metadata().keywords().getValue() << endl;
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


        cout << "Count elements of list element: ";
          if (root->wpts().list().size() == 4)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << root->wpts().list().size() << endl;
          }


        cout << "Delete missing attribute: ";
          wpt2->remove(&wpt2->lat(), &report);
          warning = report.warning();
          if (warning == gpx::Report::REMOVE_UNKNOWN_CHILD)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
          }

        cout << "Delete missing element: ";
          wpt2->remove(&wpt2->name(), &report);
          warning = report.warning();
          if (warning == gpx::Report::REMOVE_UNKNOWN_CHILD)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
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

        cout << "Delete present attribute: ";
          wpt2->remove(&wpt2->lon(), &report);
          warning = report.warning();
          if (warning == gpx::Report::NO_WARNING)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
          }

        cout << "Delete present element: ";
          root->remove(&root->metadata(), &report);
          warning = report.warning();
          if (warning == gpx::Report::NO_WARNING)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
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

        cout << "Add deleted element: ";
          root->metadata().add(&report);
          warning = report.warning();
          if (warning == gpx::Report::NO_WARNING)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
          }

        cout << "Count of attributes and elements after reading node: ";
          getCounters(root, attributes, elements);
          if ((attributes == 37) || (elements == 67))
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed." << endl;
          }

        cout << "Delete present list element: ";
          root->remove(wpt2, &report);
          warning = report.warning();
          if (warning == gpx::Report::NO_WARNING)
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed: " << warning << endl;
          }

        cout << "Count of attributes and elements after deleting list element: ";
          getCounters(root, attributes, elements);
          if ((attributes == 37) || (elements == 66))
          {
            cout << "Ok." << endl;
          }
          else
          {
            cout << "Failed." << endl;
          }

          // gpx::Writer writer;

          // writer.write(cout, root, true);
      }

      stream.close();
  }
  else
  {
    cerr << "Test file: " << test_file << " not found." << endl;
  }

  exit(0);
}
