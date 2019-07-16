#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "leitura.h"
#include "txt.h"
#include "qry.h"
#include "svg.h"

#define padrao 1

Cidade leiaGeo(char arq[], char svg[])
{
	FILE *geo;
	printf("%s\n", arq);
	geo = fopen(arq, "r");

	if (geo == NULL)
	{ //caso nao abra o arquivo: ERRO!
		printf("Nao foi possivel Abrir o arquivo geo\n");
		exit(1);
	}

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

	fscanf(geo, "%s", comando);
	if (strcmp("nx", comando) == 0) //proximo argumento deve ser numero maximo de figuras, quadras, hidrantes, semaforos e radio-bases
	{
		fscanf(geo, "%d %d %d %d %d", &nx, &nq, &nh, &ns, &nr);
	}

	Cidade cidade = criaCidade(nx, nq, nh, nr, ns);

	while (1)
	{

		if (feof(geo))
			break;
		else if (strcmp("c", comando) == 0)
		{ //proximo argumento deve ser os parametros
			fscanf(geo, "%s %lf %lf %lf %s %s", id, &raio, &x, &y, corB, corP);
			if (nxi < nx)
			{
				Info info = criaCirculo(id, corB, corP, raio, x, y, espessuraC);
				addCirculo(cidade, info);

				printaCirculo(raio, x, y, corB, corP, svg, espessuraC);
				nxi++;
			}
		}
		else if (strcmp("r", comando) == 0)
		{ //proximo argumento deve ser os parametros
			fscanf(geo, "%s %lf %lf %lf %lf %s %s", id, &largura, &altura, &x, &y, corB, corP);
			if (nxi < nx)
			{
				Info info = criaRetangulo(id, corB, corP, largura, altura, x, y, espessuraRe);
				addRetangulo(cidade, info);

				printaRetangulo(largura, altura, x, y, corB, corP, svg, espessuraRe);
				nxi++;
			}
		}
		else if (strcmp("t", comando) == 0)
		{ //proximo argumento deve ser os par?metros
			fscanf(geo, "%lf %lf", &x, &y);

			texto = (char *)malloc(bufsize * sizeof(char));

			getline(&texto, &bufsize, geo);
			escreveSvg(x, y, strtok(texto, "\n"), svg);
			free(texto);
		}
		else if (strcmp("q", comando) == 0)
		{
			fscanf(geo, "%s %lf %lf %lf %lf", id, &x, &y, &largura, &altura);
			if (nqi < nq)
			{
				//printf("%s, %lf, %lf, %lf ,%lf, %d\n", id, x, y, largura, altura, nqi);
				info = criaQuadra(id, corQB, corQP, largura, altura, x, y, espessuraQ);
				addQuadra(cidade, info);

				printaRetangulo(largura, altura, x, y, corQB, corQP, svg, espessuraQ);
				nqi++;
			}
		}
		else if (strcmp("h", comando) == 0)
		{
			fscanf(geo, "%s %lf %lf", id, &x, &y);
			if (nhi < nh)
			{
				info = criaHidrante(id, corHB, corHP, espessuraH, x, y);
				addHidrante(cidade, info);

				printaCirculo(2, x, y, corHB, corHP, svg, espessuraH);
				nhi++;
			}
		}
		else if (strcmp("s", comando) == 0)
		{
			fscanf(geo, "%s %lf %lf", id, &x, &y);
			if (nsi < ns)
			{
				info = criaSemaforo(id, corSB, corSP, x, y, espessuraS);
				addSemaforo(cidade, info);

				printaRetangulo(7, 18, x, y, corSB, corSP, svg, espessuraS);
				nsi++;
			}
		}
		else if (strcmp("rb", comando) == 0)
		{
			if (nri < nr)
			{
				fscanf(geo, "%s %lf %lf", id, &x, &y);
				info = criaRadio(id, corRB, corRP, x, y, espessuraR);
				addRadio(cidade, info);

				criaElipse(svg, x, y, 5, 15, corRP, corRB, espessuraR);
				nri++;
			}
		}
		else if (strcmp("sw", comando) == 0)
		{
			fscanf(geo, "%lf %lf", &espessuraC, &espessuraRe);
		}
		else if (strcmp("cq", comando) == 0)
		{
			fscanf(geo, "%s %s %lf", corQP, corQB, &espessuraQ);
		}
		else if (strcmp("ch", comando) == 0)
		{
			fscanf(geo, "%s %s %lf", corHP, corHB, &espessuraH);
		}
		else if (strcmp("cr", comando) == 0)
		{
			fscanf(geo, "%s %s %lf", corRP, corRB, &espessuraR);
		}
		else if (strcmp("cs", comando) == 0)
		{
			fscanf(geo, "%s %s %lf", corSP, corSB, &espessuraS);
		}
		fscanf(geo, "%s", comando);
	}

	finalizaSvg(svg);

	fclose(geo);

	return cidade;
}

