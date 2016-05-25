#include <stdio.h>

#define MAX 10

struct cyc_que {
	int data[MAX];
	int front;
	int rear;
} cq;

int in_cycque(struct cyc_que *cq, int data)
{
	if ((cq->rear + 1) % MAX == cq->front) {
		return 0;
	} else {
		cq->rear = (cq->rear + 1) % MAX;
		cq->data[cq->rear] = data;
		return 1;
	}
}

int out_cycque(struct cyc_que *cq)
{
	if (cq->front == cq->rear) {
		return 0;
	} else {
		cq->front = (cq->front + 1) % MAX;
		return cq->data[cq->front];
	}
}

int size_cycque(struct cyc_que *cq)
{
	return cq->rear >= cq->front ?
		cq->rear - cq->front :
		cq->rear + MAX - cq->front;
}

int main()
{
	int select, c, d;

	printf("1.insert 2.delete 3.size\n");
	while (1) {
		printf("Please select: ");
		if ((select = getchar()) < '1' || select > '3')
			break;
		switch (select) {
			case '1':
				printf("Input data: ");
				scanf("%d", &d);
				if (in_cycque(&cq, d) == 0)
					printf("Error: Queue is full!\n");
				else
					printf("Insert %d OK!\n", d);
				break;
			case '2':
				if ((d = out_cycque(&cq)) == 0)
					printf("Error: Queue is empty!\n");
				else
					printf("Delete data: %d\n", d);
				break;
			case '3':
				printf("Size of queue is: %d\n", size_cycque(&cq));
				break;
			default:
				;
		}
		while ((c = getchar()) != '\n')
			;
	}
}
