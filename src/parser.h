#include <Rcpp.h>
using namespace Rcpp;

class parser {

private:

  std::string default_seps;

  std::string type;

  std::string body;

  NumericVector x;

  NumericVector y;

  std::string strip_whitespace(std::string x);

  void get_type(std::string x, std::string& x_holding, std::string& type_holding);

  enum supported_types {
    point,
    multi_point,
    line_string,
    multi_line_string,
    polygon,
    geometry_collection,
    unsupported_type,
  };

  supported_types hash_type(){
    if(type == "POINT"){
      return point;
    }

    if(type == "MULTIPOINT"){
      return multi_point;
    }

    if(type == "LINESTRING"){
      return line_string;
    }
    return unsupported_type;
  }

public:

  parser(CharacterVector strings){
    default_seps = ", ";
    unsigned int in_size = strings.size();

    x = NumericVector(in_size);

    y = NumericVector(in_size);

    for(unsigned int i = 0; i < strings.size(); i++){

      if(strings[i] == NA_STRING){
        x[i] = NA_REAL;
        y[i] = NA_REAL;
      } else {
        get_type(strip_whitespace(Rcpp::as<std::string>(strings[i])), body, type);

        switch()
      }
    }
  }

};

