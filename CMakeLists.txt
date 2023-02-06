cmake_minimum_required(VERSION 3.24)
project(windows_demo C)

set(CMAKE_C_STANDARD 17)

# 隐藏控制台黑窗口
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -mwindows)

#add_executable(windows_demo src/main.c)
#add_executable(windows_demo src/demo_1.c)
#add_executable(windows_demo src/demo_2.c)
#add_executable(windows_demo src/demo_3.c)
#add_executable(windows_demo src/demo_4.c win.h)
add_executable(windows_demo src/demo_5.c)
#add_executable(windows_demo src/demo_6.c)