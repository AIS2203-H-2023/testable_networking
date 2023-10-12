cmake_minimum_required(VERSION 3.26)
project(testable_networking)

option(NETWORKING_BUILD_TESTS "Enable tests" ON)

set(CMAKE_CXX_STANDARD 17)

# Disable Boost warning
set(Boost_NO_WARN_NEW_VERSIONS 1)

if (MSVC)
    # Boost asio wants this...
    add_compile_definitions("_WIN32_WINNT=0x0601")
endif ()

find_package(Boost COMPONENTS system REQUIRED)


add_subdirectory(examples)

if (NETWORKING_BUILD_TESTS)

    include(FetchContent)

    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v3.4.0
    )
    FetchContent_MakeAvailable(Catch2)

    enable_testing()
    add_subdirectory(tests)

endif ()
