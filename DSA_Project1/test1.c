#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAX 100

typedef struct {double data[MAX];int top;} numstack;
typedef struct {char data[MAX];int top;} opstack;

void pushNum(numstack *s, double val) {
    s->data[++(s->top)] = val;
}
double popNum(numstack *s) {
    return s->data[(s->top)--];
}
void pushOp(opstack *s, char op) {
    s->data[++(s->top)] = op;
}
char popOp(opstack *s) {
    return s->data[(s->top)--];
}
char peekOp(opstack *s) {
    return s->data[s->top];
}

int precedence(char op) {
    if (op=='+'||op=='-') return 1;
    if (op=='*'||op=='/') return 2;
    return 0;
}

double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': 
        return a+b;
        case '-': 
        return a-b;
        case '*': 
        return a*b;
        case '/': 
        return b!=0?a/b:0;
        default: 
        return 0;
    }
}

double eval(const char *expr) {
    numstack values = {.top=-1};
    opstack ops = {.top=-1};
    int i=0;
    int len=strlen(expr);

    while(i<len) {
        if(isspace(expr[i])) {
            i++;
            continue;
        }
        if(expr[i]=='-'&&(i==0||expr[i-1]=='(')) {
            i++;
            char numStr[20];
            int j=0;
            numStr[j++]='-';
            while (i<len&&(isdigit(expr[i])||expr[i]=='.')) {
                numStr[j++]=expr[i++];
            }
            numStr[j]='\0';
            pushNum(&values,atof(numStr));
            continue;
        }
        if (isdigit(expr[i])||expr[i]=='.') {
            char numStr[20];
            int j=0;
            while(i<len&&(isdigit(expr[i])||expr[i]=='.')) {
                numStr[j++]=expr[i++];
            }
            numStr[j]='\0';
            pushNum(&values,atof(numStr));
        }
        else if (expr[i]=='(') {
            pushOp(&ops, expr[i]);
            i++;
        }
        else if (expr[i]==')') {
            while (ops.top!=-1&&peekOp(&ops)!='(') {
                double b=popNum(&values);
                double a=popNum(&values);
                char op=popOp(&ops);
                pushNum(&values,applyOp(a,b,op));
            }
            popOp(&ops);
            i++;
        }
        else {
            while (ops.top!=-1&&precedence(peekOp(&ops))>=precedence(expr[i])) {
                double b=popNum(&values);
                double a=popNum(&values);
                char op=popOp(&ops);
                pushNum(&values,applyOp(a,b,op));
            }
            pushOp(&ops,expr[i]);
            i++;
        }
    }
    while(ops.top!=-1) {
        double b=popNum(&values);
        double a=popNum(&values);
        char op=popOp(&ops);
        pushNum(&values,applyOp(a,b,op));
    }

    return popNum(&values);
}
int main() {
    char expr[MAX];
    int sizeLimit;
    printf("Set expression size limit (max %d): ", MAX);
    scanf("%d",&sizeLimit);
    getchar();

    if (sizeLimit>MAX) {
        printf("Size exceeds maximum limit.\n");
        return 1;
    }
    printf("Enter expressions (or type 'file' to read from file): ");
    fgets(expr,sizeof(expr),stdin);
    expr[strcspn(expr, "\n")]='\0';

    if (strcmp(expr,"file")==0) {
        char filename[50];
        printf("Enter filename:");
        scanf("%s",filename);
        FILE *fp=fopen(filename,"r");
        if (!fp) {
            printf("Error: File not found.\n");
            return 1;
        }
        printf("\n--- Results from file ---\n");
        while (fgets(expr, sizeof(expr), fp)) {
            expr[strcspn(expr,"\n")]='\0';
            if (strlen(expr) == 0)
            continue;
            printf("%s=%.2f\n",expr,eval(expr));
        }
        fclose(fp);
    } else {
        printf("Result: %.2f\n", eval(expr));
    }

    return 0;
}
