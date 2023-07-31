#include"search_file.h"
pthread_t threads[MAX_THREADS];
pthread_mutex_t mutex;
pthread_cond_t cond;
unsigned int active_threads = 0;
void* parallel_search(void* args){
  active_threads++;
  char* filename = ((struct thread_data*)args)->filename;
  char* directory = ((struct thread_data*)args)->directory;
  printf("%s\n", directory);
  pthread_t* thread = ((struct thread_data*)args)->thread;
  DIR *dir = opendir(directory);
  if (dir == NULL) {
    perror("Directory do not opened\n");
    pthread_exit(NULL);
  }
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 or strcmp(entry->d_name, "..") == 0)
      continue;
    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);
    if (DT_DIR == entry->d_type) {
      while (active_threads >= MAX_THREADS) {
        pthread_cond_wait(&cond, &mutex);
      }
      struct thread_data new_thread_args;
      new_thread_args.filename = filename;
      new_thread_args.directory = entry->d_name;
      new_thread_args.thread = &threads[active_threads];
      pthread_create(&threads[active_threads], NULL, parallel_search, &new_thread_args);
    }
    if (DT_REG == entry->d_type and 0 == strcmp(entry->d_name, filename)) {
      printf("Found file: %s/%s\n", directory, filename);
      pthread_cancel(*thread);
      active_threads--;
      pthread_exit(NULL);
    }
  }
  closedir(dir);
  pthread_exit(NULL);
  active_threads--;
  return NULL;
}

void search(char* filename){
  struct thread_data args;
  args.filename = filename;
  args.directory = "/";
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);
  args.thread = &threads[active_threads];
  parallel_search(&args);
}
