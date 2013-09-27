//==============================================================================
//
//                GPX - the main class in the GPX library
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

#include "gpx/GPX.h"


using namespace std;

namespace gpx
{
  
  GPX::GPX(Node *parent, const char *name, bool mandatory) :
    Node(parent, name, mandatory),
    _parser(0),
    _current(0),
    _version(this, "version", true),
    _creator(this, "creator", true),
    _metadata(this, "metadata", false),
    _extensions(this, "extensions", false)
  {
    attributes().push_back(&_version);
    attributes().push_back(&_creator);

    elements().push_back(&_metadata);
    elements().push_back(&_extensions);
  }

  GPX::~GPX()
  {
  }

  // Building

  Node *GPX::buildElement(const char *name, std::ostream *report)
  {
    if (_current == 0)
    {
      _current = this;
    }
    
    if (_current == this)
    {
      Node *node = 0;

      if (strcasecmp(name, "wpt") == 0)
      {
        node = new WPT(this, "wpt", false);
      }
      else if (strcasecmp(name, "rte") == 0)
      {
        node = new RTE(this, "rte", false);
      }
      else if (strcasecmp(name, "trk") == 0)
      {
        node = new TRK(this, "trk", false);
      }

      if (node != 0)
      {
        list<Node*>::      iterator iter = elements().begin();
        list<Node*>::const_iterator end  = elements().end();
        list<Node*>::      iterator last = elements().end();

        while (iter != end)
        {
          if (strcasecmp(name, (*iter)->name().c_str()) == 0)
          {
            last = iter;
          }

          ++iter;
        }

        if (last != end)
        {
          ++last;
        }

        if (last == end)
        {
          elements().push_back(node);
        }
        else
        {
          elements().insert(last, node);
        }

        _current = node;
      }
      else
      {
        _current = Node::buildElement(name, report);
      }
    }
    else
    {
      _current = _current->buildElement(name, report);
    }

    return _current;
  }

  Node *GPX::buildAttribute(const char *name, std::ostream *report)
  {
    if (_current == 0)
    {
      _current = this;
    }

    if (_current == this)
    {
      _current = Node::buildAttribute(name, report);
    }
    else
    {
      _current = _current->buildAttribute(name, report);
    }

    return _current;
  }

  Node *GPX::built()
  {
    if (_current != this)
    {
      _current = _current->built();
    }
    
    return _current;
  }

  void GPX::value(std::string value)
  {
    if (_current == this)
    {
      Node::value(value);
    }
    else
    {
      _current->value(value);
    }
  }

  // Properties

  list<Node*> GPX::wpt()
  {
    list<Node*> nodes;

    filter("wpt", nodes);

    return nodes;
  }

  // Parsing

  bool GPX::startParsing()
  {
    if (_parser != 0)
    {
      stopExpat();
    }

    startExpat();

    return true;
  }

  bool GPX::parse(const char *data, int length, bool isFinal)
  {
    bool ok = false;

    if (_parser != 0)
    {
      ok = XML_Parse(_parser, data, length, isFinal);

      if (!ok)
      {
        parsingError(string(XML_ErrorString(XML_GetErrorCode(_parser))), XML_GetCurrentLineNumber(_parser), XML_GetCurrentColumnNumber(_parser));
      }
    }

    return ok;
  }

  bool GPX::parse(const char *text, bool isFinal)
  {
    parse(text, strlen(text), isFinal);
  }

  bool GPX::parse(const std::string &data, bool isFinal)
  {
    parse(data.c_str(), data.length(), isFinal);
  }

  void parsingError(const std::string &errorText, int lineNumber, int columnNumber)
  {
    std::cerr << "Error: " << errorText << " on line " << lineNumber << " and column " << columnNumber << endl;
  }

  bool GPX::stopParsing()
  {
    if (_parser != 0)
    {
      stopExpat();
    }

    return true;
  }

  // Parse a stream

