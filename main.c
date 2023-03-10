#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5
#define PRIORITY 60

typedef struct Queue { //Estrutura da Fila
  int init;
  int end;
  int *object;
} Queue;

void createEmptyQueue(Queue *p);
int isEmpty(Queue p);
int isFull(Queue p);
void push(Queue *queue, int elem);
void printQueue(Queue queue);
int peek(Queue queue);
int pop(Queue *queue);
unsigned int chooseOption(void);

int main(void) {

  Queue queue;
  createEmptyQueue(&queue);

  unsigned int option;  
  int popped;
  while ((option = chooseOption()) != 0) { // APENAS USADO PARA TESTE DO CÓDIGO....
    switch (option) {
    case 1:
      puts("\nDigite uma idade:");
      int age;
      scanf("%d", &age);
      push(&queue, age);
      puts("\nInserido na fila com sucesso!!");
      break;
    case 2:
      printQueue(queue);
      break;
    case 3:
      printf("\nO próximo da fila é o número: %d", peek(queue)); 
      break;
    case 4:
      popped = pop(&queue);
      puts("\nElemento retirado com sucesso!!");
      break;
    }
  }

  return 0;
}

unsigned int chooseOption(void){
  unsigned int option;
  puts("\n&*&*&*&*&**MENU**&*&*&*&*&");
  puts("&* 1 - Incluir na Fila  *&");
  puts("&* 2 - Listar Fila      *&");
  puts("&* 3 - Próximo na Fila  *&");
  puts("&* 4 - Remover da Fila  *&");
  puts("&* 0 - Sair             *&");
  puts("&*&*&*&*&*&*&*&*&*&*&*&*&*");
  puts("\nDigite a opção: ");
  scanf("%u", &option);
  return option;
}

void createEmptyQueue(Queue *p) { //Função de iniciliazação da Fila
  p->init = 0;
  p->end = 0;
  p->object = (int *)malloc(MAX_SIZE * sizeof(int));
}

int isEmpty(Queue p) { //Verificação se a fila esta vazia ou não
  return (p.init == p.end); 
  }

int isFull(Queue p) { //Verificação se a fila esta cheia ou não
  return (((p.end + 1) % MAX_SIZE) == p.init); 
}

void push(Queue *queue, int elem) { //Função responsável por colocar elemento na fila de acordo com prioridade ou não
  if(!isFull(*queue)){
    int nextPos = (queue->end + 1) % MAX_SIZE;
    int aux = 0;
    if((elem >= PRIORITY) && (!isEmpty(*queue))){
      for(int i = MAX_SIZE - 1;i >= 0;i--){
        if (queue->object[i] < PRIORITY) {
          aux = queue->object[i];
          queue->object[(i + 1)] = aux;
          queue->object[i] = elem;
          queue->end = nextPos;
        }
      }
    } else {
      queue->object[queue->end] = elem;
      queue->end = nextPos;
    }

    
  } else {
    puts("\nERROR: Queue Overflow");
    exit(1);
  }
}

int pop(Queue *queue){ //Função responsável por eliminar elemento da fila
  int poped = 0;
  if(!isEmpty(*queue)){
    int poped = queue->object[queue->init];
    queue->init = (queue->init + 1) % MAX_SIZE;
  } else {
    puts("\nERROR: Queue Underflow");
    exit(1);
  }
  return poped;
}

void printQueue(Queue queue) { //Imprimir toda a fila completa, considerando impressão circular
  if (!isEmpty(queue)) {
    int ini = queue.init;
    int end = queue.end;
    int i = ini;
    while(i != end){
      printf("\n%d", queue.object[i]);
      int nextPos = (i + 1) % MAX_SIZE;
      i = nextPos;
    }
    puts("");
      
  } else {
    puts("\nERROR: Queue Underflow");
    exit(1);
  }
}

int peek(Queue queue){ //Esta Função mostra quem é o próximo da fila
  if(!isEmpty(queue)){
    return queue.object[queue.init];
  } else {
    puts("\nERROR: Queue Underflow");
    exit(1);
  }
}

