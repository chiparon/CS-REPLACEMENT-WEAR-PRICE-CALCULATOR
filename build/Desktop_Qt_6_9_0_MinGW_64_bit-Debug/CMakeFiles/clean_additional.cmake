# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QTCPP_ALCHEMY_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QTCPP_ALCHEMY_autogen.dir\\ParseCache.txt"
  "QTCPP_ALCHEMY_autogen"
  )
endif()
