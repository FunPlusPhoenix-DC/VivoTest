#include "demo_common.h"
#include <stdio.h>

int main (void){
    int status = device_controlLED(0,0,100,0);
    char* result;
    device_getResponseCodeString(status,result);
    printf("included successfully,the controlled status : %d \n",status);
    printf("the response code is : %s",result);
    return 0;
}