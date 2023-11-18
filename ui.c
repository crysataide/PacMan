#include <stdio.h>

#include "mapa.h"

char drawingGhost[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char drawingWall[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char drawingPerson[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char drawingPilula[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char drawingEmpty[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void imprimeParte(char drawing[4][7], int parte) {
    printf("%s", drawing[parte]);
}

void imprimeMapa(MAPA* m) {
    for (int i = 0; i < m->linhas; i++) {
        for (int parte = 0; parte < 4; parte++) {
            for (int j = 0; j < m->colunas; j++) {
                switch (m->matriz[i][j]) {
                    case GHOST:
                        imprimeParte(drawingGhost, parte);
                        break;   
                    case PERSON:
                        imprimeParte(drawingPerson, parte);
                        break;   
                    case PILULA:
                        imprimeParte(drawingPilula, parte);
                        break;   
                    case WALL_VERTICAL:
                    case WALL_HORIZONTAL:
                        imprimeParte(drawingWall, parte);
                        break;   
                    case EMPTY:
                        imprimeParte(drawingEmpty, parte);
                        break;   
                }
            }
            printf("\n");
        }
    }
}