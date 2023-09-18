#include "main.h"
int k, r, i, t;
int seq[4] = { 3,4,5,6 };
void setup() {
    GPIO_Init(0, GPIO_Pin_7, GPIO_PullUp);
    for (k = 3; k <= 6; k++) GPIO_Init(3, 2 << k, GPIO_OUT_PP);
}

void reverse(int* p) {
    for (k = 0; k < 2; k++) {
        t = p[k];
        p[k] = p[3 - k];
        p[3 - k] = t;
    }
}

void light(uint16_t ms) {
    for (k = 0; k < 4; k++) {
        if ((GPIO_Read_Bit(GPIO_P0, GPIO_Pin_7) && seq[0] == 3) || (GPIO_Read_Bit(GPIO_P0, GPIO_Pin_7) == 0 && seq[0] == 6)) reverse(seq);
        GPIO_Toggle_Bit(3, 2 << seq[k]);
        Ms_Delay(ms);
        GPIO_Toggle_Bit(3, 2 << seq[k]);
    }
}

void main(void) {
    Board_Init();
    setup();
    while (1) light(400);
}

