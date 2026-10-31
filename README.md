# lab_7

Parallel programming lab (C, pthreads): the readers-writers problem. 5 writer threads and 10 reader threads loop forever over a shared "reading room" guarded by a mutex and two condition variables.

- `czytelnia.c` / `czytelnia.h`: the reading-room monitor with a custom read/write lock (`my_read_lock_*`, `my_write_lock_*`) that tracks active and waiting readers/writers
- `czyt_pis.c`: creates the threads; each one sleeps for a random time, then reads or writes and logs what it does

## Build & run
```bash
cmake -B build && cmake --build build
./build/czyt_pis   # runs until stopped with Ctrl+C
```
