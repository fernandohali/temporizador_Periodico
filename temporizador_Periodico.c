#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"

#define LED_RED_PIN 13
#define LED_YELLOW_PIN 12
#define LED_GREEN_PIN 11

#define INTERVAL_MS 3000

static volatile uint8_t counter = 0;

static bool time_semaphore(struct repeating_timer *_);
void init_led();

int main()
{
    stdio_init_all();

    init_led();  // Corrigido: chamada da função init_led

    struct repeating_timer timer;
    add_repeating_timer_ms(INTERVAL_MS, time_semaphore, NULL, &timer);

    while (true)
    {
        printf("Olá, mundo!\n");
        sleep_ms(1000);
    }
}

void init_led()
{
    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_put(LED_RED_PIN, 0);

    gpio_init(LED_YELLOW_PIN);
    gpio_set_dir(LED_YELLOW_PIN, GPIO_OUT);
    gpio_put(LED_YELLOW_PIN, 0);

    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_put(LED_GREEN_PIN, 0);
}

static bool time_semaphore(struct repeating_timer *_)
{
    gpio_put(LED_RED_PIN, counter == 0);
    gpio_put(LED_YELLOW_PIN, counter == 1);
    gpio_put(LED_GREEN_PIN, counter == 2);

    counter = (counter + 1) % 3;

    return true;
}