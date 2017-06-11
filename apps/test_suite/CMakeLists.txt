find_package(GTest REQUIRED)

if (GTEST_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
    file(GLOB UNITTEST_SRC_FILES
            components/BitFont/test_*.cpp
            apps/Core/test_*.cpp
            ../Core/Environment.cpp
    )
    file(GLOB UNITTEST_CORE_DEPS_FILES
            ../Core/LexicalInterpreter.cpp
            ../Core/RegisterController.cpp
            ../Core/Instructions/Op*.cpp
            ../Core/BaseInstructions.cpp
            ../Core/BaseInstruction.cpp
            ../Core/ControlUnit.cpp
            ../Core/pluginsystem/*.cpp)

    source_group(apps\\test_suite FILES test_suite.cpp ${UNITTEST_SRC_FILES})

    add_executable(test_suite test_suite.cpp ${UNITTEST_SRC_FILES} ${UNITTEST_CORE_DEPS_FILES})
    target_link_libraries(test_suite ${GTEST_BOTH_LIBRARIES} components dl ${Boost_LIBRARIES})

    # Fix for not visible pthreads functions for linker with glibc 2.15
    if (UNIX AND NOT APPLE)
        target_link_libraries(test_suite ${CMAKE_THREAD_LIBS_INIT})
    endif()
endif()