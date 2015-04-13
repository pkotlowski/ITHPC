#include <stdio.h>
#include <stdlib.h>
#include <time.h>
double losuj(double a, double b);
int main(){
	int i=0;
	for(i=0;i<1024;i++){
	printf("%f\n",losuj(1.0,-1.0) );
}
	return 0;
}

double losuj(double a, double b){
	srand(time(NULL)+rand());	
	double wynik = (a-b) * ((double)rand() / (double)RAND_MAX)+b;		
	return wynik;
}