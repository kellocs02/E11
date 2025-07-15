#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX_THREADS 5

//bisogna usare un semaforo

sem_t semaforo;


void* funzione_thread(void* args){
    int thread_id= *((int*) args);
    sem_wait(&semaforo); //decrementa il valore del semaforo, se è a 0 , il thread che richiama questa istruzione rimane in attesa finchè un altro thread non chiama la sem_post
    //ingresso nella sezione critica
    printf("sono nella sezione critica, thread_id: %d\n", thread_id);
    //fine sezione critica
    sem_post(&semaforo); //aumento il valore del semaforo e se c'è un thread in attesa lo sveglio
    return NULL;
}

int main(){
    pthread_t thread_id[MAX_THREADS]; //creo un array di 5 thread
    int array_id[MAX_THREADS];
    sem_init(&semaforo,0,2); //inizializzo il semaforo

    for(int i=0;i<MAX_THREADS;i++){
        array_id[i]=i;
        pthread_create(&thread_id[i],NULL,funzione_thread,&array_id[i]);
    }

    for(int i=0;i<MAX_THREADS;i++){
        pthread_join(thread_id[i],NULL);
    }
    sem_destroy(&semaforo);     //elimino il sem e libero le risorse da esso occupate
}
