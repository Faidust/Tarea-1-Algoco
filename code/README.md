# Documentación

## Entrega

La entrega se realiza vía **aula.usm.cl** en formato `.zip`.
Esta tarea 1 incluye la implementación de los algoritmos, scripts para generar graficos y casos de prueba, programas principales para ejecutar todos los algoritmos y realizar mediciones y el informe.

## Multiplicación de matrices

Se analizaron 2 algoritmos de multiplicación de matrices:

1 - Strassen: Divide las matrices en submatrices y usa 7 multiplicaciones recursivas
2 - Naive: Multiplicación de matrices filas y columnas, utilizando 3 ciclos anidados 

### Programa principal

El archivo matrix_multiplication.cpp lee los archivos de entrada (el cual es una matriz), ejecuta los algoritmos de multiplicación de matrices mencionados y mide su tiempo de ejecución y memoria utilizada, para luego guardar esos resultados obtenidos en un archivo csv en data/measurements

### Scripts

1- matrix_generator.py: genera los archivos de matrices usados como casos de prueba.
2- plot_generator.py: lee las mediciones obtenidas y genera automáticamente los gráficos de tiempo y memoria en formato png.

## Ordenamiento de arreglo unidimensional

Algoritmos: MergeSort, QuickSort, PatienceSort, std::sort.

1- MergeSort: Divide el arreglo en mitades, las ordena de forma recursiva y despues une todas las mitades
2- QuickSort: Divide el arreglo usando un pivote (al medio en este caso) y ordena recursivamente las particiones
3- PatienceSort: Distribuye los elementos en pilas, las cuales estan de menor a mayor y luego reconstruye el arreglo ordenado
4- Sort: Algoritmo de ordenamiento implementado de la biblioteca estándar de C++

### Programa principal

El archivo sorting.cpp, lee un arreglo el cual esta en un archivo de entrada y ejecuta los cuatro algoritmos de ordenamiento. Para cada algoritmo se mide el tiempo de ejecución y la memoria adicional utilizada, guardando los resultados en data/measurements

### Scripts

1- array_generator.py: genera los arreglos utilizados como casos de prueba.
2- plot_generator.py: lee las mediciones de los algoritmos y genera automáticamente los gráficos de tiempo y memoria en formato png.

## Ejecución

### Sorting

Para generar los arreglos de prueba se debe ejecutar "make generate" desde /code/sorting.

Para compilar y ejecutar los algoritmos de ordenamiento se utiliza "make" desde /code/sorting.

Para generar los gráficos de tiempo y memoria se debe ingresar a la carpeta "scripts" desde /code/sorting y ejecutar "python3 plot_generator.py".

### Matrix Multiplication

Para generar las matrices de prueba se debe ejecutar "make generate" desde /code/matrix_multiplication.

Para compilar y ejecutar los algoritmos de multiplicación de matrices se utiliza "make" desde /code/matrix_multiplication.

Para generar los gráficos de tiempo y memoria se debe ingresar a la carpeta "scripts" desde /code/matrix_multiplication y ejecutar "python3 plot_generator.py".

## Repositorio de github

https://github.com/Faidust/Tarea-1-Algoco