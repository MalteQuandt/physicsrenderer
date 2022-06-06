set(src src/Logger.cpp include/Utilities.h) # Here be source files
add_library(logger ${src})
include_directories(include)
target_include_directories(logger PUBLIC include)