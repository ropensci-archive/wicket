#include <Rcpp.h>
#include "utils.h"
#include "parser.h"
using namespace Rcpp;

//[[Rcpp::export]]
DataFrame validate_wkt(CharacterVector wkt){

  unsigned int input_size = wkt.size();
  CharacterVector output_rationale(input_size);
  LogicalVector output(input_size);
  std::string holding;
  String r_holding;
  bool rr_holding;

  for(unsigned int i = 0; i < input_size; i++){

    if(wkt[i] == NA_STRING){
      output[i] = NA_LOGICAL;
      output_rationale[i] = NA_STRING;
    } else {
      holding = Rcpp::as<std::string>(wkt[i]);
      if(wkt_utils::id_type(holding) == wkt_utils::point){
        wkt_parser::point_parser::validate_wkt(holding, r_holding, rr_holding);
        output[i] = rr_holding;
        output_rationale[i] = r_holding;
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
