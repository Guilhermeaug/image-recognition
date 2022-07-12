/****************

LAED1 - Projeto (Parte II) - Estimativa do formato da pista

Alunos(as):
    * Diogo Emanuel
    * Guilherme Augusto

Data: 14/07/2022

****************/
#include <bits/stdc++.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 100

typedef struct
{
    bool Encontrado;
    bool Faixa;
    double PontoMedio;
} Padrao;

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
double CalculaPontoMedio(int p, int q);
void Imprime(TipoLista Lista);
std::vector<TipoLista> PreencheListas(std::string NomeArquivo, std::map<int, int> Colors, TipoLista Lista);
Padrao VerificaSequencia(TipoLista Lista);
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

double CalculaPontoMedio(int p, int q)
{
    // std::cout << "p: " << p << " q: " << q << std::endl;
    return (p + q) / 2.0;
}

std::vector<TipoLista> PreencheListas(std::string NomeArquivo, std::map<int, int> Colors, std::vector<TipoLista> Listas)
{
    std::ifstream Arquivo;
    int L;
    Arquivo.open(NomeArquivo);
    Arquivo >> L;

    for (int i = 0; i < L; i++)
    {
        int N;
        Arquivo >> N;

        TipoLista Lista;
        FLVazia(&Lista);

        int ContadorIds = 0;
        int ElementoAtual;
        int ContadorElementos = 0;
        Arquivo >> ElementoAtual;
        for (int j = 1; j < N + 1; j++)
        {
            int ContadorRepeticoes = 1;
            int ProximoElemento;

            int k = j;
            while (k < N)
            {
                Arquivo >> ProximoElemento;
                if (ProximoElemento == ElementoAtual)
                {
                    ContadorRepeticoes++;
                }
                else
                {
                    break;
                }
                k++;
            }

            ContadorElementos += ContadorRepeticoes;
            double PontoMedio = CalculaPontoMedio(ContadorElementos - ContadorRepeticoes, ContadorElementos - 1);

            TipoItem Item = GeraItem(ContadorIds, Colors[ElementoAtual], ContadorRepeticoes, PontoMedio);
            Insere(Item, &Lista);
            ContadorIds++;

            ElementoAtual = ProximoElemento;

            j = k;
        }

        Listas.push_back(Lista);
    }

    return Listas;
}

Padrao VerificaSequenciaTrio(TipoLista Lista, std::array<int, 3> Sequencia)
{
    Padrao Padrao;
    Padrao.Encontrado = false;

    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    int i = 0;

    while (Aux != NULL)
    {
        TipoCor Tipo = Aux->Item.Tipo;
        double PontoMedio = Aux->Item.PontoMedio;

        if (Tipo == 2)
        {
            Padrao.PontoMedio = PontoMedio;
        }

        if (Tipo == Sequencia[i])
        {
            i++;
        }
        else
        {
            i = 0;
            if (Tipo == Sequencia[i])
            {
                i++;
            }
        }

        if (i == 3)
        {
            Padrao.Encontrado = true;
            return Padrao;
        }

        Aux = Aux->Prox;
    }

    return Padrao;
}

Padrao VerificaSequencia(TipoLista Lista)
{
    Padrao Padrao;
    std::array<int, 5> Sequencia = {1, 3, 2, 3, 1};
    std::array<int, 13> Faixa = {1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1};

    Padrao = VerificaSequenciaTrio(Lista, std::array<int, 3>{2, 3, 1});
    if (Padrao.Encontrado)
    {
        return Padrao;
    }

    Padrao = VerificaSequenciaTrio(Lista, std::array<int, 3>{1, 3, 2});
    if (Padrao.Encontrado)
    {
        return Padrao;
    }

    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    int i = 0;
    int fp = 0;

    while (Aux != NULL)
    {
        TipoCor Tipo = Aux->Item.Tipo;
        double PontoMedio = Aux->Item.PontoMedio;

        if (i == 2)
        {
            Padrao.PontoMedio = PontoMedio;
        }

        if (Tipo == Sequencia[i])
        {
            i++;
        }
        else
        {
            i = 0;
            if (Tipo == Sequencia[i])
            {
                i++;
            }
        }
        if(Tipo == Faixa[i])
        {
            fp++;
        }
        else
        {
            fp = 0;
            if (Tipo == Faixa[i])
            {
                fp++;
            }
        }

        if (i == 5)
        {
            Padrao.Encontrado = true;
            return Padrao;
        }
        if (fp == 13)
        {
            Padrao.Faixa = true;
            return Padrao;
        }

        Aux = Aux->Prox;
    }
    Padrao.Faixa = false;
    Padrao.Encontrado = false;

    return Padrao;
}

double CalculaMedia(std::vector<double> PontosMedios)
{
    double Media = 0;
    for (double PontoMedio : PontosMedios)
    {
        Media += PontoMedio;
    }
    return Media / PontosMedios.size();
}

double CalculaDesvioPadrao(std::vector<double> PontosMedios, double Media)
{
    double DesvioPadrao = 0;
    for (double PontoMedio : PontosMedios)
    {
        DesvioPadrao += pow(PontoMedio - Media, 2);
    }
    return sqrt(DesvioPadrao / PontosMedios.size());
}

int main()
{
    std::map<int, int> Colors;
    Colors.insert(std::pair<int, int>(0, 1));
    Colors.insert(std::pair<int, int>(128, 2));
    Colors.insert(std::pair<int, int>(255, 3));

    std::string NomeArquivo;
    std::cout << "Digite o nome do arquivo: ";
    std::cin >> NomeArquivo;

    std::vector<TipoLista> Listas;
    std::vector<Padrao> Padroes;
    std::vector<double> PontosMediosLinhas;

    Listas = PreencheListas(NomeArquivo, Colors, Listas);

    for (auto Lista : Listas)
    {
        Padrao Padrao = VerificaSequencia(Lista);
        Padroes.push_back(Padrao);

        if (Padrao.Encontrado)
        {
            PontosMediosLinhas.push_back(Padrao.PontoMedio);
        }
    }

    double ContemPadraoPistaPorcentagem = (double)std::count_if(Padroes.begin(), Padroes.end(), [](Padrao Padrao)
                                                                { return Padrao.Encontrado; }) /
                                          Padroes.size() * 100;
    // std::cout << "Contem Padrao Pista: " << ContemPadraoPistaPorcentagem << "%" << std::endl;

    double Media, DesvioPadrao, CoeficienteVariacao;
    Media = CalculaMedia(PontosMediosLinhas);
    DesvioPadrao = CalculaDesvioPadrao(PontosMediosLinhas, Media);
    CoeficienteVariacao = (DesvioPadrao / Media) * 100;

    if (ContemPadraoPistaPorcentagem < 70)
    {
        //std::cout << "Resultado: Formato da pista nao estimado" << std::endl;
        std::cout << "Resultado:  Pista sem faixa de pedestres" << std::endl;
    }
    else
    {
        if (CoeficienteVariacao < 10)
        {
            for (auto Lista : Listas)
            {
                Padrao Padrao = VerificaSequencia(Lista);
                Padroes.push_back(Padrao);

                if (Padrao.Faixa)
                {
                    std::cout << "Resultado: Pista sem faixa de pedestres" << std::endl;
                    break;
                }
                else
                {
                    std::cout << "Resultado: Pista com faixa de pedestres" << std::endl;
                    break;
                }
            }   
        }
    }

    return 0;
}