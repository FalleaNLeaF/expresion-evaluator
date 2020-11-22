#include<stdio.h>

char expr[20];//array to store entered expression                                //почему именно 20? если правильно поняла, чтобы компиляция кода много времени не занимала?
char stack[20];//store the postfix expression
int precedence(char a, char b) {//returns true if precedence of operator a is more or equal to than that of b
    return ((a == '+') || (a == '-')) && ((b == '*') || (b == '/')) ? 0 : 1;     // что здесь значит знак вопроса перед нулем?
}

int i;
int ctr;
int topOfValueStack = -1;                                                       // почему присваивается значение -1
int topOperatorStack = -1;                                                      // почему присваивается значение -1

int applyOperator(int a, int b, char oper) {
    switch (oper) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
            break;//return result of evaluation
        case '/':
            return a / b;
        default:
            return 0;
    }
}

void postfixConvert() {
    char topsymb, operatorStack[20];
    ctr = 0;                                                                    // что значит "ctr"
    while (expr[ctr] != '\0') {
        if (expr[ctr] >= '0' && expr[ctr] <= '9') {
            int val = 0, step = 1;
            while (expr[ctr] != '\0' && isdigit(expr[ctr])) {
                val = val * step + (int) (expr[ctr] - '0');           // это действие  val=val*step+(int), что здесь значит этот (int), и за что отвечает это действие?
                step *= 10;                                           // это эквивалентно step = step * 10 ?
                ctr++;
            }
            stack[++topOfValueStack] = val + '0';                     // эти две строчки отвечают за возврат на предыдущий символ, при условии, что проверка дошла до символа окончания?
            ctr--;
        } else {                                                      // полностью, что выполняет это else, вообще не понимаю
            while (topOperatorStack >= 0 && precedence(operatorStack[topOperatorStack], expr[ctr])) {                 
                topsymb = operatorStack[topOperatorStack--];
                stack[++topOfValueStack] = topsymb;                   //зачем здесь stack
            }
            operatorStack[++topOperatorStack] = expr[ctr];            // и что выполняет вот эта строка
        }
        ctr++;
    }
    while (topOperatorStack >= 0) {
        stack[++topOfValueStack] = operatorStack[topOperatorStack--];  //зачем здесь stack
    }
}

int main() {
    printf("Enter the Expression\n");
    scanf("%s", expr);
    postfixConvert();
    int operand1, operand2, temp;
    ctr = 0;
    int result[2];                                                    // почему именно второе место присваивается?
    int rTop = -1;                                                    // почему присваивается значение -1? и что именно значит rTop?
    while (stack[ctr] != '\0') {
        temp = (int) (stack[ctr] - '0');                              // что выполняет это выражение temp = (int) (stack[ctr] - '0');
        if (temp >= 0)
            result[++rTop] = temp;                                    
        else {
            operand1 = result[rTop--];
            operand2 = result[rTop--];
            result[++rTop] = applyOperator(operand2, operand1, stack[ctr]);
        }
        ctr++;
    }
    printf("The result of the expression is: %d\n", result[0]);
    getchar();                                                         // спасибо огромное за помощь и извини за беспокойство :) Даже не знаю, как отблагодарить, если нужна будет от меня какая-то помощь, с удовольствием помогу!
} 
