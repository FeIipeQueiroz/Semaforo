#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13

typedef enum {
    RED,
    YELLOW,
    GREEN
} TrafficLightState;

TrafficLightState currentState = RED;

bool repeating_timer_callback(struct repeating_timer *t) {
    gpio_put(LED_RED, 0);
    gpio_put(LED_YELLOW, 0);
    gpio_put(LED_GREEN, 0);

    switch (currentState) {
        case RED:
            gpio_put(LED_YELLOW, 1);
            currentState = YELLOW;
            break;
        case YELLOW:
            gpio_put(LED_GREEN, 1);
            currentState = GREEN;
            break;
        case GREEN:
            gpio_put(LED_RED, 1);
            currentState = RED;
            break;
    }

    return true;
}

int main() {
    
    stdio_init_all();

    gpio_init(LED_RED);
    gpio_init(LED_YELLOW);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    gpio_put(LED_RED, 1);

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        printf("Semáforo em funcionamento...\n");
        sleep_ms(1000);
    }

    return 0;
}