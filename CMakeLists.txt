cmake_minimum_required(VERSION 3.16)
project(Classroom_Management_System)

set(CMAKE_CXX_STANDARD 14)

add_executable(Classroom_Management_System main.cpp Metadata.cpp Metadata.h Physical_location.cpp Physical_location.h Time.cpp Time.h Date.cpp Date.h User.cpp User.h Record.cpp Record.h Student.cpp Student.h Staff.cpp Staff.h Equipments.cpp Equipments.h)