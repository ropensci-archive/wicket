#include <Rcpp.h>
using namespace Rcpp;
#include "def.h"
#include "utils.h"
using namespace wkt_utils;

template <typename T>
void wkt_bounding_single_matrix(std::string wkt, T& obj, box_type& holding, unsigned int& i, NumericMatrix& output){

  try {
    boost::geometry::read_wkt(wkt, obj);
  } catch (boost::geometry::read_wkt_exception &e){
    output(i, 0) = NA_REAL;
    output(i, 1) = NA_REAL;
    output(i, 2) = NA_REAL;
    output(i, 3) = NA_REAL;
    return;
  }
  holding = boost::geometry::return_envelope<box_type>(obj);
  output(i, 0) = holding.min_corner().get<0>();
  output(i, 2) = holding.min_corner().get<1>();
  output(i, 1) = holding.max_corner().get<0>();
  output(i, 3) = holding.max_corner().get<1>();
}

NumericMatrix wkt_bounding_matrix(CharacterVector& wkt){

  unsigned int input_size = wkt.size();
  NumericMatrix output(input_size, 4);

  // Holding objects
  point_type pt;
  linestring_type ls;
  polygon_type poly;
  multipoint_type multip;
  multilinestring_type multil;
  multipolygon_type multipoly;
  box_type box_inst;

  for(unsigned int i = 0; i < input_size; i++){

    if(wkt[i] == NA_STRING){
      output(i, 0) = NA_REAL;
      output(i, 1) = NA_REAL;
      output(i, 2) = NA_REAL;
      output(i, 3) = NA_REAL;
    } else {

    }
  }

}
SEXP wkt_bounding(CharacterVector wkt, bool as_matrix = false){

  if(as_matrix){
    return Rcpp::wrap(wkt_bounding_matrix(wkt));
  }
  return Rcpp::wrap(wkt_bounding_df(wkt));
}
