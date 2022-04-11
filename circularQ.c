#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;

	do{
		printf("------------[hankyuwon]-------[2019037002]-----------");
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue() // Queue 생성 함수
{
	QueueType *cQ; 
	cQ = (QueueType *)malloc(sizeof(QueueType)); // struct QueueType 크기만큼의 메모리 생성, 이름은 cQ
	cQ->front = 0; // cQ 구조체 내의 front 값에 0 대입
	cQ->rear = 0; // cQ 구조체 내의 rear 값에 0 대입
	return cQ; // 생성한 cQ를 return
}

int freeQueue(QueueType *cQ) // cQ 메모리 해제 함수
{
    if(cQ == NULL) return 1; // cQ가 NULL을 가리키는 경우 return 1;
    free(cQ); // cQ가 가리키는 값이 있을 경우 free함수를 통해 메모리 해제
    return 1;
}

element getElement() // Insert 에서 입력값을 가져오기 위한 함수
{
	element item; // 여기서 element == char 이다.
	printf("Input element = ");
	scanf(" %c", &item);
	return item; // 입력값을 return
}

int isEmpty(QueueType *cQ) // Queue가 비어있는지 확인하는 함수
{
	if(cQ->front==cQ->rear) // cQ의 front와 rear가 같으면 비어있음. 이는 원형 Queue의 개념
	{
		printf("Circular Queue is empty!");
		return 1;
	}
    else return 0;
}

int isFull(QueueType *cQ) // Queue가 Full인 상태인지 확인하는 함수
{
	if(((cQ->rear+1)%MAX_QUEUE_SIZE)==cQ->front){ // cQ의 rear+1값을 Queue의 Size로 나눔 < (원형 Queue의 개념) 값이 front와 같으면 FULL인 상태.
		printf("Circular Queue is full!");
		return 1;
	}
   else return 0;
}


void enQueue(QueueType *cQ, element item) // Queue에 입력값을 삽입
{
	if(isFull(cQ)) return; // 먼저 isFull함수를 통해 Queue 의 상태 확인
	else{
		cQ->rear=(cQ->rear+1)%MAX_QUEUE_SIZE; // 원형 Queue에 입력값을 넣어주기 위해선 rear값을 rear+1 해준뒤 Queue Size로 나눠준 나머지로 바꿔줌
		cQ->queue[cQ->rear]=item; // 이때 증가된 rear에 입력값 넣어줌
	}
}

void deQueue(QueueType *cQ, element *item) // Queue안의 front 값을 삭제
{
	if(isEmpty(cQ)) return; // 먼저 isEmpty함수를 통해 Queue 의 상태 확인
	else{
		cQ->front=(cQ->front+1)%MAX_QUEUE_SIZE; // front 값에 (front+1)%QueueSize 값을 넣어줌
		*item=cQ->queue[cQ->front];
		return;
	}
}


void printQ(QueueType *cQ) // Queue의 상태를 print
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first; 
	while(i != last){ // first값과 last 값이 같아지면 while문 종료
		printf("%3c", cQ->queue[i]); //queue[front+1]부터 queue[rear+1]까지 출력
		i = (i+1)%MAX_QUEUE_SIZE; // front+1부터 front+2 front+3 출력하기 위해 1씩 증가시키고 Circular Queue인 이유로 Queue Size만큼 나눠줌

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) // 디버그
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) // Queue의 상태를 확인하기 위해 Queue[0], Queue[1]... Queue[MAX_SIZE] 의 값과 
	//Debug 당시의 front rear값 출력
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}


