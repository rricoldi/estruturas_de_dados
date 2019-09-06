#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "leitura.h"

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

	int tipo = 0;
	int numeroDeFiguras = 0;
	int numeroDeQuadras = 0;
	int numeroDeHidrantes = 0;
	int numeroDeSemaforos = 0;
	int numeroDeRadioBases = 0;
	int numeroDePredios = 0;
	int numeroDeMuros = 0;

	int numeroMaximoDeFiguras = 1000;
	int numeroMaximoDeQuadras = 1000;
	int numeroMaximoDeHidrantes = 1000;
	int numeroMaximoDeSemaforos = 1000;
	int numeroMaximoDeRadioBases = 1000;
	int numeroMaximoDePredios = 1000;
	int numeroMaximoDeMuros = 1000;

	double numeroDoPredio;
	double x, y, altura, largura, raio;
	double xCalcada, yCalcada, xCalcadaMax, yCalcadaMax;
	double xNum, yNum;
	double x1, x2, y1, y2;
	double tamanhoDaFrente;
	double tamanhoDoLado;
	double larguraDaCalcada;
	double espessuraDosCirculos = 1;
	double espessuraDosRetangulos = 1;
	double espessuraDasQuadras = 1;
	double espessuraDosHidrantes = 1;
	double espessuraDosSemaforos = 1;
	double espessuraDasRadioBases = 1;

	char *texto;
	char comando[3];
	char id[20];
	char face[6];
	char corDoPreenchimentoDaFigura[20] = "white";
	char corDaBordaDaFigura[20] = "black";
	char corDoPreenchimentoDaQuadra[20] = "orange";
	char corDaBordaDaQuadra[20] = "blue";
	char corDoPreenchimentoDoHidrante[20] = "red";
	char corDaBordaDoHidrante[20] = "black";
	char corDoPreenchimentoDoSemaforo[20] = "yellow";
	char corDaBordaDoSemagoro[20] = "green";
	char corDoPreenchimentoDaRadioBase[20] = "purple";
	char corDaBordaDaRadioBase[20] = "pink";

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
		{
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
				
				Info quadra = procuraNaCidade(cidade, id, &tipo, "", 0.0);
				
				if (strcmp("N", face) == 0)
				{
					x = retornaQX(quadra) + numeroDoPredio - (tamanhoDaFrente / 2);
					y = retornaQY(quadra) + retornaQH(quadra) - tamanhoDoLado;
					xCalcada = retornaQX(quadra);
					xCalcadaMax = retornaQW(quadra);
					yCalcada = retornaQY(quadra) + retornaQH(quadra);
					yCalcadaMax = larguraDaCalcada;
					xNum = retornaQX(quadra) + (retornaQW(quadra) / 2);
					yNum = retornaQY(quadra) + (retornaQH(quadra) - 2);
				}
				else if (strcmp("S", face) == 0)
				{
					x = retornaQX(quadra) + numeroDoPredio - (tamanhoDaFrente / 2);
					y = retornaQY(quadra);
					xCalcada = retornaQX(quadra);
					xCalcadaMax = retornaQW(quadra);
					yCalcada = retornaQY(quadra) - larguraDaCalcada;
					yCalcadaMax = larguraDaCalcada;
					xNum = retornaQX(quadra) + (retornaQW(quadra) / 2);
					yNum = retornaQY(quadra) + 2;
				}
				else if (strcmp("L", face) == 0)
				{
					x = retornaQX(quadra);
					y = retornaQY(quadra) + numeroDoPredio - (tamanhoDaFrente / 2);
					xCalcada = retornaQX(quadra) - larguraDaCalcada;
					xCalcadaMax = larguraDaCalcada;
					yCalcada = retornaQY(quadra);
					yCalcadaMax = retornaQH(quadra);
					xNum = retornaQX(quadra) + 2;
					yNum = retornaQY(quadra) + (retornaQH(quadra) / 2);
				}
				else if (strcmp("O", face) == 0)
				{
					x = retornaQX(quadra) + retornaQW(quadra) - tamanhoDoLado;
					y = retornaQY(quadra) + numeroDoPredio - (tamanhoDaFrente / 2);
					xCalcada = retornaQX(quadra) + retornaQW(quadra);
					xCalcadaMax = larguraDaCalcada;
					yCalcada = retornaQY(quadra);
					yCalcadaMax = retornaQH(quadra);
					xNum = retornaQX(quadra) + retornaQW(quadra) - 2;
					yNum = retornaQY(quadra) + (retornaQH(quadra) / 2);
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
				info = criarMuro(x1, y1, x2, y2);
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

void leiaQry(char prefixoDoArquivoQry[], char nomeDoArquivoQry[], Cidade cidade)
{
	int tipo1, tipo2;
	int verificador = 0;

	double x, y;
	double dx, dy;
	double distancia, largura, altura;

	char id1[20], id2[20];
	char metrica[3];
	char comando[5];
	char sufixo[30];
	char cor[30];
	
	Info info1 = 0, info2 = 0;

	FILE *ArquivoQry;
	printf("%s\n", nomeDoArquivoQry);
	ArquivoQry = fopen(nomeDoArquivoQry, "r");
	if (ArquivoQry == NULL)
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
		fscanf(ArquivoQry, "%s", comando);

		if (feof(ArquivoQry))
			break;
		
		if (strcmp("o?", comando) == 0)
		{ //proximo argumento deve ser numero maximo de circulos e retangulos
			fscanf(ArquivoQry, "%s %s", &id1, &id2);
			
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
			fscanf(ArquivoQry, "%s %lf %lf", &id1, &x, &y);

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
			fscanf(ArquivoQry, "%s %s", &id1, &id2);
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
			fscanf(ArquivoQry, "%s %s", &sufixo, &cor);

			char *arquivoDeSaida = (char *)(malloc((strlen(prefixoDoArquivoQry) + strlen(sufixo) + 7) * sizeof(char)));
			sprintf(arquivoDeSaida, "%s-%s.svg", prefixoDoArquivoQry, sufixo);
			iniciaSvg(arquivoDeSaida);

			boudingBoxCirculos(cidade, arquivoDeSaida );
			boundingBoxRetangulos(cidade, arquivoDeSaida , cor);

			finalizaSvg(arquivoDeSaida);
		}
		else if (strcmp("dq", comando) == 0)
		{
			fscanf(ArquivoQry, "%s %s %lf", metrica, id1, &distancia);
			info1 = procuraNaCidade(cidade, id1, &tipo1, "", 0.0);
			verificador++;

			fclose(arquivoTxt);

			if (tipo1 == 4)
			{
				percorreCidade(cidade, distancia, retornaHX(info1), retornaHY(info1), metrica, nomeDoArquivoSvg, nomeDoArquivoTxt, id1, 1, "", 0, 0, 0, 0);
			}
			else if (tipo1 == 5)
			{
				percorreCidade(cidade, distancia, retornaSX(info1), retornaSY(info1), metrica, nomeDoArquivoSvg, nomeDoArquivoTxt, id1, 1, "", 0, 0, 0, 0);
			}
			else if (tipo1 == 6)
			{
				percorreCidade(cidade, distancia, retornaRX(info1), retornaRY(info1), metrica, nomeDoArquivoSvg, nomeDoArquivoTxt, id1, 1, "", 0, 0, 0, 0);
			}
			arquivoTxt = fopen(nomeDoArquivoTxt, "a");
		}
	}

	finalizaSvg(nomeDoArquivoSvg);

	free(nomeDoArquivoSvg);

	fclose(ArquivoQry);
}