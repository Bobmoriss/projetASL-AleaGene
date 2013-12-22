
#include <ieee754.h>
#include <stdio.h>
#include <stdlib.h>

void affiche_bin(unsigned int n,int size)
{
	unsigned bit = 0 ;
	unsigned mask = 1 ;
	int i=0;
	for (i=0 ; i < size ; ++i)
	{
		bit = (n & mask) >> i ;
		printf("%d", bit) ;
		mask <<= 1 ;
	}
	printf(" ");
}

// void affiche_bin(int i,int size){
// 	char buffer [size];
//   itoa (i,buffer,2);
//   printf ("%s",buffer);

// }


int main (int argc, char ** argv)
{
union ieee754_double *pd1;
double X, Y, L;
unsigned long int sign, exp, M01, M02, M03,M04, M1, M2, M3, M4, mantissa0, mantissa1;
L=3.9999;
X=0.42325627;

X = L*X*(1.0-X);
pd1 = (union ieee754_double *)&X;
sign = pd1->ieee.negative;
exp = pd1->ieee.exponent;
mantissa0 = pd1->ieee.mantissa0;
mantissa1 = pd1->ieee.mantissa1;
// printf("%d %d %s %d",sign,exp,mantissa0,mantissa1);
affiche_bin(sign, 1);
affiche_bin(exp, 11);
affiche_bin(mantissa0, 20);
affiche_bin(mantissa1, 32);
printf("\n");


return 0;
} 