#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "avl.h"


/* rotacao_simples_direita:
    Executa o algoritmo de RSD e atualiza o contador de execucoes. */
tipoAVL* rotacao_simples_direita (tipoAVL* a, int *exec)
{
    tipoAVL* aux;

    (*exec)++;          //atualiza o contador de execucoes

    aux = a->esq;       //executa o algoritmo da rotacao
    a->esq = aux->dir;
    aux->dir = a;

    a->fator = 0;       //atualiza o fator do antigo nodo a
    a = aux;

    return a;           //retorna a arvore rotacionada
}

/* rotacao_simples_esquerda:
    Executa o algoritmo de RSE e atualiza o contador de execucoes. */
tipoAVL* rotacao_simples_esquerda (tipoAVL* a, int *exec)
{
    tipoAVL* aux;

    (*exec)++;          //atualiza o contador de execucoes

    aux = a->dir;       //executa o algoritmo da rotacao
    a->dir = aux->esq;
    aux->esq = a;

    a->fator = 0;       //atualiza o fator do antigo nodo a
    a = aux;

    return a;           //retorna a arvore rotacionada
}

/* rotacao_dupla_direita:
    Executa o algoritmo de RDD e atualiza o contador de execucoes. */
tipoAVL* rotacao_dupla_direita (tipoAVL* a, int *exec)
{
    a->esq = rotacao_simples_esquerda(a->esq, exec);  //executa as duas rotacoes simples
    a = rotacao_simples_direita(a, exec);             //que compoem a RDD

    if (a->fator == 1)        //recalcula o fator da antiga raiz de acordo com o fator da nova raiz
        a->dir->fator = -1;
    else
        a->dir->fator = 0;

    if (a->fator == -1)       //recalcula o fator da antiga raiz->esq de acordo com o fator da nova raiz
        a->esq->fator = 1;
    else
        a->esq->fator = 0;

    return a;                 //retorna a arvore rotacionada
}

/* rotacao_dupla_esquerda:
    Executa o algoritmo de RDE e atualiza o contador de execucoes. */
tipoAVL* rotacao_dupla_esquerda (tipoAVL* a, int *exec)
{
    a->dir = rotacao_simples_direita(a->dir, exec);  //executa as duas rotacoes simples
    a = rotacao_simples_esquerda(a, exec);           //que compoem a RDD

    if (a->fator == -1)       //recalcula o fator da antiga raiz->dir de acordo com o fator da nova raiz
        a->dir->fator = 1;
    else
        a->dir->fator = 0;

    if (a->fator == 1)        //recalcula o fator da antiga raiz de acordo com o fator da nova raiz
        a->esq->fator = -1;
    else
        a->esq->fator = 0;

    return a;                 //retorna a arvore rotacionada
}

/* caso1:
    Redireciona para as funcoes de rotacao. */
tipoAVL* caso1 (tipoAVL* a, int *ok, int *exec)
{
    if (a->esq->fator == 1)     //se a subarvore esquerda so tiver subarvore esquerda
    {
        a = rotacao_simples_direita(a, exec);
    }
    else                        //se a subarvore esquerda so tiver subarvore direita
    {
        a = rotacao_dupla_direita(a, exec);
    }

    a->fator = 0;               //atualiza o fator do nodo a
    *ok = 0;

    return a;                   //retorna a arvore modificada
}

/* caso2:
    Redireciona para as funcoes de rotacao. */
tipoAVL* caso2 (tipoAVL* a, int *ok, int *exec)
{
    if (a->dir->fator == -1)     //se a subarvore direita so tiver subarvore direita
    {
        a = rotacao_simples_esquerda(a, exec);
    }
    else                         //se a subarvore direita so tiver subarvore esquerda
    {
        a = rotacao_dupla_esquerda(a, exec);
    }

    a->fator = 0;               //atualiza o fator do nodo a
    *ok = 0;

    return a;                   //retorna a arvore modificada
}

/* insereAVL:
    Funcao recursiva para inserir um novo nodo na arvore a, sendo chave o valor
      ascii do caractere e codigo sua representacao em morse.
    Atualiza o contador de execucoes para a criacao da AVL. 
    A variavel *ok serve para indicar quando deve ocorrer recalculo de fator. */
