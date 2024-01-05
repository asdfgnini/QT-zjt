# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "src\\app\\CMakeFiles\\demo_autogen.dir\\AutogenUsed.txt"
  "src\\app\\CMakeFiles\\demo_autogen.dir\\ParseCache.txt"
  "src\\app\\demo_autogen"
  "src\\thread\\CMakeFiles\\worker_autogen.dir\\AutogenUsed.txt"
  "src\\thread\\CMakeFiles\\worker_autogen.dir\\ParseCache.txt"
  "src\\thread\\worker_autogen"
  )
endif()
