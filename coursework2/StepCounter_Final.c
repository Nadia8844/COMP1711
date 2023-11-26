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
            fclose(input);
            printf("File successfully loaded.\n");
            break;
            
        case 'B':
        case 'b':
           
            printf("Total number of records: %d\n", counter);
            fclose(input);
            break;

        case 'C':
        case 'c':
        
            if (counter == 0) {
                printf("No data available. Load data first (Option A).\n");
            } else {
                FITNESS_DATA fewestStepsSlot = fitnessdata[0];

                // Find the timeslot with the fewest steps
                for (int i = 1; i < counter; i++) {
                    if (fitnessdata[i].steps < fewestStepsSlot.steps) {
                        fewestStepsSlot = fitnessdata[i];
                    }
                }

                // Display the timeslot with the fewest steps
                printf("Fewest steps: %s %s\n", fewestStepsSlot.date, fewestStepsSlot.time);
            }
                break;

        case 'D':
        case 'd':
            if (counter == 0) {
                printf("No data available. Load data first (Option A).\n");
            } else {
                FITNESS_DATA largestStepsSlot = fitnessdata[0];

                // Find the timeslot with the largest number of steps
                for (int i = 1; i < counter; i++) {
                    if (fitnessdata[i].steps > largestStepsSlot.steps) {
                        largestStepsSlot = fitnessdata[i];
                    }
                }

                // Display the timeslot with the largest number of steps (without the steps value)
                printf("Largest steps: %s %s\n", largestStepsSlot.date, largestStepsSlot.time);
            }
            break;

        case 'E':
        case 'e':
            if (counter == 0) {
                printf("No data available. Load data first (Option A).\n");
            } else {
                int totalSteps = 0;

                for (int i = 0; i < counter; i++) {
                    totalSteps += fitnessdata[i].steps;
                }

                float meanSteps = (float)totalSteps / counter;

                // Display the mean step count
                printf("Mean step count: %.0f\n", meanSteps);
            }
            break;

        case 'F':
        case 'f':
            if (counter == 0) {
                printf("No data available. Load data first (Option A).\n");
            } else {
                int currentlength = 0;
                int maxlength = 0;
                int startIdx = 0;

                // Iterate through the fitnessdata array
                for (int i = 0; i < counter; i++) {
                    if (fitnessdata[i].steps > 500) {
                        currentlength++;
                    } else {
                        // Check if the current period is longer than the maximum
                        if (currentlength > maxlength) {
                            maxlength = currentlength;
                            startIdx = i - maxlength;
                        }

                        currentlength = 0;
                    }
                }

                if (currentlength > maxlength) {
                    startIdx = counter - maxlength;
                }

                // Display the longest continuous period above 500 steps
                printf("Longest period start: %s %s\n", fitnessdata[startIdx].date, fitnessdata[startIdx].time);
                printf("Longest period end: %s %s\n", fitnessdata[startIdx + maxlength - 1].date, fitnessdata[startIdx + maxlength - 1].time);
            }
            break;


        case 'Q':
        case 'q':
            return 0;

        default:
            printf("Invalid choice\n");
            break;
        }
    }
}


