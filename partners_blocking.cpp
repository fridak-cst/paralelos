#include <mpi.h>
#include <iostream>


using namespace std;

int main (int argc, char *argv[]) {
   const int MASTER = 0;
   int num_processes = 0;
   int process_id = 0; 
   int partner = 0;
   int message = 0;
   char host_name[MPI_MAX_PROCESSOR_NAME];
   
   MPI_Status status;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

   // an even number of nodes is required
   if (num_processes % 2 != 0) {
      if (process_id == MASTER) 
         cout << "It needs an even number of processes " << num_processes << "\n";
   } else {
      if (process_id == MASTER) 
         cout << "MASTER: The number of MPI processes is " << num_processes << "\n";

      int name_length = 0;
      MPI_Get_processor_name(host_name, &name_length);
      
      cout << "Hi from process " << process_id << " on " << host_name << "\n";

      // determine your partner and exchange messages
      if (process_id < num_processes/2) {
         partner = process_id + num_processes/2;
         MPI_Send(&process_id, 1, MPI_INT, partner, 0, MPI_COMM_WORLD);
         MPI_Recv(&message, 1, MPI_INT, partner, 0, MPI_COMM_WORLD, &status);
      } else if (process_id >= num_processes/2) {
         partner = process_id - num_processes/2;
         MPI_Recv(&message, 1, MPI_INT, partner, 0, MPI_COMM_WORLD, &status);
         MPI_Send(&process_id, 1, MPI_INT, partner, 0, MPI_COMM_WORLD);
      }

      cout << "---------- Process " << process_id << " is partner with " << message << "\n";
   
   }

   MPI_Finalize();
   return 0;
}