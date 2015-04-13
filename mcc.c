#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>


double losuj(double, double); /*Prototyp funkcji*/


int main(int argc, char *argv[]){
	
	
	int i, 
	liczba_trafien=0, 		/*liczba_trafien sluzy do okreslania czy punkt lezy wewnatrz koĹ‚a*/
	id_procesu, 
	ilosc_procesow,
	ilosc_rzutow;
	
	double x,y,z, 
	liczba_PI_procesu,
	suma_wynikow_czesciowych,czas_poczatkowy, czas_koncowy;
	
	struct timeval stime;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ilosc_procesow);
	MPI_Comm_rank(MPI_COMM_WORLD, &id_procesu);
	
	if(argc > 1){
			ilosc_rzutow = atoi(argv[1]);				
			}
	else{
			ilosc_rzutow = 100000;
	}
	if(id_procesu == 0){
			printf("Wybrano %d prĂłb\n", ilosc_rzutow);
	}
	
	czas_poczatkowy = MPI_Wtime();
	
	srand(2);
	gettimeofday(&stime, NULL);
	  
	
	//Caly for musi byc wykonywany w kazdym procesie!!!!!!!!
	for (i=0;i<ilosc_rzutow;i++){
		x = losuj(1.0,-1.0);
		y = losuj(1.0,-1.0);
	
	
	z = pow(x,2)+ pow (y,2);
	if(z<=1.0){
			liczba_trafien++;
		}
		
	}
	liczba_PI_procesu = 4.0 * liczba_trafien/ilosc_rzutow;
	
	printf("Proces %d obliczyl %11.10lf trafiĹ‚ %d\n", id_procesu, liczba_PI_procesu, liczba_trafien);
	MPI_Reduce(&liczba_PI_procesu, &suma_wynikow_czesciowych, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	czas_koncowy = MPI_Wtime();	
	if(id_procesu == 0){
		printf("Liczba Pi z biblioteki math.h: %11.10lf\n", M_PI);
		printf("Liczba PI obliczona: %11.10lf\n", suma_wynikow_czesciowych/ilosc_procesow);
		printf("Czas potrzebny do obliczenia:  %f s\n", (czas_koncowy - czas_poczatkowy));
		
	}
	
	MPI_Finalize();
	return 0;
}
/* funkcja losujÄ…ca punkt z przedziaĹ‚u -1,-1;1,-1 itp. Argumentami sÄ… wartoĹ›Ä‡i min i max*/
double losuj(double a, double b){
		
	double wynik = (a-b) * ((double)rand() / (double)RAND_MAX)+b;		
	return wynik;
}