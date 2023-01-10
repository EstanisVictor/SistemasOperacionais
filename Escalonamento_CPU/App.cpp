#include <bits/stdc++.h>
#include <unistd.h>
#include "Processo.h"

using namespace std;

void fcfs(vector<Processo *> processos)
{
    int execProcesso = 0, tempo_atual = 0;

    cout << "                         FCFS" << endl;
    printTempoExec(processos);

    while (!processos.empty())
    {
        Processo *processoAtual = processos.front();
        processos.erase(processos.begin());

        if (processoAtual->tem_interrupcao)
        {
            execProcesso = retorna_tempo_exec(processoAtual->tempo_exec);

            int duracao = 0;

            srand(time(NULL));
            while (duracao == 0)
            {
                if (processoAtual->tempo_exec <= 10)
                {
                    duracao = rand() % 10;
                }
                else if (processoAtual->tempo_exec > 10 && processoAtual->tempo_exec <= 50)
                {
                    duracao = rand() % 50;
                }
                else
                {
                    duracao = rand() % 100;
                }
            }

            cout << "-----------------------------------------------------------------" << endl;
            cout << "*****************************************************************" << endl;
            cout << "Processo " << processoAtual->nome << " vai interromper aos " << execProcesso << "s" << endl;
            cout << "Vai ficar interrompido por " << duracao << "s" << endl;
            cout << "*****************************************************************" << endl;

            Processo *processo_salvo = new Processo(processoAtual->nome, processoAtual->tempo_exec - execProcesso,
                                                    processoAtual->tempo_chegada, processoAtual->tempo_gasto, false,
                                                    true, tempo_atual + duracao, processoAtual->prioridade);

            processos.push_back(processo_salvo);
        }
        else
        {
            execProcesso = processoAtual->tempo_exec;
        }

        if (tempo_atual < processoAtual->momento_volta && processoAtual->esta_interrompido)
        {
            cout << "-----------------------------------------------------------------" << endl;
            cout << "CPU em estado de ocioso..." << endl;
            printCounter(processoAtual->momento_volta - tempo_atual + 1, tempo_atual);

            cout << "\n-----------------------------------------------------------------" << endl;
            cout << processoAtual->nome << " comeca a executar no tempo: " << tempo_atual << endl;
            printCounter(execProcesso, tempo_atual);
        }
        else
        {
            cout << "-----------------------------------------------------------------" << endl;
            cout << processoAtual->nome << " comeca a executar no tempo: " << tempo_atual << endl;
            printCounter(execProcesso, tempo_atual);
        }
        cout << "\nTerminou em: " << tempo_atual << endl;
    }
}

void sjf(vector<Processo *> processos)
{
    int execProcesso = 0, tempo_atual = 0;
    sort(processos.begin(), processos.end(), ordenaMenorTempo);

    cout << "                         SJF" << endl;
    printTempoExec(processos);

    while (!processos.empty())
    {
        Processo *processoAtual = processos.front();
        processos.erase(processos.begin());
        sort(processos.begin(), processos.end(), ordenaMenorTempo);

        if (processoAtual->tem_interrupcao)
        {
            execProcesso = retorna_tempo_exec(processoAtual->tempo_exec);

            int duracao = 0, volta = 0;

            srand(time(NULL));
            while (duracao == 0)
            {
                if (processoAtual->tempo_exec <= 10)
                {
                    duracao = rand() % 10;
                }
                else if (processoAtual->tempo_exec > 10 && processoAtual->tempo_exec <= 50)
                {
                    duracao = rand() % 50;
                }
                else
                {
                    duracao = rand() % 100;
                }
            }

            if (tempo_atual == 0)
            {
                volta = duracao + tempo_atual + execProcesso;
            }
            else
            {
                volta = duracao + tempo_atual;
            }

            cout << "-----------------------------------------------------------------" << endl;
            cout << "*****************************************************************" << endl;
            cout << "Processo " << processoAtual->nome << " vai interromper apos " << execProcesso << "s de sua execucao" << endl;
            cout << "Vai ficar interrompido por " << duracao << "s" << endl;
            cout << "Vai retornar aos " << volta << "s" << endl;
            cout << "*****************************************************************" << endl;

            Processo *processo_salvo = new Processo(processoAtual->nome, processoAtual->tempo_exec - execProcesso,
                                                    processoAtual->tempo_chegada, processoAtual->tempo_gasto, false,
                                                    true, volta, processoAtual->prioridade);
            processos.push_back(processo_salvo);
        }
        else
        {
            execProcesso = processoAtual->tempo_exec;
        }
        if (tempo_atual < processoAtual->momento_volta && processoAtual->esta_interrompido)
        {
            cout << "-----------------------------------------------------------------" << endl;
            cout << "CPU entra em estado de ocioso aos " << tempo_atual << endl;
            printCounter(processoAtual->momento_volta - tempo_atual, tempo_atual);
            cout << "\nTerminou em: " << tempo_atual << endl;

            cout << "-----------------------------------------------------------------" << endl;
            cout << processoAtual->nome << " comeca a executar no tempo: " << tempo_atual << endl;
            printCounter(execProcesso, tempo_atual);
        }
        else
        {
            cout << "-----------------------------------------------------------------" << endl;
            cout << processoAtual->nome << " comeca a executar no tempo: " << tempo_atual << endl;
            printCounter(execProcesso, tempo_atual);
        }
        cout << "\nTerminou em: " << tempo_atual << endl;
    }
}

