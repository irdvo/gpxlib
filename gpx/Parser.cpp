//==============================================================================
//
//             Parser - the parser class in the gpx library
//
//               Copyright (C) 2013  Dick van Oudheusden
//  
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free
// Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//==============================================================================
// 
//  $Date: 2013-03-10 12:02:27 +0100 (Sun, 10 Mar 2013) $ $Revision: 5 $
//
//==============================================================================

#include <strings.h>
#include <cstring>

#include "gpx/Parser.h"


using namespace std;

namespace gpx
{
  
  Parser::Parser(std::ostream *report) :
    _report(report),
    _parser(0),
    _current(0),
    _root(0),
    _errorText(),
    _errorLineNumber(0),
    _errorColumnNumber(0)
  {
  }

  Parser::~Parser()
  {
    if (_parser != 0)
    {
      stopExpat();
    }
  }

  // Building

  void Parser::makeElement(const char *name)
  {
    // cout << "BuildElement:" << name << " for " << (_current != 0 ? _current->name().c_str() : "null") << endl;

    if (strcasecmp(name, "gpx") == 0)
    {
      if (_root == 0)
      {
        _current = _root = new GPX(0, name, true);
      }
      else if (_report != 0)
      {
        *_report << "Double element 'gpx'" << endl;
      }
    }
    else if (_current != 0)
    {
      _current = _current->makeElement(name, _report);
    }
    else if (_report != 0)
    {
      *_report << "Missing element 'gpx'" << endl;
    }
  }

  void Parser::makeAttribute(const char *name)
  {
    // cout << "BuildAttribute:" << name << " for " << (_current != 0 ? _current->name().c_str() : "null") << endl;

    if (_current != 0)
    {
      _current = _current->makeAttribute(name, _report);
    }
    else if (_report != 0)
    {
      *_report << "Missing element 'gpx'" << endl;
    }
  }

  void Parser::made()
  {
    // cout << "Built for " << (_current != 0 ? _current->name().c_str() : "null") << endl;

    if (_current != 0)
    {
      _current = _current->made();
    }
    else if (_report != 0)
    {
      *_report << "Misformed gpx source" << endl;
    }
  }

  void Parser::value(std::string value)
  {
    if (_current != 0)
    {
      _current->value(value);
    }
    else if (_report != 0)
    {
      *_report << "Misformed gpx source" << endl;
    }
  }


  // Parsing

  bool Parser::parse(const char *data, int length, bool isFinal)
  {
    bool ok = false;

    if (_parser == 0)
    {
      startExpat();

      if (_parser == 0)
      {
        return false;
      }
    }

    ok = XML_Parse(_parser, data, length, isFinal);

    if (!ok)
    {
      _errorText         = XML_ErrorString(XML_GetErrorCode(_parser));
      _errorLineNumber   = XML_GetCurrentLineNumber(_parser);
      _errorColumnNumber = XML_GetCurrentColumnNumber(_parser);
    }

    if (isFinal)
    {
      stopExpat();
    }

    return ok;
  }

  bool Parser::parse(const char *text, bool isFinal)
  {
    parse(text, strlen(text), isFinal);
  }

  bool Parser::parse(const std::string &data, bool isFinal)
  {
    parse(data.c_str(), data.length(), isFinal);
  }

  // Parse a stream

  GPX *Parser::parse(std::istream &stream)
  {
    bool ok = stream.good();

    if (ok)
    {
      char buffer[4096];

      while ((ok) && (stream.good()))
      {
        stream.read(buffer, sizeof(buffer));

        ok = parse(buffer, stream.gcount(), (stream.gcount() < sizeof(buffer)));
      }
    }

    return _root;
  }


  // Privates

  void Parser::startExpat()
  {
    _parser = XML_ParserCreate(NULL);
    
    XML_SetUserData(_parser, this);
  
    XML_SetXmlDeclHandler(_parser, xmlDeclHandler);
    XML_SetElementHandler(_parser, startElementHandler, endElementHandler);
    XML_SetCharacterDataHandler(_parser, characterDataHandler);
    XML_SetCommentHandler(_parser, commentHandler);
    XML_SetProcessingInstructionHandler(_parser, processingInstructionHandler);
    XML_SetCdataSectionHandler(_parser, startCdataSectionHandler, endCdataSectionHandler);
    XML_SetDefaultHandlerExpand(_parser, defaultHandler);
    XML_SetNamespaceDeclHandler(_parser, startNamespaceDeclHandler, endNamespaceDeclHandler);
  }
  
