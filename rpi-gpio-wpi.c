/**
 * @file   main.c, Exercice1
 * @author Mohammad Barin Wahidi
 * @date   9 novembre 2021
 * @brief  Utilisation de WiringPi pour contrôler les GPIO du rPi.
 *         L’application s’appelle rpi-gpio et prend les paramètres suivants:
 *         rpi-gpio bcm_pin on|off
 */

#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>


int main(int argc, char *argv[]) 
{
    int gpio = atoi(argv[1]);

    if (gpio < 0 || gpio > 27)
    {
        printf("Numéro de GPIO inexistant.\n\r");
        return 0;
    }
    else
    {
        wiringPiSetupGpio();
        pinMode(gpio, 1);
    }

    if(argv[2][1] == 'n')
    {
        digitalWrite(gpio, 1);
    }
    else if (argv[2][1] == 'f')
    {
        digitalWrite(gpio, 0);
    }
    else
    {
        printf("Écrivez on ou off la prochaine fois.\n\r");
        return 0;
    }
    
    return 0;
}