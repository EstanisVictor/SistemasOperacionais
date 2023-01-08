#include <bits/stdc++.h>
using namespace std;

class Processo
{
public:
    string nome;
    int tempo_exec;
    int tempo_chegada;
    int tempo_gasto;
    bool tem_interrupcao;
    bool esta_interrompido;
    int momento_volta;

    Processo(string name, int tempo_exec, int tempo_chegada, int tempo_gasto, bool tem_interrupcao, bool esta_interrompido, int momento_volta);

    void imprimir();
    bool ordenaMenorTempo(Processo *p1, Processo *p2);
    int getTime() const;
    void setTempoGasto(int tempo_gasto);
};

Processo::Processo(string name, int tempo_exec, int tempo_chegada, int tempo_gasto, bool tem_interrupcao, bool esta_interrompido, int momento_volta)
{
    this->nome = name;
    this->tempo_exec = tempo_exec;
    this->tempo_chegada = tempo_chegada;
    this->tempo_gasto = tempo_gasto;
    this->tem_interrupcao = tem_interrupcao;
    this->esta_interrompido = esta_interrompido;
    this->momento_volta = momento_volta;
}

int Processo::getTime() const
{
    return tempo_exec;
}

void Processo::setTempoGasto(int tempo_gasto)
{
    this->tempo_gasto = tempo_gasto;
}

bool ordenaMenorTempo(Processo *p1, Processo *p2)
{
    return p1->getTime() < p2->getTime();
}

int aloca_processos(vector<Processo *> processos, int *tempo_atual)
{
    for (int i = 0; i < processos.size(); i++)
    {
        if (processos[i]->tempo_chegada <= *tempo_atual && processos[i]->momento_volta <= *tempo_atual)
        {
            return i;
        }
    }
    return 0;
}

int aloca_processos_menor_tempo(vector<Processo *> processos, int *tempo_atual, Processo *processo_atual, int tempo)
{
    for (int i = 0; i < processos.size(); i++)
    {
        if (processos[i]->tempo_chegada < *tempo_atual && processos[i]->momento_volta <= *tempo_atual &&
            (processos[i]->tempo_exec - processos[i]->tempo_gasto) < (processo_atual->tempo_exec - tempo))
        {
            return i;
        }
    }
    return -1;
}

int retorna_tempo_exec(int tempo)
{
    if (tempo % 2 == 0)
    {
        return tempo / 2;
    }
    else
    {
        return 1;
    }
}