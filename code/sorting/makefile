all: sorting
	./sorting

sorting: sorting.cpp algorithms/patiencesort.cpp algorithms/quicksort.cpp algorithms/mergesort.cpp algorithms/sort.cpp
	g++ -std=c++17 sorting.cpp algorithms/patiencesort.cpp algorithms/quicksort.cpp algorithms/mergesort.cpp algorithms/sort.cpp -o sorting

generate:
	cd scripts && python3 array_generator.py

clean:
	rm -f sorting