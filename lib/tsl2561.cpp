#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

// Функция для получения данных с сенсора TSL2561
int read_tsl2561(float &visible_lux, float &ir_lux, float &total_lux)	{

	// Переменные необходимы для работы функции
	int file_descriptor;									// Дескриптор файла шины I2C
	const char *i2c_file_path =	"/dev/i2c-1";				// Путь к файлу шины I2C - 1
	int TSL2561_I2C_ADDR = 0x39;							// Задаём адрес сенсора на шине I2C

	if	((file_descriptor = open(i2c_file_path, O_RDWR)) < 0)	{
		std::cout << "SENSUS SENSOR LIB - function read_tsl2561  ERROR: Can't open I2C bus file " << i2c_file_path << " for read and write!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_OPEN_I2C_BUS_FILE;

	}

	if ((ioctl(file_descriptor, I2C_SLAVE, TSL2561_I2C_ADDR)) < 0)	{
		std::cout << "SENSUS SENSOR LIB - function read_tsl2561  ERROR: Failed to acquire bus access and/or talk to slave sensor!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	}

	char config[2] = {0};
	config[0] = 0x00 | 0x80;
	config[1] = 0x03;
	if ((write(file_descriptor, config, 2)) == -1) {
		std::cout << "SENSUS SENSOR LIB - function read_tsl2561  ERROR: Failed to acquire bus access. Can't power on sensor!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	};

	config[0] = 0x01 | 0x80;
	config[1] = 0x02;
	if ((write(file_descriptor, config, 2)) == -1) {
		std::cout << "SENSUS SENSOR LIB - function read_tsl2561  ERROR: Failed to acquire bus access. Can't set integration time!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	};

	sleep(1);

	char reg[1] = {0x0C | 0x80};
	if ((write(file_descriptor, reg, 1)) == -1) {
		std::cout << "SENSUS SENSOR LIB - function read_tsl2561  ERROR: Failed to acquire bus access. Can't send command to sensor SI7021!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	};

	char data[4] = {0};
	if (read(file_descriptor, data, 4) != 4) {
		std::cout << "SENSUS SENSOR LIB - function read_tsl2561  ERROR: Failed to acquire bus access. Can't read result of measurements from sensor!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	}

	close(file_descriptor);

	ir_lux = (data[3] * 256 + data[2]);
 	visible_lux = ((data[1] * 256 + data[0]) - (data[3] * 256 + data[2]));
	total_lux = (data[1] * 256 + data[0]);

	return FUNCTION_SUCCESS;

}
