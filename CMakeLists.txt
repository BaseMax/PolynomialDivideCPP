cmake_minimum_required(VERSION 3.5)

project(Polynomial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_CXX_STANDARD_REQUIRED on)

file(GLOB source_code_files src/*.cc)
file(GLOB header_files include/Polynomial/*.h)

add_executable(${PROJECT_NAME}
	${source_code_files}
	${header_files}
)
target_include_directories(${PROJECT_NAME} PRIVATE include)
