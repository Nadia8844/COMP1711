#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define buffer_size 100

// Define an appropriate struct
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FITNESS_DATA;

void tokeniseRecord(const char *input, const char *delimiter, char *date, char *time, int *steps) {

    char *inputCopy = strdup(input);

    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {
        strcpy(date, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        *steps = atoi(token);
    }

    // Free the duplicated string
    free(inputCopy);
}

int main()
{
    // array of fitness data
    FITNESS_DATA fitnessdata[MAX_RECORDS];

    char line[buffer_size];
    char filename[buffer_size];

    // get filename from the user
    printf("Please enter the name of the data file: ");

    // these lines read in a line from the stdin (where the user types)
    // and then take the actual string out of it
    // this removes any spaces or newlines.
    fgets(line, buffer_size, stdin);
    sscanf(line, " %s ", filename);

    char choice;
    int counter = 0;
    double mean = 0;

    while (1)
    {
        FILE *input = fopen(filename, "r");
        if (!input)
        {
            printf("Error: File could not be opened\n");
            return 1;
        }

        printf("A: Display all fitness data\n");              
        printf("B: Display the total number of records\n");     
        printf("C: Find the timeslot with the fewest steps\n"); 
        printf("D: Find the timeslot with the largest number of steps\n"); 
        printf("E: Calculate the mean step count\n");         
        printf("F: Find the longest continuous period above 500 steps\n");  
        printf("Q: Exit the program\n");

    
        choice = getchar();

        while (getchar() != '\n');

        switch (choice)
        {

        case 'A':
        case 'a':
            counter = 0;
            while (fgets(line, buffer_size, input))
            {

                tokeniseRecord(line, ",", fitnessdata[counter].date, fitnessdata[counter].time, &fitnessdata[counter].steps);
                counter++;
            }
            for (int i = 0; i < counter; i++)
            {
                printf("%s/%s - Steps: %d\n", fitnessdata[i].date, fitnessdata[i].time, fitnessdata[i].steps);
            }
            fclose(input);
            break;

        case 'B':
        case 'b':
            printf("Total number of records: %d\n", counter);
            fclose(input);
            break;

        case 'C':
        case 'c':

            break;

        case 'D':
        case 'd':

            break;

        case 'E':
        case 'e':

            break;

        case 'F':
        case 'f':
            // Implement logic to find the longest continuous period above 500 steps
            break;

        case 'Q':
        case 'q':
            return 0;

        // if they type anything else:
        default:
            printf("Invalid choice\n");
            break;
        }
    }
}

