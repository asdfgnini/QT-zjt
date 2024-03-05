# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\network01_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\network01_autogen.dir\\ParseCache.txt"
  "network\\CMakeFiles\\network_autogen.dir\\AutogenUsed.txt"
  "network\\CMakeFiles\\network_autogen.dir\\ParseCache.txt"
  "network\\network_autogen"
  "network01_autogen"
  "thread\\CMakeFiles\\thread_autogen.dir\\AutogenUsed.txt"
  "thread\\CMakeFiles\\thread_autogen.dir\\ParseCache.txt"
  "thread\\thread_autogen"
  )
endif()
