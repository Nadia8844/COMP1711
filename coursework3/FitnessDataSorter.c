#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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
            }
        }
    }
}

bool isValidRecord(char *record, char delimiter) {
    char date[11], time[6];
    int steps;
    char *tmp = strdup(record);  // Create a temporary copy of record for validation

    tokeniseRecord(tmp, delimiter, date, time, &steps);
    free(tmp);  // Free the temporary copy

    // Check if any field is empty or if steps are not valid (atoi returns 0 for invalid conversion)
    if (date[0] == '\0' || time[0] == '\0' || steps == 0) {
        return false;
    }

    return true;
}

// Function to compare fitness data (for sorting)
int compareFitnessData(const void *a, const void *b) {
    FitnessData *dataA = (FitnessData *)a;
    FitnessData *dataB = (FitnessData *)b;
    return dataB->steps - dataA->steps;
}

int main() {
    char filename[256];
    printf("Enter filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: invalid file\n");
        return 1;
    }

    FitnessData data[1000];
    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        if (!isValidRecord(line, ',')) {
            printf("Error: invalid file (non-numeric steps)\n");
            fclose(file);
            return 1;
        }

        tokeniseRecord(line, ',', data[count].date, data[count].time, &data[count].steps);
        count++;
    }
    fclose(file);

    // Sort the data
    qsort(data, count, sizeof(FitnessData), compareFitnessData);

    // Create output file name
    char outputFilename[260];
    snprintf(outputFilename, sizeof(outputFilename), "%s.tsv", filename);

    // Write sorted data to new file
    FILE *outputFile = fopen(outputFilename, "w");
    for (int i = 0; i < count; i++) {
        fprintf(outputFile, "%s\t%s\t%d\n", data[i].date, data[i].time, data[i].steps);
    }
    fclose(outputFile);

    printf("Data sorted and written to %s\n", outputFilename);

    return 0;
}



