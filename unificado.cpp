#include <mpi.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
   int num_processes = 0;
   int process_id = 0; 
   int name_length = 0;
   char host_name[MPI_MAX_PROCESSOR_NAME];
   int numero_de_enteros = 5;
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
   MPI_Get_processor_name(host_name, &name_length);

   cout << "Hola soy proceso " << process_id << " en " << host_name << "\n";
    /* Si eres el maestro, i.e., el primero proceso que sea crea, entonces*/
   if (process_id == 0) {
        int mensaje[numero_de_enteros] = {11, 12, 13, 14, 15};
        int partner = 1;
        int etiqueta = 101;
        MPI_Send(&mensaje, numero_de_enteros, MPI_INT, partner, etiqueta, MPI_COMM_WORLD);
        for (int i = 0; i < numero_de_enteros; i++) 
            cout << "Proceso " << process_id << " envio el mensaje " << mensaje[i] << endl;
   } else if (process_id == 1) {
        MPI_Status status;
        int mensaje[numero_de_enteros];
        int partner = 0;
        int etiqueta = 101;
        MPI_Recv(&mensaje, numero_de_enteros, MPI_INT, partner, etiqueta, MPI_COMM_WORLD, &status);
        for (int i=0; i < numero_de_enteros; i++)
            cout << "Hola de receiver " << process_id << " recibi " << mensaje[i] << endl;


   }
   

   
   
   
   
   
   MPI_Finalize();

   return 0;
}