#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "leitura.h"
#include "cidade.h"
#include "comercioPessoas.h"
#include "geometria.h"

Cidade leiaGeo(char nomeDoArquivoGeo[], char nomeDoArquivoSvg[])
{
	FILE *arquivoGeo;
	printf("%s\n", nomeDoArquivoGeo);
	printf("%s\n", nomeDoArquivoSvg);
	arquivoGeo = fopen(nomeDoArquivoGeo, "r");
	if (arquivoGeo == NULL)
	{
		printf("Nao foi possivel Abrir o arquivo Geo\n");
		exit(1);
	}

    int tipo                     = 0;
    int numeroDeFiguras          = 0;
    int numeroDeQuadras          = 0;
    int numeroDeHidrantes        = 0;
    int numeroDeSemaforos        = 0;
    int numeroDeRadioBases       = 0;
    int numeroDePredios          = 0;
    int numeroDeMuros            = 0;

    int numeroMaximoDeFiguras    = 1000;
    int numeroMaximoDeQuadras    = 1000;
    int numeroMaximoDeHidrantes  = 1000;
    int numeroMaximoDeSemaforos  = 1000;
    int numeroMaximoDeRadioBases = 1000;
    int numeroMaximoDePredios    = 1000;
    int numeroMaximoDeMuros      = 1000;

	double numeroDoPredio;
	double x, y, altura, largura, raio;
	double xCalcada, yCalcada, xCalcadaMax, yCalcadaMax;
	double xNum, yNum;
	double x1, x2, y1, y2;
	double tamanhoDaFrente;
	double tamanhoDoLado;
	double larguraDaCalcada;
    double espessuraDosCirculos   = 1;
    double espessuraDosRetangulos = 1;
    double espessuraDasQuadras    = 1;
    double espessuraDosHidrantes  = 1;
    double espessuraDosSemaforos  = 1;
    double espessuraDasRadioBases = 1;

	char *texto;
	char comando[3];
	char id[20];
	char face[6];
    char corDoPreenchimentoDaFigura[20]    = "white";
    char corDaBordaDaFigura[20]            = "black";
    char corDoPreenchimentoDaQuadra[20]    = "orange";
    char corDaBordaDaQuadra[20]            = "blue";
    char corDoPreenchimentoDoHidrante[20]  = "red";
    char corDaBordaDoHidrante[20]          = "black";
    char corDoPreenchimentoDoSemaforo[20]  = "yellow";
    char corDaBordaDoSemagoro[20]          = "green";
    char corDoPreenchimentoDaRadioBase[20] = "purple";
    char corDaBordaDaRadioBase[20]         = "pink";

	size_t bufsize = 32;
	Info info;

	iniciaSvg(nomeDoArquivoSvg);

	fscanf(arquivoGeo, "%s", comando);
	if (strcmp("nx", comando) == 0)
	{
		fscanf(arquivoGeo, "%d %d %d %d %d %d %d", &numeroMaximoDeFiguras, &numeroMaximoDeQuadras, &numeroMaximoDeHidrantes, &numeroMaximoDeSemaforos, &numeroMaximoDeRadioBases, &numeroMaximoDePredios, &numeroMaximoDeMuros);
	}
	Cidade cidade = criarCidade();
	while (1)
	{
		if (feof(arquivoGeo))
		{
			break;
		}
		else if (strcmp("c", comando) == 0)
		{
			fscanf(arquivoGeo, "%s %lf %lf %lf %s %s", id, &raio, &x, &y, corDaBordaDaFigura, corDoPreenchimentoDaFigura);
			if (numeroDeFiguras < numeroMaximoDeFiguras)
			{
				Info info = criarCirculo(id, corDaBordaDaFigura, corDoPreenchimentoDaFigura, raio, x, y, espessuraDosCirculos);
				adicionarCirculo(cidade, info);
				imprimirCirculo(raio, x, y, corDaBordaDaFigura, corDoPreenchimentoDaFigura, nomeDoArquivoSvg, espessuraDosCirculos);
				numeroDeFiguras++;
			}
		}
		else if (strcmp("r", comando) == 0)
		{
			fscanf(arquivoGeo, "%s %lf %lf %lf %lf %s %s", id, &largura, &altura, &x, &y, corDaBordaDaFigura, corDoPreenchimentoDaFigura);
			if (numeroDeFiguras < numeroMaximoDeFiguras)
			{
				Info info = criarRetangulo(id, corDaBordaDaFigura, corDoPreenchimentoDaFigura, largura, altura, x, y, espessuraDosRetangulos);
				adicionarRetangulo(cidade, info);

				imprimirRetangulo(largura, altura, x, y, corDaBordaDaFigura, corDoPreenchimentoDaFigura, nomeDoArquivoSvg, espessuraDosRetangulos);
				numeroDeFiguras++;
			}
		}
		else if (strcmp("t", comando) == 0)
		{
			fscanf(arquivoGeo, "%lf %lf", &x, &y);

			texto = (char *)malloc(bufsize * sizeof(char));

			getline(&texto, &bufsize, arquivoGeo);
			escreverNoSvg(x, y, strtok(texto, "\n"), nomeDoArquivoSvg);
			free(texto);
		}
		else if (strcmp("q", comando) == 0)
		{
			fscanf(arquivoGeo, "%s %lf %lf %lf %lf", id, &x, &y, &largura, &altura);
			if (numeroDeQuadras < numeroMaximoDeQuadras)
			{
				info = criarQuadra(id, corDaBordaDaQuadra, corDoPreenchimentoDaQuadra, largura, altura, x, y, espessuraDasQuadras);
				adicionarQuadra(cidade, info);

				imprimirRetangulo(largura, altura, x, y, corDaBordaDaQuadra, corDoPreenchimentoDaQuadra, nomeDoArquivoSvg, espessuraDasQuadras);
				numeroDeQuadras++;
			}
		}
		else if (strcmp("h", comando) == 0)
		{
			fscanf(arquivoGeo, "%s %lf %lf", id, &x, &y);
			if (numeroDeHidrantes < numeroMaximoDeHidrantes)
			{
				info = criarHidrante(id, corDaBordaDoHidrante, corDoPreenchimentoDoHidrante, espessuraDosHidrantes, x, y);
				adicionarHidrante(cidade, info);

				imprimirCirculo(2, x, y, corDaBordaDoHidrante, corDoPreenchimentoDoHidrante, nomeDoArquivoSvg, espessuraDosHidrantes);
				numeroDeHidrantes++;
			}
		}
		else if (strcmp("s", comando) == 0)
		{getQuadra(cidade, id);
			fscanf(arquivoGeo, "%s %lf %lf", id, &x, &y);
			if (numeroDeSemaforos < numeroMaximoDeSemaforos)
			{
				info = criarSemaforo(id, corDaBordaDoSemagoro, corDoPreenchimentoDoSemaforo, x, y, espessuraDosSemaforos);
				adicionarSemaforo(cidade, info);

				imprimirRetangulo(7, 18, x, y, corDaBordaDoSemagoro, corDoPreenchimentoDoSemaforo, nomeDoArquivoSvg, espessuraDosSemaforos);
				numeroDeSemaforos++;
			}
		}
		else if (strcmp("rb", comando) == 0)
		{
			fscanf(arquivoGeo, "%s %lf %lf", id, &x, &y);
			if (numeroDeRadioBases < numeroMaximoDeRadioBases)
			{
				info = criarRadioBase(id, corDaBordaDaRadioBase, corDoPreenchimentoDaRadioBase, x, y, espessuraDasRadioBases);
				adicionarRadioBase(cidade, info);

				imprimirElipse(nomeDoArquivoSvg, x, y, 5, 15, corDoPreenchimentoDaRadioBase, corDaBordaDaRadioBase, espessuraDasRadioBases);
				numeroDeRadioBases++;
			}
		}
		else if (strcmp("prd", comando) == 0)
		{
			fscanf(arquivoGeo, "%s %s %lf %lf %lf %lf", id, face, &numeroDoPredio, &tamanhoDaFrente, &tamanhoDoLado, &larguraDaCalcada);
			if (numeroDePredios < numeroMaximoDePredios)
			{
				
				Info quadra = getQuadra(cidade, id);
				if (quadra == NULL)
					continue;
				
				if (strcmp("N", face) == 0)
				{
					x = retornaQX(quadra) + numeroDoPredio - (tamanhoDaFrente / 2);
					y = retornaQY(quadra) + retornaQH(quadra) - tamanhoDoLado - larguraDaCalcada;
					xCalcada = retornaQX(quadra);
					xCalcadaMax = retornaQW(quadra);
					yCalcada = retornaQY(quadra) + retornaQH(quadra) - larguraDaCalcada;
					yCalcadaMax = larguraDaCalcada;
					xNum = retornaQX(quadra) + numeroDoPredio - (tamanhoDaFrente / 2);
					yNum = retornaQY(quadra) + (retornaQH(quadra) - 2) - larguraDaCalcada;
				}
				else if (strcmp("S", face) == 0)
				{
					x = retornaQX(quadra) + numeroDoPredio - (tamanhoDaFrente / 2);
					y = retornaQY(quadra) + larguraDaCalcada;
					xCalcada = retornaQX(quadra);
					xCalcadaMax = retornaQW(quadra);
					yCalcada = retornaQY(quadra);
					yCalcadaMax = larguraDaCalcada;
					xNum = retornaQX(quadra) + numeroDoPredio - (tamanhoDaFrente / 2);
					yNum = retornaQY(quadra) + 10 + larguraDaCalcada;
				}
				else if (strcmp("L", face) == 0)
				{
					x = retornaQX(quadra)  + larguraDaCalcada;
					y = retornaQY(quadra) + numeroDoPredio - (tamanhoDaFrente / 2);
					xCalcada = retornaQX(quadra);
					xCalcadaMax = larguraDaCalcada;
					yCalcada = retornaQY(quadra);
					yCalcadaMax = retornaQH(quadra);
					xNum = retornaQX(quadra) + larguraDaCalcada;
					yNum = retornaQY(quadra) + numeroDoPredio + 5;
				}
				else if (strcmp("O", face) == 0)
				{
					x = retornaQX(quadra) + retornaQW(quadra) - tamanhoDoLado - larguraDaCalcada;
					y = retornaQY(quadra) + numeroDoPredio - (tamanhoDaFrente / 2);
					xCalcada = retornaQX(quadra) + retornaQW(quadra) - larguraDaCalcada;
					xCalcadaMax = larguraDaCalcada;
					yCalcada = retornaQY(quadra);
					yCalcadaMax = retornaQH(quadra);
					xNum = retornaQX(quadra) + retornaQW(quadra) - 10 - larguraDaCalcada;
					yNum = retornaQY(quadra) + numeroDoPredio + 5;
				}
				info = criarPredio(id, face, numeroDoPredio, tamanhoDaFrente, tamanhoDoLado, larguraDaCalcada, x, y, xCalcada, xCalcadaMax, yCalcada, yCalcadaMax, xNum, yNum);
				adicionarPredio(cidade, info);

				imprimirPredio(nomeDoArquivoSvg, x, y, tamanhoDaFrente, tamanhoDoLado, xCalcada, yCalcada, xCalcadaMax, yCalcadaMax, numeroDoPredio, xNum, yNum);
				numeroDePredios++;
			}
		}
		else if (strcmp("mur", comando) == 0)
		{
			fscanf(arquivoGeo, "%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
			if (numeroDeMuros < numeroMaximoDeMuros)
			{
				info = criarMuro(x1, x2, y1, y2);
				adicionarMuro(cidade, info);
				imprimirLinha(x1, y1, x2, y2, nomeDoArquivoSvg);
				numeroDeMuros++;
			}
		}
		else if (strcmp("sw", comando) == 0)
		{
			fscanf(arquivoGeo, "%lf %lf", &espessuraDosCirculos, &espessuraDosRetangulos);
		}
		else if (strcmp("cq", comando) == 0)
		{
			fscanf(arquivoGeo, "%s %s %lf", corDoPreenchimentoDaQuadra, corDaBordaDaQuadra, &espessuraDasQuadras);
		}
		else if (strcmp("ch", comando) == 0)
		{
			fscanf(arquivoGeo, "%s %s %lf", corDoPreenchimentoDoHidrante, corDaBordaDoHidrante, &espessuraDosHidrantes);
		}
		else if (strcmp("cr", comando) == 0)
		{
			fscanf(arquivoGeo, "%s %s %lf", corDoPreenchimentoDaRadioBase, corDaBordaDaRadioBase, &espessuraDasRadioBases);
		}
		else if (strcmp("cs", comando) == 0)
		{
			fscanf(arquivoGeo, "%s %s %lf", corDoPreenchimentoDoSemaforo, corDaBordaDoSemagoro, &espessuraDosSemaforos);
		}
		fscanf(arquivoGeo, "%s", comando);
	}

	// imprimeCidade(cidade, nomeDoArquivoSvg);

	finalizaSvg(nomeDoArquivoSvg);

	fclose(arquivoGeo);

	return cidade;
}

void leiaQry(char caminhoDoArquivoDeEntrada[], char prefixoDoArquivoQry[], char nomeDoArquivoQry[], Cidade cidade, Graph grafo, char caminhoDoArquivoDeSaida[], char prefixoDoArquivoDeSaida[])
{
	int tipo1, tipo2;
	int verificador = 0;
	int verificador2 = 0;
	int numeroDeSemaforos = 0;
	int numeroDeHidrantes = 0;

	double x, y;
	double dx, dy;
	double distancia, largura, altura;
	double numeroDoPredio;

	char arvore;
	char id1[20], id2[20];
	char metrica[3];
	char comando[6];
	char sufixo[30];
	char cor[30];
	char cep[20];
	char face[6];

	//	Cria um arquivo temporário para quaisquer elementos que precisem
	//acima da cidade no Svg, isso se aplica aos comandos de incêncio,
	//ver quantidade de pessoas na quadra, procurar estabelecimentos, etc
	char nomeDoArquivoDeArvoreSvg[100];

	char* tempFileName = "tempFile.txt";
	FILE* tempFile = fopen(tempFileName, "w");
	fclose(tempFile);
	
	Info info1 = 0, info2 = 0;
	Ponto R[11] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

	FILE *arquivoQry;
	printf("%s\n", nomeDoArquivoQry);
	arquivoQry = fopen(nomeDoArquivoQry, "r");
	if (arquivoQry == NULL)
	{
		printf("erro ao tentar abrir o arquivo qry!\n");
		exit(1);
	}

	char *nomeDoArquivoSvg = (char *)malloc((strlen(prefixoDoArquivoQry) + 5) * sizeof(char));
	sprintf(nomeDoArquivoSvg, "%s.svg", prefixoDoArquivoQry);

	iniciaSvg(nomeDoArquivoSvg);
	imprimeCirculosERetangulos(cidade, nomeDoArquivoSvg);

	char *nomeDoArquivoTxt = (char *)malloc((strlen(prefixoDoArquivoQry) + 5) * sizeof(char));
	sprintf(nomeDoArquivoTxt, "%s.txt", prefixoDoArquivoQry);

	FILE *arquivoTxt;
	arquivoTxt = fopen(nomeDoArquivoTxt, "w");
	if (arquivoTxt == NULL)
	{
		printf("nao foi possivel abrir o arquivo txt\n");
		exit(1);
	}

	while (1)
	{
		fscanf(arquivoQry, "%s", comando);

		if (feof(arquivoQry))
			break;
		
		if (strcmp("o?", comando) == 0)
		{ //proximo argumento deve ser numero maximo de circulos e retangulos
			fscanf(arquivoQry, "%s %s", &id1, &id2);
			
			info1 = procuraNaCidade(cidade, id1, &tipo1, "", 0.0);
			info2 = procuraNaCidade(cidade, id2, &tipo2, "", 0.0);
			fclose(arquivoTxt);

			if (tipo1 == 1 && tipo2 == 2)
			{
				colisaoEntreCirculosERetangulos(retornaCX(info1), retornaCY(info1), retornaCR(info1), retornaReX(info2), retornaReY(info2), retornaReW(info2), retornaReH(info2), id1, id2, nomeDoArquivoTxt, nomeDoArquivoSvg);
			}
			else if (tipo1 == 2 && tipo2 == 1)
			{
				colisaoEntreCirculosERetangulos(retornaCX(info2), retornaCY(info2), retornaCR(info2), retornaReX(info1), retornaReY(info1), retornaReW(info1), retornaReH(info1), id1, id2, nomeDoArquivoTxt, nomeDoArquivoSvg);
			}
			else if (tipo1 == 1 && tipo2 == 1)
			{
				colisaoEntreCirculos(retornaCX(info1), retornaCY(info1), retornaCR(info1), retornaCX(info2), retornaCY(info2), retornaCR(info2), id1, id2, nomeDoArquivoTxt, nomeDoArquivoSvg);
			}
			else if (tipo1 == 2 && tipo2 == 2)
			{
				colisaoEntreRetangulos(retornaReX(info1), retornaReY(info1), retornaReW(info1), retornaReH(info1), retornaReX(info2), retornaReY(info2), retornaReW(info2), retornaReH(info2), id1, id2, nomeDoArquivoTxt, nomeDoArquivoSvg);
			}
			arquivoTxt = fopen(nomeDoArquivoTxt, "a");
		}
		else if (strcmp("i?", comando) == 0)
		{ //proximo argumento deve ser os parametros
			fscanf(arquivoQry, "%s %lf %lf", &id1, &x, &y);

			info1 = procuraNaCidade(cidade, id1, &tipo1, "", 0.0);

			if (tipo1 == 1)
			{
				if (pontoInternoCirculo(x, y, retornaCX(info1), retornaCY(info1), retornaCR(info1)))
				{
					fprintf(arquivoTxt, "i? %s %lf %lf\nINTERNO\n", id1, x, y);
					imprimirCirculo(2, x, y, "black", "green", nomeDoArquivoSvg, 1);
				}
				else
				{
					fprintf(arquivoTxt, "i? %s %lf %lf\nNAO INTERNO\n", id1, x, y);
					imprimirCirculo(2, x, y, "black", "red", nomeDoArquivoSvg, 1);
				}
				imprimirLinha(x, y, retornaCX(info1), retornaCY(info1), nomeDoArquivoSvg);
			}
			else if (tipo2 == 2)
			{
				if (pontoInternoRetangulo(x, y, retornaReX(info1), retornaReY(info1), retornaReW(info1), retornaReH(info1)))
				{
					fprintf(arquivoTxt, "i? %s %lf %lf\nINTERNO\n", id1, x, y);
					imprimirCirculo(2, x, y, "black", "green", nomeDoArquivoSvg, 1);
				}
				else
				{
					fprintf(arquivoTxt, "i? %s %lf %lf\nNAO INTERNO\n", id1, x, y);
					imprimirCirculo(2, x, y, "black", "red", nomeDoArquivoSvg, 1);
				}
				imprimirLinha(x, y, retornaReX(info1), retornaReY(info1), nomeDoArquivoSvg);
			}
		}
		else if (strcmp("d?", comando) == 0)
		{ //proximo argumento deve ser os parametros
			fscanf(arquivoQry, "%s %s", &id1, &id2);
			info1 = procuraNaCidade(cidade, id1, &tipo1, "", 0.0);
			info2 = procuraNaCidade(cidade, id2, &tipo2, "", 0.0);

			if(info1 == NULL || info2 == NULL)
				continue;	
			if (tipo1 == 1 && tipo2 == 2)
				distancia = distanciaDaFigura(retornaCX(info1), retornaCY(info1), retornaReX(info2), retornaReY(info2), nomeDoArquivoSvg);
			else if (tipo1 == 2 && tipo2 == 1)
				distancia = distanciaDaFigura(retornaCX(info2), retornaCY(info2), retornaReX(info1), retornaReY(info1), nomeDoArquivoSvg);
			else if (tipo1 == 1 && tipo2 == 1)
			{
				distancia = distanciaDaFigura(retornaCX(info2), retornaCY(info2), retornaCX(info1), retornaCY(info1), nomeDoArquivoSvg);
			}
			else if (tipo1 == 2 && tipo2 == 2)
				distancia = distanciaDaFigura(retornaReX(info2), retornaReY(info2), retornaReX(info1), retornaReY(info1), nomeDoArquivoSvg);

			fprintf(arquivoTxt, "d? %s %s\n%lf\n", id1, id2, distancia);
		}
		else if (strcmp("bb", comando) == 0)
		{ //proximo argumento deve ser os parametros
			fscanf(arquivoQry, "%s %s", &sufixo, &cor);

			char *arquivoDeSaida = (char *)(malloc((strlen(prefixoDoArquivoQry) + strlen(sufixo) + 7) * sizeof(char)));
			sprintf(arquivoDeSaida, "%s-%s.svg", prefixoDoArquivoQry, sufixo);
			iniciaSvg(arquivoDeSaida);
			imprimeBoundingBox(cidade, arquivoDeSaida, cor);
			finalizaSvg(arquivoDeSaida);
		}
		else if (strcmp("dq", comando) == 0)
		{
			fscanf(arquivoQry, "%s %s %lf", metrica, id1, &distancia);
			info1 = procuraNaCidade(cidade, id1, &tipo1, "", 0.0);
			verificador++;

			fclose(arquivoTxt);

			if (tipo1 == 4)
			{
				qry_dq(cidade, info1, distancia, retornaHX(info1), retornaHY(info1), nomeDoArquivoSvg, nomeDoArquivoTxt, id1, metrica, 4);
			}
			else if (tipo1 == 5)
			{
				qry_dq(cidade, info1, distancia, retornaSX(info1), retornaSY(info1), nomeDoArquivoSvg, nomeDoArquivoTxt, id1, metrica, 5);
			}
			else if (tipo1 == 6)
			{
				qry_dq(cidade, info1, distancia, retornaRX(info1), retornaRY(info1), nomeDoArquivoSvg, nomeDoArquivoTxt, id1, metrica, 6);
			}
			arquivoTxt = fopen(nomeDoArquivoTxt, "a");
		}
		else if (strcmp("del", comando) == 0)
		{
			fscanf(arquivoQry, " %s", &id1);
			verificador++;

			fclose(arquivoTxt);

			removeDaCidade(cidade, id1, nomeDoArquivoTxt);

			arquivoTxt = fopen(nomeDoArquivoTxt, "a");
		}
		else if (strcmp("cbq", comando) == 0)
		{
			fscanf(arquivoQry, "%lf %lf %lf %s", &x, &y, &distancia, cor);
			verificador++;
			fprintf(arquivoTxt, "cbq %lf %lf %lf %s\n", x, y, distancia, cor);
			fclose(arquivoTxt);
			qry_cbq(cidade, distancia, x, y, cor, nomeDoArquivoTxt);

			arquivoTxt = fopen(nomeDoArquivoTxt, "a");
		}
		else if (strcmp("crd?", comando) == 0)
		{
			verificador += 84;
			fscanf(arquivoQry, " %s", id1);
			fprintf(arquivoTxt, "crd? %s\n", id1);
			fclose(arquivoTxt);
			qry_crd(cidade, id1, nomeDoArquivoTxt); 
			arquivoTxt = fopen(nomeDoArquivoTxt, "a");
		}
		else if (strcmp("trns", comando) == 0)
		{
			fscanf(arquivoQry, "%lf %lf %lf %lf %lf %lf", &x, &y, &largura, &altura, &dx, &dy);
			verificador++;
			fprintf(arquivoTxt, "trns %lf %lf %lf %lf %lf %lf\n", x, y, largura, altura, dx, dy);
			fclose(arquivoTxt);
			qry_trns(cidade, largura, altura, x, y, dx, dy, nomeDoArquivoTxt);
			arquivoTxt = fopen(nomeDoArquivoTxt, "a");
		}
		else if (strcmp("fi", comando) == 0)
		{
			fscanf(arquivoQry, "%lf %lf %d %lf", &x, &y, &numeroDeSemaforos, &distancia);
			if(verificador2 == 0)
			{
				remove(nomeDoArquivoSvg);
				iniciaSvg(nomeDoArquivoSvg);
				imprimeCidade(cidade, nomeDoArquivoSvg);	
				verificador2++;
			}
			fclose(arquivoTxt);
			qry_fi(cidade, x, y, distancia, numeroDeSemaforos, nomeDoArquivoSvg, nomeDoArquivoTxt);
			arquivoTxt = fopen(nomeDoArquivoTxt, "a");
			verificador = 0;
		}
		else if (strcmp("fh", comando) == 0)
		{
			fscanf(arquivoQry, "%d %s %s %lf", &numeroDeHidrantes, cep, face, &numeroDoPredio);
			if(verificador2 == 0)
			{
				remove(nomeDoArquivoSvg);
				iniciaSvg(nomeDoArquivoSvg);
				imprimeCidade(cidade, nomeDoArquivoSvg);	
				verificador2++;
			}
			info1 = procuraNaCidade(cidade, cep, &tipo1, face, numeroDoPredio);
			fclose(arquivoTxt);
			resolveFH(cidade, info1, numeroDeHidrantes, nomeDoArquivoSvg, nomeDoArquivoTxt);
			arquivoTxt = fopen(nomeDoArquivoTxt, "a");
			verificador2++;
		}
		else if (strcmp("fs", comando) == 0)
		{
			fscanf(arquivoQry, "%d %s %s %lf", &numeroDeSemaforos, cep, face, &numeroDoPredio);
			if(verificador2 == 0)
			{
				remove(nomeDoArquivoSvg);
				iniciaSvg(nomeDoArquivoSvg);
				imprimeCidade(cidade, nomeDoArquivoSvg);
				verificador2++;
			}
			info1 = procuraNaCidade(cidade, cep, &tipo1, face, numeroDoPredio);
			fclose(arquivoTxt);
			resolveFS(cidade, info1, numeroDeSemaforos, nomeDoArquivoSvg, nomeDoArquivoTxt);
			arquivoTxt = fopen(nomeDoArquivoTxt, "a");
			verificador2++;
		}
		else if(strcmp("brl", comando)==0){
			double brlX, brlY;
			fscanf(arquivoQry, "%lf %lf ", &brlX, &brlY);

			if(verificador2 == 0){
				remove(nomeDoArquivoSvg);
				iniciaSvg(nomeDoArquivoSvg);
				imprimeCidade(cidade, nomeDoArquivoSvg);	
				verificador2++;
			}
			
			qry_bombaRadiacaoLum(cidade, brlX, brlY, nomeDoArquivoSvg);
		}
		else if(strcmp("brn", comando)==0){
			double brnX, brnY;
			char arqPol[51];
			fscanf(arquivoQry, "%lf %lf %50s ", &brnX, &brnY, arqPol);
			
			if(verificador2 == 0){
				remove(nomeDoArquivoSvg);
				iniciaSvg(nomeDoArquivoSvg);
				imprimeCidade(cidade, nomeDoArquivoSvg);	
				verificador2++;
			}

			qry_bombaRadiacaoNuc(cidade, brnX, brnY, nomeDoArquivoSvg, nomeDoArquivoTxt, arqPol, caminhoDoArquivoDeEntrada);
		}
		else if(strcmp("mplg?", comando)==0){
			char arqPol[51];
			int tamanhoPoligono;
			fscanf(arquivoQry, "%50s ", arqPol);
			Reta *poligono = leiaPol(caminhoDoArquivoDeEntrada, arqPol, &tamanhoPoligono);
			qry_mplg(caminhoDoArquivoDeSaida, poligono, tamanhoPoligono, arquivoTxt, tempFileName, cidade);
			for(int i=0;i<tamanhoPoligono;i++){
				retaFinalizar(poligono[i]);
			}
			free(poligono);
			verificador++;
		}
		else if(strcmp("m?", comando)==0){
			char cep[10];
			fscanf(arquivoQry, "%9s ", cep);
			qry_m(arquivoTxt, cep, cidade);
		}
		else if(strcmp("dm?", comando)==0){
			char cpf[15];
			fscanf(arquivoQry, "%14s ", cpf);
			qry_dm(arquivoTxt, cpf, cidade);
		}
		else if(strcmp("de?", comando)==0){
			char cnpj[20];
			fscanf(arquivoQry, "%19s ", cnpj);
			qry_de(arquivoTxt, cnpj, cidade);
		}
		else if(strcmp("mud", comando)==0){
			char cpf[15], cep[10], face, complemento[135];
			int num;
			fscanf(arquivoQry, "%14s %9s %c %d %134[^\n] ", cpf, cep, &face, &num, complemento);
			qry_mud(arquivoTxt, cpf, cep, face, num, complemento, cidade);
		}
		else if(strcmp("dmprbt", comando)==0)
		{
			fscanf(arquivoQry, " %c", &arvore);
            fscanf(arquivoQry, "%s", nomeDoArquivoDeArvoreSvg);
			char *nomeFinalDoArquivoSvg = (char *) malloc((strlen(caminhoDoArquivoDeSaida)+strlen(nomeDoArquivoDeArvoreSvg)+6)*sizeof(char));
            sprintf(nomeFinalDoArquivoSvg, "%s/%s", caminhoDoArquivoDeSaida, nomeDoArquivoDeArvoreSvg);
            qry_dmprbt(cidade, nomeFinalDoArquivoSvg, arvore);
			free(nomeFinalDoArquivoSvg);
		}
		else if(strcmp("eplg?", comando)==0)
		{
			char arqPol[51], tipo[31];
			int tamPolig=0;
			fscanf(arquivoQry, "%50s %30s ", arqPol, tipo);
			Reta *poligono = leiaPol(caminhoDoArquivoDeEntrada, arqPol, &tamPolig);
			qry_eplg(caminhoDoArquivoDeSaida, poligono, tamPolig, arquivoTxt, tempFileName, tipo, cidade);
			for(int i=0;i<tamPolig;i++){
				retaFinalizar(poligono[i]);
			}
			free(poligono);
			verificador++;
		}
		else if(strcmp("catac", comando)==0){
			char arqPol[51];
			int tamPolig=0;
			fscanf(arquivoQry, "%50s ", arqPol);
			Reta *poligono = leiaPol(caminhoDoArquivoDeEntrada, arqPol, &tamPolig);
			qry_catac(arquivoTxt, tempFileName, poligono, tamPolig, cidade);

			for(int i=0;i<tamPolig;i++){
				retaFinalizar(poligono[i]);
			}
			free(poligono);
			verificador++;
		}
		else if(strcmp("@m?", comando)==0){
				char cpf[15], registrador[4];
				fscanf(arquivoQry, "%3s %14s ", registrador, cpf);
				int index = atoi(registrador+1);
				if(index>=0 && index<=10){
					qry_ATmQM(cpf, R, index, cidade);
				}
			}
		else if(strcmp("@e?", comando)==0){
			char cep[10], registrador[4], face;
			int num;
			fscanf(arquivoQry, "%3s %9s %c %d ", registrador, cep, &face, &num);
			int index = atoi(registrador+1);
			if(index>=0 && index<=10){
				qry_ATeQM(cep, face, num, R, index, cidade);
			}
		}
		else if(strcmp("@g?", comando)==0){
			scanf("%d", numeroDeSemaforos);
			char registrador[4], id[20];
			fscanf(arquivoQry, "%3s %19s ", registrador, id);
			int index = atoi(registrador+1);
			if(index>=0 && index<=10){
				qry_ATgQM(id, R, index, cidade);
			}
		}
		else if(strcmp("@xy", comando)==0){
			char registrador[4];
			double x, y;
			fscanf(arquivoQry, "%3s %lf %lf ", registrador, &x, &y);
			int index = atoi(registrador+1);
			R[index] = criarPonto(x, y);
		}
		else if(strcmp("p?", comando)==0) {
			char corMaisCurto[20];
			char corMaisRapido[20];
			char registrador1[4];
			char registrador2[4];
			char sufixoDoArquivo[100];

			fscanf(arquivoQry, " %s %s %s %s %s", sufixoDoArquivo, registrador1, registrador2, corMaisCurto, corMaisRapido);
			int index1 = atoi(registrador1+1);
			int index2 = atoi(registrador2+1);

			char* arquivoDeSaidaGrafoSvg = malloc(sizeof(prefixoDoArquivoQry) + sizeof(sufixoDoArquivo) + 3);
			sprintf(arquivoDeSaidaGrafoSvg, "%s-%s.svg", prefixoDoArquivoQry, sufixoDoArquivo);

			char* arquivoDeSaidaGrafoTxt = malloc(sizeof(prefixoDoArquivoQry) + sizeof(sufixoDoArquivo) + 3);
			sprintf(arquivoDeSaidaGrafoTxt, "%s-%s.txt", prefixoDoArquivoQry, sufixoDoArquivo);
			iniciaSvg(arquivoDeSaidaGrafoSvg);
			imprimeCidade(cidade, arquivoDeSaidaGrafoSvg);
			imprimeCirculosERetangulos(cidade, arquivoDeSaidaGrafoSvg);
			dijkstra(grafo, retornaIndiceVertice(getLista(grafo), getPontoX(R[index1]), getPontoY(R[index1])), retornaIndiceVertice(getLista(grafo), getPontoX(R[index2]), getPontoY(R[index2])), arquivoDeSaidaGrafoSvg, arquivoDeSaidaGrafoTxt, corMaisCurto, corMaisRapido, 1);
			dijkstra(grafo, retornaIndiceVertice(getLista(grafo), getPontoX(R[index1]), getPontoY(R[index1])), retornaIndiceVertice(getLista(grafo), getPontoX(R[index2]), getPontoY(R[index2])), arquivoDeSaidaGrafoSvg, arquivoDeSaidaGrafoTxt, corMaisCurto, corMaisRapido, 2);
			finalizaSvg(arquivoDeSaidaGrafoSvg);
			verificador = 0;
			verificador2 = 1;
		}
	}
	if(verificador != 0 && verificador2 == 0){
		imprimeCidade(cidade, nomeDoArquivoSvg);
		imprimeCirculosERetangulos(cidade, nomeDoArquivoSvg);
		FILE* arquivoSvg = fopen(nomeDoArquivoSvg, "a");
		if(arquivoSvg != NULL){
			FILE* tempFile = fopen(tempFileName, "r+");
			while(!feof(tempFile)){
				char buffer[301];
				fgets(buffer, 300, tempFile);
				fputs(buffer, arquivoSvg);
			}
			fclose(tempFile);
			remove(tempFileName);
			fclose(arquivoSvg);
		}
		finalizaSvg(nomeDoArquivoSvg);
	}

	if (verificador == 84)
		remove(nomeDoArquivoSvg);

	free(nomeDoArquivoSvg);
	nomeDoArquivoSvg = NULL;
	free(nomeDoArquivoTxt);
	nomeDoArquivoTxt = NULL;
	for(int i=0;i<11;i++){
		if(R[i])
			pontoFinalizar(R[i]);
	}

	fclose(arquivoQry);
}

void leiaEc(char* arquivoEc, HashTable comercios, HashTable tiposComercio, HashTable comercios_cpf){
	FILE* ec = fopen(arquivoEc, "r");
	if(!ec){
		printf("Não foi possível abrir o arquivo ec: %s\n", arquivoEc);
		exit(-1);
	}
	
	char comando;
	char linha[150];
	while(!feof(ec)){
		fgets(linha, 148, ec);
		sscanf(linha, "%c", &comando);

		if(comando == 't'){
			char tipo[21], descricao[129];

			sscanf(linha, "%*c %20s %[^\n]", tipo, descricao);

			ComercioTipo ct = tipoComercioNovo(tipo, descricao);
			int reg = insereRegistro(tiposComercio, tipo, ct);
			if(reg<0){
				printf("Erro ao inserir o tipo de comercio \'%s\'\n", tipo);
			}
		}
		else if(comando == 'e'){
			char cnpj[19], cpf[15], tipo[21], cep[10], nome[85];
			char face;
			int num;

			sscanf(linha, "%*c %18s %14s %20s %9s %c %d %[^\n]", cnpj, cpf, tipo, cep, &face, &num, nome);

			if(!existeChave(tiposComercio, tipo)){
				printf("O tipo de estabelecimento %s não existe\n", tipo);
			}else{
				EstabelecimentoComercial com = estabelecimentoNovo(cnpj, cpf, tipo, cep, face, num, nome);
				int reg = insereRegistro(comercios, cnpj, com);
				int reg1 = insereRegistro(comercios_cpf, cpf, com);
				if(reg<0 || reg1<0){
					printf("Erro ao inserir o comercio \'%s\'\n", cnpj);
				}
			}
		}
	}
}

void leiaPm(char* arquivoPm, HashTable pessoas, HashTable moradias, HashTable moradiaPessoa){
	FILE* pm = fopen(arquivoPm, "r");
	if(!pm){
		printf("Erro ao abrir o arquivo pm \'%s\'\n", arquivoPm);
		exit(-1);
	}

	char comando;
	char linha[150];
	while(!feof(pm)){
		fgets(linha, 150, pm);
		sscanf(linha, "%c", &comando);

		if(comando == 'p'){
			char cpf[15], nome[50], sobrenome[50], nascimento[11];
			char sexo;

			sscanf(linha, "%*c %14s %49s %49s %c %10s ", cpf, nome, sobrenome, &sexo, nascimento);

			Pessoa pes = pessoaNovo(cpf, nome, sobrenome, nascimento, sexo);
			int reg = insereRegistro(pessoas, cpf, pes);
			if(reg<0){
				printf("Erro ao inserir a pessoa \'%s\'\n", cpf);
			}
		}
		else if(comando == 'm'){
			char cpf[15], cep[10], complemento[135];
			char face;
			int num;

			sscanf(linha, "%*c %14s %9s %c %d %[^\n]", cpf, cep, &face, &num, complemento);
			
			Moradia mor = moradiaNovo(cep, face, num, complemento);
			int reg = insereRegistro(moradias, cpf, mor);
			if(reg<0){
				printf("Erro ao inserir a moradia \'%s, %c, %d\'\n", cep, face, num);
			}

			char* cpfInfo = malloc(strlen(cpf)+1);
			strcpy(cpfInfo, cpf);
			insereRegistro(moradiaPessoa, cep, cpfInfo);
		}
	}
}

Reta* leiaPol(char* caminhoDoArquivoDeSaida, char* nomeArquivoPoligono, int* array_size){
	char* nomeArqPol = NULL;
	if(caminhoDoArquivoDeSaida){
		nomeArqPol = malloc((strlen(caminhoDoArquivoDeSaida)+strlen(nomeArquivoPoligono)+2)*sizeof(char));
		sprintf(nomeArqPol, "%s/%s", caminhoDoArquivoDeSaida, nomeArquivoPoligono);
	}else{
		nomeArqPol = malloc(strlen(nomeArquivoPoligono)*sizeof(char));
		strcpy(nomeArqPol, nomeArquivoPoligono);
	}
	FILE* arq = fopen(nomeArqPol, "r");
	if(!arq){
		printf("Não foi possível abrir o arquivo do polígono: %s\n", nomeArqPol);
		return NULL;
	}
	*array_size = 0;
	char linha[41];

	//Checa a quantidade de linhas do arquivo
	while(!feof(arq)){
		fgets(linha, 40, arq);
		*array_size = *array_size +1;
	}

	if(*array_size <=2){
		printf("Do arquivo '%s', muitos poucos pontos para formar um polígono\n", nomeArquivoPoligono);
		return NULL;
	}

	double* arrayPontos = malloc(sizeof(double)*(*array_size)*2);
	rewind(arq);
	int i=0;
	while(!feof(arq)){
		double x, y;
		fgets(linha, 40, arq);
		sscanf(linha, "%lf %lf ", &x, &y);
		arrayPontos[i] = x;
		i++;
		arrayPontos[i]= y;
		i++;
	}

	int j=0;
	int reta=0;
	Reta* arrayRetas = malloc(sizeof(Reta)*(*array_size));
	while(j<i){
		double x1, x2, y1, y2;
		x1 = arrayPontos[j];
		j++;
		y1 = arrayPontos[j];
		j++;
		if(j>=i){
			x2 = arrayPontos[0];
			y2 = arrayPontos[1];
		}else{
			x2 = arrayPontos[j];
			y2 = arrayPontos[j+1];
		}
		arrayRetas[reta] = criarReta(x1, y1, x2, y2);
		reta++;
	}
	
	fclose(arq);
	free(nomeArqPol);
	free(arrayPontos);
	return arrayRetas;
}

Graph leiaVia(char* nomeDoArquivoVia) {
	FILE* arquivoVia;

	List lista;
	Graph grafo;

	char comando = 'v';
	char id[100];
	char nome[100];
	char ladoDireito[100];
	char ladoEsquerdo[100];
	char v1[100];
	char v2[100];
	char nomeDaRua[100];

	double x, y, comprimento, velocidade;

	printf("nome do arquivo: %s\n", nomeDoArquivoVia);

	arquivoVia = fopen(nomeDoArquivoVia, "r");
	if(!arquivoVia){
		printf("Erro ao abrir o arquivo pm \'%s\'\n", nomeDoArquivoVia);
		exit(1);
	}

	lista = criaLista();

	while (1)
	{
		fscanf(arquivoVia, "\n%c", &comando);
		if (feof(arquivoVia))
			break;
		
		if ('v' == comando) {
			fscanf(arquivoVia, "%s %lf %lf", id, &x, &y);
			criaNoListaDinamica(lista, id, x, y);
		}
		else
		{
			break;
		}
	}

	grafo = criaGrafo(getTamanho(lista));

	insereVertice(grafo, lista);

	setLista(grafo, lista);

	if ('e' == comando) {
		fscanf(arquivoVia, "%s %s %s %s %lf %lf %s", v1, v2, ladoDireito, ladoEsquerdo, &comprimento, &velocidade, nomeDaRua);
		insereAresta(grafo, getIndiceVertice(grafo, v1), getIndiceVertice(grafo, v2), ladoDireito, ladoEsquerdo, comprimento, velocidade, nomeDaRua);
	}

	while (1)
	{
		fscanf(arquivoVia, "\n%c", &comando);

		if (feof(arquivoVia))
			break;
		
		if ('e' == comando) {
			fscanf(arquivoVia, "%s %s %s %s %lf %lf %s", v1, v2, ladoDireito, ladoEsquerdo, &comprimento, &velocidade, nomeDaRua);
			insereAresta(grafo, getIndiceVertice(grafo, v1), getIndiceVertice(grafo, v2), ladoDireito, ladoEsquerdo, comprimento, velocidade, nomeDaRua);
		}
		else
		{
			break;
		}
	}

	// (b0|2,2)(b0|3,2).0 (b0|8,5)(b0|7,5).0
	// dijkstra(grafo, getIndiceVertice(grafo, "(b0|10,10)"), getIndiceVertice(grafo, "(b0|1,1)"), 1);
	// imprimeGrafo(grafo);
	return grafo;
}
