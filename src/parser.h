#include <Rcpp.h>
#include "utils.h"
using namespace Rcpp;

#ifndef __WKT_PARSER__
#define __WKT_PARSER__
namespace wkt_parser {

  //This checks data formatted as "12 45" for, you know, size and suchlike
  void check_pointpair(std::string& pointpair, String& rationale, bool& result, bool& alter);

  void check_braces(std::string& wkt_obj, String& rationale, bool& result, bool& alter);

  namespace point_parser {

    //A point object should consist of:
    //* Two coordinates
    //* Stored as numeric values
    //* Separated by a space
    void validate_wkt(std::string& wkt, String& rationale, bool& result);
  };

  namespace linestring_parser {
    //A linestring object should consist of:
    //* Any number of coordinate *pairs*
    //* Stored as numeric values
    //* Separated into pairs by a comma
    //* Separated by a space.
    void validate_wkt(std::string& wkt, String& rationale, bool& result);

  };

  namespace multipoint_parser {
    //A multipoint object should consist of:
    //* Any number of coordinate *pairs*
    //* Stored as numeric values
    //* Separated into pairs by a comma,
    //* Separated by a space
    //* Optionally with braces around each pair.
    void validate_wkt(std::string& wkt, String& rationale, bool& result);

  };

};

#endif
