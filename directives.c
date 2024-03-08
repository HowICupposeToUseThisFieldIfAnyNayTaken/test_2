#ifndef DIRECTIVES_C
#define DIRECTIVES_C
#include "directives.h"
void TIM1_UP_IRQHandler (void){}
//полная инициализция канала
int16_t dma_init(uint16_t rx_volume, uint8_t *rx_pointer){return 1;}
//обнуляем счетчик пересланных в\из байт
void dma_rx_reinit(uint16_t rx_volume){}
//инциализация таймера tim_psk - предделитель , tim_arr - счетчик, считает вверх от 0. в конце вызывает прерывание TIM1_UP_IRQHandler и оканчивает счет.
void tim1_init(uint16_t tim_psk, uint16_t tim_arr){}
#endif // DIRECTIVES_C
