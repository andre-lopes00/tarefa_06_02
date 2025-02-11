#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

const uint SERVO_PWM_PIN = 22;
const uint LED_PWM_PIN = 12;

const float DIV = 100.0;
const uint WRAP = 25000;

const uint  MOV_180 = 2400;
const uint MOV_90 = 1470;
const uint MOV_0 = 500;

#define US_TO_PWM(us) ((us) * WRAP / 20000) //conversão de microssegundos para ciclos do PWM

void set_pwm_config(uint PIN)
{

    gpio_set_function(PIN, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM

    uint slice = pwm_gpio_to_slice_num(PIN); //obter o canal PWM da GPIO

    pwm_set_clkdiv(slice, DIV); //define o divisor de clock do PWM

    pwm_set_wrap(slice, WRAP); //definir o valor de wrap

    pwm_set_gpio_level(PIN, 0); //definir o ciclo de trabalho (duty cycle) do pwm

    pwm_set_enabled(slice, true); //habilita o pwm no slice correspondente
}

void movimento_inicial (void)
{
    pwm_set_gpio_level(SERVO_PWM_PIN, US_TO_PWM(MOV_180)); pwm_set_gpio_level(LED_PWM_PIN,US_TO_PWM(MOV_180)); 
    sleep_ms(5000);
    pwm_set_gpio_level(SERVO_PWM_PIN,US_TO_PWM(MOV_90)); pwm_set_gpio_level(LED_PWM_PIN, US_TO_PWM(MOV_90));
    sleep_ms(5000);
    pwm_set_gpio_level(SERVO_PWM_PIN, US_TO_PWM(MOV_0)); pwm_set_gpio_level(LED_PWM_PIN, US_TO_PWM(MOV_0));
    sleep_ms(5000);
}



int main()
{   
    stdio_init_all();
    set_pwm_config(LED_PWM_PIN);
    set_pwm_config(SERVO_PWM_PIN);
    movimento_inicial();

    while (true) {
        for(int WRAP_CICLO = MOV_0; WRAP_CICLO<=MOV_180; WRAP_CICLO+=5){
            pwm_set_gpio_level(SERVO_PWM_PIN, US_TO_PWM(WRAP_CICLO));
            pwm_set_gpio_level(LED_PWM_PIN, US_TO_PWM(WRAP_CICLO));
            sleep_ms(10);
        }
        for(int WRAP_CICLO = MOV_180; WRAP_CICLO>=MOV_0; WRAP_CICLO-=5){
            pwm_set_gpio_level(SERVO_PWM_PIN, US_TO_PWM(WRAP_CICLO));
            pwm_set_gpio_level(LED_PWM_PIN, US_TO_PWM(WRAP_CICLO));
            sleep_ms(10);
        }
    }
}

