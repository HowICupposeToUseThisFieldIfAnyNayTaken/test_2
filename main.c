#ifndef MAIN_C
#define MAIN_C
#include "directives.h"
#include "proto.h"
#endif // MAIN_C
int main(){
    uint8_t i;
   do{
        if(global_is_buff_full){
           i = s_msg_in.lenght;
            while(i){
                printf(" %d\n", &s_msg_in.data_prt[i]);
                i--;
            }
       }
   }while(1);
   return 0;
}
