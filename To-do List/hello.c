#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Erros codes

#define SUCCESS 0
#define ERROR_INVALID_POSITION 1
#define ERROR_TOO_LONG 2


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

void editTask(char newDescrip[50], int index) {
    struct Task t = tasks[index-1];
    strcpy(t.description, newDescrip);
    tasks[index-1] = t;
}

int changeStatus(int index) {
    if (tasks[index-1].status == 0) {
        tasks[index-1].status = 1;
        return 1;
    }
    else{
        tasks[index-1].id = 0;
        return 0;
    }
}

int deleteTask(int index) {
    if (index <= 0 || index > total) {
        return ERROR_INVALID_POSITION;
    }
    else {
        int i = index - 1;
    
        for ( int j = i; j < total - 1; j++) {
            tasks[j] = tasks[j + 1];
        }
    
        total--;
    
        for (int i = 0; i < total; i++) {
            tasks[i].id = i + 1;
        }
        return SUCCESS;
    }
}

int main() {
    int option = -1; 

    while (option != 0){
        system("clear");
        printf("0 - Exit\n1 - Show tasks\n2 - New task\n3 - Change status\n4 - Edit task\n5 - Delete task\n\n");
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
            int id;
            system("clear");

            printf("Write task id: \n--> ");
            scanf("%d", &id);

            int status = changeStatus(id);

            printf("\nStatus changed to %s!!\nPress enter to go back to the menu...", status ? "Done" : "In progress");
            getchar();
            getchar();
        }
        else if (option == 4) {
            int id;
            char newDescrip[50];

            system("clear");

            printf("Write task id: \n--> ");
            scanf("%d", &id);

            printf("Write the new task name: \n--> ");
            scanf(" %[^\n]", newDescrip);

            editTask(newDescrip, id);

            printf("\nSucess!!\nPress enter to go back to the menu...");
            getchar();
            getchar();
        }
        else if (option == 5){
            int id;

            system("clear");

            printf("Write task id: \n--> ");
            scanf("%d", &id);

            int status = deleteTask(id);

            printf("\n%s\nPress enter to go back to the menu...", status ? "Id not found." : "Sucess!");
            getchar();
            getchar();
        } 
        else if (option == 0){
            printf("\nGood bye.\n");
        }
        else {
            system("clear");
            printf("Choice is not valid.");
            printf("\nSucess!!\nPress enter to go back to the menu...");
            getchar();
            getchar();
        }
    }
    return 0;
}