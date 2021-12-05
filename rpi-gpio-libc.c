/**
 * @file   main.c, Exercice1
 * @author Mohammad Barin Wahidi
 * @date   9 novembre 2021
 * @brief  Utilisation de la librairie standard C pour contrôler les GPIO du rPi.
 *         L’application s’appelle rpi-gpio et prend les paramètres suivants:
 *         rpi-gpio bcm_pin on|off
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) 
{
    int gpio = atoi(argv[1]);   //convert gpio char to gpio int
    int fd; //file descriptor
    char buf[50];  //buffer to access the sysfs with the right gpio number

    if (gpio < 0 || gpio > 27)
    {
        printf("Numéro de GPIO inexistant.\n\r");
        return 0;
    }
    else
    {
        fd = open("/sys/class/gpio/export", O_WRONLY);

        if (fd == -1) 
        {
            printf("Unable to open /sys/class/gpio/export");
            return 0;
        }
        
        write(fd, argv[1], strlen(argv[1])); 
        close(fd);

        sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);
        fd = open(buf, O_WRONLY);
        if (fd < 0) 
        {
        printf("Unable to open /sys/class/gpio/gpio%d/direction", gpio);
        return 0;
        }

        if (write(fd, "out", 3) != 3)
        {
           printf("Error writing to /sys/class/gpio/gpio%d/direction", gpio); 
           return 0;
        }
        close(fd);
    }

    if(argv[2][1] == 'n')
    {
        sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
        fd = open(buf, O_WRONLY);
        if (fd < 0)
        {
            printf("Unable to open /sys/class/gpio/gpio%d/value", gpio);
            return 0;
        }
        write(fd, "1", 1);
        close(fd);

    }
    else if (argv[2][1] == 'f')
    {
        sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
        fd = open(buf, O_WRONLY);
        write(fd, "0", 1);
        close(fd);
        
    }
    else
    {
        printf("Écrivez on ou off la prochaine fois.\n\r");
        return 0;
    }

    fd = open("/sys/class/gpio/unexport", O_WRONLY);

        if (fd == -1) 
        {
            printf("Unable to open /sys/class/gpio/unexport");
            return 0;
        }
    write(fd, gpio, strlen(argv[1])); 
    close(fd);
    
    return 0;
}
