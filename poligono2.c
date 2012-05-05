#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <X11/Xlib.h>

struct ponto2D {
	  float x, y;
          };
	  
int largura, altura;

int Desenha_reta(int *, struct ponto2D, struct ponto2D);
int Desenha_janela(int *);

int main(void) {

 struct ponto2D P1, P2, P3, P4, P5, P6;
 int * imagem;
 
 P1.x = 130.0;
 P1.y = 45.0;
 
 P2.x = 180.0;
 P2.y = 110.0;
 
 P3.x = 250.0;
 P3.y = 30.0;
 
 P4.x = 400.0;
 P4.y = 270.0;
 
 P5.x = 190.0;
 P5.y = 450.0;
 
 P6.x = 70.0;
 P6.y = 320.0;
 
 largura = 500;
 altura = 500;
 
 imagem = (int *) malloc(largura*altura*sizeof(int));
 
 Desenha_reta(imagem, P1, P2);
 Desenha_reta(imagem, P2, P3);
 Desenha_reta(imagem, P3, P4);
 Desenha_reta(imagem, P4, P5);
 Desenha_reta(imagem, P5, P6);
 Desenha_reta(imagem, P6, P1);
 
 Desenha_janela(imagem);

 return 0;
 }

int Desenha_reta(int * imagem, struct ponto2D primeiro, struct ponto2D segundo) {
 float x, y, a, b;
 struct ponto2D aux;

 if (primeiro.x >= segundo.x) {
   aux.x = primeiro.x;
   aux.y = primeiro.y;
   primeiro.x = segundo.x;
   primeiro.y = segundo.y;
   segundo.x = aux.x;
   segundo.y = aux.y;
   }
 
 if (primeiro.x == segundo.x) {
      if (primeiro.y >= segundo.y) {
        aux.x = primeiro.x;
        aux.y = primeiro.y;
        primeiro.x = segundo.x;
        primeiro.y = segundo.y;
        segundo.x = aux.x;
        segundo.y = aux.y;
        }
    x = primeiro.x;
    y = primeiro.y;
    while (y <= segundo.y) {
      imagem[(int)y*largura+(int)x] = 1;
      y = y + 1.0;
      }
    }  
 else {
   a = (segundo.y - primeiro.y)/(segundo.x - primeiro.x);
   b = primeiro.y - a*primeiro.x;
   x = primeiro.x;
   while (x <= segundo.x) {
      y = a*x + b;
      imagem[(int)y*largura+(int)x] = 1;
      x = x + 0.1;
      }
    }

 return 0;
 }
 
int Desenha_janela(int * imagem) {
 Display * display;  
 GC gc;  
 Window win, root_window;
 XGCValues values;
 XColor cor;
 int screennumber, x, y;
 unsigned long white_pixel, black_pixel;
 
 display = XOpenDisplay(NULL); 
 screennumber = DefaultScreen(display); 
 root_window = RootWindow(display, screennumber); 
 black_pixel = BlackPixel(display, screennumber);  
 white_pixel = WhitePixel(display, screennumber); 
 win = XCreateSimpleWindow(display,root_window, 0, 0, largura, altura, 1, black_pixel, white_pixel);
 XMapWindow(display, win); 
 gc = XCreateGC(display, win, 0, &values); 
 XSync(display, False);  
 XSetForeground(display, gc, white_pixel);
 XSetBackground(display, gc, black_pixel); 
 XAllocNamedColor(display, XDefaultColormap(display, screennumber), "red", &cor, &cor);  
 XSetForeground(display, gc, cor.pixel);

 for(y = 0; y < altura; y++)
   for(x = 0; x < largura; x++)
      if (imagem[y*largura+x] == 1) XDrawPoint(display, win, gc, x, y); 
 
 XFlush(display);
 sleep(5);
 XFreeGC(display, gc);  
 XCloseDisplay(display);
 
 return 0;  
 }

 