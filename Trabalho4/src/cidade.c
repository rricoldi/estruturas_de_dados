#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "cidade.h"
#include"comercioPessoas.h"

#include"leitura.h"

typedef struct city
{
    // Tree arvoreCirculo;
    Tree arvoreMuro;
    HashTable pessoas_cpf;          //key: CPF da pessoa
    HashTable moradiaPessoa_cep;    //key: CEP da quadra
    HashTable moradias_cpf;         //key: CPF do morador
    HashTable tiposComercio_tipo;   //key: tipo do comercio
    HashTable comercios_cnpj;       //key: CNPJ do estabelecimento
    HashTable circulo_id;
    HashTable retangulo_id;
    HashTable quadra_cep;
    HashTable hidrante_id;
    HashTable radio_id;
    HashTable semaforo_id;
    HashTable predio_cep;
    Tree arvoreCirculo;
    Tree arvoreRetangulo;
    Tree arvoreQuadra;
    Tree arvoreHidrante;
    Tree arvoreRadio;
    Tree arvoreSemaforo;
    Tree arvorePredio;
    Lista listaCirculo;
    Lista listaRetangulo;
    Lista listaQuadra;
    Lista listaHidrante;
    Lista listaRadio;
    Lista listaSemaforo;
    Lista listaPredio;
    Lista listaMuro;
} cidade;

Cidade criarCidade()
{
    Cidade cid    = calloc(1, sizeof(cidade));
    cidade *city  = (cidade *)  cid;
    
    city->arvoreCirculo = criaArvore(comparaCirculo);
    city->arvoreRetangulo = criaArvore(comparaRetangulo);
    city->arvoreQuadra = criaArvore(comparaQuadra);
    city->arvoreHidrante = criaArvore(comparaHidrante);
    city->arvoreRadio = criaArvore(comparaRadio);
    city->arvoreSemaforo = criaArvore(comparaSemaforo);
    city->arvoreMuro = criaArvore(comparaMuro);
    city->arvorePredio = criaArvore(comparaPredio);
    city->circulo_id = criaTabela(997);
    city->retangulo_id = criaTabela(997);
    city->quadra_cep = criaTabela(997);
    city->hidrante_id = criaTabela(997);
    city->radio_id = criaTabela(997);
    city->semaforo_id = criaTabela(997);
    city->predio_cep = criaTabela(997);
    city->pessoas_cpf = NULL;
    city->moradiaPessoa_cep = NULL;
    city->moradias_cpf = NULL;
    city->tiposComercio_tipo = NULL;
    city->comercios_cnpj = NULL;

    return city;
}

// void imprimeCity(Cidade cid)
// {
//     cidade *city = (cidade *)cid;
//     percorreArvore(city->arvoreCirculo, imprime);
// }

void iniciaComercios(Cidade cidade, char* arquivoEc){
    struct city *essa = (struct city*) cidade;
    essa->tiposComercio_tipo = criaTabela(97);
    essa->comercios_cnpj = criaTabela(97);
    leiaEc(arquivoEc, essa->comercios_cnpj, essa->tiposComercio_tipo);
}
void iniciaPessoas(Cidade cidade, char* arquivoPm){
    struct city *essa = (struct city*) cidade;
    essa->pessoas_cpf = criaTabela(97);
    essa->moradiaPessoa_cep = criaTabela(97);
    essa->moradias_cpf = criaTabela(97);
    leiaPm(arquivoPm, essa->pessoas_cpf, essa->moradias_cpf, essa->moradiaPessoa_cep);
}

void removeCidade(Cidade cid)
{
    cidade *city = (cidade *)cid;
    desalocaArvore(city->arvoreCirculo);
    desalocaArvore(city->arvoreRetangulo);
    desalocaArvore(city->arvoreQuadra);
    desalocaArvore(city->arvoreHidrante);
    desalocaArvore(city->arvoreSemaforo);
    desalocaArvore(city->arvoreRadio);
    desalocaArvore(city->arvoreMuro);
    desalocaArvore(city->arvorePredio);
    free(city);
}

void boudingBoxCirculos(Cidade cid, char arquivo[])
{
    cidade *city = (cidade *)cid;
    bbcLista(city->listaCirculo, arquivo);
}

void boundingBoxRetangulos(Cidade cid, char arquivo[], char cor[])
{
    cidade *city = (cidade *)cid;
    bbrLista(city->listaRetangulo, arquivo, cor);
}

void imprimeCirculosERetangulos(Cidade cid, char nomeDoArquivoSvg[])
{
    cidade *city = (cidade *)cid;
    
    imprimeCirculos(city->listaCirculo, nomeDoArquivoSvg);
    imprimeRetangulos(city->listaRetangulo, nomeDoArquivoSvg);
}

