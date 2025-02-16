add_library(gmsh SHARED IMPORTED)
set_target_properties(gmsh PROPERTIES
        IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libgmsh.so"
        INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
)
set(GMSH_LIBRARIES gmsh)

file(GLOB_RECURSE SOURCES *.cpp)

foreach (CPP_FILE IN LISTS SOURCES)
    get_filename_component(CPP_FILE_NAME ${CPP_FILE} NAME_WE)
    add_executable(${CPP_FILE_NAME} ${CPP_FILE})
    target_link_libraries(${CPP_FILE_NAME} ${GMSH_LIBRARIES})
endforeach ()
