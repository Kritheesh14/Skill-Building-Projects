#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

int main() {
    char expr[MAX];
    int sizeLimit;

    printf("Set expression size limit (max %d): ", MAX);
    scanf("%d", &sizeLimit);
    getchar();

    if (sizeLimit > MAX) {
        printf("Error: Size exceeds maximum limit.\n");
        return 1;
    }

    printf("Enter expression (or type 'file' to read from file): ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = '\0';

    if (strcmp(expr, "file") == 0) {
        char filename[50];
        FILE *fp;

        printf("Enter filename: ");
        scanf("%s", filename);

        fp = fopen(filename, "r");
        if (!fp) {
            printf("Error: File not found.\n");
            return 1;
        }

        printf("\n--- Results from file ---\n");
        while (fgets(expr, sizeof(expr), fp)) {
            expr[strcspn(expr, "\n")] = '\0';
            if (strlen(expr) == 0) continue;
            printf("%s = %.2f\n", expr, eval(expr));
        }
        fclose(fp);
    }
    else {
        printf("Result: %.2f\n", eval(expr));
    }

    return 0;
}
