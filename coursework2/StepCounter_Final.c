#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define BUFFER_SIZE 100

// Define an appropriate struct
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FITNESS_DATA;

void tokeniseRecord(const char *input, const char *delimiter, char *date, char *time, int *steps) {
    char *inputCopy = strdup(input);

    if (inputCopy == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return;
    }

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

    free(inputCopy);
}

int main() {
    FITNESS_DATA fitnessdata[MAX_RECORDS];

    char line[BUFFER_SIZE];
    char filename[BUFFER_SIZE];

    FILE *input = NULL;

    char choice;
    int counter = 0;

    while (1) {
        printf("Menu Options:\n");
        printf("A: Specify the filename to be imported\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: Find the date and time of the timeslot with the fewest steps\n");
        printf("D: Find the date and time of the timeslot with the largest number of steps\n");
        printf("E: Find the mean step count of all the records in the file\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");
        printf("Q: Quit\n");

        printf("Enter choice: ");
        choice = getchar();

        // Clear input buffer
        while (getchar() != '\n');

        switch (choice) {
            case 'A':
            case 'a':
                printf("Input filename: ");
                fgets(line, BUFFER_SIZE, stdin);

                if (sscanf(line, " %99s", filename) != 1) {
                    printf("Error: Invalid input for filename\n");
                    break;
                }

                input = fopen(filename, "r");
                if (!input) {
                    printf("Error: File could not be opened\n");
                    return 1;
                }

                counter = 0;
                while (fgets(line, BUFFER_SIZE, input) && counter < MAX_RECORDS) {
                    char date[11], time[6];
                    int steps;

                    tokeniseRecord(line, ",", date, time, &steps);

                    strcpy(fitnessdata[counter].date, date);
                    strcpy(fitnessdata[counter].time, time);
                    fitnessdata[counter].steps = steps;

                    counter++;
                }

                fclose(input);
                printf("File successfully loaded.\n");
                break;

            case 'B':
            case 'b':
                printf("Total records: %d\n", counter);
                break;

            case 'C':
            case 'c':
                if (counter == 0) {
                    printf("No data available. Load data first (Option A).\n");
                } else {
                    FITNESS_DATA fewestStepsSlot = fitnessdata[0];

                    for (int i = 1; i < counter; i++) {
                        if (fitnessdata[i].steps < fewestStepsSlot.steps) {
                            fewestStepsSlot = fitnessdata[i];
                        }
                    }

                    printf("Fewest steps: %s %s\n", fewestStepsSlot.date, fewestStepsSlot.time);
                }
                break;

            case 'D':
            case 'd':
                if (counter == 0) {
                    printf("No data available. Load data first (Option A).\n");
                } else {
                    FITNESS_DATA largestStepsSlot = fitnessdata[0];

                    for (int i = 1; i < counter; i++) {
                        if (fitnessdata[i].steps > largestStepsSlot.steps) {
                            largestStepsSlot = fitnessdata[i];
                        }
                    }

                    printf("Largest steps: %s %s\n", largestStepsSlot.date, largestStepsSlot.time);
                }
                break;

            case 'E':
            case 'e':
                if (counter == 0) {
                    printf("No data available. Load data first (Option A).\n");
                } else {
                    long long totalSteps = 0; // Use long long to handle large totals

                    for (int i = 0; i < counter; i++) {
                        totalSteps += fitnessdata[i].steps;
                    }

                    double meanSteps = (double)totalSteps / counter;
                    int roundedMean = (int)(meanSteps + 0.5); // Round to the nearest integer

                    printf("Mean step count: %d\n", roundedMean);
                }
                break;

            case 'F':
            case 'f':
                if (counter == 0) {
                    printf("No data available. Load data first (Option A).\n");
                } else {
                    int currentLength = 0;
                    int maxLength = 0;
                    int startIdx = 0;

                    for (int i = 0; i < counter; i++) {
                        if (fitnessdata[i].steps > 500) {
                            currentLength++;
                        } else {
                            // Check if the current period is longer than the maximum
                            if (currentLength > maxLength) {
                                maxLength = currentLength;
                                startIdx = i - maxLength;
                            }

                            currentLength = 0;
                        }
                    }

                    if (currentLength > maxLength) {
                        startIdx = counter - currentLength;
                    }

                    printf("Longest period start: %s %s\n", fitnessdata[startIdx].date, fitnessdata[startIdx].time);
                    printf("Longest period end: %s %s\n", fitnessdata[startIdx + maxLength - 1].date,
                           fitnessdata[startIdx + maxLength - 1].time);
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
