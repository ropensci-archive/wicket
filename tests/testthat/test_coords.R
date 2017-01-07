testthat::context("Test coordinates can be extracted from WKT polygons")

testthat::test_that("Coordinates can be extracted from valid polygons", {
  result <- wkt_coords("POLYGON ((30 10, 40 40, 20 40, 10 20, 30 10))")
  expect_true(is.list(result))
  testthat::expect_length(result, 1)
  result_f <- result[[1]]
  testthat::expect_true(is.data.frame(result_f))
  testthat::expect_equal(nrow(result_f), 5)
  testthat::expect_equal(result_f[1,1], 30)
  testthat::expect_equal(result_f[1,2], 10)
})

testthat::test_that("Invalid polygons are handled correctly", {
  result <- wkt_coords("POLYGGKFDMGLFKGMON ((30 10, 40 40, 20 40, 10 20, 30 10))")
  expect_true(is.list(result))
  testthat::expect_length(result, 1)
  result_f <- result[[1]]
  testthat::expect_true(is.data.frame(result_f))
  testthat::expect_equal(nrow(result_f), 1)
  testthat::expect_true(is.na(result_f[1,1]))
  testthat::expect_true(is.na(result_f[1,1]))
})

testthat::test_that("non-objects are handled correctly", {
  result <- wkt_coords(NA_character_)
  expect_true(is.list(result))
  testthat::expect_length(result, 1)
  result_f <- result[[1]]
  testthat::expect_true(is.data.frame(result_f))
  testthat::expect_equal(nrow(result_f), 1)
  testthat::expect_true(is.na(result_f[1,1]))
  testthat::expect_true(is.na(result_f[1,1]))
})
