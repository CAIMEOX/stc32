#include "main.h"
int k, r;
void setup() {
	for (k = 3; k <= 6; k++) {
		GPIO_Init(3, 2 << k, GPIO_OUT_PP);
	}
}

void light(uint16_t ms) {
	for (k = 3; k <= 6; k++) {
		GPIO_Toggle_Bit(3, 2 << k);
		Ms_Delay(ms);
		GPIO_Toggle_Bit(3, 2 << k);
	}
}

void main(void) {
	Board_Init();
	setup();
	while (1) {
		light(200);
	}
}