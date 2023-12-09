#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "FitnessDataStruct.h"  // Include the header file
#define MAX_RECORDS 1000
#define buffer_size 1000

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array

// Helper function prototype
void tokeniseRecord(const char *input, const char *delimiter, char *date, char *time, char *steps);

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Outputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
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
        strcpy(steps, token);
    }

    // Free the duplicated string
    free(inputCopy);
}


int main() 
{
   FITNESS_DATA fitnessdata[MAX_RECORDS];

    char line[buffer_size];
    char filename[buffer_size];
    double meanFloat = 0.0;

    FILE *input = NULL;

    char choice;
    int counter = 0;

    while (1)
    {
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
        while (getchar() != '\n');

        switch (choice)
        {
            case 'A':
            case 'a':
            printf("Input filename: ");
            fgets(line, 200, stdin);
            sscanf(line, " %s ", filename);

                input = fopen(filename, "r");
                    if (!input) {
                        printf("Error: File could not be opened\n");
                        return 1;}
                    

                counter = 0;
                while (fgets(line, buffer_size, input)) {
                    if (counter >= MAX_RECORDS) {
                        printf("Maximum records exceeded. Data truncated.\n");
                        break;
                    }

                    char date[11], time[6], stepss[100];
                    
                    tokeniseRecord(line, ",", date, time, stepss);

                    strcpy(fitnessdata[counter].date, date);
                    strcpy(fitnessdata[counter].time, time);
                    fitnessdata[counter].steps = atoi(stepss);

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
            input = fopen(filename, "r");
            if (!input) {
            printf("Error opening file\n");
             break;
            }

            meanFloat = 0.0;
            counter = 0;

            char date[20], time[20], stepss[10000];

            while (fgets(line, buffer_size, input)) {
            tokeniseRecord(line, ",", date, time, stepss);
            fitnessdata[counter].steps = atoi(stepss);
            meanFloat += fitnessdata[counter].steps;
            counter++;
             }

            fclose(input);

            if (counter == 0) {
        printf("No records in the file\n");
        } else {
            meanFloat /= counter;
            int meansteps = (int)meanFloat;
            printf("Mean step count: %d\n", meansteps);
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