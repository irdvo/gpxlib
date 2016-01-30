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

#include "gpx/Parser.h"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cerr << "Usage: gpxwpt file ..." << endl;
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
        cout << argv[i] << " waypoints :" << endl;
        list<gpx::WPT*> &wpts = root->wpts().list();

        for (list<gpx::WPT*>::iterator node = wpts.begin(); node != wpts.end(); ++node)
        {
          gpx::WPT *wpt = (*node);

          if (wpt != 0)
          {
            cout << "Position: " << wpt->lat().value() << ',' << wpt->lon().value() << endl;
            cout << "  Elevation: " << wpt->ele().value() << endl;
            cout << "  Time     : " << wpt->time().value() << endl;
            cout << "  Name     : " << wpt->name().value() << endl;
            cout << "  Comment  : " << wpt->cmt().value() << endl;
            cout << "  Symbol   : " << wpt->sym().value() << endl;
            cout << "  Type     : " << wpt->type().value() << endl;
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
