/*
Bir bankaya sabahleyin gelmiş olan N kişinin, geliş sıralarına göre kuyruk oluşturduklarını varsayın.
Her birinin işleminin 30 saniye ile 300 sn. arasında random bir zaman aldığını varsayın.
Her bir banka müşterisine numara vererek ve her birine random birer işlem süresi atayarak N elemanlı bir kuyruk oluşturunuz.
Her bir müşterinin işi biterek kuyruktan çıkarıldığında işlem tamamlanma süresini
(işlem süresi dâhil ne kadar süre kuyrukta kaldığını) liste halinde yazdırınız.
Ayrıca, N adet müşteri için ortalama işlem tamamlanma süresini de hesaplayıp yazdırınız.
*/

/*
Her bir dizi elemanı kendi işlem sürelerini tutmaktadır.
Kuyrukta tanımlanan no değişkeni dizinin indexlerine ulaşmakta kullanılmaktadır.
clearQueue() fonksiyonundan sonra dizi varsayılan değerlerine döndürülmüş ve tekrar kullanıma hazır hale gelmiştir.
MAX sabiti dizinin boyutunu belirlemekle beraber arzulara bağlı daha uzun veya daha kısa kuyruklar oluşturulabilinir.
*/

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "time.h"

#define MAX 5

/* Kuyruk yapısının düğüm yapısı */
typedef struct node{
    int array[MAX];
}Node;

/* Kuyruk yapısı */
typedef struct queue{
    int head; /* Kuyruğun ilk elemanının numarasını tutan değişken */
    int last;
    int processTimeSum; /* Kuyrukta geçirilen toplam işlem süresi */
    int no; /* Kuyruk üzerinde dolaşmamızı sağlayan değişken */
}Queue;

int randProcessTime(void);
Node* newNode(void);
Queue* newQueue(void);
bool emptyQueue(Queue*);
void addNodeToQueue(Queue* queue,Node* node);
int popNodeFromQueue(Queue* queue,Node* node);
void clearQueue(Queue* queue,Node* node);
void averageOfProcessTime(Queue* queue);

int main(void){
    int select;
    int n;
    Queue* newQueuex=newQueue();
    Node* newNodex=newNode();
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
                    for(int i=0;i<600000000;i++); /* Bu satır randomize sayinin üretilebilmesi için zaman geçiriyor */
                    addNodeToQueue(newQueuex,newNodex);
                    n--;
                }
                break;
            case 2:
                clearQueue(newQueuex,newNodex);
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
    int n=0;
    while(n<MAX){ /* Dizideki elemanlara varsayılan 0 değeri atandı */
        newNode->array[n]=0;
        n++;
    }
    return newNode;
}

/* Kuyruk yapısı oluşturma fonksiyonu */
Queue* newQueue(void){
    Queue* newQueue=(Queue*)malloc(sizeof(Queue));
    newQueue->head=-1;
    newQueue->last=-1;
    newQueue->processTimeSum=0;
    newQueue->no=-1;
    return newQueue;
}

/* Kuyruğun boş olup olmadığını kontrol eden fonksiyon */
bool emptyQueue(Queue* queue){
    if(!(queue->head>=-1 && queue->head<5))
    return true;
    else
    return false;
}

/* Kuyruk yapısına yeni bir düğüm ekleme fonksiyonu */
void addNodeToQueue(Queue* queue,Node* node){
    queue->no++;
    if(queue->no==MAX){ /* Kuyruğun full olma durumu */
        printf("Queue is full, the transaction has not been approved!\n");
        queue->no--;
        return;
    }
    if(queue->no==0){
        queue->head=queue->no;
    }
    queue->last=queue->no;
    node->array[queue->no]=randProcessTime();
    if(queue->no==0){ /* Kuyruğa eklenen ilk elemana özel süreç */
        queue->processTimeSum+=node->array[queue->no];
        return;
    }
    queue->processTimeSum+=node->array[queue->no];
    node->array[queue->no]=queue->processTimeSum;
}

/* Kuyruktan eleman çıkarma ve çıkarılan elemanın işlem süresini döndüren fonksiyon */
int popNodeFromQueue(Queue* queue,Node* node){
    if(emptyQueue(queue)){ /* Eğer kuyruk boşsa işlem yapılmadan -1 döner */
        printf("Queue is empty!\n");
        return -1;
    }
    int data=node->array[queue->head];
    queue->head++;
    return data;
}

/* Kuyruğu boşaltan ve her bir müşterinin kuyrukta harcadıkları süreyi gösteren fonksiyon */
void clearQueue(Queue* queue,Node* node){
    int temp;
    while(!(queue->head==MAX+1)){
        temp=popNodeFromQueue(queue,node);
        if(temp==-1){ /* Dönen değer -1 ise kuyruk boşaltılmıştır fonksiyondan çıkılacaktır */
            queue->head=-1;
            queue->last=-1;
            queue->no=-1;
            queue->processTimeSum=0;
            return;
        }
        printf("The time the %d. customer spent in the queue: %d second.\n",queue->head,temp);
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
