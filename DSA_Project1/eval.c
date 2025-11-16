#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calc.h"

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : 0;
    }
    return 0;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

double eval(const char *expr) {
    numstack values = {.top = -1};
    opstack ops = {.top = -1};
    int i = 0, len = strlen(expr);

    while (i < len) {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        if (expr[i] == '-' && (i == 0 || expr[i - 1] == '(')) {// expr[i] == '-' for case of unary minus
            char numStr[20];
            int j = 0;
            numStr[j++] = '-';
            i++;

            while (i < len && (isdigit(expr[i]) || expr[i] == '.'))
                numStr[j++] = expr[i++];

            numStr[j] = '\0';
            pushNum(&values, atof(numStr));
            continue;
        }

        if (isdigit(expr[i]) || expr[i] == '.') {
            char numStr[20];
            int j = 0;

            while (i < len && (isdigit(expr[i]) || expr[i] == '.'))
                numStr[j++] = expr[i++];

            numStr[j] = '\0';
            pushNum(&values, atof(numStr));
        }
        else if (expr[i] == '(') {
            pushOp(&ops, expr[i]);
            i++;
        }
        else if (expr[i] == ')') {
            while (ops.top != -1 && peekOp(&ops) != '(') {
                double b = popNum(&values);
                double a = popNum(&values);
                char op = popOp(&ops);
                pushNum(&values, applyOp(a, b, op));
            }
            popOp(&ops);
            i++;
        }
        else {
            while (ops.top != -1 && precedence(peekOp(&ops)) >= precedence(expr[i])) {
                double b = popNum(&values);
                double a = popNum(&values);
                char op = popOp(&ops);
                pushNum(&values, applyOp(a, b, op));
            }
            pushOp(&ops, expr[i]);
            i++;
        }
    }

    while (ops.top != -1) {
        double b = popNum(&values);
        double a = popNum(&values);
        char op = popOp(&ops);
        pushNum(&values, applyOp(a, b, op));
    }

    return popNum(&values);
}

double evalPostfix(const char *expr) {
    numstack values = {.top = -1};
    int i = 0, len = strlen(expr);

    while (i < len) {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        if (isdigit(expr[i]) || (expr[i] == '-' && i + 1 < len && isdigit(expr[i + 1]))) {
            char numStr[20];
            int j = 0;

            if (expr[i] == '-') {
                numStr[j++] = expr[i++];
            }

            while (i < len && (isdigit(expr[i]) || expr[i] == '.'))
                numStr[j++] = expr[i++];

            numStr[j] = '\0';
            pushNum(&values, atof(numStr));
        }
        else if (isOperator(expr[i])) {
            double b = popNum(&values);
            double a = popNum(&values);
            pushNum(&values, applyOp(a, b, expr[i]));
            i++;
        }
        else {
            i++;
        }
    }

    return popNum(&values);
}

double evalPrefix(const char *expr) {
    numstack values = {.top = -1};
    int len = strlen(expr);
    int i = len - 1;

    while (i >= 0) {
        if (isspace(expr[i])) {
            i--;
            continue;
        }

        if (isdigit(expr[i]) || (expr[i] == '.' && i > 0 && isdigit(expr[i - 1]))) {
            char numStr[20];
            int j = 0;
            int end = i;

            while (i >= 0 && (isdigit(expr[i]) || expr[i] == '.')) {
                i--;
            }

            if (i >= 0 && expr[i] == '-') {
                i--;
                for (int k = i + 1; k <= end; k++) {
                    numStr[j++] = expr[k];
                }
            } else {
                for (int k = i + 1; k <= end; k++) {
                    numStr[j++] = expr[k];
                }
            }

            numStr[j] = '\0';
            pushNum(&values, atof(numStr));
        }
        else if (isOperator(expr[i])) {
            double a = popNum(&values);
            double b = popNum(&values);
            pushNum(&values, applyOp(a, b, expr[i]));
            i--;
        }
        else {
            i--;
        }
    }

    return popNum(&values);
}
