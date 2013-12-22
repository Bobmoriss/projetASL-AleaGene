#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ieee754.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ALPHA_INITIAL 3.999 
#define ALPHA_FINAL	3.99999999 
#define PAS 0.00000001 // 1E-8
#define NB_ITER_PAR_ALPHA 1000 //Nombre de periode calculé pour chaque valeur de alpha
#define PERIODE_INITIAL 300000000 // 3E+8 Nombre d'iteration pour trouver une graine dans le cycle.
#define FICHIER_RES "resultats.txt"
#define FICHIER_LOG "logs.txt"
#define SEPARATOR "\t"

FILE *fd_res = NULL;
FILE *fd_log = NULL;

void ecrire_log(char* s){
	fprintf(fd_log,"%s\n",s);
	printf("%s\n",s);
}

void ecrire_res(double alpha, int p_min, int p_max){
	printf("Printing to res\n");
	fprintf(fd_res, "%lf%s%i%s%i\n",alpha,SEPARATOR,p_min,SEPARATOR,p_max);
}

double trouver_graine_cyclique(double x0,double alpha){
	double xn = x0;
	unsigned long long int i=0;
	while(i < PERIODE_INITIAL && xn > 0.5 ){
		xn = alpha*xn*(1-xn);
		i++;
	}
	fprintf(fd_log,"Pour alpha=%d et x0=%d on choisit la graine cyclique xn=%d\n",alpha,x0,xn);
	return xn ;
}

int trouver_periode(double x0,double alpha){
	double xn=x0;
	unsigned long long int i=0;
	do{
		xn = alpha*xn*(1-xn);
		i++;
	}
	while(xn != x0);
	fprintf(fd_log,"Pour alpha=%d et x0=%d on trouve une periode=%i\n",alpha,x0,i);
	return i;
}

void determiner_min_max(double alpha,unsigned long long int* p_min,unsigned long long int* p_max){
	double x0;
	unsigned long long int p;
	x0 = (double)rand()/(double)RAND_MAX;
	x0 = trouver_graine_cyclique(x0,alpha);
	p = trouver_periode(x0,alpha);
	if(p > (*p_max))
		*p_max = p;
	if(p < (*p_min))
		*p_min = p;
}

void calculer_min_max(double alpha){
	unsigned long long int i = 0;
	unsigned long long int* p_min = (unsigned long long int*)malloc(sizeof(unsigned long long int));
	unsigned long long int* p_max = (unsigned long long int*)malloc(sizeof(unsigned long long int));
	*p_min = PERIODE_INITIAL ;
	*p_max = 0;
	//printf("%d %d\n",*p_min,*p_max);
	for(i=0;i<NB_ITER_PAR_ALPHA;i++){
		determiner_min_max(alpha,p_min,p_max);
	}
	ecrire_res(alpha,*p_min,*p_max);
}

void a(){
	double alpha = ALPHA_INITIAL ;
	while(alpha < ALPHA_FINAL){
		calculer_min_max(alpha);
		alpha = alpha + PAS ;
	}
}



int main(int argc,char** argv){

	/* Initialisation des fd*/
	fd_res = fopen(FICHIER_RES, "w+") ;
	if (fd_res == NULL) {                                                                                                                                                        
        fprintf(stderr, "ERROR");                                                                                                      
        exit(EXIT_FAILURE);                                                                                                                                                         
    }    
	fd_log = fopen(FICHIER_LOG, "w+") ;
	if (fd_log == NULL) {                                                                                                                                                        
        fprintf(stderr, "ERROR");                                                                                                      
        exit(EXIT_FAILURE);                                                                                                                                                         
    }
    //printf("%p\n",fd_res);
    fprintf(fd_res, "Alpha%sp_min%sp_max\n",SEPARATOR,SEPARATOR);
    //printf("Alpha%sp_min%sp_max\n",SEPARATOR,SEPARATOR);

	printf("Debut de la recherche\n");
	a();
	fclose(fd_res);
	fclose(fd_log);
	return 0;
}