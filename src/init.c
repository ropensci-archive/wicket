#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME:
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP wicket_bounding_wkt_list(SEXP);
extern SEXP wicket_bounding_wkt_points(SEXP, SEXP, SEXP, SEXP);
extern SEXP wicket_sp_convert_(SEXP, SEXP);
extern SEXP wicket_validate_wkt(SEXP);
extern SEXP wicket_wkt_bounding(SEXP, SEXP);
extern SEXP wicket_wkt_centroid(SEXP);
extern SEXP wicket_wkt_coords(SEXP);
extern SEXP wicket_wkt_correct(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"wicket_bounding_wkt_list",   (DL_FUNC) &wicket_bounding_wkt_list,   1},
    {"wicket_bounding_wkt_points", (DL_FUNC) &wicket_bounding_wkt_points, 4},
    {"wicket_sp_convert_",         (DL_FUNC) &wicket_sp_convert_,         2},
    {"wicket_validate_wkt",        (DL_FUNC) &wicket_validate_wkt,        1},
    {"wicket_wkt_bounding",        (DL_FUNC) &wicket_wkt_bounding,        2},
    {"wicket_wkt_centroid",        (DL_FUNC) &wicket_wkt_centroid,        1},
    {"wicket_wkt_coords",          (DL_FUNC) &wicket_wkt_coords,          1},
    {"wicket_wkt_correct",         (DL_FUNC) &wicket_wkt_correct,         1},
    {NULL, NULL, 0}
};

void R_init_wicket(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