void srt(vector<Processo *> processos)
{
    cout << "                         SRT" << endl;
    sort(processos.begin(), processos.end(), ordenaMenorTempo);
    printTempoExec(processos);
    int tempo_atual = 0;
    int contadorEstadoOcioso = 1;

    while (!processos.empty())
    {
        sort(processos.begin(), processos.end(), ordenaMenorTempo);

        int indiceProcesso = aloca_processos(processos, &tempo_atual);
        Processo *processo_atual = processos.at(indiceProcesso);
        processos.erase(processos.begin() + indiceProcesso);

        if (processo_atual->esta_interrompido && processo_atual->momento_volta > tempo_atual)
        {
            cout << "Ocioso: " << tempo_atual << "s" << endl;
            sleep(1);

            tempo_atual++;
            processos.push_back(processo_atual);
            contadorEstadoOcioso++;

            continue;
        }

        if (processo_atual->tempo_chegada > tempo_atual)
        {
            cout << "processo nao esta pronto" << endl;
            sleep(1);

            tempo_atual++;
            processos.push_back(processo_atual);

            continue;
        }

        if (processo_atual->tempo_gasto > 0)
        {
            cout << "-----------------------------------------------------------------" << endl;
            cout << processo_atual->nome << " volta no tempo: " << tempo_atual << endl;
        }
        else
        {
            cout << "-----------------------------------------------------------------" << endl;
            cout << processo_atual->nome << " comeca a executar no tempo: " << tempo_atual << endl;
        }

        for (size_t tempo = processo_atual->tempo_gasto; tempo <= processo_atual->tempo_exec; tempo++)
        {

            int indiceProcessoMenorTempo = aloca_processos_menor_tempo(processos, &tempo_atual, processo_atual, tempo);

            if (indiceProcessoMenorTempo != -1)
            {
                processo_atual->setTempoGasto(tempo);
                processos.push_back(processo_atual);

                cout << "\nProcesso " << processo_atual->nome << " interrompido!!" << endl;
                cout << "Tempo restante: " << processo_atual->tempo_exec - tempo << endl;

                break;
            }

            if (tempo == processo_atual->tempo_gasto)
            {
                tempo_atual++;
                continue;
            }

            if (tempo == processo_atual->tempo_exec)
            {
                cout << "Executando: " << tempo << "s" << endl;
                sleep(1);
                cout << "Processo " << processo_atual->nome << " terminou em " << tempo_atual << endl;
                continue;
            }

            if (processo_atual->tem_interrupcao && tempo == retorna_tempo_exec(processo_atual->tempo_exec))
            {
                cout << "Executando: " << tempo << "s" << endl;
                sleep(1);

                int duracao = 0;

                srand(time(NULL));
                while (duracao == 0)
                {
                    duracao = rand() % 10;
                }

                cout << "*****************************************************************" << endl;
                cout << "Vai ficar interrompido por " << duracao << "s" << endl;
                cout << "Processo pode retornar a partir dos " << tempo_atual + duracao << "s" << endl;
                cout << "*****************************************************************" << endl;

                Processo *processo_salvo = new Processo(processo_atual->nome, processo_atual->tempo_exec,
                                                        processo_atual->tempo_chegada, tempo, false, true,
                                                        tempo_atual + duracao, processo_atual->prioridade);
                processos.push_back(processo_salvo);

                break;
            }
            cout << "Executando: " << tempo << "s" << endl;
            sleep(1);
            tempo_atual++;
        }
    }
    cout << "Tempo total: " << tempo_atual << "s" << endl;
}

