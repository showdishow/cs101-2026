#include <stdio.h>

int main(){
    FILE*fp;
    int a[] = {0,1,2};
    char b[] = {'A', 'B', 'C'};
    float c[] = {1.1,1.2,1.3};
    fp = fopen("a.bin","wb+");

    fwrite(a,sizeof(a),1,fp);
    fseek(fp, -(long)sizeof(a), SEEK_CUR);
    fread(a,sizeof(a),1,fp);

    for(int i = 0;i < 3;i++){
        printf("%d ",a[i]);
    }

    printf("\n");

    fwrite(b,sizeof(b),1,fp);
    fseek(fp, -(long)sizeof(b), SEEK_CUR);
    fread(b,sizeof(b),1,fp);

    for(int i = 0;i < 3;i++){
        printf("%c ",b[i]);
    }

    printf("\n");

    fwrite(c,sizeof(c),1,fp);
    fseek(fp, -(long)sizeof(c), SEEK_CUR);
    fread(c,sizeof(c),1,fp);

    for(int i = 0;i < 3;i++){
        printf("%f ",c[i]);
    }

    fclose(fp);
    return 0;
}
