#include <Rcpp.h>
using namespace Rcpp;

namespace wkt_utils {

  std::string tolower(std::string x);

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
}
