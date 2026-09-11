import pandas as pd
import matplotlib.pyplot as plt
import os


# Ruta del archivo de mediciones
archivo = "../data/measurements/sorting_measurements.csv"

# Carpeta donde se guardaran los graficos
carpeta_salida = "../data/plots"


# Crear carpeta si no existe
os.makedirs(carpeta_salida, exist_ok=True)


# Leer el csv
datos = pd.read_csv(archivo)


# Obtener informacion desde el nombre del archivo
def obtener_tipo(nombre):
    partes = nombre.split("_")
    return partes[1]


def obtener_dominio(nombre):
    partes = nombre.split("_")
    return partes[2]


datos["tipo"] = datos["archivo"].apply(obtener_tipo)
datos["dominio"] = datos["archivo"].apply(obtener_dominio)


# Tipos de arreglos
tipos = datos["tipo"].unique()

# Dominios
dominios = datos["dominio"].unique()


for tipo in tipos:

    for dominio in dominios:

        # Filtrar solo los casos de este tipo y dominio
        filtrados = datos[
            (datos["tipo"] == tipo) &
            (datos["dominio"] == dominio)
        ]

        if filtrados.empty:
            continue


        # Sacar promedio de las muestras a, b y c
        promedio = filtrados.groupby(
            ["algoritmo", "n"]
        )[["tiempo", "memoriaKB"]].mean().reset_index()


        # GRAFICO DE TIEMPO

        plt.figure()

        for algoritmo in promedio["algoritmo"].unique():

            datos_algoritmo = promedio[
                promedio["algoritmo"] == algoritmo
            ]

            datos_algoritmo = datos_algoritmo.sort_values("n")

            plt.plot(
                datos_algoritmo["n"],
                datos_algoritmo["tiempo"],
                marker="o",
                label=algoritmo
            )


        plt.xlabel("Cantidad de elementos (n)")
        plt.ylabel("Tiempo (segundos)")
        plt.title("Tiempo - " + tipo + " - " + dominio)

        plt.xscale("log")

        plt.legend()
        plt.grid()

        nombre_grafico = (
            carpeta_salida +
            "/tiempo_" +
            tipo +
            "_" +
            dominio +
            ".png"
        )

        plt.savefig(nombre_grafico)

        plt.close()


        # GRAFICO DE MEMORIA

        plt.figure()

        for algoritmo in promedio["algoritmo"].unique():

            datos_algoritmo = promedio[
                promedio["algoritmo"] == algoritmo
            ]

            datos_algoritmo = datos_algoritmo.sort_values("n")

            plt.plot(
                datos_algoritmo["n"],
                datos_algoritmo["memoriaKB"],
                marker="o",
                label=algoritmo
            )


        plt.xlabel("Cantidad de elementos (n)")
        plt.ylabel("Memoria (KB)")
        plt.title("Memoria - " + tipo + " - " + dominio)

        plt.xscale("log")

        plt.legend()
        plt.grid()

        nombre_grafico = (
            carpeta_salida +
            "/memoria_" +
            tipo +
            "_" +
            dominio +
            ".png"
        )

        plt.savefig(nombre_grafico)

        plt.close()


print("Graficos generados correctamente.")