#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#define ROUND(x) (int)(x+0.5)

struct ponto2D {
	  float x, y;
          };

int Desenha_reta(Display *, GC, Window, struct ponto2D, struct ponto2D);
int Visualiza(int, int, struct ponto2D, struct ponto2D);

int main(void) {
 int largura, altura;
 struct ponto2D P1, P2;
 
 P1.x = 30;
 P1.y = 30;
 
 P2.x = 450;
 P2.y = 450;
 
 largura = 500;
 altura = 500;

 Visualiza(largura, altura, P1, P2); 
 
 return 0;
 }

int Desenha_reta(Display * display, GC gc, Window win, struct ponto2D primeiro, struct ponto2D segundo) {
 float a, b, x, y;
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
      XDrawPoint(display, win, gc, (int)ROUND(x), (int)ROUND(y));
      y = y + 1.0;
      }
    }  
 else {
   a = (segundo.y - primeiro.y)/(segundo.x - primeiro.x);
   b = (primeiro.y) - a*(primeiro.x);
   x = primeiro.x;
   while (x <= segundo.x) {
      y = a*x + b;
      XDrawPoint(display, win, gc, (int)ROUND(x), (int)ROUND(y));
      x = x + 0.1;
      }
   }

 return 0;
 }

int Visualiza(int largura, int altura, struct ponto2D P1, struct ponto2D P2) {
 Display * display;  
 GC gc;  
 Window win, root_window;
 XGCValues values;
 XColor cor;
 int screennumber, i;
 unsigned long white_pixel, black_pixel;

 display = XOpenDisplay(NULL); 
 screennumber = DefaultScreen(display); 
 root_window = RootWindow(display, screennumber); 
 black_pixel = BlackPixel(display,screennumber);  
 white_pixel = WhitePixel(display, screennumber); 
 win = XCreateSimpleWindow(display, root_window, 0, 0, largura, altura, 4, black_pixel, white_pixel);
 XMapWindow(display, win); 
 gc = XCreateGC(display, win, 0, &values); 
 XSync(display, False);  
 XSetForeground(display, gc, white_pixel);
 XSetBackground(display, gc, black_pixel); 
 XAllocNamedColor(display, XDefaultColormap(display, screennumber), "red", &cor, &cor);  
 XSetForeground(display, gc, cor.pixel);
 Desenha_reta(display, gc, win, P1, P2);
 XFlush(display);
 getchar();
 XFreeGC(display,gc);  
 XCloseDisplay(display); 

 return 0;
 }
