#include <mpi.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

/**
 * \author Sébastien Boisvert
 * */
int main(int argc,char**argv){

	int MASTER_RANK=0;
	int TEST_MESSAGE=0;
	int messages=10000;

	int rank;
	int size;

	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	vector<int> received;
	received.resize(size);

	int total=0;

	if(size==1){
		cout<<"This test can not be run with 1 MPI rank."<<endl;
		return EXIT_FAILURE;
	}

	if(rank==MASTER_RANK){
		for(int i=0;i<(size-1)*messages;i++){
			MPI_Status status;
			MPI_Recv(NULL,0,MPI_BYTE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,
				&status);
		
			int tag=status.MPI_TAG;
			int source=status.MPI_SOURCE;
			received[source]++;
			total++;

			cout<<"Received message from "<<source<<", total: "<<received[source]<<" ";

			double expected=100.0/size;
			double actual=100.0*received[source]/total;

			cout<<"expected: "<<expected<<" actual: "<<actual<<endl;
		}
	}else{
		for(int i=0;i<messages;i++){
			MPI_Send(NULL,0,MPI_BYTE,MASTER_RANK,TEST_MESSAGE,MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();

	return EXIT_SUCCESS;
}
