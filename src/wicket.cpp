#include <Rcpp.h>
#include "utils.h"
#include "parser.h"
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

//[[Rcpp::export]]
DataFrame lint_point(CharacterVector x){

  unsigned int input_size = x.size();
  CharacterVector output_rationale(input_size);
  LogicalVector output(input_size);
  std::string holding;
  for(unsigned int i = 0; i < input_size; i++){

    if(x[i] == NA_STRING){
      output[i] = NA_LOGICAL;
      output_rationale[i] = NA_STRING;
    } else {
      holding = Rcpp::as<std::string>(x[i]);
      if(wkt_utils::id_type(holding) == wkt_utils::point){
        wkt_parser::point_parser::lint_wkt(holding, i, output, output_rationale);
      } else {
        output[i] = NA_LOGICAL;
        output_rationale[i] = "Not a point object";
      }
    }
  }

  return Rcpp::DataFrame::create(_["is_wkt"] = output,
                                 _["rationale"] = output_rationale,
                                 _["stringsAsFactors"] = false);
}


//[[Rcpp::export]]
DataFrame lint_wkt(CharacterVector wkt){

  unsigned int input_size = wkt.size();
  CharacterVector output_rationale(input_size);
  LogicalVector output(input_size);
  std::string holding;
  for(unsigned int i = 0; i < input_size; i++){

    if(wkt[i] == NA_STRING){
      output[i] = NA_LOGICAL;
      output_rationale[i] = NA_STRING;
    } else {
      holding = Rcpp::as<std::string>(wkt[i]);
      if(wkt_utils::id_type(holding) == wkt_utils::point){
        wkt_parser::point_parser::lint_wkt(holding, i, output, output_rationale);
      } else {
        output[i] = NA_LOGICAL;
        output_rationale[i] = "Not a point object";
      }
    }
  }

  return Rcpp::DataFrame::create(_["is_wkt"] = output,
                                 _["rationale"] = output_rationale,
                                 _["stringsAsFactors"] = false);
}
