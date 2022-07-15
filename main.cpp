/****************

LAED1 - Projeto (Parte III) - Detecção de Faixa de pedestres em uma imagem

Alunos(as):
    * Diogo Emanuel
    * Guilherme Augusto

Data: 14/07/2022

****************/
#include <bits/stdc++.h>

typedef struct
{
    bool IsPista = false;
    bool IsFaixaPedestre = false;
    double PontoMedio = 0;
} Perfil;

typedef struct
{
    int Chave;
    int Tipo;
    int NumElementos;
    double PontoMedio = 0;
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
    Perfil Resultado;
} TipoLista;

// Definicoes das funcoes
void FLVazia(TipoLista *Lista);
int Vazia(TipoLista Lista);
void Insere(TipoItem x, TipoLista *Lista);
void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item);
void Imprime(TipoLista Lista);
double CalculaPontoMedio(int p, int q);
TipoItem GeraItem(int Chave, int Tipo, int NumElementos, double PontoMedio);
std::vector<TipoLista> PreencheListas(std::string NomeArquivo, std::map<int, int> Colors, std::vector<TipoLista> Listas);
Perfil VerificaSequencia(TipoLista Lista);
double CalculaMedia(std::vector<double> PontosMedios);
double CalculaDesvioPadrao(std::vector<double> PontosMedios, double Media);

// Funcoes utilitarias
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

double CalculaPontoMedio(int p, int q)
{
    return (p + q) / 2.0;
}

// Funcoes de manipulacao de listas do ziviani
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

TipoItem GeraItem(int Chave, int Tipo, int NumElementos, double PontoMedio)
{
    TipoItem Item;
    Item.Chave = Chave;
    Item.NumElementos = NumElementos;
    Item.Tipo = Tipo;
    Item.PontoMedio = PontoMedio;
    return Item;
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

Perfil VerificaSequencia(TipoLista Lista)
{
    Perfil Resultado;

    std::array<int, 5> SequenciaPista = {1, 3, 2, 3, 1};
    int IndicePista = 0;

    std::array<int, 13> SequenciaFaixaPedestre = {1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1};
    int IndiceFaixaPedestre = 0;

    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;

    while (Aux != NULL)
    {
        int Tipo = Aux->Item.Tipo;
        double PontoMedio = Aux->Item.PontoMedio;

        if (Tipo == 2)
        {
            Resultado.PontoMedio = PontoMedio;
        }

        if (Tipo == SequenciaPista[IndicePista])
        {
            IndicePista++;
        }
        else
        {
            IndicePista = 0;
            if (Tipo == SequenciaPista[IndicePista])
            {
                IndicePista++;
            }
        }

        if (Tipo == SequenciaFaixaPedestre[IndiceFaixaPedestre])
        {
            IndiceFaixaPedestre++;
        }
        else
        {
            IndiceFaixaPedestre = 0;
            if (Tipo == SequenciaFaixaPedestre[IndiceFaixaPedestre])
            {
                IndiceFaixaPedestre++;
            }
        }

        if (IndicePista == 5)
        {
            Resultado.IsPista = true;
        }

        if (IndiceFaixaPedestre == 13)
        {
            Resultado.IsFaixaPedestre = true;
        }

        Aux = Aux->Prox;
    }

    return Resultado;
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
    std::vector<double> PontosMediosLinhas;

    Listas = PreencheListas(NomeArquivo, Colors, Listas);
    for (auto &Lista : Listas)
    {
        Perfil Resultado = VerificaSequencia(Lista);
        Lista.Resultado = Resultado;

        if (Resultado.IsPista)
        {
            PontosMediosLinhas.push_back(Resultado.PontoMedio);
        }
    }

    auto contaPadrao = [](TipoLista Lista)
    { return Lista.Resultado.IsPista; };

    double ContemPadraoPistaPorcentagem = (double)std::count_if(Listas.begin(), Listas.end(), contaPadrao) /
                                          PontosMediosLinhas.size() * 100;

    double Media, DesvioPadrao, CoeficienteVariacao;
    Media = CalculaMedia(PontosMediosLinhas);
    DesvioPadrao = CalculaDesvioPadrao(PontosMediosLinhas, Media);
    CoeficienteVariacao = (DesvioPadrao / Media) * 100;

    if (ContemPadraoPistaPorcentagem < 70)
    {
        std::cout << "Resultado: Formato da pista nao estimado" << std::endl;
    }
    else
    {
        if (CoeficienteVariacao < 10)
        {
            std::cout << "Resultado: Formato da pista estimado" << std::endl;
        }
        else
        {
            std::cout << "Resultado: Formato da pista nao estimado" << std::endl;
        }
    }

    bool found = false;
    for (auto Lista : Listas)
    {
        Perfil Resultado = Lista.Resultado;

        if (Resultado.IsFaixaPedestre)
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        std::cout << "Resultado: Pista com faixa de pedestres" << std::endl;
    }
    else
    {
        std::cout << "Resultado: Pista sem faixa de pedestres" << std::endl;
    }

    return 0;
}