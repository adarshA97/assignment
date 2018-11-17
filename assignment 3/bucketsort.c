#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define length 100

int main(int argc, char* argv[])
{
	int r[length], i, j,, min,max, tmp, n,counter; rank,size, s[length];
  int* count, disp, b;
  MPI_Status status;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

 	if (rank == 0){
    for (i = 0; i < length; i++){
      r[i] = rand() % length;
    }
    for (i = 1; i < size; i++){
      MPI_Send(r,length,MPI_INT,i,1,MPI_COMM_WORLD);}
  	}
	else{
      MPI_Recv(r,length,MPI_INT,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
  	}
  counter = 0;
  min = rank * (length/size);
  max = (rank + 1) * (length/size);
  for (i = 0; i < length; i++){
   if ((r[i] >= min) && (r[i] < max)){
  counter += 1;
 	}
}
  	b = malloc(counter * sizeof(int));
  	counter = 0;
  	for (i = 0; i < length; i++){
    		if ((r[i] >= min) && (r[i] < max)){
      			b[counter] = r[i];
      			counter += 1;}
  }
  for (i = 0; i < counter; i++){
    		for (j = i+1; j < counter; j++){
      		if (b[i] > b[j]){
        			tmp = b[i];
        			b[i] = b[j];
        			b[j] = tmp;
     }
    }
  	}
  	if (rank == 0){
    count = malloc(size * sizeof(int));
    disp = malloc(size * sizeof(int));
  	}
  	MPI_Gather(&counter,1,MPI_INT,count,1,MPI_INT,0,MPI_COMM_WORLD);
    if (rank == 0){
    		disp[0] = 0;
    		for (i = 0; i < size-1; i++){
      			disp[i+1] = disp[i] + count[i];
    		}
  	}
  	MPI_Gatherv(b,counter,MPI_INT,s,count,disp,MPI_INT,0,MPI_COMM_WORLD);
  	if (rank == 0)
	{		printf("Before sort: \n");
    		for (i = 0; i < length; i++) 
			printf("%d ",r[i]);
    		printf("\nAfter sort: \n");
    		for (i = 0; i < length; i++) 
			printf("%d ",s[i]);
  }
  	MPI_Finalize();
  	return 0;
}
