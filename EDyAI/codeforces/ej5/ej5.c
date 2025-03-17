#include<stdio.h>
#include<stdlib.h>

int encontrarMinimo(int *denom, int n, int x);

#define INF 1000000000

int main(void) {

    int n, x;
    scanf("%d %d", &n, &x);

    int *denom = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) 
        scanf("%d", &denom[i]);

    int cantidad = encontrarMinimo(denom, n, x);
    if (cantidad != INF)
        printf("%d", cantidad);
    else 
        printf("-1");

    free(denom);
} 

int encontrarMinimo(int *denom, int n, int x) {

    int memo[x + 1];

    memo[0] = 0;

    for (int i = 1; i <= x; i++) {
        memo[i] = INF;
        for (int j = 0; j < n; j++) {
            if (denom[j] <= i) {

                int subRes = memo[i - denom[j]];
                if (subRes != INF && subRes + 1 < memo[i])
                    memo[i] = subRes + 1;
            }
        }
    }

    return memo[x];
}