void imprimeCidade(Cidade cid, char nomeDoArquivoSvg[])
{
    cidade *city = (cidade *)cid;
 
    imprimeQuadras(city->listaQuadra, nomeDoArquivoSvg);
    imprimeHidrantes(city->listaHidrante, nomeDoArquivoSvg);
    imprimeSemaforos(city->listaSemaforo, nomeDoArquivoSvg);
    imprimeRadios(city->listaRadio, nomeDoArquivoSvg);
    if(lenght(city->listaPredio) > 0)
        imprimePredios(city->listaPredio, nomeDoArquivoSvg);
    if(lenght(city->listaMuro) > 0)
        imprimeMuros(city->listaMuro, nomeDoArquivoSvg);
}

Info procuraNaCidade(Cidade cid, char id[], int *tipo, char face[], double num)
{
    cidade *city = (cidade *)cid;
    int posicao;
    posicao = procuraCirculo(city->listaCirculo, id);
    if (posicao != -1)
    {
        *tipo = 1;
        return get(city->listaCirculo, posicao);
    }
    posicao = procuraRetangulo(city->listaRetangulo, id);
    if (posicao != -1)
    {
        *tipo = 2;
        return get(city->listaRetangulo, posicao);
    }
    posicao = procuraQuadra(city->listaQuadra, id);
    if (posicao != -1)
    {
        *tipo = 3;
        return get(city->listaQuadra, posicao);
    }

    posicao = procuraHidrante(city->listaHidrante, id);
    if (posicao != -1)
    {
        *tipo = 4;
        return get(city->listaHidrante, posicao);
    }

    posicao = procuraSemaforo(city->listaSemaforo, id);
    if (posicao != -1)
    {
        *tipo = 5;
        return get(city->listaSemaforo, posicao);
    }

    posicao = procuraRadio(city->listaRadio, id);
    if (posicao != -1)
    {
        *tipo = 6;
        return get(city->listaRadio, posicao);
    }

    posicao = procuraPredio(city->listaPredio, id, face, num);
    if (posicao != -1)
    {
        *tipo = 7;
        return get(city->listaPredio, posicao);
    }

    printf("Nao foi possivel achar o elemento na cidade\n");
    return NULL;
}

void removeDaCidade(Cidade cid, char id[], char txt[])
{
    FILE *arqTxt;
    arqTxt = fopen(txt, "a");

    cidade *city = (cidade *)cid;
    int posicao;

    posicao = procuraQuadra(city->listaQuadra, id);
    if (posicao != -1)
    {
        fprintf(arqTxt, "del %s\nquadra -> x: %lf y: %lf w: %lf h: %lf\n", id, retornaQX(getQuadra(city, posicao)), retornaQY(getQuadra(city, posicao)), retornaQW(getQuadra(city, posicao)), retornaQH(getQuadra(city, posicao)));
        removerDaLista(city->listaQuadra, posicao);
        fclose(arqTxt);
        return;
    }

    posicao = procuraHidrante(city->listaHidrante, id);
    if (posicao != -1)
    {
        fprintf(arqTxt, "del %s\nhidrante -> x: %lf y: %lf\n", id, retornaHX(getHidrante(city, posicao)), retornaHY(getHidrante(city, posicao)));
        removerDaLista(city->listaHidrante, posicao);
        fclose(arqTxt);
        return;
    }

    posicao = procuraSemaforo(city->listaSemaforo, id);
    if (posicao != -1)
    {
        fprintf(arqTxt, "del %s\nsemaforo -> x: %lf y: %lf\n", id, retornaSX(getSemaforo(city, posicao)), retornaSY(getSemaforo(city, posicao)));
        removerDaLista(city->listaHidrante, posicao);
        fclose(arqTxt);
        return;
    }

    posicao = procuraRadio(city->listaRadio, id);
    if (posicao != -1)
    {
        fprintf(arqTxt, "del %s\nradio base -> x: %lf y: %lf\n", id, retornaRX(getRadio(city, posicao)), retornaRY(getRadio(city, posicao)));
        removerDaLista(city->listaHidrante, posicao);
        fclose(arqTxt);
        return;
    }

    printf("Nao foi possivel achar o elemento na cidade\n");
    fclose(arqTxt);
    return;
}

void adicionarCirculo(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    insereRegistro(city->circulo_id, retornaCID(info), info);
    return insereNaArvore(&(city->arvoreCirculo), info);
}


Circulo getCirculo(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaCirculo, i);
}

void adicionarRetangulo(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    insereRegistro(city->retangulo_id, retornaReID(info), info);
    return insereNaArvore(&(city->arvoreRetangulo), info);
}

Retangulo getRetangulo(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaRetangulo, i);
}

void adicionarQuadra(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    insereRegistro(city->quadra_cep, retornaQCEP(info), info);
    return insereNaArvore(&(city->arvoreQuadra), info);
}

Quadra getQuadra(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaQuadra, i);
}

void adicionarHidrante(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    insereRegistro(city->hidrante_id, retornaHID(info), info);
    return insereNaArvore(&(city->arvoreHidrante), info);
}

