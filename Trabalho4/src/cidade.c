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
    HashTable comercios_cpf;
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
    city->comercios_cpf = NULL;

    return city;
}

// void imprimeCity(Cidade cid)
// {
//     cidade *city = (cidade *)cid;
//     percorreArvore(city->arvoreCirculo, imprime);
// }

void iniciaComercios(Cidade cid, char* arquivoEc){
    cidade *city = (cidade *)cid;
    city->tiposComercio_tipo = criaTabela(97);
    city->comercios_cnpj = criaTabela(97);
    city->comercios_cpf = criaTabela(97);
    leiaEc(arquivoEc, city->comercios_cnpj, city->tiposComercio_tipo, city->comercios_cpf);
}
void iniciaPessoas(Cidade cid, char* arquivoPm){
    cidade *city = (cidade *)cid;
    city->pessoas_cpf = criaTabela(97);
    city->moradiaPessoa_cep = criaTabela(97);
    city->moradias_cpf = criaTabela(97);
    leiaPm(arquivoPm, city->pessoas_cpf, city->moradias_cpf, city->moradiaPessoa_cep);
}

void removeCidade(Cidade cid)
{
    cidade *city = (cidade *)cid;

    percorreArvore(city->arvoreCirculo, circuloFinalizar);
    percorreArvore(city->arvoreHidrante, hidranteFinalizar);
    percorreArvore(city->arvoreMuro, muroFinalizar);
    percorreArvore(city->arvorePredio, predioFinalizar);
    percorreArvore(city->arvoreQuadra, quadraFinalizar);
    percorreArvore(city->arvoreRadio, radioBaseFinalizar);
    percorreArvore(city->arvoreRetangulo, retanguloFinalizar);
    percorreArvore(city->arvoreSemaforo, semaforoFinalizar);
    desalocaArvore(city->arvoreCirculo);
    desalocaArvore(city->arvoreRetangulo);
    desalocaArvore(city->arvoreQuadra);
    desalocaArvore(city->arvoreHidrante);
    desalocaArvore(city->arvoreSemaforo);
    desalocaArvore(city->arvoreRadio);
    desalocaArvore(city->arvoreMuro);
    desalocaArvore(city->arvorePredio);
    if(city->tiposComercio_tipo){
        HshTblMap(city->tiposComercio_tipo, comercioFinalizar);
        HshTblMap(city->comercios_cnpj, estabelecimentoFinalizar);
    }
    if(city->pessoas_cpf){
        HshTblMap(city->pessoas_cpf, pessoaFinalizar);
        HshTblMap(city->moradias_cpf, moradiaFinalizar);
        HshTblMap(city->moradiaPessoa_cep, free);
    }
    hashtableFinalizar(city->circulo_id);
    hashtableFinalizar(city->retangulo_id);
    hashtableFinalizar(city->quadra_cep);
    hashtableFinalizar(city->hidrante_id);
    hashtableFinalizar(city->radio_id);
    hashtableFinalizar(city->semaforo_id);
    hashtableFinalizar(city->predio_cep);
    hashtableFinalizar(city->moradiaPessoa_cep);
    hashtableFinalizar(city->pessoas_cpf);
    hashtableFinalizar(city->moradias_cpf);
    hashtableFinalizar(city->tiposComercio_tipo);
    hashtableFinalizar(city->comercios_cnpj);
    free(city);
}

void imprimeRetangulos(Info info, char nomeDoArquivoSvg[], char cor[])
{
    Retangulo retangulo = info;
    imprimirRetangulo(retornaReW(retangulo), retornaReH(retangulo), retornaReX(retangulo), retornaReY(retangulo), retornaReCorB(retangulo), retornaReCorP(retangulo), nomeDoArquivoSvg, retornaReEspessura(retangulo));
}

void imprimeCirculosERetangulos(Cidade cid, char nomeDoArquivoSvg[])
{
    cidade *city = (cidade *)cid;
    imprimeNoSvg(city->arvoreCirculo, imprimeCirculos, nomeDoArquivoSvg, " ");    
    imprimeNoSvg(city->arvoreRetangulo, imprimeRetangulos, nomeDoArquivoSvg, " ");
}

