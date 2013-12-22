#include <ieee754.h>

void affiche_bin_2(int N, int T)
//Fonction qui écrit en binaire les éléments de v dans le fichier fic en utilisant les opérateurs de bits
{
 int a, i, j, bit, Taille;
 
 
     j=T-1;
     
     while (j>-1)
     {
         bit = (N >> (j) & 1); 
         printf ("%d",bit);
         j=j-1;
     }
     printf ("\n");
     
}

void MIKA_IEEE_754(unsigned int Long)
//Ma méthode
{
 short unsigned int bit1, bit2, bit3, b, dist;
 unsigned int i, j, k, l, x, y, z, r;
 unsigned long long int bx, by, bz, P;
 double X, Y, Z, Zb, Zx, Zy, Zz;
 
 union ieee754_double *pd1;
 union ieee754_double *pd2;
 union ieee754_double *pd3;
 unsigned long int sign, exp, M01, M02, M03,M04, M1, M2, M3, M4, mantissa0, mantissa1;
 time_t start,end;
 clock_t tps_1, tps_2, tps_inter; 
 double nbtops = CLOCKS_PER_SEC; 
 unsigned long long int Q;

 FILE * FIC;
 FIC = fopen("binaire.txt", "w");
 FILE * FIC2;
 FIC2 = fopen("correlation.txt", "w");
 //Long=8928571;
 //Long=35923140;
   Long=2436755950;
    //Zb=0.2467912856746353;
    //Zb=0.43241836985214754;
    X=0.24834264038461704925;
    Y=X + pow(2, -49.8289);
    Zb=Y + pow(2, -49.8289);
tps_1 = clock();
//for (j=0; j<1; j++)
//{
 
     X=0.24834264038461704925;
     Y=X + pow(2, -49.8289);
     Z=Zb;

    //X=0.2467912856746351;
    //Y=0.2467912856746352;
   //Z=Zb;
/*
X = 0.12345678901;
Y = 0.23456789012;
Z = 0.34567890123;
*/


for (k=0; k<29; k++)
     {
         X = 3.9999*X*(1.0-X);
         Y = 3.9999*Y*(1.0-Y);
         Z = 3.9999*Z*(1.0-Z);
     }


 for (i=0; i<Long; i++)
 {
     
         X = 3.9999*X*(1.0-X);
         Y = 3.9999*Y*(1.0-Y);
         Z = 3.9999*Z*(1.0-Z);
         
         pd1 = (union ieee754_double *)&X;
         pd2 = (union ieee754_double *)&Y;
         pd3 = (union ieee754_double *)&Z;
         /*
         sign = pd1->ieee.negative;
         exp = pd1->ieee.exponent;
         mantissa0 = pd1->ieee.mantissa0;
         mantissa1 = pd1->ieee.mantissa1;
         M1=mantissa1; M01=mantissa0;
         
         fprintf(FIC, "%d\n",i);
         fprintf(FIC, "%d ",sign);
         affiche_bin(exp, 11, FIC);
         affiche_bin(mantissa0, 20, FIC); 
         affiche_bin(mantissa1, 32, FIC);
         fprintf(FIC, "\n");
         
         
         
         sign = pd2->ieee.negative;
         exp = pd2->ieee.exponent;
         mantissa0 = pd2->ieee.mantissa0;
         mantissa1 = pd2->ieee.mantissa1;
         M2=mantissa1; M02=mantissa0;

         fprintf(FIC, "%d ",sign);
         affiche_bin(exp, 11, FIC);
         affiche_bin(mantissa0, 20, FIC); 
         affiche_bin(mantissa1, 32, FIC);
         fprintf(FIC, "\n");
         
         sign = pd3->ieee.negative;
         exp = pd3->ieee.exponent;
         mantissa0 = pd3->ieee.mantissa0;
         mantissa1 = pd3->ieee.mantissa1;
         M3=mantissa1; M03=mantissa0;

         fprintf(FIC, "%d ",sign);
         affiche_bin(exp, 11, FIC);
         affiche_bin(mantissa0, 20, FIC); 
         affiche_bin(mantissa1, 32, FIC);
         
         fprintf(FIC, "\n");
         
         */
         
         //mantissa0 = pd1->ieee.mantissa0;
         M1 = pd1->ieee.mantissa1;
         //M1=mantissa1; M01=mantissa0;
         
         //mantissa0 = pd2->ieee.mantissa0;
         //M02 = mantissa0;
         M2 = pd2->ieee.mantissa1;
         //M2=mantissa1;//printf("%d\n", M2);

         //mantissa0 = pd3->ieee.mantissa0;
         //M03 = mantissa0;
         M3 = pd3->ieee.mantissa1;
         //M3=mantissa1;//printf("%d\n", M3);
         
         //M04 = (M01^M02)^M03;
         M4 = (M1^M2)^M3;
         
         //affiche_bin(M04, 20, FIC);
         //affiche_bin(M4, 32, FIC);
         /*
         for (k=32; k>0; k--)
         {
             bit1 = (M1 >> (k-1) & 1);
             bit2 = (M2 >> (k-1) & 1);
             bit3 = (M3 >> (k-1) & 1);
             fprintf (FIC, "%d",(bit1+bit2+bit3)%2);
             
         }
         */
         /*
         for (k=20; k>0; k--)
         {
             b = (M04 >> (k-1) & 1);
             fprintf (FIC, "%d",b);
         }
         //fprintf(FIC," ");
         for (k=32; k>0; k--)
         {
             b = (M4 >> (k-1) & 1);
             
             fprintf (FIC, "%d",b);
         }
        
     
     fprintf(FIC,"\n");
         */
 }
//Zb=Zb + pow(2, -49.8289);

//}
tps_2 = clock(); 
printf("TC = %.2lf\n", (tps_2-tps_1)/nbtops);
fclose(FIC);
fclose(FIC2);
//return X;
}


