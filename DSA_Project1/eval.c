#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calc.h"

Node* createNode(const char *data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data, data);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

double evaluateTree(Node *root) {
    if (root == NULL) return 0;
    
    // operand is leaf node
    if (root->left == NULL && root->right == NULL) {
        return atof(root->data);
    }
    
    // recursive evaluation
    double leftVal = evaluateTree(root->left);
    double rightVal = evaluateTree(root->right);
    
    return applyOp(leftVal, rightVal, root->data[0]);
}

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

void infixToPostfix(const char *infix, char *postfix) {
    opstack ops = {.top = -1};
    int i = 0, k = 0, len = strlen(infix);

    while (i < len) {
        if (isspace(infix[i])) {
            i++;
            continue;
        }

        if (infix[i] == '-' && (i == 0 || infix[i - 1] == '(')) {// unary minus
            postfix[k++] = '-';
            i++;

            while (i < len && (isdigit(infix[i]) || infix[i] == '.'))
                postfix[k++] = infix[i++];

            postfix[k++] = ' ';
            continue;
        }

        if (isdigit(infix[i]) || infix[i] == '.') {
            while (i < len && (isdigit(infix[i]) || infix[i] == '.'))
                postfix[k++] = infix[i++];

            postfix[k++] = ' ';
        }
        else if (infix[i] == '(') {
            pushOp(&ops, infix[i]);
            i++;
        }
        else if (infix[i] == ')') {
            while (ops.top != -1 && peekOp(&ops) != '(') {
                postfix[k++] = popOp(&ops);
                postfix[k++] = ' ';
            }
            popOp(&ops);
            i++;
        }
        else if (isOperator(infix[i])) {
            while (ops.top != -1 && peekOp(&ops) != '(' && precedence(peekOp(&ops)) >= precedence(infix[i])) {
                postfix[k++] = popOp(&ops);
                postfix[k++] = ' ';
            }
            pushOp(&ops, infix[i]);
            i++;
        }
        else {
            i++;
        }
    }

    while (ops.top != -1) {
        postfix[k++] = popOp(&ops);
        postfix[k++] = ' ';
    }

    postfix[k] = '\0';
}

double eval_Infix(const char *expr) {
    char postfix[EXPR_MAX * 2];
    infixToPostfix(expr, postfix);
    Node *tree = buildTreeFromPostfix(postfix);
    double result = evaluateTree(tree);
    freeTree(tree);
    return result;
}

Node* buildTreeFromPostfix(const char *expr) {
    nodestack nodes = {.top = -1};
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
            pushNode(&nodes, createNode(numStr));
        }
        else if (isOperator(expr[i])) {
            Node *right = popNode(&nodes);
            Node *left = popNode(&nodes);
            
            char opStr[2] = {expr[i], '\0'};
            Node *opNode = createNode(opStr);
            opNode->left = left;
            opNode->right = right;
            pushNode(&nodes, opNode);
            i++;
        }
        else {
            i++;
        }
    }

    return popNode(&nodes);
}

double evalPostfix(const char *expr) {
    Node *tree = buildTreeFromPostfix(expr);
    double result = evaluateTree(tree);
    freeTree(tree);
    return result;
}

Node* buildTreeFromPrefix(const char *expr) {
    nodestack nodes = {.top = -1};
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
            pushNode(&nodes, createNode(numStr));
        }
        else if (isOperator(expr[i])) {
            Node *left = popNode(&nodes);
            Node *right = popNode(&nodes);
            
            char opStr[2] = {expr[i], '\0'};
            Node *opNode = createNode(opStr);
            opNode->left = left;
            opNode->right = right;
            pushNode(&nodes, opNode);
            i--;
        }
        else {
            i--;
        }
    }

    return popNode(&nodes);
}

double evalPrefix(const char *expr) {
    Node *tree = buildTreeFromPrefix(expr);
    double result = evaluateTree(tree);
    freeTree(tree);
    return result;
}
