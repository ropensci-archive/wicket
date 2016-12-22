#include <Rcpp.h>
#include "utils.h"
using namespace Rcpp;

//[[Rcpp::export]]
bool type_works(std::string x){
  std::string& ptr = x;
  wkt_utils::supported_types output = wkt_utils::id_type(ptr);
  if(output == wkt_utils::unsupported_type){
    return false;
  }
  return true;
}
