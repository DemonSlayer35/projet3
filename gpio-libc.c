#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "gpio.h"

void set_gpio(char* numPin, char state)
{
    int gpio = atoi(numPin);
    int fd;
    char buf[50];

    if (gpio < 0 || gpio > 27)
    {
        printf("Numéro de GPIO inexistant.\n\r");
        return;
    }
    else
    {
        fd = open("/sys/class/gpio/export", O_WRONLY);
        write(fd, numPin, strlen(numPin)); 
        close(fd);

        /* ATTENTION! Il faut utiliser sudo parce que sinon, on ne pourra pas accéder à la direction
        juste après l'exportation. On dirait qu'avec sudo, le délai est supprimé. */

        sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);
        fd = open(buf, O_WRONLY);

        write(fd, "out", 3);
        close(fd);
    }

    if(state == 'n')
    {
        sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
        fd = open(buf, O_WRONLY);
        write(fd, "1", 1);
        close(fd);

    }
    else if (state == 'f')
    {
        sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
        fd = open(buf, O_WRONLY);
        write(fd, "0", 1);
        close(fd);
        
    }
    else
    {
        printf("Écrivez on ou off la prochaine fois.\n\r");
        return;
    }

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd, numPin, strlen(numPin)); 
    close(fd);
    
    return;
}