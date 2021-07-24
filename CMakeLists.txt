project(dijkstra C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        adt/linked_list.c adt/linked_list.h
        graph/graph.c graph/graph.h
        )

add_executable(dijkstra main.c ${SOURCE_FILES} graph/graph.c graph/graph.h)

add_executable(tests ${SOURCE_FILES} tests/main-tests.c)
