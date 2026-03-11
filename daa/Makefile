CXXFLAGS=-Wall -Wextra -Wconversion -Wsign-conversion -Weffc++ -pedantic -std=c++20
DEBUG_FLAGS=-g

all: strassen sorts

strassen: strassen.cpp
	$(CXX) -o exe/strassen strassen.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

sorts: merge_sort insertion_sort heap_sort quick_sort count_sort selection_sort bubble_sort radix_sort

count_sort: count_sort.cpp
	$(CXX) -o exe/count_sort arrayutils.cpp count_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

radix_sort: radix_sort.cpp
	$(CXX) -o exe/radix_sort arrayutils.cpp radix_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

quick_sort: quick_sort.cpp
	$(CXX) -o exe/quick_sort arrayutils.cpp quick_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

heap_sort: heap_sort.cpp
	$(CXX) -o exe/heap_sort arrayutils.cpp heap_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

merge_sort: merge_sort.cpp
	$(CXX) -o exe/merge_sort arrayutils.cpp merge_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

insertion_sort: insertion_sort.cpp
	$(CXX) -o exe/insertion_sort arrayutils.cpp insertion_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

selection_sort: selection_sort.cpp
	$(CXX) -o exe/selection_sort arrayutils.cpp selection_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)

bubble_sort: bubble_sort.cpp
	$(CXX) -o exe/bubble_sort arrayutils.cpp bubble_sort.cpp $(CXXFLAGS) $(DEBUG_FLAGS)
