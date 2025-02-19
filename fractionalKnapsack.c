#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index, value, weight;
    float ratio;
} Item;

int compare(const void *a, const void *b) {
    float r1 = ((Item *)a)->ratio;
    float r2 = ((Item *)b)->ratio;
    return (r2 > r1) - (r2 < r1);  
}

void fracKnapsack(int n, int W, int val[], int wt[]) {
    Item items[n];
    for (int i = 0; i < n; i++) {
        items[i].index = i + 1;  
        items[i].value = val[i];
        items[i].weight = wt[i];
        items[i].ratio = (float)val[i] / wt[i];
    }

    qsort(items, n, sizeof(Item), compare);

    float totalValue = 0;
    int currentWeight = 0;

    printf("Items taken:\n");
    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= W) {
            totalValue += items[i].value;
            currentWeight += items[i].weight;
            printf("Item %d: Full (Weight: %d, Value: %d)\n", items[i].index, items[i].weight, items[i].value);
        } 
        else {
            int remainingWeight = W - currentWeight;
            totalValue += items[i].value * ((float)remainingWeight / items[i].weight);
            printf("Item %d: Fractional (Weight: %d, Value: %.2f)\n", items[i].index, remainingWeight, 
                   items[i].value * ((float)remainingWeight / items[i].weight));
            break;
        }
    }

    printf("\nOptimal value: %.2f\n", totalValue);
}

int main() {
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);

    int values[n], weights[n];

    printf("Enter values of items: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }

    printf("Enter weights of items: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }

    printf("Enter the backpack capacity: ");
    scanf("%d", &W);

    fracKnapsack(n, W, values, weights);

    return 0;
}
