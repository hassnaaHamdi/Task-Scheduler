cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
project(TaskSchedulerTest)


include_directories("../include/task_scheduler")
link_directories("../build")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
add_executable(task_scheduler_test ./src/test.cpp)
target_link_libraries(task_scheduler_test task_scheduler)