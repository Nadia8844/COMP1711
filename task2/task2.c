#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

#define MAX_RECORDS 100

// Define an appropriate struct
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FITNESS_DATA;

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
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




// Complete the main function
int main() {
       char filename[] = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening the file\n");
        return 1;
    }

    const int buffer_size = 100;
    char line_buffer[buffer_size];
    FITNESS_DATA fitnessdata[MAX_RECORDS];
    int dataCount = 0;
        
    char date[11];
    char time[6];
    char steps[10];

    while (fgets(line_buffer, buffer_size, file) != NULL) {
        
        
        tokeniseRecord(line_buffer, ",", date, time, steps);

        FITNESS_DATA data;
        strcpy(data.date, date);
        strcpy(data.time, time);
        data.steps = atoi(steps);
        fitnessdata[dataCount] = data;
        dataCount++;
    }

        printf("Number of records in file: %d\n", dataCount);

        for (int i = 0; i < 3; i++) {
        printf("%s/%s/%d\n", fitnessdata[i].date, fitnessdata[i].time, fitnessdata[i].steps);
        }
    

    fclose(file);
    return 0;
}
