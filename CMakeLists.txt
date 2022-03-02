cmake_minimum_required(VERSION 3.9)
project(openmp_test) # you can change the project name

set(EXE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/executable")
set(EXECUTABLE_OUTPUT_PATH  ${EXE_DIR})

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()



add_executable(task1 task1.cpp) # you can change the excutable name
target_link_libraries(task1 PUBLIC OpenMP::OpenMP_CXX)

add_executable(task2 task2.cpp) # you can change the excutable name
target_link_libraries(task2 PUBLIC OpenMP::OpenMP_CXX)

add_executable(task3 task3.cpp) # you can change the excutable name
target_link_libraries(task3 PUBLIC OpenMP::OpenMP_CXX)

add_executable(task4 task4.cpp) # you can change the excutable name
target_link_libraries(task4 PUBLIC OpenMP::OpenMP_CXX)

add_executable(task5 task5.cpp) # you can change the excutable name
target_link_libraries(task5 PUBLIC OpenMP::OpenMP_CXX)

add_executable(task6 task6.cpp) # you can change the excutable name
target_link_libraries(task6 PUBLIC OpenMP::OpenMP_CXX)

add_executable(task7 task7.cpp) # you can change the excutable name
target_link_libraries(task7 PUBLIC OpenMP::OpenMP_CXX)

add_executable(task8 task8.cpp) # you can change the excutable name
target_link_libraries(task8 PUBLIC OpenMP::OpenMP_CXX)

add_executable(task9 task9.cpp) # you can change the excutable name
target_link_libraries(task9 PUBLIC OpenMP::OpenMP_CXX)