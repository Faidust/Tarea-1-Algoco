all: matrix_multiplication
	echo "archivo,algoritmo,n,tiempo,memoriaKB" > data/measurements/matrix_measurements.csv
	for archivo1 in data/matrix_input/*_1.txt; do \
		archivo2=$${archivo1%_1.txt}_2.txt; \
		if [ -f "$$archivo2" ]; then \
			./matrix_multiplication "$$archivo1" "$$archivo2"; \
		fi; \
	done

matrix_multiplication: matrix_multiplication.cpp algorithms/naive.cpp algorithms/strassen.cpp
	g++ -std=c++17 -pthread matrix_multiplication.cpp algorithms/naive.cpp algorithms/strassen.cpp -o matrix_multiplication

generate:
	cd scripts && python3 matrix_generator.py

clean:
	rm -f matrix_multiplication