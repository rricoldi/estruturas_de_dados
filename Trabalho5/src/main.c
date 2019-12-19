#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cidade.h"
#include "leitura.h"
#include"hashTable.h"

char *retornarPrefixoDoArquivo(char nomeDoArquivo[])
{
    char *prefixo, caractere;
    int contador, contador2;
    int posicao;

    for(contador = strlen(nomeDoArquivo) - 1; contador >= 0; contador --)
    {
		caractere = nomeDoArquivo[contador];
        
        if(caractere == '/')
        {
			posicao = strlen(nomeDoArquivo) - contador;
        	prefixo = (char*) malloc(posicao*sizeof(char));

        	for(contador2 = 0; contador2 <= posicao; contador2 ++){
            	prefixo[contador2] = nomeDoArquivo[contador + 1];
            	contador ++;
        	}  
			return strtok(prefixo,".");
        }        
    }
	return strtok(nomeDoArquivo,".");
}

void resolverInterativos(Cidade cidade, char* caminhoDoArquivoDeSaida, char* prefixoDoArquivoGeo, char* caminhoDoArquivo, Graph grafo){
    
    char comando[9];
    char nomeDoArquivoQry[100];
    char nomeDoArquivoSvg[100];
    char arvore;
    char *prefixoFinalDoArquivoQry = NULL;
    char *nomeFinalDoArquivoSvg = NULL;

    while(1)
    {
        printf("interativo\n");
        scanf("%s", comando);
        if(strcmp(comando, "q")==0){
            scanf("%s", nomeDoArquivoQry);
            char* prefixoDoArquivoDeSaida = (char *) malloc((strlen(caminhoDoArquivoDeSaida)+strlen(prefixoDoArquivoGeo)+6)*sizeof(char));
            sprintf(prefixoDoArquivoDeSaida, "%s/%s", caminhoDoArquivoDeSaida, prefixoDoArquivoGeo);

            // interativoQ(argumento1, cidade);
            prefixoFinalDoArquivoQry = (char *) malloc((strlen(caminhoDoArquivoDeSaida)+strlen(prefixoDoArquivoGeo)+6+strlen(retornarPrefixoDoArquivo(nomeDoArquivoQry)))*sizeof(char));
            sprintf(prefixoFinalDoArquivoQry, "%s/%s-%s", caminhoDoArquivoDeSaida, prefixoDoArquivoGeo, retornarPrefixoDoArquivo(nomeDoArquivoQry));

            printf("Bloco do Qry inicializado\n");
            leiaQry(caminhoDoArquivo, prefixoFinalDoArquivoQry, nomeDoArquivoQry, cidade, grafo, caminhoDoArquivoDeSaida, prefixoDoArquivoDeSaida);
            printf("Bloco do Qry finalizado\n");
        }
        else if(strcmp(comando, "dmprbt")==0){
            scanf(" %c", &arvore);
            scanf("%s", nomeDoArquivoSvg);
            nomeFinalDoArquivoSvg = (char *) malloc((strlen(caminhoDoArquivoDeSaida)+strlen(nomeDoArquivoSvg)+6)*sizeof(char));
            sprintf(nomeFinalDoArquivoSvg, "%s/%s", caminhoDoArquivoDeSaida, nomeDoArquivoSvg);
            qry_dmprbt(cidade, nomeFinalDoArquivoSvg, arvore);
        }
        else if(strcmp(comando, "sai")==0){
            free(prefixoFinalDoArquivoQry);
            free(nomeFinalDoArquivoSvg);
            break;
        }
        else if(strcmp(comando, "nav")==0){
            scanf(" %c", &arvore);
            qry_nav(cidade, arvore);
        }
    }
}