Hidrante getHidrante(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaHidrante, i);
}

void adicionarRadioBase(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    insereRegistro(city->radio_id, retornaCID(info), info);
    return insereNaArvore(&(city->arvoreRadio), info);
}

Radio getRadio(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaRadio, i);
}

void adicionarSemaforo(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    insereRegistro(city->semaforo_id, retornaSID(info), info);
    return insereNaArvore(&(city->arvoreSemaforo), info);
}

Semaforo getSemaforo(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaSemaforo, i);
}


void adicionarPredio(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    insereRegistro(city->predio_cep, retornaPCep(info), info);
    return insereNaArvore(&(city->arvorePredio), info);
}

Predio getPredio(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaPredio, i);
}

void adicionarMuro(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereNaArvore(&(city->arvoreMuro), info);
}

Muro getMuro(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaMuro, i);
}


void percorreCidade(Cidade cid, double r, double fx, double fy, char tipo[], char svg[], char txt[], char id[], int option, char cor[], double largura, double altura, double dx, double dy)
{
    cidade *city = (cidade *)cid;
    if (option == 1 || option == 2)
        percorreListaQ(city->listaQuadra, r, fx, fy, tipo, svg, txt, id, option, cor, largura, altura, dx, dy);
    else
    {
        percorreListaQ(city->listaQuadra, r, fx, fy, tipo, svg, txt, id, option, cor, largura, altura, dx, dy);
        percorreListaH(city->listaHidrante, fx, fy, largura, altura, dx, dy, txt);
        percorreListaS(city->listaSemaforo, fx, fy, largura, altura, dx, dy, txt);
        percorreListaR(city->listaRadio, fx, fy, largura, altura, dx, dy, txt);
    }
}

void resolveIncendios(Cidade cid, double x, double y, double raio, int numeroDeSemaforos, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[])
{
    cidade *city = (cidade *)cid;

    char comando[] = "fi";
    resolveSemaforos(city->listaSemaforo, x, y, numeroDeSemaforos, nomeDoArquivoSvg, nomeDoArquivoTxt, comando);
    int xa = 1 + 1;
    resolveHidrantes(city->listaHidrante, x, y, raio, nomeDoArquivoSvg, nomeDoArquivoTxt);
        
}

void resolveFH(Cidade cid, Info quadra, int numeroDeHidrantes, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[])
{
    cidade *city = (cidade*) cid;
    double x = (retornaQX(quadra) + retornaQW(quadra)) / 2;
    double y = (retornaQY(quadra) + retornaQH(quadra)) / 2;
    int sinal;
    if ( numeroDeHidrantes < 0)
    {
        sinal = 0;
        numeroDeHidrantes = -numeroDeHidrantes;
    }
    else
    {
        sinal = 1;
    }
    
    
    resolveFHidrantes(city->listaHidrante, x, y, numeroDeHidrantes, sinal, nomeDoArquivoSvg, nomeDoArquivoTxt);
}

void resolveFS(Cidade cid, Info quadra, int numeroDeSemaforos, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[])
{
    cidade *city = (cidade*) cid;
    char comando[] = "fs";
    double x = (retornaQX(quadra) + retornaQW(quadra)) / 2;
    double y = (retornaQY(quadra) + retornaQH(quadra)) / 2;

    resolveSemaforos(city->listaSemaforo, x, y, numeroDeSemaforos, nomeDoArquivoSvg, nomeDoArquivoTxt, comando);
}

void qry_m(FILE* arquivoTxt, char cep[], Cidade cid){
    int tamanhoVetorInfo;
    Info* vetorCpfs;
    cidade *city = (cidade*)cid;

    vetorCpfs = getVetorRegistros(city->moradiaPessoa_cep, cep, &tamanhoVetorInfo);
    fprintf(arquivoTxt, "m? cep: %s\n", cep);
    for(int i=0;i<tamanhoVetorInfo;i++){
        fprintf(arquivoTxt, " -cpf: %s\n", vetorCpfs[i]);
        Pessoa pes = getPrimeiroRegistro(city->pessoas_cpf, vetorCpfs[i]);
        Moradia mor = getPrimeiroRegistro(city->moradias_cpf, vetorCpfs[i]);

        if(pes == NULL){
            fprintf(arquivoTxt, "  .Pessoa não encontrada\n");
        }else{
            fprintf(arquivoTxt, "  .%s %s, %c, %s\n", pessoaGetNome(pes), pessoaGetSobrenome(pes), pessoaGetSexo(pes), pessoaGetNascimento(pes));
        }
        if(mor == NULL){
            fprintf(arquivoTxt, "  .Casa da pessoa não encontrada\n");
        }else{
            fprintf(arquivoTxt, "  .%s, %c, %d, %s\n", moradiaGetCep(mor), moradiaGetFace(mor), moradiaGetNum(mor), moradiaGetComplemento(mor));
        }
    }
    fprintf(arquivoTxt, "\n");
}