void imprimeBoundingBox(Cidade cid, char nomeDoArquivoSvg[], char cor[])
{
    cidade *city = (cidade *)cid;
    imprimeNoSvg(city->arvoreCirculo, boundingBoxCirculos, nomeDoArquivoSvg, cor);
    imprimeNoSvg(city->arvoreRetangulo, boundingBoxRetangulos, nomeDoArquivoSvg, cor);
}

void imprimeCidade(Cidade cid, char nomeDoArquivoSvg[])
{
    cidade *city = (cidade *)cid;

    percorreArvore(city->arvoreQuadra, imprimirQuadra, nomeDoArquivoSvg);
 
    // imprimeQuadras(city->listaQuadra, nomeDoArquivoSvg);
    // imprimeHidrantes(city->listaHidrante, nomeDoArquivoSvg);
    // imprimeSemaforos(city->listaSemaforo, nomeDoArquivoSvg);
    // imprimeRadios(city->listaRadio, nomeDoArquivoSvg);
    // if(lenght(city->listaPredio) > 0)
    //     imprimePredios(city->listaPredio, nomeDoArquivoSvg);
    // if(lenght(city->listaMuro) > 0)
    //     imprimeMuros(city->listaMuro, nomeDoArquivoSvg);
}

Info procuraNaCidade(Cidade cid, char id[], int *tipo, char face[], double num)
{
    cidade *city = (cidade *)cid;
    Info info;
    info = getPrimeiroRegistro(city->circulo_id, id);
    if (info != NULL)
    {
        *tipo = 1;
        return info;
    }
    info = getPrimeiroRegistro(city->retangulo_id, id);
    if (info != NULL)
    {
        *tipo = 2;
        return info;
    }
    info = getPrimeiroRegistro(city->quadra_cep, id);
    if (info != NULL)
    {
        *tipo = 3;
        return info;
    }

    info = getPrimeiroRegistro(city->hidrante_id, id);
    if (info != NULL)
    {
        *tipo = 4;
        return info;
    }

    info = getPrimeiroRegistro(city->semaforo_id, id);
    if (info != NULL)
    {
        *tipo = 5;
        return info;
    }

    info = getPrimeiroRegistro(city->radio_id, id);
    if (info != NULL)
    {
        *tipo = 6;
        return info;
    }
    // int tamanho;
    // Info *infos = getVetorRegistros(city->predio_cep, id, &tamanho);
    // if (infos[0] != NULL)
    // {
    //     for(int i = 0; i < tamanho; i++)
    //     {
    //         if (retornaPFace(infos[i]) == face && retornaPNumero(infos[i]) == num)
    //         {
    //             *tipo = 7;
    //             return infos[i];
    //         }
            
    //     }
    // }

    printf("Nao foi possivel achar o elemento na cidade\n");
    return NULL;
}

