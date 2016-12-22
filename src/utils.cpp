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
  size_t type_loc = wkt_obj.find("(");
  if(type_loc == std::string::npos || type_loc == wkt_obj.size()){
    return wkt_utils::unsupported_type;
  }
  wkt_utils::supported_types output = wkt_utils::hash_type(wkt_obj.substr(0, type_loc));
  wkt_obj = wkt_obj.substr(type_loc+1);
  return output;
}
