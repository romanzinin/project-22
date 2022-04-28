#include <sys/time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int voidruntime (long int lim) {

    struct timeval t;
    struct timeval dt;

    gettimeofday (&t, NULL);

    int i = 0;
    while (i < lim) {

            i++;
    }

    gettimeofday (&dt, NULL);

    return 1000000 * (dt.tv_sec - t.tv_sec) + dt.tv_usec - t.tv_usec;
}

int runtime (long int lim) {

    struct timeval t;
    struct timeval dt;


    int ix = rand () % 32767, iy = rand () % 32767;
    float fx = (float)rand() / (float)RAND_MAX * ix, fy = (float)rand() / (float)RAND_MAX * iy;
    double dx = (double)rand() / (double)RAND_MAX * ix, dy = (double)rand() / (double)RAND_MAX * iy;

    gettimeofday (&t, NULL); //�������� ����� ������

    int i = 0;
    while (i < lim) {  //��������� i �� ����� � ����������� ������ ��� ��������

        ix += iy; //���� �������� ������ �������� ��� ��������������� �����
        i++;
    }

    gettimeofday (&dt, NULL); //�������� ����� ���������

    //�������� ��������� ����� �� ��������� � ������������ ��������� � ��� (10^-6 �)
    return 1000000 * (dt.tv_sec - t.tv_sec) + dt.tv_usec - t.tv_usec;
}

typedef struct {
    int delay;
    float avg;
} call;

int main () {

    call blank; //������ ��������
    call total;

    total.delay = 0;
    blank.delay = 0;

    //opers - ����� ��������
    //tests - ����� �������� �� opers
    //<...>.delay - ����� ����� ���� ��������
    //<...>.avg - ������� ����� �����

    int tests, opers, hz;

    FILE* enter = fopen ("input.txt", "r");
    fscanf (enter, "%d %d", &hz, &opers);

    tests = opers;

    call curr;
    curr.delay = 0;

    for (int j = 0; j < tests; j++) blank.delay += voidruntime (opers);
    blank.avg = (float)blank.delay / (float)tests / (float)opers;

    for (int q = 0; q < tests; q++) curr.delay += runtime (opers);
    curr.avg = (float) curr.delay / (float)tests / (float)opers;

    total.avg = curr.avg - blank.avg;
    total.delay = curr.delay - blank.delay;
    float total_ticks = total.avg * (float)hz;

    printf ("\nAverage operation time: %f ms (%f cycles)\nTotal time: %d ms", total.avg, total_ticks, total.delay);
}
