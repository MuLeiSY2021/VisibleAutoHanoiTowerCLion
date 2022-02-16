#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

static int discHigh = 3;
static int languageValue = 0;

typedef struct disc {
    int aryX;
    int aryY;
} *D;


int **buildHanoiTower() {
    int **HanoiTower = (int **)malloc(sizeof(int *) * 3);

    for (int i = 0; i < 3; i++) {
        int *pole = (int *)malloc(sizeof(int) * discHigh);
        HanoiTower[i] = pole;
        for (int o = 0; o < discHigh; o++) {
            HanoiTower[i][o] = -1;
        }
    }

    for (int i = 0; i < discHigh; i++) {
        HanoiTower[0][i] = discHigh - i;
    }
    return HanoiTower;
}

D *budDiscPile() {
    D *discPile = (D *)malloc(sizeof(D *)*discHigh);
    for (int i = 0; i < discHigh; i++) {
        D tem_disc = (D)malloc(sizeof(struct disc));
        tem_disc->aryX = 0;
        tem_disc->aryY = i;
        discPile[i] = tem_disc;
    }
    return discPile;
}

void movDisc(int **, D *, int, int);

void movDiscPile(int **HanoiTower, D *discPile, int ptr_discNum, int ptr_pole) {
    int now_pole = discPile[discHigh - ptr_discNum]->aryX;
    int ary_ptrPole[3] = {0};
    int nxt_pole = 0;
    ary_ptrPole[ptr_pole] = 1;
    ary_ptrPole[now_pole] = 1;
    for (int i = 0; i < 3; i++) {
        if (ary_ptrPole[i] == 0) {
            nxt_pole = i;
            break;
        }
    }


    if (discPile[discHigh - ptr_discNum]->aryY == discHigh - 1
        || HanoiTower[now_pole][discPile[discHigh - ptr_discNum]->aryY + 1] == -1)
        movDisc(HanoiTower, discPile, ptr_discNum, ptr_pole);
    else {
        int nxt_discNum = HanoiTower[now_pole][discPile[discHigh - ptr_discNum]->aryY + 1];
        movDiscPile(HanoiTower, discPile, nxt_discNum, nxt_pole);
        movDisc(HanoiTower, discPile, ptr_discNum, ptr_pole);
        movDiscPile(HanoiTower, discPile, nxt_discNum, ptr_pole);
    }
}

void prnHanoiTower(int **, D *, int, int);

void movDisc(int **HanoiTower, D *discPile, int ptr_discNum, int ptr_pole) {
    int ptr_poleLv;
    for (int i = discHigh - 1; i >= 0; i--) {
        if (HanoiTower[ptr_pole][i] != -1) {
            ptr_poleLv = i;
            break;
        } else if (i == 0)
            ptr_poleLv = -1;
    }
    ptr_poleLv++;
    HanoiTower[ptr_pole][ptr_poleLv] = ptr_discNum;
    HanoiTower[discPile[discHigh - ptr_discNum]->aryX][discPile[discHigh - ptr_discNum]->aryY] = -1;
    discPile[discHigh - ptr_discNum]->aryX = ptr_pole;
    discPile[discHigh - ptr_discNum]->aryY = ptr_poleLv;
    prnHanoiTower(HanoiTower, discPile, ptr_discNum, ptr_pole);
}

void prnHanoiTower(int **HanoiTower, D *discPile, int ptr_discNum, int ptr_pole) {
    printf("Mov Action:\n");
    printf("Disc%2d:\n  Move to --> Pole%d\n", ptr_discNum, ptr_pole + 1);
    for (int i = 0; i < 3; i++) {
        printf("pole%d:", i + 1);
        for (int i = 0; i < (discHigh * 2 + 1); i++)
            printf(" ");
    }
    printf("\n");
    for (int i = discHigh - 1; i >= 0; i--) {
        for (int o = 0; o < 3; o++) {
            printf("      ");
            if (HanoiTower[o][i] != -1) {
                for (int n = 0; n < (discHigh - HanoiTower[o][i]); n++)
                    printf(" ");
                for (int n = 0; n < HanoiTower[o][i]; n++)
                    printf("-");
                printf("%d", HanoiTower[o][i]);
                for (int n = 0; n < HanoiTower[o][i]; n++)
                    printf("-");
                for (int n = 0; n < (discHigh - HanoiTower[o][i]); n++)
                    printf(" ");
            } else {
                for (int i = 0; i < (discHigh * 2 + 1); i++)
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("--------------------------------------------------------\n");
    if (languageValue == 2)
        printf("Please enter \"Enter\" to next step\n");
    else
        printf("请输入\"回车\"进行下一步\n");
    getchar();
}

void prnSrcHanoiTower(int **HanoiTower) {
    for (int i = 0; i < 3; i++) {
        printf("pole%d:", i + 1);
        for (int i = 0; i < (discHigh * 2 + 1); i++)
            printf(" ");
    }
    printf("\n");
    for (int i = discHigh - 1; i >= 0; i--) {
        for (int o = 0; o < 3; o++) {
            printf("      ");
            if (HanoiTower[o][i] != -1) {
                for (int n = 0; n < (discHigh - HanoiTower[o][i]); n++)
                    printf(" ");
                for (int n = 0; n < HanoiTower[o][i]; n++)
                    printf("-");
                printf("%d", HanoiTower[o][i]);
                for (int n = 0; n < HanoiTower[o][i]; n++)
                    printf("-");
                for (int n = 0; n < (discHigh - HanoiTower[o][i]); n++)
                    printf(" ");
            } else {
                for (int i = 0; i < (discHigh * 2 + 1); i++)
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("----------------------------------------------------------\n");
    Sleep(1000);
}

void AutoSolveHanoiTower(int discnum) {
    discHigh = discnum;
    int **HanoiTower = buildHanoiTower();
    D *discPile = budDiscPile();
    prnSrcHanoiTower(HanoiTower);
    movDiscPile(HanoiTower, discPile, discHigh, 2);
    if (languageValue == 2)
        printf("----------------The program ends running----------------\n");
    else
        printf("----------------------�������н���-----------------------\n");
}


int main() {
    int discnum;
    printf("----------------------------------------------------------\n");
    printf("|                      选择程序语言                       |\n");
    printf("|              Please choose program language:           |\n");
    printf("|              1.Chinese         2.England               |\n");
    printf("----------------------------------------------------------\n");
    for (;;) {
        printf("请输入选项数字 Please input number:\n");
        scanf("%d", &languageValue);
        if (languageValue == 1 || languageValue == 2)
            break;
        else
            printf("你选择了错误输出 You made a mistake in your input\n");
    }
    if (languageValue == 2) {
        printf("----------------------------------------------------------\n");
        printf("|    Automatic solution of the Hanoi-tower Tower program    |\n");
        printf("|                                                        |\n");
        printf("|   Please enter the number of floors of Hanoi Tower:    |\n");
        printf("----------------------------------------------------------\n");
    } else {
        printf("----------------------------------------------------------\n");
        printf("|                    自动解汉诺塔程序                     |\n");
        printf("|                                                        |\n");
        printf("|                   请输入汉诺塔的层高                    |\n");
        printf("----------------------------------------------------------\n");
    }
    scanf("%d", &discnum);
    getchar();
    AutoSolveHanoiTower(discnum);
    return 0;
}
