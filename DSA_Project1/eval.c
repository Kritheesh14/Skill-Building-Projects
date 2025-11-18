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

Node* buildTreeFromInfix(const char *expr) {
    nodestack nodes = {.top = -1};
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
            pushNode(&nodes, createNode(numStr));
            continue;
        }

        if (isdigit(expr[i]) || expr[i] == '.') {
            char numStr[20];
            int j = 0;

            while (i < len && (isdigit(expr[i]) || expr[i] == '.'))
                numStr[j++] = expr[i++];

            numStr[j] = '\0';
            pushNode(&nodes, createNode(numStr));
        }
        else if (expr[i] == '(') {
            pushOp(&ops, expr[i]);
            i++;
        }
        else if (expr[i] == ')') {
            while (ops.top != -1 && peekOp(&ops) != '(') {
                Node *right = popNode(&nodes);
                Node *left = popNode(&nodes);
                char op = popOp(&ops);
                
                char opStr[2] = {op, '\0'};
                Node *opNode = createNode(opStr);
                opNode->left = left;
                opNode->right = right;
                pushNode(&nodes, opNode);
            }
            popOp(&ops);
            i++;
        }
        else {
            while (ops.top != -1 && peekOp(&ops) != '(' && precedence(peekOp(&ops)) >= precedence(expr[i])) {
                Node *right = popNode(&nodes);
                Node *left = popNode(&nodes);
                char op = popOp(&ops);
                
                char opStr[2] = {op, '\0'};
                Node *opNode = createNode(opStr);
                opNode->left = left;
                opNode->right = right;
                pushNode(&nodes, opNode);
            }
            pushOp(&ops, expr[i]);
            i++;
        }
    }

    while (ops.top != -1) {
        Node *right = popNode(&nodes);
        Node *left = popNode(&nodes);
        char op = popOp(&ops);
        
        char opStr[2] = {op, '\0'};
        Node *opNode = createNode(opStr);
        opNode->left = left;
        opNode->right = right;
        pushNode(&nodes, opNode);
    }

    return popNode(&nodes);
}

double eval(const char *expr) {
    Node *tree = buildTreeFromInfix(expr);
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
