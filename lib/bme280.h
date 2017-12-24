#ifndef SENSUM_BME280_H_INCLUDED
#define SENSUM_BME280_H_INCLUDED

// Объявления функций библиотеки Sensus sensor.
int	read_bme280(float &humidity, float &temperature, float &pressure);											// Функция получения данных с сенсора BME280

// Значения возвращаемые функциями.
#define	FUNCTION_SUCCESS    1           			// Функция выполнена успешно. The function completed successfully.
#define FUNC_ERR_OPEN_I2C_BUS_FILE		-300		// Ошибка! Не могу открыть файл /dev/i2c-1. ERROR! Can't open I2C bus file /dev/i2c-1.
#define FUNC_ERR_ACQ_I2C_BUS			-301		// Ошибка! Не удаётся получить доступ к шине I2C или взаимодействовать с сенсором. ERROR! Failed to acquire bus access and / or talk to slave sensor.

// Подключае файл с определениями функций.
#include <sensum/bme280.cpp>

#endif // SENSUM_BME280_H_INCLUDED
