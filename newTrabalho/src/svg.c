#include "svg.h"
#include <stdio.h>
#include <stdlib.h>

void iniciaSvg(char nomeDoArquivoSvg[])
{
    FILE *arquivoSvg;
    
    arquivoSvg = fopen(nomeDoArquivoSvg, "w");
    if (arquivoSvg == NULL){ 
        printf("Nao foi possivel abrir o arquivo svg!\n");
        exit(1);
    }
    
    fprintf(arquivoSvg, "<svg>");
    
    fclose(arquivoSvg);
}

void imprimirCirculo(double raio, double x, double y, char corB[], char corP[], char nomeDoArquivoSvg[], double espessura){
    FILE *arq;
    
    arq = fopen(nomeDoArquivoSvg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo de saida");
        exit(1);
	}
	
	fprintf(arq, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%f\" fill-oppacity=\"0.5\" stroke-oppacity=\"0.7\" />", x, y, raio, corB, corP, espessura);
	
    fclose(arq);
}


void imprimirRetangulo(double largura, double altura, double x, double y, char corB[], char corP[], char svg[], double espessura)
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo de saida");
        exit(1);
	}
	
	fprintf(arq, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke:%s;stroke-width:%f;fill-oppacity:0.5;stroke-oppacity:0.7\" />", x, y, largura, altura, corP, corB, espessura);
	
    fclose(arq);
}

void escreverNoSvg(float x, float y, char texto[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a+");
    fprintf(arq, "\n\t<text x=\"%f\" y=\"%f\" fill=\"black\">%s</text>", x, y, texto);
    fclose(arq);
}

void imprimirElipse(char svg[], double cx, double cy, double rx, double ry, char corP[], char corB[], double espessura)
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo de saida");
        exit(1);
	}

    fprintf(arq, "\n\t<ellipse cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" style=\"fill:%s;stroke:%s;stroke-width:%f;fill-oppacity:0.5;stroke-oppacity:0.7\" />", cx, cy, rx, ry, corP, corB, espessura);

    fclose(arq);
}

