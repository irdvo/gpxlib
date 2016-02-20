//==============================================================================
//
//                gpxtrkcon - the gpxtrkcon example
//
//               Copyright (C) 2016  Dick van Oudheusden
//
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
//
//  $Date: 2013-03-10 12:02:27 +0100 (Sun, 10 Mar 2013) $ $Revision: 5 $
//
//==============================================================================
//

#include <cstring>
#include <fstream>
#include <iostream>

#include "gpx/Parser.h"
#include "gpx/ReportCerr.h"
#include "gpx/Writer.h"


using namespace std;


void copyNode(gpx::Node *source, gpx::Node *destination, gpx::Report *report = 0)
{
  destination->setValue(source->getValue());

  for (std::list<gpx::Node*>::iterator node = source->getAttributes().begin(); node != source->getAttributes().end(); ++node)
  {
    gpx::Node *attribute = destination->add((*node)->getName().c_str(), gpx::Node::ATTRIBUTE, report);

    copyNode((*node), attribute);
  }

  for (std::list<gpx::Node*>::iterator node = source->getElements().begin(); node != source->getElements().end(); ++node)
  {
    gpx::Node *element = destination->add((*node)->getName().c_str(), gpx::Node::ELEMENT, report);

    copyNode((*node), element);
  }
}

int countTrkpts(gpx::Node *node)
{
  int count = (strcasecmp(node->getName().c_str(), "trkpt") == 0 ? 1 : 0);

  for (std::list<gpx::Node*>::iterator child = node->getElements().begin(); child != node->getElements().end(); ++child)
  {
    count = count + countTrkpts((*child));
  }

  return count;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cerr << "Usage: gpxtrkcon file" << endl;
    cerr << "  Add all the track segments of the second till last track to the first track," << endl;
    cerr << "  resulting in one track with all the track segments of all original tracks" << endl;
    cerr << "  and outputs this gpx to stdout." << endl;
    exit(1);
  }

  ifstream stream(argv[1]);

  if (stream.is_open())
  {
    gpx::ReportCerr report;

    gpx::Parser parser(&report);

    gpx::GPX *root = parser.parse(stream);

    if (root == 0)
    {
      cerr << "Parsing of " << argv[1] << " failed due to " << parser.errorText() << " on line " << parser.errorLineNumber() << " and column " << parser.errorColumnNumber() << endl;
    }
    else if (root->trks().list().empty())
    {
      cerr << "No tracks in in-file, nothing to concatenate." << endl;
    }
    else
    {
      cerr << "Number of Trackpoints in in-file: " << countTrkpts(root) << endl;

      gpx::TRK *firstTrk = root->trks().list().front();

      list<gpx::TRK*>::iterator track = root->trks().list().begin();

      ++track; // skip the first one
      for (; track != root->trks().list().end(); ++track)
      {
        cerr << "Track:" << (*track)->name().getValue() << " with " << (*track)->trksegs().list().size() << " segment" << endl;

        for (list<gpx::TRKSeg*>::iterator source = (*track)->trksegs().list().begin(); source != (*track)->trksegs().list().end(); ++source)
        {
          gpx::TRKSeg *destination = dynamic_cast<gpx::TRKSeg*>(firstTrk->trksegs().add());

          copyNode((*source), destination, &report);
        }
      }

      // Remove the moved tracks
      while (root->trks().list().size() > 1)
      {
        root->remove(root->trks().list().back(), &report);
      }
    }
    stream.close();

    cerr << "Number of Trackpoints in out-file: " << countTrkpts(root) << endl;

    gpx::Writer writer;

    writer.write(cout, root, true);
  }
  else
  {
    cerr << "File: " << argv[1] << " not found." << endl;
  }

  exit(0);
}
