#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

void mem_print(int odim, int idim; bool mem[odim][idim], int odim, int idim){
	for(int i=0; i<odim; i++){
		for(int j=0; j<idim; j++)
			printf("%d ", mem[i][j]);
		printf("\n");
	}
}
void mem_init(int odim, int idim; bool mem[odim][idim], int odim, int idim){
	for(int i=0; i<odim; i++){
		for(int j=0; j<idim; j++)
			mem[i][j]=0;
	}
}

void giveup_test(int odim, int idim, int n_fault){//TODO Multiple faults
	int r=(RAND_MAX+1U)%(odim*idim);
	if(random()<r)
		printf("%d ", 1);//giveup
	else
		printf("%d ", 0);
}
int main(){
	int common_dim=10;//Change to 1024
	int odim=common_dim ,idim=common_dim;
	bool mem[odim][idim];
	srandom(time(NULL));
	mem_init(mem, odim, idim);
	//mem_print(mem, odim, idim);
	//printf("%u", RAND_MAX+1U);
	//2**30
	for(int i=0; i<1000; i++)
		giveup_test(pow(2,10), pow(2,20));//812825 and 1321
}
