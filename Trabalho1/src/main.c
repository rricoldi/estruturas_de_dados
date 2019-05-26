#include "struct.h"
#include "svg.h"
#include "qry.h"
#include "leitura.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


char *tratamento(char arqNome[]){

    int i,x,y;
    char *prefixo, caractere;

    for(i=strlen(arqNome);i>=0;i--) {
		caractere = arqNome[i];
        //analiza se o caractere pego é igual a '/'
        if(caractere=='/') {
        //caso for acrescenta um a i pois o path[i] sera a posição de / e quermos pegar o proximo
			y = strlen(arqNome)-i;
        	prefixo = (char*) malloc(y*sizeof(char));

        	for(x=0;x<=y;x++){
            	prefixo[x] = arqNome[i+1];
            	i++; 
        	}  
			return strtok(prefixo,".");
        }        
    }
	return strtok(arqNome,".");
}


int main(int argc, char *argv[])
{
	No *inicio;
	inicio = iniciar();

    int i = 1;

    char *geoNome = NULL;
    char *path = NULL;
    char *consulta = NULL;
    char *outpath = NULL;
    char *geoArq = NULL;
    char *prefixoGeo = NULL;
    char *prefixoQry = NULL;
	char *prefixoArq = NULL;
    char *svg = NULL;
    char *consultaArq = NULL;

    while(i<argc){
        if (strcmp("-f",argv[i])==0){ //proximo argumento deve ser nome do arquivos
            i++;

            if (argv[i] == NULL){ //se n?o existir pr?ximo parametro: ERRO!
                printf("\n!Erro! Sem parametros em -f");
                exit(1);
            }

            geoNome = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(geoNome,argv[i]);
        }
        else if (strcmp("-e",argv[i])==0){ //proximo argumento deve ser o nome do caminho
            i++;

            if (argv[i] == NULL){ //se n?o existir pr?ximo parametro: ERRO!
                printf("\n!Erro! Sem parametros em -e");
                exit(1);
            }

            path = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(path,argv[i]);
        }
        else if (strcmp("-q",argv[i])==0){ //proximo argumento deve ser um arquivo de consultas
            i++;

            if (argv[i] == NULL){ //se n?o existir pr?ximo parametro: ERRO!
                printf("\n!Erro! Sem parametros em -q");
                exit(1);
            }

            consulta = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(consulta,argv[i]);
        }
        else if (strcmp("-o",argv[i])==0){ //proximo argumento deve ser o nome do diret?rio
            i++;

            if (argv[i] == NULL){ //se n?o existir pr?ximo parametro: ERRO!
                printf("\n!Erro! Sem parametros em -o");
                exit(1);
            }

            outpath = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(outpath,argv[i]);
        }

        i++;
    }

	if (path != NULL) {
		geoArq = (char *)malloc((strlen(geoNome)+strlen(path)+2)*sizeof(char));
    	sprintf(geoArq,"%s/%s",path,geoNome);

    	consultaArq = (char *)malloc((strlen(consulta)+strlen(path)+2)*sizeof(char));
    	sprintf(consultaArq,"%s/%s",path,consulta);
	} else {
		geoArq = (char *)malloc((strlen(geoNome)+1)*sizeof(char));
    	sprintf(geoArq, geoNome);

    	consultaArq = (char *)malloc((strlen(consulta)+1)*sizeof(char));
    	strcpy(consultaArq, consulta);
	}

	prefixoGeo = (char *) malloc((strlen(geoNome)+1)*sizeof(char));	
    prefixoGeo = tratamento(geoNome);    
	
    prefixoQry = (char *) malloc((strlen(consulta)+1)*sizeof(char));
    prefixoQry = tratamento(consulta);
    
	svg = (char *)malloc((strlen(outpath)+strlen(prefixoGeo)+6)*sizeof(char));
    sprintf(svg, "%s/%s.svg", outpath, prefixoGeo);

    printf("Bloco do Geo inicializado\n");
	inicio = leiaGeo(geoArq, inicio, svg);
    printf("Bloco do Geo finalizado\n");
	
	prefixoArq = (char *) malloc((strlen(svg)+strlen(prefixoQry)-6)*sizeof(char));	
	sprintf(prefixoArq, "%s/%s-%s", outpath, prefixoGeo, prefixoQry);

    printf("Bloco do Qry inicializado\n");
    leiaQry(prefixoArq, consultaArq, inicio);
	printf("Bloco do Qry finalizado\n");

	desalocar(inicio);
	printf("Lista desalocada\n");

	free(geoArq);
	free(geoNome);
    free(path);
	free(outpath);
    free(consulta);
    free(consultaArq);
	free(prefixoGeo);
    free(prefixoQry);
    free(prefixoArq);  
    free(svg);
    printf("Mémoria desalocada\n");
    
    return 0;
}