tipoAVL* insereAVL (tipoAVL* a, int chave, char codigo[10], int *ok, int *exec)
{
    (*exec)++;      //atualiza o contador de execucoes

    if (a == NULL)
    {
        a = (tipoAVL*)malloc(sizeof(tipoAVL));            //se for nulo, cria a raiz
        a->chave = chave;
        strcpy(a->codigo, codigo);
        a->fator = 0;
        a->esq = NULL;
        a->dir = NULL;

        *ok = 1;
        return a;       //retorna a arvore criada
    }
    else if (chave < a->chave)
    {
        a->esq = insereAVL(a->esq, chave, codigo, ok, exec);    //modifica a subarvore esquerda recursivamente

        if (*ok == 1)   //recalcula o fator do nodo se preciso
        {
            switch (a->fator)
            {
                case -1:
                    a->fator = 0;
                    *ok = 0;
                    break;
                case  0:
                    a->fator = 1;
                    break;
                case  1:
                    a = caso1(a, ok, exec);   //chama as funcoes de rotacao porque o fator chegou em 2
                    break;                    //e atualiza o contador de execucoes
            }
        }

        return a;       //retorna a arvore modificada
    }
    else
    {
        a->dir = insereAVL(a->dir, chave, codigo, ok, exec);    //modifica a subarvore direita recursivamente

        if (*ok == 1)   //recalcula o fator do nodo se preciso
        {
            switch (a->fator)
            {
                case -1:
                    a = caso2(a, ok, exec);   //chama as funcoes de rotacao porque o fator chegou em -2
                    break;                    //e atualiza o contador de execucoes
                case  0:
                    a->fator = -1;
                    break;
                case  1:
                    a->fator = 0; *ok = 0;
                    break;
            }
        }

        return a;       //retorna a arvore modificada
    }
}

/* consultaAVL:
    Procura um caractere por seu valor ascii na arvore a, e atualiza o contador de comparacoes.
    Caso nao encontre o valor procurado, retorna NULL. */
tipoAVL* consultaAVL (tipoAVL* a, int chave, int *comp)
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

/* criaAVL:
    Abre o arquivo com a tabela morse cujo nome eh recebido como parametro,
      e cria uma AVL, inserindo nela nodos com o conteudo do arquivo.
    Atualiza o contador de execucoes para a criacao da AVL. */
tipoAVL* criaAVL (char* nomeArquivo, int *exec)
{
    FILE *arq;
    char buffer;            //guarda o caractere lido
    char codigo[10];        //guarda o codigo morse lido
    int ok;                 //na funcao insereAVL, indica se o fator de um nodo deve ser recalculado
    tipoAVL *avl = NULL;    //inicializa avl a ser construida

    if (!(arq = fopen(nomeArquivo, "r")))    //testa abertura do arquivo
    {
        printf("Erro na abertura do arquivo %s\n", nomeArquivo);
    }
    else
    {
        while (!feof(arq))  //repete ate o fim do arquivo
        {
            fscanf(arq, "%c\t%s\n", &buffer, codigo);   //armazena em buffer o valor do char lido e em codigo a string do seu codigo morse
            avl = insereAVL(avl, buffer, codigo, &ok, exec);  //insere na avl o novo valor
        }

        fclose(arq);
    }

    return avl;             //retorna a avl com os caracteres e suas representacoes em morse
}

/* ajeitaBufferAVL:
    Modifica o valor do caractere recebido, removendo acentos (nao funciona nesta versao)
      e tornando-o maiusculo caso seja letra minuscula. */
char ajeitaBufferAVL (char buffer)
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

/* traduzArqAVL:
    Recebe como entrada o nome do arquivo a ser lido, o nome do arquivo a ser criado e a arvore para a traducao.
    Abre os arquivos e, para cada caractereo arquivo de entrada, faz o tratamento com a funcao ajeitaBufferAVL e
      insere o string com sua representacao em morse ao final do arquivo de saida.
    Retorna o numero de comparacoes feitas durante a traducao. */
int traduzArqAVL (char* nomeEntrada, char* nomeSaida, tipoAVL *a)
{
    FILE *entrada, *saida;      //ponteiros para os arquivos de entrada e saida
    tipoAVL *nodo;              //ponteiro que armazenara o nodo com o codigo do caractere procurado a cada busca
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

                buffer = ajeitaBufferAVL(buffer);    //tira acentos (nao funciona nesta versao) e deixa tudo maiusculo

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
                    nodo = consultaAVL(a, buffer, &comp);

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
