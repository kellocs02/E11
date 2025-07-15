#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_THREADS 10
#define MAX_VALUE 10000

//creiamo il mutex e il cond che mi servono per la sincronizzazione
pthread_mutex_t mutex =PTHREAD_MUTEX_INITIALIZER;
int variabile_condivisa=0;
//dobbiamo fare in modo che i thread quando eseguono la funzione si blocchino se un altro thread la sta già eseguendo
//quindi prima di entrare nella sezione critica dobbiamo mettere il lock sul mutex

void* Funzione_thread(void* args){
    int thread_id= *((int*)args); //prendiamo il valore dell'id del thread
    pthread_mutex_lock(&mutex); //il thread prova a prendere il controllo del mutex, se un altro thread lo ha già preso, aspetta
    for (int i=0;i<MAX_VALUE;i++){
        variabile_condivisa++;
        fprintf(stderr,"Thread_ID: %d, Valore_Variabile: %d\n",thread_id,variabile_condivisa);
    }
    pthread_mutex_unlock(&mutex); //liberiamo il mutex, ora gli altri thread possono entrare nella sezione critica
    return NULL;
}

int main(){
    pthread_t thread_id[MAX_THREADS]; //creiamo o threads
    int array_id[MAX_THREADS]; //se passiamo come id il valore &i, tutti i thread avranno lo stesso id
    for(int j=0;j<MAX_THREADS;j++){
        array_id[j]=j; //in questo modo passiamo una cella diversa che contiene l'id del thread ad ogni funzione
        pthread_create(&thread_id[j],NULL,Funzione_thread,(void*)&array_id[j]); //creiamo il thread
    }
    for(int i=0;i<MAX_THREADS;i++){
        pthread_join(thread_id[i],NULL);
    }

    pthread_mutex_destroy(&mutex); //distruggiamo il mutex e liberiamo le risorse
}
