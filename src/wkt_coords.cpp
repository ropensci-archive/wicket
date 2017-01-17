#include <Rcpp.h>
using namespace Rcpp;
#include "utils.h"
using namespace wkt_utils;
//[[Rcpp::depends(BH)]]

void get_coords_single(std::string& x,
                       std::list<polygon_type>::iterator& it,
                       std::list<polygon_type>& output,
                       unsigned int& out_size){

  polygon_type p;
  try {
    boost::geometry::read_wkt(x, p);
  } catch (...){
    output.insert(it, p);
    out_size++;
    return;
  }
  output.insert(it, p);

  out_size += p.outer().size();
  for(unsigned int i = 0; i < p.inners().size(); i++){
    out_size += p.inners()[i].size();
  }

}


void extract_coords(polygon_type& p, unsigned int& outsize,
                    CharacterVector& ring, NumericVector& lat,
                    NumericVector& lng){

  if(p.outer().size() == 0){
    ring[outsize] = NA_STRING;
    lat[outsize] = NA_REAL;
    lng[outsize] = NA_REAL;
    outsize++;
    return;
  }
  std::vector < point_type > points = p.outer();
  for(unsigned int i = 0; i < points.size(); i++){
    ring[outsize] = "outer";
    lat[outsize]  = boost::geometry::get<1>(points[i]);
    lng[outsize]  = boost::geometry::get<0>(points[i]);
    outsize++;
  }

  if(p.inners().size()){
    std::string ring_id;
    polygon_type x;
    for(unsigned int i = 0; i < p.inners().size(); i++){
      boost::geometry::convert(p.inners()[i], x);
      ring_id = "inner " + make_string(i);
      for(unsigned int j = 0; j < p.outer().size(); j++){
        lat[outsize]  = boost::geometry::get<1>(points[i]);
        lng[outsize]  = boost::geometry::get<0>(points[i]);
        outsize++;
      }

    }
  }
}

// '@title Extract Latitude and Longitude from WKT polygons
// '@description \code{wkt_coords} extracts lat/long values from WKT polygons,
// 'specifically the outer shell of those polygons (working on the assumption that
// 'said outer edge is what you want).
// '
// '@param wkt a character vector of WKT objects
// '
// '@return a list of data.frames, one per WKT object. In the event that the
// 'WKT object cannot be decoded (or is not a POLYGON), a data.frame of NA values
// 'will be returned.
// '
// //'@examples
// 'wkt_coords("POLYGON ((30 10, 40 40, 20 40, 10 20, 30 10))")
// '#[[1]]
// '#lon lat
// '# 1  30  10
// '# 2  40  40
// '# 3  20  40
// '# 4  10  20
// '# 5  30  10
// '//@export
//
// DataFrame wkt_coords(CharacterVector wkt){
//
//   unsigned int input_size = wkt.size();
//   std::list<polygon_type> holding;
//   std::list<polygon_type>::iterator it;
//   unsigned int n_size = 0;
//
//   for(unsigned int i = 0; i < input_size; i++){
//     if((i % 10000) == 0){
//       Rcpp::checkUserInterrupt();
//     }
//     get_coords_single(Rcpp::as<std::string>(wkt[i]), it, holding, n_size);
//     std::advance(it,1);
//   }
//
//   return output;
// }