void removeDaCidade(Cidade cid, char id[], char txt[])
{
    FILE *arqTxt;
    arqTxt = fopen(txt, "a");

    cidade *city = (cidade *)cid;
    Info info;

    info = getPrimeiroRegistro(city->quadra_cep, id);
    if (info != NULL)
    {
        fprintf(arqTxt, "del %s\nquadra -> x: %lf y: %lf w: %lf h: %lf\n", id, retornaQX(info), retornaQY(info), retornaQW(info), retornaQH(info));
        fclose(arqTxt);
        return;
    }

    info = getPrimeiroRegistro(city->quadra_cep, id);
    if (info != NULL)
    {
        fprintf(arqTxt, "del %s\nhidrante -> x: %lf y: %lf\n", id, retornaHX(info), retornaHY(info));
        fclose(arqTxt);
        return;
    }

    info = getPrimeiroRegistro(city->semaforo_id, id);
    if (info != NULL)
    {
        fprintf(arqTxt, "del %s\nsemaforo -> x: %lf y: %lf\n", id, retornaSX(info), retornaSY(info));
        fclose(arqTxt);
        return;
    }

    info = getPrimeiroRegistro(city->radio_id, id);
    if (info != NULL)
    {
        fprintf(arqTxt, "del %s\nradio base -> x: %lf y: %lf\n", id, retornaRX(info), retornaRY(info));
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
    insereNaArvore(&(city->arvoreCirculo), info);
}


Circulo getCirculo(Cidade cid, char id[])
{
    cidade *city = (cidade *)cid;
    return getPrimeiroRegistro(city->circulo_id, id);
}

void adicionarRetangulo(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    insereRegistro(city->retangulo_id, retornaReID(info), info);
    insereNaArvore(&(city->arvoreRetangulo), info);
}

Retangulo getRetangulo(Cidade cid, char id[])
{
    cidade *city = (cidade *)cid;
    return getPrimeiroRegistro(city->retangulo_id, id);
}

void adicionarQuadra(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    insereRegistro(city->quadra_cep, retornaQCEP(info), info);
    insereNaArvore(&(city->arvoreQuadra), info);
}

Quadra getQuadra(Cidade cid, char id[])
{
    cidade *city = (cidade *)cid;
    return getPrimeiroRegistro(city->quadra_cep, id);
}

void adicionarHidrante(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    insereRegistro(city->hidrante_id, retornaHID(info), info);
    insereNaArvore(&(city->arvoreHidrante), info);
}

Hidrante getHidrante(Cidade cid, char id[])
{
    cidade *city = (cidade *)cid;
    return getPrimeiroRegistro(city->hidrante_id, id); 
}

void adicionarRadioBase(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    insereRegistro(city->radio_id, retornaCID(info), info);
    insereNaArvore(&(city->arvoreRadio), info);
}

Radio getRadio(Cidade cid, char id[])
{
    cidade *city = (cidade *)cid;
    return getPrimeiroRegistro(city->radio_id, id);
}

void adicionarSemaforo(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    insereRegistro(city->semaforo_id, retornaSID(info), info);
    insereNaArvore(&(city->arvoreSemaforo), info);
}

Semaforo getSemaforo(Cidade cid, char id[])
{
    cidade *city = (cidade *)cid;
    return getPrimeiroRegistro(city->semaforo_id, id);
}


void adicionarPredio(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    insereRegistro(city->predio_cep, retornaPCep(info), info);
    insereNaArvore(&(city->arvorePredio), info);
}

Predio getPredio(Cidade cid, char id[])
{
    cidade *city = (cidade *)cid;
    return getPrimeiroRegistro(city->predio_cep, id);
}

void adicionarMuro(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    insereNaArvore(&(city->arvoreMuro), info);
}

Muro getMuro(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return;
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

    if(city->moradiaPessoa_cep == NULL){
        printf("ERRO: nenhum arquivo -pm foi informado\n");
    }

    vetorCpfs = getVetorRegistros(city->moradiaPessoa_cep, cep, &tamanhoVetorInfo);
    fprintf(arquivoTxt, "m? cep: %s\n", cep);

    if(tamanhoVetorInfo == 0){
        fprintf(arquivoTxt, " -Não há pessoas morando nesse cep");
        free(vetorCpfs);
        return;
    }

    for(int i=0;i<tamanhoVetorInfo;i++){
        fprintf(arquivoTxt, " -cpf: %s\n", (char*)vetorCpfs[i]);
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
    free(vetorCpfs);
    fprintf(arquivoTxt, "\n");
}
void qry_dm(FILE* arquivoTxt, char* cpf, Cidade cid){
    cidade* city = (cidade*)cid;
    Pessoa pes = getPrimeiroRegistro(city->pessoas_cpf, cpf);

    fprintf(arquivoTxt, "dm? cpf: %s\n", cpf);

    if(pes == NULL){
        fprintf(arquivoTxt, " -Pessoa não encontrada\n");
    }else{
        fprintf(arquivoTxt, " -%s %s, %c, %s\n", pessoaGetNome(pes), pessoaGetSobrenome(pes), pessoaGetSexo(pes), pessoaGetNascimento(pes));
    }

    Moradia mor = getPrimeiroRegistro(city->moradias_cpf, cpf);
    if(mor == NULL){
        fprintf(arquivoTxt, " -Endereço da pessoa não encontrado\n");
    }else{
        fprintf(arquivoTxt, " -%s, %c, %d, %s\n", moradiaGetCep(mor), moradiaGetFace(mor), moradiaGetNum(mor), moradiaGetComplemento(mor));
    }
    fprintf(arquivoTxt, "\n");
}
void qry_de(FILE* arquivoTxt, char* cnpj, Cidade cid){
    cidade *city = (cidade*)cid;
    EstabelecimentoComercial ec = getPrimeiroRegistro(city->comercios_cnpj, cnpj);
    Pessoa pes = NULL;

    fprintf(arquivoTxt, "de? cnpj: %s\n", cnpj);
    if(ec == NULL){
        fprintf(arquivoTxt, " -Estabelecimento não encontrado\n");
    }else{
        ComercioTipo ct = getPrimeiroRegistro(city->tiposComercio_tipo, estabelecimentoGetTipo(ec));
        fprintf(arquivoTxt, " -%s, %s, %s, %c, %d\n", estabelecimentoGetNome(ec), comercioGetDescricao(ct), estabelecimentoGetCep(ec),
                                                        estabelecimentoGetFace(ec), estabelecimentoGetNum(ec));
        pes = getPrimeiroRegistro(city->pessoas_cpf, estabelecimentoGetCpf(ec));
    }
    if(pes == NULL){
        fprintf(arquivoTxt, " -Proprietário (cpf %s) não encontrado\n", estabelecimentoGetCpf(ec));
    }else{
        fprintf(arquivoTxt, " -Propriedade de %s %s, %s\n", pessoaGetNome(pes), pessoaGetSobrenome(pes), pessoaGetCpf(pes));
    }
    fprintf(arquivoTxt, "\n");
}

void qry_dq_no(Node no, Info info, va_list args)
{
    va_list variaveis;
    va_copy(variaveis, args);
    Cidade cid = va_arg(variaveis, void*);
    double r = va_arg(variaveis, double);
    double fx = va_arg(variaveis, double);
    double fy = va_arg(variaveis, double);
    char *svg = va_arg(variaveis, char*);
    char *txt = va_arg(variaveis, char*);
    char *id = va_arg(variaveis, char*);
    char *metrica = va_arg(variaveis, char*);
    int tipo = va_arg(variaveis, int);
    cidade *city = (cidade*) cid;
    FILE *arqSvg, *arqTxt;
    arqSvg = fopen(svg,"a");
    arqTxt = fopen(txt, "a");

    if(strcmp("L1", metrica) == 0)
    {
        if(retornaDistanciaL1(r, fx, fy, retornaQX(info), retornaQY(info), retornaQW(info), retornaQH(info)))
        {
            fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"10\" stroke= \"black\" fill=\"none\" stroke-width=\"4\" stroke-oppacity=\"0.7\" />", fx, fy);
            fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"15\" stroke= \"yellow\" fill=\"none\" stroke-width=\"4\" stroke-oppacity=\"0.7\" />", fx, fy);
            fprintf(arqTxt, "cep: %s\n", retornaQCEP(info));
            quadraFinalizar(info);
            deletaDaArvore(city->arvoreQuadra, no);
            removeChave(city->quadra_cep, retornaQCEP(info));
        }
    }
    else if(strcmp("L2", metrica) == 0)
    {
        if(retornaDistanciaL2(r, fx, fy, retornaQX(info), retornaQY(info), retornaQW(info), retornaQH(info)))
        {
            fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"10\" stroke= \"black\" fill=\"none\" stroke-width=\"4\" stroke-oppacity=\"0.7\" />", fx, fy);
            fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"15\" stroke= \"yellow\" fill=\"none\" stroke-width=\"4\" stroke-oppacity=\"0.7\" />", fx, fy);
            fprintf(arqTxt, "cep: %s\n", retornaQCEP(info));
            quadraFinalizar(info);
            deletaDaArvore(city->arvoreQuadra, no);
            removeChave(city->quadra_cep, retornaQCEP(info));
        }
    }
    fclose(arqSvg);
    fclose(arqTxt);
    va_end(variaveis);
}

