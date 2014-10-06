project (visualfoosball-detection-cvblob)

###############################################################################
# generate build configuration
###############################################################################

###############################################################################
# source and header files
###############################################################################

find_package(OpenCV REQUIRED)
find_package(cvblob REQUIRED)

set (visualfoosball-detection-cvblob_SOURCES
  "BallDetectionTest.cpp"
  "BallDetector.cpp"
  "Config.cpp"
  "CustomDeleters.cpp"
  "FramePreparer.cpp"
  "Main.cpp"
)

###############################################################################
# create target
###############################################################################

add_executable (visualfoosball-detection-cvblob ${visualfoosball-detection-cvblob_SOURCES})
target_link_libraries (visualfoosball-detection-cvblob opencv_core)
target_link_libraries (visualfoosball-detection-cvblob opencv_highgui)
target_link_libraries (visualfoosball-detection-cvblob opencv_photo)
target_link_libraries (visualfoosball-detection-cvblob cvblob)

###############################################################################
# install targets
###############################################################################

install (TARGETS visualfoosball-detection-cvblob DESTINATION "bin")

