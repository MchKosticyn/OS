#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

int i[3]={0,0,0};
typedef int (*fPtr)();


typedef struct {
    int key;
    fPtr pr;
} tkey;

typedef struct {
    tkey prog[20000];
    int heap_size;
} tHeap;

int Heap_Increase_Key(tHeap* A, int i,tkey key) {
    A->prog[i] = key;
    while ((i>0)&&(A->prog[i/2].key<A->prog[i].key)){
        tkey c;
        c = A->prog[i];
        A->prog[i] = A->prog[i/2];
        A->prog[i/2] = c;
    }
    return 0;
}

int Heap_insert(tHeap* A, tkey key) {
    A->prog[A->heap_size].key = -10000;
    Heap_Increase_Key(A, A->heap_size,key);
    (A->heap_size)++;
    return 0;
}
tkey Heap_Extract(tHeap* A) {
    if (A->heap_size < 0)
        printf("GRUST");
    else {
    tkey max = A->prog[0];
    A->heap_size--;
    A->prog[0] = A->prog[A->heap_size];
    heapsort(A,A->heap_size);
    swap(A);
    return max;
    }
}

int max (tHeap a, int n, int i, int j, int k) {
    int m = i;
    if (j < n && a.prog[j].key > a.prog[m].key) {
        m = j;
    }
    if (k < n && a.prog[k].key > a.prog[m].key) {
        m = k;
    }
    return m;
}

void downheap (tHeap* a, int n, int i) {
    while (1) {
        int j = max( (*a), n, i, 2 * i + 1, 2 * i + 2);
        if (j == i) {
            break;
        }
        tkey t = a->prog[i];
        a->prog[i] = a->prog[j];
        a->prog[j] = t;
        i = j;
    }
}
void swap(tHeap* A) {
    int i;
    for (i=0;i<A->heap_size/2;i++) {
        tkey c=A->prog[i];
        A->prog[i]=A->prog[A->heap_size-i-1];
        A->prog[A->heap_size-i-1]=c;
    }
}

void heapsort (tHeap* a, int n) {
    int i;
    for (i = (n - 2) / 2; i >= 0; i--) {
        downheap(a, n, i);
    }
    for (i = 0; i < n; i++) {
        tkey t = a->prog[n - i - 1];
        a->prog[n - i - 1] = a->prog[0];
        a->prog[0] = t;
        downheap(a, n - i - 1, 0);
    }
}



int prog1()
{
    char* s="hello";
    int length=strlen(s);
    i[1]++;
    printf("Program 1 {%d %s} - %c\n",i[1]*100/length,"%",s[i[1]-1]);
    if (i[1]>=length) printf("Program 1 - DONE\n");
    return i[1]>=length;
}

int prog2()
{
    char* s="hello, world!";
    int length=strlen(s);
    i[2]++;
    printf("Program 2 {%d %s} - %c\n",i[2]*100/length,"%",s[i[2]-1]);
    if (i[2]>=length) printf("Program 2 - DONE\n");
    return i[2]>=length;
}

int prog3()
{
    char* s="hello, John...";
    int length=strlen(s);
    i[3]++;
    printf("Program 3 {%d %s} - %c\n",i[3]*100/length,"%",s[i[3]-1]);
    if (i[3]>=length) printf("Program 3 - DONE\n");
    return i[3]>=length;
}

typedef int (*tProgs)();
tProgs progs[3] = {prog1, prog2, prog3};



int main()
{

    printf("0: First task in => first task out\n");
    printf("1: More tasks are done => better\n");
    printf("2: User must be able to choose his program priority\n");
    printf("3: All tasks have equal time to evaluate\n");
    int b;
    scanf("%d",&b);

    switch (b)
    {
        case 0: {
            TAILQ_HEAD(tailhead, entry) head;
            struct entry {
                int (*fPt)();
                TAILQ_ENTRY(entry) entries;
            } *n1,*n2;

            TAILQ_INIT(&head);
            n1 = malloc(sizeof(struct entry));
            n1->fPt = prog1;
            TAILQ_INSERT_HEAD(&head,n1,entries);
            n1 = malloc(sizeof(struct entry));
            n1->fPt = prog2;
            TAILQ_INSERT_HEAD(&head,n1,entries);
            n1 = malloc(sizeof(struct entry));
            n1->fPt = prog3;
            TAILQ_INSERT_HEAD(&head,n1,entries);

            while (!TAILQ_EMPTY(&head)){
                n1 = TAILQ_FIRST(&head);
                while (!n1->fPt());
                TAILQ_REMOVE(&head,n1,entries);
                free(n1);
            }
            break;
        }
        case 1:{
            tHeap A;
            A.heap_size=0;
            tkey k;
            k.pr = prog1;
            k.key = 100;
            Heap_insert(&A,k);
            k.pr = prog2;
            k.key = 60;
            Heap_insert(&A,k);
            k.pr = prog3;
            k.key = 80;
            Heap_insert(&A,k);

            while (A.heap_size>0) {
                heapsort(&A,A.heap_size);
                tkey k = Heap_Extract(&A);
                while (!k.pr());
            }
            break;
        }
        case 2:{
            tHeap A;
            A.heap_size=0;
            tkey k;
            k.pr = prog1;
            k.key = 128;
            Heap_insert(&A,k);
            k.pr = prog2;
            k.key = 256;
            Heap_insert(&A,k);
            k.pr = prog3;
            k.key = 4;
            Heap_insert(&A,k);

            while (A.heap_size>0) {
                heapsort(&A,A.heap_size);
                swap(&A);
                tkey k = Heap_Extract(&A);
                while (!k.pr());
            }
            break;
        }
        case 3:{
            TAILQ_HEAD(tailhead, entry) head;
            struct entry {
                int (*fPt)();
                TAILQ_ENTRY(entry) entries;
            } *n1,*n2;

            TAILQ_INIT(&head);
            n1 = malloc(sizeof(struct entry));
            n1->fPt = prog1;
            TAILQ_INSERT_HEAD(&head,n1,entries);
            n1 = malloc(sizeof(struct entry));
            n1->fPt = prog2;
            TAILQ_INSERT_HEAD(&head,n1,entries);
            n1 = malloc(sizeof(struct entry));
            n1->fPt = prog3;
            TAILQ_INSERT_HEAD(&head,n1,entries);

            n1 = TAILQ_FIRST(&head);

            while (!TAILQ_EMPTY(&head)){
                n1 = TAILQ_FIRST(&head);
                int i = n1->fPt();
                TAILQ_REMOVE(&head,n1,entries);
                if (i) free(n1);
                else TAILQ_INSERT_TAIL(&head,n1,entries);
            }
            break;
        }
    }


    return 0;
}