void qry_dq(Cidade cid, Info info, double r, double fx, double fy, char svg[], char txt[], char id[], char metrica[], int tipo){
    cidade *city = cid;
    percorreArvore2(city->arvoreQuadra, qry_dq_no, cid, r, fx, fy, svg, txt, id, metrica, tipo);
}


void qry_mud(FILE* arquivoTxt, char* cpf, char* cep, char face, int num, char* complemento, Cidade cid){
    cidade *city = (cidade*)cid;
    Pessoa pes = getPrimeiroRegistro(city->pessoas_cpf, cpf);
    Moradia mor = getPrimeiroRegistro(city->moradias_cpf, cpf);

    fprintf(arquivoTxt, "mud cpf: %s\n", cpf);
    if(!pes){
        fprintf(arquivoTxt, " -Pessoa não encontrada\n\n");
        return;
    }
    
    fprintf(arquivoTxt, " -%s %s, %s mudou-se\n", pessoaGetNome(pes), pessoaGetSobrenome(pes), pessoaGetNascimento(pes));
    if(!mor){
        fprintf(arquivoTxt, "  .de lugar nenhum, aparetemente\n");
        mor = moradiaNovo(cep, face, num, complemento);
        insereRegistro(city->moradias_cpf, cpf, mor);
    }else{
        fprintf(arquivoTxt, "  .de: %s, %c, %d, %s\n", moradiaGetCep(mor), moradiaGetFace(mor), moradiaGetNum(mor), moradiaGetComplemento(mor));
    }
    fprintf(arquivoTxt, "  .para: %s, %c, %d, %s\n\n", cep, face, num, complemento);
}
int qry_mplg_quadra_predios(Cidade cid, char* cep, Reta* poligono, int tamPolig, FILE* arquivoTxt){
    cidade* city = cid;
    int tamVetPre=0, tamVetCpf=0;
    int qtdPessoas = 0;
    Predio* predios = getVetorRegistros(city->predio_cep, cep, &tamVetPre);
    Info* cpfs = getVetorRegistros(city->moradiaPessoa_cep, cep, &tamVetCpf);
    for(int i=0;i<tamVetPre;i++){
        Reta* predio = retornaPredioLados(predios[i]);
        if(retanguloTotalDentroPoligono(predio, poligono, tamPolig)){
            for(int j=0;j<tamVetCpf;j++){
                Moradia mor = getPrimeiroRegistro(city->moradias_cpf, cpfs[j]);
                if(moradiaGetFace(mor) == retornaPFace(predios[i])[0] && moradiaGetNum(mor) == (int)retornaPNumero(predios[i])){
                    fprintf(arquivoTxt, "  ~cpf %s\n", (char*)cpfs[j]);
                    Pessoa pes = getPrimeiroRegistro(city->pessoas_cpf, cpfs[j]);
                    if(pes == NULL){
                        fprintf(arquivoTxt, "   .Pessoa não encontrada\n");
                    }else{
                        fprintf(arquivoTxt, "   .%s %s, %c, %s\n", pessoaGetNome(pes), pessoaGetSobrenome(pes), pessoaGetSexo(pes), pessoaGetNascimento(pes));
                    }
                    fprintf(arquivoTxt, "   .%s, %c, %d, %s\n", moradiaGetCep(mor), moradiaGetFace(mor), moradiaGetNum(mor), moradiaGetComplemento(mor));
                    qtdPessoas++;
                }
            }
        }
    }
    free(predios);
    return qtdPessoas;
}
void qry_mplg_quadra(Info info, va_list args){
    va_list variaveis;
    va_copy(variaveis, args);
    Reta* polig = va_arg(variaveis, void**);
    int tamPolig = va_arg(variaveis, int);
    FILE* arquivoTxt = va_arg(variaveis, FILE*);
    FILE* arquivoSvg = va_arg(variaveis, FILE*);
    Cidade cid = va_arg(variaveis, void*);

    double x = retornaQX(info);
    double y = retornaQY(info);
    double w = retornaQW(info);
    double h = retornaQH(info);
    Reta retangulo[4] = {criarReta(x, y, x+w, y), criarReta(x+w, y, x+w, y+h), criarReta(x+w, y+h, x, y+h), criarReta(x, y+h, x, y)};
    if(retanguloIntersectaPoligono(retangulo, polig, tamPolig) || retanguloTotalDentroPoligono(retangulo, polig, tamPolig)){
        setQEspessura(info, retornaQEspessura(info)*2);
        fprintf(arquivoTxt, " -cep: %s\n", retornaQCEP(info));
        int qtdPessoas = qry_mplg_quadra_predios(cid, retornaQCEP(info), polig, tamPolig, arquivoTxt);
        fprintf(arquivoSvg, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"black\">%d</text>", retornaQX(info)+retornaQW(info)/2, retornaQY(info)+retornaQH(info)/2, qtdPessoas);
    }

    for(int i=0;i<4;i++)
        retaFinalizar(retangulo[i]);
    va_end(variaveis);
}
void qry_mplg(char* caminhoDoArquivo, Reta poligono[], int tamPolig, FILE* arquivoTxt, char* nomeArqSvg, Cidade cid){
    cidade *city = cid;
    FILE* arquivoSvg = fopen(nomeArqSvg, "a+");
    fprintf(arquivoTxt, "mplg?\n");
    percorreArvore(city->arvoreQuadra, qry_mplg_quadra, poligono, tamPolig, arquivoTxt, arquivoSvg, cid);
    fclose(arquivoSvg);
    fprintf(arquivoTxt, "\n");
}

