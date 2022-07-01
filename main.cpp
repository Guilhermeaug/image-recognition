/****************

LAED1 - Projeto (Parte I) - Busca por padrão em sequência

Alunos(as):
    * Diogo Emanuel
    * Guilherme Augusto

Data: 30/06/2022

****************/
#include <bits/stdc++.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 100

typedef int TipoChave;
typedef int TipoCor;

typedef struct
{
    TipoChave Chave;
    TipoCor Tipo;
    int NumElementos;
    double PontoMedio;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula
{
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;

typedef struct
{
    TipoApontador Primeiro, Ultimo;
} TipoLista;

// Declaracao das funcoes
void FLVazia(TipoLista *Lista);
int Vazia(TipoLista *Lista);
void Insere(TipoItem x, TipoLista *Lista);
void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item);
TipoItem GeraItem(TipoChave chave, TipoCor tipo, int nElementos, double pontoMedio);
void Imprime(TipoLista Lista);
TipoLista PreencheLista(std::string NomeArquivo, std::map<int, int> Colors, TipoLista Lista);
bool VerificaSequencia(TipoLista lista);

void FLVazia(TipoLista *Lista)
{
    Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

int Vazia(TipoLista Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
    TipoApontador q;
    if (Vazia(*Lista) || p == NULL || p->Prox == NULL)
    {
        printf(" Erro   Lista vazia ou posi  c   a o n  a o existe\n");
        return;
    }
    q = p->Prox;
    *Item = q->Item;
    p->Prox = q->Prox;
    if (p->Prox == NULL)
        Lista->Ultimo = p;
    free(q);
}

void Imprime(TipoLista Lista)
{
    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL)
    {
        printf("Chave: %d, Numero de elementos: %d, Tipo: %d, Ponto Medio: %.2lf \n",
               Aux->Item.Chave, Aux->Item.NumElementos, Aux->Item.Tipo, Aux->Item.PontoMedio);
        Aux = Aux->Prox;
    }
}

TipoItem GeraItem(TipoChave Chave, TipoCor Tipo, int NumElementos, double PontoMedio)
{
    TipoItem item;
    item.Chave = Chave;
    item.NumElementos = NumElementos;
    item.Tipo = Tipo;
    item.PontoMedio = PontoMedio;
    return item;
}

TipoLista PreencheLista(std::string NomeArquivo, std::map<int, int> Colors, TipoLista Lista)
{
    std::ifstream Arquivo;
    int N;
    Arquivo.open(NomeArquivo);
    Arquivo >> N;

    int ContadorIds = 0;
    int ElementoAtual;
    Arquivo >> ElementoAtual;
    for (int i = 1; i < N; i++)
    {
        int ContadorRepeticoes = 1;
        int ProximoElemento;
        while (Arquivo >> ProximoElemento)
        {
            if (ProximoElemento == ElementoAtual)
            {
                ContadorRepeticoes++;
            }
            else
            {
                break;
            }
        }

        TipoItem Item = GeraItem(ContadorIds, Colors[ElementoAtual], ContadorRepeticoes, 0);
        Insere(Item, &Lista);
        ContadorIds++;

        ElementoAtual = ProximoElemento;
        i = i + ContadorRepeticoes - 1;
    }

    return Lista;
}
/**
 *
 * Se uma
linha possuir N elementos (pixels), de 0 a N-1, então o ponto médio do segmento será (p+q)/2,
onde p e q são as posições do início e do fim do segmento. Outros campos poderão ser
adicionados, se necessário.

 */
/* double PontoMedio(TipoItem item, TipoLista lista){
//     // encontrar quantos elementos tem até chegar nesse item
//     // item.chave
        int p = 0, q = 0;
        TipoApontador Aux;
       int pontoMedio;
       Aux = Lista.Primeiro->Prox;
        if(lista.Chave == item.Chave)
        {
            p->Aux;
        }
        while (Aux != NULL)
        {
         Aux = Aux->Prox;
        }
        if(lista.Chave == item.Chave)
        {
            p->Aux;
        }
     pontoMedio = q+p/2;
     return pontoMedio;
 } */

bool VerificaSequencia(TipoLista lista)
{
    std::array<int, 5> sequencia = {1, 3, 2, 3, 1};
    int contador = 0;

    TipoApontador Aux;
    Aux = lista.Primeiro->Prox;

    while (Aux != NULL)
    {
        TipoCor tipo = Aux->Item.Tipo;
        if (tipo == sequencia[contador])
        {
            contador++;
        }
        else
        {
            contador = 0;
            if (tipo == sequencia[contador])
            {
                contador++;
            }
        }

        if (contador == 5)
        {
            return true;
        }

        Aux = Aux->Prox;
    }

    return false;
}

int main()
{
    std::map<int, int> Colors;
    Colors.insert(std::pair<int, int>(0, 1));
    Colors.insert(std::pair<int, int>(128, 2));
    Colors.insert(std::pair<int, int>(255, 3));

    TipoLista Lista;
    FLVazia(&Lista);

    std::string NomeArquivo;
    std::cout << "Digite o nome do arquivo: ";
    std::cin >> NomeArquivo;

    Lista = PreencheLista(NomeArquivo, Colors, Lista);

    std::cout << "Lista: " << std::endl;
    Imprime(Lista);

    if (VerificaSequencia(Lista))
    {
        std::cout << "Resultado: Padrao encontrado." << std::endl;
    }
    else
    {
        std::cout << "Resultado: Padrao nao encontrado." << std::endl;
    }

    return 0;
}