#include "gpio.h"

int main(int argc, char *argv[])
{
    set_gpio(argv[1], argv[2][1]);
}