void duling_nao_preemptivo(vector<Processo *> processos)
{
    cout << "                         DULING" << endl;
    sort(processos.begin(), processos.end(), ordenaMaiorPrioridade);
    printTempoExec(processos);
    int tempo_atual = 0;
    int contadorEstadoOcioso = 1;

    while (!processos.empty())
    {
        sort(processos.begin(), processos.end(), ordenaMaiorPrioridade);

        int indiceProcesso = aloca_processos(processos, &tempo_atual);
        Processo *processo_atual = processos.at(indiceProcesso);
        processos.erase(processos.begin() + indiceProcesso);

        if (processo_atual->esta_interrompido && processo_atual->momento_volta > tempo_atual)
        {
            cout << "Ocioso: " << tempo_atual << "s" << endl;
            sleep(1);

            tempo_atual++;
            processos.push_back(processo_atual);
            contadorEstadoOcioso++;

            continue;
        }

        if (processo_atual->tempo_chegada > tempo_atual)
        {
            cout << "processo nao esta pronto" << endl;
            sleep(1);

            tempo_atual++;
            processos.push_back(processo_atual);

            continue;
        }

        if (processo_atual->tempo_gasto > 0)
        {
            cout << "-----------------------------------------------------------------" << endl;
            cout << processo_atual->nome << " volta no tempo: " << tempo_atual << endl;
        }
        else
        {
            cout << "-----------------------------------------------------------------" << endl;
            cout << processo_atual->nome << " comeca a executar no tempo: " << tempo_atual << endl;
        }

        for (size_t tempo = processo_atual->tempo_gasto; tempo <= processo_atual->tempo_exec; tempo++)
        {

            int indiceProcessoMenorTempo = aloca_processos_menor_prioridade(processos, &tempo_atual, processo_atual, tempo);

            if (indiceProcessoMenorTempo != -1)
            {
                processo_atual->setTempoGasto(tempo);
                processos.push_back(processo_atual);

                cout << "\nProcesso " << processo_atual->nome << " interrompido!!" << endl;
                cout << "Tempo restante: " << processo_atual->tempo_exec - tempo << endl;

                break;
            }

            if (tempo == processo_atual->tempo_gasto)
            {
                tempo_atual++;
                continue;
            }

            if (tempo == processo_atual->tempo_exec)
            {
                cout << "Executando: " << tempo << "s" << endl;
                sleep(1);
                cout << "Processo " << processo_atual->nome << " terminou em " << tempo_atual << endl;
                continue;
            }

            if (processo_atual->tem_interrupcao && tempo == retorna_tempo_exec(processo_atual->tempo_exec))
            {
                cout << "Executando: " << tempo << "s" << endl;
                sleep(1);

                int duracao = 0;

                srand(time(NULL));
                while (duracao == 0)
                {
                    duracao = rand() % 10;
                }

                cout << "*****************************************************************" << endl;
                cout << "Vai ficar interrompido por " << duracao << "s" << endl;
                cout << "Processo pode retornar a partir dos " << tempo_atual + duracao << "s" << endl;
                cout << "*****************************************************************" << endl;

                Processo *processo_salvo = new Processo(processo_atual->nome, processo_atual->tempo_exec,
                                                        processo_atual->tempo_chegada, tempo, false, true,
                                                        tempo_atual + duracao, processo_atual->prioridade);
                processos.push_back(processo_salvo);

                break;
            }
            cout << "Executando: " << tempo << "s" << endl;
            sleep(1);
            tempo_atual++;
        }
    }
    cout << "Tempo total: " << tempo_atual << "s" << endl;
}

void round_robin_process(vector<Processo *> processos)
{
    cout << "                   ROUND ROBIN" << endl;
    int tempo_atual = 0, quantum = 0;
    srand(time(NULL));

    while (quantum == 0)
    {
        quantum = rand() % 10;
    }

    printTempoExec(processos);

    while (!processos.empty())
    {
        Processo *processoAtual = processos.front();
        processos.erase(processos.begin());
        int quantidade_exec = 0;

        if (processoAtual->tempo_exec > 0)
        {
            if (processoAtual->tempo_exec - quantum < 0)
            {
                quantidade_exec = (processoAtual->tempo_exec - quantum) * (-1);
                processoAtual->tempo_exec = processoAtual->tempo_exec - quantidade_exec;
                Processo *processoSalvo = verifica_interrupcao(processoAtual, quantidade_exec, tempo_atual);
                processos.push_back(processoSalvo);
            }
            else
            {
                quantidade_exec = quantum;
                processoAtual->tempo_exec = processoAtual->tempo_exec - quantidade_exec;
                Processo *processoSalvo = verifica_interrupcao(processoAtual, quantidade_exec, tempo_atual);
                processos.push_back(processoSalvo);
            }

            if (tempo_atual < processoAtual->momento_volta && processoAtual->esta_interrompido)
            {
                cout << "-----------------------------------------------------------------" << endl;
                cout << "CPU entra em estado de ocioso aos " << tempo_atual << endl;
                printCounter(processoAtual->momento_volta - tempo_atual, tempo_atual);
                cout << "\nTerminou em: " << tempo_atual << endl;

                cout << "-----------------------------------------------------------------" << endl;
                cout << processoAtual->nome << " comeca a executar no tempo: " << tempo_atual << endl;
                printCounter(quantidade_exec, tempo_atual);
            }
            else
            {
                cout << "-----------------------------------------------------------------" << endl;
                cout << processoAtual->nome << " comeca a executar no tempo: " << tempo_atual << endl;
                printCounter(quantidade_exec, tempo_atual);
            }
            cout << "\nEsta faltando " << processoAtual->tempo_exec << "s de execucao";
            cout << "\nTerminou em: " << tempo_atual << endl;
        }
    }
}

int main()
{
    vector<Processo *> processos;

    processos.push_back(new Processo("P1", 4, 0, 0, true, false, 0, 2));
    processos.push_back(new Processo("P2", 5, 0, 0, false, false, 0, 5));
    processos.push_back(new Processo("P3", 7, 0, 0, false, false, 0, 3));

    // fcfs(processos);
    // sjf(processos);
    // srt(processos);
    duling_nao_preemptivo(processos);
    // round_robin_process(processos);

    return 0;
}