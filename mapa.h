#ifndef _MAPA_H_
#define _MAPA_H_

#define EMPTY '.'
#define GHOST 'F'
#define PERSON '@'
#define PILULA 'P'
#define WALL_VERTICAL '|'
#define WALL_HORIZONTAL '-'

struct mapa {
    char** matriz;
    int linhas;
    int colunas;
};

typedef struct mapa MAPA;

void alocaMapa(MAPA* m);
void lerMapa(MAPA* m);
void liberaMapa(MAPA* m);

struct posicao {
    int x;
    int y;
};

typedef struct posicao POSICAO;

int encontraMapa(MAPA* m, POSICAO* person, char c);

int ehValida(MAPA* m, int x, int y);
int ehParede(MAPA* m, int x, int y);
int ehPilula(MAPA* m, int x, int y);
int ehPerson(MAPA* m, char person, int x, int y);

void moveMapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino);
void copiaMapa(MAPA* destino, MAPA * origem);

int podeAndar(MAPA* m, char person, int x, int y);

#endif