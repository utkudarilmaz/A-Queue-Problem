/*Bir bankaya sabahleyin gelmiş olan N kişinin, geliş sıralarına göre kuyruk oluşturduklarını varsayın.
Her birinin işleminin 30 saniye ile 300 sn. arasında random bir zaman aldığını varsayın.
Her bir banka müşterisine numara vererek ve her birine random birer işlem süresi atayarak N elemanlı bir kuyruk oluşturunuz.
Her bir müşterinin işi biterek kuyruktan çıkarıldığında işlem tamamlanma süresini
(işlem süresi dâhil ne kadar süre kuyrukta kaldığını) liste halinde yazdırınız.
Ayrıca, N adet müşteri için ortalama işlem tamamlanma süresini de hesaplayıp yazdırınız.
*/

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "time.h"

/* Kuyruk yapısının düğüm yapısı */
typedef struct node{
    int no; /* Müşteri numarası */
    int processTime; /* Müşterinin işlem süresini tutan değişken */
    struct node* next; /* Kendinden sonra sıraya gelen müşteriyi gösteren pointer */
}Node;

/* Kuyruk yapısı */
typedef struct queue{
    Node* head;
    Node* last; /* Kuyruğun başını ve sonunu gösteren pointerlar */
    int processTimeSum; /* Kuyrukta müşterilerin harcadığı toplam işlem süresi */
    int no; /* Genel müşteri numarası */
}Queue;

int randProcessTime(void);
Node* newNode(void);
Queue* newQueue(void);
bool emptyQueue(Queue*);
void addNodeToQueue(Node*,Queue*);
Node* popNodeFromQueue(Queue*);
void clearQueue(Queue*);
void averageOfProcessTime(Queue*);

int main(void){
    int select;
    int n;
    Queue* newQueuex=newQueue();
    Node* newNodex;
    printf("Welcome to Bank");
    while(1){
        printf("\n\n1: Add \"n\" customer\n2: The time the customers spend on the queue\n3: Average process time\n\nPlease select your process: ");
        scanf("%d",&select);
        printf("\n\n");
        switch(select){
            case 1:
                printf("How many customer in the queue?\nChoose: ");
                scanf("%d",&n);
                while(n>0){
                    newNodex=newNode();
                    for(int i=0;i<600000000;i++); /* Bu satır randomize sayinin üretilebilmesi için zaman geçiriyor */
                    addNodeToQueue(newNodex,newQueuex);
                    n--;
                }
                break;
            case 2:
                clearQueue(newQueuex);
                break;
            case 3:
                averageOfProcessTime(newQueuex);
                break;
            default :
                printf("Wrong choose!\n");
                break;
        }
    }
    return 0;
}

/* Rastgele işlem süresini hesaplayan fonksiyon */
int randProcessTime(void){
    srand(time(NULL));
    int x=rand()%270+30;
    return x;
}

/* Dugum oluşturma fonksiyonu */
Node* newNode(void){
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->no=0;
    newNode->processTime=0;
    newNode->next=NULL;
    return newNode;
}

/* Kuyruk yapısı oluşturma fonksiyonu */
Queue* newQueue(void){
    Queue* newQueue=(Queue*)malloc(sizeof(Queue));
    newQueue->head=NULL;
    newQueue->last=NULL;
    newQueue->no=0;
    newQueue->processTimeSum=0;
    return newQueue;
}

/* Kuyruğun boş olup olmadığını kontrol eden fonksiyon */
bool emptyQueue(Queue* queue){
    if(queue->head==NULL)
        return true;
    else
        return false;
}

/* Kuyruk yapısına yeni bir düğüm ekleme fonksiyonu */
void addNodeToQueue(Node* newNode,Queue* queue){
    queue->no+=1; /* Genel müşteri numarasının bir artttırılması */
    if(emptyQueue(queue)){
        queue->head=newNode; /* Eğer kuyruk boş ise kuyruğun başına yeni elemanın adresinin atanması */
    }
    else{
        queue->last->next=newNode; /* Kuyruğun son müşterisinden sonra gelecek müşterinin adresinin atanması */
    }
    queue->last=newNode; /* Kuyruğun sonuna son gelen müşteri atanması */
    newNode->no=queue->no; /* Müşteri numarasının atanması */
    newNode->processTime=randProcessTime(); /* Müşterinin işlem süresi hesaplanması */
    if(queue->no==1){
        queue->processTimeSum+=newNode->processTime;
        return;
    }
    queue->processTimeSum+=newNode->processTime; /* Toplam kuyrukta geçirilen vaktin hesaplanması */
    newNode->processTime=queue->processTimeSum; /* Yeni müşterinin işlem süresi dahil kuyrukta geçirdiği sürenin hesaplanması */
}

/* Kuyruktan eleman çıkarma ve çıkarılan elemanı döndüren fonksiyon */
Node* popNodeFromQueue(Queue* queue){
    Node* returnNode;
    if(emptyQueue(queue)){ /* Eğer kuyruk boşsa işlem yapılmadan null döner */
        printf("Queue is empty!\n");
        return NULL;
    }
    returnNode=queue->head;
    queue->head=queue->head->next; /* Listenin başına kuyrukta işi biten müşterinden sonra gelen müşterinin atanması */
    return returnNode;
}

/* Kuyruğu boşaltan ve her bir müşterinin kuyrukta harcadıkları süreyi gösteren fonksiyon */
void clearQueue(Queue* queue){
    if(emptyQueue(queue)){
        printf("Queue is empty already!\n\n");
        return;
    }
    Node* temp;
    while(!emptyQueue(queue)){
        temp=popNodeFromQueue(queue);
        printf("The time the %d. customer spent in the queue: %d second.\n",temp->no,temp->processTime);
    }
}

/* Kuyrukta geçirilen ortalama işlem süresini gösteren fonskiyon */
void averageOfProcessTime(Queue* queue){
    if(emptyQueue(queue)){
        printf("Queue is empty!\n\n");
        return;
    }
    int average=queue->processTimeSum/queue->no;
    printf("Avarege process time in the queue: %d second.\n",average);
}
