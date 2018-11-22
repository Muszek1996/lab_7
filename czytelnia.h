#ifndef _czytelnia_
#define _czytelnia_
#include <pthread.h>
#include <stdint-gcc.h>

/*** Definicje typow zmiennych ***/
typedef struct {
    unsigned int liczba_czyt,liczba_pis;
    unsigned int liczba_czek_czyt,liczba_czek_pis;
  pthread_mutex_t mutex;
  pthread_cond_t czytelnicy,pisarze;
} czytelnia_t;



/*** Deklaracje procedur interfejsu ***/
void inicjuj(czytelnia_t* czytelnia_p);
void czytam(czytelnia_t* czytelnia_p);
void pisze(czytelnia_t* czytelnia_p);

int my_read_lock_lock(czytelnia_t* czytelnia_p);
int my_read_lock_unlock(czytelnia_t* czytelnia_p);
int my_write_lock_lock(czytelnia_t* czytelnia_p);
int my_write_lock_unlock(czytelnia_t* czytelnia_p);

#endif
