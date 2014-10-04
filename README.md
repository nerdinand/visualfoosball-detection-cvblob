visualfoosball-detection-cvblob
===============================

Dependencies
------------

* [cmake](http://cmake.org) (for building)
* [OpenCV](http://opencv.org/) (Computer Vision library)
* [cvblob](https://code.google.com/p/cvblob/) (depends on OpenCV)

On a Mac, just

    brew tap homebrew/science
    brew install opencv cvblob

Building
--------

    git checkout git@github.com:nerdinand/visualfoosball-detection-cvblob.git
    cd visualfoosball-detection-cvblob
    mkdir build
    cd build
    cmake ..
    make
