// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// validate_wkt
DataFrame validate_wkt(CharacterVector x);
RcppExport SEXP wicket_validate_wkt(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(validate_wkt(x));
    return rcpp_result_gen;
END_RCPP
}
// wkt_bounding
SEXP wkt_bounding(CharacterVector wkt, bool as_matrix);
RcppExport SEXP wicket_wkt_bounding(SEXP wktSEXP, SEXP as_matrixSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type wkt(wktSEXP);
    Rcpp::traits::input_parameter< bool >::type as_matrix(as_matrixSEXP);
    rcpp_result_gen = Rcpp::wrap(wkt_bounding(wkt, as_matrix));
    return rcpp_result_gen;
END_RCPP
}