  bool GPX::parse(std::istream &stream)
  {
    bool ok = false;

    if (stream.good())
    {
      char buffer[4096];

      ok = startParsing();

      while ((ok) && (stream.good()))
      {
        stream.read(buffer, sizeof(buffer));

        ok = parse(buffer, stream.gcount(), (stream.gcount() < sizeof(buffer)));
      }

      stopParsing();
    }

    return ok;
  }


  // Privates

  void GPX::startExpat()
  {
    _parser = XML_ParserCreateNS(NULL, ':');
    
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
  
  void GPX::stopExpat()
  {
    XML_ParserFree(_parser);
    
    _parser = 0;
  }

  void GPX::xmlDeclHandler(void *userData, const XML_Char *version, const XML_Char *encoding, int standalone)
  {
    GPX *me = static_cast<GPX*>(userData);
  
    //[reader->_handler startDocument :version :encoding :standalone];
  }

  void GPX::startElementHandler(void *userData, const XML_Char *name, const XML_Char **atts)
  {
    GPX *me = static_cast<GPX*>(userData);
    
    me->buildElement(name);
    
    //emptyCharacters(reader->_characters, reader->_handler);
    //emptyUnparsed  (reader->_unparsed,   reader->_handler);
  
    for (int i = 0; atts[i] != NULL; i+=2)
    {
      me->buildAttribute(atts[i]);
      
      me->value(atts[i+1]);
      
      me->built();
    }
  }

  void GPX::endElementHandler(void *userData, const XML_Char *name)
  {
    GPX *me = static_cast<GPX*>(userData);
    
    me->built();
  }

  void GPX::characterDataHandler(void *userData, const XML_Char *s, int len)
  {
    GPX *me = static_cast<GPX*>(userData);
    
    string data(s, len);
    
    me->value(data);
  }

  void GPX::commentHandler(void *userData, const XML_Char *data)
  {
    GPX *me = static_cast<GPX*>(userData);

    //DXMLReader *reader = (DXMLReader *) userData;

    //emptyCharacters(reader->_characters, reader->_handler);
    //emptyUnparsed  (reader->_unparsed,   reader->_handler);

    //[reader->_handler comment :data];
  }

  void GPX::processingInstructionHandler(void *userData, const XML_Char *target, const XML_Char *data)
  {
    GPX *me = static_cast<GPX*>(userData);

    //DXMLReader *reader = (DXMLReader *) userData;

    //emptyCharacters(reader->_characters, reader->_handler);
    //emptyUnparsed  (reader->_unparsed,   reader->_handler);
  
    //[reader->_handler processingInstruction :target :data];
  }

  void GPX::startCdataSectionHandler(void *userData)
  {
    GPX *me = static_cast<GPX*>(userData);

    //DXMLReader *reader = (DXMLReader *) userData;

    //emptyCharacters(reader->_characters, reader->_handler);
    //emptyUnparsed  (reader->_unparsed,   reader->_handler);

    //[reader->_handler startCDATA];
  }

  void GPX::endCdataSectionHandler(void *userData)
  {
    GPX *me = static_cast<GPX*>(userData);

    //DXMLReader *reader = (DXMLReader *) userData;

    //emptyCharacters(reader->_characters, reader->_handler);
  
    //[reader->_handler endCDATA];
  }

  void GPX::defaultHandler(void *userData, const XML_Char *s, int len)
  {
    GPX *me = static_cast<GPX*>(userData);

    //int i;
  
    //DXMLReader *reader = (DXMLReader *) userData;
  
    //emptyCharacters(reader->_characters, reader->_handler);
  
    //for (i = 0; i < len; i++)
    //{
      //[reader->_unparsed push :s[i]];
    //}
  }

  void GPX::startNamespaceDeclHandler(void *userData, const XML_Char *prefix, const XML_Char *uri)
  {
    GPX *me = static_cast<GPX*>(userData);

    //DXMLReader *reader = (DXMLReader *) userData;
  
    //[reader->_handler startNamespace :prefix :uri];
  }

  void GPX::endNamespaceDeclHandler(void *userData, const XML_Char *prefix)
  {
    GPX *me = static_cast<GPX*>(userData);

    //DXMLReader *reader = (DXMLReader *) userData;
  
    //[reader->_handler endNamespace];
  }

}
