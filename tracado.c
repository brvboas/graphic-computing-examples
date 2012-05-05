#include <stdio.h>
#include <stdlib.h>

#define MAXIMO 30

int main(void) {

float x1, y1, /* coordenadas reais do primeiro ponto do segmento de reta */
      x2, y2, /* coordenadas reais do último ponto do segmento de reta */
      a, b,   /* parâmetros da equação da reta */
      x, y;   /* coordenadas dos pontos que pertencem a reta */

int i, j; /* indices dos pontos da matriz que conterá a aproximação */
          /* do segmento de reta */

char imagem[MAXIMO][MAXIMO];  /* matriz que conterá a representação matricial 
                              /* de um segmento */
                              /* de reta (vetor) de um espaço contínuo */

/* Valores de entrada */
/* Estes valores deveriam ser testados para verificar se não estão além dos */
/* intervalos permitidos */

x1 = 3.0;
y1 = 6.4;
x2 = 26.7;
y2 = 24.4;

/* Determinação dos valores de "a" e "b" */
/* y1 = a*x1 + b e y2 = a*x2 + b */
/* Sistema linear de duas equações com duas incógnitas */

if (x1 == x2) exit(1);  
else {
  a = (y2 - y1)/(x2 - x1); /* Como chegamos a isto? */
  b = y1 - a*x1;
  }

/* Fazendo o mapeamendo do segmento de reta na matriz imagem */

/* Inicializando a matriz imagem */
for(j = 0; j < MAXIMO; j++) {
  for(i = 0; i < MAXIMO; i++) {
     imagem[j][i] = ' ';
     }
  }

/* Determinando onde ficará (x1,y1) representadas em um espaço contínuo na matriz */
/* Critério adotado: aproximação por um valor inteiro */
i = x1; /* conversão implícita de um valor em ponto flutuante para um inteiro */
j = MAXIMO - y1; /* Por quê? */

/* Primeiro ponto da reta discretizada */
imagem[j][i] = 219;

/* Determinando onde ficará (x2,y2) representadas em um espaço contínuo na matriz */
/* Critério adotado: aproximação por um valor inteiro */
i = x2;
j = MAXIMO - y2; /* Por quê? */

/* Segundo ponto da reta discretizada */
imagem[j][i] = 219;

/* Traçando a reta seguindo um dos critérios visto em aula. Qual? */
x = x1++;
y = a*x + b;  /* (x,y) são pontos do espaço contínuo */

while (y < y2 - 1.0) {
  i = x;      
  j = MAXIMO - y;
  imagem[j][i] = 219;
  y = a*(++x) + b;
  }
 
/* Exibindo o segmento de reta */
for(j = 0; j < MAXIMO; j++) {
  for(i = 0; i < MAXIMO; i++) {
    printf("%c",imagem[j][i]);
    }
  printf("\n");
  }

printf("\n");
system("PAUSE");

return 0;
}

