/*
 * =====================================================================================
 *
 *       Filename:  semaphore_strict_counter.c
 *
 *    Description: This file demonstrates the use of POSIX threads - A hello world program 
 *
 *        Version:  1.0
 *        Created:  11/03/2020 07:50:04 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ABHISHEK SAGAR (), sachinites@gmail.com
 *   Organization:  Juniper Networks
 *    Modified by:  Howie Chang
 *    Modified on:  2025/06/06
 *
 * =====================================================================================
 */

/*
 * compile using :
 * gcc -g -c semaphore_strict_counter.c -o semaphore_strict_counter.o
 * gcc -g semaphore_strict_counter.o -o semaphore_strict_counter.exe -lpthread
 * Run : ./semaphore_strict_counter.exe
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /* For working with POSIX threads*/
#include <unistd.h>  /* For pause() and sleep() */
#include <errno.h>	 /* For using Global variable errno */
#include "sema.h"

sema_t sema0_1, sema0_2;
pthread_t even_thread, odd_thread;


/* A thread callback fn must have following prototypes 
 * void *(*thread_fn)(void *)
 * */
static void *
thread_fn_callback_even(void *arg) {
    for(int i = 2; i <= 15; i += 2){
        sema_wait(&sema0_2);
        printf("%d\n", i);
        sema_post(&sema0_1);
    }
    return NULL;
}

static void *
thread_fn_callback_odd(void *arg) {
    for(int i = 1; i <= 15; i += 2){
        printf("%d\n",i);
        sema_post(&sema0_2);
        sema_wait(&sema0_1);
    }
    return NULL;
}

void
thread_create(pthread_t *thread_handle, void *(*thread_fn)(void *)) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    int rc = pthread_create(thread_handle,
            &attr,
            thread_fn,
            NULL);
    if(rc != 0){
        printf("Error occurred\n");
        exit(0);
    }
}

int
main(int argc, char **argv){
    sema_init(&sema0_1, 0);
    sema_init(&sema0_2, 0);
    thread_create(&even_thread, thread_fn_callback_even);
    thread_create(&odd_thread, thread_fn_callback_odd);
    pthread_join(even_thread, NULL);
    pthread_join(odd_thread, NULL);
    sema_destroy(&sema0_1);
    sema_destroy(&sema0_2);
    return 0;
}

