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
  attributes += node->getAttributes().size();

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

int check_count  = 0;
int check_failed = 0;

void check(const string &text, bool result, ReportTest *report = 0, gpx::Report::Warning expecting = gpx::Report::NO_WARNING)
{
  check_count++;

  cout << text << ": " ;

  gpx::Report::Warning warning = (report == 0 ? gpx::Report::NO_WARNING : report->warning());

  if ((result) && (warning == expecting))
  {
    cout << "Ok.";
  }
  else
  {
    cout << "Failed";

    if (report != 0)
    {
      cout << '(' << gpx::Report::text(warning) << ")";
    }

    cout << ".";

    check_failed++;
  }

  cout << endl;
}


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


        cout << endl << "Tests:" << endl << endl;

        getCounters(root, attributes, elements);
        check("Initial count of attributes and elements", ((attributes == 41) && (elements == 67)));

        check("Validate the tree", root->validate(&report), &report);

        root->version().add(&report);
        check("Add already present version attribute", true, &report, gpx::Report::ADD_ALREADY_PRESENT_NODE);

        root->add("version", gpx::Node::ATTRIBUTE, &report);
        check("Add already present version attribute by name", true, &report, gpx::Report::ADD_ALREADY_PRESENT_NODE);

        root->metadata().add(&report);
        check("Add already present metadata element", true, &report, gpx::Report::ADD_ALREADY_PRESENT_NODE);

        root->add("metadata", gpx::Node::ELEMENT, &report);
        check("Add already present metadata element by name", true, &report, gpx::Report::ADD_ALREADY_PRESENT_NODE);

        getCounters(root, attributes, elements);
        check("Count of attributes and elements after adding already present nodes", ((attributes == 41) && (elements == 67)));

        gpx::WPT *wpt1;

        wpt1 = dynamic_cast<gpx::WPT*>(root->wpts().add(&report));
        check("Add new wpt list element", true, &report, gpx::Report::NO_WARNING);

        check("Validate new wpt list element", !wpt1->validate());

        gpx::WPT *wpt2;

        wpt2 = dynamic_cast<gpx::WPT*>(root->add("wpt", gpx::Node::ELEMENT, &report));
        check("Add new wpt list element by name", true, &report, gpx::Report::NO_WARNING);

        getCounters(root, attributes, elements);
        check("Count of attributes and elements after adding list elements", ((attributes == 41) && (elements == 69)));

        wpt1->lat().add(&report);
        check("Add new lat attribute", true, &report, gpx::Report::NO_WARNING);

        wpt1->lat().setValue("abc");
        check("Validate invalid lat attribute (abc) value", !wpt1->lat().validate(&report), &report, gpx::Report::INCORRECT_VALUE);

        wpt1->lat().setValue("91.0");
        check("Validate out-of-range lat attribute (91.0) value", !wpt1->lat().validate(&report), &report, gpx::Report::INCORRECT_VALUE);

        wpt1->lat().setValue("-91.0");
        check("Validate out-of-range lat attribute (-91.0) value", !wpt1->lat().validate(&report), &report, gpx::Report::INCORRECT_VALUE);

        wpt1->lat().setValue("51.9");
        check("Validate correct lat attribute (51.9) value", wpt1->lat().validate(&report));

        gpx::Longitude *lon2;

        lon2 = dynamic_cast<gpx::Longitude*>(wpt2->add("lon", gpx::Node::ATTRIBUTE, &report));
        check("Add new lon attribute by name", true, &report, gpx::Report::NO_WARNING);

        check("Initial lon attribute value", (wpt2->lon().getValue() == ""));

        wpt2->lon().setValue("abc");
        check("Validate invalid lon attribute (abc) value", !wpt2->lon().validate(&report), &report, gpx::Report::INCORRECT_VALUE);

        wpt2->lon().setValue("181.0");
        check("Validate out-of-range lon attribute (181.0) value", !wpt2->lon().validate(&report), &report, gpx::Report::INCORRECT_VALUE);

        wpt2->lon().setValue("-181.0");
        check("Validate out-of-range lon attribute (-181.0) value", !wpt2->lon().validate(&report), &report, gpx::Report::INCORRECT_VALUE);

        wpt2->lon().setValue("51.9");
        check("Validate correct lon attribute  (51.9) value", wpt2->lon().validate(&report));

        wpt2->magvar().add(&report);
        check("Add new magvar element", true, &report, gpx::Report::NO_WARNING);

        wpt2->magvar().setValue("abc");
        check("Validate invalid magvar element (abc) value", !wpt2->magvar().validate(&report), &report, gpx::Report::INCORRECT_VALUE);

        wpt2->magvar().setValue("-0.1");
        check("Validate out-of-range magvar element (-0.1) value", !wpt2->magvar().validate(&report), &report, gpx::Report::INCORRECT_VALUE);

        wpt2->magvar().setValue("360.1");
        check("Validate out-of-range magvar element (360.1) value", !wpt2->magvar().validate(&report), &report, gpx::Report::INCORRECT_VALUE);

        wpt2->magvar().setValue("51.9");
        check("Validate correct magvar element (51.9) value", wpt2->magvar().validate(&report));

        wpt2->remove(&wpt2->magvar(), &report);
        check("Remove magvar element", true, &report, gpx::Report::NO_WARNING);

        wpt2->dgpsid().add(&report);
        check("Add new dgpsid element", true, &report, gpx::Report::NO_WARNING);

        wpt2->dgpsid().setValue("-0.1");
        check("Validate invalid dgpsid element (-0.1) value", !wpt2->dgpsid().validate(&report), &report, gpx::Report::INCORRECT_VALUE);

        wpt2->dgpsid().setValue("1024");
        check("Validate out-of-range dgpsid element (1024) value", !wpt2->dgpsid().validate(&report), &report, gpx::Report::INCORRECT_VALUE);

        wpt2->dgpsid().setValue("78");
        check("Validate correct dgpsid element (78) value", wpt2->dgpsid().validate(&report));

        wpt2->remove(&wpt2->dgpsid(), &report);
        check("Remove dgpsid element", true, &report, gpx::Report::NO_WARNING);

        wpt2->sat().add(&report);
        check("Add new sat element", true, &report, gpx::Report::NO_WARNING);

        wpt2->sat().setValue("-0.1");
        check("Validate invalid sat element (-0.1) value", !wpt2->sat().validate(&report), &report, gpx::Report::INCORRECT_VALUE);

        wpt2->sat().setValue("7");
        check("Validate correct sat element (78) value", wpt2->sat().validate(&report));

        wpt2->remove(&wpt2->sat(), &report);
        check("Remove sat element", true, &report, gpx::Report::NO_WARNING);

        wpt2->fix().add(&report);
        check("Add new fix element", true, &report, gpx::Report::NO_WARNING);

        wpt2->fix().setValue("abc");
        check("Validate invalid fix element (abc) value", !wpt2->fix().validate(&report), &report, gpx::Report::INCORRECT_VALUE);

        wpt2->fix().setValue("2d");
        check("Validate correct fix element (2d) value", wpt2->fix().validate(&report));

        wpt2->fix().setValue("3d");
        check("Validate correct fix element (3d) value", wpt2->fix().validate(&report));

        wpt2->fix().setValue("dgps");
        check("Validate correct fix element (dgps) value", wpt2->fix().validate(&report));

        wpt2->fix().setValue("pps");
        check("Validate correct fix element (pps) value", wpt2->fix().validate(&report));

        wpt2->fix().setValue("none");
        check("Validate correct fix element (none) value", wpt2->fix().validate(&report));

        wpt2->remove(&wpt2->fix(), &report);
        check("Remove fix element", true, &report, gpx::Report::NO_WARNING);

        getCounters(root, attributes, elements);
        check("Count of attributes and elements after adding attributes", ((attributes == 43) && (elements == 69)));

        root->metadata().author().add(&report);
        check("Add new author element", true, &report, gpx::Report::NO_WARNING);

        root->metadata().add("keywords", gpx::Node::ELEMENT, &report);
        check("Add new keywords element by name", true, &report, gpx::Report::NO_WARNING);

        getCounters(root, attributes, elements);
        check("Count of attributes and elements after adding elements", ((attributes == 43) && (elements == 71)));

        lon2->setValue("50.8343");
        check("Setting lon attribute value", (wpt2->lon().getValue() == "50.8343"));

        check("Initial keywords element value", (root->metadata().keywords().getValue() == ""));

        root->metadata().keywords().setValue("Official");
        check("Setting keywords element value", (root->metadata().keywords().getValue() == "Official"));

        getCounters(root, attributes, elements);
        check("Count of attributes and elements after setting values",  ((attributes == 43) && (elements == 71)));

        check("Count elements of list element", (root->wpts().list().size() == 4));

        wpt2->remove(&wpt2->lat(), &report);
        check("Delete not present lat attribute", true, &report, gpx::Report::REMOVE_UNKNOWN_CHILD);

        wpt2->remove(&wpt2->name(), &report);
        check("Delete not present name element", true, &report, gpx::Report::REMOVE_UNKNOWN_CHILD);

        getCounters(root, attributes, elements);
        check("Count of attributes and elements after removing missing nodes", ((attributes == 43) && (elements == 71)));

        wpt2->remove(&wpt2->lon(), &report);
        check("Delete present lon attribute", true, &report, gpx::Report::NO_WARNING);

        root->remove(&root->metadata(), &report);
        check("Delete present metadata element", true, &report, gpx::Report::NO_WARNING);

        getCounters(root, attributes, elements);
        check("Count of attributes and elements after removing missing nodes", ((attributes == 37) && (elements == 69)));

        root->metadata().add(&report);
        check("Add deleted metadata element", true, &report, gpx::Report::NO_WARNING);

        getCounters(root, attributes, elements);
        check("Count of attributes and elements after reading node", ((attributes == 37) && (elements == 68)));

        root->remove(wpt2, &report);
        check("Delete present wpt list element", true, &report, gpx::Report::NO_WARNING);

        getCounters(root, attributes, elements);
        check("Count of attributes and elements after deleting list element", ((attributes == 37) && (elements == 67)));

        // gpx::Writer writer;

        // writer.write(cout, root, true);

        cout << ">>> " << check_count << " tests done, " << check_failed << " failed." << endl;
      }

      stream.close();
  }
  else
  {
    cerr << "Test file: " << test_file << " not found." << endl;
  }

  exit(0);
}
