#' @title Well-Known Text utilities
#' @name wicket
#' @description This package provides basic, standalone functions for WKT
#' manipulation, generation and validation, backed by C++ for improved speed.
#'
#' @seealso \code{\link{validate_wkt}} for checking the validity of WKT objects,
#' \code{\link{sp_convert}} for turning SP objects \emph{into} WKT, and
#' \code{\link{wkt_bounding}} and \code{\link{bounding_wkt}} for bounding box
#' conversion in both directions.
#' @useDynLib wicket, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @docType package
#' @aliases wicket wicket-package
NULL
