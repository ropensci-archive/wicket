#include "parser.h"

void wkt_parser::check_pointpair(std::string& pointpair, String& rationale, bool& result, bool& alter){
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

void wkt_parser::check_braces(std::string& wkt_obj, String& rationale, bool& result, bool& alter){
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

void split_multi(std::string& wkt_obj, std::deque <std::string>& output, String& rationale, bool& result, bool& alter){
  //(10 10, 20 20, 10 40), (40 40, 30 30, 40 20, 30 10)
  wkt_parser::check_braces(wkt_obj, rationale, result, alter);
  if(!alter){

  }
}
void wkt_parser::linestring_parser::validate_wkt(std::string& wkt, String& rationale, bool& result){

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

void wkt_parser::multipoint_parser::validate_wkt(std::string& wkt, String& rationale, bool& result){
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

void wkt_parser::multilinestring_parser::validate_wkt(std::string& wkt, String& rationale, bool& result){
  bool alter = false;
  std::deque < std::string > holding;

}
