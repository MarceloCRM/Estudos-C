#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STATUS CODES

#define SUCCESS 0
#define ERROR_INVALID_POSITION 1
#define ERROR_TOO_LONG 2
#define ERROR_INPUT_INVALID 3
#define ERROR_INPUT_EMPTY 4

// MAX LENGTH

#define MAX_TASKS 100
#define MAX_DESCRIPTION_LENGTH 50

struct Task
{
    int id;
    char description[MAX_DESCRIPTION_LENGTH];
    int status;
};


struct Task tasks[MAX_TASKS];
int total;

int readLine(char string[], int length){
    if (fgets(string, length, stdin) == NULL) {
        return ERROR_INPUT_INVALID;
    }
    if (strchr(string, '\n') == NULL ) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return ERROR_TOO_LONG;
    }

    string[strcspn(string, "\n")] = '\0';
    
    if (string[0] == '\0') {
        return ERROR_INPUT_EMPTY;
    }

    return SUCCESS;
}

int readInt(char string[]){

}

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

void newTask(char descrip[MAX_DESCRIPTION_LENGTH]) {
    struct Task t;

    t.id = total + 1;
    strcpy(t.description, descrip);
    t.status = 0;

    tasks[total] = t;
    total++;
}

int editTask(char newDescrip[MAX_DESCRIPTION_LENGTH], int index) {
    if (index <= 0 || index > total){
        return ERROR_INVALID_POSITION;
    }

    struct Task t = tasks[index-1];
    strcpy(t.description, newDescrip);
    tasks[index-1] = t;
    return SUCCESS;
}

int changeStatus(int index) {
    if (index <= 0 || index > total){
        return ERROR_INVALID_POSITION;
    }

    tasks[index-1].status = !tasks[index - 1].status;
    return SUCCESS;

}

int deleteTask(int index) {
    if (index <= 0 || index > total) {
        return ERROR_INVALID_POSITION;
    }

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

int main() {
    int option = 0; 
    char buffer[10];

    while (option != 6){
        system("clear");
        printf("1 - Show tasks\n2 - New task\n3 - Change status\n4 - Edit task\n5 - Delete task\n6 - Exit\n\n");
        printf("--> ");
        readLine(buffer, sizeof(buffer));
        option = atoi(buffer);

        int c;
        if (option == 1){
            system("clear");
            showTask(tasks, total);
            printf("\nPress enter to go back to the menu...");
            while (getchar() != '\n');
        }
        else if (option == 2) {
            char descrip[MAX_DESCRIPTION_LENGTH];
            int statusError;

            do {
                system("clear");
                printf("Write the task name: \n--> ");
                statusError = readLine(descrip, MAX_DESCRIPTION_LENGTH);

                if (statusError == ERROR_TOO_LONG) {
                    printf("\nText too long. Maximum %d characters.\nPress enter to try again...", MAX_DESCRIPTION_LENGTH);
                    while (getchar() != '\n');
                }
                else if (statusError == ERROR_INPUT_EMPTY) {
                    printf("\nText is empty.\nPress enter to try again...");
                    while (getchar() != '\n');
                }
                else if (statusError == SUCCESS)
                {
                    newTask(descrip);           
                }
                else {
                    printf("\nUnexpected error.\nPress enter to try again...");
                    while (getchar() != '\n');
                }
                
            } while (statusError != SUCCESS);
            
            printf("\nSuccess!\nPress enter to go back to the menu...");
            while (getchar() != '\n');
        }
        else if (option == 3) {
            int id;
            int statusError;
            do {
                system("clear");
                printf("Write the task id: \n--> ");
                readLine(buffer, sizeof(buffer));
                id = atoi(buffer);
                statusError = changeStatus(id);
                if (statusError == ERROR_INVALID_POSITION){
                    printf("\nId not found.\nPress enter to try again...");
                    while (getchar() != '\n');
                }
            } while (statusError != SUCCESS);

            printf("\nStatus changed to %s!!\nPress enter to go back to the menu...", tasks[id - 1].status ? "Done" : "In progess");
            while (getchar() != '\n');
        }
        else if (option == 4) {
            int id;
            char newDescrip[MAX_DESCRIPTION_LENGTH];
            int statusErrorInput;
            int statusErrorEdit;

            do {
                system("clear");

                printf("Write the task id: \n--> ");

                readLine(buffer, sizeof(buffer));
                id = atoi(buffer);

                printf("Write the task name: \n--> ");

                statusErrorInput = readLine(newDescrip, MAX_DESCRIPTION_LENGTH);

                if (statusErrorInput == ERROR_TOO_LONG){
                    printf("\nText too long. Maximum %d characters.\nPress enter to try again...", MAX_DESCRIPTION_LENGTH);
                    while (getchar() != '\n');
                }
                else if (statusErrorInput == ERROR_INPUT_EMPTY) {
                    printf("\nText is empty.\nPress enter to try again...");
                    while (getchar() != '\n');
                }
                else {
                    statusErrorEdit = editTask(newDescrip, id);
                    if (statusErrorEdit == ERROR_INVALID_POSITION){
                        printf("\nId not found.\nPress enter to try again...");
                        while (getchar() != '\n');
                    }
                }
            } while (statusErrorEdit != SUCCESS);

            printf("\nSuccess!\nPress enter to go back to the menu...");
            while (getchar() != '\n');
        }
        else if (option == 5){
            int id;
            int statusErrorDelete;
            do {
                system("clear");
                printf("Write the task id: \n--> ");

                readLine(buffer, sizeof(buffer));
                id = atoi(buffer);

                statusErrorDelete = deleteTask(id);
                if (statusErrorDelete == ERROR_INVALID_POSITION){
                    printf("\nId not found.\nPress entre to try again...");
                    while (getchar() != '\n');
                }

            } while (statusErrorDelete != SUCCESS);

            printf("\nSuccess!\nPress enter to go back to the menu...");
            while (getchar() != '\n');
        } 
        else if (option == 6){
            printf("\nGood bye.\n");
        }
        else {
            system("clear");
            printf("\nChoice is not valid.\n");
            printf("\nPress enter to try again...");
            while (getchar() != '\n');
        }
    }
    return 0;
}