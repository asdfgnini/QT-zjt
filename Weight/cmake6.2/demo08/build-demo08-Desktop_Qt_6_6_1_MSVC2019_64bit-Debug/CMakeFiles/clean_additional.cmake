# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\helloworld_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\helloworld_autogen.dir\\ParseCache.txt"
  "helloworld_autogen"
  "thread\\CMakeFiles\\worker_autogen.dir\\AutogenUsed.txt"
  "thread\\CMakeFiles\\worker_autogen.dir\\ParseCache.txt"
  "thread\\worker_autogen"
  )
endif()
