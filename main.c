#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "abp.h"
#include "avl.h"

int main(int argc, char *argv[])
{
    int opcao;
    char arqsaida[30];              //recebe os nomes para criar os arquivos de saida
    tipoABP *abp;                   //abp para armazenar os codigos morse
    tipoAVL *avl;                   //avl para armazenar os codigos morse
    int exec;                       //recebe o numero de execucoes das funcoes durante nas criacoes das arvores
    int comparacoes;                //recebe o numero de comparacoes realizadas nas traducoes
    clock_t start, end, elapsed;    //para determinar o tempo gasto no processo

    printf("\n\n\n\n");
    printf("     --     --  .......  --------   ......  -------- \n");
    printf("     ---   --- ..     .. --     -- ..    .. --       \n");
    printf("     ---- ---- ..     .. --     -- ..       --       \n");
    printf("     -- --- -- ..     .. --------   ......  ------   \n");
    printf("     --     -- ..     .. --   --         .. --       \n");
    printf("     --     -- ..     .. --    --  ..    .. --       \n");
    printf("     --     --  .......  --     --  ......  -------- \n\n\n");


    if (argc != 3)    //testa se foi fornecido o numero correto de parametros na chamada do programa
    {
        printf("\nNumero incorreto de parametros.");
        printf("\nUso correto: conversor-morse.exe <tabela_morse.txt> <arq_entrada.txt>\n\n");
        system("pause");
        return 0;
    }
    else
    {
        printf("\n    Seja bem-vindo ao Conversor de ASCII para Morse :)\n\n");

        printf("\nComo deseja executar o programa?");
        printf("\n (1) Criar ABP e AVL para comparar as arvores");
        printf("\n (2) Somente AVL");
        printf("\n (3) Somente ABP\n\n>");
        scanf("%d", &opcao);                //usuario escolhe quais arvores quer usar na execucao


        if (opcao == 1 || opcao == 3)       //executa a parte da ABP de acordo com a opcao
        {
            printf("\n===================================== ABP =====================================");

            printf("\n>Insira um nome para o arquivo de saida da ABP (com o sufixo): ");
            scanf("%s", &arqsaida);         //recebe o nome para o arquivo de saida da ABP

            /* cria a abp com o arquivo dicionario fornecido,
                calcula o numero de comparacoes e conta o tempo decorrido */
            start=clock();
            printf("\n   Criando uma ABP generica com os dados da tabela Morse...");
            abp = criaABP(argv[1], &exec);
            end = clock();
            elapsed = 1000*(end-start) / (CLOCKS_PER_SEC);
            printf("\n      Execucoes: %d", exec);
            printf("\n      Tempo criando a arvore: %ld ms\n", elapsed);

            /* gera arquivo com a traducao do arquivo de entrada para morse usando ABP generica,
                calcula o numero de comparacoes e conta o tempo decorrido */
            start=clock();
            printf("\n   Traduzindo o arquivo %s usando uma ABP generica...", argv[2]);
            comparacoes = traduzArqABP(argv[2], arqsaida, abp);
            end = clock();
            elapsed = 1000*(end-start) / (CLOCKS_PER_SEC);
            printf("\n      Comparacoes: %d", comparacoes);
            printf("\n      Tempo traduzindo: %ld ms\n", elapsed);

            printf("TOTAL DE OPERACOES: %d\n", exec+comparacoes);
        }

        if (opcao == 1 || opcao == 2)       //executa a parte da AVL de acordo com a opcao
        {
            printf("\n===================================== AVL =====================================");

            printf("\n>Insira um nome para o arquivo de saida da AVL (com o sufixo): ");
            scanf("%s", &arqsaida);         //recebe o nome para o arquivo de saida da AVL

            /* cria a avl com o arquivo dicionario fornecido,
                calcula o numero de comparacoes e conta o tempo decorrido */
            start=clock();
            printf("\n   Criando uma AVL com os dados da tabela Morse...");
            avl = criaAVL(argv[1], &exec);
            end = clock();
            elapsed = 1000*(end-start) / (CLOCKS_PER_SEC);
            printf("\n      Execucoes: %d", exec);
            printf("\n      Tempo criando a arvore: %ld ms\n", elapsed);

            /* gera arquivo com a traducao do arquivo de entrada para morse usando AVL,
                calcula o numero de comparacoes e conta o tempo decorrido */
            start=clock();
            printf("\n   Traduzindo o arquivo %s usando uma AVL...", argv[2]);
            comparacoes = traduzArqAVL(argv[2], arqsaida, avl);
            end = clock();
            elapsed = 1000*(end-start) / (CLOCKS_PER_SEC);
            printf("\n      Comparacoes: %d", comparacoes);
            printf("\n      Tempo traduzindo: %ld ms\n", elapsed);

            printf("TOTAL DE OPERACOES: %d\n", exec+comparacoes);
        }

        return 1;
    }

}
