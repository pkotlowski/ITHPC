#include <stdio.h>
#include <stdlib.h>
#define SIZE 15842*4

void fillMatrix(double **matrix,int rows,int cols);
void fillVector(double *vector,int cols);
void pr(double *result,int size);
void SAXPY(double *vector, double **matrix,double *result, int size);
int main(){

double **matrix, *vector, *result;
int i,j;
matrix = malloc(SIZE * sizeof(double *));
for (i = 0; i < SIZE; i++){
  matrix[i] = malloc(SIZE * sizeof(double *));
}
vector = malloc(SIZE * sizeof(double *));
result = malloc(SIZE * sizeof(double *));

fillMatrix(matrix,SIZE,SIZE);
fillVector(vector,SIZE);
SAXPY(vector,matrix,result,SIZE);
//pr(result,SIZE);
free(matrix);
free(vector);
free(result);
return 0;
}
void SAXPY(double *vector, double **matrix,double *result, int size){
int i,j;
#pragma omp parallel for shared(vector,matrix,result,size) private(i, j) 
for(i=0;i<size;i++){
	double tmp=0;
	for(j=0;j<size;j++){
		tmp=tmp+matrix[i][j]*vector[j];
	}
	result[i]=tmp;
}
}
void fillVector(double *vector,int cols){
int j;
for(j=0; j<cols; j++){  
            vector[j]=j;
        }
}
void fillMatrix(double **matrix,int rows,int cols){
int i,j;
for(i=0; i<rows; i++){    
        for(j=0; j<cols; j++){  
            matrix[i][j]=i+j;
        }        
    }
}

void pr(double *result,int size){
	int i;
	for(i=0;i<size;i++){
		printf("%f ",result[i] );
	}
}
