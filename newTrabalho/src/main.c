#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cidade.h"
#include "leitura.h"

char *retornarPrefixoDoArquivo(char nomeDoArquivo[])
{
    char *prefixo, caractere;
    int contador, contador2;
    int posicao;

    for(contador = strlen(nomeDoArquivo) - 1; contador >= 0; contador --) {
		caractere = nomeDoArquivo[contador];
        
        if(caractere == '/') {
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

int main(int argc, char *argv[])
{
    int contador                  = 1;

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
    
    while(contador<argc)
    {
        if (strcmp("-f",argv[contador])==0){ 
            if (argv[contador] == NULL){
                printf("\n!Erro! Sem parametros em -f");
                exit(1);
            }

            nomeDoArquivoGeo = (char *)malloc((strlen(argv[contador])+1)*sizeof(char));
            strcpy(nomeDoArquivoGeo,argv[contador]);
            contador++;
        }
        else if (strcmp("-e",argv[contador])==0){ 
           if (argv[contador] == NULL){ 
                printf("\n!Erro! Sem parametros em -e");
                exit(1);
            }

            caminhoDoArquivo = (char *)malloc((strlen(argv[contador])+1)*sizeof(char));
            strcpy(caminhoDoArquivo,argv[contador]);
            contador++;
        }
        else if (strcmp("-q",argv[contador])==0){ 
            if (argv[contador] == NULL){ 
                printf("\n!Erro! Sem parametros em -q");
                exit(1);
            }

            nomeDoArquivoQry = (char *)malloc((strlen(argv[contador])+1)*sizeof(char));
            strcpy(nomeDoArquivoQry,argv[contador]);
            contador++;
        }
        else if (strcmp("-o",argv[contador])==0){ 
            if (argv[contador] == NULL){    
                printf("\n!Erro! Sem parametros em -o");
                exit(1);
            }

            caminhoDoArquivoDeSaida = (char *)malloc((strlen(argv[contador])+1)*sizeof(char));
            strcpy(caminhoDoArquivoDeSaida,argv[contador]);
            contador++;
        }
        contador++;
    }


	if (caminhoDoArquivo != NULL)
    {
		arquivoGeo = (char *)malloc((strlen(nomeDoArquivoGeo)+strlen(caminhoDoArquivo)+2)*sizeof(char));
    	sprintf(arquivoGeo,"%s/%s",caminhoDoArquivo,nomeDoArquivoGeo);


    	arquivoQry = (char *)malloc((strlen(nomeDoArquivoQry)+strlen(caminhoDoArquivo)+2)*sizeof(char));
    	sprintf(arquivoQry,"%s/%s",caminhoDoArquivo,nomeDoArquivoQry);
	}
    else
    {
		arquivoGeo = (char *)malloc((strlen(nomeDoArquivoGeo)+1)*sizeof(char));
    	sprintf(arquivoGeo, nomeDoArquivoGeo);


    	arquivoQry = (char *)malloc((strlen(nomeDoArquivoQry)+1)*sizeof(char));
    	strcpy(arquivoQry, nomeDoArquivoQry);
	}

	prefixoDoArquivoGeo = (char *) malloc((strlen(nomeDoArquivoGeo)+1)*sizeof(char));	
    prefixoDoArquivoGeo = retornarPrefixoDoArquivo(nomeDoArquivoGeo);

    if(nomeDoArquivoQry != NULL)
    {
        prefixoDoAquivoQry = (char *) malloc((strlen(nomeDoArquivoQry)+1)*sizeof(char));
        prefixoDoAquivoQry = retornarPrefixoDoArquivo(nomeDoArquivoQry);
    }
	 
	nomeDoArquivoSvg = (char *)malloc((strlen(caminhoDoArquivoDeSaida)+strlen(prefixoDoArquivoGeo)+6)*sizeof(char));
    sprintf(nomeDoArquivoSvg, "%s/%s.nomeDoArquivoSvg", caminhoDoArquivoDeSaida, prefixoDoArquivoGeo);

    //BLOCO QUE RESOLVE O GEO
    printf("Bloco do Geo inicializado\n");
	Cidade cidade = leiaGeo(arquivoGeo, nomeDoArquivoSvg);
    printf("Bloco do Geo finalizado\n");


	if(nomeDoArquivoQry != NULL)
    {
        //ARRUMA O PREFIXO DO NOME DO ARQUIVO QRY
    	prefixoFinalDoQry = (char *) malloc((strlen(nomeDoArquivoSvg)+strlen(prefixoDoAquivoQry)+6)*sizeof(char));	
	    sprintf(prefixoFinalDoQry, "%s/%s-%s", caminhoDoArquivoDeSaida, prefixoDoArquivoGeo, prefixoDoAquivoQry);

        printf("Bloco do Qry inicializado\n");
        leiaQry(prefixoFinalDoQry, arquivoQry, cidade);
	    printf("Bloco do Qry finalizado\n");
        
        free(nomeDoArquivoQry);
        free(prefixoDoAquivoQry);
        free(prefixoFinalDoQry); 
    }
        
    removeCidade(cidade);
	printf("Lista desalocada\n");

	free(arquivoGeo);
	free(nomeDoArquivoGeo);
    free(caminhoDoArquivo);
	free(caminhoDoArquivoDeSaida);
    free(arquivoQry);    
    free(nomeDoArquivoSvg);
    printf("Mémoria desalocada\n");
    
    return 0;
}