#include <Rcpp.h>
using namespace Rcpp;

#ifndef __WKT_UTILS__
#define __WKT_UTILS__
namespace wkt_utils {

  void lower_case(std::string& x);

  void clean_wkt(std::string& x);

  void strip_braces(std::string& x);

  enum supported_types {
    point = 1,
    multi_point = 2,
    line_string = 3,
    multi_line_string = 4,
    polygon = 5,
    geometry_collection = 6,
    multi_polygon = 7,
    unsupported_type = 8
  };

  supported_types hash_type(std::string type);

  supported_types id_type(std::string& wkt_obj);

  void split_elements(std::string& wkt_obj, std::deque < std::string >& output, std::string delim);

  bool check_digit(std::string& x);

  std::string to_string(unsigned int x);
};
#endif
