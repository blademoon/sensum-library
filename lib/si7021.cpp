#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

// Функция для получения данных с сенсора SI7021
int read_si7021(float &humidity, float &temperature)	{

	// Переменные необходимы для работы функции
	int file_descriptor;									// Дескриптор файла шины I2C
	const char *i2c_file_path =	"/dev/i2c-1";				// Путь к файлу шины I2C - 1
	int SI7021_I2C_ADDR = 0x40;								// Задаём адрес сенсора на шине I2C

	if	((file_descriptor = open(i2c_file_path, O_RDWR)) < 0)	{
		std::cout << "SENSUS SENSOR LIB - function read_si7021() ERROR: Can't open I2C bus file " << i2c_file_path << " for read and write!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_OPEN_I2C_BUS_FILE;
	}

	if ((ioctl(file_descriptor, I2C_SLAVE, SI7021_I2C_ADDR)) < 0)	{
		std::cout << "SENSUS SENSOR LIB - function read_si7021() ERROR: Failed to acquire bus access and/or talk to slave sensor!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	}

	char config[1] = {0xF5};
	if ((write(file_descriptor, config, 1)) == -1)	{
		std::cout << "SENSUS SENSOR LIB - function read_si7021() ERROR: Failed to acquire bus access. Can't send command to sensor SI7021!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	}

	sleep(1);

	char data[2] = {0};
	if (read(file_descriptor, data, 2) != 2)	{
		std::cout << "SENSUS SENSOR LIB - function read_si7021() ERROR: Failed to acquire bus access. Can't read data from sensor SI7021!" << std::endl;
		return FUNC_ERR_ACQ_I2C_BUS;
	}

	humidity = ((((data[0] * 256 + data[1]) * 125.0) / 65536.0) - 6);

	config[0] = 0xF3;
	if (write(file_descriptor, config, 1) == -1)	{
		std::cout << "SENSUS SENSOR LIB - function read_si7021() ERROR: Failed to acquire bus access. Can't send command to sensor SI7021!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	}

	sleep(1);

	if(read(file_descriptor, data, 2) != 2)	{
		std::cout << "SENSUS SENSOR LIB - function read_si7021() ERROR: Failed to acquire bus access. Can't read data from sensor SI7021!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	}

	close(file_descriptor);

	temperature = (((data[0] * 256 + data[1]) * 175.72) / 65536.0) - 46.85;

	return FUNCTION_SUCCESS;

}
