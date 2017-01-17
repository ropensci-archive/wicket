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
