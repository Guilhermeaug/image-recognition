/****************

LAED1 - Projeto (Parte I) - Busca por padrão em sequência

Alunos(as):
    * Diogo Emanuel
    * Guilherme Augusto

Data: 30/06/2022

****************/

#include <bits/stdc++.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 10

/*********************************************************/
// Ziviani

typedef int TipoChave;
typedef int Tipo;
typedef int NumElementos;
typedef int PontoMedio;

typedef struct
{
    int Chave;
    /* outros componentes */
    Tipo tipo;
    NumElementos numElementos;
    PontoMedio pontoMedio;
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

/* ========================================================================= */

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
        printf("%d\n", Aux->Item.Chave);
        Aux = Aux->Prox;
    }
}

/*********************************************************/

typedef struct Elemento
{
    int number;
    int quantity;

    Elemento(int number, int quantity)
    {
        this->number = number;
        this->quantity = quantity;
    }
} Elemento;

int main()
{
    std::string fileName;
    std::ifstream file;
    int n; // numero de elementos
    int previousElement, actualElement;

    std::cout << "Digite o nome do arquivo: ";
    std::cin >> fileName;

    file.open(fileName);
    file >> n;

    std::vector<Elemento> elements; // para guardar as repeticoes
    std::map<int, int> segmentsMap; // para guardar qual numero tem qual segmento
    std::set<int> values;

    file >> actualElement;
    previousElement = actualElement;
    values.insert(actualElement);

    int repeatCounter = 1;
    for (int i = 1; i < n; i++)
    {
        file >> actualElement;

        if (previousElement != actualElement)
        {
            elements.push_back(Elemento(previousElement, repeatCounter));

            repeatCounter = 1;
            if (values.find(actualElement) == values.end())
            {
                values.insert(actualElement);
            }
        }
        else
        {
            repeatCounter = repeatCounter + 1;
        }

        previousElement = actualElement;
    }
    elements.push_back(Elemento(previousElement, repeatCounter)); // o ultimo estava de fora

    std::string line1;
    std::string line2;
    std::cout << "Matriz:\n";
    for (auto e : elements)
    {
        auto it = values.find(e.number);
        int index = std::distance(values.begin(), it) + 1;

        line1.append(std::to_string(index) + " ");
        line2.append(std::to_string(e.quantity) + " ");
    }

    // removendo os ultimos espacos
    line1.pop_back();
    line2.pop_back();
    std::cout << line1 << "\n";
    std::cout << line2 << "\n";

    // TRABALHO AEDS
    std::map<int, int> colors;
    colors.insert(std::pair<int, int>(1, 0));
    colors.insert(std::pair<int, int>(2, 128));
    colors.insert(std::pair<int, int>(3, 255));

    TipoLista lista;

    for (int i = 0; i < elements.size(); i++)
    {
        auto e = elements[i];

        TipoItem item;
        item.Chave = i;
        item.tipo = colors[e.number];
        item.numElementos = e.quantity;

        // Insere(elements[i], &lista);
    }

    return 0;
}