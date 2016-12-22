#include <Rcpp.h>
using namespace Rcpp;

#ifndef __WKT_UTILS__
#define __WKT_UTILS__
namespace wkt_utils {

  void lower_case(std::string& x);

  void clean_wkt(std::string& x);

  enum supported_types {
    point,
    multi_point,
    line_string,
    multi_line_string,
    polygon,
    geometry_collection,
    unsupported_type,
  };

  supported_types hash_type(std::string type);

  supported_types id_type(std::string& wkt_obj);
};
#endif
