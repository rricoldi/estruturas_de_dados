#include "svg.h"
#include <stdio.h>
#include <stdlib.h>

void iniciaSvg(char nomeDoArquivoSvg[])
{
    FILE *arquivoSvg;
    
    arquivoSvg = fopen(nomeDoArquivoSvg, "w+");
    if (arquivoSvg == NULL){ 
        printf("Nao foi possivel abrir o arquivo svg!\n");
        exit(1);
    }
    
    fprintf(arquivoSvg, "<svg viewBox=\"0 0 0 0\"  xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns=\"http://www.w3.org/2000/svg\">");
    
    fclose(arquivoSvg);
}

void finalizaSvg(char arq[])
{
	FILE* arqout;
	
    arqout = fopen(arq, "a");
     if (arqout == NULL){
        printf("Nao foi possivel Abrir o arquivo geo");
        exit(1);
    }
    
    fprintf(arqout, "\n</svg>");
    
    fclose(arqout);
}

void imprimirCirculo(double raio, double x, double y, char corB[], char corP[], char nomeDoArquivoSvg[], double espessura){
    FILE *arq;
    
    arq = fopen(nomeDoArquivoSvg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo de saida");
        exit(1);
	}
	
	fprintf(arq, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%lf\" fill-oppacity=\"0.5\" stroke-oppacity=\"0.7\" />", x, y, raio, corB, corP, espessura);
	
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
	
	fprintf(arq, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:%s;stroke:%s;stroke-width:%lf;fill-oppacity:0.5;stroke-oppacity:0.7\" />", x, y, largura, altura, corP, corB, espessura);
	
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

    fprintf(arq, "\n\t<ellipse cx=\"%lf\" cy=\"%lf\" rx=\"%lf\" ry=\"%lf\" style=\"fill:%s;stroke:%s;stroke-width:%lf;fill-oppacity:0.5;stroke-oppacity:0.7\" />", cx, cy, rx, ry, corP, corB, espessura);

    fclose(arq);
}

void imprimirPredio(char svg[], double x, double y, double tamanhoDaFrente, double tamanhoDoLado, double xCalcada, double yCalcada, double xCalcadaMax, double yCalcadaMax, double numeroDoPredio, double xNum, double yNum)
{
    FILE *arq;

    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo de saida");
        exit(1);
	}

    fprintf(arq, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:grey;stroke:black;fill-oppacity:0.5;stroke-oppacity:0.7\" />", x, y, tamanhoDaFrente, tamanhoDoLado);
    fprintf(arq, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:red;stroke:black;fill-oppacity:0.9;stroke-oppacity:0.7\" />", xCalcada, yCalcada, xCalcadaMax, yCalcadaMax);
    fprintf(arq, "\n\t<text x=\"%f\" y=\"%f\" fill=\"black\" font-size=\"8\">%.0lf</text>", xNum, yNum, numeroDoPredio);

    fclose(arq);
}

void imprimirLinha(float x1, float y1, float x2, float y2, char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo de saida");
        exit(1);
	}

	fprintf(arq, "\n\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:black\" />", x1, y1, x2, y2);

    fclose(arq);
}

void imprimirLinha2(float x1, float y1, float x2, float y2, char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo de saida");
        exit(1);
	}

	fprintf(arq, "\n\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke-width:3;stroke:green;stroke-oppacity:0.1\" />", x1, y1, x2, y2);

    fclose(arq);
}

void escreverDistancia(float x1, float y1, float x2, float y2, float distancia, char svg[])
{
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

void imprimirIncendio(double x, double y, char nomeDoArquivoSvg[])
{
    FILE *arq;
    arq = fopen(nomeDoArquivoSvg, "a");

    fprintf(arq, "\n\t<polygon points=\"%lf,%lf %lf,%lf %lf,%lf\" style=\"fill:red;stroke:yellow;stroke-width:1\" />", x, y, x+10, y, x+5, y-10);

    fclose(arq);
}