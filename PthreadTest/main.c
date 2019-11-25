#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NUM_THREADS     5

struct bigAssStruct {
	char name[16];
	int hp;
	int mp;
	bool isAlive;
};

void *PrintHello(void *bas)
{
   char* name;
   struct bigAssStruct* tmp = (struct bigAssStruct*)bas;
   name = tmp->name;
   int mp = tmp->mp;
   printf("Hello World! It's me, %s!  My MP is currently %d\n", name, mp);
   free(tmp);
   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   for(t=0; t<NUM_THREADS; t++){
      printf("In main: creating thread %ld\n", t);
      struct bigAssStruct* bas = malloc(sizeof(struct bigAssStruct));
      strcpy(bas->name, "DildoSwaggins");
      bas->hp = 400;
      bas->mp = 80*t;
      bas->isAlive = true;
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)bas);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }

   /* Last thing that main() should do */
   pthread_exit(NULL);
}
