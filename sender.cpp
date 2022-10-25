#include <mpi.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
   int num_processes = 0;
   int process_id = 0; 
   int name_length = 0;
   char host_name[MPI_MAX_PROCESSOR_NAME];
   /* Puse el partner 0 asumiendo que el sender.exe se ejecutara despues de
   receiver.exe */
   int partner = 0; 
   int numero_de_enteros_a_enviar = 5;
   int mensaje[5] = {11, 12, 13, 14, 15};
   int etiqueta = 101;
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
   MPI_Get_processor_name(host_name, &name_length);

   cout << "Hola soy proceso " << process_id << " en " << host_name << "\n";

   MPI_Send(&mensaje, numero_de_enteros_a_enviar, MPI_INT, partner, etiqueta, MPI_COMM_WORLD);
   for (int i = 0; i < numero_de_enteros_a_enviar; i++) 
      cout << "Proceso " << process_id << " envio el mensaje " << mensaje[i] << endl;
   MPI_Finalize();

   return 0;
}