#include <Rcpp.h>
#include "utils.h"
//[[Rcpp::depends(BH)]]
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
using namespace Rcpp;

//[[Rcpp::export]]
std::deque < std::string > test(std::string x){
  std::deque < std::string > output;
  wkt_utils::split_gc(x, output);
  return output;
}
