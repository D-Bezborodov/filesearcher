/* Application (App) to find file on Local Host
 * ============================================================================================================
 * 1. App has to find file by "name"
 *
 * 2. Search has to be started from root "/" directory. (or Disk "C:\ " en Windows OS)
 *
 * 3. To make this search faster - App creates new Searching Thread for each sub-directory in root directory,
 * but not more than 8 Execution Threads.
 * 
 * 4. Thread who will find needed file has to print Full Path to the file and has to notify all the rest
 * threads to stop searching
 * ============================================================================================================
 * - Logic “to search file” has to be placed into static library.
 * - Application just uses this library to find files in a fast way.
 * - Static Library compilation has to be done separately from Application.
 * - Compiler: GCC or G++.
 * - Use Makefile for conpilation/linking instructions
 * ============================================================================================================
 * Things to Google: (Concurrency, Makefile, GCC, Static Library)
 */
#include"search_file.h"
#include<stddef.h>
#include<iso646.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char* argv[]){
  if (2 > argc) {
    printf("Usage: ./%s <searched_filename>\n", PROGRAM_NAME);
    return 1;
  } else if (2 < argc) {
    printf("Usage: ./%s 'searched filename'\n", PROGRAM_NAME);
    return 1;
  }
  search(argv[1]);
  return 0;
}
