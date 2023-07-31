#include<iso646.h>
#include<stddef.h>
#include<unistd.h>
#include<dirent.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef SEARCH_H
#define SEARCH_H
struct thread_data{
  char* filename;
  char* directory;
  pthread_t* thread;
};
void search(char*);
#define MAX_THREADS 8
#endif
