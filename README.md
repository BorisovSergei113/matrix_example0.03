[![Build Status](https://travis-ci.org/github/BorisovSergei113/matrix_example0.03)](https://travis-ci.org/github/BorisovSergei113/matrix_example0.03)
```
cmake -H. -B_builds -DBUILD_TESTS=ON -DBUILD_EXAMPLES=ON
cmake --build _builds
cmake --build _builds --target test -- ARGS=--verbose
_builds/example
```
