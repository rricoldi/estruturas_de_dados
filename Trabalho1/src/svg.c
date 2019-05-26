#include "svg.h"
#include "lista.h"
#include <stdio.h>

void iniciaSvg(char arq[]){
    FILE *arqout;
    
    arqout = fopen(arq, "w");
    if (arqout == NULL){ 
        printf("Nao foi possivel Abrir o arquivo svg");
        exit(1);
    }
    
    fprintf(arqout, "<svg>");
    
    fclose(arqout);
}

void finalizaSvg(char arq[]){
	FILE* arqout;
	
    arqout = fopen(arq, "a");
     if (arqout == NULL){
        printf("Nao foi possivel Abrir o arquivo geo");
        exit(1);
    }
    
    fprintf(arqout, "\n</svg>");
    
    fclose(arqout);
}

void criaLinha(float x1, float y1, float x2, float y2, char cor[], char svg[]){
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo de saida");
        exit(1);
	}

	fprintf(arq, "\n\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:%s\" />", x1, y1, x2, y2, cor);

    fclose(arq);
}

void criaCirculo(float raio, float x, float y, char cor1[], char cor2[], char svg[]){
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo de saida");
        exit(1);
	}
	
	fprintf(arq, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />", x, y, raio, cor1, cor2);
	
    fclose(arq);
}

void criaRetangulo(float largura, float altura, float x, float y, char cor1[], char cor2[], char svg[]){
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo de saida");
        exit(1);
	}
	
	fprintf(arq, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke:%s\" />", x, y, largura, altura, cor2, cor1);
	
    fclose(arq);
}

void escreveDistancia(float x1, float y1, float x2, float y2, float distancia, char svg[]){
    FILE *arq;
    
    arq = fopen(svg, "a");

    if(x1>=x2 && y1>=y2){
        fprintf(arq, "\n\t<text x=\"%f\" y=\"%f\" fill=\"black\">%f</text>", x2+((x1-x2)/2), y2+((y1-y2)/2), distancia);    
    } else if(x1<=x2 && y1>=y2) {
        fprintf(arq, "\n\t<text x=\"%f\" y=\"%f\" fill=\"black\">%f</text>", x1+((x2-x1)/2), y2+((y1-y2)/2), distancia);
    } else if(x1>=x2 && y1<=y2){
        fprintf(arq, "\n\t<text x=\"%f\" y=\"%f\" fill=\"black\">%f</text>", x2+((x1-x2)/2), y1+((y2-y1)/2), distancia);
    } else if(x1<=x2 && y1<=y2) {
        fprintf(arq, "\n\t<text x=\"%f\" y=\"%f\" fill=\"black\">%f</text>", x1+((x2-x1)/2), y1+((y2-y1)/2), distancia);
    }

    fclose(arq);
}

void escreveSvg(float x, float y, char texto[], char svg[]){
    FILE *arq;
    
    arq = fopen(svg, "a+");
    fprintf(arq, "\n\t<text x=\"%f\" y=\"%f\" fill=\"black\">%s</text>", x, y, texto);
    fclose(arq);
}
