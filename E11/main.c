#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_THREADS 10
#define MAX_VALUE 10000

int variabile_condivisa=0;

void* Funzione_thread(void* args){
    int thread_id= *((int*)args); //prendiamo il valore dell'id del thread
    for (int i=0;i<MAX_VALUE;i++){
        variabile_condivisa++;
        fprintf(stderr,"Thread_ID: %d, Valore_Variabile: %d\n",thread_id,i);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t thread_id[MAX_THREADS]; //creiamo o threads
    int array_id[MAX_THREADS]; //se passiamo come id il valore &i, tutti i thread avranno lo stesso id
    for(int j=0;j<MAX_THREADS;j++){
        array_id[j]=j; //in questo modo passiamo una cella diversa che contiene l'id del thread ad ogni funzione
        pthread_create(&thread_id[j],NULL,Funzione_thread,(void*)&array_id[j]); //creiamo il thread
    }
    pthread_join(&thread_id[9],NULL);
}