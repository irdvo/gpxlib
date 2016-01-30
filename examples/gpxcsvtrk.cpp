//==============================================================================
//
//    gpxcsvtrk - convert a csv file with lat,lon to a gpx trk file example
//
//               Copyright (C) 2016  Dick van Oudheusden
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
#include <cctype>

#include "gpx/Node.h"
#include "gpx/GPX.h"

using namespace std;


void trim(string &str)
{
  size_t start = 0;
  size_t end   = str.length() - 1;

  while ((start < str.length()) && (isspace(str[start])))
  {
    start++;
  }
  while ((end >= start) && (isspace(str[end])))
  {
    end--;
  }

  if (start <= end)
  {
    str = str.substr(start, end - start + 1);
  }
  else
  {
    str = "";
  }
}

string parseLine(string &str)
{
  size_t  pos = 0;
  string result;

  while ((pos < str.length()) && (str[pos] != ','))
  {
    result += str[pos++];
  }

  if (pos >= str.length())
  {
    str = "";
  }
  else
  {
    str.erase(0, pos+1);
  }

  trim(result);

  return result;
}

int main(int argc, char *argv[])
{
  if ((argc < 3) || (argc > 4))
  {
    cout << "Usage: gpxcsvtrk NAME FILE.csv [FILE.gpx]" << endl;
    cout << "Convert the lat,lon points in the comma-separated file to a gpx trk file" << endl << endl;
    exit(1);
  }

  ifstream input(argv[2]);

  if (!input.is_open())
  {
    cerr << "Unable to open: " << argv[1] << endl;
    exit(1);
  }

  // Create the root node
  gpx::GPX *root = new gpx::GPX();

  root->version().add(&cerr)->setValue("1.1");

  root->creator().add(&cerr)->setValue("gpxcsvtrk");

  gpx::TRK *trk = dynamic_cast<gpx::TRK*>(root->trks().add(&cerr));

  trk->name().add(&cerr)->setValue(argv[1]);

  gpx::TRKSeg *trkseg = dynamic_cast<gpx::TRKSeg *>(trk->trksegs().add(&cerr));

  string latitude;
  string longitude;

  while (!input.eof())
  {
    string line;

    getline(input, line);

    trim(line);

    while (line.length() > 0)
    {
      if (longitude.length() == 0)
      {
        longitude = parseLine(line);
      }
      else if (latitude.length() == 0)
      {
        latitude = parseLine(line);
      }

      if ((latitude.length() > 0) && (longitude.length() > 0))
      {
        gpx::WPT *trkpt = dynamic_cast<gpx::WPT*>(trkseg->trkpts().add(&cerr));

        trkpt->lat().add(&cerr)->setValue(latitude);
        trkpt->lon().add(&cerr)->setValue(longitude);

        latitude = "";
        longitude = "";
      }
    }
  }
  input.close();

  if (argc == 3)
  {
    root->write(cout, 0);
  }
  else
  {
    ofstream stream(argv[3]);

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
