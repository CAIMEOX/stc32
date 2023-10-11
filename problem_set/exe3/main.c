#include "main.h"
#define map(start, end, index, fun) for (index = start; index <= end; index++) {fun;}
#define open(x) map(0, 3, k, GPIO_Write_Bit(Pins[k][0], 1 << Pins[k][1], x == k ? 0 : 1));
int i, j, k;
int Pins[4][2] = { {5,3}, {5,0}, {6,1}, {6,3} };
int arr[4];
int target_number = 1000;

static uint8_t numbers[10][8] = {
    { 1, 1, 1, 1, 1, 1, 0, 0 }, // 0
    { 0, 1, 1, 0, 0, 0, 0, 0 }, // 1
    { 1, 1, 0, 1, 1, 0, 1, 0 }, // 2
    { 1, 1, 1, 1, 0, 0, 1, 0 }, // 3
    { 0, 1, 1, 0, 0, 1, 1, 0 }, // 4
    { 1, 0, 1, 1, 0, 1, 1, 0 }, // 5
    { 1, 0, 1, 1, 1, 1, 1, 0 }, // 6
    { 1, 1, 1, 0, 0, 0, 0, 0 }, // 7
    { 1, 1, 1, 1, 1, 1, 1, 0 }, // 8
    { 1, 1, 1, 1, 0, 1, 1, 0 } 	// 9
};

void ex_digits(int num) {
    int numCount = 0;
    if (num < 0) num = -num;
    memset(arr, 0, sizeof arr);
    while (num != 0) {
        arr[3 - numCount++] = num % 10;
        num /= 10;
    }
}

void setup() {
    Board_Init();
    map(0, 3, i, GPIO_Init(Pins[i][0], 1 << Pins[i][1], GPIO_OUT_PP));
    map(0, 3, i, {
        GPIO_Toggle_Bit(Pins[i][0], 1 << Pins[i][1]);
        GPIO_Init(7, 1 << i, GPIO_OUT_PP);
    });
    PIT_Timer_Ms(TIM0,10);
    PIT_Timer_Ms(TIM1,10);
    GPIO_EXTI_Init(0, GPIO_Pin_7, FALLING_EDGE);
    GPIO_EXTI_Init(0, GPIO_Pin_6, FALLING_EDGE);
    GPIO_EXTI_Init(4, GPIO_Pin_2, FALLING_EDGE);
    GPIO_EXTI_Open(0, GPIO_Pin_6);
    GPIO_EXTI_Open(0, GPIO_Pin_7);
    GPIO_EXTI_Open(4, GPIO_Pin_2);
}

int c = 0;
void timer() interrupt TMR0_VECTOR
{
    PIT_Timer_Clear(TIM0);
    c++;
    if (c % 100 == 0) ex_digits(target_number--);
}

void show_numbers() {
    map(0, 3, i, {
        open(i);
        map(0, 7, j, GPIO_Write_Bit(7, 1 << j, numbers[arr[i]][j]));
        Ms_Delay(1);
    });
}

int on[2], interval[2], button_state[2] ;
void run_state_aux(uint8_t pin, int acc, int index){
    button_state[index] = GPIO_Read_Bit(GPIO_P0, 1 << pin);
    if (interval[index] == 1) ex_digits(target_number += acc); 
    if (!button_state[index] && on[index]) {
        interval[index]++;
        if (interval[index] >= 100) ex_digits(target_number += acc);
    } 
    if (button_state[index]) {
        on[index] = 0;
        interval[index] = 0;
    }
}

void run_state() interrupt TMR1_VECTOR
{   
    run_state_aux(6, 1, 0);
    run_state_aux(7, -1, 1);
}

void mod_number() interrupt P0INT_VECTOR
{
    GPIO_EXTI_Flag_Read(GPIO_P0);
    if (Port_Exti_Flag[0]) {
        GPIO_EXTI_Flag_Clear(GPIO_P0);
        if (ET0) goto end;
        if (Port_Exti_Flag[0] & Port_Pin_6) on[0] = 1;
        if (Port_Exti_Flag[0] & Port_Pin_7) on[1] = 1;
    }
    end:;
}

void pause() interrupt P4INT_VECTOR
{
    GPIO_EXTI_Flag_Read(GPIO_P4);
    if (Port_Exti_Flag[4]) {
        GPIO_EXTI_Flag_Clear(GPIO_P4);
        if (Port_Exti_Flag[4] & Port_Pin_2) ET0 = ~ET0;
    }
}

void main() {
    setup();
    while(1) show_numbers();
}