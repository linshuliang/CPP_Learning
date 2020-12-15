include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(DEFINE_DEMO "define_demo.cpp")
add_executable(DEFINE_FUNC_DEMO "define_func_demo.cpp")
add_executable(IFDEF_DEMO "ifdef_demo.cpp")
add_executable(STD_MACRO_DEMO "std_macro_demo.cpp")


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})