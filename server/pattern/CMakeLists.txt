cmake_minimum_required (VERSION 2.6)

add_library (PatternSinus SHARED src/sinus.cpp)

set_target_properties(PatternSinus PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../../patterns/)

target_link_libraries(PatternSinus RTypeCommon)

add_library (PatternFocus SHARED src/focus.cpp)

set_target_properties(PatternFocus PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../../patterns/)

target_link_libraries(PatternFocus RTypeCommon)
