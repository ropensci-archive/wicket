#include "parser.h"

void wkt_parser::check_pointpair(std::string& pointpair, String& rationale,
                                 bool& result, bool& alter){
  std::deque < std::string > holding;
  wkt_utils::split_elements(pointpair, holding, " ");
  if(holding.size() == 2){
    if(wkt_utils::check_digit(holding[0]) && wkt_utils::check_digit(holding[1])){
      result = false;
      alter = true;
      rationale = "Coordinates must be numeric values";
    }
  } else {
    result = false;
    alter = true;
    rationale = "WKT object coordinates should come in pairs";
  }
}

void wkt_parser::check_braces(std::string& wkt_obj, String& rationale, bool& result,
                              bool& alter){
  if(wkt_obj[0] != '(' | wkt_obj[wkt_obj.size()-1] != ')'){
    result = false;
    rationale = "WKT objects are expected to have braces around the set(s) of coordinates";
    alter = true;
  } else {
    wkt_obj.erase(0,1);
    wkt_obj.erase(wkt_obj.size()-1, 1);
  }
}

void wkt_parser::point_parser::validate_wkt(std::string& wkt, String& rationale, bool& result){

  bool alter = false;
  wkt_parser::check_braces(wkt, rationale, result, alter);
  if(!alter){
    wkt_parser::check_pointpair(wkt, rationale, result, alter);
    if(!alter){
      result = true;
      rationale = NA_STRING;
    }
  }
}

void wkt_parser::linestring_parser::validate_wkt(std::string& wkt,
                                                 String& rationale, bool& result){

  bool alter = false;
  wkt_parser::check_braces(wkt, rationale, result, alter);
  if(!alter){
    std::deque < std::string > holding;
    wkt_utils::split_elements(wkt, holding, ",");
    for(unsigned int i = 0; i < holding.size(); i++){
      wkt_utils::clean_wkt(holding[i]);
      wkt_parser::check_pointpair(holding[i], rationale, result, alter);
      if(alter){
        break;
      }
    }
    if(!alter){
      result = true;
      rationale = NA_STRING;
    }
  }
}

void wkt_parser::multipoint_parser::validate_wkt(std::string& wkt,
                                                 String& rationale, bool& result){
  bool alter = false;
  wkt_parser::check_braces(wkt, rationale, result, alter);
  if(!alter){
    wkt_utils::strip_braces(wkt);
    std::deque < std::string > holding;
    wkt_utils::split_elements(wkt, holding, ",");
    for(unsigned int i = 0; i < holding.size(); i++){
      wkt_utils::clean_wkt(holding[i]);
      wkt_parser::check_pointpair(holding[i], rationale, result, alter);
      if(alter){
        break;
      }
    }
    if(!alter){
      result = true;
      rationale = NA_STRING;
    }
  }
}