int main(int argc, char *argv[])
{
    int contador                  = 1;
    int interativo                = 0;

    char *caminhoDoArquivo        = NULL;
    char *caminhoDoArquivoDeSaida = NULL;
    char *nomeDoArquivoGeo        = NULL;
    char *prefixoDoArquivoGeo     = NULL;
    char *arquivoGeo              = NULL;
    char *nomeDoArquivoQry        = NULL;
    char *prefixoDoAquivoQry      = NULL;
    char *arquivoQry              = NULL;
    char *prefixoFinalDoQry       = NULL;
    char *nomeDoArquivoSvg        = NULL;
    char *nomeDoArquivoEc         = NULL;
    char *arquivoEc               = NULL;
    char *nomeDoArquivoPm         = NULL;
    char *arquivoPm               = NULL;
    char *nomeDoArquivoVia        = NULL;
    char *arquivoVia              = NULL;

    while(contador<argc)
    {
        if (strcmp("-f",argv[contador])==0){ 
            contador++;
            if (argv[contador] == NULL){
                printf("\n!Erro! Sem parametros em -f");
                exit(1);
            }
            nomeDoArquivoGeo = (char *)malloc((strlen(argv[contador])+1)*sizeof(char));
            strcpy(nomeDoArquivoGeo,argv[contador]);
        }
        else if (strcmp("-e",argv[contador])==0){ 
            contador++;
           if (argv[contador] == NULL){ 
                printf("\n!Erro! Sem parametros em -e");
                exit(1);
            }        
            caminhoDoArquivo = (char *)malloc((strlen(argv[contador])+1)*sizeof(char));
            strcpy(caminhoDoArquivo,argv[contador]);
        }
        else if (strcmp("-q",argv[contador])==0)
        {
            contador++;
            if (argv[contador] == NULL){ 
                printf("\n!Erro! Sem parametros em -q");
                exit(1);
            }

            nomeDoArquivoQry = (char *)malloc((strlen(argv[contador])+1)*sizeof(char));
            strcpy(nomeDoArquivoQry,argv[contador]);
        }
        else if (strcmp("-o",argv[contador])==0)
        {  
            contador++;
            if (argv[contador] == NULL){    
                printf("\n!Erro! Sem parametros em -o");
                exit(1);
            }

            caminhoDoArquivoDeSaida = (char *)malloc((strlen(argv[contador])+1)*sizeof(char));
            strcpy(caminhoDoArquivoDeSaida,argv[contador]);
        }
        else if (strcmp("-ec", argv[contador]) == 0)
        {
            contador++;
            if (argv[contador] == NULL){    
                printf("\n!Erro! Sem parametro para -ec");
                exit(1);
            }

            nomeDoArquivoEc = (char *)malloc((strlen(argv[contador])+1)*sizeof(char));
            strcpy(nomeDoArquivoEc, argv[contador]);
        }
        else if (strcmp("-pm", argv[contador]) == 0)
        {
            contador++;
            if (argv[contador] == NULL){    
                printf("\n!Erro! Sem parametro para -pm");
                exit(1);
            }

            nomeDoArquivoPm = (char *)malloc((strlen(argv[contador])+1)*sizeof(char));
            strcpy(nomeDoArquivoPm, argv[contador]);
        }
        else if (strcmp("-v", argv[contador]) == 0)
        {
            contador++;
            if (argv[contador] == NULL){    
                printf("\n!Erro! Sem parametro para -v");
                exit(1);
            }

            nomeDoArquivoVia = (char *)malloc((strlen(argv[contador])+1)*sizeof(char));
            strcpy(nomeDoArquivoVia, argv[contador]);
        }
        else if (strcmp("-i", argv[contador]) == 0)
        {
            interativo = 1;
        }
        contador++;
    }

	if (caminhoDoArquivo != NULL)
    {
		arquivoGeo = (char *)malloc((strlen(nomeDoArquivoGeo)+strlen(caminhoDoArquivo)+2)*sizeof(char));
    	sprintf(arquivoGeo,"%s/%s",caminhoDoArquivo,nomeDoArquivoGeo);
        
        if (nomeDoArquivoQry != NULL)
        {
            arquivoQry = (char *)malloc((strlen(nomeDoArquivoQry)+strlen(caminhoDoArquivo)+2)*sizeof(char));
            sprintf(arquivoQry,"%s/%s",caminhoDoArquivo,nomeDoArquivoQry);
        }
        if(nomeDoArquivoEc != NULL){
            arquivoEc = malloc(sizeof(char)*(strlen(caminhoDoArquivo) + strlen(nomeDoArquivoEc) + 2));
            sprintf(arquivoEc, "%s/%s", caminhoDoArquivo, nomeDoArquivoEc);
        }
        if(nomeDoArquivoPm != NULL){
            arquivoPm = malloc(sizeof(char)*(strlen(caminhoDoArquivo) + strlen(nomeDoArquivoPm) + 2));
            sprintf(arquivoPm, "%s/%s", caminhoDoArquivo, nomeDoArquivoPm);
        }
        if(nomeDoArquivoVia != NULL){
            arquivoVia = malloc(sizeof(char)*(strlen(caminhoDoArquivo) + strlen(nomeDoArquivoVia) + 2));
            sprintf(arquivoVia, "%s/%s", caminhoDoArquivo, nomeDoArquivoVia);
        }
	}
    else
    {
		arquivoGeo = (char *)malloc((strlen(nomeDoArquivoGeo)+1)*sizeof(char));
    	sprintf(arquivoGeo, nomeDoArquivoGeo);

    	if (nomeDoArquivoQry != NULL)
        {
            arquivoQry = (char *)malloc((strlen(nomeDoArquivoQry)+1)*sizeof(char));
    	    strcpy(arquivoQry, nomeDoArquivoQry);
        }
        if(nomeDoArquivoEc != NULL){
            arquivoEc = malloc(sizeof(char)*(strlen(nomeDoArquivoEc) + 1));
            sprintf(arquivoEc, "%s", nomeDoArquivoEc);
        }
        if(nomeDoArquivoPm != NULL){
            arquivoPm = malloc(sizeof(char)*(strlen(nomeDoArquivoPm) + 1));
            sprintf(arquivoPm, "%s", nomeDoArquivoPm);
        }
        if(nomeDoArquivoVia != NULL){
            arquivoVia = malloc(sizeof(char)*(strlen(nomeDoArquivoVia) + 1));
            sprintf(arquivoVia, "%s", nomeDoArquivoVia);
        }
	}

	prefixoDoArquivoGeo = (char *) malloc((strlen(nomeDoArquivoGeo)+1)*sizeof(char));	
    prefixoDoArquivoGeo = retornarPrefixoDoArquivo(nomeDoArquivoGeo);

    if(nomeDoArquivoQry != NULL)
    {
        prefixoDoAquivoQry = (char *) malloc((strlen(nomeDoArquivoQry)+1)*sizeof(char));
        prefixoDoAquivoQry = retornarPrefixoDoArquivo(nomeDoArquivoQry);
    }
	 
	nomeDoArquivoSvg = (char *)malloc((strlen(caminhoDoArquivoDeSaida)+strlen(prefixoDoArquivoGeo)+6)*sizeof(char));
    sprintf(nomeDoArquivoSvg, "%s/%s.svg", caminhoDoArquivoDeSaida, prefixoDoArquivoGeo);

    //BLOCO QUE RESOLVE O GEO
    printf("Bloco do Geo inicializado\n");
	Cidade cidade = leiaGeo(arquivoGeo, nomeDoArquivoSvg);
    printf("Bloco do Geo finalizado\n");

    printf("Bloco do Via inicializado\n");
    Graph grafo = leiaVia(arquivoVia);
    printf("Bloco do Via finalizado\n");

    if(arquivoEc != NULL){
        iniciaComercios(cidade, arquivoEc);
    }
    if(arquivoPm != NULL){
        iniciaPessoas(cidade, arquivoPm);
    }

    if(nomeDoArquivoQry != NULL)
    {
        //    ARRUMA O PREFIXO DO NOME DO ARQUIVO QRY
        prefixoFinalDoQry = (char *) malloc((strlen(caminhoDoArquivoDeSaida)+strlen(prefixoDoArquivoGeo)+strlen(prefixoDoAquivoQry)+6)*sizeof(char));
        sprintf(prefixoFinalDoQry, "%s/%s-%s", caminhoDoArquivoDeSaida, prefixoDoArquivoGeo, prefixoDoAquivoQry);

        char* prefixoDoArquivoDeSaida = (char *) malloc((strlen(caminhoDoArquivoDeSaida)+strlen(prefixoDoArquivoGeo)+6)*sizeof(char));
        sprintf(prefixoDoArquivoDeSaida, "%s/%s", caminhoDoArquivoDeSaida, prefixoDoArquivoGeo);

        printf("Bloco do Qry inicializado\n");
        leiaQry(caminhoDoArquivo, prefixoFinalDoQry, arquivoQry, cidade, grafo, caminhoDoArquivoDeSaida, prefixoDoArquivoDeSaida);
        printf("Bloco do Qry finalizado\n");

        if(!interativo)
        {
            free(nomeDoArquivoQry);
            free(prefixoDoAquivoQry);
            free(prefixoFinalDoQry);
            free(arquivoQry);
        }
    }

    if(interativo)
    {
        resolverInterativos(cidade, caminhoDoArquivoDeSaida, prefixoDoArquivoGeo, grafo, caminhoDoArquivo);
        free(nomeDoArquivoQry);
        free(prefixoDoAquivoQry);
        free(prefixoFinalDoQry);
        free(arquivoQry);
    }

    removeCidade(cidade);
	printf("Cidade desalocada\n");

	free(arquivoGeo);
	free(nomeDoArquivoGeo);
    free(caminhoDoArquivo);
	free(caminhoDoArquivoDeSaida);
    
    free(nomeDoArquivoSvg);
    printf("Mémoria desalocada\n");
    
    return 0;
}
