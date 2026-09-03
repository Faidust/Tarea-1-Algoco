all: sorting
	echo "archivo,algoritmo,n,tiempo,memoriaKB" > data/measurements/sorting_measurements.csv
	for archivo in data/array_input/*.txt; do \
		./sorting "$$archivo"; \
	done

sorting: sorting.cpp algorithms/patiencesort.cpp algorithms/quicksort.cpp algorithms/mergesort.cpp algorithms/sort.cpp
	g++ -std=c++17 -pthread sorting.cpp algorithms/patiencesort.cpp algorithms/quicksort.cpp algorithms/mergesort.cpp algorithms/sort.cpp -o sorting

generate:
	cd scripts && python3 array_generator.py

clean:
	rm -f sorting