cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
project(TaskScheduler)

aux_source_directory(./src src_list)
add_library(task_scheduler ${src_list})
target_include_directories(task_scheduler PUBLIC include/task_scheduler)
target_include_directories(task_scheduler PRIVATE src)