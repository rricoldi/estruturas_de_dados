#include "leitura.h"
#include "struct.h"
#include "qry.h"
#include "lista.h"
#include "svg.h"

No *leiaGeo(char arq[], No *inicio, char svg[]){
    FILE *geo;
    geo = fopen(arq, "r");

    if (geo == NULL){ //caso n?o abra o arquivo: ERRO!
        printf("Nao foi possivel Abrir o arquivo geo\n");
        exit(1);
    }
	printf("Arquivo Geo foi aberto\n");
	
    int nummax = 1000;
    char comando[3];
    char *texto;
    int i = 0;
    int id;
	float x, y, altura, largura, raio;
	char cor1[20], cor2[20];
    size_t bufsize = 32;
    
    iniciaSvg(svg);
	printf("svg inicializado\n");

    while(i<nummax){	

		fscanf(geo,"%s", comando);
		if (feof(geo))
	        	break;
       
	    if (strcmp("nx",comando)==0){ //proximo argumento deve ser n?mero m?ximo de c?rculos e ret?ngulos         
			fscanf(geo,"%d", &nummax);
        }
        else if (strcmp("c",comando)==0){ //proximo argumento deve ser os par?metros          
			fscanf(geo,"%d %f %f %f %s %s", &id, &raio, &x, &y, &cor1, &cor2);
            	
			inicio = inserir(inicio, id, raio, x, y, 0, 0, cor1, cor2, 'c');
		
            	criaCirculo(raio, x, y, cor1, cor2, svg);
            	i++;
        }
        else if (strcmp("r",comando)==0){ //proximo argumento deve ser os par?metros
            fscanf(geo,"%d %f %f %f %f %s %s", &id, &largura, &altura, &x, &y, &cor1, &cor2);
            
            inicio = inserir(inicio, id, 0, x, y, altura, largura, cor1, cor2, 'r');
            criaRetangulo(largura, altura, x, y, cor1, cor2, svg);
            i++;
        }
        else if (strcmp("t",comando)==0){ //proximo argumento deve ser os par?metros
            fscanf(geo,"%f %f", &x, &y);
	
	    	texto = (char *)malloc(bufsize * sizeof(char));

            getline(&texto, &bufsize, geo);
	    	escreveSvg(x, y, strtok(texto,"\n"), svg);
			free(texto);
		}
    }
	
	finalizaSvg(svg);
	printf("svg finalizado\n");

    fclose(geo);
	printf("Arquivo Geo foi fechado\n");

	return inicio;
}

void leiaQry(char prefixoArq[], char arq[], No *inicio){
	FILE *qry;		
	qry = fopen(arq,"r");
	if(qry == NULL){
		printf("erro ao tentar abrir o arquivo qry!\n");
		exit(1);
	}
	printf("Arquivo Qry foi aberto\n");

	No *Np1, *Np2;
	par *par1, *par2;

	int j, k;
	float x, y;
    char comando[4];
    char sufixo[20];
    char cor[20];

    char *svg = (char*) malloc((strlen(prefixoArq)+5)*sizeof(char));
    sprintf(svg,"%s.svg", prefixoArq);

	iniciaSvg(svg);
	printf("svg incializa do\n");

    No *lista;
    lista = inicio;

    par *par;
    
	FILE *arqout;
    arqout = fopen(svg, "w");
    fprintf(arqout, "<svg>");

    while(lista != NULL){
    	par = lista->par;
    	if (par->type == 'c'){
    	    fprintf(arqout, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />", par->x, par->y, par->raio, par->cor1, par->cor2);
    	}
    	else if (par->type == 'r'){
    	    fprintf(arqout, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke:%s\" />", par->x, par->y, par->largura, par->altura, par->cor2, par->cor1);
    	}

	    lista = lista->prox;
    }

   fclose(arqout);
    
	char *txt = (char*) malloc((strlen(prefixoArq)+5)*sizeof(char));
    sprintf(txt,"%s.txt", prefixoArq);

	FILE *texto;
	texto = fopen(txt, "w");
	if (texto == NULL)
		printf("ERRO AO CRIAR TXT\n");
	fclose(texto);

    while(1){
		fscanf(qry,"%s", comando);
	
		if (feof(qry))
        	break;
       
	    if (strcmp("o?",comando)==0){ //proximo argumento deve ser n?mero m?ximo de c?rculos e ret?ngulos
        	fscanf(qry, "%d %d", &j, &k);

			Np1 = buscar(inicio, j);
            Np2 = buscar(inicio, k);
			
			par1 = Np1->par;
			par2 = Np2->par;
            
			if (par1->type == 'c' && par2->type == 'r') {
                colisaoCR(par1->x, par1->y, par1->raio, par2->x, par2->y, par2->largura, par2->altura, j, k, txt, svg);
            } else if (par1->type == 'r' && par2->type == 'c') {
                colisaoCR(par2->x, par2->y, par2->raio, par1->x, par1->y, par1->largura, par1->altura, j, k, txt, svg);
            } else if (par1->type == 'c' && par2->type == 'c') {
                colisaoCC(par1->x, par1->y, par1->raio, par2->x, par2->y, par2->raio, j, k, txt, svg);
            } else if (par1->type == 'r' && par2->type == 'r') {
                colisaoRR(par1->x, par1->y, par1->largura, par1->altura, par2->x, par2->y, par2->largura, par2->altura, j, k, txt, svg);
            }
		}
        else if (strcmp("i?",comando)==0){ //proximo argumento deve ser os par?metros
        	fscanf(qry, "%d %f %f", &j, &x, &y);

        	Np1 = buscar(inicio, j);
			par1 = Np1->par;

        	if (par1->type == 'c')
        	    pontoInternoCirculo(x, y, par1->x, par1->y, par1->raio, txt, j, svg);
		    else
		        pontoInternoQuadrado(x, y, par1->x, par1->y, par1->altura, par1->largura, txt, par1->id, svg);
        }
        else if (strcmp("d?",comando)==0){ //proximo argumento deve ser os par?metros
			fscanf(qry, "%d %d", &j, &k);

            Np1 = buscar(inicio, j);
            Np2 = buscar(inicio, k);

			par1 = Np1->par;
			par2 = Np2->par;

            distanciaFig(par1->x, par1->y, par2->x, par2->y, txt, svg, j, k);
        }
        else if (strcmp("bb",comando)==0){ //proximo argumento deve ser os par?metros
            fscanf(qry, " %s %s", &sufixo, &cor);

            boundingBox(cor, prefixoArq, sufixo, inicio);
        } 
    }
    finalizaSvg(svg);
	printf("svg finalizado\n");

    free(txt);

    fclose(qry);
	printf("O arquivo Qry foi fechado\n");
}
