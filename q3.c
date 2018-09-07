#include<mpi.h>
#include<stdio.h>
void main(int argc,char** argv){
	int rank,size,var,id;
	MPI_Init(&argc,&argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0){
		scanf("%d",&var);
		printf("%d is send\n",var);

	}
	
		MPI_Bcast(&var,1,MPI_INT,0,MPI_COMM_WORLD);
		printf("value received by process %d is %d\n",rank,var);
	
	MPI_Finalize();
	
}
