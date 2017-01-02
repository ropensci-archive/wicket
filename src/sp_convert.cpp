#include "utils.h"
using namespace wkt_utils;

String mat_poly(List x){

  polygon_type poly;
  NumericMatrix holding = Rcpp::as<NumericMatrix>(x[0]);
  if(holding.ncol() != 2){
    return NA_STRING;
  }
  for(unsigned int i = 0; i < holding.nrow(); i++){
    boost::geometry::append(poly, point_type(holding(i,0), holding(i,1)));
  }

  return wkt_utils::make_wkt_poly(poly);

}

String mat_multipoly(List x){

  multipolygon_type mpoly;
  NumericMatrix holding;
  for(unsigned int i = 0; i < x.size(); i++){
    polygon_type poly;
    holding = Rcpp::as<NumericMatrix>(x[i]);
    if(holding.ncol() != 2){
      return NA_STRING;
    }
    for(unsigned int j = 0; j < holding.nrow(); i++){
      boost::geometry::append(poly, point_type(holding(i,0), holding(i,1)));
    }
    mpoly.push_back(poly);
  }

  return wkt_utils::make_wkt_multipoly(mpoly);

}

CharacterVector sp_convert_simplify(List x){

  unsigned int input_size = x.size();
  CharacterVector output(input_size);
  List holding;
  for(unsigned int i = 0; i < x.size(); i++){

    holding = Rcpp::as<List>(x[i]);
    if(holding.size() > 1){
      output[i] = mat_multipoly(holding);
    } else {
      output[i] = mat_poly(holding);
    }
  }
  return output;
}

List sp_convert_complex(List x){

  unsigned int input_size = x.size();
  List output(input_size);
  List holding;

  for(unsigned int i = 0; i < input_size; i++){
    holding = Rcpp::as<List>(x[i]);
    CharacterVector med(holding.size());
    for(unsigned int j = 0; j < holding.size(); j++){
      med[j] = mat_poly(holding[j]);
    }
    output[i] = med;
  }

  return output;
}

//[[Rcpp::export]]
SEXP sp_convert(List x, bool group = true){
  if(group){
    return(Rcpp::wrap(sp_convert_simplify(x)));
  }
  return(Rcpp::wrap(sp_convert_complex(x)));
}
