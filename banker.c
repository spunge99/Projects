#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_RESOURCES 10

int main(){
  char choice;
  int processNumber;
  int resourceNumber;
  int resourceBuffer[MAX_RESOURCES];
  int processBuffer[MAX_RESOURCES][MAX_RESOURCES*2];
  int availableBuffer[MAX_RESOURCES];
  int workBuffer[MAX_RESOURCES];
  int finishBuffer[MAX_RESOURCES];
  int safeBuffer[MAX_RESOURCES];
  int safe = 0;
  int i;
  int j;

  printf("\nEnter 'r' for random execution, 's' for hardcoded safestate,\n");
  printf("or 'u' for hardcoded unsafe state: ");
  scanf("%c",&choice);
  if(choice != 'r' && choice != 's' && choice != 'u'){
    printf("Error: Must use r, s, or u\n");
    return -1;
  }
  
  if(choice == 'r'){
    printf("Enter number of processes: ");
    scanf("%d", &processNumber);
    if(processNumber < 1 || processNumber > 10){
      printf("Error, must be between 1-9\n");
      return -1;
    }
    printf("Enter number of resources: ");
    scanf("%d", &resourceNumber);
    if(resourceNumber < 1 || resourceNumber > 10){
      printf("Error, must be between 1-9\n");
      return -1;
    }

    srand(time(NULL));
    
    for(i = 0; i < resourceNumber; i++){
      resourceBuffer[i] = rand() % 12 + 5;
    }
    for(i = 0; i< processNumber; i++){
      for(j = 0; j < resourceNumber * 2; j++){
	processBuffer[i][j] = rand() % 3;
	if(rand() % 5 > 2 && (processBuffer[i][j] != 0))
	  processBuffer[i][j]--;
      }
    }
    
  }
  else if(choice == 's'){
    processNumber = 5;
    resourceNumber = 3;
    resourceBuffer[0] = 9;
    resourceBuffer[1] = 5;
    resourceBuffer[2] = 7;
//process 0
    processBuffer[0][0] = 0;//Allocation 
    processBuffer[0][1] = 1;
    processBuffer[0][2] = 0;
    processBuffer[0][3] = 7;//Need
    processBuffer[0][4] = 4;
    processBuffer[0][5] = 3;
//process 1
    processBuffer[1][0] = 3;//Allocation q
    processBuffer[1][1] = 0;
    processBuffer[1][2] = 1;
    processBuffer[1][3] = 0;//Need
    processBuffer[1][4] = 2;
    processBuffer[1][5] = 1;
//process 2
    processBuffer[2][0] = 3;//Allocation 
    processBuffer[2][1] = 0;
    processBuffer[2][2] = 2;
    processBuffer[2][3] = 6;//Need
    processBuffer[2][4] = 0;
    processBuffer[2][5] = 0;
//process 3
    processBuffer[3][0] = 2;//Allocation 
    processBuffer[3][1] = 1;
    processBuffer[3][2] = 1;
    processBuffer[3][3] = 0;//Need
    processBuffer[3][4] = 1;
    processBuffer[3][5] = 1;
//process 4
    processBuffer[4][0] = 0;//Allocation 
    processBuffer[4][1] = 0;
    processBuffer[4][2] = 2;
    processBuffer[4][3] = 4;//Need
    processBuffer[4][4] = 3;
    processBuffer[4][5] = 1;

  }
  else if(choice == 'u'){
    processNumber = 5;
    resourceNumber = 3;
    resourceBuffer[0] = 9;
    resourceBuffer[1] = 5;
    resourceBuffer[2] = 7;
//process 0
    processBuffer[0][0] = 0;//Allocation 
    processBuffer[0][1] = 1;
    processBuffer[0][2] = 0;
    processBuffer[0][3] = 7;//Need
    processBuffer[0][4] = 4;
    processBuffer[0][5] = 3;
//process 1
    processBuffer[1][0] = 3;//Allocation q
    processBuffer[1][1] = 0;
    processBuffer[1][2] = 1;
    processBuffer[1][3] = 0;//Need
    processBuffer[1][4] = 2;
    processBuffer[1][5] = 1;
//process 2
    processBuffer[2][0] = 3;//Allocation 
    processBuffer[2][1] = 0;
    processBuffer[2][2] = 2;
    processBuffer[2][3] = 6;//Need
    processBuffer[2][4] = 0;
    processBuffer[2][5] = 0;
//process 3
    processBuffer[3][0] = 2;//Allocation 
    processBuffer[3][1] = 1;
    processBuffer[3][2] = 1;
    processBuffer[3][3] = 6;//Need
    processBuffer[3][4] = 1;
    processBuffer[3][5] = 1;
//process 4
    processBuffer[4][0] = 0;//Allocation 
    processBuffer[4][1] = 0;
    processBuffer[4][2] = 2;
    processBuffer[4][3] = 4;//Need
    processBuffer[4][4] = 3;
    processBuffer[4][5] = 1;
  }
 
//Filling availableBuffer[]
  for(i = 0; i < resourceNumber; i++){
    int sum = 0;
    for(j = 0; j < processNumber; j++){
      sum += processBuffer[j][i];
    }
    availableBuffer[i] = resourceBuffer[i] - sum;
  }

//Print buffers
  printf("\nProcess\t| Allocation\t| Need\t\t| Available\n");
  
  printf("\t| ");
  for(i = 0; i < resourceNumber; i++){
    printf("%c ", 65 + i);
  }
  printf("\t| ");
  for(i = 0; i < resourceNumber; i++){
    printf("%c ", 65 + i);
  }
  printf("\t| ");
  for(i = 0; i < resourceNumber; i++){
    printf("%c ", 65 + i);
  }
  printf("\n");
  printf("___________________________________________________\n");

  int printed = 0;
  for(i = 0; i < processNumber; i++){
    printf("P%d\t| ", i);
    for(j = 0; j < resourceNumber; j++){
      printf("%d ", processBuffer[i][j]);
    }
    printf("\t| ");
    for(j; j < resourceNumber * 2; j++){
      printf("%d ", processBuffer[i][j]);
    }
    printf("\t| ");
    if(!printed){
      for(j = 0; j < resourceNumber; j++){
	printf("%d ", availableBuffer[j]);
      }
      printed = 1;
    }
    printf("\n");
  }

//Bankers Algorithm

//Inititialize
  for(i = 0; i < resourceNumber; i++){
    workBuffer[i] = availableBuffer[i];
  }
  for(i = 0; i < processNumber; i++){
    finishBuffer[i] = 0;
  }
  printf("\nWork\n");

//Algorithm
  i = 0;
  int s = 0;
  int done = 0;
  while(!safe && i < processNumber){
    int less = 0;

    if(i == 0){
      for(j = 0; j < resourceNumber; j++){
	printf("%d ", workBuffer[j]);
      }
      printf("\n");
    }

    for(j = 0; j < resourceNumber; j++){
      if(processBuffer[i][j+resourceNumber] <= workBuffer[j]){
	less++;
      }

    }
    if(less == resourceNumber && (finishBuffer[i] == 0)){
      safeBuffer[s] = i;
      s++;

      finishBuffer[i] = 1;
      for(j = 0; j < resourceNumber; j++){
	workBuffer[j] += processBuffer[i][j]; 
      }
      done++;
      i = -1;
    }
    
    if(done == processNumber){
      safe = 1;
    }
    i++;
  }//end of algorithm

  if(safe == 1){
    printf("\nMachine in SAFE State\n");
    printf("Possible Process order: ");
    for(i = 0; i < processNumber; i++){
      printf("%d ", safeBuffer[i]);
    }
    printf("\n");
  }
  else{
    printf("\nMacine in UNSAFE State\n");
    printf("No possible process orders\n");
  }
}

