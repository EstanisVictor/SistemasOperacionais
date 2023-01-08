#include <bits/stdc++.h>
#include <unistd.h>
#include "Processo.h"

using namespace std;



void srt(vector<Processo *> processos)
{
    sort(processos.begin(), processos.end(), ordenaMenorTempo);
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
            cout << "\rOcioso: " << contadorEstadoOcioso << "s";
            sleep(1);

            tempo_atual++;
            processos.push_back(processo_atual);
            contadorEstadoOcioso++;

            if (tempo_atual == processo_atual->momento_volta)
            {
                cout << endl;
            }

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
            cout << processo_atual->nome << " comeca a executar no tempo: " << tempo_atual << endl;
        }

        for (size_t tempo = processo_atual->tempo_gasto; tempo <= processo_atual->tempo_exec; tempo++)
        {
            sort(processos.begin(), processos.end(), ordenaMenorTempo);

            int indiceProcessoMenorTempo = aloca_processos_menor_tempo(processos, &tempo_atual, processo_atual, tempo);

            if (indiceProcessoMenorTempo != -1)
            {
                processo_atual->setTempoGasto(tempo);
                processos.push_back(processo_atual);

                cout << "\nProcesso " << processo_atual->nome << " interrompido!!" << endl;
                cout << "Tempo restante: " << processo_atual->tempo_exec - tempo << endl;

                break;
            }

            if (tempo == 0)
            {
                cout << "-----------------------------------------------------------------" << endl;
                cout << processo_atual->nome << " comeca a executar no tempo: " << tempo_atual << endl;
                tempo_atual++;
                continue;
            }

            if (tempo == processo_atual->tempo_exec)
            {
                cout << "\rExecutando: " << tempo << "s" << endl;
                sleep(1);
                cout << "Processo " << processo_atual->nome << " terminou em " << tempo_atual << endl;
                continue;
            }

            if (processo_atual->tem_interrupcao && tempo == retorna_tempo_exec(processo_atual->tempo_exec))
            {
                cout << "\rExecutando: " << tempo << "s" << endl;
                sleep(1);

                int duracao = 0;

                srand(time(NULL));
                while (duracao == 0)
                {
                    duracao = rand() % 10;
                }

                cout << "*****************************************************************" << endl;
                cout << "Processo esta interrompido por " << duracao << "s" << endl;
                cout << "Processo vai retornar aos " << tempo_atual + duracao << "s" << endl;
                cout << "*****************************************************************" << endl;

                Processo *processo_salvo = new Processo(processo_atual->nome, processo_atual->tempo_exec,
                                                        processo_atual->tempo_chegada, tempo, false, true,
                                                        tempo_atual + duracao);
                processos.push_back(processo_salvo);

                break;
            }
            cout << "\rExecutando: " << tempo << "s";
            sleep(1);
            tempo_atual++;
        }
    }
    cout << "Tempo total: " << tempo_atual << "s" << endl;
}

int main()
{
    vector<Processo *> processos;

    processos.push_back(new Processo("P1", 6, 0, 0, false, false, 0));
    processos.push_back(new Processo("P2", 5, 0, 0, true, false, 0));
    processos.push_back(new Processo("P3", 7, 0, 0, false, false, 0));

    srt(processos);

    return 0;
}
