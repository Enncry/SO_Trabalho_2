#include <stdio.h>

typedef struct{
    int id;
    int t_ingresso;
    int t_cpu_total;
    int t_cpu_processado;
    int prioridade; //nesse caso, quanto maior o valor, maior a prioridade

} Processo;

float calc_tmed_PP_e_imprime_gantt(Processo processos[], int n){
    int t_total=0;
    int t_espera_total=0;
    int max_ingresso=0;

    //somando o tempo total para executar todos os processos
    for(int i=0;i<n;i++){ 
        t_total += processos[i].t_cpu_total; 
        if (processos[i].t_ingresso > max_ingresso) {
            max_ingresso = processos[i].t_ingresso;
        }
    }

    int j=0; //indice do processo atual no processador
    int maior_prioridade=-1; 

    int tam_max_gantt = max_ingresso + t_total;
    int gantt[tam_max_gantt];

    for(int t=0;t<t_total;t++){  
        maior_prioridade = -1;
        j = -1;
        //escolhendo processo que vai rodar no tempo t
        for(int i=0;i<n;i++){
            //processo já esta na fila? processo já terminou de processar?
            if(processos[i].t_ingresso <= t && processos[i].t_cpu_processado < processos[i].t_cpu_total){
                if(processos[i].prioridade>maior_prioridade){ //critério de desempate: menor id
                    maior_prioridade = processos[i].prioridade;
                    j=i;
                }
            }
        }

        //rodar processo
        if(j>=0){ //encontrou processo candito
            processos[j].t_cpu_processado++;
            gantt[t] = processos[j].id;
        } //não encontrou processo canditado
        else {
            t_total++;
            gantt[t] = -1;
        }

        //contabilizando os processos que esperaram na fila
        for(int i=0;i<n;i++){
            if(i!=j && processos[i].t_ingresso <= t && processos[i].t_cpu_processado < processos[i].t_cpu_total){
                t_espera_total++;
            }
        }

    }

    //imprimindo o diagrama de gantt
    printf("\n| -- | -> indica processador ocioso(não rodou processo)\n\n");
    printf("---====DIAGRAMA DE GANTT ====---\n");
    printf("|");
    for(int t=0;t < t_total;t++){
        if(gantt[t]!=-1){
            printf(" P%d |", gantt[t]);
        }
        else{
            printf(" -- |");
        }
        
    }

    printf("\n0");
    for(int t=0;t<t_total;t++){
        printf("%5d",t+1);
    }
    printf("\n\n");

    float tmed_espera = (float)t_espera_total / n;
    return tmed_espera;
}

int main(void){
    Processo processos[5] = {{1,0,5,0,2},
                             {2,0,2,0,3},
                             {3,1,4,0,1},
                             {4,3,1,0,4},
                             {5,5,2,0,5}};

                             
    printf("Tempo médio de espera: %.2f u.t.\n",calc_tmed_PP_e_imprime_gantt(processos,5));

    return 0;
}