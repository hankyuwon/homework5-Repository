#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

typedef enum
{
    lparen = 0,
    rparen = 9,
    times = 7,
    divide = 6,
    plus = 5,
    minus = 4,
    operand = 1
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];
char postfixEXP[MAX_EXPRESSION_SIZE];
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];

int postfixStackTop = -1; // postfix 를 stack 을 이용하여 계산하기 위해 Top 설정
int evalStackTop = -1;    // evaluation도 동일

int evalResult = 0;

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char *c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
    char command;

    do
    {
        printf("---------------[hankyuwon]------------[2019037002]--------------\n");
        printf("----------------------------------------------------------------\n");
        printf("               Infix to Postfix, then Evaluation               \n");
        printf("----------------------------------------------------------------\n");
        printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'i':
        case 'I':
            getInfix();
            break;
        case 'p':
        case 'P':
            toPostfix();
            break;
        case 'e':
        case 'E':
            evaluation();
            break;
        case 'd':
        case 'D':
            debug();
            break;
        case 'r':
        case 'R':
            reset();
            break;
        case 'q':
        case 'Q':
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }
    } while (command != 'q' && command != 'Q');

    return 1;
}

void postfixPush(char x) // postfixStack push함수
{
    postfixStack[++postfixStackTop] = x; // 입력값 스택에 Top 1만큼 증가시키고 저장
}

char postfixPop() // postfix pop함수
{
    char x;
    if (postfixStackTop == -1) // postfixstack의 top이 -1이면 비어있는 상태
        return '\0';
    else
    {
        x = postfixStack[postfixStackTop--]; // 비어있지 않다면 x값을 빼주고 Top--
    }
    return x;
}

void evalPush(int x) // evalStack 에서의 push 함수
{
    evalStack[++evalStackTop] = x;
}

int evalPop() // evalStack 에서의 pop 함수
{
    if (evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s", infixExp); // 입력값을 infixExp에 저장
}

precedence getToken(char symbol) // ()+-/* 수식을 숫자로 저장하는 함수
{
    switch (symbol) // 각각의 수식을 저장
    {
    case '(':
        return lparen;
    case ')':
        return rparen;
    case '+':
        return plus;
    case '-':
        return minus;
    case '/':
        return divide;
    case '*':
        return times;
    default:
        return operand;
    }
}

precedence getPriority(char x) // 연산자 우선순위를 비교하기위해 toPostfix함수에서 사용할 함수
{
    return getToken(x);
}

void charCat(char *c) // 문자열을 이어붙이는 함수
{
    if (postfixEXP == '\0')        // postfixEXP가 가리키는 값이 없을때
        strncpy(postfixEXP, c, 1); // postfixEXP에 c를 이어붙힌다.
    else
        strncat(postfixEXP, c, 1); // postfixEXP에 c를 이어붙힌다.
}

void toPostfix() // Postfix로 바꾸는 함수
{
    char *exp = infixExp;
    char x;

    while (*exp != '\0') // exp가 NULL을 가리키면 종료
    {

        if (getPriority(*exp) == operand) // exp의 값이 수식이 아닌경우
        {
            x = *exp;
            charCat(&x); // postfixEXP에 붙힌다.
        }
        else if (getPriority(*exp) == lparen) // '(' 인 경우
        {
            postfixPush(*exp);
        }
        else if (getPriority(*exp) == rparen) // ')' 인 경우
        {
            while ((x = postfixPop()) != '(')
            { // '(' 이 나올때까지
                charCat(&x);
            }
        }
        else
        {
            while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) // stack에 저장된 연산자가 postfixstack의 연산자의 우선순위보다 
            //클 동안 반복
            {
                x = postfixPop(); // postfix에서 x를 빼주고 top--
                charCat(&x); // 빼온 x값을 postfixEXP에 이어붙힌다.
            }
            postfixPush(*exp); // postfix에 저장
        }
        exp++; // exp++로 다음 으로 넘어감(NULL이 나올때 까지)
    }

    while (postfixStackTop != -1) // postfixStackTop이 -1일때까지 반복
    {
        x = postfixPop(); // postfixpop으로 x 빼주고
        charCat(&x); // x값 이어붙힘
    }
}

void debug() // 상태 점검 (infixExp, postfixExp, evalResult, postfixStack값을 모두 출력해줌)
{
    printf("\n---DEBUG\n");
    printf("infixExp = %s\n", infixExp);
    printf("postExp = %s\n", postfixEXP);
    printf("eval result = %d\n", evalResult);

    printf("postfixStack : ");
    for (int i = 0; i < MAX_STACK_SIZE; i++)
    {
        printf("%c ", postfixStack[i]);
    }
    printf("\n");
}

void reset() // infix와 postfix postfixStack을 초기 상태로 되돌림
{
    infixExp[0] = '\0';
    postfixEXP[0] = '\0';

    for (int i = 0; i < MAX_STACK_SIZE; i++)
        postfixStack[i] = '\0';

    postfixStackTop = -1;
    evalStackTop = -1;
    evalResult = 0;
}

void evaluation() // 계산
{
    int opr1, opr2, i;

    int length = strlen(postfixEXP); // postfixEXP 길이 저장
    char symbol;
    evalStackTop = -1;

    for (i = 0; i < length; i++)
    {
        symbol = postfixEXP[i];
        if (getToken(symbol) == operand) // 숫자일때
        {
            evalPush(symbol - '0'); // symbol - '0' 은 문자로 된 숫자를 정수형으로 반환
        }
        else
        {
            opr2 = evalPop(); // evalStack에서 pop한 값을 opr2에 대입
            opr1 = evalPop(); // evalStack에서 pop한 값을 opr1에 대입
            switch (getToken(symbol))
            {
            case plus: // + 인경우 Plus로 저장되어있고, 다시 이를 opr1+opr2 한 후 evalstack에 저장
                evalPush(opr1 + opr2);
                break;
            case minus: // 이하 동문
                evalPush(opr1 - opr2);
                break;
            case times:
                evalPush(opr1 * opr2);
                break;
            case divide:
                evalPush(opr1 / opr2);
                break;
            default:
                break;
            }
        }
    }
    evalResult = evalPop(); // 결과 evalResult에 저장
}