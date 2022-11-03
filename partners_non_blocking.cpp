#include <mpi.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
   const int MASTER = 0;
   int num_processes = 0;
   int process_id = 0; 
   int partner = 0;
   int i = 0;
   char host_name[MPI_MAX_PROCESSOR_NAME];
   MPI_Request requests[4];   // required variable for non-blocking calls
   MPI_Status statuses[4];   // required variable for Waitall routine
   int messages[2] = {111, 999};

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

   if (process_id == MASTER) 
      cout << "MASTER: The number of MPI processes is " << num_processes << "\n";

   int name_length = 0;
   MPI_Get_processor_name(host_name, &name_length);
      
   cout << "Hi from process " << process_id << " on " << host_name << "\n";

   int left = process_id - 1;
   int right = process_id + 1;

   if (process_id == 0)
      left = num_processes - 1;

   if (process_id == (num_processes - 1))
      right = 0;

   // post non-blocking receives and sends for neighbors
   MPI_Irecv(&messages[0], 1, MPI_INT, left, 101, MPI_COMM_WORLD, &requests[0]);
   cout << "Firstly, I process " << process_id << " set everything for receiving left's message " << messages[0] << endl;
   MPI_Irecv(&messages[1], 1, MPI_INT, right, 102, MPI_COMM_WORLD, &requests[1]);
   cout << "Firstly, I process " << process_id << " set everything for receiving right's message " << messages[1] << endl;      

   MPI_Isend(&process_id, 1, MPI_INT, left, 102, MPI_COMM_WORLD, &requests[2]);
   MPI_Isend(&process_id, 1, MPI_INT, right, 101, MPI_COMM_WORLD, &requests[3]);

   cout << "Do some work while sends/receives progress in background" << endl;

   while (i < 50) {
      i++;
      cout << "Process " << process_id << " doing nothing " << i << endl;
   }
      
   // wait for all non-blocking operations to complete
   MPI_Waitall(4, requests, statuses);
   cout << "Secondly, I process " << process_id << " received left's  message " << messages[0] << endl;
   cout << "Secondly, I process " << process_id << " received right's message " << messages[1] << endl;      
   cout << process_id << " Mission accomplished!" << endl;

   MPI_Finalize();
   return 0;
}