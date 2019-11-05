testthat::context("Test coordinates can be reversed")

testthat::test_that("Coordinates can be reversed from a single valid polygon", {
  wkt <- "POLYGON((42 -26,42 -13,52 -13,52 -26,42 -26))"
  result <- wkt_reverse(wkt)
  expect_is(result, "character")
  testthat::expect_length(result, 1)
  testthat::expect_false(identical(result, wkt))
  testthat::expect_match(wkt, "-26,42")
  testthat::expect_match(result, "-26,52")
})

testthat::test_that("Coordinates can be reversed from many valid polygons", {
  wkts <- c(
    "POLYGON((42 -26,42 -13,52 -13,52 -26,42 -26))",
    "POLYGON((-0.1 50.0,14.3 50.0,14.3 42.5,-0.1 42.5,-0.1 50.0))",
    'POLYGON((30.1 10.1,10 20,20 60,60 60,30.1 10.1))'
  )
  result <- wkt_reverse(wkts)
  testthat::expect_is(result, "character")
  testthat::expect_length(result, 3)
  testthat::expect_false(identical(result, wkts))

  testthat::expect_match(wkts[1], "-26,42")
  testthat::expect_match(result[1], "-26,52")

  testthat::expect_match(wkts[2], "50.0,14.3")
  testthat::expect_match(result[2], "50,-0.1")

  testthat::expect_match(wkts[3], "10.1,10")
  testthat::expect_match(result[3], "10.1,60")
})

testthat::test_that("reverse fails as expected", {
  # not WKT, given back as is
  testthat::expect_equal(wkt_reverse("foo"), "foo")

  # invalid WKT, given back as is, but lowercased
  bad1 <- "polygon((42 -26,42 -13,52 -13,52 -26,42 -26a))"
  testthat::expect_equal(wkt_reverse(bad1), bad1)
})

testthat::test_that("Coordinates can be reversed from a valid multipolygon", {
  multi <- "MULTIPOLYGON (((30 20, 45 40, 10 40, 30 20)), ((15 5, 40 10, 10 20, 5 10, 15 5)))"
  result <- wkt_reverse(multi)
  expect_is(result, "character")
  testthat::expect_length(result, 1)
  testthat::expect_false(identical(result, multi))
  testthat::expect_match(multi, "20, 45")
  testthat::expect_match(result, "20,10")
})
