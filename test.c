#include <stdio.h>
#include <string.h>

#define COLOR_BOLD "\e[1m"
#define COLOR_OFF "\e[m"

/// Task management program
int createTask();
void clearTasks();
void readTasks();

int main() {
    printf("Choose an option...\n");
    printf("(1) Create a task\n");
    printf("(2) Read list of tasks\n");
    printf("(3) Clear all tasks\n");

    int option;
    scanf("%i", &option);

    switch (option) {
        case 1:
            createTask();
            break;
        case 2:
            readTasks();
            break;
        case 3:
            clearTasks();
            break;
    }
}

int createTask() {
    fflush(stdin);
    char title[30];
    printf("\nTitle: (Max length of 30 characters)\n");
    scanf("%s", &title);

    if (strlen(title) > 30 || strlen(title) == 0) {
        printf("Title is too long or is empty");
        return 0;
    }

    fflush(stdin);

    char desc[200];
    printf("\nDescription: (Max length of 200 characters)\n");
    scanf("%s", &desc);

    if (strlen(desc) > 200 || strlen(title) == 0) {
        printf("Description is too long or is empty");
        return 0;
    }

    FILE *tfile;
    tfile = fopen("tasks.md", "r");

    int i = 0;
    do {
        if (tfile == NULL) {
            printf("\n\"tasks.md\" file not found, creating one now...");
            fclose(tfile);

            tfile = fopen("tasks.md", "w");
        } else {
            printf("\n\"tasks.md\" file found...");

            tfile = fopen("tasks.md", "a");
        }

        i++;

        if (i == 3) {
            printf("File could not be created or found\n");
            return 0;
        }
    }
    while (tfile == NULL);

    fprintf(tfile, "\033[1m%s\033[m\n%s\n\n", title, desc);
    fclose(tfile);

    printf("\nTask successfully written to \"tasks.md\"\n");
}

void readTasks() {
    printf("\nList of tasks...\n\n");

    FILE *tfile;
    tfile = fopen("tasks.md", "r");

    char tasks[65535];

    if(tfile != NULL) {
        while(fgets(tasks, 65535, tfile)) {
            printf("%s", tasks);
        }
    } else {
        printf("File does not have any tasks");
    }

    fclose(tfile);
}

void clearTasks() {
    fflush(stdin);
    printf("\nAre you sure you would like to clear ALL your tasks?\nY for yes, N for no\n");
    char confirm;
    scanf("%c", &confirm);

    switch (confirm) {
        case 'Y':
            printf("\nClearing all tasks...\n");
            if (remove("tasks.md") == 0) {
                printf("Tasks cleared successfully\n");
            } else {
                printf("Tasks were not able to be cleared\n");
            }
            break;

        case 'N':
            printf("\nTask clear canceled...\n");
            break;

        default:
            printf("\nInvalid option\n");
            clearTasks();
            break;
    }
}
