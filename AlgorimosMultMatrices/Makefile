# Variables
CXX = g++
CXXFLAGS = -std=c++11 -O2
TARGETS = GenMatrix CubicoTradicional CubicoOptimizado AlgoritmoStrassen

# Regla por defecto: compilar todos los programas
all: $(TARGETS)

# Regla para compilar el generador de matrices
gen: GenMatrix.cpp
	$(CXX) $(CXXFLAGS) -o GenMatrix GenMatrix.cpp

# Regla para compilar el algoritmo cúbico tradicional
cubic: CubicoTradicional.cpp
	$(CXX) $(CXXFLAGS) -o CubicoTradicional CubicoTradicional.cpp

# Regla para compilar el algoritmo cúbico optimizado
opti: CubicoOptimizado.cpp
	$(CXX) $(CXXFLAGS) -o CubicoOptimizado CubicoOptimizado.cpp

# Regla para compilar el algoritmo de Strassen
strassen: AlgoritmoStrassen.cpp
	$(CXX) $(CXXFLAGS) -o AlgoritmoStrassen AlgoritmoStrassen.cpp

# Regla para ejecutar el generador y los algoritmos con tamaños específicos de matrices 
run_tests: all
#@echo "Generando matrices..."  
#./GenMatrix
	@echo "Ejecutando el algoritmo cúbico tradicional..."
	./CubicoTradicional
	@echo "Ejecutando el algoritmo cúbico optimizado..."
	./CubicoOptimizado
	@echo "Ejecutando el algoritmo de Strassen..."
	./AlgoritmoStrassen

# Regla para limpiar los binarios generados
clean:
	rm -f $(TARGETS) *.o

