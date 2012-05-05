#include <stdio.h>
#include <stdlib.h>

#define MAXIMO 30

int main(void) {
 float x1, y1, x2, y2, deltax, deltay, m, e;
 int i, j, k;
 
 //cria matriz 30x30
 char imagem[MAXIMO][MAXIMO];
 
 //preenche a matriz com espaços vazios
 for(j = 0; j < MAXIMO; j++) {
  for(i = 0; i < MAXIMO; i++) {
      imagem[j][i] = ' ';
      }
   }

 //define os pontos x e y
 x1 = 3.0;
 y1 = 6.4;
 x2 = 26.7;
 y2 = 24.4;
 
 deltax = x2 - x1;
 deltay = y2 - y1;
 
 if (deltax != 0.0) {
    m = deltay/deltax;
    e = m - 0.5;
    i = x1;
    j = MAXIMO - y1;
    for(k = 1;k <= deltax; k++) {
       imagem[j][i] = 219;
       while(e >= 0) {
         j = j - 1;  // Por que nesta implementação não é j = j + 1 ? R: pq comeca de baixo pra cima!
         e = e - 1.0;         
         }
       i = i + 1;
       e = e + m;
       }
    }          
 else exit(1);
 
 for(j = 0; j < MAXIMO; j++) {
  for(i = 0; i < MAXIMO; i++) {
    printf("%c",imagem[j][i]);
    }
  printf("\n");
  }
 
 system("PAUSE");	
 return 0;
 }
