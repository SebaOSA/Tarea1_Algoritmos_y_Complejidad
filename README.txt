===========================================================================================================
                                                    (Tarea 1 Algoco)

===========================================================================================================

Fecha: 10/09/2024
Nombre: Sebastian Olea Schaufler
Rol: 202273566-K 

-----------------------------------------------------------------------------------------------------------

[Paquetes Utilizados]

-----------------------------------------------------------------------------------------------------------



- No es necesario instalar ningún paquete



-----------------------------------------------------------------------------------------------------------

[Ambiente de Ejecución Usado]

-----------------------------------------------------------------------------------------------------------

- Sistema Operativo usado: Windows Subsystem Linux (WSL)

- IDE: Visual Studio Code 1.88


-----------------------------------------------------------------------------------------------------------

[Instrucciones de Ejecución]

-----------------------------------------------------------------------------------------------------------


1. Tener un interpretador del lenguaje de programacion C++ (Visual Code Studio de preferencia)

2. Ejecutar el programa con makefile en el siguiente orden (teniendo el PATH en la carpeta donde se encuentra este mismo):
        Para los arreglos:
          - make -f Makefile (crear los .o)
          - make -f Makefile run-bubble (corre BubbleSort)
          - make -f Makefile run-merge (corre MergeSort)
          - make -f Makefile run-quick (corre QuickSort)
          - make -f Makefile run-sort (corre Sort Estandar)
          - make -f Makefile run-gen (genera los archivos de matrices)
          - make -f Makefile run-all (corre todos los Sort)
          - make -f Makefile clean (borra los .o)

        Para las Matrices:
          - make all(crear los ejecutables)
          - make run_tests (correr todos los Algoritmos)
-----------------------------------------------------------------------------------------------------------

[Consideraciones]

-----------------------------------------------------------------------------------------------------------

1. No printea la matriz ni el arreglo resultante pero si da los tiempos

4. Los comentarios de los getters y setters los puse todo en uno debido a que podria ser muy tedioso hacerlos y leerlos uno por uno.

5. En la mayoria de los inputs si ingresas algo que no sea un numero tirara error :,c.

6. Me hubiera gustado hacer mas cosas pero por problemas de tiempo no las hice :c.
