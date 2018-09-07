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
		printf("%d send to slave\n",var);
		MPI_Send(&var,1,MPI_INT,1,1,MPI_COMM_WORLD);
	}
	else if(rank==1){
		MPI_Recv(&id,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		printf("slave receives %d\n",id);
	}
	
	MPI_Finalize();
	
}
