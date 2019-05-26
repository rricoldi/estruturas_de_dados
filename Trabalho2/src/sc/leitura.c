#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"


#define padrao 1

Cidade leiaGeo(char arq[], char svg[])
{
    FILE *geo;
	printf("%s\n", arq);
    geo = fopen(arq, "r");

    if (geo == NULL){ //caso nao abra o arquivo: ERRO!
        printf("Nao foi possivel Abrir o arquivo geo\n");
        exit(1);
    }
	printf("Arquivo Geo foi aberto\n");
	
    int nx = 1000, nq = 1000, nh = 1000, ns = 1000, nr = 1000;
    int nxi = 0, nqi = 0, nhi = 0, nsi = 0, nri = 0;
	char comando[3];
    char *texto;
	double x, y, altura, largura, raio;
	double espessuraC = 1;
	double espessuraRe = 1;
	char corP[20] = "white";
	char corB[20] = "black";
	double espessuraQ = 1;
	char corQP[20] = "orange";
	char corQB[20] = "blue";
	double espessuraH = 1;
	char corHP[20] = "red";
	char corHB[20] = "black";
	double espessuraS = 1;
	char corSP[20] = "yellow";
	char corSB[20] = "green";
	double espessuraR = 1;
	char corRP[20] = "purple";
	char corRB[20] = "pink";
	char id[20];
    size_t bufsize = 32;
    Info info;

    iniciaSvg(svg);
	printf("svg inicializado\n");

	fscanf(geo,"%s", comando);
	if (strcmp("nx",comando)==0) //proximo argumento deve ser numero maximo de figuras, quadras, hidrantes, semaforos e radio-bases
	{ 
		fscanf(geo,"%d %d %d %d %d", &nx, &nq, &nh, &ns, &nr);
    }

	Cidade cidade = criaCidade(nx, nq, nh, nr, ns);
	
    while(1){	
		
		if (feof(geo))
	        break;
        else if (strcmp("c",comando)==0){ //proximo argumento deve ser os parametros 
			printf("circulo\n");         
			if(nxi<nx){
				fscanf(geo,"%s %lf %lf %lf %s %s", &id, &raio, &x, &y, &corB, &corP);
				Info info = criaCirculo(id, corB, corP, raio, x, y, espessuraC);
				addCirculo(cidade, info);
				
				printaCirculo(raio, x, y, corB, corP, svg, espessuraC);
				nxi++;
			}
        }
        else if (strcmp("r",comando)==0){ //proximo argumento deve ser os parametros
			printf("retangulo\n");
            if(nxi<nx){
				fscanf(geo,"%s %lf %lf %lf %lf %s %s", &id, &largura, &altura, &x, &y, &corB, &corP);
				Info info = criaRetangulo(id, corB, corP, largura, altura, x, y, espessuraRe);
				addRetangulo(cidade, info);
            	
            	
				printaRetangulo(largura, altura, x, y, corB, corP, svg, espessuraRe);
            	nxi++;
			}
        }
        else if (strcmp("t",comando)==0){ //proximo argumento deve ser os par?metros
            fscanf(geo,"%lf %lf", &x, &y);
	
	    	texto = (char *)malloc(bufsize * sizeof(char));

            getline(&texto, &bufsize, geo);
	    	escreveSvg(x, y, strtok(texto,"\n"), svg);
			free(texto);
		}
		else if (strcmp("q",comando)==0)
		{
			printf("quadra\n");
            if(nqi < nq)
			{
				fscanf(geo,"%s %lf %lf %lf %lf", &id, &x, &y, &largura, &altura);
				printf("%s, %lf, %lf, %lf ,%lf\n", id, x, y, largura, altura);
				info = criaQuadra(id, corQB, corQP, largura, altura, x, y, espessuraQ);
				addQuadra(cidade, info);

				printaRetangulo(largura, altura, x, y, corQB, corQP, svg, espessuraQ);
			}
		}
		else if (strcmp("h",comando)==0)
		{
			printf("hidrante\n");
            if(nhi < nh)
			{
				fscanf(geo,"%s %lf %lf", &id, &x, &y);
				info = criaHidrante(id, corHB, corHP, espessuraH, x, y);
				addHidrante(cidade, info);

				printaCirculo(2, x, y, corHB, corHP, svg, espessuraH);
			}
		}
		else if (strcmp("s",comando)==0)
		{
			printf("semaforo\n");
            if(nsi<ns)
			{
				fscanf(geo,"%s %lf %lf", &id, &x, &y);
				info = criaSemaforo(id, corSB, corSP, x, y, espessuraS);
				addQuadra(cidade, info);

				printaRetangulo(7, 18, x, y, corSB, corSP, svg, espessuraS);
			}
		}
		else if (strcmp("rb",comando)==0)
		{
			printf("radio\n");
            if(nri<nr)
			{
				fscanf(geo,"%s %lf %lf", &id, &x, &y);
				info = criaRadio(id, corRB, corRP, x, y, espessuraR);
				addRadio(cidade, info);

				criaElipse(svg, x, y, 5, 15, corRP, corRB, espessuraR);
			}
		}
		else if (strcmp("sw",comando)==0)
		{
			printf("sw\n");
			fscanf(geo,"%lf %lf", &espessuraC, &espessuraRe);	
		}
		else if (strcmp("cq",comando)==0)
		{
			printf("cq\n");
			fscanf(geo,"%s %s %lf", &corQP, &corQB, espessuraQ);	
		}
		else if (strcmp("ch",comando)==0)
		{
			printf("ch\n");
			fscanf(geo,"%s %s %lf", &corHP, &corHB, espessuraH);	
		}
		else if (strcmp("cr",comando)==0)
		{
			printf("cr\n");
			fscanf(geo,"%s %s %lf", &corRP, &corRB, espessuraR);	
		}
		else if (strcmp("cs",comando)==0)
		{
			printf("cs\n");
			fscanf(geo,"%s %s %lf", &corSP, &corSB, espessuraS);	
		}
		fscanf(geo,"%s", comando);
    }
	
	finalizaSvg(svg);
	printf("svg finalizado\n");

    fclose(geo);
	printf("Arquivo Geo foi fechado\n");

	return cidade;
}
