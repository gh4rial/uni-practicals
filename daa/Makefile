CXXFLAGS=-Wall -Wextra -Wconversion -Wno-sign-conversion -Weffc++ -pedantic -std=c++20
DEBUG_FLAGS=-g

all: strassen all_sorts test_sorts dfs bfs prims wis

wis: weighted_interval_scheduling.cpp
	$(CXX) -o exe/wis weighted_interval_scheduling.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

prims: prims.cpp
	$(CXX) -o exe/prims utils/graphutils.cpp prims.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

bfs: bfs.cpp
	$(CXX) -o exe/bfs utils/queueutils.cpp utils/graphutils.cpp bfs.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

dfs: dfs.cpp
	$(CXX) -o exe/dfs utils/graphutils.cpp dfs.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

test: test.cpp
	$(CXX) -o exe/test utils/graphutils.cpp test.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

strassen: strassen.cpp
	$(CXX) -o exe/strassen utils/matrixutils.cpp strassen.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

test_sorts: test_sorts.cpp
	$(CXX) -o exe/test_sorts sorts.cpp test_sorts.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

all_sorts: merge_sort insertion_sort heap_sort quick_sort count_sort selection_sort bubble_sort radix_sort

count_sort: count_sort.cpp
	$(CXX) -o exe/count_sort utils/arrayutils.cpp count_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

radix_sort: radix_sort.cpp
	$(CXX) -o exe/radix_sort utils/arrayutils.cpp radix_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

quick_sort: quick_sort.cpp
	$(CXX) -o exe/quick_sort utils/arrayutils.cpp quick_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

heap_sort: heap_sort.cpp
	$(CXX) -o exe/heap_sort utils/arrayutils.cpp heap_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

merge_sort: merge_sort.cpp
	$(CXX) -o exe/merge_sort utils/arrayutils.cpp merge_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

insertion_sort: insertion_sort.cpp
	$(CXX) -o exe/insertion_sort utils/arrayutils.cpp insertion_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

selection_sort: selection_sort.cpp
	$(CXX) -o exe/selection_sort utils/arrayutils.cpp selection_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

bubble_sort: bubble_sort.cpp
	$(CXX) -o exe/bubble_sort utils/arrayutils.cpp bubble_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)
