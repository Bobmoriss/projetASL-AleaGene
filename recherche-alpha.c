#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ieee754.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define ALPHA_INI 3.999
#define ALPHA_FIN 3.99900004 
#define       PAS 0.00000001 // 1E-8
#define NB_ITER_PAR_ALPHA 1000 //Nombre de periode calculé pour chaque valeur de alpha
#define PERIODE_INITIAL 300000000 // 3E+8 Nombre d'iteration pour trouver une graine dans le cycle.
#define FICHIER_RES "resultats.txt"
#define FICHIER_LOG "logs.txt"
#define SEPARATOR "\t"

double Alpha_ini = ALPHA_INI;
double Alpha_final = ALPHA_FIN;
int Nb_iter_par_alpha = NB_ITER_PAR_ALPHA ;
char * Fichier_res ;

FILE *fd_res = NULL;
FILE *fd_log = NULL;

void ecrire_log(char* s){
	fprintf(fd_log,"%s\n",s);
	//printf("%s\n",s);
	fflush(fd_log);
}

void ecrire_res(double alpha, unsigned long long int p_min, unsigned long long int p_max){
	fprintf(fd_res,"%.8lf%s%llu%s%llu\n",alpha,SEPARATOR,p_min,SEPARATOR,p_max);
	fflush(fd_res);
}

double trouver_graine_cyclique(double x0,double alpha){
	double xn = x0;
	unsigned long long int i=0;
	while(i < PERIODE_INITIAL || xn > 0.5 ){
		xn = alpha*xn*(1-xn);
		i++;
		//if(i%1000000 == 0)
			//printf("Grain cyclique %ld\n",i);
	}
	fprintf(fd_log,"Pour alpha=%lf et x0=%lf on choisit la graine cyclique xn=%lf\n",alpha,x0,xn);
	return xn ;
}

int trouver_periode(double x0,double alpha){
	double xn=x0;
	unsigned long long int i=0;
	do{
		xn = alpha*xn*(1-xn);
		// printf("%lf\n",xn);
		i++;
		// if(i%10000000 == 0)
		// 	printf("Trouver_periode %ld\n",i);
	}
	while(xn != x0);
	//printf("x0 : %.25lf\nxn : %.25lf\n",x0,xn);
	fprintf(fd_log,"Pour alpha=%lf et x0=%lf on trouve une periode=%llu\n",alpha,x0,i);
	return i;
}

double get_random_double(int precision){
	double result = 0.0;
   	double div = 1.0;
	double mul = 1.0;
	int i=0;
	for (i = 0; i < precision; i++)
	{
	  int t = rand() % 10;
	  result += t * mul;
	  mul *= 10.0;
	  div /= 10.0;
	}    
	return result * div;
}

void determiner_min_max(double alpha,unsigned long long int* p_min,unsigned long long int* p_max){
	double x0;
	unsigned long long int p;
	x0 = (double)rand()/(double)RAND_MAX;
	//printf("Graine aleatoire : %.9lf\n",x0);
	x0 = trouver_graine_cyclique(x0,alpha);
	//printf("Graine cyclique : %.9lf\n",x0);
	p = trouver_periode(x0,alpha);
	//printf("Periode : %llu\n",p);
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
	//printf("Alpha : %.9lf\n",alpha);
	for(i=0;i<Nb_iter_par_alpha;i++){
		determiner_min_max(alpha,p_min,p_max);
	}
	printf("Max : %llu Min : %llu\n",*p_max,*p_min);
	ecrire_res(alpha,*p_min,*p_max);
}

void a(){
	double alpha = Alpha_ini ;
	while(alpha < Alpha_final){
		calculer_min_max(alpha);
		alpha = alpha + PAS ;
	}
}



int main(int argc,char** argv){
	Fichier_res = (char*)calloc(sizeof(char),256);
	strcpy(Fichier_res,FICHIER_RES) ;
	if(argc != 1){
		if(argc != 5){
			printf("%s usage: alpha_initial nb_alpha nb_iter_par_alpha fichier_resultat\n",argv[0]);
			exit(0);
		}
		Alpha_ini = atof(argv[1]);
		Alpha_final = Alpha_ini + (atoi(argv[2])-1)*PAS;
		Nb_iter_par_alpha = atoi(argv[3]);
		Fichier_res = argv[4];
	}
	else
		printf("Starting with default parameters\n");
	/* Initialisation des fd*/
	fd_res = fopen(Fichier_res, "w+") ;
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