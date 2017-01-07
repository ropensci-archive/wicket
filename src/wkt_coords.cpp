#include <Rcpp.h>
using namespace Rcpp;
#include "utils.h"
using namespace wkt_utils;
//[[Rcpp::depends(BH)]]

template <typename T>
DataFrame coords_single(std::string& x, T& p){

  try {
    boost::geometry::read_wkt(x, p);
  } catch (boost::geometry::read_wkt_exception &e){
    return Rcpp::DataFrame::create(_["lon"] = NumericVector(1, NA_REAL),
                                   _["lat"] = NumericVector(1, NA_REAL));
  }

  std::vector < point_type > points = p.outer();
  unsigned int input_size = points.size();
  NumericVector out_ln(input_size);
  NumericVector out_lat(input_size);

  for(unsigned int i = 0; i < input_size; i++){
    out_ln[i] = boost::geometry::get<0>(points[i]);
    out_lat[i]  = boost::geometry::get<1>(points[i]);
  }

  return Rcpp::DataFrame::create(_["lon"] = out_ln,
                                 _["lat"] = out_lat);

}

//'@title Extract Latitude and Longitude from WKT polygons
//'@description \code{wkt_coords} extracts lat/long values from WKT polygons,
//'specifically the outer shell of those polygons (working on the assumption that
//'said outer edge is what you want).
//'
//'@param wkt a character vector of WKT objects
//'
//'@return a list of data.frames, one per WKT object. In the event that the
//'WKT object cannot be decoded (or is not a POLYGON), a data.frame of NA values
//'will be returned.
//'
//'@examples
//'wkt_coords("POLYGON ((30 10, 40 40, 20 40, 10 20, 30 10))")
//'#[[1]]
//'#lon lat
//'# 1  30  10
//'# 2  40  40
//'# 3  20  40
//'# 4  10  20
//'# 5  30  10
//'@export
//[[Rcpp::export]]
List wkt_coords(CharacterVector wkt){

  unsigned int input_size = wkt.size();
  List output(input_size);
  std::string holding;
  polygon_type poly;

  for(unsigned int i = 0; i < input_size; i++){
    if((i % 10000) == 0){
      Rcpp::checkUserInterrupt();
    }
    if(wkt[i] == NA_STRING){
      output[i] = Rcpp::DataFrame::create(_["lon"] = NumericVector(1, NA_REAL),
                                          _["lat"] = NumericVector(1, NA_REAL));
    } else {
      holding = Rcpp::as<std::string>(wkt[i]);
      switch(id_type(holding)){
        case polygon:
          output[i] = coords_single(holding, poly);
          break;
        default:
          output[i] = Rcpp::DataFrame::create(_["lon"] = NumericVector(1, NA_REAL),
                                              _["lat"] = NumericVector(1, NA_REAL));
      }
    }
  }

  return output;
}