void qry_eplg_predio(cidade *city, Predio predio, Reta* poligono, int tamPolig, FILE* arquivoTxt, FILE* arquivoSvg, EstabelecimentoComercial item){
    Reta* lados = retornaPredioLados(predio);
    if(retanguloTotalDentroPoligono(lados, poligono, tamPolig)){
        fprintf(arquivoTxt, " -Estabelecimento: %s\n", estabelecimentoGetNome(item));
        Pessoa pes = getPrimeiroRegistro(city->pessoas_cpf, estabelecimentoGetCpf(item));
        if(!pes){
            fprintf(arquivoTxt, "  .proprietário não encontrado\n");
        }else{
            fprintf(arquivoTxt, "  .proprietário: %s %s\n", pessoaGetNome(pes), pessoaGetSobrenome(pes));
        }
        fprintf(arquivoTxt, "  .localizado em: %s, %c, %d\n", retornaPCep(predio), retornaPFace(predio)[0], (int)retornaPNumero(predio));
        fprintf(arquivoSvg, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%lf\" fill-oppacity=\"0.5\" stroke-oppacity=\"0.7\" />",
            retornaPX(predio), retornaPY(predio), 5.0, "magenta", "yellow", 0.5);
        Quadra quad = getPrimeiroRegistro(city->quadra_cep, retornaPCep(predio));
        if(quad != NULL){
            if(strcmp(retornaQCorB(quad), "green")!=0){
                setQCorP(quad, "green");
            }else{
                setQCorP(quad, "blue");
            }
        }
    }
}
void qry_elpg_estabelecimentos(Info item, va_list args){
    va_list variaveis;
    va_copy(variaveis, args);
    char* tipo = va_arg(variaveis, char*);
    Reta* polig = va_arg(variaveis, void**);
    int tamPolig = va_arg(variaveis, int);
    FILE* arquivoTxt = va_arg(variaveis, FILE*);
    FILE* arquivoSvg = va_arg(variaveis, FILE*);
    Cidade cid = va_arg(variaveis, void*);
    
    if(strcmp(tipo, estabelecimentoGetTipo(item))!=0 && tipo[0] != '*'){
        printf("_%s__%s_\n", tipo, estabelecimentoGetTipo(item));fflush(stdout);
        return;
    }

    cidade *city = cid;
    char* cep = estabelecimentoGetCep(item);
    char face = estabelecimentoGetFace(item);
    int num = estabelecimentoGetNum(item);
    int tamVet=0;
    Predio* predios = getVetorRegistros(city->predio_cep, cep, &tamVet);
    for(int i=0;i<tamVet;i++){
        if(retornaPFace(predios[i])[0] == face && retornaPNumero(predios[i]) == num){
            qry_eplg_predio(city, predios[i], polig, tamPolig, arquivoTxt, arquivoSvg, item);
            break;
        }
    }

    free(predios);
    va_end(variaveis);
}
void qry_eplg(char* caminhoDoArquivo, Reta poligono[], int tamPolig, FILE* arquivoTxt, char* nomeArqSvg, char* tipo, Cidade cid){
    cidade *city = cid;
    FILE* arquivoSvg = fopen(nomeArqSvg, "a+");
    fprintf(arquivoTxt, "eplg? %s\n", tipo);
    HshTblMap(city->comercios_cpf, qry_elpg_estabelecimentos, tipo, poligono, tamPolig, arquivoTxt, arquivoSvg, cid);
    fprintf(arquivoTxt, "\n");
    fclose(arquivoSvg);
}
