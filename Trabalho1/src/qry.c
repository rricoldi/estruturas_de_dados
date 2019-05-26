#include "leitura.h"
#include "svg.h"
#include "struct.h"
#include <stdio.h>
#include <math.h>
#include "lista.h"

float max(float n1, float n2){
    if(n1 > n2)
        return n1;
    else
        return n2;
}

float min(float n1, float n2){
    if(n1 < n2)
        return n1;
    else
        return n2;
}

int interno(float px, float py, float rx, float ry, float h, float w){
    if(px>=rx && px<=(rx+w) && py>=ry &&py<=ry+h)
        return 1;
    else 
        return 0;
    
}

float distancia (float x1, float y1, float x2, float y2){
    float dx = x2 - x1;
    float dy = y2 - y1;

    return sqrt((dx * dx) + (dy * dy));
}

void distanciaFig(float x1, float y1, float x2, float y2, char txt[], char svg[], int j, int k){
    FILE *arq;

    arq = fopen(txt, "a");

    float dist = distancia(x1, y1, x2, y2);

    fprintf(arq, "d? %d %d\n%f\n", j, k, dist);

    criaLinha(x1, y1, x2, y2, "black", svg);

    escreveDistancia(x1, y1, x2, y2, dist, svg);

    fclose(arq);
}

void colisaoRR(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2, int j, int k, char txt[], char svg[]){
    FILE *arq;
    FILE *arqsvg;

    arq = fopen(txt, "a");
    arqsvg = fopen(svg, "a");
    
    float x = min(x1,x2);
    float y = min(y1,y2);
    float w = max(x1+w1, x2+w2) - min(x1, x2);
    float h = max(y1+h1, y2+h2) - min(y1, y2);

    if(x1<x2+w2 && x1+w1>x2 && y1<y2+h2 && y1+h1>y2){
        fprintf(arq, "o? %d %d\nSIM\n", j, k);
        fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,w,h);
    }else{
        fprintf(arq, "o? %d %d\nNAO\n", j, k);
        fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,w,h);
    }
    fclose(arqsvg);
    fclose(arq);
}

void colisaoCR(float cx, float cy, float r, float rx, float ry, float w, float h, int j, int k, char txt[], char svg[]){
    FILE *arq;
    FILE *arqsvg;

    arq = fopen(txt, "a");
    arqsvg = fopen(svg, "a");

    float x = min(rx,cx-r);
    float y = min(ry, cy-r);
    float wc = max(rx+w,cx+r)-min(rx,cx-r);
    float hc = max(ry+h,cy+r)-min(ry,cy-r);

    if(cx >= rx && cx <= rx + w && cy >= ry - r && cy <= ry + h + r){
        fprintf(arq, "o? %d %d\nSIM\n", j, k);
        fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,wc,hc);
    } else if(cy >= ry && cy <= ry + h && cx >= rx - r && cx <= rx + w + r) {
        fprintf(arq, "o? %d %d\nSIM\n", j, k);
        fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,wc,hc);
    } else if(cx >= rx - r && cx < rx && cy >= ry - r && cy < ry) {
        if(distancia(cx,cy,rx,ry) <= r){
            fprintf(arq, "o? %d %d\nSIM\n", j, k);
            fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,wc,hc);
        } else {
            fprintf(arq, "o? %d %d\nNAO\n", j, k);
            fprintf(arqsvg,"<\n\trect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,wc,hc);
        }
    } else if(cx >= rx - r && cx < rx && cy > ry + h && cy <= ry + h + r) {
        if(distancia(cx,cy,rx,ry+h) <= r){
            fprintf(arq, "o? %d %d\nSIM\n", j, k);
            fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,wc,hc);
        } else {
            fprintf(arq, "o? %d %d\nNAO\n", j, k);
            fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,wc,hc);
        }
    } else if(cx > rx + w && cx <= rx + w + r && cy >= ry - r && cy < ry) {
        if(distancia(cx,cy,rx+w,ry) <= r){
            fprintf(arq, "o? %d %d\nSIM\n", j, k);
            fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,wc,hc);
        } else {
            fprintf(arq, "o? %d %d\nNAO\n", j, k);
            fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,wc,hc);
        }
    } else if(cx > rx + w && cx <= rx + w + r && cy > ry + h && cy <= ry + h + r) {                             
        if(distancia(cx,cy,rx+w,ry+h) <= r){
            fprintf(arq, "o? %d %d\nSIM\n", j, k);
            fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,wc,hc);
        } else {
            fprintf(arq, "o? %d %d\nNAO\n", j, k);
            fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,wc,hc);
        }
    } else {
            fprintf(arq, "o? %d %d\nNAO\n", j, k);
            fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,w,h);
    }

    fclose(arq);
    fclose(arqsvg);
}

