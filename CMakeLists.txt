project(dijkstra C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        abt/linked_list.c abt/linked_list.h
        )

add_executable(dijkstra main.c ${SOURCE_FILES})
add_executable(tests tests/cheat.h tests/linked-list-tests.c ${SOURCE_FILES})
