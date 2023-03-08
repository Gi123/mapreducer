cmake_minimum_required (VERSION 3.8)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
    project ("mapreduce" VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else ()
    project ("mapreduce")
endif()

if (UNIX)
    find_package (Threads)
endif()

file(GLOB mapreduce_file_cpp
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
# Добавьте источник в исполняемый файл этого проекта.
add_executable (${PROJECT_NAME} ${mapreduce_file_cpp})
target_include_directories(${PROJECT_NAME} 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include 
)

target_link_libraries(${PROJECT_NAME}
        ${CMAKE_THREAD_LIBS_INIT}
        ) 

if (UNIX)
    target_link_libraries (${PROJECT_NAME} Threads::Threads)
endif()

if (MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC
        /W4
    )
else ()

    target_compile_options(${PROJECT_NAME} PUBLIC
        -Wall -Wextra -pedantic -Werror
    )
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

include(CPack)