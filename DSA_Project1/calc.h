#ifndef CALC_H
#define CALC_H

#define EXPR_MAX 100

typedef struct {
    double data[EXPR_MAX];
    int top;
} numstack;

typedef struct {
    char data[EXPR_MAX];
    int top;
} opstack;

typedef struct Node {
    char data[20];
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node* data[EXPR_MAX];
    int top;
} nodestack;

void pushNum(numstack *s, double val);
double popNum(numstack *s);

void pushOp(opstack *s, char op);
char popOp(opstack *s);
char peekOp(opstack *s);

void pushNode(nodestack *s, Node* node);
Node* popNode(nodestack *s);

int precedence(char op);
double applyOp(double a, double b, char op);
int isOperator(char c);

double eval(const char *expr);
double evalPostfix(const char *expr);
double evalPrefix(const char *expr);

#endif