#include "main.h"
int k, r, toggled, l;
void setup() {
    GPIO_Init(0, GPIO_Pin_7, GPIO_PullUp);
    for (k = 3; k < 6; k++) GPIO_Init(3, 2 << k, GPIO_OUT_PP);
}

void run_toggle_bit(int k, uint16_t ms) {
    GPIO_Toggle_Bit(3, 2 << k);
    Ms_Delay(ms);
    GPIO_Toggle_Bit(3, 2 << k);
}

void light(uint16_t ms) {
    if (GPIO_Read_Bit(0, GPIO_Pin_7)) {
        for (k = 3; k <= 6; k++) run_toggle_bit(k, ms);
    }
    else {
        for (k = 6; k >= 3; k--) run_toggle_bit(k, ms);
    }
}

void main(void) {
    Board_Init();
    setup();
    while (1) light(200);
}