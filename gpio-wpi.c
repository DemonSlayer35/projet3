#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include "gpio.h"

void set_gpio(char *numPin, char state)
{
    int gpio = atoi(numPin);

    if (gpio < 0 || gpio > 27)
    {
        printf("Numéro de GPIO inexistant.\n\r");
        return;
    }
    else
    {
        wiringPiSetupGpio();
        pinMode(gpio, 1);
    }

    if(state == 'n')
    {
        digitalWrite(gpio, 1);
    }
    else if (state == 'f')
    {
        digitalWrite(gpio, 0);
    }
    else
    {
        printf("Écrivez on ou off la prochaine fois.\n\r");
        return;
    }
    
    return;
}