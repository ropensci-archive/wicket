# WKT utilities in R
[![Travis-CI Build Status](https://travis-ci.org/ropensci/wicket.svg?branch=master)](https://travis-ci.org/ropensci/wicket) ![downloads](http://cranlogs.r-pkg.org/badges/grand-total/wicket)
`wicket` is a little package to make handling Well-Known Text (WKT) data easier in R, letting you easily:

1. Validate WKT data;
2. Generate WKT bounding boxes from R data types, and;
3. Convert `sp` objects (particularly SpatialPolygons and SpatialPolygonDataFrames) into WKT.

The package is mostly built out of C++, and as such can perform all of these operations extremely fast, to
the tune of 100,000 sp-to-WKT conversions in just over a second. For more information, see the introductory vignette.

Please note that this project is released with a [Contributor Code of Conduct](https://github.com/Ironholds/wicket/blob/master/CONDUCT.md). By participating in this project you agree to abide by its terms.

## Installation

The package can be installed via:

```
install.packages("wicket")
```

For the release version, and:

```
devtools::install_github("ropensci/wicket")
```

For the development version.
