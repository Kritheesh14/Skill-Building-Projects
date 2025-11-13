#ifndef CALC_H
#define CALC_H

#define MAX 100

typedef struct {
    double data[MAX];
    int top;
} numstack;

typedef struct {
    char data[MAX];
    int top;
} opstack;

void pushNum(numstack *s, double val);
double popNum(numstack *s);

void pushOp(opstack *s, char op);
char popOp(opstack *s);
char peekOp(opstack *s);

int precedence(char op);
double applyOp(double a, double b, char op);

double eval(const char *expr);

#endif