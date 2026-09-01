all: matrix_multiplication
	./matrix_multiplication

matrix_multiplication: matrix_multiplication.cpp algorithms/naive.cpp algorithms/strassen.cpp
	g++ -std=c++17 matrix_multiplication.cpp algorithms/naive.cpp algorithms/strassen.cpp -o matrix_multiplication

generate:
	cd scripts && python3 matrix_generator.py