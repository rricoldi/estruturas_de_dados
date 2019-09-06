#include "cidade.h"
#include "leitura.h"
#include "qry.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

double max(double n1, double n2)
{
    if(n1 > n2)
        return n1;
    else
        return n2;
}

double min(double n1, double n2)
{
    if(n1 < n2)
        return n1;
    else
        return n2;
}

void colisaoEntreCirculosERetangulos(float cx, float cy, float r, float rx, float ry, float w, float h, char j[], char k[], char txt[], char svg[])
{
    FILE *arq;
    FILE *arqsvg;

    arq = fopen(txt, "a");
    arqsvg = fopen(svg, "a");

    float x = min(rx,cx-r);
    float y = min(ry, cy-r);
    float wc = max(rx+w,cx+r)-min(rx,cx-r);
    float hc = max(ry+h,cy+r)-min(ry,cy-r);

    if(retornaDistanciaL2(r, cx, cy, rx, ry, w, h))
    {
        fprintf(arq, "o? %s %s\nSIM\n", j, k);
        fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,wc,hc);
    }
    else
    {
        fprintf(arq, "o? %s %s\nNAO\n", j, k);
        fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,wc,hc);
    }

    fclose(arq);
    fclose(arqsvg);
}

bool retornaDistanciaL2(double r, double fx, double fy, double x, double y, double w, double h)
{
    double d1 = sqrt(pow(fabs(fx-(x+w)),2) + pow(fabs(fy-y),2));
    double d2 = sqrt(pow(fabs(fx-(x+w)),2) + pow(fabs(fy-(y+h)),2));
    double d3 = sqrt(pow(fabs(fx-x),2) + pow(fabs(fy-y),2));
    double d4 = sqrt(pow(fabs(fx-x),2) + pow(fabs(fy-(y+h)),2));
    
    if(d1 <= r)
    {
        if(d2 <= r)
        {
            if(d3 <= r)
            {
                if(d4 <= r)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void colisaoEntreCirculos(int x1, int y1, float r1, int x2, int y2, float r2, char j[], char k[], char txt[], char svg[])
{
    FILE *arq;
    FILE *arqsvg;

    arq = fopen(txt, "a");
    arqsvg = fopen(svg, "a");

    float x = min(x1,x2)-max(r1,r2);
    float y = min(y1,y2)-max(r1,r2);
    float w = max(x1,x2) - min(x1,x2) + r1 + r2;
    float h = max(y1,y2) - min(y1,y2) + r1 + r2;
   
    if(distancia(x1,y1,x2,y2) <= r1+r2){
        fprintf(arq, "o? %s %s\nSIM\n", j, k);
        fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,w,h);
    } else {
        fprintf(arq, "o? %s %s\nNAO\n", j, k);
        fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,w,h);
    }

    fclose(arq);
    fclose(arqsvg);
}

double distancia (double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;

    return sqrt((dx * dx) + (dy * dy));
}

void colisaoEntreRetangulos(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2, char j[], char k[], char txt[], char svg[])
{
    FILE *arq;
    arq = fopen(txt, "a");
    FILE *arqsvg;
    arqsvg = fopen(svg, "a");
    
    float x = min(x1,x2);
    float y = min(y1,y2);
    float w = max(x1+w1, x2+w2) - min(x1, x2);
    float h = max(y1+h1, y2+h2) - min(y1, y2);

    if(VerificaColisao(x1, y1, w1, h1, x2, y2, w2, h2)){
        fprintf(arq, "o? %s %s\nSIM\n", j, k);
        fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black;stroke-width:2\" />",x,y,w,h);
    }else{
        fprintf(arq, "o? %s %s\nNAO\n", j, k);
        fprintf(arqsvg,"\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill=:none;stroke:black;stroke-dasharray:5;stroke-width:2\" />",x,y,w,h);
    }
    fclose(arqsvg);
    fclose(arq);
}

bool VerificaColisao(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
    if(x1<x2+w2 && x1+w1>x2 && y1<y2+h2 && y1+h1>y2)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

bool pontoInternoCirculo(float px, float py, float cx, float cy, float r)
{
    float d = distancia(px, py, cx, cy);

    if (d <= r)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool pontoInternoRetangulo(float px, float py, float rx, float ry, float h, float w)
{

    if(px>rx && px<(rx+w) && py>ry &&py<ry+h)
    {
        return true;
    }
    else
    {
        return false;
    }
}

double distanciaDaFigura(double x1, double y1, double x2, double y2, char svg[])
{
    double dist = distancia(x1, y1, x2, y2);
    imprimirLinha(x1, y1, x2, y2, svg);

    escreverDistancia(x1, y1, x2, y2, dist, svg);

    return dist;
}