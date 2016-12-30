#include <Rcpp.h>
using namespace Rcpp;
#include "def.h"
#include "utils.h"
using namespace wkt_utils;

//[[Rcpp::export]]
CharacterVector bounding_wkt_points(NumericVector min_x, NumericVector max_x, NumericVector min_y, NumericVector max_y){

  unsigned int input_size = min_x.size();
  if(max_x.size() != input_size || min_y.size() != input_size || max_y.size() != input_size){
    Rcpp::stop("All input vectors must be the same length");
  }

  CharacterVector output(input_size);
  box_type bx;
  polygon_type poly;

  for(unsigned int i = 0; i < input_size; i++){
    if((i % 10000) == 0){
      Rcpp::checkUserInterrupt();
    }
    if(min_x[i] == NA_REAL || max_x[i] == NA_REAL || min_y[i] == NA_REAL || max_y[i] == NA_REAL){
      output[i] = NA_STRING;
    } else {
      bx = boost::geometry::make<box_type>(min_x[i], max_x[i], min_y[i], max_y[i]);
      boost::geometry::convert(bx, poly);
      std::stringstream ss;
      ss << boost::geometry::wkt(poly);
      output[i] = ss.str();
    }
  }
  return output;
}
