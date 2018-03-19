[![Build Status](https://travis-ci.org/BorisovSergei113/matrix_example0.03.svg?branch=master)](https://travis-ci.org/BorisovSergei113/matrix_example0.03)
```
cmake -H. -B_builds -DBUILD_TESTS=ON -DBUILD_EXAMPLES=ON
cmake --build _builds
cmake --build _builds --target test -- ARGS=--verbose
_builds/example
```
