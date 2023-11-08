#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUBSTRINGS 100
#define MAX_LENGTH 100

char* needleman_wunsch(char *s1, char *s2) {
    int m = strlen(s1);
    int n = strlen(s2);
    int dp[MAX_LENGTH + 1][MAX_LENGTH + 1];
    int i, j;

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = i + j;
            } else if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + ((dp[i - 1][j] < dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1]);
            }
        }
    }

    i = m;
    j = n;
    char *result = (char *)malloc((m + n) * sizeof(char));
    int k = 0;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            result[k++] = s1[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] < dp[i][j - 1]) {
            result[k++] = s1[i - 1];
            i--;
        } else {
            result[k++] = s2[j - 1];
            j--;
        }
    }

    while (i > 0) {
        result[k++] = s1[i - 1];
        i--;
    }
    while (j > 0) {
        result[k++] = s2[j - 1];
        j--;
    }
    result[k] = '\0';

    int len = strlen(result);
    for (i = 0; i < len / 2; i++) {
        char temp = result[i];
        result[i] = result[len - i - 1];
        result[len - i - 1] = temp;
    }

    return result;
}

int main() {
    char substrings[MAX_SUBSTRINGS][MAX_LENGTH];
    int count = 0;
    int num_substrings;

    printf("Enter the number of substrings: ");
    scanf("%d", &num_substrings);

    if (num_substrings < 2 || num_substrings > MAX_SUBSTRINGS) {
        printf("Invalid number of substrings.\n");
        return 1;
    }

    printf("Enter %d substrings:\n", num_substrings);
    for (int i = 0; i < num_substrings; i++) {
        printf("Enter substring %d: ", i + 1);
        scanf("%s", substrings[i]);
    }

    char *result = needleman_wunsch(substrings[0], substrings[1]);
    for (int i = 2; i < num_substrings; i++) {
        char *temp = needleman_wunsch(result, substrings[i]);
        strcpy(result, temp);
        free(temp);
    }

    printf("Constructed word: %s\n", result);

    free(result);

    return 0;
}
