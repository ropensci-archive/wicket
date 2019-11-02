library(wicket)

testthat::context("Test sp convert")
testthat::test_that("sp_convert works", {
  # library(sp)
  # s1 <- SpatialPolygons(list(Polygons(list(Polygon(cbind(c(2,4,4,1,2),c(2,3,5,4,2)))), "s1")))
  # save(s1, file = "tests/testthat/sp_convert1.rda") 
  # load("tests/testthat/sp_convert1.rda")
  
  load("sp_convert1.rda")
  x <- sp_convert(s1)

  testthat::expect_length(x, 1)
  testthat::expect_is(x, "character")
  testthat::expect_match(x, "POLYGON\\(\\(2 2,1 4,4 5,4 3,2 2\\)\\)")
})

testthat::context("Test sf convert")
testthat::test_that("sf_convert works", {
  # library(sp)
  # library(sf)
  # tmp <- SpatialPolygons(list(Polygons(list(Polygon(cbind(c(2,4,4,1,2),c(2,3,5,4,2)))), "s1")))
  # s2 <- st_as_sf(tmp)
  # save(s2, file = "tests/testthat/sf_convert1.rda") 
  # load("tests/testthat/sf_convert1.rda")
  
  load("sf_convert1.rda")
  x <- sf_convert(s2)

  testthat::expect_length(x, 1)
  testthat::expect_is(x, "character")
  testthat::expect_match(x, "POLYGON\\(\\(2 2,1 4,4 5,4 3,2 2\\)\\)")
})
