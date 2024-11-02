cmake_minimum_required(VERSION 3.22.1)
project(main)

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
set(PACKAGE_NAME matplotlib_cpp)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/${PACKAGE_NAME}/cmake)


# Library target
add_library(matplotlib_cpp INTERFACE)
target_include_directories(matplotlib_cpp
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/examples>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(matplotlib_cpp INTERFACE
  cxx_std_11
)
# TODO: Use `Development.Embed` component when requiring cmake >= 3.18
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
target_link_libraries(matplotlib_cpp INTERFACE
  Python3::Python
  Python3::Module
)
find_package(Python3 COMPONENTS NumPy)
if(Python3_NumPy_FOUND)
  target_link_libraries(matplotlib_cpp INTERFACE
    Python3::NumPy
  )
else()
  target_compile_definitions(matplotlib_cpp INTERFACE WITHOUT_NUMPY)
endif()
install(
  TARGETS matplotlib_cpp
  EXPORT install_targets
)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(main 
               src/main.cpp
               src/cube/magicfive.cpp
               src/solver/solver.cpp
               src/hillclimb/hillclimb.cpp
               src/hillclimb/stochastic.cpp
               src/advanced/genetic.cpp
               src/hillclimb/randomrestart.cpp
               src/advanced/simulatedannealing.cpp
               src/hillclimb/steepestascent.cpp
               src/hillclimb/sidewaysmove.cpp
               src/visualize/visualize.cpp)

target_link_libraries(main ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} matplotlib_cpp)