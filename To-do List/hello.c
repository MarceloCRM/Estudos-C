#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Task
{
    int id;
    char description[50];
    int status;
};


struct Task tasks[100];
int total;


void showTask(struct Task tasks[], int total) {
    if (total == 0) {
        printf("No tasks found.\n");
    }
    else{
        for (int i = 0; i < total; i++) {
            printf("%d) %s - ", tasks[i].id, tasks[i].description);
            if (tasks[i].status == 1) {
                printf("Done\n");
            }
            else {
                printf("In progress\n");
            }
        }
    }
}

void newTask(char descrip[50]) {
    struct Task t;

    t.id = total + 1;
    strcpy(t.description, descrip);
    t.status = 0;

    tasks[total] = t;
    total++;
}


int main() {
    int option = -1; 

    while (option != 0){
        system("clear");
        printf("0 - Exit\n1 - Show tasks\n2 - New task\n3 - Edit task\n4 - Delete task\n\n");
        printf("--> ");
        scanf("%d", &option);
        if (option == 1){
            system("clear");
            showTask(tasks, total);
            printf("\nPress enter to go back to the menu...");
            getchar();
            getchar();  
        }
        else if (option == 2) {
            char descrip[50];

            system("clear");
            printf("Write the task name: \n--> ");
            scanf(" %[^\n]", descrip);

            newTask(descrip);
            
            printf("\nSucess!!\nPress enter to go back to the menu...");
            getchar();
            getchar();
        }
        else if (option == 3) {
            //EditTask();
        }
        else if (option == 4){
            //DeleteTask();
        } 
    }
    return 0;
}