get_coords <- function(sp_single){
  unlist(lapply(sp_single@polygons, function(ss){
    lapply(ss@Polygons, function(ss_i){
      return(ss_i@coords)
    })
  }), recursive = FALSE)
}

#'@title Convert SpatialPolygons or SpatialPolygonDataFrames into WKT objects
#'@description \code{sp_convert} turns objects from the \code{sp} package -
#'specifically, SpatialPolygons and SpatialPolygonDataFrames - into WKT POLYGONs
#'or MULTIPOLYGONs
#'
#'@param x a list of SP/SPDF objects (or a single object)
#'
#'@param group whether or not to group coordinates together in the case that an object
#'in \code{x} has multiple sets of coordinates. If TRUE (the default), such objects will
#'be returned as \code{MULTIPOLYGON}s - if FALSE, as a vector of \code{POLYGON}s.
#'
#'@return either a character vector of WKT objects - one per sp object - if \code{group} is TRUE,
#'or a list of vectors if \code{group} is FALSE.
#'
#'@seealso \code{\link{bounding_wkt}}, for turning bounding boxes within \code{sp} objects
#'into WKT objects.
#'
#'@examples
#'\dontrun{
#'library(sp)
#'s1 <- SpatialPolygons(list(Polygons(list(Polygon(cbind(c(2,4,4,1,2),c(2,3,5,4,2)))), "s1")))
#'sp_convert(s1)
#'}
#'@export
sp_convert <- function(x, group = TRUE){
  if(!is.list(x)){
    x <- list(x)
  }
  coords <- lapply(x, get_coords)
  return(sp_convert_(coords, group))
}
