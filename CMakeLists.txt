cmake_minimum_required(VERSION 3.16)
project(TDAVideo)

set(CMAKE_CXX_STANDARD 14)
set(BASE_FOLDER estudiante)

include_directories(${BASE_FOLDER}/include)
#add_library(imageio ${BASE_FOLDER}/src/imageio.cpp)
#add_library(image ${BASE_FOLDER}/src/image.cpp ${BASE_FOLDER}/src/imageop.cpp ${BASE_FOLDER}/src/imageIO.cpp)
add_library(video ${BASE_FOLDER}/src/video.cpp ${BASE_FOLDER}/src/image.cpp ${BASE_FOLDER}/src/imageop.cpp ${BASE_FOLDER}/src/imageIO.cpp)

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/rebobinar.cpp)
    add_executable(rebobinar ${BASE_FOLDER}/src/rebobinar.cpp)
    target_link_libraries(rebobinar LINK_PUBLIC video)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/morphing.cpp)
    add_executable(morphing ${BASE_FOLDER}/src/morphing.cpp)
    target_link_libraries(morphing LINK_PUBLIC video)
endif()

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
