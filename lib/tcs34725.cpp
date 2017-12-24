#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

// Сенсоры цвета.
// Функция для получения данных с сенсора TCS34725
int read_tcs34725(int &red_color, int &green_color, int &blue_color, int &clear_color, int &ir_luminance)	{

	int file_descriptor;										// Дескриптор файла шины I2C
	const char *i2c_file_path =	"/dev/i2c-1";					// Путь к файлу шины I2C - 1
	int TCS34725_I2C_ADDR = 0x29;								// Задаём адрес сенсора на шине I2C

	if	((file_descriptor = open(i2c_file_path, O_RDWR)) < 0)	{
		std::cout << "SENSUS SENSOR LIB - function read_tcs34725() ERROR: Can't open I2C bus file " << i2c_file_path << " for read and write!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_OPEN_I2C_BUS_FILE;
	}

	if ((ioctl(file_descriptor, I2C_SLAVE, TCS34725_I2C_ADDR)) < 0)	{
		std::cout << "SENSUS SENSOR LIB - function read_tcs34725() ERROR: Failed to acquire bus access and/or talk to slave sensor!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	}

	char config[2] = {0};
	config[0] = 0x80;
	config[1] = 0x03;
	if ((write(file_descriptor, config, 2)) == -1) {
		std::cout << "SENSUS SENSOR LIB - function read_tcs34725() ERROR: Failed to acquire bus access. Can't power on sensor!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	};

	config[0] = 0x81;
	config[1] = 0x00;
	if ((write(file_descriptor, config, 2)) == -1) {
		std::cout << "SENSUS SENSOR LIB - function read_tcs34725() ERROR: Failed to acquire bus access. Can't set ALS time register!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	};

	config[0] = 0x83;
	config[1] = 0xFF;
	if ((write(file_descriptor, config, 2)) == -1) {
		std::cout << "SENSUS SENSOR LIB - function read_tcs34725() ERROR: Failed to acquire bus access. Can't set Wait Time register!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	};

	config[0] = 0x8F;
	config[1] = 0x00;
	if ((write(file_descriptor, config, 2)) == -1) {
		std::cout << "SENSUS SENSOR LIB - function read_tcs34725() ERROR: Failed to acquire bus access. Can't set control register!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	};

	sleep(1);

	char reg[1] = {0x94};
	if (write(file_descriptor, reg, 1) == -1) {
		std::cout << "SENSUS SENSOR LIB - function read_tcs34725() ERROR: Failed to acquire bus access. Can't read data from sensor!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	};

	char data[8] = {0};
	if(read(file_descriptor, data, 8) != 8)	{
		std::cout << "SENSUS SENSOR LIB - function read_tcs34725() ERROR: Failed to acquire bus access. Can't read data from sensor!" << std::endl;
		close(file_descriptor);
		return FUNC_ERR_ACQ_I2C_BUS;
	}
	else	{
		clear_color = (data[1] * 256 + data[0]);
		red_color = (data[3] * 256 + data[2]);
		green_color = (data[5] * 256 + data[4]);
		blue_color = (data[7] * 256 + data[6]);

		ir_luminance = (-0.32466) * (red_color) + (1.57837) * (green_color) + (-0.73191) * (blue_color);

		if (ir_luminance < 0) 		{
			ir_luminance = 0;
		}

		return FUNCTION_SUCCESS;
	}
}
