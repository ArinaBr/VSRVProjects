#include <stdio.h>

int main() {
        int n, AT[10], BT[10], WT[10], G[10], i, m;
        float Avg_wt = 0;

        for(i = 0; i < 1; i++) {
                AT[i] = 0;
                BT[i] = 0;
                WT[i] = 0;
                G[i] = 0;
        }

        printf("Enter the number of processes: \t");
        scanf("%d", &n);

        for(i = 0; i < n; i++) {
                printf("Enter the Arrival time & Burst time for process no %d:", i);
                scanf("%d", &AT[i]);
                scanf("%d", &BT[i]);
        }

        for(i = 0; i < n; i++) {
                WT[i] = G[i] - AT[i];
                Avg_wt = Avg_wt + WT[i];
                G[i + 1]= G[i] + BT[i];
        }

        Avg_wt = Avg_wt / n;
        printf("\n\t Process \t Arrival time \t Ext_Time \t Waiting time \t\n");

        for(i = 0; i < n; i++) {
                printf("\t %d\t\t %d\t\t %d\t\t %d\t\t \n", i, AT[i], BT[i], WT[i]);
        }

        printf("\n The average waiting time is %f\n", Avg_wt);
}
