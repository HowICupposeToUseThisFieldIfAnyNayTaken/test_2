
#include "proto.h"
 uint8_t global_proto_data[UINT8_MAX];
 uint8_t global_is_buff_full= 0;//можно читать входные данные в s_msg_in
 uint8_t global_is_data_in_lost= 0;//поднимается, если сообщение не считано а новые данные поступили. новые утеряны.
 uint8_t global_tim_expired_flag= 0;
 struct s_proto_msg s_msg_in;
//не объявлять их в хедере
uint8_t global_is_tim_expired = 0;
uint8_t global_is_start_data = 0;

struct s_proto_msg s_msg_out;

//считываем входной поток
//ждем преамбулу, запускаем таймер, читаем дальше, если приемник мы, считываем в буфер иначе сбрасываем и сначала.
//по истечению таймера, сбрасываем и снова ждем.
void PROTOX_IRQHandler(){
    static uint32_t get_pre_ambl = 0;
    static uint8_t crc_tmp = PROTO_PRE_ABL_CRC;
    static uint8_t i = 0;
    static uint8_t length = UINT8_MAX;
    static uint8_t source = UINT8_MAX;
    uint8_t reg_data = 0;
    static uint8_t pre_a_ready = 0;
    reg_data = *(uint8_t *)PROTO_DATA_OUT_REG;
    if(i >= length){//принят весь пакет
        //fill struct msg
        s_msg_in.lenght = length + PROTO_PRE_AMBLE_LENGHT;
        s_msg_in.master_addr =source;
        s_msg_in.crc = crc_tmp == reg_data;
        s_msg_in.data_prt = PROTO_BUFF_IN_PTR;
        global_is_buff_full =1;
    }
    if(i >= length || global_is_tim_expired){//зануляем при приеме или истечении времени
        crc_tmp = PROTO_PRE_ABL_CRC;
        length = UINT8_MAX;
        source = UINT8_MAX;
        get_pre_ambl = 0;
        pre_a_ready = 0;
        i = 0;
        TIM1_DISABLE();
        global_is_start_data = 0;
        global_is_tim_expired=0;
    }
    if(!global_is_start_data){//size adrr_s addr_d
        get_pre_ambl = (get_pre_ambl << 8) | reg_data;
        if(get_pre_ambl == PROTO_PRE_ABML ){//ловим преамбулу
            pre_a_ready = 1;
            tim1_init(TIM1_MSEC_PSK,PROTO_TIME_2_EXEED_MS);
            TIM1_ENABLE();
        }
        //если cчитан размер и аддр1,2
        if(get_pre_ambl & (PROTO_PRE_AMBLE_3<<(3*8)) && pre_a_ready ){
            pre_a_ready = 0;
            if((uint8_t)get_pre_ambl == PROTO_DEVICE_ADDRES){//если приемник мы
                source = get_pre_ambl>>(8*1);
                length = get_pre_ambl>>(8*2);
                length = reg_data - PROTO_PRE_AMBLE_LENGHT;//pre_ambl+lenght_byte-crc_byte
                //если данные не считаны пользователем
                if(global_is_buff_full){
                    global_is_data_in_lost =1;
                    global_is_start_data = 0;
                }else{
                    global_is_start_data = 1;
                    global_is_data_in_lost = 0;
                    TIM1_DISABLE();
                }
            }else{
                TIM1_DISABLE();
            }
        }
    }else{//data & crc
        global_proto_data[i] = reg_data;
        crc_tmp = crc_tmp ^ reg_data;
        i++;
    }
}
