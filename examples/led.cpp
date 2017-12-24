#include <iostream>
#include <sensum/fs_gpio.h>

using namespace std;

int main () {
    int lamp_pin = 33;          // к выводу 33 Raspberry Pi 3 подключен светодиод.
                                // Connect LED "+" to Raspberry Pi pin 33.

    export_pin(lamp_pin);       //Экспортируем пин к которому подключен светодиод.
                                //Export the pin connected to the LED.

    // Теперь, перед входом в цикл мигания светодиодом нам необходимо установить "известное" состояние пина.
    // Now, before entering the flashing cycle of the LED, we need to set the "well-known" pin state.

    set_active_low_state(lamp_pin,PIN_ACTIVE_LOW_ON);   // Включаем режим "active_low".
                                                        // Enable Active_low state.

    set_pin_direction(lamp_pin,PIN_OUT);                // Задаём режим работы пина - ВЫВОД.
                                                        // Set the operating mode of pin - OUTPUT.

    set_pin_value(lamp_pin,PIN_OFF);                    // Выключаем светодиод.
                                                        // Turn LED off.

    for (int i=0 ;i < 30;i++)     {
		cout << "Iteration " << i << " of 30 " << endl;

                set_pin_value (lamp_pin,PIN_ON);     		                // Включаем светодиод.
                                                                            // Turn LED on.
                sleep(5);                                                   // Ждём 5 секунд.
                                                                            // Wait 5 seconds.
                set_pin_value (lamp_pin,PIN_OFF);               	        // Выключаем светодиод.
                                                                            // Turn LED off.
                sleep(5);                                                   // Ждём 5 секунд.
                                                                            // Wait 5 seconds.
        }


    return 0;
}
