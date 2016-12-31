#include "utils.h"

void wkt_utils::lower_case(std::string& x){

  std::string out(x);
  for(unsigned int i = 0; i < x.size(); i++){
    x[i] = std::tolower(x[i]);
  }

}

void wkt_utils::clean_wkt(std::string& x){
  size_t first_point = x.find_first_not_of(" \t");
  x.erase(0, first_point);
  first_point = x.find_last_not_of(" \t");
  if(first_point != std::string::npos){
    x.erase(first_point+1);
  }
}

void wkt_utils::strip_braces(std::string& x){
  size_t brace_loc = x.find_first_of("()");
  while(brace_loc != std::string::npos){
    x.erase(brace_loc, 1);
    brace_loc = x.find_first_of("()");
  }
}

wkt_utils::supported_types wkt_utils::hash_type(std::string type){
  if(type == "point"){
    return point;
  }
  if(type == "multipoint"){
    return multi_point;
  }
  if(type == "linestring"){
    return line_string;
  }
  if(type == "multilinestring"){
    return multi_line_string;
  }
  if(type == "polygon"){
    return polygon;
  }
  if(type == "multipolygon"){
    return multi_polygon;
  }
  if(type == "geometrycollection"){
    return geometry_collection;
  }
  return unsupported_type;
}

wkt_utils::supported_types wkt_utils::id_type(std::string& wkt_obj){

  // Clean object
  wkt_utils::lower_case(wkt_obj);
  wkt_utils::clean_wkt(wkt_obj);

  // Split out type
  size_t type_loc = wkt_obj.find_first_of(" (");
  if(type_loc == std::string::npos || type_loc == wkt_obj.size()){
    return wkt_utils::unsupported_type;
  }

  return wkt_utils::hash_type(wkt_obj.substr(0, type_loc));
}

void wkt_utils::split_gc(std::string& wkt_obj, std::deque < std::string >& output){

  bool last_alpha = false;
  unsigned int input_size = wkt_obj.size();
  size_t point = std::string::npos;

  for(signed int i = input_size; i >= 0; i--){
    if(isalpha(wkt_obj[i])){
      if(!last_alpha){
        last_alpha = true;
      }
    } else {
      if(last_alpha){
        output.push_back(wkt_obj.substr(i+1, (point - i)));
        last_alpha = false;
        point = i;
      }
    }
  }

  size_t brace_point;
  if(output.size() > 0){
    output[0] = output[0].erase(output[0].size()-1);
    for(unsigned int i = 0; i < output.size(); i++){
      brace_point = output[i].find_last_of(")");
      if(brace_point != std::string::npos && brace_point != (output[i].size() - 1)){
        output[i] = output[i].erase(brace_point+1);
      }
    }
  }
}

void wkt_utils::split_elements(std::string& wkt_obj, std::deque < std::string >& output, std::string delim){

  size_t first = 0;
  size_t last = wkt_obj.find(delim);

  while(last != std::string::npos){
    output.push_back(wkt_obj.substr(first, (last - first)));
    first = ++last;
    last = wkt_obj.find(delim, last);

    if(last == std::string::npos){
      output.push_back(wkt_obj.substr(first, wkt_obj.size()));
    }
  }
}

std::string wkt_utils::to_string(unsigned int i){
  std::ostringstream ss;
  ss << i;
  return ss.str();
}
bool wkt_utils::check_digit(std::string& x){

  bool has_p = false;

  for(unsigned int i = 0; i < x.size(); i++){

    if(!isdigit(x[i])){
      if(x[i] == '.'){
        if(has_p){
          return false;
        }
        has_p = true;
      } else {
        return false;
      }
    }
  }
  return true;
}
