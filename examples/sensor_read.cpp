#include <iostream>
#include <sensum/bme280.h>
#include <sensum/tsl2561.h>
#include <sensum/tcs34725.h>
#include <sensum/si7021.h>


using namespace std;

int main () {

    // Переменные для хранения значений считанных с датчика влажности BME280.
    float pressure = 0, humidity = 0, temperature = 0;

    //Считываем данные с сенсора BME280, если функция
    if ((read_bme280(humidity,temperature,pressure)) != 1)  {
        cout << "ERROR: Can't read data from bme280 sensor!" << endl;
        exit(1);
    };

    //Выводим инфромацию полученную с датчика BME280.
    cout << "BME280 - Temperature (C) " << temperature << ". Pressure (hPa) " << pressure << ". Humidity (%) " << humidity << "." << endl;
    cout << endl;



    //Переменные для хранения значений освещения считываемых с датчика освещения TSL2561.
    float visible_light = 0, infrared_light = 0, total_light = 0;

    //Считываем данные с сенсора TSL2560
    if ((read_tsl2561(visible_light,infrared_light,total_light)) != 1)  {
        cout << "ERROR: Can't read data from TSL2561 sensor!" << endl;
        exit(1);
    }

    //Выводим инфромацию полученную с датчика TLS 2561.
    cout << "TSL2561 - Visible light (lx) " << visible_light << ". Infrared light " << infrared_light << ". Total light " << total_light << "." << endl;
    cout << endl;



    // Переменные для хранения значений цвета  считываемых с датчика цвета TCS34725
    int red = 0, green = 0, blue = 0, clear = 0, ir = 0;

    //Считываем данные с сенсора TCS34725
    if ((read_tcs34725(red,green,blue,clear,ir)) != 1)  {
        cout << "ERROR: Can't read data from TCS34725 sensor!" << endl;
        exit(1);
    }

    //Выводим инфромацию полученную с датчика TCS34725.
    cout << "TCS34725 - Red (lx): " << red << ". Green (lx): " << green << ". Blue (lx): " << blue << ". Clear (lx): " << clear << ". InfraRed (lx): " << ir << endl;
    cout << endl;



    // Переменные для хранения значений   считываемых с датчика цвета TCS34725
    // Используем переменные объявленные для датчика BME280

    //Считываем данные с сенсора SI7021
    if ((read_si7021(humidity,temperature)) != 1)  {
        cout << "ERROR: Can't read data from SI7021 sensor!" << endl;
        exit(1);
    }

    //Выводим инфромацию полученную с датчика SI7021.
    cout << "SI7021 - Humidity (%): " << humidity << ". Temperature (C): " << temperature << endl;
    cout << endl;


    return 0;
}
