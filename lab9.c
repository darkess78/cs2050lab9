#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int width;
    int height;
}Rect;

typedef struct node {
    Rect* r;
    struct node* next;
}Node;

typedef struct {
    Node* head;
    Node* tail;
}Queue;

Queue* createQueue(void);
int enQueue(Queue*);
void* deQueue(Queue*);
int deQueueAll(Queue*);
void printQueue(Queue*);
void freeQueue(Queue*);

int main(void){

    srand(time(NULL));

    Queue* queue = createQueue();
    if (queue == NULL){
        return -1;
    }
    int check = 1;;

    for (int i = 0; i < 10; i++){
        check = enQueue(queue);
        if (check == -1){
            return -1;
        }
    }
    printf("(printQueue)");
    printQueue(queue);

    Rect *r = NULL;
    for (int i = 0; i < 2; i++){
        r = (Rect*)deQueue(queue);
        if (r != NULL){
            printf("(deQueue)");
            printf("Rectangle with area %d has been dequeued\n",r->height*r->width);
        }
    }
    printf("(printQueue)");
    printQueue(queue);

    printf("(deQueueAll)");
    check = deQueueAll(queue);
    printf("(printQueue)");
    printQueue(queue);

    // final test for deQueue
    printf("(deQueue)");
    r = deQueue(queue);

    printf("(freeQueue)\n");
    freeQueue(queue);
    queue = NULL;

    return 0;
}

Queue* createQueue(void){
    Queue *queue = malloc(sizeof(Queue));
    
    Node* node = malloc(sizeof(Node));
    
    //create an empty queue and make it circular linked list
    queue->head=node;
    queue->tail=node;
    queue->head->next = queue->tail;
    queue->tail->next = queue->head;
    
    return queue;
}

int enQueue(Queue* queue){
    if(queue==NULL){
        printf("could not find queue for enqueue");
        return -1;
    }
    Node *newNode = malloc(sizeof(Node));
    if(newNode==NULL){
        printf("could not malloc newNode for enqueue");
        return -1;
    }
    Node *current =queue->head;
    Rect *r = malloc(sizeof(Rect));
    if(r==NULL){
        printf("could not malloc rectangle r for enqueue");
        return -1;
    }
    
    //random values for height and width into r
    r->height = rand()%10+1;
    r->width = rand()%10+1;
    
    newNode->r=r;
    
    
    if(queue->head->next == queue->tail){
        //if head and tail are the only things in queue then put newNode after head and before tail
        newNode->next = queue->tail;
        queue->head->next=newNode;
        return 1;
    }else{
        //if there are more nodes than head and tail go to the last spot before the tail
        while(current->next != queue->tail){
            current=current->next;
        }
        //set the newNode to the spot before tail and set its next value to tail
        newNode->next = queue->tail;
        current->next = newNode;
        current=newNode;
        return 1;
    }
    return -1;
    
}

void* deQueue(Queue* queue){
    //grab the deQueued node and store it in deleted
    Node *deleted = queue->head->next;
    
    //check that there is something to delete
    if(queue->head == NULL){
        return NULL;
    }else{
        //remove the value after the head dummy node and set head->next to the new node
        queue->head->next=queue->head->next->next;    
        return deleted->r;
    }
}

int deQueueAll(Queue* queue){
    Node* current = queue->head;//setting current the empty head node
    
    //as long as current->next isnt the tail go through the queue
    while(current->next != queue->tail){
        
        //remove the value after the dummy head and set it to the next node
        current->next=current->next->next;
    }
    //if everything but the dummy nodes were deleted then return 
    if(current->next == queue->tail){
        return 1;
    }else{
        return -1;
    }
}

void printQueue(Queue* queue){
    //set current to the head node
    Node *current = queue->head;
    
    //as long as current->next isnt the tail print the area of the current node and go to the next node
    while(current->next != queue->tail){
        current=current->next;
        printf("Rectangle with area %d\n",current->r->height*current->r->width);
    }
}

void freeQueue(Queue* queue){
    //make sure the queue isnt already empty
    if(queue==NULL){
        return;
    }else{
        Node *current = queue->head;
        Node *p=queue->head;
        
        //while current->next isnt tail go through the queue and free what the current node is
        for(current=current->next; current->next != queue->tail; current = current->next){
            free(p);
            p=current;
        }
        //if there is only the dummy nodes left free them
        if(queue->head->next==queue->tail ){
            free(queue->tail);//queue->head gets freed in main otherwise double free error
        }
    }
}
