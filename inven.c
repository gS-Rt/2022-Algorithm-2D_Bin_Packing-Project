#include <stdio.h>
#define SIZE 10
/*
선반 알고리즘을 이용한 2d bin packing 알고리즘
아이디어: 물건들을 정렬한 뒤 가로부터 채워나가기, 가로 끝에 닿으면 가장 긴 물건 아래부터 재시작
*/
typedef struct item {
    int width;
    int height;
    int id;
}item; //각 아이템은 고유의 가로와 세로의 크기를 가짐

typedef struct things { //인벤에 들어간 물건의 정보를 저장
    int tid;
    int tx;
    int ty;
    int twidth;
    int theight;
} things; //thing의 int변수란 의미로 그냥 앞에 t붙임

int inven[SIZE][SIZE] = {0};

void merge(item arr[], int left, int right) {
    int center = (left + right) / 2;
    int l = left, t = left, c = center + 1;
    item temp[100000];
    
    while(l <= center && c <= right) {
        if(arr[l].height > arr[c].height)
            temp[t++] = arr[l++];
        else if(arr[l].height < arr[c].height)
            temp[t++] = arr[c++];
        else {
            if(arr[l].width > arr[c].width)
                temp[t++] = arr[l++];
            else
                temp[t++] = arr[c++];
        }
    }
    
    if(l <= center) {
        while(l <= center) {
            temp[t++] = arr[l++];
        }
    }
    else {
        while(c <= right) {
            temp[t++] = arr[c++];
        }
    }
    
    while(left <= right) {
        arr[left] = temp[left];
        left++;
    }
}

void mergeSort(item arr[], int left, int right) {
    
    if(left >= right)
        return;
    
    int center = (left + right) / 2;
    mergeSort(arr, left, center);
    mergeSort(arr,  center + 1, right);
    merge(arr, left, right);
}

int main()
{
    int n;
    int w = 0, h = 0; //현재 검사 중인 x좌표와 y좌표
    int isSame = 1; // 인벤토리의 변화를 판단할 변수
    item arr[10]; //입력받은 물건들
    int index = 0; //inArr의 인덱스
    things inArr[10]; //실제 들어갈 물건들

    printf("물건의 수를 입력(최대 10): ");
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        int x, y;
        printf("%d번 물건의 가로와 세로를 입력: ", i+1);
        scanf("%d %d", &x, &y);
        arr[i].width = x;
        arr[i].height = y;
        arr[i].id = i + 1;
    }
    
    mergeSort(arr, 0, n - 1); //merge sort로 arr은 세로 긴 순, 세로가 같다면 가로 긴순으로 정렬됨. >> 가로로 쭉 이을 거기에 해봤음.

    do {
        isSame = 1;
        int longest = 0; //넣은 물건 중 가장 긴 세로, 다음 가로줄의 시작 좌표 판단용
        w = 0;
        for(int i = 0; i < n; i ++) {
            if(arr[i].width > SIZE - w || arr[i].height > SIZE - h) //넣을 수 없는 물건이면
                continue;
            else {
                isSame = 0;
                inArr[index].tid = arr[i].id;
                inArr[index].twidth = arr[i].width;
                inArr[index].theight = arr[i].height;
                inArr[index].tx = w;
                inArr[index].ty = h;
                arr[i].width = 21;
                arr[i].width = 21; //넣은 물건 판단하려 그냥 넣음. 연결리스트같은거 쓰면 될거같은데 일단 걍 함.
                if(longest < inArr[index].theight)
                    longest = inArr[index].theight;
                w += inArr[index].twidth;
                index++;
            }
        }
        h += longest;
    } while(!isSame);

    for(int i = 0; i < index; i++) {
        for(int a = inArr[i].ty; a < inArr[i].ty + inArr[i].theight; a++) {
            for(int b = inArr[i].tx; b < inArr[i].tx + inArr[i].twidth; b++) {
                inven[a][b] = inArr[i].tid;
            }
        }
    }
    
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            printf("%3d", inven[i][j]);
        }
        printf("\n");
    }

    return 0;
}