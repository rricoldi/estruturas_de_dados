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

void resolverInterativos(Cidade cidade, char* caminhoDoArquivoDeSaida, char* prefixoDoArquivoGeo, char* caminhoDoArquivo, char* nomeDoArquivoVia){
    
    char comando[9];
    char comando2[3];
    char nomeDoArquivoQry[100];
    char nomeDoArquivoSvg[100];
    char arvore;
    char *prefixoFinalDoArquivoQry = NULL;
    char *nomeFinalDoArquivoSvg = NULL;
    Graph* grafo = leiaVia(nomeDoArquivoVia);
    int modo;

    while(1)
    {
        printf("interativo\n");
        scanf("%s", comando);
        if(strcmp(comando, "q")==0){
            scanf("%s", nomeDoArquivoQry);
            char* prefixoDoArquivoDeSaida = (char *) malloc((strlen(caminhoDoArquivoDeSaida)+strlen(prefixoDoArquivoGeo)+6)*sizeof(char));
            sprintf(prefixoDoArquivoDeSaida, "%s/%s", caminhoDoArquivoDeSaida, prefixoDoArquivoGeo);

            prefixoFinalDoArquivoQry = (char *) malloc((strlen(caminhoDoArquivoDeSaida)+strlen(prefixoDoArquivoGeo)+6+strlen(retornarPrefixoDoArquivo(nomeDoArquivoQry)))*sizeof(char));
            sprintf(prefixoFinalDoArquivoQry, "%s/%s-%s", caminhoDoArquivoDeSaida, prefixoDoArquivoGeo, retornarPrefixoDoArquivo(nomeDoArquivoQry));

            printf("Bloco do Qry inicializado\n");
            leiaQry(caminhoDoArquivo, prefixoFinalDoArquivoQry, nomeDoArquivoQry, cidade, grafo, caminhoDoArquivoDeSaida, prefixoDoArquivoDeSaida, 0);
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
        else if(strcmp(comando, "qr")==0 || strcmp(comando, "qc")==0){
            if(strcmp(comando, "qc")==0)
                modo = 1;
            else
                modo = 2;
            scanf("%s", nomeDoArquivoQry);
            char* prefixoDoArquivoDeSaida = (char *) malloc((strlen(caminhoDoArquivoDeSaida)+strlen(prefixoDoArquivoGeo)+6)*sizeof(char));
            sprintf(prefixoDoArquivoDeSaida, "%s/%s", caminhoDoArquivoDeSaida, prefixoDoArquivoGeo);

            prefixoFinalDoArquivoQry = (char *) malloc((strlen(caminhoDoArquivoDeSaida)+strlen(prefixoDoArquivoGeo)+6+strlen(retornarPrefixoDoArquivo(nomeDoArquivoQry)))*sizeof(char));
            sprintf(prefixoFinalDoArquivoQry, "%s/%s-%s", caminhoDoArquivoDeSaida, prefixoDoArquivoGeo, retornarPrefixoDoArquivo(nomeDoArquivoQry));
            Ponto *R = leiaQry(caminhoDoArquivo, prefixoFinalDoArquivoQry, nomeDoArquivoQry, cidade, grafo, caminhoDoArquivoDeSaida, prefixoDoArquivoDeSaida, 1);

            char corMaisCurto[20];
            char corMaisRapido[20];
            char registrador1[4];
            char registrador2[4];
            char sufixoDoArquivo[100];
            FILE* arquivoQry = fopen(nomeDoArquivoQry, "a+");
                
            while(1){
                fscanf(arquivoQry, "%s", sufixoDoArquivo);
                if(strcmp(sufixoDoArquivo, "p?") == 0)
                    break;
            }   

            fscanf(arquivoQry, " %s %s %s %s %s", sufixoDoArquivo, registrador1, registrador2, corMaisCurto, corMaisRapido);
            fclose(arquivoQry);
            int index1 = atoi(registrador1+1);
            int index2 = atoi(registrador2+1);

            char* direcao;
            int* caminho;

            caminho = dijkstra(grafo, retornaIndiceVertice(getLista(grafo), getPontoX(R[index1]), getPontoY(R[index1])), retornaIndiceVertice(getLista(grafo), getPontoX(R[index2]), getPontoY(R[index2])), "removivel.svg", "removivel.txt", corMaisCurto, corMaisRapido, modo);
            auxilioDirecao(grafo, caminho, modo, retornaIndiceVertice(getLista(grafo), getPontoX(R[index2]), getPontoY(R[index2])));
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
	Cidade cidade = leiaGeo(arquivoGeo, nomeDoArquivoSvg);
    Graph* grafo;
    if(arquivoVia != NULL){
        grafo = leiaVia(arquivoVia);
    }

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

        leiaQry(caminhoDoArquivo, prefixoFinalDoQry, arquivoQry, cidade, grafo, caminhoDoArquivoDeSaida, prefixoDoArquivoDeSaida, 0);

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
        resolverInterativos(cidade, caminhoDoArquivoDeSaida, prefixoDoArquivoGeo, caminhoDoArquivo, arquivoVia);
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
    remove("tempFile.txt");
    
    return 0;
}
