#ifndef CALC_H
#define CALC_H

#define EXPR_MAX 100

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

void pushOp(opstack *s, char op);
char popOp(opstack *s);
char peekOp(opstack *s);

void pushNode(nodestack *s, Node* node);
Node* popNode(nodestack *s);

int precedence(char op);
double applyOp(double a, double b, char op);
int isOperator(char c);

Node* createNode(const char *data);
void infixToPostfix(const char *infix, char *postfix);
Node* buildTreeFromPostfix(const char *expr);
Node* buildTreeFromPrefix(const char *expr);
double evaluateTree(Node *root);
void freeTree(Node *root);

double eval_Infix(const char *expr);
double evalPostfix(const char *expr);
double evalPrefix(const char *expr);

#endif