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

bool ordenaMaiorTempo(Processo *p1, Processo *p2)
{
    return p1->getTime() > p2->getTime();
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

void printCounter(int counter, int &tempo_atual)
{
    for (int i = 1; i <= counter; i++)
    {
        cout << "\rExecutando: " << i << "s";
        sleep(1);
        tempo_atual++;
    }
}

void printTempoExec(vector<Processo *> processos)
{
    for (const auto &p : processos)
    {
        cout << p->nome << " --> Tempo de execucao: " << p->tempo_exec << endl;
    }
}

Processo* verifica_interrupcao(Processo *processoAtual, int quantidade_exec, int &tempo_atual)
{
    if (processoAtual->tem_interrupcao)
    {
        int duracao = 0, volta = 0;

        srand(time(NULL));
        while (duracao == 0)
        {
            duracao = rand() % 10;
        }

        if (tempo_atual == 0)
        {
            volta = duracao + tempo_atual + quantidade_exec;
        }
        else
        {
            volta = duracao + tempo_atual;
        }

        cout << "-----------------------------------------------------------------" << endl;
        cout << "*****************************************************************" << endl;
        cout << "Processo " << processoAtual->nome << " vai interromper apos " << quantidade_exec << "s de sua execucao" << endl;
        cout << "Vai ficar interrompido por " << duracao << "s" << endl;
        cout << "Vai retornar aos " << volta << "s" << endl;
        cout << "*****************************************************************" << endl;
        Processo *processo_salvo = new Processo(processoAtual->nome, processoAtual->tempo_exec,
                                                processoAtual->tempo_chegada, processoAtual->tempo_gasto, false,
                                                true, volta);
        return processo_salvo;
    }
    else
    {
        return processoAtual;
    }
}