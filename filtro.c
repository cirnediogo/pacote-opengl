#include <stdio.h>

#define SIZE 420
int grass[SIZE][SIZE][3];
int grassFiltered[SIZE][SIZE][3];

int main() {

    FILE *arq;
    arq = fopen("grass3.pnm", "r");
    char formato[3];
    int w, h, d;
    fscanf(arq, "%s %d %d %d", formato, &w, &h, &d);
    int i, j;
    for(i = 0; i < SIZE; i++)
	for(j = 0; j < SIZE; j++) {
	    int a, b, c;
	    fscanf(arq, "%d %d %d", &grass[i][j][0], &grass[i][j][1], &grass[i][j][2]);
	}
    fclose(arq);


    for(i = 0; i < SIZE; i++) {
	for(j = 0; j < SIZE; j++) {
	    //especificar a cor de grassFiltered[i][j][.]
	    //aqui temos o negativo da imagem, modifique para utilizar um filtro de media 5x5, trate as bordas como quiser
	    grassFiltered[i][j][0] = 255-grass[i][j][0];
	    grassFiltered[i][j][1] = 255-grass[i][j][1];
	    grassFiltered[i][j][2] = 255-grass[i][j][2];
	}
    }

    arq = fopen("media.pnm", "w+");
    fprintf(arq, "%s  %d %d %d\n", formato, w, h, d);
    for(i = 0; i < SIZE; i++)
	for(j = 0; j < SIZE; j++) {
	    int a, b, c;
	    a = grassFiltered[i][j][0];
	    b = grassFiltered[i][j][1];
	    c = grassFiltered[i][j][2];
	    fprintf(arq, "%d %d %d ", a, b, c);
	}

    fclose(arq);

    return 0;
}

