#ifndef DIRECTIVES_H
#define DIRECTIVES_H
#include <stdint.h>
//некоторые макросы взял с пет проектов, и подтянул для них необходимые структуры
#define CPU_CLOCK_MHZ 36/*625*25*9*256*/
#define FREQUENCY_KHZ 1000
#define FREQUENCY_MHZ (1000 * FREQUENCY_KHZ)
#define CPU_CLOCK CPU_CLOCK_MHZ * FREQUENCY_MHZ/

#define TIM_CR1_CEN (uint32_t)1<<0
#define TIM1_MSEC_PSK (CPU_CLOCK_MHZ* FREQUENCY_KHZ)
#define TIM1_DISABLE() {} 	/* отключение таймера 1*/
#define TIM1_ENABLE() {} 		/* включение таймера 1*/

//interrupts
//при переполнении выдает флаг ошибки в global_is_tim_expired
void TIM1_UP_IRQHandler (void);
//полная инициализция канала
int16_t dma_init(uint16_t rx_volume, uint8_t *rx_pointer);
//обнуляем счетчик пересланных в\из байт
void dma_rx_reinit(uint16_t rx_volume);
//инциализация таймера tim_psk - предделитель , tim_arr - счетчик, считает вверх от 0. в конце вызывает прерывание TIM1_UP_IRQHandler и оканчивает счет.
void tim1_init(uint16_t tim_psk, uint16_t tim_arr);
#endif // DIRECTIVES_H
