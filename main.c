#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/stat.h>
#include "single.h"
#include "multi.h"
#include "parse.h"

int main() {
  char * f = "questions.txt";

  printf("-----------------------------------------\n");
  printf("Welcome to the single player QuizWiz mode!\n");
  printf("-----------------------------------------\n");

  // Receive username
  char username[16];
  printf("Enter username: ");
  fgets(username, 16, stdin);
  username[strlen(username)-1] = '\0';
  printf("Welcome %s!\n", username);

  // Sets up semaphores
  us.val = 1;
  sb.sem_num = 0;
  sb.sem_op = -1;
  createSemaphore();

  // receive input of number of questions desired
  int databaseMax = getMaxQuestions(f);
  printf("There are currently %d questions in the database\n", databaseMax);
  printf("Enter number of questions desired: ");
  char input[8];
  fgets(input, 8, stdin);
  int n = atoi(input);
  int score = singleGame(f, n);

  updateLeaderboard(username, score);
  viewLeaderboard();
  removeSemaphore();
  return 0;
}
