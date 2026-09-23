#include <stdio.h>

typedef struct{
    int id;
    int t_cpu;
    int termino;
    
} Processo;

float calc_tmed_FCFS(Processo processos[], int n){
    int t_atual = 0;
    int soma_espera = 0;
    float t_espera_medio;

    //OBS: considerando que todos os processos começam no tempo 0 (como solicitado em sala), o algoritmo fica mais simples
    for(int i=0;i<n;i++){
        soma_espera += t_atual;
        t_atual += processos[i].t_cpu;
        processos[i].termino = t_atual;

        printf("P%d: Duração: %d | Término: %d\n",processos[i].id,processos[i].t_cpu,processos[i].termino);

    }

    t_espera_medio = (float)soma_espera / n;

    return t_espera_medio;

}

void imprimir_gantt(Processo processos[], int n){
    
    printf("---====DIAGRAMA DE GANTT====---\n");
    
    for(int i=0;i<n;i++){
        if(i==n-1){
            printf("|  P%d  |\n",processos[i].id);
        }
        else{
            printf("|  P%d  ",processos[i].id);
        }
    }

    printf("0");
    for(int i=0;i<n;i++){
        printf("%7d",processos[i].termino);
    }
    printf("\n");

}

int main(void){
    Processo processos[5] = {{1,10,0},
                             {2,1,0},
                             {3,2,0},
                             {4,1,0},
                             {5,5,0}};


    printf("\nTempo médio de espera: %.2f u.t.\n\n", calc_tmed_FCFS(processos, 5));
    imprimir_gantt(processos, 5);

    return 0;
}