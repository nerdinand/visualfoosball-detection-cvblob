visualfoosball-detection-cvblob
===============================

Dependencies
------------

* [cmake](http://cmake.org) (for building)
* [OpenCV](http://opencv.org/) (Computer Vision library)
* [cvblob](https://code.google.com/p/cvblob/) (depends on OpenCV)

On a Mac, just

    brew tap nerdinand/homebrew-science
    brew install opencv cvblob

Building
--------

    git clone git@github.com:nerdinand/visualfoosball-detection-cvblob.git
    cd visualfoosball-detection-cvblob
    mkdir build
    cd build
    cmake ..
    make

Developing
----------

You can use [Eclipse with CDT](http://www.eclipse.org/downloads/packages/eclipse-ide-cc-developers/lunasr1) as an IDE for this. To generate the Eclipse project files (NOTE: execute this in the project root):

    cmake . -G "Eclipse CDT4 - Unix Makefiles"

Then choose `File -> Import... -> Existing Projects into Workspace` to import in Eclipse. 

On Mavericks and later, in order to be able to debug, you'll have to install gdb, because Apple does not ship it anymore and Eclipse has no support for lldb yet:

    brew install gdb
    
When doing this, you'll also have to codesign your custom gdb executable: http://sourceware.org/gdb/wiki/BuildingOnDarwin
