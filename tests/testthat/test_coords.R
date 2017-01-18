testthat::context("Test coordinates can be extracted from WKT polygons")

testthat::test_that("Coordinates can be extracted from valid polygons", {
  result <- wkt_coords("POLYGON ((30 10, 40 40, 20 40, 10 20, 30 10))")
  expect_true(is.data.frame(result))
  testthat::expect_length(result, 4)
  testthat::expect_equal(nrow(result), 5)
  testthat::expect_equal(result[1,1], 1)
  testthat::expect_equal(result[1,2], "outer")
  testthat::expect_equal(result[1,4], 30)
  testthat::expect_equal(result[1,3], 10)

})

testthat::test_that("Invalid polygons are handled correctly", {
  result <- wkt_coords("POLYGGKFDMGLFKGMON ((30 10, 40 40, 20 40, 10 20, 30 10))")
  expect_true(is.data.frame(result))
  testthat::expect_length(result, 4)
  testthat::expect_equal(nrow(result), 1)
  testthat::expect_equal(result[1,1], 1)
  testthat::expect_equal(sum(is.na(result)), 3)
})

testthat::test_that("non-objects are handled correctly", {
  result <- wkt_coords(NA_character_)
  expect_true(is.data.frame(result))
  testthat::expect_length(result, 4)
  testthat::expect_equal(nrow(result), 1)
  testthat::expect_equal(result[1,1], 1)
  testthat::expect_equal(sum(is.na(result)), 3)
})
