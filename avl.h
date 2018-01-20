typedef struct AVL tipoAVL;

struct AVL
{
    int chave;          ///armazena o valor do caractere ascii
    char codigo[10];    ///armazena a representacao do caractere em morse
    int fator;
    tipoAVL *esq;
    tipoAVL *dir;
};

tipoAVL* rotacao_simples_direita (tipoAVL* a, int *exec);
tipoAVL* rotacao_simples_esquerda (tipoAVL* a, int *exec);
tipoAVL* rotacao_dupla_direita (tipoAVL* a, int *exec);
tipoAVL* rotacao_dupla_esquerda (tipoAVL* a, int *exec);

tipoAVL* caso1 (tipoAVL* a, int *ok, int *exec);
tipoAVL* caso2 (tipoAVL* a, int *ok, int *exec);

tipoAVL* insereAVL (tipoAVL* a, int chave, char codigo[10], int *ok, int *exec);

tipoAVL* consultaAVL (tipoAVL* a, int chave, int *comp);

tipoAVL* criaAVL (char* nomeArquivo, int *exec);

char ajeitaBufferAVL (char buffer);

int traduzArqAVL (char* nomeEntrada, char* nomeSaida, tipoAVL *a);
