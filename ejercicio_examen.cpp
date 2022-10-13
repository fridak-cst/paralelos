#include <omp.h>
#include <iostream>
#include <time.h>

int main (int argc, char** argv) {
    // indica el tamanio de la cartera de clientes
	long long int numero_clientes = 100000000;
                                    
    // indica el numero de threads
	int number_threads = 10;
    
    // puede utilizarse para indicar el numero de clientes con un score crediticio malo
    long long int malos = 0; 

    // puede utilizarse para indicar el numero de clientes con un score crediticio bueno
    long long int buenos = 0; 

	// indica el tamanio de la cartera de clientes
    int* scores_crediticios {new int[numero_clientes]{}};
	
	// Cambia la semilla para generar diferentes numeros aleatorios.
    srand(time(NULL)); 

    // Crea aleatoriamente los scores crediticios de la cartera de clientes
	for (long long int i=0; i < numero_clientes; i++) {
        // Numero aleatorio del 1 al 100
        scores_crediticios[i] = rand() % 100 + 1;  
    }
		
    // Indica el numero de hilos a crear en la region paralela
	omp_set_num_threads(number_threads);
    
    /*Introduzca aqui su codigo paralelo para contar a los clientes con score bueno y malo */    
    /*Introduzca aqui su codigo paralelo para contar a los clientes con score bueno y malo */    
    /*Introduzca aqui su codigo paralelo para contar a los clientes con score bueno y malo */    
    /*Introduzca aqui su codigo paralelo para contar a los clientes con score bueno y malo */    
    /*Introduzca aqui su codigo paralelo para contar a los clientes con score bueno y malo */    

    std::cout << "La cantidad de clientes con un score crediticio malo es: \n";
    std::cout << "La cantidad de clientes con un score crediticio bueno es: \n";

	delete[] scores_crediticios;
}