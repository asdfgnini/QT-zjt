# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/rosqt_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/rosqt_autogen.dir/ParseCache.txt"
  "rosqt_autogen"
  )
endif()
