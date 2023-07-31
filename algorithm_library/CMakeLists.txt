add_library(algorithm 
src/a_star.cpp 
src/convert_map.cpp 
src/path_smoothing.cpp
src/necessary_function.cpp)

target_include_directories(algorithm PUBLIC include)
