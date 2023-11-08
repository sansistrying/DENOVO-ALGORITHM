#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 100
#define MAX_SUBSTRINGS 100

// Define a struct to represent a state in the DFS stack
struct DFSState {
    char current_string[MAX_LENGTH];
    char remaining_strings[MAX_SUBSTRINGS][MAX_LENGTH];
};

// Function to check if two strings can be merged
int can_merge(char* current, char* remaining) {
    if (strlen(current) >= 2 && strlen(remaining) >= 2) {
        return current[strlen(current) - 2] == remaining[0] && current[strlen(current) - 1] == remaining[1];
    }
    return 0;
}

int main() {
    struct DFSState stack[MAX_SUBSTRINGS];
    int top = -1;

    char given_strings[MAX_SUBSTRINGS][MAX_LENGTH];
    int num_strings;

    printf("Enter the number of strings: ");
    scanf("%d", &num_strings);

    if (num_strings > MAX_SUBSTRINGS) {
        printf("Exceeded the maximum number of strings.\n");
        return 1;
    }

    printf("Enter the strings:\n");
    for (int i = 0; i < num_strings; i++) {
        printf("Enter string %d: ", i + 1);
        scanf("%s", given_strings[i]);
    }

    // Initialize the stack with the first string and the remaining strings
    struct DFSState initial_state;
    strcpy(initial_state.current_string, given_strings[0]);
    for (int i = 1; i < num_strings; i++) {
        strcpy(initial_state.remaining_strings[i - 1], given_strings[i]);
    }

    stack[++top] = initial_state;

    // Initialize variables to track the best parent string and its similarity
    char best_parent_string[MAX_LENGTH];
    strcpy(best_parent_string, given_strings[0]);
    double best_similarity = 0.0;

    while (top >= 0) {
        // Pop a state from the stack
        struct DFSState current_state = stack[top--];

        if (current_state.remaining_strings[0][0] == '\0') {
            // No more strings to merge
            double similarity = (double)strlen(current_state.current_string) / (double)strlen(strcat(strdup(given_strings[0]), given_strings[1]));
            if (similarity > best_similarity) {
                best_similarity = similarity;
                strcpy(best_parent_string, current_state.current_string);
            }
        } else {
            for (int i = 0; current_state.remaining_strings[i][0] != '\0'; i++) {
                if (can_merge(current_state.current_string, current_state.remaining_strings[i])) {
                    char new_current[MAX_LENGTH];
                    strcpy(new_current, current_state.current_string);
                    strcat(new_current, current_state.remaining_strings[i] + 2);

                    struct DFSState new_state;
                    strcpy(new_state.current_string, new_current);

                    int j = 0;
                    for (int k = 0; current_state.remaining_strings[k][0] != '\0'; k++) {
                        if (k != i) {
                            strcpy(new_state.remaining_strings[j], current_state.remaining_strings[k]);
                            j++;
                        }
                    }
                    new_state.remaining_strings[j][0] = '\0';

                    stack[++top] = new_state;
                }
            }
        }
    }

    printf("Best parent string: %s\n", best_parent_string);

    return 0;
}
