#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    int n, a[5][7];
    srand(time(NULL));

    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩：");
    scanf("%d", &n);
    if (n < 1 || n > 5) return 1;

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
    fprintf(fp, "======== lotto649 =========\n");
    fprintf(fp, "= %s %d %02d:%02d:%02d %d =\n", d, p->tm_mday,
            p->tm_hour, p->tm_min, p->tm_sec, p->tm_year + 1900);
    for (int i = 0; i < 5; i++) {
        fprintf(fp, "[%d]:", i + 1);
        for (int j = 0; j < 7; j++) {
            if (i < n) fprintf(fp, " %02d", a[i][j]);
            else fprintf(fp, " --");
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "======== csie@CGU =========\n");
    fclose(fp);

    printf("以為您購買的 %d 組樂透組合輸出至 lotto.txt\n", n);

#ifdef _WIN32
    printf("\n");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    fp = fopen("lotto.txt", "r");
    int c, line = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '=' || c == '-') SetConsoleTextAttribute(h, 6);       
        else if (c >= '0' && c <= '9' && line > 0) SetConsoleTextAttribute(h, 9); 
        else SetConsoleTextAttribute(h, 7);                            
        putchar(c);
        if (c == '\n') line++;
    }
    SetConsoleTextAttribute(h, 7);
    fclose(fp);
#endif

    return 0;
}
