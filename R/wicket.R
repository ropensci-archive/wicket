#' @useDynLib wicket
#' @importFrom Rcpp sourceCpp
NULL

#'@title Generate Bounding Boxes
#'@description \code{bounding_wkt} takes bounding boxes, in various formats,
#'and turns them into WKT POLYGONs.
#'
#'@param min_x a numeric vector of the minimum value for \code{x} coordinates.
#'
#'@param max_x a numeric vector of the maximum value for \code{x} coordinates.
#'
#'@param min_y a numeric vector of the minimum value for \code{y} coordinates.
#'
#'@param max_y a numeric vector of the maximum value for \code{y} coordinates.
#'
#'@param values as an alternative to specifying the various values as vectors,
#' a list of length-4 numeric vectors containing min and max x and y values.
#' NULL (meaning that the other parameters will be expected) by default.
#'
#'@return a character vector of WKT POLYGON objects
#'
#'@seealso \code{\link{wkt_bounding}}, to turn WKT objects of various types into
#'a matrix or data.frame of bounding boxes.
#'@examples
#'# With individual columns
#'bounding_wkt(10, 12, 14, 16)
#'
#'# With a list
#'bounding_wkt(values = list(c(10, 12, 14, 16)))
#'
#'@export
bounding_wkt <- function(min_x, max_x, min_y, max_y, values = NULL){

  if(is.null(values)){
    return(bounding_wkt_points(min_x, max_x, min_y, max_y))
  }

  if(is.data.frame(values)){
    return(NULL)
  }

  if(is.matrix(values)){
    return(NULL)
  }

  if(is.list(values)){
    return(bounding_wkt_list(values))
  }
}