void colisaoCC(int x1, int y1, float r1, int x2, int y2, float r2, int j, int k, char txt[], char svg[]){
    FILE *arq;
    FILE *arqsvg;

    arq = fopen(txt, "a");
    arqsvg = fopen(svg, "a");

    float x = min(x1,x2)-max(r1,r2);
    float y = min(y1,y2)-max(r1,r2);
    float w = max(x1,x2) - min(x1,x2) + r1 + r2;
    float h = max(y1,y2) - min(y1,y2) + r1 + r2;
   
    if(distancia(x1,y1,x2,y2) <= r1+r2){
        fprintf(arq, "o? %d %d\nSIM\n", j, k);
        fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,w,h);
    } else {
        fprintf(arq, "o? %d %d\nNAO\n", j, k);
        fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,w,h);
    }

    fclose(arq);
    fclose(arqsvg);
}

void boundingBox(char cor[], char arquivo[], char sufixo[], No *inicio){
    FILE *arq;

    char *arqout = (char*) (malloc((strlen(arquivo) + strlen(sufixo)+7)*sizeof(char)));

    sprintf(arqout,"%s-%s.svg", arquivo, sufixo);

	iniciaSvg(arqout);

    arq = fopen(arqout, "a");
    if (arq == NULL){
       printf("Erro ao abrir o arquivo de saida");
       exit(1);
    }

    No *lista;
    lista = inicio;

    par *par;

    while(lista != NULL){
    	par = lista->par;
    	if (par->type == 'c'){
    	    fprintf(arq, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />", par->x, par->y, par->raio, par->cor1, par->cor2);
    	    fprintf(arq, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke:%s\" />", par->x-par->raio, par->y-par->raio, par->raio*2, par->raio*2, cor, cor);
    	}
    	else if (par->type == 'r'){
    	    fprintf(arq, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke:%s\" />", par->x, par->y, par->largura, par->altura, par->cor2, par->cor1);
    	    fprintf(arq, "\n\t<ellipse cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" style=\"fill:%s;stroke:%s\" />", par->x+(par->largura/2), par->y+(par->altura/2), par->largura/2, par->altura/2, cor, cor);
    	}

	    lista = lista->prox;
    }    

    fclose(arq);

    finalizaSvg(arqout);
}

void pontoInternoCirculo(float px, float py, float cx, float cy, float r, char arquivo[], int j, char svg[]) {
    FILE *arq;

    arq = fopen(arquivo, "a");
    if (arq == NULL){
    	printf("nao foi possivel abrir o arquivo txt\n");
		exit(1);
	}

    float d = distancia(px, py, cx, cy);

    if (r > d) {
         fprintf(arq, "i? %d %f %f\nINTERNO\n", j, px, py);
         criaCirculo(2, px, py, "black", "green", svg);
    }else {
         fprintf(arq, "i? %d %f %f\nNAO INTERNO\n", j, px, py);
         criaCirculo(2, px, py, "black", "red", svg);
    }

    criaLinha(px, py, cx, cy, "black", svg);
    
    fclose(arq);
}

void pontoInternoQuadrado(float px, float py, float rx, float ry, float h, float w, char arquivo[], int j, char svg[]){
    FILE *arq;
    
    arq = fopen(arquivo, "a+");
	
    if (arq == NULL){
		printf("nao foi possivel abrir o arquivo txt\n");
		exit(1);
	 }

    if(px>rx && px<(rx+w) && py>ry &&py<ry+h){
        fprintf(arq, "i? %d %f %f\nINTERNO\n", j, px, py);
        criaCirculo(1, px, py, "black", "green", svg);
    }else {
        fprintf(arq, "i? %d %f %f\nNAO INTERNO\n", j, px, py);
        criaCirculo(1, px, py, "black", "red", svg);
    }
    
    criaLinha(px, py, rx, ry, "black", svg);
    
    fclose(arq);
}
