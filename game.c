#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>

#include "ui.h"
#include "game.h"
#include "mapa.h"

MAPA m;
POSICAO person;

int exitgame = 0;
int tempilula = 0;

char comando;

int acabou() {
	POSICAO pos;

	int ganhou = !encontraMapa(&m, &pos, GHOST);
	int perdeu = !encontraMapa(&m, &pos, PERSON);
	int exit = (comando != 'E' ? 0 : 1);

	return ganhou || perdeu || exit;
}

int ehDirecao(char direcao) {
	return
		direcao == UP ||
		direcao == LOW ||
		direcao == LEFT || 
		direcao == RIGHT;
}

void move(char direcao) {

	int proximox = person.x;
	int proximoy = person.y;

	switch(direcao) {
		case UP:
			proximox--;
			break;
		case LOW:
			proximox++;
			break;
		case LEFT:
			proximoy--;
			break;
		case RIGHT:
			proximoy++;
			break;
	}

	if(!podeAndar(&m, PERSON, proximox, proximoy))
		return;

	if (ehPerson(&m, PILULA, proximox, proximoy)) {
		tempilula = 1;
	}

	moveMapa(&m, person.x, person.y, proximox, proximoy);
    person.x = proximox;
    person.y = proximoy;
}

int ghostDirecao(int xatual, int yatual, int* xdestino, int* ydestino) {
    int opcoes[4][2] = {
        { xatual   , yatual+1 },
        { xatual+1 , yatual   },
        { xatual   , yatual-1 },
        { xatual-1 , yatual   }
    };

    srand(time(0));
    for(int i = 0; i < 10; i++) {
        int posicao = rand() % 4;

        if (podeAndar(&m, GHOST, opcoes[posicao][0], opcoes[posicao][1])) {
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];
            return 1;
        }
    }
    return 0;
}

void ghost() {
    MAPA copia;

    copiaMapa(&copia, &m);

    for(int i = 0; i < m.linhas; i++) {
        for(int j = 0; j < m.linhas; j++) {
			if (copia.matriz[i][j] == GHOST) {

				int xdestino;
				int ydestino;

				int found = ghostDirecao(i, j, &xdestino, &ydestino);

				if (found) {
					moveMapa(&m, i, j, xdestino, ydestino);
				}
			}
        }
    }
    liberaMapa(&copia);
}

void explodePilula2(int x, int y, int somax, int somay, int qtd) {

	if (qtd == 0) return;

	int novox = x + somax;
	int novoy = y + somay;

	if (!ehValida(&m, novox, novoy)) return;
	if ( ehParede(&m, novox, novoy)) return;
	if ( ehPilula(&m, novox, novoy)) return;

	m.matriz[novox][novoy] = EMPTY;
	explodePilula2(novox, novoy, somax, somay, qtd-1);
}

void explodePilula() {

	if (!tempilula) return;

	explodePilula2(person.x, person.y, 0, 1, 3);
	explodePilula2(person.x, person.y, 0,-1, 3);
	explodePilula2(person.x, person.y, 1, 0, 3);
	explodePilula2(person.x, person.y,-1, 0, 3);

	tempilula = 0;
}

void apresentacao() {

	printf("\n=================================\n");
	printf("   Bem vindo ao Jogo do PacMan");
	printf("\n=================================\n");

	printf("\nComandos do jogo:");

	printf("\nw -> cima");
	printf("\ns -> baixo");
	printf("\nd -> direita");
	printf("\na -> esquerda");

	printf("\n");

	printf("\nPara sair do jogo digite: e/E");

	printf("\n");

	printf("\nPressione enter para continuar: ");
}

int main() {
	
	lerMapa(&m);
	encontraMapa(&m, &person, PERSON);
	apresentacao();

	getch();

	do {
		system("cls");
		printf("Pilula: %s\n", (tempilula ? "SIM" : "NAO"));
		imprimeMapa(&m);

		scanf(" %c", &comando);

		if (ehDirecao(comando)) move(comando);
		if (comando == BOMBA) explodePilula();

        ghost();

	} while (!acabou());

	printf("\nObrigado por jogar :)");
	getch();

	liberaMapa(&m);
}