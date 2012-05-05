#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#define PI 3.1415
#define round(x) ((int)((x)+(float)0.5))

struct matriz_transformacao {
	float a11, a12, a13;
	float a21, a22, a23;
	float a31, a32, a33;
};

struct ponto3D {
	float x, y, z;
};

struct ponto2D {
	int x, y;
};

struct ponto3D * Rotacao(struct matriz_transformacao *, struct ponto3D *);

struct ponto3D * Projeta(float, float, struct ponto3D *);

struct ponto3D * Sru2srn(float, float, float, float, struct ponto3D *);

struct ponto2D * Srn2srd(int, int, struct ponto3D *);

int Desenha_reta(Display *, GC, Window, struct ponto2D, struct ponto2D);

int Visualiza(int, int, struct ponto2D *);

int main(void) {
	int largura, altura, i;
 	float Cpz, Tz, rxmin, rxmax, rymin, rymax;
 	struct ponto3D * P[9], * PR[9], * PP[9], * PPN[9];
 	struct ponto2D * PD[9], pontos[9];
 	for (i=1;i<=8;++i) 
		P[i] = (struct ponto3D *) malloc(sizeof(struct ponto3D));
 	Cpz = -50.0;
 	Tz = 100.0;
 	P[1]->x = 50.0; P[1]->y = -30.0; P[1]->z = 15.0;
 	P[2]->x = 50.0; P[2]->y = -30.0; P[2]->z = -15.0;
 	P[3]->x = 50.0; P[3]->y = 30.0; P[3]->z = 15.0;
 	P[4]->x = 50.0; P[4]->y = 30.0; P[4]->z = -15.0;
	P[5]->x = -50.0; P[5]->y = -30.0; P[5]->z = 15.0;
	P[6]->x = -50.0; P[6]->y = -30.0; P[6]->z = -15.0;
	P[7]->x = -50.0; P[7]->y = 30.0; P[7]->z = 15.0;
	P[8]->x = -50.0; P[8]->y = 30.0; P[8]->z = -15.0;

 	for (i=1;i<=8;++i) 
		PP[i] = Projeta(Cpz, Tz, P[i]);

 	rxmin = -250.0; rxmax = 250.0; rymin = -250.0; rymax = 250.0;
 	for (i=1;i<=8;++i) 
		PPN[i] = Sru2srn(rxmin, rxmax, rymin, rymax, PP[i]);
 	largura = (int) 2*rxmax;
 	altura = (int) 2*rymax;
 	for (i=1;i<=8;++i) 
		PD[i] = Srn2srd(largura, altura, PPN[i]);
 	for (i=1;i<=8;++i) 
		pontos[i] = *PD[i];

	for (i=1;i<=8;++i) 
		printf("Ponto %d = %d %d \n",i, pontos[i].x,pontos[i].y);

 	Visualiza(largura, altura, pontos);
 	return 0;
}

struct ponto3D * Rotacao(struct matriz_transformacao * m, struct ponto3D * p) {
 	struct ponto3D * pr;
 	pr = (struct ponto3D *) malloc(sizeof(struct ponto3D));
 	(pr->x) = (m->a11)*(p->x) + (m->a12)*(p->y) + (m->a13)*(p->z);
 	(pr->y) = (m->a21)*(p->x) + (m->a22)*(p->y) + (m->a23)*(p->z);
 	(pr->z) = (m->a31)*(p->x) + (m->a32)*(p->y) + (m->a33)*(p->z);
 	return pr;
}

struct ponto3D * Projeta(float cpz, float tz, struct ponto3D * p) {
	float lambda = 0.0;
	struct ponto3D * pp;
 	pp = (struct ponto3D *) malloc(sizeof(struct ponto3D));
 	lambda = (tz - (p->z))/((p->z) - cpz);
 	pp->x = p->x + lambda*(p->x);
 	pp->y = p->y + lambda*(p->y);
 	pp->z = p->z + lambda*((p->z) - cpz);
 	return pp;
 }

struct ponto3D * Sru2srn(float rxmin, float rxmax, float rymin, float rymax, struct ponto3D * P) {
 	struct ponto3D * ponto;
 	ponto = (struct ponto3D *) malloc(sizeof(struct ponto3D));
 	ponto->x = (P->x - rxmin) / (rxmax - rxmin);
 	ponto->y = (P->y - rymin) / (rymax - rymin);
 	ponto->z = 0.0;
 	return ponto;
}

struct ponto2D * Srn2srd(int largura, int altura, struct ponto3D * P) {
 	struct ponto2D * ponto;
 	ponto = (struct ponto2D *) malloc(sizeof(struct ponto2D));
 	ponto->x = (int) round((P->x)*(largura-1));
 	ponto->y = (int) round((P->y)*(altura-1));
 	return ponto;
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
    	x = primeiro.x;
    	y = primeiro.y;
    	while (y <= segundo.y) {
     		XDrawPoint(display, win, gc, (int)round(x), (int)round(y));
      		y++;
      	}
    }else{
	   	a = ((float)(segundo.y - primeiro.y))/((float)(segundo.x - primeiro.x));
	   	b = (primeiro.y) - a*(primeiro.x);
	   	x = (float) primeiro.x++;
	   	y = a*x + b;
	   	while (x <= segundo.x) {
      		XDrawPoint(display, win, gc, (int)round(x), (int)round(y));
      		y = a*(++x) + b;
      	}
   	}
 	return 0;
}

int Visualiza(int largura, int altura, struct ponto2D * P) {
	Display * display;
	GC gc;
	Window win, root_window;
	unsigned long valuemask = 0;
	XGCValues values;
	XColor cor;
	int x = 0, y = 0, screennumber, espessura = 10, i;
	unsigned long white_pixel, black_pixel;
	display = XOpenDisplay(NULL);
	screennumber = DefaultScreen(display);
	root_window = RootWindow(display, screennumber);
	black_pixel = BlackPixel(display,screennumber);
	white_pixel = WhitePixel(display, screennumber);
	win = XCreateSimpleWindow(display,root_window,x,y,largura,altura,espessura,black_pixel,white_pixel);
	XMapWindow(display, win);
	gc = XCreateGC(display, win, valuemask, &values);
	XSync(display, False);
	XSetForeground(display, gc, white_pixel);
	XSetBackground(display, gc, black_pixel);
	XAllocNamedColor(display, XDefaultColormap(display, screennumber), "#FF7F00", &cor, &cor);
	XSetForeground(display, gc, cor.pixel);
	for (i=1;i<=8;++i) 
		XDrawPoint(display, win, gc, P[i].x, P[i].y);
	Desenha_reta(display, gc, win, P[1], P[2]);
	Desenha_reta(display, gc, win, P[3], P[1]); 
	Desenha_reta(display, gc, win, P[4], P[2]); 
	Desenha_reta(display, gc, win, P[3], P[4]);
	Desenha_reta(display, gc, win, P[5], P[6]);
	Desenha_reta(display, gc, win, P[8], P[6]); 
	Desenha_reta(display, gc, win, P[7], P[5]); 
	Desenha_reta(display, gc, win, P[7], P[8]);
	Desenha_reta(display, gc, win, P[3], P[7]);
	Desenha_reta(display, gc, win, P[4], P[8]);
	Desenha_reta(display, gc, win, P[1], P[5]);
	Desenha_reta(display, gc, win, P[2], P[6]);
	XFlush(display);
	getchar();
	XFreeGC(display,gc);
	XCloseDisplay(display);
	return 0;
}

