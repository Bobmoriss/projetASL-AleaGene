/*Programme qui crée une suite pseudo aléatoire en utilisant des congruences*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ieee754.h>

int main(void)
{
unsigned int P, P2;
int c, k, P_min, P_max;
P_min=100000000;
P_max=10;
P=P_max;
P2=P_min;
c=0; k=1;
char stop = 0;
unsigned long long int i, j, T, minc, MAXC;
double X, X_ref, X_min, X_MAX, X0, L, L_M;
T=pow(2, 32);
X0=0.252001202574591050648521;
//X=0.00862574591050648521;
//X=0.49862574591050648521;
FILE * fic;
fic=fopen("resultats.txt", "w");
//X=0.00433678086587329249;
X0=X0+0.000001;
//k=0;
//L=3.999999839999393;
L=3.99999999;

while (L<4.0 && P<178845757)
{
X0=0.000001202574591050648521;
fprintf(fic, "Lambda = %6.20lf\n", L);
k=0;
while (X0<1.0 && k<13000)
{
 i=0;
 X=X0;
while (i<300)
{
      X = L * X * (1.0-X);
      i++;
}

while (X > 0.5)
{
      X = L * X * (1.0-X);
}
X_ref = X;
X = L * X * (1.0-X);
i=1;
 while((X != X_ref) && (i < T))
{
     X = L * X * (1.0-X);
     i++;
}
//if (i<T && (i!=40037583) && (i!=2169558) && (i!=2952866))
if (i<T)
{
   //printf("X = %6.20lf\n", X);
   //printf("Cycle = %llu\n", i);
   //c++;
   fprintf(fic, "%6.20lf %llu\n", X, i);
   if (i<P_min)
   {
       P_min=i;
   }
   if (i>P_max)
   {
       P_max=i;
   }
   k++;
}

X0=X0+0.000000000000001;
}
if (P<P_max)
{
   P=P_max;
   L_M=L;
}
if (P2>P_min)
{
   P2=P_min;
   //L_M=L;
}
L=L+0.000000000000001;
fprintf(fic, "\n\n");
L=5.0;
}
/*if (P>178845757)
{
printf("yes on l'a trouvé : %u\n", P);
}*/
fprintf(fic, "\n\nLe meilleur Lambda est %6.20lf\n", L_M);
fprintf(fic, "\nP_max = %u\n", P);
fprintf(fic, "\nP_min = %u\n", P2);

//printf("P_min = %d\n", P_min);
//printf("P_max = %d\n", P_max);

fclose(fic);
  return 0;
}
//minc = 2169558 pour X_min = 0.09213901293891887945
//MAXC = 40037583 pour X_MAX = 0.13877085470046165994 