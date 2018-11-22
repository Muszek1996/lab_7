#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(czytelnia_t* czytelnia_p){
  pthread_mutex_lock(&czytelnia_p->mutex);
  if(czytelnia_p->liczba_pis || czytelnia_p->liczba_czek_pis){
      printf("czytelnik %ld - Nie mogę wejść bo czytelnia zajeta przez: %d pisarzy piszacych i %d czekających pisarzy\n", pthread_self(),czytelnia_p->liczba_pis,czytelnia_p->liczba_czek_pis);
      czytelnia_p->liczba_czek_czyt++;
      pthread_cond_wait(&czytelnia_p->czytelnicy,&czytelnia_p->mutex);
      czytelnia_p->liczba_czek_czyt--;
  }
    czytelnia_p->liczba_czyt++;
    pthread_cond_signal(&czytelnia_p->czytelnicy);
    pthread_mutex_unlock(&czytelnia_p->mutex);
}


int my_read_lock_unlock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->mutex);
    czytelnia_p->liczba_czyt--;
    if(!czytelnia_p->liczba_czyt) {
        pthread_cond_signal(&czytelnia_p->pisarze);
    }
    pthread_mutex_unlock(&czytelnia_p->mutex);
}


int my_write_lock_lock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->mutex);
    if(czytelnia_p->liczba_czyt+czytelnia_p->liczba_pis){
        czytelnia_p->liczba_czek_pis++;
        pthread_cond_wait(&czytelnia_p->pisarze,&czytelnia_p->mutex);
        czytelnia_p->liczba_czek_pis--;
    }
    czytelnia_p->liczba_pis++;
    pthread_mutex_unlock(&czytelnia_p->mutex);
}


int my_write_lock_unlock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->mutex);
    czytelnia_p->liczba_pis--;

    if(czytelnia_p->liczba_czek_czyt){
        printf("pisarz %ld - wpuszczam czytelnika bo jest: %d czekających czytelników\n", pthread_self(),czytelnia_p->liczba_czek_czyt);
        pthread_cond_signal(&czytelnia_p->czytelnicy);
    }
    else {
        printf("pisarz %ld - %s\n", pthread_self(),czytelnia_p->liczba_czek_pis?"wpuszczam chętnego pisarza":"wychodze i nie wpuszczam nikogo bo niema chetych pisarzy");
        pthread_cond_signal(&czytelnia_p->pisarze);
    }
    pthread_mutex_unlock(&czytelnia_p->mutex);
}


void inicjuj(czytelnia_t* czytelnia_p){
    czytelnia_p->liczba_czyt = 0;
    czytelnia_p->liczba_czek_czyt = 0;
    czytelnia_p->liczba_pis = 0;
    czytelnia_p->liczba_czek_pis = 0;
    pthread_mutex_init(&czytelnia_p->mutex,NULL);
    pthread_cond_init(&czytelnia_p->czytelnicy,NULL);
    pthread_cond_init(&czytelnia_p->pisarze,NULL);
}

void czytam(czytelnia_t* czytelnia_p){
    printf("czytelnik %ld - CZYTAM\n", pthread_self());
    usleep(rand()%1000000);
}

void pisze(czytelnia_t* czytelnia_p){
    printf("pisarz %ld - PISZE\n", pthread_self());
    usleep(rand()%1000000);
}


