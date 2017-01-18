#include <Rcpp.h>
using namespace Rcpp;
#include "utils.h"
using namespace wkt_utils;

void centroid_single(std::string wkt, polygon_type& poly,
                     unsigned int& outlength,
                     NumericVector& lat,
                     NumericVector& lng){

  point_type p;
  try{
    boost::geometry::read_wkt(wkt, poly);
    boost::geometry::centroid(poly, p);
  } catch(...){
    lat[outlength] = NA_REAL;
    lng[outlength] = NA_REAL;
    return;
  }

  lat[outlength]  = boost::geometry::get<1>(p);
  lng[outlength]  = boost::geometry::get<0>(p);
}

//'@title Extract Centroid
//'@description \code{get_centroid} identifies the 2D centroid
//'in a WKT object (or vector of WKT objects).
//'
//'@param wkt a character vector of WKT objects, represented as strings
//'
//'@return a data.frame of two columns, \code{lat} and \code{lng},
//'with each row containing the centroid from the corresponding wkt
//'object. In the case that the object is NA (or cannot be decoded)
//'the resulting values will also be NA
//'
//'@examples
//'get_centroid("POLYGON((2 1.3,2.4 1.7))")
//'#  lat lng
//'#1 1.3   2
//'@export
//[[Rcpp::export]]
DataFrame get_centroid(CharacterVector wkt){

  polygon_type p;
  unsigned int input_size = wkt.size();
  NumericVector lat(input_size);
  NumericVector lng(input_size);

  for(unsigned int i = 0; i < input_size; i++){
    if((i % 10000) == 0){
      Rcpp::checkUserInterrupt();
    }
    if(wkt[i] == NA_STRING){
      lat[i] = NA_REAL;
      lng[i] = NA_REAL;
    } else {
      centroid_single(as<std::string>(wkt[i]), p, i, lat, lng);
    }
  }

  return DataFrame::create(_["lat"] = lat,
                           _["lng"] = lng);
}
