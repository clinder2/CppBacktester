cmake_minimum_required(VERSION 3.10)
project(CppBacktester)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(APP_DOMAIN ./domain)
set(APP_CALC ./calc)
#set(CMAKE_PREFIX_PATH /Users/evankirkiles/Qt/5.11.1/clang_64)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Boost 1.88 COMPONENTS filesystem regex)
find_package( Boost REQUIRED COMPONENTS regex system date_time )
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})

    add_executable(CppBacktester data.cpp)
    target_link_libraries(CppBacktester Boost::filesystem Boost::regex)
endif()
find_package(CURL REQUIRED)
IF (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(CppBacktester ${CURL_LIBRARIES})
endif()
#new
# find python libraries
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
find_package(PythonLibs 3.0 REQUIRED)
include_directories(${PYTHON3_INCLUDE_DIRS} ${NumPy_INCLUDE_DIRS})

# populate matplotlib repository
include(FetchContent)
FetchContent_Declare(
    matplotlib
    GIT_REPOSITORY https://github.com/lava/matplotlib-cpp.git
    GIT_TAG        f23347fca25219d1c42cbb91608b5556814bf572
)
FetchContent_GetProperties(matplotlib)
if(NOT matplotlib_POPULATED)
    FetchContent_Populate(matplotlib)
endif()
include_directories(SYSTEM ${matplotlib_SOURCE_DIR})

# link python and numpy
target_link_libraries(example
    PRIVATE
        ${PYTHON_LIBRARIES}
        Python3::NumPy
)
set_target_properties(
    INSTALL_RPATH
)
#find_package(Qt5Widgets REQUIRED)
#IF (Qt5Widgets_FOUND)
#    include_directories(${Qt5Widgets_INCLUDE_DIRS})
#    target_link_libraries(CppBacktester ${Qt5Widgets_LIBRARIES})
#endif()

include_directories(${APP_DOMAIN})
include_directories(${APP_CALC})