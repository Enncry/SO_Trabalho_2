#include <stdio.h>

typedef struct{
    int id;
    int t_cpu_total;
    int t_cpu_processado;

} Processo;

//OBS: considerenado todos os processos chegando no tempo 0
float calc_tmed_RR_e_imprime_gantt(Processo processos[], int n, int quantum){
    int t_total=0;
    int t_espera_total=0;

    //somando o tempo total para executar todos os processos
    for(int i=0;i<n;i++){ 
        t_total += processos[i].t_cpu_total; 
    }

    int j=0; //indice do processo atual no processador 
    int k=0; //contador do quantum

    int gantt[t_total];

    for(int t=0;t<t_total;t++){
        //verifica se o processo atual está completo
        while(processos[j].t_cpu_processado >= processos[j].t_cpu_total){
            if(j<n-1){
                j++;
            }
            else{j=0;} //avanço na fila circular

            k=0;
        }

        //executando processo j por 1 u.t.
        processos[j].t_cpu_processado++;
        k++;

        //guarda no histórico o id do processo que rodou no tempo 't'
        gantt[t] = processos[j].id;

        //contabilizando os processos que esperaram na fila
        for(int l=0;l<n;l++){
            if(l!=j && processos[l].t_cpu_processado < processos[l].t_cpu_total){
                t_espera_total++;
            }
        }
        
        //se esgotou quantum, passa o processador pro próximo processo
        if(k==quantum || processos[j].t_cpu_processado == processos[j].t_cpu_total){
            if(j<n-1){
                j++;
            }
            else {j=0;} //avanço na fila circular

            k=0;
        }
    }

    //imprimindo o diagrama de gantt
    printf("---====DIAGRAMA DE GANTT (Quantum = %d) ====---\n", quantum);
    printf("|");
    for(int t=0;t < t_total;t++){
        printf("P%d|", gantt[t]);
    }

    printf("\n0");
    for(int t=0;t<t_total;t++){
        printf("%3d",t+1);
    }
    printf("\n\n");

    float tmed_espera = (float)t_espera_total / n;
    return tmed_espera;
}

int main(void){
    Processo processos[5] = {{1,10,0},
                             {2,29,0},
                             {3,3,0},
                             {4,7,0},
                             {5,12,0}};

                             
    printf("Tempo médio de espera: %.2f u.t.\n",calc_tmed_RR_e_imprime_gantt(processos,5,10));

    return 0;
}