set(src src/Logger.cpp) # Here be source files
add_library(logger ${src})
include_directories(include)
target_include_directories(logger PUBLIC include)