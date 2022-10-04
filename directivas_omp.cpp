#include <iostream>
#include <omp.h>
using namespace std;

int main(int argc, char** argv) {

	const int number_threads = 12;
	const long long int vector_size = 100;
	const int chunk_size = vector_size / number_threads;
	
	int* a {new int[vector_size]};
	int* b {new int[vector_size]};
	int* c {new int[vector_size]};
	
	long long int i; 
	int thread_id;

	omp_set_num_threads(number_threads);

    #pragma omp parallel shared(a, b, c, vector_size, chunk_size) private(i, thread_id)
    {
        thread_id = omp_get_thread_num();
//		cout << "Thread " << thread_id << " waiting...\n";
		#pragma omp barrier 
		cout << "Thread " << thread_id << " moving on...\n";
		#pragma omp for schedule(static, chunk_size)
		for (i=0; i < vector_size; i++)
			a[i] = b[i] = i + 1;

        // SECTIONS Permite que un hilo (y no más) sea asignado a cada Section 
        #pragma omp sections 
        {
            #pragma omp section
            {
                cout << "Gane la seccion A y soy: " << thread_id << "\n";
                for(i=0; i < vector_size/2; i++) {
                    c[i] = a[i] + b[i];                    
                }
            }

            #pragma omp section 
            {
                cout << "Gane la sección B y soy: " << thread_id << "\n";
                for(i=vector_size/2; i < vector_size; i++){
                    c[i] = a[i] + b[i];
                }

            }

        }




    }

    delete[] a;
    delete[] b;
    delete[] c;
    cout<< "hola";
    return 0;
}