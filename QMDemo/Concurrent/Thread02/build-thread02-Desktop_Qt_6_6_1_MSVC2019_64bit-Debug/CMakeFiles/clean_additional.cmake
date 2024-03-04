# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\thread02_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\thread02_autogen.dir\\ParseCache.txt"
  "thread\\CMakeFiles\\worker_autogen.dir\\AutogenUsed.txt"
  "thread\\CMakeFiles\\worker_autogen.dir\\ParseCache.txt"
  "thread\\worker_autogen"
  "thread02_autogen"
  )
endif()
