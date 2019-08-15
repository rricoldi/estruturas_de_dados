#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "leitura.h"

Cidade leiaGeo(char nomeDoArquivoGeo[], char nomeDoArquivoSvg[])
{
	FILE *arquivoGeo;
	printf("%s\n", nomeDoArquivoGeo);
	arquivoGeo = fopen(nomeDoArquivoGeo, "r");

	if (arquivoGeo == NULL)
	{
		printf("Nao foi possivel Abrir o arquivo Geo\n");
		exit(1);
	}

    int numeroDoPredio;
    int numeroDeFiguras    = 0;
    int numeroDeQuadras    = 0;
    int numeroDeHidrantes  = 0;
    int numeroDeSemaforos  = 0;
    int numeroDeRadioBases = 0;
    int numeroDePredios    = 0;
    int numeroDeMuros      = 0;

    int numeroMaximoDeFiguras    = 1000;
    int numeroMaximoDeQuadras    = 1000;
    int numeroMaximoDeHidrantes  = 1000;
    int numeroMaximoDeSemaforos  = 1000;
    int numeroMaximoDeRadioBases = 1000;
    int numeroMaximoDePredios    = 1000;
    int numeroMaximoDeMuros      = 1000;

    double x, y, altura, largura, raio;
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
    char corDoPreenchimentoDoPredio[20]    = "grey";
    char corDaBordaDoPredio[20]            = "black";

	size_t bufsize = 32;
	Info info;

	iniciaSvg(nomeDoArquivoSvg);

	fscanf(arquivoGeo, "%s", comando);
	if (strcmp("nx", comando) == 0)
	{
		fscanf(arquivoGeo, "%d %d %d %d %d %d %d", &numeroMaximoDeFiguras, &numeroMaximoDeQuadras, &numeroMaximoDeHidrantes, &numeroMaximoDeSemaforos, &numeroMaximoDeRadioBases, &numeroMaximoDePredios, &numeroMaximoDeMuros);
	}

	Cidade cidade = criarCidade(numeroMaximoDeFiguras, numeroMaximoDeQuadras, numeroMaximoDeHidrantes, numeroMaximoDeSemaforos, numeroMaximoDeRadioBases, numeroMaximoDePredios, numeroMaximoDeMuros);

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
				numeroDeFiguras ++;
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
				numeroDeFiguras ++;
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
				numeroDeQuadras ++;
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
				numeroDeHidrantes ++;
			}
		}
		else if (strcmp("s", comando) == 0)
		{
			fscanf(arquivoGeo, "%s %lf %lf", id, &x, &y);
			if (numeroDeSemaforos < numeroMaximoDeSemaforos)
			{
				info = criarSemaforo(id, corDaBordaDoSemagoro, corDoPreenchimentoDoSemaforo, x, y, espessuraDosSemaforos);
				adicionarSemaforo(cidade, info);

				imprimirRetangulo(7, 18, x, y, corDaBordaDoSemagoro, corDoPreenchimentoDoSemaforo, nomeDoArquivoSvg, espessuraDosSemaforos);
				numeroDeSemaforos ++;
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
				numeroDeRadioBases ++;
			}
		}
        else if (strcmp("prd", comando) == 0)
        {
            fscanf(arquivoGeo, "%s %s %d %lf %lf %lf", &id, &face, &numeroDoPredio, &tamanhoDaFrente, &tamanhoDoLado, &larguraDaCalcada);
            if (numeroDePredios < numeroMaximoDePredios)
            {
                info = criarPredio(id, corDaBordaDoPredio, corDoPreenchimentoDoPredio, face, numeroDoPredio, tamanhoDaFrente, tamanhoDoLado, larguraDaCalcada);
                adicionarPredio(cidade, info);

                imprimirPredio(id, corDaBordaDoPredio, corDoPreenchimentoDoPredio, face, numeroDoPredio, tamanhoDaFrente, tamanhoDoLado, larguraDaCalcada);
                numeroDePredios ++;
            }
        }
		else if (strcmp("mur", comando) == 0)
		{
			fscanf(arquivoGeo, "%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
			if (numeroDeMuros < numeroMaximoDeMuros)
			{
				info = criarMuro(x1, y1, x2, y2);
				adicionarMuro(cidade, info);
				numeroDeMuros ++;
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

	imprimeCidade(cidade, nomeDoArquivoSvg);

	finalizaSvg(nomeDoArquivoSvg);

	fclose(arquivoGeo);

	return cidade;
}