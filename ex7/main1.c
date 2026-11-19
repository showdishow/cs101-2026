#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define O "\033[38;5;208m" 
#define B "\033[38;5;74m"   
#define W "\033[0m"  

int main() {
    int n, a[5][7];
    srand(time(NULL));

    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩：");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 7; j++) {
            int ok;
            do {
                a[i][j] = rand() % 69 + 1;
                ok = 1;
                for (int k = 0; k < j; k++)
                    if (a[i][k] == a[i][j]) ok = 0;
            } while (!ok);
        }
        for (int j = 0; j < 5; j++)        
            for (int k = 0; k < 5 - j; k++)
                if (a[i][k] > a[i][k + 1]) {
                    int t = a[i][k];
                    a[i][k] = a[i][k + 1];
                    a[i][k + 1] = t;
                }
    }

    time_t now = time(NULL);
    struct tm *p = localtime(&now);
    char d[20];
    strftime(d, sizeof d, "%a %b", p);

    FILE *fp = fopen("lotto.txt", "w");
    fprintf(fp, O "========" W " lotto649 " O "=========" W "\n");
    fprintf(fp, O "=" W " %s " B "%d %02d" W ":" B "%02d" W ":" B "%02d %d " O "=" W "\n",
            d, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, p->tm_year + 1900);
    for (int i = 0; i < 5; i++) {
        fprintf(fp, W "[" B "%d" W "]:", i + 1);
        for (int j = 0; j < 7; j++) {
            if (i < n) fprintf(fp, " " B "%02d", a[i][j]);
            else fprintf(fp, " " O "--");
        }
        fprintf(fp, W "\n");
    }
    fprintf(fp, O "========" W " csie@CGU " O "=========" W "\n");
    fclose(fp);

    printf("以為您購買的 %d 組樂透組合輸出至 lotto.txt\n", n);
    return 0;
}
