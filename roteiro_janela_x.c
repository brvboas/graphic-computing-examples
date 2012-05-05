

/* 
   Programa exemplo para trabalhar com uma janela no ambiente X-Window
   Curso de Computação Gráfica, Bacharelado em Ciência da Computação - UFSCar campus Sorocaba
   Prof. Murillo Rodrigo Petrucelli Homem

   Observação: a implementação de um programa que utiliza a biblioteca X é bem complexa. Este roteiro
   tem como objetivo apresentar apenas o necessário para abrir uma janela gráfica para a implementação
   de alguns algoritmos vistos em sala de aula e dessa forma muitos detalhes serão negligenciados.

   Para compilar este programa, digite em um shell (Linux) a seguinte linha de comando:
   gcc roteiro_janela_x.c -o roteiro_janela_x -lX11

   Para executar o programa digite: ./roteiro_janela_x
*/


#include <stdio.h>    /* Biblioteca padrão das funções de entrada e saída da linguagem C. */
#include <unistd.h>   /* Para o uso de funções como sleep() etc ... */
#include <X11/Xlib.h> /* Arquivo de cabeçalho da biblioteca que implementa as funções de baixo nível 
                         para acesso ao servidor X. */

int main(void) {
  /* 
     O sistema X-Window pode suportar inúmeros "displays" conectados a um único computador.
     Um "display" é usado para fazer referência a uma coleção de monitores que compartilham 
     um teclado e um mouse. Em outras palavras, pode haver inúmeros monitores para cada "display". 
     Uma "screen" é um monitor (hardware).
  */

  /* 
     Cada servidor X tem um nome para o display na forma: hostname:displaynumber.screennumber.
     Esta informação é armazenada em uma estrutura do tipo Display.
     O "hostname" especifica o nome da máquina na qual o display está fisicamente conectado.
     O "displaynumber" é usado para fazer referência a coleção de monitores que compartilham um 
     teclado e um mouse. O "screennumber" é utilizado para referenciar um monitor específico.
     Em sistemas POSIX, o nome do display padrão é armazenado na variável de ambiente DISPLAY 
     do sistema operacional. Experimente digitar em um shell: echo $DISPLAY
  */
  Display * display;  

   /* 
     Contexto Gráfico: define um conjunto de atributos (cor do fundo, como as linhas serão 
     desenhadas etc) que serão utilizados pelas inúmeras funções de desenho do ambiente X.
     Quando declaramos uma variável deste tipo, assumimos um conjunto de atributos default, 
     mas eles podem ser alterados pelo programador através de funções específicas.
   */ 
  GC gc;  

  Window win, root_window; /* Ponteiros para as janelas criadas. */

  unsigned long valuemask = 0; /* Variável necessária para a função XCreateGC() para criar 
                                  um contexto gráfico. */
  XGCValues values;  /* Estrutura que contém os valores iniciais do GC. */
  XColor cor;        /* XColor é uma estrutura que contém informações sobre uma cor 
                        associada a um pixel. */

  /* Variáveis utilizadas neste programa exemplo. */
  int width = 256, height = 256, x = 0, y = 0, screennumber, espessura = 4;
 
  unsigned long white_pixel, black_pixel;

   /* 
     Abre uma conexão para o display passado como argumento para a função. Se o argumento NULL 
     é passado, é assumido o display padrão armazenado na variável de ambiente DISPLAY do SO. 
   */
  display = XOpenDisplay(NULL); 

  /* Retorna o número do screen referenciado pela função XOpenDisplay(). */
  screennumber = DefaultScreen(display); 

  /* Determina o identificador da janela raiz do monitor. Esta janela sempre existirá. */
  root_window = RootWindow(display, screennumber); 
  
  /* Valor dos pixels da borda. */
  black_pixel = BlackPixel(display,screennumber);  
  
  /* Valor dos pixels no interior (fundo) da janela. */
  white_pixel = WhitePixel(display, screennumber); 

  /* Cria uma janela. */
  win = XCreateSimpleWindow(display,root_window,x,y,width,height,espessura,black_pixel,white_pixel);
  
  /*
     O fato de criar a janela não significa que ela vai aparecer na tela. Para isso, usamos
     a XMapWindow() para que a janela seja exibida na tela.
  */    
  XMapWindow(display, win); 
  
  /* Cria o contexto gráfico para nossa aplicação. */
  gc = XCreateGC(display, win, valuemask, &values); 
 
  /* Atua praticamente da mesma forma que a XFlush(). */
  XSync(display, False);  
  
  /* Altera a cor da janela associada ao contexto gráfico gc. */ 
  XSetForeground(display, gc, white_pixel);

  /* Altera a cor de fundo da janela associada ao contexto gráfico. */
  XSetBackground(display, gc, black_pixel); 
 
  /* Aloca na variável "cor" as informações sobre a cor vermelha. */
  XAllocNamedColor(display, XDefaultColormap(display, screennumber), "red", &cor, &cor);  
   
  /* Altera no contexto gráfico a cor que será usada para desenhar um pixel. */
  XSetForeground(display, gc, cor.pixel);

  /* Desenha um pixel nas coordenadas (15,15) com a cor definida pela função anterior. */
  XDrawPoint(display, win, gc, 15, 15);

  /* Faz com que o X execute todas as requisições pendentes. */
  XFlush(display);

  /* Espera por alguns segundos ... */
  sleep(30); 

  /* Libera o GC. */
  XFreeGC(display,gc);  

  /* Encerra a sessão com o servidor X. */
  XCloseDisplay(display); 

  return 0;
  }


