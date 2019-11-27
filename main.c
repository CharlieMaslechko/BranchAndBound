#include <stdio.h>

    
const int tasksAmount = 5;
const int amountOfPeople = 5;
struct Person *Persons[amountOfPeople];
int globalUpper;
int globalLower;

//Make dynamic later
struct PartialSolution *Partials[1000];
int partialIndexLast = 0;


    
struct LowerUpperManager{
    int lower;
    int upper;
};

struct PartialSolution{
    int *taskAssignments;
    struct LowerUpperManager *LPManager;
};

struct Person{
    int *tasks;
};

struct LowerUpperManager* createLUM(){
    struct LowerUpperManager *newManager = (struct LowerUpperManager *)(malloc(sizeof(struct LowerUpperManager)));
    newManager->lower = -1;
    newManager->upper = -1;
    return newManager;
}

struct PartialSolution* createPartial(int *assignments){
    struct PartialSolution *newPartial = (struct PartialSolution*)(malloc(sizeof(struct PartialSolution)));
    struct LowerUpperManager *LPManager = createLUM();
    newPartial->taskAssignments = assignments; 
    return newPartial;
}

void addPartial(struct PartialSolution *givenSolution){
    partialIndexLast++;
    Partials[partialIndexLast] = givenSolution;
}
void deletePartial(struct PartialSolution *givenSolution){
    Partials[partialIndexLast] = NULL;
    partialIndexLast--;
}

//returns the index of number in an array
int getMinIndex(int *x){
    int min = 0;
    for (int i = 1; i < amountOfPeople; i++){
        if (x[i] < x[min]){
             min = i;
        }
    }
    return min;
}

void printPartial(struct PartialSolution *givenSolution){
    printf("PARTIAL SOLUTION: ");
    for (int i = 0; i < tasksAmount; i++){
        printf("%d,", givenSolution->taskAssignments[i]);
    }
}

struct Person* createPerson(int* taskTimes, int size){
    int* newTasks = (int*)(malloc(sizeof(int) * size));
    struct Person *newPerson = (struct Person*)(malloc(sizeof(struct Person)));
    for (int i = 0; i < size; i++){
        newTasks[i] = taskTimes[i];
    }
    newPerson->tasks = newTasks;
    return newPerson;
    
}

//returns the last assigned task given a partial solution
int getLastAssignedTask(int* taskAssignments){
    int index = 0;
    while(taskAssignments[index] != -1){
        index++;
    }
    //else if it is -1 then minus 1 from that is the end
    index--;
    return index;
}

//given a partial get CSF (currently works properly)
int getCSF(struct PartialSolution *givenSolution){
     int lastIndex = getLastAssignedTask(givenSolution->taskAssignments);
     int csf = 0;
     printf("last index is %d ", lastIndex);
     //index +1 is the person assigned then pull the value which is the task
     for (int i = 0; i < lastIndex+1; i++){
       struct Person *currentPerson = Persons[i];
        //To get cost of task x get from task[x] from y person
        //The reason it is i-1 is since we want to input what is the cost of t
        csf += currentPerson->tasks[givenSolution->taskAssignments[i] - 1];
     }
     return csf;
}

//given a partial get GFC
int getGFC(struct PartialSolution *givenSolution){
    int lastIndex = getLastAssignedTask(givenSolution->taskAssignments);
    int amount = lastIndex + 1;
    int blackList[amount];
    printf("\n\nBLACK LIST these are tasks that are set in stone: ");
    for (int i = 0; i < lastIndex + 1; i++){
        blackList[i] = givenSolution->taskAssignments[i];
    }
    //Now we have a set of tasks that cant be chosen from
    
    
    return 0;
}

//Given a partial solution get the lower and upperbound
struct LowerUpperManager* getLowerUpper(struct PartialSolution *givenSolution){
    //so given that a solution where person 1 was assigned task 1
    int lastIndex = getLastAssignedTask(givenSolution->taskAssignments);
    //given that a partial solution get what task it was assignmedn
}

int main(int argc, char **argv){

	int a[] = {10, 15, 4, 12, 9};
    int b[] = {7, 18, 3, 10, 16};
    int c[] = {4, 5, 14, 12, 10};
    int d[] = {17, 2, 18, 6, 21};
    int e[] = {21, 18, 2, 10, 25};
    

    struct Person *Person1 = createPerson(a, tasksAmount);
    struct Person *Person2 = createPerson(b, tasksAmount);
    struct Person *Person3 = createPerson(c, tasksAmount);
    struct Person *Person4 = createPerson(d, tasksAmount);
    struct Person *Person5 = createPerson(e, tasksAmount);
   
    Persons[0] = Person1;
    Persons[1] = Person2;
    Persons[2] = Person3;
    Persons[3] = Person4;
    Persons[4] = Person5;
    
    
    printf("***INPUT***\n");
    for (int i = 0; i < 5; i++){
        struct Person *getCurrPers = Persons[i];

        for (int j = 0; j < 5; j++){
            printf("%d, ", getCurrPers->tasks[j]);
        }
        printf("\n");
    }
    printf("====================");
    //if I create a partial solution
    //Assign task 3 to person 1
    int partial[5] = {3, 2, -1, -1, -1};
    struct PartialSolution* newPartial = createPartial(partial);
    printPartial(newPartial);
    printf("CSF IS: %d", getGFC(newPartial));
    
}
