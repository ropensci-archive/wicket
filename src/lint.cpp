#include <Rcpp.h>
using namespace Rcpp;


//[[Rcpp::export]]
DataFrame lint_wkt(CharacterVector wkt){

  unsigned int input_length = wkt.size();

  LogicalVector   is_valid(input_length);
  CharacterVector problems(input_length);

  return DataFrame::create(_["is_valid"] = is_valid,
                           _["problems"] = problems,
                           _["stringsAsFactors"] = false);
}
