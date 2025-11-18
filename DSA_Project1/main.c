#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"
#include "gui.h"

int run_cli();

int main(int argc, char *argv[]) {
    int mode;
    
    printf("=== Expression Calculator ===\n");
    printf("Select mode:\n");
    printf("1. CLI (Command Line Interface)\n");
    printf("2. GUI (Graphical User Interface)\n");
    printf("Enter choice (1-2): ");
    
    if (scanf("%d", &mode) != 1) { // Defaults to CLI
        mode = 1; 
    }
    getchar();
    
    if (mode == 2) {
        printf("Starting GUI mode...\n");
        run_gui(argc, argv);
    } else {
        printf("Starting CLI mode...\n\n");
        run_cli();
    }
    
    return 0;
}

int run_cli() {
    char expr[EXPR_MAX];
    int sizeLimit;
    int exprType;

    printf("Set expression size limit (max %d): ", EXPR_MAX);
    scanf("%d", &sizeLimit);
    getchar();

    if (sizeLimit > EXPR_MAX) {
        printf("Error: Size exceeds maximum limit.\n");
        return 1;
    }

    printf("\nInput expression type:\n");
    printf("1. Infix [default]\n");
    printf("2. Postfix\n");
    printf("3. Prefix\n");
    printf("Enter choice (1-3): ");
    
    if (scanf("%d", &exprType) != 1) {
        exprType = 1; // Default to infix
    }
    getchar();

    if (exprType < 1 || exprType > 3) {
        exprType = 1; // Default to infix if invalid input
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
            expr[strcspn(expr, "\n")] = '\0'; //strcspn(str1, str2) does a search of str1 against str2. For if character in str1 in str2 it stops the search.
            if (strlen(expr) == 0) continue;
            
            double result;
            switch(exprType) {
                case 2:
                    result = evalPostfix(expr);
                    break;
                case 3:
                    result = evalPrefix(expr);
                    break;
                default:
                    result = eval(expr);
                    break;
            }
            printf("%s = %.2f\n", expr, result);
        }
        fclose(fp);
    }
    else {
        double result;
        switch(exprType) {
            case 2:
                result = evalPostfix(expr);
                break;
            case 3:
                result = evalPrefix(expr);
                break;
            default:
                result = eval(expr);
                break;
        }
        printf("Result: %.2f\n", result);
    }
    
    return 0;
}
