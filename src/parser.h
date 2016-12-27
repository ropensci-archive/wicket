#include <Rcpp.h>
#include "utils.h"
using namespace Rcpp;

#ifndef __WKT_PARSER__
#define __WKT_PARSER__
namespace wkt_parser {

  bool check_deque(std::deque < std::string >& x, std::string to_check);

  namespace point_parser {

    //A point object should consist of:
    //* Two coordinates
    //* Stored as numeric values
    //* Separated by a space
    void lint_wkt(std::string& wkt, int i, LogicalVector& result, CharacterVector& rationale){

      // Strip braces
      if(wkt[0] != '(' | wkt[wkt.size()-1] != ')'){
        result[i] = false;
        rationale[i] = "WKT objects are expected to have braces around the set of coordinates";
      } else {
        wkt.erase(0,1);
        wkt.erase(wkt.size()-1, 1);

        std::deque < std::string > holding;
        wkt_utils::split_elements(wkt, holding, " ");
        Rcpp::print(Rcpp::wrap(holding[0]));
        Rcpp::print(Rcpp::wrap(holding[1]));

        if(holding.size() == 2){
          if(wkt_utils::check_digit(holding[0]) && wkt_utils::check_digit(holding[1])){
            result[i] = true;
            rationale[i] = NA_STRING;
          } else {
            result[i] = false;
            rationale[i] = "Coordinates must be numeric values";
          }
        } else {
          result[i] = false;
          rationale[i] = "Point WKT objects should have two, space-separated coordinates";
        }
      }
    }
  };

  namespace multipoint_parser {

    CharacterVector lint_wkt(std::string wkt);

  };

  namespace linestring_parser {

    CharacterVector lint_wkt(std::string wkt);

  };
};

#endif