void leiaQry(char prefixoArq[], char arq[], Cidade cidade)
{
	FILE *qry;
	qry = fopen(arq, "r");

	if (qry == NULL)
	{
		printf("erro ao tentar abrir o arquivo qry!\n");
		exit(1);
	}

	double x, y, distancia, largura, altura, dx, dy;
	char id1[20], id2[20];
	char L[3];
	char comando[5];
	char sufixo[30];
	char cor[30];
	Info info1 = 0, info2 = 0;
	int tipo1, tipo2, verificador = 0;

	char *svg = (char *)malloc((strlen(prefixoArq) + 5) * sizeof(char));
	sprintf(svg, "%s.svg", prefixoArq);

	iniciaSvg(svg);

	printaCirculoseRetangulos(cidade, svg);

	char *txt = (char *)malloc((strlen(prefixoArq) + 5) * sizeof(char));
	sprintf(txt, "%s.txt", prefixoArq);

	FILE *arqTxt;

	arqTxt = fopen(txt, "w");
	if (arqTxt == NULL)
	{
		printf("nao foi possivel abrir o arquivo txt\n");
		exit(1);
	}

	while (1)
	{
		fscanf(qry, "%s", comando);

		if (feof(qry))
			break;

		if (strcmp("o?", comando) == 0)
		{ //proximo argumento deve ser n?mero m?ximo de c?rculos e ret?ngulos
			fscanf(qry, "%s %s", &id1, &id2);

			info1 = procuraCidade(cidade, id1, &tipo1);
			info2 = procuraCidade(cidade, id2, &tipo2);
			fclose(arqTxt);

			if (tipo1 == 1 && tipo2 == 2)
			{
				colisaoCR(retornaCX(info1), retornaCY(info1), retornaCR(info1), retornaReX(info2), retornaReY(info2), retornaReW(info2), retornaReH(info2), id1, id2, txt, svg);
			}
			else if (tipo1 == 2 && tipo2 == 1)
			{
				colisaoCR(retornaCX(info2), retornaCY(info2), retornaCR(info2), retornaReX(info1), retornaReY(info1), retornaReW(info1), retornaReH(info1), id1, id2, txt, svg);
			}
			else if (tipo1 == 1 && tipo2 == 1)
			{
				colisaoCC(retornaCX(info1), retornaCY(info1), retornaCR(info1), retornaCX(info2), retornaCY(info2), retornaCR(info2), id1, id2, txt, svg);
			}
			else if (tipo1 == 2 && tipo2 == 2)
			{
				colisaoRR(retornaReX(info1), retornaReY(info1), retornaReW(info1), retornaReH(info1), retornaReX(info2), retornaReY(info2), retornaReW(info2), retornaReH(info2), id1, id2, txt, svg);
			}
			arqTxt = fopen(txt, "a");
		}
		else if (strcmp("i?", comando) == 0)
		{ //proximo argumento deve ser os par?metros
			fscanf(qry, "%s %lf %lf", &id1, &x, &y);

			info1 = procuraCidade(cidade, id1, &tipo1);

			if (tipo1 == 1)
			{
				if (pontoInternoCirculo(x, y, retornaCX(info1), retornaCY(info1), retornaCR(info1)))
				{
					fprintf(arqTxt, "i? %s %lf %lf\nINTERNO\n", id1, x, y);
					printaCirculo(2, x, y, "black", "green", svg, 1);
				}
				else
				{
					fprintf(arqTxt, "i? %s %lf %lf\nNAO INTERNO\n", id1, x, y);
					printaCirculo(2, x, y, "black", "red", svg, 1);
				}
				criaLinha(x, y, retornaCX(info1), retornaCY(info1), "black", svg);
			}
			else if (tipo2 == 2)
			{
				if (pontoInternoRetangulo(x, y, retornaReX(info1), retornaReY(info1), retornaReW(info1), retornaReH(info1)))
				{
					fprintf(arqTxt, "i? %s %lf %lf\nINTERNO\n", id1, x, y);
					printaCirculo(2, x, y, "black", "green", svg, 1);
				}
				else
				{
					fprintf(arqTxt, "i? %s %lf %lf\nNAO INTERNO\n", id1, x, y);
					printaCirculo(2, x, y, "black", "red", svg, 1);
				}
				criaLinha(x, y, retornaReX(info1), retornaReY(info1), "black", svg);
			}
		}
		else if (strcmp("d?", comando) == 0)
		{ //proximo argumento deve ser os par?metros
			fscanf(qry, "%s %s", &id1, &id2);
			info1 = procuraCidade(cidade, id1, &tipo1);
			info2 = procuraCidade(cidade, id2, &tipo2);

			if(info1 == NULL || info2 == NULL)
				continue;	
			if (tipo1 == 1 && tipo2 == 2)
				distancia = distanciaFig(retornaCX(info1), retornaCY(info1), retornaReX(info2), retornaReY(info2), svg);
			else if (tipo1 == 2 && tipo2 == 1)
				distancia = distanciaFig(retornaCX(info2), retornaCY(info2), retornaReX(info1), retornaReY(info1), svg);
			else if (tipo1 == 1 && tipo2 == 1)
			{
				distancia = distanciaFig(retornaCX(info2), retornaCY(info2), retornaCX(info1), retornaCY(info1), svg);
			}
			else if (tipo1 == 2 && tipo2 == 2)
				distancia = distanciaFig(retornaReX(info2), retornaReY(info2), retornaReX(info1), retornaReY(info1), svg);

			fprintf(arqTxt, "d? %s %s\n%lf\n", id1, id2, distancia);
		}
		else if (strcmp("bb", comando) == 0)
		{ //proximo argumento deve ser os par?metros
			fscanf(qry, " %s %s", &sufixo, &cor);

			char *arqout = (char *)(malloc((strlen(prefixoArq) + strlen(sufixo) + 7) * sizeof(char)));
			sprintf(arqout, "%s-%s.svg", prefixoArq, sufixo);
			iniciaSvg(arqout);

			boudingBoxCirculos(cidade, arqout);
			boundingBoxRetangulos(cidade, arqout, cor);

			finalizaSvg(arqout);
		}
		else if (strcmp("dq", comando) == 0)
		{
			fscanf(qry, "%s %s %lf", L, id1, &distancia);
			info1 = procuraCidade(cidade, id1, &tipo1);
			verificador++;

			fclose(arqTxt);

			if (tipo1 == 4)
			{
				percorreCidadeLQ(cidade, distancia, retornaHX(info1), retornaHY(info1), L, svg, txt, id1, 1, "", 0, 0, 0, 0);
			}
			else if (tipo1 == 5)
			{
				percorreCidadeLQ(cidade, distancia, retornaSX(info1), retornaSY(info1), L, svg, txt, id1, 1, "", 0, 0, 0, 0);
			}
			else if (tipo1 == 6)
			{
				percorreCidadeLQ(cidade, distancia, retornaRX(info1), retornaRY(info1), L, svg, txt, id1, 1, "", 0, 0, 0, 0);
			}
			arqTxt = fopen(txt, "a");
		}
		else if (strcmp("del", comando) == 0)
		{
			fscanf(qry, " %s", &id1);
			verificador++;

			fclose(arqTxt);

			removeDaCidade(cidade, id1, txt);

			arqTxt = fopen(txt, "a");
		}
		else if (strcmp("cbq", comando) == 0)
		{
			fscanf(qry, "%lf %lf %lf %s", &x, &y, &distancia, cor);
			verificador++;
			fprintf(arqTxt, "cbq %lf %lf %lf %s\n", x, y, distancia, cor);
			fclose(arqTxt);
			percorreCidadeLQ(cidade, distancia, x, y, "L2", svg, txt, "0", 2, cor, 0, 0, 0, 0);

			arqTxt = fopen(txt, "a");
		}
		else if (strcmp("crd?", comando) == 0)
		{
			fscanf(qry, " %s", id1);
			fprintf(arqTxt, "crd? %s\n", id1);
			info1 = procuraCidade(cidade, id1, &tipo1);
			if(info1 == NULL)
				continue;
			if (tipo1 == 3)
			{
				fprintf(arqTxt, "quadra -> cep: %s x: %lf y: %lf w: %lf h: %lf\n", id1, retornaQX(info1), retornaQY(info1), retornaQW(info1), retornaQH(info1));
			}
			else if (tipo1 == 4)
			{
				fprintf(arqTxt, "hidrante -> id: %s x: %lf y: %lf\n", id1, retornaHX(info1), retornaHY(info1));
			}
			else if (tipo1 == 5)
			{
				fprintf(arqTxt, "semaforo -> id: %s x: %lf y: %lf\n", id1, retornaSX(info1), retornaSY(info1));
			}
			else if (tipo1 == 6)
			{
				fprintf(arqTxt, "radio base -> id: %s x: %lf y: %lf\n", id1, retornaRX(info1), retornaRY(info1));
			}
		}
		else if (strcmp("trns", comando) == 0)
		{
			fscanf(qry, "%lf %lf %lf %lf %lf %lf", &x, &y, &largura, &altura, &dx, &dy);
			verificador++;
			fprintf(arqTxt, "trns %lf %lf %lf %lf %lf %lf\n", x, y, largura, altura, dx, dy);
			fclose(arqTxt);
			percorreCidadeLQ(cidade, distancia, x, y, "L2", svg, txt, "0", 3, cor, largura, altura, dx, dy);
			arqTxt = fopen(txt, "a");
		}
	}
	if(verificador != 0)
		printaCidade(cidade, svg);

	finalizaSvg(svg);
	fclose(arqTxt);
	free(txt);
	free(svg);

	fclose(qry);
}