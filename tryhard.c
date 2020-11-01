#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.h"

#define NUM_THREADS 2

typedef struct someArgs_tag {
    int numberOfThread;
    int bitCounter;
    int deleteByTh;
    pthread_mutex_t *mutex;
    DblLinkedList* list;
} someArgs_t;

int countOfBit(int element, int numberOfThread);
void *find(void *args);

int main()
{
    int i;

    DblLinkedList *list;
    list = createDblLinkedList();
    int SIZE = 100;
    initListByRand(list, SIZE);
    printDblLinkedList(list, printInt);

    pthread_mutex_t mutex;

    someArgs_t th[NUM_THREADS];
    for(i=0;i<NUM_THREADS;i++)
    {
        th[i].numberOfThread=i;
        th[i].bitCounter=0;
        th[i].deleteByTh=0;
        th[i].mutex=&mutex;
        th[i].list=list;
    }

    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    for(i=0;i<NUM_THREADS;i++)
    {
        pthread_create(&threads[i],NULL,find,(void *)&th[i]);
    }

    for(i=0;i<NUM_THREADS;i++)
    {
        pthread_join(threads[i],NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Количество нулевых бит: %d\n",th[0].bitCounter);
    printf("Количество единичных бит: %d\n",th[1].bitCounter);
    printf("Количество пройденных первым потоком элементов: %d\n",th[0].deleteByTh);
    printf("Количество пройденных вторым потоком элементов: %d\n",th[1].deleteByTh);

    return 0;
}

int countOfBit(int element, int numberOfThread) {
    int result = 0;
    int shiftBySize = ((sizeof(int) * 8) - 1);
    if (element < 0) {
        result++;
        element &= ((1 << shiftBySize) - 1);
    }
    while (element) {
        result += (element & 1);
        element >>= 1;
    }

    switch (numberOfThread)
    {
    case 0:
        return (sizeof(int) * 8) - result;

    case 1:
        return result;
    }
}

void *find(void *args)
{
    someArgs_t *arg=(someArgs_t *) args;
    
    while (1)
    {
        if (arg->list->size > 0)
        {
            switch (arg->numberOfThread)
            {
            case 0:
                if (arg->list->head)
                {
                    arg->bitCounter += countOfBit(arg->list->head->value, arg->numberOfThread);
                    pthread_mutex_lock(arg->mutex);
                    popFront(arg->list);
                    arg->deleteByTh++;
                    pthread_mutex_unlock(arg->mutex);

                }
                break;

            case 1:
                if (arg->list->tail)
                {
                    arg->bitCounter += countOfBit(arg->list->tail->value, arg->numberOfThread);
                    pthread_mutex_lock(arg->mutex);
                    popBack(arg->list);
                    arg->deleteByTh++;
                    pthread_mutex_unlock(arg->mutex);
                }
                break;
            }
        }
        sleep(1e-6);

        if (arg->list->size == 0)
            return NULL;
    }
}