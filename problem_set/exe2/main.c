#include "main.h"
#define map(start, end, index, fun) for (index = start; index <= end; index++) {fun;}
#define open(x) map(0, 3, k, GPIO_Write_Bit(Pins[k][0], 1 << Pins[k][1], x == k ? 0 : 1));
#define swap(a, b) temp=a;a=b;b=temp;
uint8_t numbers[10][8] = {
    { 1, 1, 1, 1, 1, 1, 0, 0 }, // 0
    { 0, 1, 1, 0, 0, 0, 0, 0 }, // 1
    { 1, 1, 0, 1, 1, 0, 1, 0 }, // 2
    { 1, 1, 1, 1, 0, 0, 1, 0 }, // 3
    { 0, 1, 1, 0, 0, 1, 1, 0 }, // 4
    { 1, 0, 1, 1, 0, 1, 1, 0 }, // 5
    { 1, 0, 1, 1, 1, 1, 1, 0 }, // 6
    { 1, 1, 1, 0, 0, 0, 0, 0 }, // 7
    { 1, 1, 1, 1, 1, 1, 1, 0 }, // 8
    { 1, 1, 1, 1, 0, 1, 1, 0 }  // 9
};
int i, j, k, temp;
int Pins[4][2] = { {5,3}, {5,0}, {6,1}, {6,3} };
int target_number = 1435;
int numCount, digit; // For ex_digits
uint8_t arr[4] = { 0, 0, 0, 0 };

void ex_digits(int num) {
    numCount = 0;
    while (num != 0) {
        digit = num % 10;
        arr[3 - numCount] = digit;
        numCount++;
        num /= 10;
    }
}

void bubble_sort() {
    map(0, 2, i,
        map(0, 2 - i, j, {
            if (arr[j] > arr[j + 1]) { swap(arr[j], arr[j + 1]); }
        }))
}

void setup() {
    Board_Init();
    map(0, 3, i, GPIO_Init(Pins[i][0], 1 << Pins[i][1], GPIO_OUT_PP));
    map(0, 3, i, {
        GPIO_Toggle_Bit(Pins[i][0], 1 << Pins[i][1]);
        GPIO_Init(7, 1 << i, GPIO_OUT_PP);
        });
}

void show_numbers() {
    while (1) {
        map(0, 3, i, {
            open(i);
            map(0, 7, j, GPIO_Write_Bit(7, 1 << j, numbers[arr[i]][j]));
            Ms_Delay(1);
            });
    }
}

void main() {
    setup();
    ex_digits(target_number);
    bubble_sort();
    show_numbers();
}