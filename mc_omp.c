#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX 1024*1024*100
float *tab, a=1.0,b=-1.0;
int i =0, j=0,liczba_rzutow=MAX, liczba_trafien=0;

int main(){
	readFile();
	for(j=0;j<MAX;j=j+1){
		srand(time(NULL)+rand());	
		double x = (a-b) * ((double)rand() / (double)RAND_MAX)+b;
		double y = (a-b) * ((double)rand() / (double)RAND_MAX)+b;
		if((pow(x,2)+pow(y,2))<=1.0){
			liczba_trafien++;
		}
	}
	printf("%.10f %d %d \n", 4.0*liczba_trafien/liczba_rzutow, liczba_rzutow, liczba_trafien);
	free(tab);
	return 0;
}

int readFile (){
	tab = malloc(sizeof *tab * (MAX + 1));
	FILE *ptr_file;
    		char buf[1000];

    		ptr_file =fopen("data","r");
    		if (!ptr_file)
        		return 1;

    		while ((fgets(buf,1000, ptr_file)!=NULL)&& i<MAX){
        		tab[i]=atof(buf);
        		i++;
}
		fclose(ptr_file);
    		return 0;

}