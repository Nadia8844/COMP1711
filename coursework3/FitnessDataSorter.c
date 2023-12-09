#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            } else {
                fprintf(stderr, "Error: invalid file (missing steps)\n");
                exit(1);
            }
        } else {
            fprintf(stderr, "Error: invalid file (missing time)\n");
            exit(1);
        }
    } else {
        fprintf(stderr, "Error: invalid file (missing date)\n");
        exit(1);
    }
}

// Function to compare two FitnessData records for sorting
int compareRecords(const void *a, const void *b) {
    return ((FitnessData *)b)->steps - ((FitnessData *)a)->steps;
}

int main() {
    char filename[256];

    // Step 1: Ask the user for a filename
    printf("Enter Filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");

    // Step 1: Ensure the filename is valid and the file can be opened
    if (file == NULL) {
        fprintf(stderr, "Error: invalid file\n");
        return 1;
    }

    // Read the file into an array
    FitnessData fitnessRecords[100]; // Adjust the size as needed
    int recordCount = 0;
    char line[100]; // Adjust the size as needed

    while (fgets(line, sizeof(line), file) != NULL && recordCount < 100) {
        tokeniseRecord(line, ',', fitnessRecords[recordCount].date, fitnessRecords[recordCount].time, &fitnessRecords[recordCount].steps);
        recordCount++;
    }

    fclose(file);

    // Step 2: Sort the data in descending order of steps
    qsort(fitnessRecords, recordCount, sizeof(FitnessData), compareRecords);

    // Step 3: Write out the sorted data to a new file with .tsv extension
    strcat(filename, ".tsv");
    FILE *outputFile = fopen(filename, "w");

    if (outputFile == NULL) {
        fprintf(stderr, "Error creating output file\n");
        return 1;
    }

    for (int i = 0; i < recordCount; i++) {
        fprintf(outputFile, "%s\t%s\t%d\n", fitnessRecords[i].date, fitnessRecords[i].time, fitnessRecords[i].steps);
    }

    fclose(outputFile);

    printf("Data sorted and written to %s\n", filename);

    // Successful execution
    return 0;
}
