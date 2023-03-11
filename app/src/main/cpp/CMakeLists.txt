# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.22.1)

# Declares and names the project.

project("render")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

include_directories(
        egl
        render
        sample
        util
)

message('----------${CMAKE_SOURCE_DIR}')

file(GLOB src-files
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/egl/*.cpp
        ${CMAKE_SOURCE_DIR}/util/*.cpp
        ${CMAKE_SOURCE_DIR}/render/*.cpp
        ${CMAKE_SOURCE_DIR}/sample/*.cpp
        )

# 创建共享库  add_library(<target_name> [STATIC | SHARED | MODULE] source1 [source2 ...])
add_library( # Sets the name of the library.
        render

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${src-files})


# 查找的库文件
find_library( # Sets the name of the path variable.
        log-lib
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# target_link_libraries(目标名称 库名称1 库名称2 ...)
target_link_libraries( # Specifies the target library.
        render

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        EGL
        GLESv3
        android
        )