cmake_minimum_required(VERSION 3.10)
project(rufrender C)

set(CMAKE_C_STANDARD 11)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(LIBS_DIR ${CMAKE_SOURCE_DIR}/libs)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    ${LIBS_DIR}/glfw3.lib
    ${LIBS_DIR}/glew32.lib
    ${LIBS_DIR}/opengl32.lib
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${LIBS_DIR}/glew32.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_library(GLEW SHARED IMPORTED)
set_target_properties(GLEW PROPERTIES
    IMPORTED_IMPLIB "${LIBS_DIR}/glew32.lib"
    IMPORTED_LOCATION "${LIBS_DIR}/glew32.dll")

target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    ${LIBS_DIR}/glfw3.lib
    GLEW
    ${LIBS_DIR}/opengl32.lib
)

add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT")
endif()

if(MINGW)
  target_link_libraries(${PROJECT_NAME} -lgdi32 -lopengl32)
endif()
