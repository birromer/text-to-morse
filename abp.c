#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "abp.h"


/* insereABP:
    Funcao recursiva para inserir um novo nodo na arvore a, sendo chave o valor
      ascii do caractere e codigo sua representacao em morse.
    Atualiza o contador de execucoes para a criacao da ABP. */
tipoABP* insereABP (tipoABP* a, int chave, char codigo[10], int *exec)
{
    (*exec)++;      //atualiza o contador de execucoes

    if (a == NULL)
    {
        a = (tipoABP*)malloc(sizeof(tipoABP));            //se for nulo, cria a raiz
        a->chave = chave;
        strcpy(a->codigo, codigo);
        a->esq = NULL;
        a->dir = NULL;

        return a;       //retorna a arvore criada
    }
    else if (chave < a->chave)
    {
        a->esq = insereABP(a->esq, chave, codigo, exec);        //modifica a subarvore esquerda recursivamente

        return a;       //retorna a arvore modificada
    }
    else if (chave > a->chave)
    {
        a->dir = insereABP(a->dir, chave, codigo, exec);        //modifica a subarvore direita recursivamente

        return a;       //retorna a arvore modificada
    }
}


/* consultaABP:
    Procura um caractere por seu valor ascii na arvore a, e atualiza o contador de comparacoes.
    Caso nao encontre o valor procurado, retorna NULL. */
tipoABP* consultaABP (tipoABP* a, int chave, int *comp)
{
    while (a != NULL)                 //enquanto nao chega nas folhas, procura pelo nodo com a chave indicada
    {
        (*comp)++;                    //incrementa o contador de comparacoes

        if (chave == a->chave)
            return a;                 //retorna o nodo com o char procurado
        else if (chave < a->chave)
            a = a->esq;               //passa para a subarvore esquerda para continuar procurando
        else
            a = a->dir;               //passa para a subarvore direita para continuar procurando
    }

    return NULL;                      //retorna NULL se nao encontrar o valor na arvore
}

/* criaABP:
    Abre o arquivo com a tabela morse cujo nome eh recebido como parametro,
      e cria uma ABP, inserindo nela nodos com o conteudo do arquivo.
    Atualiza o contador de execucoes para a criacao da ABP. */
tipoABP* criaABP (char* nomeArquivo, int *exec)
{
    FILE *arq;
    char buffer;            //guarda o caractere lido
    char codigo[10];        //guarda o codigo morse lido
    tipoABP *abp = NULL;    //inicializa abp a ser construida

    if (!(arq = fopen(nomeArquivo, "r")))    //testa abertura do arquivo
    {
        printf("Erro na abertura do arquivo %s\n", nomeArquivo);
    }
    else
    {
        while (!feof(arq))  //repete ate o fim do arquivo
        {
            fscanf(arq, "%c\t%s\n", &buffer, codigo);   //armazena em buffer o valor do char lido e em codigo a string do seu codigo morse
            abp = insereABP(abp, buffer, codigo, exec);       //insere na abp o novo valor
        }

        fclose(arq);
    }

    return abp;             //retorna a abp com os caracteres e suas representacoes em morse
}

/* ajeitaBufferAVL:
    Modifica o valor do caractere recebido, removendo acentos (nao funciona nesta versao)
      e tornando-o maiusculo caso seja letra minuscula. */
char ajeitaBufferABP (char buffer)
{
    /*** TESTES PARA REMOCAO DE ACENTOS NAO ESTAO FUNCIONANDO :( ***

    ///testes para transformar caracteres acentuados para versoes maiusculas sem acento, que se encontram na arvore
    if ((buffer >= 131 && buffer <= 134) || buffer == 142 || buffer == 143 || buffer == 160 || buffer == 199 || (buffer >= 181 && buffer <= 183))
        buffer = 'A';
    else if (buffer == 128 || buffer == 135)
        buffer = 'C';
    else if (buffer == 130 || (buffer >= 136 && buffer <= 138) || buffer == 144 || (buffer >= 210 && buffer <= 212))
        buffer = 'E';
    else if ((buffer >= 139 && buffer <= 141) || buffer == 161 || (buffer >= 213 && buffer <= 216))
        buffer = 'I';
    else if (buffer == 164 || buffer == 165)
        buffer = 'N';
    else if ((buffer >= 147 && buffer <= 149) || buffer == 153 || buffer == 162 || buffer == 224 || (buffer >= 226 && buffer <= 229))
        buffer = 'O';
    else if (buffer == 129 || buffer == 150 || buffer == 151 || buffer == 154 || buffer == 163 || (buffer >= 233 && buffer <= 235))
        buffer = 'U';
    else if (buffer == 152 || buffer == 236 || buffer == 237)
        buffer = 'Y';
    */

    if (buffer >= 97 && buffer <= 122)    //passa para maiusculo, caso necessario
        buffer -= 32;

    return buffer;
}

/* traduzArqABP:
    Recebe como entrada o nome do arquivo a ser lido, o nome do arquivo a ser criado e a arvore para a traducao.
    Abre os arquivos e, para cada caractereo arquivo de entrada, faz o tratamento com a funcao ajeitaBufferABP e
      insere o string com sua representacao em morse ao final do arquivo de saida.
    Retorna o numero de comparacoes feitas durante a traducao. */
int traduzArqABP (char* nomeEntrada, char* nomeSaida, tipoABP *a)
{
    FILE *entrada, *saida;      //ponteiros para os arquivos de entrada e saida
    tipoABP *nodo;              //ponteiro que armazenara o nodo com o codigo do caractere procurado a cada busca
    char buffer;                //buffer para o caractere do momento
    int comp = 0;               //armazena o numero de comparacoes feitas

    if (!(entrada = fopen(nomeEntrada, "r")))   //testa a abertura do arquivo de entrada
    {
        printf("Erro na abertura do arquivo %s.\n", nomeEntrada);
    }
    else
    {
        if (!(saida = fopen(nomeSaida, "w")))   //testa a abertura do arquivo de saida
        {
            printf("Erro na abertura do arquivo %s.\n", nomeSaida);
        }
        else
        {
            while (!feof(entrada))              //enquanto nao for o fim do arquivo
            {
                buffer = getc(entrada);              //buffer recebe o proximo caractere do arquivo

                buffer = ajeitaBufferABP(buffer);    //tira acentos (nao funciona nesta versao) e deixa tudo maiusculo

                if (buffer == 32)       //se houver espaco, insere '/ ' em vez de ' ', que ja se usa para separar letras
                {
                    putc('/', saida);
                    putc(' ', saida);
                }
                else if (buffer == 10)  //se houver line feed, pula uma linha
                {
                    putc('\n', saida);
                }
                else
                {
                    //encontra e guarda o nodo desejado e atualiza o contador de comparacoes
                    nodo = consultaABP(a, buffer, &comp);

                    if (nodo != NULL)
                        fprintf(saida, "%s ", nodo->codigo);  //insere no arquivo de saida o codigo morse do caractere
                }
            }

            fclose(saida);
        }

        fclose(entrada);
    }

    return comp;    //retorna a soma das comparacoes realizadas nas operacoes de busca pelos caracteres desejados
}
