# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Thread03_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Thread03_autogen.dir\\ParseCache.txt"
  "Thread03_autogen"
  "thread\\CMakeFiles\\worker_autogen.dir\\AutogenUsed.txt"
  "thread\\CMakeFiles\\worker_autogen.dir\\ParseCache.txt"
  "thread\\worker_autogen"
  )
endif()
