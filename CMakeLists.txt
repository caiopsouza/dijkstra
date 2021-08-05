project(dijkstra C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        adt/edge.c adt/edge.h
        adt/array.c adt/array.h
        adt/heap.c adt/heap.h
        adt/linked_list.c adt/linked_list.h
        graph/graph.c graph/graph.h
        solver/dijkstra_array.c solver/dijkstra_array.h
        solver/dijkstra_heap.c solver/dijkstra_heap.h)

add_executable(dijkstra main.c benchmark.h benchmark.c ${SOURCE_FILES})

set(TEST_FILES
        tests/main-tests.c)

set(CMAKE_C_FLAGS_RELEASE "-O3 -DNO_FREE")

add_executable(tests ${SOURCE_FILES} ${TEST_FILES})
