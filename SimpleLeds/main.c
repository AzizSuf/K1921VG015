#include <K1921VG015.h>
#include <stdint.h>

#define LEDS_MSK	0x0F00
#define LED0_MSK	(1 << 8)
#define LED1_MSK	(1 << 9)
#define LED2_MSK	(1 << 10)
#define LED3_MSK	(1 << 11)

void some_delay()
{
    for (int i = 0; i < 50000; i++)
    {
        asm("NOP");
    }
}

int main(void)
{
    //Разрешаем тактирование GPIOA
    RCU->CGCFGAHB_bit.GPIOAEN = 1;
    //Включаем  GPIOA
    RCU->RSTDISAHB_bit.GPIOAEN = 1;
    GPIOA->OUTENSET = LEDS_MSK;
    GPIOA->DATAOUTCLR = LEDS_MSK;

    uint32_t led_shift = LED0_MSK;

    while (1)
    {
        GPIOA->DATAOUTTGL = led_shift;
        led_shift = led_shift << 1;
        if (led_shift > LED3_MSK)
        {
            led_shift = LED0_MSK;
        }

        some_delay();
    }

    return 0;
}
