#include "main.h"
#define map(start, end, index, fun) for (index = start; index <= end; index++) {fun;}
#define open(x) map(0, 3, k, GPIO_Write_Bit(Pins[k][0], 1 << Pins[k][1], x == k ? 0 : 1));

int target_number = 0;
int previous_state;
int button_state;
int i, j, k;
int Pins[4][2] = { {5,3}, {5,0}, {6,1}, {6,3} };
int numCount;
int arr[4];

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


void ex_digits(int num) {
    numCount = 0;
    while (num != 0) {
        arr[3 - numCount++] = num % 10;
        num /= 10;
    }
}

void setup(){
    Board_Init();
    map(0, 3, i, GPIO_Init(Pins[i][0], 1 << Pins[i][1], GPIO_OUT_PP));
    map(0, 3, i, {
        GPIO_Toggle_Bit(Pins[i][0], 1 << Pins[i][1]);
        GPIO_Init(7, 1 << i, GPIO_OUT_PP);
    });
    GPIO_Init(GPIO_P0, GPIO_Pin_7, GPIO_PullUp);
}

void show_numbers() {
    map(0, 3, i, {
        open(i);
        map(0, 7, j, GPIO_Write_Bit(7, 1 << j, numbers[arr[i]][j]));
        Ms_Delay(1);
    });
}

void main(){
    setup();
    while(1){
        button_state = GPIO_Read_Bit(GPIO_P0, GPIO_Pin_7);
        if (!button_state && previous_state) ex_digits(target_number++);
        previous_state = button_state;
        show_numbers();
    }
}