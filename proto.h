#ifndef PROTO_H
#define PROTO_H
/*
Описание протокола:

Преамбула 4 байта 0x01 0x02 0x03 0x04
Длина сообщения 1 байт
Адрес источника 1 байт
Адрес приёмника 1 байт
Данные N байт
CRC - XOR всех байт сообщения включая преамбулу

максимальное время приёма сообщения 1 сек.

Задание 1.
Написать прототипы функций которые потребуются для обработки протокола.

Задание 2.
Представить реализацию на C алгоритма приёма сообщений протокола.

*/
#include "directives.h"
#include <stdio.h>
#include <stdint.h>

#define PROTO_PRE_AMBLE_0 1
#define PROTO_PRE_AMBLE_1 2
#define PROTO_PRE_AMBLE_2 3
#define PROTO_PRE_AMBLE_3 4
#define PROTO_PRE_AMBLE_LENGHT 4
#define PROTO_PRE_ABML (PROTO_PRE_AMBLE_1<<8*3 | PROTO_PRE_AMBLE_1<<8*2 | PROTO_PRE_AMBLE_1<<8*1 | PROTO_PRE_AMBLE_1<<8*0 )
#define PROTO_PRE_ABL_CRC (PROTO_PRE_AMBLE_3 ^ PROTO_PRE_AMBLE_2 ^ PROTO_PRE_AMBLE_1 ^ PROTO_PRE_AMBLE_0)

#define PROTO_TIME_2_EXEED_MS 1

#define PROTO_BUFF_IN_PTR global_proto_data
#define PROTO_DEVICE_ADDRES 0xf3

#define PROTO_DATA_OUT_REG 0x34234121 /*пусть будет некий регистр откуда мы читаем данные, предположим что у нас физически реализован интерфейс*/



struct s_proto_msg{
    //uint8_t pre_ambl;//= PROTO_PRE_AMBLE_1;
    //uint8_t pre_ambl1;// = PROTO_PRE_AMBLE_2;
    //uint8_t pre_ambl2;// = PROTO_PRE_AMBLE_3;
    //uint8_t pre_ambl3;// = PROTO_PRE_AMBLE_4;
    uint8_t lenght;
    uint8_t master_addr;
    //uint8_t slave_addr;
    uint8_t *data_prt;
    uint8_t crc;
};
extern uint8_t global_proto_data[UINT8_MAX];
extern uint8_t global_is_buff_full;//можно читать входные данные в s_msg_in
extern uint8_t global_is_data_in_lost;//поднимается, если сообщение не считано а новые данные поступили. новые утеряны.
extern uint8_t global_tim_expired_flag;
extern struct s_proto_msg s_msg_in;

//предположим что у нас существует данное прерывание, которое срабатывает при поступлении байта
void PROTOX_IRQHandler();
//отправляет через дма сообщение
uint8_t proto_msg_send(struct s_proto_msg * s_msg);

#endif // PROTO_H
