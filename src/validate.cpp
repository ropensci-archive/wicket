#include <Rcpp.h>
using namespace Rcpp;
#include "def.h"
#include "utils.h"
using namespace wkt_utils;

template <typename T>
inline void validate_single(std::string& x, unsigned int& i, CharacterVector& com, LogicalVector& valid, T& p){
  try {
    boost::geometry::read_wkt(x, p);
  } catch (boost::geometry::read_wkt_exception &e){
    com[i] = e.what();
    valid[i] = false;
  }
}

//'@title Validate WKT objects
//'@description \code{validate_wkt} takes a vector of WKT objects and validates that
//'they are parsable, returning a data.frame containing the status of each entry and
//'(in the case it cannot be parsed) any comments as to what, in particular, may be
//'wrong with it.
//'
//'@param x a character vector of WKT objects.
//'
//'@return a data.frame of two columns, \code{is_valid} (containing TRUE or FALSE values
//'for whether the WKT object is valid) and \code{comments} (containing any error messages
//'in the case that the WKT object cannot be validated). If the objects are simply NA,
//'both fields will contain NA.
//'
//'@export
//[[Rcpp::export]]
DataFrame validate_wkt(CharacterVector x){

  // Create instances of each type
  point_type pt;
  linestring_type ls;
  polygon_type poly;
  multipoint_type multip;
  multilinestring_type multil;
  multipolygon_type multipoly;

  // Generate output objects
  unsigned int input_size = x.size();
  CharacterVector comments(input_size, NA_STRING);
  LogicalVector is_valid(input_size, true);
  std::string holding;
  std::deque < std::string > gc_holding;

  for(unsigned int i = 0; i < input_size; i++){
    if(x[i] == NA_STRING){
      is_valid[i] = NA_LOGICAL;
    } else {
      holding = Rcpp::as<std::string>(x[i]);
      switch(id_type(holding)){
        case point:
          validate_single(holding, i, comments, is_valid, pt);
          break;
        case line_string:
          validate_single(holding, i, comments, is_valid, ls);
          break;
        case polygon:
          validate_single(holding, i, comments, is_valid, poly);
          break;
        case multi_point:
          validate_single(holding, i, comments, is_valid, multip);
          break;
        case multi_line_string:
          validate_single(holding, i, comments, is_valid, multil);
          break;
        case multi_polygon:
          validate_single(holding, i, comments, is_valid, multipoly);
          break;
        case geometry_collection:
          break;
        default:
          is_valid[i] = false;
          comments[i] = "Object could not be recognised as a supported WKT type";
      }
    }
  }

  return DataFrame::create(_["is_valid"] = is_valid,
                           _["comments"] = comments,
                           _["stringsAsFactors"] = false);
}