void MIKA_IEEE_754_croisement(unsigned int Long)
//Ma méthode
{
 int F, d1, d2, d3;
 short unsigned int B, Bx, bx, By, by, Bz, bz, dist,C1, C2, C3, c1, c2, c3;
 unsigned int i, j, k, l, r, e;
 double X, Y, Z, Zb, Zx, Zy, Zz, x, y, z;
 
 union ieee754_double *pd1;
 union ieee754_double *pd2;
 union ieee754_double *pd3;
 unsigned int sign, exp, m1,M1, m2, M2, m3, M3, mantissa0, mantissa1, pasx, pasy, pasz, grx, gry, grz;
 time_t start,end;
 clock_t tps_1, tps_2, tps_inter; 
 double nbtops = CLOCKS_PER_SEC; 
 
 FILE * FIC;
 FIC = fopen("binaire.txt", "w");
 FILE * FIC2;
 FIC2 = fopen("correlation.txt", "w");

Long=190000000;

        //Zb=0.999999999999997;
        //Zb=0.956888543456566;
    Zb=0.000000000000003;
//for (j=0; j<15000; j++)
 //{
  // X=0.999999999999999;
  // Y=0.999999999999998;
     X=0.000000000000001;
     Y=0.000000000000002;
   //X=0.685546894548665;
   //Y=0.721578543456567;
   //X=0.4565433655656355;
   //Y=0.1467912882325621;
   Z=Zb;

tps_1 = clock();
for (k=0; k<30; k++)
     {
         X = 3.9999*X*(1.0-X);
         Y = 3.9999*Y*(1.0-Y);
         Z = 3.9999*Z*(1.0-Z);
     }

 for (i=0; i<Long; i++)
 {
         X = 3.9999*X*(1.0-X);
         Y = 3.9999*Y*(1.0-Y);
         Z = 3.9999*Z*(1.0-Z);
          // X = 3.9999*X - 3.9999*X*X;
          // Y = 3.9999*Y - 3.9999*Y*Y;
         //  Z = 3.9999*Z - 3.9999*Z*Z;
         pd1 = (union ieee754_double *)&X;
         pd2 = (union ieee754_double *)&Y;
         pd3 = (union ieee754_double *)&Z;
         
         m1 = pd1->ieee.mantissa0; 
         M1 = pd1->ieee.mantissa1; 
         m2 = pd2->ieee.mantissa0; 
         M2 = pd2->ieee.mantissa1;
         m3 = pd3->ieee.mantissa0; 
         M3 = pd3->ieee.mantissa1;
         
         
         k=32;
         while (k>0)
         {
             l=k-1;
             grx = m3 % k; 
             gry = m1 % k;
             grz = m2 % k;
             bx = (M1 >> (grx) & 1);
             by = (M2 >> (gry) & 1);
             bz = (M3 >> (grz) & 1);
             B = (bx+by+bz)%2;
             //fprintf (FIC, "%d",(bx+by+bz)%2);
             Bx=(M1 >> (l) & 1);
             By=(M2 >> (l) & 1);
             Bz=(M3 >> (l) & 1);

             if (bx != Bx)
             {
                 M1 = M1 ^ (1 << (l));
                 M1 = M1 ^ (1 << (grx));
             }
             if (by != By)
             {
                 M2 = M2 ^ (1 << (l));
                 M2 = M2 ^ (1 << (gry));
             }
             if (bz != Bz)
             {
                 M3 = M3 ^ (1 << (l));
                 M3 = M3 ^ (1 << (grz));    
             }
             k=k-1;
         }
     
 }
//Zb=Zb+0.000000000000001;

//}
tps_2 = clock(); 
printf("TC = %.2lf\n", (tps_2-tps_1)/nbtops);
fclose(FIC);
fclose(FIC2);
}
