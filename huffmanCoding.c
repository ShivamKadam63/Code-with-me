#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char ch;
    int freq;
    struct Node *l, *r;
} Node;

typedef struct Heap {
    int size;
    Node **arr;
} Heap;

Node *newNode(char ch, int freq) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->ch = ch;
    n->freq = freq;
    n->l = n->r = NULL;
    return n;
}

void swap(Node **a, Node **b) {
    Node *t = *a;
    *a = *b;
    *b = t;
}

void heapify(Heap *h, int i) {
    int sm = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < h->size && h->arr[l]->freq < h->arr[sm]->freq) sm = l;
    if (r < h->size && h->arr[r]->freq < h->arr[sm]->freq) sm = r;
    if (sm != i) {
        swap(&h->arr[sm], &h->arr[i]);
        heapify(h, sm);
    }
}

Heap *newHeap(int cap) {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->size = 0;
    h->arr = (Node **)malloc(cap * sizeof(Node *));
    return h;
}

void insertHeap(Heap *h, Node *n) {
    int i = h->size++;
    while (i && n->freq < h->arr[(i - 1) / 2]->freq) {
        h->arr[i] = h->arr[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->arr[i] = n;
}

Node *extractMin(Heap *h) {
    Node *t = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    heapify(h, 0);
    return t;
}

Node *buildTree(char ch[], int freq[], int n) {
    Heap *h = newHeap(n);
    for (int i = 0; i < n; i++)
        insertHeap(h, newNode(ch[i], freq[i]));
    while (h->size > 1) {
        Node *x = extractMin(h);
        Node *y = extractMin(h);
        Node *z = newNode('$', x->freq + y->freq);
        z->l = x;
        z->r = y;
        insertHeap(h, z);
    }
    return extractMin(h);
}

void storeCodes(Node *root, char *code, int top, char codes[256][20]) {
    if (root->l) {
        code[top] = '0';
        storeCodes(root->l, code, top + 1, codes);
    }
    if (root->r) {
        code[top] = '1';
        storeCodes(root->r, code, top + 1, codes);
    }
    if (!root->l && !root->r) {
        code[top] = '\0';
        strcpy(codes[(unsigned char)root->ch], code);
        printf("Char: %c | Code: %s\n", root->ch, code);
    }
}

void generateCodes(Node *root, char codes[256][20]) {
    char code[20];
    storeCodes(root, code, 0, codes);
}

void encodeMessage(char *message, char codes[256][20]) {
    printf("\nEncoded message: ");
    for (int i = 0; message[i] != '\0'; i++)
        printf("%s ", codes[(unsigned char)message[i]]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter no. of characters: ");
    scanf("%d", &n);

    char ch[n];
    int freq[n];

    printf("Enter characters: ");
    for (int i = 0; i < n; i++)
        scanf(" %c", &ch[i]);

    printf("Enter frequencies: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &freq[i]);

    Node *root = buildTree(ch, freq, n);

    char codes[256][20] = {0};
    generateCodes(root, codes);

    char message[100];
    printf("\nEnter message to encode: ");
    scanf("%s", message);
    
    encodeMessage(message, codes);

    return 0;
}