  void Parser::stopExpat()
  {
    XML_ParserFree(_parser);
    
    _parser = 0;
  }

  void Parser::xmlDeclHandler(void *userData, const XML_Char *version, const XML_Char *encoding, int standalone)
  {
    Parser *me = static_cast<Parser*>(userData);
  
    //[reader->_handler startDocument :version :encoding :standalone];
  }

  void Parser::startElementHandler(void *userData, const XML_Char *name, const XML_Char **atts)
  {
    Parser *me = static_cast<Parser*>(userData);
    
    me->makeElement(name);
    
    //emptyCharacters(reader->_characters, reader->_handler);
    //emptyUnparsed  (reader->_unparsed,   reader->_handler);
  
    for (int i = 0; atts[i] != NULL; i+=2)
    {
      me->makeAttribute(atts[i]);
      
      me->value(atts[i+1]);
      
      me->made();
    }
  }

  void Parser::endElementHandler(void *userData, const XML_Char *name)
  {
    Parser *me = static_cast<Parser*>(userData);
    
    me->made();
  }

  void Parser::characterDataHandler(void *userData, const XML_Char *s, int len)
  {
    Parser *me = static_cast<Parser*>(userData);
    
    string data(s, len);
    
    me->value(data);
  }

  void Parser::commentHandler(void *userData, const XML_Char *data)
  {
    Parser *me = static_cast<Parser*>(userData);

    //DXMLReader *reader = (DXMLReader *) userData;

    //emptyCharacters(reader->_characters, reader->_handler);
    //emptyUnparsed  (reader->_unparsed,   reader->_handler);

    //[reader->_handler comment :data];
  }

  void Parser::processingInstructionHandler(void *userData, const XML_Char *target, const XML_Char *data)
  {
    Parser *me = static_cast<Parser*>(userData);

    //DXMLReader *reader = (DXMLReader *) userData;

    //emptyCharacters(reader->_characters, reader->_handler);
    //emptyUnparsed  (reader->_unparsed,   reader->_handler);
  
    //[reader->_handler processingInstruction :target :data];
  }

  void Parser::startCdataSectionHandler(void *userData)
  {
    Parser *me = static_cast<Parser*>(userData);

    //DXMLReader *reader = (DXMLReader *) userData;

    //emptyCharacters(reader->_characters, reader->_handler);
    //emptyUnparsed  (reader->_unparsed,   reader->_handler);

    //[reader->_handler startCDATA];
  }

  void Parser::endCdataSectionHandler(void *userData)
  {
    Parser *me = static_cast<Parser*>(userData);

    //DXMLReader *reader = (DXMLReader *) userData;

    //emptyCharacters(reader->_characters, reader->_handler);
  
    //[reader->_handler endCDATA];
  }

  void Parser::defaultHandler(void *userData, const XML_Char *s, int len)
  {
    Parser *me = static_cast<Parser*>(userData);

    //int i;
  
    //DXMLReader *reader = (DXMLReader *) userData;
  
    //emptyCharacters(reader->_characters, reader->_handler);
  
    //for (i = 0; i < len; i++)
    //{
      //[reader->_unparsed push :s[i]];
    //}
  }

  void Parser::startNamespaceDeclHandler(void *userData, const XML_Char *prefix, const XML_Char *uri)
  {
    Parser *me = static_cast<Parser*>(userData);

    //DXMLReader *reader = (DXMLReader *) userData;
  
    //[reader->_handler startNamespace :prefix :uri];
  }

  void Parser::endNamespaceDeclHandler(void *userData, const XML_Char *prefix)
  {
    Parser *me = static_cast<Parser*>(userData);

    //DXMLReader *reader = (DXMLReader *) userData;
  
    //[reader->_handler endNamespace];
  }

}
