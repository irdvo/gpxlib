#ifndef GPX_H
#define GPX_H

//==============================================================================
//
//                   GPX - the GPX class
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
//  $Date$ $Revision$
//
//==============================================================================

#include <iostream>

#include "expat.h"

#include "gpx/Node.h" 

#include "gpx/String.h"
#include "gpx/Metadata.h" 
#include "gpx/WPT.h"
#include "gpx/RTE.h"
#include "gpx/TRK.h"
#include "gpx/Extensions.h"

///
/// @namespace gpx
///
/// @brief The namespace of the gpx library
///

namespace gpx
{
  ///
  /// @class GPX
  ///
  /// @brief The main class of the gpx library.
  ///
  
  class GPX : public Node
  {
  public:

    ///
    /// Constructor
    ///
    /// @param  parent     the parent node
    /// @param  name       the name of the attribute or element
    /// @param  mandatory  is the attribute or element mandatory ?
    ///
    GPX(Node *parent, const char *name, bool mandatory = false);

    ///
    /// Deconstructor
    ///
    virtual ~GPX();
    
    ///
    /// Get version
    ///
    /// @return the version object
    ///
    String  &version() { return _version; };

    ///
    /// Get creator
    ///
    /// @return the creator object
    ///
    String  &creator() { return _creator; };

    ///
    /// Get metadata
    ///
    /// @return the metadata object
    ///
    Metadata  &metadata() { return _metadata; };

    ///
    /// Get wpt
    ///
    /// @return the wpt object
    ///
    std::list<Node*> wpt();
    
    ///
    /// Get rte
    ///
    /// @return the rte object
    ///
    /// @todo return rte
    ///
    //RTE  &rte() { return _rte; };
    
    ///
    /// Get trk
    ///
    /// @return the trk object
    ///
    /// @todo return trk
    ///
    //TRK  &trk() { return _trk; };
    
    ///
    /// Get extensions
    ///
    /// @return the extensions object
    ///
    Extensions  &extensions() { return _extensions; };

    // Building methods
    
    ///
    /// Build an element node
    ///
    /// @param  name    the name of the element
    /// @param  report  the optional report stream
    ///
    /// @return the node (or 0 if not found)
    ///
    virtual Node *buildElement(const char *name, std::ostream *report = 0);

    ///
    /// Build an attribute node
    ///
    /// @param  name    the name of the attribute
    /// @param  report  the optional report stream
    ///
    /// @return the node (or 0 if not found)
    ///
    virtual Node *buildAttribute(const char *name, std::ostream *report = 0);

    ///
    /// Done building the node
    ///
    /// @return the parent node (or 0 if not found)
    ///
    virtual Node *built();

    ///
    /// Set the value
    ///
    /// @param value   the value of the attribute or element
    ///
    virtual void value(std::string value);

    // Low level rarsing methods

    ///
    /// Start parsing
    ///
    /// @return success
    ///
    bool startParsing();

    ///
    /// Parse data
    ///
    /// @param  data    the data to be parsed
    /// @param  length  the length of the data
    /// @param  isFinal is this the last data ?
    ///
    /// @return success
    ///
    bool parse(const char *data, int length, bool isFinal);

    ///
    /// Start parsing
    ///
    /// @param  text    the zero terminated text to be parsed
    /// @param  isFinal is this the last data ?
    ///
    /// @return success
    ///
    bool parse(const char *text, bool isFinal);

    ///
    /// Start parsing
    ///
    /// @param  data    the data to be parsed
    /// @param  isFinal is this the last data ?
    ///
    /// @return success
    ///
    bool parse(const std::string &data, bool isFinal);

    ///
    /// Report parsing error
    ///
    /// @param  errorText     the text for the error
    /// @param  lineNumber    the line number of the error
    /// @param  columnNumber  the column number of the error
    ///
    /// @return success
    ///
    virtual void parsingError(const std::string &errorText, int lineNumber, int columnNumber);

    ///
    /// Stop parsing
    ///
    /// @return success
    ///
    bool stopParsing(); 

    // Stream parsing methods

    ///
    /// Parse an input stream
    ///
    /// @param  stream        the stream to be parsed
    ///
    /// @return success
    ///
    bool parse(std::istream &stream);

  private:

    // Start using expat
    void startExpat();
    
    // Stop using expat
    void stopExpat();
    
    
    // Statics
    static void xmlDeclHandler              (void *userData, const XML_Char *version, const XML_Char *encoding, int standalone);
    static void startElementHandler         (void *userData, const XML_Char *name,    const XML_Char **atts);
    static void endElementHandler           (void *userData, const XML_Char *name);
    static void characterDataHandler        (void *userData, const XML_Char *s, int len);
    static void commentHandler              (void *userData, const XML_Char *data);
    static void processingInstructionHandler(void *userData, const XML_Char *target, const XML_Char *data);
    static void startCdataSectionHandler    (void *userData);
    static void endCdataSectionHandler      (void *userData);
    static void defaultHandler              (void *userData, const XML_Char *s, int len);
    static void startNamespaceDeclHandler   (void *userData, const XML_Char *prefix, const XML_Char *uri);
    static void endNamespaceDeclHandler     (void *userData, const XML_Char *prefix);

    static bool _expatStarted;
    
    // Members
    XML_Parser  _parser;
    Node       *_current;
    String      _version;
    String      _creator;
    Metadata    _metadata;
    Extensions  _extensions;
    
    // Disable copy constructors
    GPX(const GPX &);
    GPX& operator=(const GPX &);  

  };
  
}


#endif

