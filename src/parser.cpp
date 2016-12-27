#include "parser.h"

void wkt_parser::point_parser::validate_wkt(std::string& wkt, String& rationale, bool result){

  // Strip braces
  if(wkt[0] != '(' | wkt[wkt.size()-1] != ')'){
    result = false;
    rationale = "WKT objects are expected to have braces around the set of coordinates";
  } else {
    wkt.erase(0,1);
    wkt.erase(wkt.size()-1, 1);

    std::deque < std::string > holding;
    wkt_utils::split_elements(wkt, holding, " ");
    Rcpp::print(Rcpp::wrap(holding[0]));
    Rcpp::print(Rcpp::wrap(holding[1]));

    if(holding.size() == 2){
      if(wkt_utils::check_digit(holding[0]) && wkt_utils::check_digit(holding[1])){
        result = true;
        rationale = NA_STRING;
      } else {
        result = false;
        rationale = "Coordinates must be numeric values";
      }
    } else {
      result = false;
      rationale = "Point WKT objects should have two, space-separated coordinates";
    }
  }
}

void wkt_parser::linestring_parser::validate_wkt(std::string& wkt, String& rationale, bool result){

  bool fail = false;
  // Strip braces
  if(wkt[0] != '(' | wkt[wkt.size()-1] != ')'){
    result = false;
    fail = true;
    rationale = "WKT objects are expected to have braces around the set of coordinates";
  } else {
    wkt.erase(0,1);
    wkt.erase(wkt.size()-1, 1);

    std::deque < std::string > holding;
    std::deque < std::string > in_holding;
    wkt_utils::split_elements(wkt, holding, ",");

    for(unsigned int i = 0; i < holding.size(); i++){
      wkt_utils::clean_wkt(holding[i]);
      wkt_utils::split_elements(holding[i], in_holding, " ");
      if(in_holding.size() == 2){
        if(!wkt_utils::check_digit(in_holding[0]) || !wkt_utils::check_digit(in_holding[1])){
          result = false;
          fail = true;
          rationale = "Coordinates must be numeric values";
          break;
        }
      } else {
        result = false;
        fail = true;
        rationale = "Each point in a LineString should have two, space-separated coordinates." +
          (std::string)"point " + wkt_utils::to_string(i) + " does not";
        break;
      }
      in_holding.clear();
    }
  }
  if(!fail){
    result = true;
    rationale = NA_STRING;
  }
}
