#ifndef _GAME_H_
#define _GAME_H_

#define UP 'w'
#define LOW 's'
#define LEFT 'a'
#define RIGHT 'd'

#define BOMBA 'b'

void apresentacao();

int acabou();
void move(char direcao);

int ehDirecao(char direcao);

void ghost();
void explodePilula();
void explodePilula2(int x, int y, int somax, int somay, int qtd);

int ghostDirecao(int xatual, int yatual, int* xdestino, int* ydestino);

#endif