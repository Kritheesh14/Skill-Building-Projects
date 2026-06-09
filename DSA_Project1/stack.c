#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

void pushOp(opstack *s, char op) {
    s->data[++(s->top)] = op;
}

char popOp(opstack *s) {
    return s->data[(s->top)--];
}

char peekOp(opstack *s) {
    return s->data[s->top];
}

void pushNode(nodestack *s, Node* node) {
    s->data[++(s->top)] = node;
}

Node* popNode(nodestack *s) {
    return s->data[(s->top)--];
}
