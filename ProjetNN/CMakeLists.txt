project(MethSeq)

cmake_minimum_required(VERSION 2.4.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")


#########################################
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
if (NOT SDL_FOUND)
  message (FATAL_ERROR "SDL not found")
endif (NOT SDL_FOUND)
link_libraries( ${SDL_LIBRARY}
  SDLmain)
#######################################

find_package(GSL REQUIRED)

include_directories(${GSL_INCLUDE_DIRS} ${GSLCBLAS_INCLUDE_DIRS})
set(LIBS ${LIBS} ${GSL_LIBRARIES} ${GSLCBLAS_LIBRARIES})
target_link_libraries(${LIBS})
link_libraries(${LIBS})


if(WIN32)
  set(Boost_USE_STATIC_LIBS ON)
endif(WIN32)
set(Boost_ADDITIONAL_VERSIONS "1.46.1" )
if ( WIN32 )
  find_package(Boost REQUIRED COMPONENTS  thread program_options system filesystem)
else ( WIN32 )
  find_package(Boost REQUIRED COMPONENTS thread program_options system filesystem)
endif ( WIN32 )
if ( Boost_FOUND )
  include_directories(${Boost_INCLUDE_DIRS})
  add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})
  link_directories(${Boost_LIBRARY_DIRS})
endif ( Boost_FOUND )


set(executable_output_path bin/${C_MAKE_BUILD_TYPE})

include(FindBoost)

find_package(
  Boost
  1.46.1
  #REQUIRED signals
  )


link_directories(${Boost_LIBRARY_DIRS})


MESSAGE(STATUS "Boost Found = ${Boost_FOUND}")
MESSAGE(STATUS "Boost include = ${Boost_INCLUDE_DIRS}")
MESSAGE(STATUS "Boost Librairies path= ${Boost_LIBRARY_DIRS}")
MESSAGE(STATUS "Boost Librairies path= ${BOOST_PROGRAM_OPTIONS_LIBRARY}")

include_directories(${Boost_INCLUDE_DIRS})

file(
  GLOB_RECURSE
  source_files
  src/main.cpp

  src/tools/smart_ptr.h
  src/tools/Vector.hpp
  src/tools/Matrix.hpp
  src/tools/Plot.hpp
  src/tools/Plot.cpp

  src/network/Module.hpp
  src/network/Module.cpp
  src/network/SigModule.hpp
  src/network/SigModule.cpp
  src/network/TanModule.hpp
  src/network/TanModule.cpp
  src/network/Expert.hpp
  src/network/Expert.cpp
  src/network/Loss.hpp
  src/network/Loss.cpp
  src/network/Layer.hpp
  src/network/Layer.cpp
  
  src/simulation/Display.hpp
  src/simulation/Display.cpp
  src/simulation/Map.hpp
  src/simulation/Goal.hpp
  src/simulation/IlluminatedSwitch.hpp
  src/simulation/misc.hpp
  src/simulation/Posture.hpp
  src/simulation/Robot.hpp
  src/simulation/Robot.cpp
  src/simulation/Laser.hpp
  src/simulation/Laser.cpp
  src/simulation/Radar.hpp
  src/simulation/Radar.cpp
  src/simulation/LightSensor.hpp
  src/simulation/LightSensor.cpp
  src/simulation/LinearCamera.hpp
  src/simulation/LinearCamera.cpp
  src/simulation/Navigation.hpp
  src/simulation/Navigation.cpp
  
)
add_executable(expert
                 ${source_files})



target_link_libraries(
	expert
	${Boost_LIBRARIES}
)
