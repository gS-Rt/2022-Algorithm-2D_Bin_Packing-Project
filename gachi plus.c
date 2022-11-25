#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#define SIZE 10
/*
���� �˰����� �̿��� 2d bin packing �˰���
���̵��: ���ǵ��� ������ �� ���κ��� ä��������, ���� ���� ������ ���� �� ���� �Ʒ����� �����
*/
typedef struct item {
    int width;
    int height;
    int id;
    int gaChi; // ��ġ
    int gastarrain; // ������ ��ġ
}item; //�� �������� ������ ���ο� ������ ũ�⸦ ����

typedef struct things { //�κ��� �� ������ ������ ����
    int tid;
    int tx;
    int ty;
    int twidth;
    int theight;
    int tgaChi;
} things; //thing�� int������ �ǹ̷� �׳� �տ� t����

int inven[SIZE][SIZE] = { 0 };

void merge(item arr[], int left, int right) {
    int center = (left + right) / 2;
    int l = left, t = left, c = center + 1;
    item temp[100000];

    while (l <= center && c <= right) {
        if (arr[l].height > arr[c].height)
            temp[t++] = arr[l++];
        else if (arr[l].height < arr[c].height)
            temp[t++] = arr[c++];
        else {
            if (arr[l].width > arr[c].width)
                temp[t++] = arr[l++];
            else
                temp[t++] = arr[c++];
        }
    }

    if (l <= center) {
        while (l <= center) {
            temp[t++] = arr[l++];
        }
    }
    else {
        while (c <= right) {
            temp[t++] = arr[c++];
        }
    }

    while (left <= right) {
        arr[left] = temp[left];
        left++;
    }
}

void mergeSort(item arr[], int left, int right) {

    if (left >= right)
        return;

    int center = (left + right) / 2;
    mergeSort(arr, left, center);
    mergeSort(arr, center + 1, right);
    merge(arr, left, right);
}

void merge_gaChi(item arr[], int left, int right) {
    int center = (left + right) / 2;
    int l = left, t = left, c = center + 1;

    item temp[100000];

    while (l <= center && c <= right) {
        if (arr[l].gastarrain > arr[c].gastarrain)
            temp[t++] = arr[l++];
        else if (arr[l].gastarrain < arr[c].gastarrain)
            temp[t++] = arr[c++];
        else {
            if (arr[l].height > arr[c].height)
                temp[t++] = arr[l++];
            else if (arr[l].height < arr[c].height)
                temp[t++] = arr[c++];
            else {
                if (arr[l].width > arr[c].width)
                    temp[t++] = arr[l++];
                else
                    temp[t++] = arr[c++];
            }
        }
    }

    if (l <= center) {
        while (l <= center) {
            temp[t++] = arr[l++];
        }
    }
    else {
        while (c <= right) {
            temp[t++] = arr[c++];
        }
    }

    while (left <= right) {
        arr[left] = temp[left];
        left++;
    }
}

void merge_gaChiSort(item arr[], int left, int right) {
    if (left >= right)
        return;

    int center = (left + right) / 2;
    merge_gaChiSort(arr, left, center);
    merge_gaChiSort(arr, center + 1, right);
    merge_gaChi(arr, left, right);
}

int main()
{
    int n;
    int it[SIZE]; // �κ��丮�� �ִ� ������
    int w = 0, h = 0; //���� �˻� ���� x��ǥ�� y��ǥ
    int isSame = 1; // �κ��丮�� ��ȭ�� �Ǵ��� ����
    item arr[10]; //�Է¹��� ���ǵ�
    int index = 0; //inArr�� �ε���
    things inArr[10]; //���� �� ���ǵ�

    printf("������ ���� �Է�(�ִ� 10): ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int x, y, z;
        printf("%2d�� ������ ���ο� ����, ��ġ�� �Է�: ", i + 1);
        scanf("%d %d %d", &x, &y, &z);
        arr[i].width = x;
        arr[i].height = y;
        arr[i].gaChi = z;
        arr[i].gastarrain = z / (x * y);
        arr[i].id = i + 1;
    }

    //mergeSort(arr, 0, n - 1); //merge sort�� arr�� ���� �� ��, ���ΰ� ���ٸ� ���� ������� ���ĵ�. >> ���η� �� ���� �ű⿡ �غ���.
    merge_gaChiSort(arr, 0, n - 1);
    do {
        isSame = 1;
        int longest = 0; //���� ���� �� ���� �� ����, ���� �������� ���� ��ǥ �Ǵܿ�
        w = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i].width > SIZE - w || arr[i].height > SIZE - h) //���� �� ���� �����̸�
                continue;
            else {
                isSame = 0;
                inArr[index].tid = arr[i].id;
                inArr[index].twidth = arr[i].width;
                inArr[index].theight = arr[i].height;
                inArr[index].tx = w;
                inArr[index].ty = h;
                inArr[index].tgaChi = arr[i].gaChi;
                arr[i].width = 21;
                arr[i].width = 21; //���� ���� �Ǵ��Ϸ� �׳� ����. ���Ḯ��Ʈ������ ���� �ɰŰ����� �ϴ� �� ��.
                if (longest < inArr[index].theight)
                    longest = inArr[index].theight;
                w += inArr[index].twidth;
                index++;
            }
        }
        h += longest;
    } while (!isSame);

    for (int i = 0; i < index; i++) {
        for (int a = inArr[i].ty; a < inArr[i].ty + inArr[i].theight; a++) {
            for (int b = inArr[i].tx; b < inArr[i].tx + inArr[i].twidth; b++) {
                inven[a][b] = inArr[i].tid;
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%3d", inven[i][j]);
        }
        printf("\n");
    }

    printf("�κ��丮�� �� ����\n");
    for (int i = 0; i < index; i++) {
        printf("%d�� ����\n", inArr[i].tid);
    }

    printf("�κ��丮 �� ��ġ\n");
    int sum = 0;
    for (int i = 0; i < index; i++) {
        sum += inArr[i].tgaChi;
    }
    printf("%d \n", sum);
    return 0;
}