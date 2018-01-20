typedef struct ABP tipoABP;

struct ABP
{
    int chave;          ///armazena o valor do caractere ascii
    char codigo[10];    ///armazena a representacao do caractere em morse
    tipoABP *esq;
    tipoABP *dir;
};

tipoABP* insereABP(tipoABP* a, int chave, char codigo[10], int *exec);

tipoABP* consultaABP(tipoABP* a, int chave, int *comp);

tipoABP* criaABP(char* nomeArquivo, int *exec);

char ajeitaBufferABP (char buffer);

int traduzArqABP(char* nomeEntrada, char* nomeSaida, tipoABP *a);
