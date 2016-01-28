//==============================================================================
//
//                gpxtrk - the gpxtrk example
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

#include "gpx/Parser.h"

using namespace std;

void show(gpx::Node &node, int width)
{
  string value(width, ' ');

  if (node.used())
  {
    value = node.value();

    if (value.length() > width)
    {
      value = value.substr(0, width);
    }
    else if (value.length() < width)
    {
      value.insert(0, width - value.length(), ' ');
    }
  }

  cout << value << ' ';
}

void show(const string str, int width)
{
  string value = str;;

  if (value.length() > width)
  {
    value = value.substr(0, width);
  }
  else if (value.length() < width)
  {
    value.append(width - value.length(), ' ');
  }

  cout << value << ' ';
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cerr << "Usage: gpxtrk file ..." << endl;
    exit(1);
  }

  for (int i = 1; i < argc; i++)
  {
    ifstream stream(argv[i]);

    if (stream.is_open())
    {
      gpx::Parser parser(&cerr);

      gpx::GPX *root = parser.parse(stream);

      if (root == 0)
      {
        cerr << "Parsing of " << argv[i] << " failed due to " << parser.errorText() << " on line " << parser.errorLineNumber() << " and column " << parser.errorColumnNumber() << endl;
      }
      else
      {
        list<gpx::Node*> trks = root->trk();

        int trknr = 1;
        for (list<gpx::Node*>::iterator node = trks.begin(); node != trks.end(); ++node)
        {
          gpx::TRK *trk = dynamic_cast<gpx::TRK*>(*node);

          if (trk != 0)
          {
            cout << "Track:" << trknr++ << endl;
            if (trk->name()  .used()) cout << "  Name        : " << trk->name()  .value() << endl;
            if (trk->cmt()   .used()) cout << "  Comment     : " << trk->cmt()   .value() << endl;
            if (trk->desc()  .used()) cout << "  Description : " << trk->desc()  .value() << endl;
            if (trk->src()   .used()) cout << "  Source      : " << trk->src()   .value() << endl;
            if (trk->type()  .used()) cout << "  Type        : " << trk->type()  .value() << endl;
            if (trk->number().used()) cout << "  Number      : " << trk->number().value() << endl;
                                      cout << "  Segments:   : " << trk->trkseg().size()  << endl << endl;

            list<gpx::Node*> trksegs = trk->trkseg();

            int segnr = 1;
            for (list<gpx::Node*>::iterator iter2 = trksegs.begin(); iter2 != trksegs.end(); ++iter2)
            {
              gpx::TRKSeg *seg = dynamic_cast<gpx::TRKSeg*>(*iter2);

              if (seg != 0)
              {
                cout << "  Segment     : " << segnr++ << endl;
                cout << "    ";
                show("Latitude", 11);
                show("Longitude", 11);
                show("Elevation", 11);
                show("Time", 20);
                show("Name", 8);
                show("Comment", 10);
                cout << endl;

                list<gpx::Node*> trkpts = seg->trkpt();

                for (list<gpx::Node*>::iterator iter3 = trkpts.begin(); iter3 != trkpts.end(); ++iter3)
                {
                  gpx::WPT *trkpt = dynamic_cast<gpx::WPT*>(*iter3);

                  if (trkpt != 0)
                  {
                    cout << "    ";
                    show(trkpt->lat(),  11);
                    show(trkpt->lon(),  11);
                    show(trkpt->ele(),  11);
                    show(trkpt->time(), 20);
                    show(trkpt->name(),  8);
                    show(trkpt->cmt(),  10);
                    cout << endl;
                  }
                }
              }
            }
          }
        }
        cout << endl;
      }

      stream.close();
    }
    else
    {
      cerr << "File: " << argv[i] << " not found." << endl;
    }
  }
  exit(0);
}
