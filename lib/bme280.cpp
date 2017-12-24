#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>


// Функция для получения данных с сенсора BME280
int	read_bme280(float &humidity, float &temperature, float &pressure)	{

	// Переменные необходимы для работы функции
	int file_descriptor;							// Дескриптор файла шины I2C
	const char *i2c_file_path =	"/dev/i2c-1";		// Путь к файлу шины I2C - 1
	int BME280_I2C_ADDR = 0x76;						// Задаём адрес сенсора на шине I2C
	char data[8] = {0};								// Переменная для хранения данных считываемых с сенсора.
	char b1[24] = {0};
	char config[2] = {0};							// Переменная используемая для хранения настроек записываемых в регистра сенсора.
	char reg[1] = {0x88};							// Переменная хранит номер регистра


	// Открываем файл шины I2C для чтения и записи.
	if	((file_descriptor = open(i2c_file_path, O_RDWR)) < 0)	{
		std::cout << "SENSUS SENSOR LIB - function read_bme280() ERROR: Can't open I2C bus file " << i2c_file_path << " for read and write!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_OPEN_I2C_BUS_FILE;

	}

	// Устанавливаем на шине I2C адрес сенсора.
	if ((ioctl(file_descriptor, I2C_SLAVE, BME280_I2C_ADDR)) < 0)	{
		std::cout << "SENSUS SENSOR LIB - function read_bme280() ERROR: Failed to acquire bus access and/or talk to slave sensor!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	}

	// Считаем 24 байта из регистра 0x88 - это коэффициенты компенсации температуры, влажности и давления.
	if ((write(file_descriptor, reg, 1)) == -1) {
		std::cout << "SENSUS SENSOR LIB - function read_bme280() ERROR: Failed to acquire bus access. Can not write register address to the i2c bus (0x88)!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	};

	if ((read(file_descriptor, b1, 24)) != 24)	{
		std::cout << "SENSUS SENSOR LIB - function read_bme280() ERROR: Failed to acquire bus access. Can not read temperature, humidity and pressure compensation coefficients from the sensor!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	}

	// Конвертируем полученые данные в коэффициента компенсации температуры
	int dig_T1 = (b1[0] + b1[1] * 256);
	int dig_T2 = (b1[2] + b1[3] * 256);

	if(dig_T2 > 32767)	{
		dig_T2 -= 65536;
	}

	int dig_T3 = (b1[4] + b1[5] * 256);

	if(dig_T3 > 32767)	{
		dig_T3 -= 65536;
	}

	// Конвертируем полученые данные в коэффициент компенсации давления
	int dig_P1 = (b1[6] + b1[7] * 256);
	int dig_P2 = (b1[8] + b1[9] * 256);
	if	(dig_P2 > 32767)	{
		dig_P2 -= 65536;
	}

	int dig_P3 = (b1[10] + b1[11] * 256);
	if (dig_P3 > 32767)	{
		dig_P3 -= 65536;
	}

	int dig_P4 = (b1[12] + b1[13] * 256);
	if (dig_P4 > 32767)	{
		dig_P4 -= 65536;
	}

	int dig_P5 = (b1[14] + b1[15] * 256);
	if (dig_P5 > 32767)	{
	dig_P5 -= 65536;
	}

	int dig_P6 = (b1[16] + b1[17] * 256);
	if (dig_P6 > 32767)	{
		dig_P6 -= 65536;
	}

	int dig_P7 = (b1[18] + b1[19] * 256);
	if (dig_P7 > 32767)	{
		dig_P7 -= 65536;
	}

	int dig_P8 = (b1[20] + b1[21] * 256);
	if (dig_P8 > 32767)	{
	dig_P8 -= 65536;
	}

	int dig_P9 = (b1[22] + b1[23] * 256);
	if (dig_P9 > 32767)	{
		dig_P9 -= 65536;
	}

	// Считываем 1 байт данных из регистра 0xA1. Это часть коэффициента компенсации влажности.
	reg[0] = 0xA1;

	if ((write(file_descriptor, reg, 1)) == -1) {
		std::cout << "SENSUS SENSOR LIB - function read_bme280() ERROR: Failed to acquire bus access. Can not write register address to the i2c bus (0xA1)!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	};

	if ((read(file_descriptor, data, 1)) != 1)	{
		std::cout << "SENSUS SENSOR LIB - function read_bme280() ERROR: Failed to acquire bus access. Can not read part of the humidity compensation coefficient!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	}

	int dig_H1 = data[0];

	// Считываем 7 байт данных из регистра 0xE1. Это часть коэффициента компенсации влажности.
	reg[0] = 0xE1;

	if ((write(file_descriptor, reg, 1)) == -1) {
		std::cout << "SENSUS SENSOR LIB - function read_bme280() ERROR: Failed to acquire bus access. Can not write register address to the i2c bus (0xE1)!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	};

	if ((read(file_descriptor, b1, 7)) != 7)	{
		std::cout << "SENSUS SENSOR LIB - function read_bme280() ERROR: Failed to acquire bus access. Can not read part of the humidity compensation coefficient!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	}

	// Конвертируем полученые данные в коэффициент компенсации влажности
	int dig_H2 = (b1[0] + b1[1] * 256);
	if (dig_H2 > 32767)	{
		dig_H2 -= 65536;
	}

	int dig_H3 = b1[2] & 0xFF ;
	int dig_H4 = (b1[3] * 16 + (b1[4] & 0xF));

	if (dig_H4 > 32767)	{
		dig_H4 -= 65536;
	}
	int dig_H5 = (b1[4] / 16) + (b1[5] * 16);

	if (dig_H5 > 32767)	{
		dig_H5 -= 65536;
	}
	int dig_H6 = b1[6];

	if	(dig_H6 > 127)	{
		dig_H6 -= 256;
	}

	// Выбираем регистр управления сбором данных о влажности устройства (0xF2)
	// Задаём частоту передескритизации измерения влажности = 1(0x01)
	// Возможные варианты значений: 0x00 - X0, 0x01 - X1, 0x02 - X2, 0x03 - X4, 0x04 - X8, 0x05 - X16.
	config[0] = 0xF2;
	config[1] = 0x01;

	if ((write(file_descriptor, config, 2)) == -1) {
		std::cout << "SENSUS SENSOR LIB - function read_bme280() ERROR: Failed to acquire bus access. Can not set oversampling of humidity data!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	};

	// Выбираем регист управления измерениями (0xF4)
	// Задаём нормальный режим измерений, частота передескритизации измерений температуры и давления = 1(0x27)
	// Возможные варианты: 0x00 - X0, 0x27 - X1, 0x4B - X2, 0x6F - X4, 0x93 - X8, 0xB7 - X16.	Пунк 7.4.5
	config[0] = 0xF4;
	config[1] = 0x4B;

	if ((write(file_descriptor, config, 2)) == -1) {
		std::cout << "SENSUS SENSOR LIB - function read_bme280() ERROR: Failed to acquire bus access. Can not set oversampling of temperature and pressure data!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	};

	// Выбираем регистр конфигурации (настройки) сенсора 0xF5) Пунк 7.4.6
	// Задаём время неактивности (ожидания) в нормальном режиме работы = 1000 ms(0xA0).
	// Это время - период между измерениями (Возможные варианты: 0xE0 - 20 ms, 0xC0 - 10 ms, 0xA - 1000 ms, 0x80 - 500 ms, 0x60 - 250 ms, 0x40 - 125 ms, 0x20 - 62.5 ms, 0x00 - 0.5 ms )
	// Тест. Значения для IIR фильтра(1000 ms, IIR filter x8): 0xAC
	config[0] = 0xF5;
	config[1] = 0xAC;

	if ((write(file_descriptor, config, 2)) == -1) {
		std::cout << "SENSUS SENSOR LIB - function read_bme280() ERROR: Failed to acquire bus access. Can not set inactive duration time in normal mode!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	};


	// Считываем 8 байт данных из регистра (0xF7). Это текущее давление, температура и влажность."
	// pressure msb1, pressure msb, pressure lsb, temp msb1, temp msb, temp lsb, humidity lsb, humidity msb
	reg[0] = 0xF7;

	if ((write(file_descriptor, reg, 1)) == -1) {
		std::cout << "SENSUS SENSOR LIB - function read_bme280() ERROR: Failed to acquire bus access. Can not write register address to the i2c bus (0xF7)!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	};

	if ((read(file_descriptor, data, 8)) != 8)	{
		std::cout << "SENSUS SENSOR LIB - function read_bme280() ERROR: Failed to acquire bus access. Can not read current temperature, humidity and pressure from sensor!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	}

	// Конвертируем давление и температуру в 19-битное значение.
	long adc_p = ((long)(data[0] * 65536 + ((long)(data[1] * 256) + (long)(data[2] & 0xF0)))) / 16;
	long adc_t = ((long)(data[3] * 65536 + ((long)(data[4] * 256) + (long)(data[5] & 0xF0)))) / 16;

	// Конверитруем влажность.
	long adc_h = (data[6] * 256 + data[7]);

	// Расчитываем температурное смещение
	float var1 = (((float)adc_t) / 16384.0 - ((float)dig_T1) / 1024.0) * ((float)dig_T2);
	float var2 = ((((float)adc_t) / 131072.0 - ((float)dig_T1) / 8192.0) *
					(((float)adc_t)/131072.0 - ((float)dig_T1)/8192.0)) * ((float)dig_T3);
	float t_fine = (long)(var1 + var2);
	temperature = (var1 + var2) / 5120.0;

	// Расчитываем смещение давления
	var1 = ((float)t_fine / 2.0) - 64000.0;
	var2 = var1 * var1 * ((float)dig_P6) / 32768.0;
	var2 = var2 + var1 * ((float)dig_P5) * 2.0;
	var2 = (var2 / 4.0) + (((float)dig_P4) * 65536.0);
	var1 = (((float) dig_P3) * var1 * var1 / 524288.0 + ((float) dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0) * ((float)dig_P1);
	float p = 1048576.0 - (float)adc_p;
	p = (p - (var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((float) dig_P9) * p * p / 2147483648.0;
	var2 = p * ((float) dig_P8) / 32768.0;
	pressure = (p + (var1 + var2 + ((float)dig_P7)) / 16.0) / 100;

	// Расчитываем смещение влажности
	float var_H = (((float)t_fine) - 76800.0);
	var_H = (adc_h - (dig_H4 * 64.0 + dig_H5 / 16384.0 * var_H)) * (dig_H2 / 65536.0 * (1.0 + dig_H6 / 67108864.0 * var_H * (1.0 + dig_H3 / 67108864.0 * var_H)));
	humidity = var_H * (1.0 -  dig_H1 * var_H / 524288.0);
	if(humidity > 100.0)	{
		humidity = 100.0;
	} else if (humidity < 0.0)	{
		humidity = 0.0;
	}

	// Закрываем дескриптор файла и выходим.
	close(file_descriptor);

	return FUNCTION_SUCCESS;
}
