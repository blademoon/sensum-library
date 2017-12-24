#include <cstring>

#include <fcntl.h>
#include <unistd.h>

// Функции библиотеки
// Функция преобразования номера пина в номер порта GPIO
int calculate_pin_number(int pin_number) {

	if ((pin_number == 1) || (pin_number == 17)){ 																		//3.3V PIN
	    #ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() ERROR: This PI2 bus pin is +3.3V PWR and you can't use this pin in programm!" << std::endl;
        #endif // DEBUG
		return FUNC_ERR_PIN_NUM;
	}

	if ((pin_number == 2) || (pin_number == 4)) {																		//5V PIN
	    #ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() ERROR: This PI2 bus pin is +5V PWR and you can't use this pin in programm!" << std::endl;
        #endif // DEBUG
		return FUNC_ERR_PIN_NUM;
	}

	if (pin_number == 3) {																								//WARNING PIN
        #ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() WARNING: This PI2 bus pin has additional functionality (I2C1_SDA)! Use this pin carefully!" << std::endl;
        #endif // DEBUG
		return 2;
	}

	if (pin_number == 5) {
        #ifdef DEBUG                                                                                                    //WARNING PIN
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() WARNING: This PI2 bus pin has additional functionality (I2C1_SCL)! Use this pin carefully!" << std::endl;
        #endif // DEBUG
        return 3;
	}

	if ((pin_number == 6) || (pin_number == 9) || (pin_number == 14) || (pin_number == 20) || (pin_number == 25) || (pin_number == 30) || (pin_number == 34) || (pin_number == 39)) {	//GROUND PIN
        #ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() ERROR: This PI2 bus pin is GND and you can't use this pin in programm!" << std::endl;;
        #endif // DEBUG
		return FUNC_ERR_PIN_NUM;
	}

	if (pin_number == 7) {																								//GOOD PIN
		return 4;
	}

	if (pin_number == 8) {																								//WARNING PIN
        #ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() WARNING: This PI2 bus pin has additional functionality (UART0_TX)! Use this pin carefully!" << std::endl;
        #endif // DEBUG
		return 14;
	}

	if (pin_number == 10) {																								//WARNING PIN
        #ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() WARNING: This PI2 bus pin has additional functionality (UART0_RX)! Use this pin carefully!" << std::endl;
        #endif // DEBUG
		return 15;
	}

	if (pin_number == 11) {																								//GOOD PIN
		return 17;
	}

	if (pin_number == 12) {																								//WARNING PIN
        #ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() WARNING: This PI2 bus pin has additional functionality (PCM_CLK)! Use this pin carefully!" << std::endl;
        #endif // DEBUG
		return 18;
	}

	if (pin_number == 13) {																								//GOOD PIN
		return 27;
	}

	if (pin_number == 15) {																								//GOOD PIN
		return 22;
	}

	if (pin_number == 16) {																								//GOOD PIN
		return 23;
	}

	if (pin_number == 18) {																								//GOOD PIN
		return 24;
	}

	if (pin_number == 19) {																								//WARNING PIN
		#ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() WARNING: This PI2 bus pin has additional functionality (SPI0_M0SI)! Use this pin carefully!" << std::endl;
		#endif // DEBUG
		return 10;
	}

	if (pin_number == 21) {																								//WARNING PIN
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() WARNING: This PI2 bus pin has additional functionality (SPI0_MISO)! Use this pin carefully!" << std::endl;
		return 9;
	}

	if (pin_number == 22) {																								//GOD PIN
		return 25;
	}

	if (pin_number == 23) {																								//WARNING PIN
		#ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() WARNING: This PI2 bus pin has additional functionality (SPI0_SCLK)! Use this pin carefully!" << std::endl;
		#endif // DEBUG
		return 11;
	}

	if (pin_number == 24) {																								//WARNING PIN
		#ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() WARNING: This PI2 bus pin has additional functionality (SPI0_CS0)! Use this pin carefully!" << std::endl;
		#endif // DEBUG
		return 8;
	}

	if (pin_number == 26) {																								//WARNING PIN
		#ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() WARNING: This PI2 bus pin has additional functionality (SPI0_CS1)! Use this pin carefully!" << std::endl;
		#endif // DEBUG
		return 7;
	}

	if (pin_number == 27) {																								//BAD PIN
		#ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() ERROR: This PI2 bus pin is RESERVED!" << std::endl;
		#endif // DEBUG
		return FUNC_ERR_PIN_NUM;
	}

	if (pin_number == 28) {																								//BAD PIN
		#ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() ERROR: This PI2 bus pin is RESERVED" << std::endl;
		#endif // DEBUG
		return FUNC_ERR_PIN_NUM;
	}

	if (pin_number == 29) {																								//GOD PIN
		return 5;
	}

	if (pin_number == 31) {																								//GOD PIN
		return 6;
	}

	if (pin_number == 32) {																								//GOD PIN
		return 12;
	}

	if (pin_number == 33) {																								//GOD PIN
		return 13;
	}

	if (pin_number == 35) {																								//WARNING PIN
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() WARNING: This PI2 bus pin has additional functionality (SPI1_MISO)! Use this pin carefully!" << std::endl;
        #endif // DEBUG
		return 19;
	}

	if (pin_number == 36) {																								//WARNING PIN
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() WARNING: This PI2 bus pin has additional functionality (SPI1_CS0)! Use this pin carefully!" << std::endl;
        #endif // DEBUG
		return 16;
	}

	if (pin_number == 37) {																								//GOD PIN
		return 26;
	}

	if (pin_number == 38) {																								//WARNING PIN
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() WARNING: This PI2 bus pin has additional functionality (SPI1_MOSI)! Use this pin carefully!" << std::endl;
        #endif // DEBUG
		return 20;
	}

	if (pin_number == 40) {																								//WARNING PIN
        #ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() WARNING: This PI2 bus pin has additional functionality (SPI1_SCLK)! Use this pin carefully!" << std::endl;
        #endif // DEBUG
		return 21;
	}

	else {
        #ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function calculate_pin_number() ERROR: Incorrect pin number!" << std::endl;
        #endif // DEBUG
		return FUNC_ERR_PIN_NUM;
	}
}

// Функция экспорта пина GPIO
int export_pin(int pin_number) {

	char buffer[3];
	int file_descriptor;
	int gpio_port = 0;
	const char *path = "/sys/class/gpio/export";

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	gpio_port = calculate_pin_number(pin_number);
	// Добавить debug и release
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if (gpio_port == -1) {
        #ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function export() ERROR: Incorrect Pin number! Please choose another pin!" << std::endl;
        #endif // DEBUG
		return FUNC_ERR_PIN_NUM;
	}

	file_descriptor = open(path, O_WRONLY);
	if (file_descriptor == - 1)	{
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function export() ERROR: Can't open file " << path << " for write!" << std::endl;
        #endif // DEBUG
		return FUNC_ERR_OPEN_EXPORT_WR;
	}

	snprintf(buffer, sizeof(buffer), "%d", gpio_port);

	if ((write(file_descriptor, buffer, sizeof(buffer))) == -1) {
        #ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function export() ERROR: Can't write to file " << path << " " << std::endl;
        #endif // DEBUG
		close(file_descriptor);
		return FUNC_ERR_WR_TO_EXPORT;
	};

	close(file_descriptor);
	return FUNCTION_SUCCESS;
}

// Функция деэкспорта пина GPIO
int unexport_pin(int pin_number) {

	char buffer[3];
	int file_descriptor;
	int gpio_port = 0;
	const char *path = "/sys/class/gpio/unexport";

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	gpio_port = calculate_pin_number(pin_number);
	// Добавить debug и release
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if (gpio_port == -1) {
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function unexport() ERROR: Incorrect Pin number! Please choose another pin!" << std::endl;
        #endif // DEBUG
		return FUNC_ERR_PIN_NUM;
	}

	file_descriptor = open(path, O_WRONLY);
	if (file_descriptor == - 1)	{
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function unexport() ERROR: Can't open file " << path << " for write!" << std::endl;
        #endif // DEBUG
		return FUNC_ERR_OPEN_UNEXPORT_WR;
	}


	snprintf(buffer, sizeof(buffer), "%d", gpio_port);

	if ((write(file_descriptor, buffer, sizeof(buffer))) == -1) {
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function unexport() ERROR: Can't write to file " << path << " !" << std::endl;
        #endif // DEBUG
		close(file_descriptor);
		return FUNC_ERR_WR_TO_UNEXPORT;
	};

	close(file_descriptor);
	return FUNCTION_SUCCESS;
}

// Функция проверки направления работы пина GPIO
int check_pin_direction (int pin_number) {

	ssize_t read_result;
	int     file_descriptor;
	char    READ_BUFFER[3];
	char 	path[40];
	int gpio_port = 0;

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	gpio_port = calculate_pin_number(pin_number);
	// Добавить debug и release
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if (gpio_port == -1) {
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function check_pin_direction() ERROR: Incorrect Pin number! Please choose another pin!" << std::endl;
        #endif // DEBUG
		return FUNC_ERR_PIN_NUM;
	}

	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", gpio_port);

	file_descriptor = open(path, O_RDONLY);
	if (file_descriptor == - 1)	{
        #ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function check_pin_direction() ERROR: Can't open file " << path << " for read!" << std::endl;
        #endif // DEBUG
		return FUNC_ERR_OPEN_DIRECTION_RD;
	}

    read_result = read(file_descriptor, READ_BUFFER, sizeof(READ_BUFFER));
    if (read_result == -1) {
        #ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function check_pin_direction() ERROR: Can't read from file " << path << " !" << std::endl;
        #endif // DEBUG
		close(file_descriptor);
		return FUNC_ERR_RD_FROM_DIRECTION;
	}

    close(file_descriptor);

    if ((strstr(READ_BUFFER,"in") != 0)) {return PIN_IN;}
    if ((strstr(READ_BUFFER,"out") != 0)) { return PIN_OUT;}
	else {
	    #ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function check_pin_direction ERROR: Unknown value in file " << path << " !" << std::endl;
        #endif // DEBUG
		return FUNC_ERR_UNK_DIR_RET;
	}
}

// Функция задания направления работы пина GPIO
int set_pin_direction (int pin_number, int direction) {

	int 	gpio_port = 0;
	char 	path[40];
	int     file_descriptor;
	ssize_t	write_result;
	char    WRITE_BUFFER[4];

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	gpio_port = calculate_pin_number(pin_number);
	// Добавить debug и release
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if (gpio_port == -1) {
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function set_pin_direction() ERROR: Incorrect Pin number! Please choose another pin!" << std::endl;
        #endif // DEBUG
		return FUNC_ERR_PIN_NUM;
	}

	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", gpio_port);

	file_descriptor = open(path, O_WRONLY);
	if (file_descriptor == - 1)	{
        #ifdef DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function set_pin_direction() ERROR: Can't open file " << path << " for write!" << std::endl;
        #endif // DEBUG
		return FUNC_ERR_OPEN_DIRECTION_WR;
	}

	if (direction == PIN_IN) {
		snprintf(WRITE_BUFFER, sizeof(WRITE_BUFFER), "%s", "in");
	}
	if (direction == PIN_OUT) {
		snprintf(WRITE_BUFFER, sizeof(WRITE_BUFFER), "%s", "out");
	}
	if ((direction != PIN_IN) && (direction != PIN_OUT)) {
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function set_pin_direction() ERROR: Incorrect direction for pin! Use PIN_IN for INPUT or PIN_OUT for OUTPUT!" << std::endl;
        #endif // DEBUG
		close(file_descriptor);
		return FUNC_ERR_UNK_DIR_SENT;
	}

	write_result = write(file_descriptor,WRITE_BUFFER,sizeof(WRITE_BUFFER));

	if (write_result == -1) {
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function set_pin_direction() ERROR: Can't write to file " << path << " !" << std::endl;
        #endif // DEBUG
		close(file_descriptor);
		return FUNC_ERR_WR_TO_DIRECTION;
	}

	close(file_descriptor);
	return FUNCTION_SUCCESS;
}

// Функция проверки значения пина GPIO
int check_pin_value (int pin_number) {

	ssize_t read_result;
	int     file_descriptor;
	char    READ_BUFFER[2];
	char 	path[40];
	int gpio_port = 0;

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	gpio_port = calculate_pin_number(pin_number);
    // Добавить debug и release
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if (gpio_port == -1) {
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function check_pin_value() ERROR: Incorrect Pin number! Please choose another pin!" << std::endl;
        #endif // DEBUG
		return FUNC_ERR_PIN_NUM;
	}

	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", gpio_port);

	file_descriptor = open(path, O_RDONLY);
	if (file_descriptor == - 1)	{
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function check_pin_value()ERROR: Can't open file " << path << " for read!" << std::endl;
        #endif // DEBUG
		return FUNC_ERR_OPEN_VALUE_RD;
	}

    read_result = read(file_descriptor, READ_BUFFER, sizeof(READ_BUFFER));
    if (read_result == -1) {
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function check_pin_value() ERROR: Can't read from file " << path << " !" << std::endl;
        #endif // DEBUG
		close(file_descriptor);
		return FUNC_ERR_RD_FROM_VALUE;
	}

    close(file_descriptor);

    if ((strstr(READ_BUFFER,"1") != 0)) {return PIN_ON;}
    if ((strstr(READ_BUFFER,"0") != 0)) { return PIN_OFF;}
	else {
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function check_pin_value ERROR: Unknown value in file " << path << " !" << std::endl;
        #endif // DEBUG
		return FUNC_ERR_UNK_VAL_RET;
	}
}

// Функция задания значения пина GPIO
int set_pin_value (int pin_number, int pin_value) {

	int 	gpio_port = 0;
	char 	path[40];
	int     file_descriptor;
	ssize_t	write_result;
	char    WRITE_BUFFER[2];

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	gpio_port = calculate_pin_number(pin_number);
    // Добавить debug и release
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if (gpio_port == -1) {
		#ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function set_pin_value() ERROR: Incorrect Pin number! Please choose another pin!" << std::endl;
		#endif // DEBUG
		return FUNC_ERR_PIN_NUM;
	}

	if (check_pin_direction(pin_number) == 1) {
		#ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function set_pin_value() ERROR: Incorrect direction for pin. Set pin direction to OUT first!" << std::endl;
		#endif // DEBUG
		return FUNC_ERR_INC_PIN_DIR;
	}

	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", gpio_port);

	file_descriptor = open(path, O_WRONLY);
	if (file_descriptor == - 1)	{
		#ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function set_pin_value() ERROR: Can't open file " << path << " for write!" << std::endl;
		#endif // DEBUG
		return FUNC_ERR_OPEN_VALUE_WR;
	}

	if (pin_value == PIN_ON) {
		snprintf(WRITE_BUFFER, sizeof(WRITE_BUFFER), "%d", 1);
	}
	if (pin_value == PIN_OFF) {
		snprintf(WRITE_BUFFER, sizeof(WRITE_BUFFER), "%d", 0);
	}
	if ((pin_value != PIN_ON) && (pin_value != PIN_OFF)) {
		#ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function set_pin_value() ERROR: Incorrect value for pin! Use PIN_ON for 1 or PIN_OFF for 0!" << std::endl;
		#endif // DEBUG
		close(file_descriptor);
		return FUNC_ERR_UNK_VAL_SENT;
	}

	write_result = write(file_descriptor,WRITE_BUFFER,sizeof(WRITE_BUFFER));
	if (write_result == -1) {
		#ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function set_pin_value() ERROR: Can't write to file " << path << " !" << std::endl;
		#endif // DEBUG
		close(file_descriptor);
		return FUNC_ERR_WR_TO_VALUE;
	}

	close(file_descriptor);
	return FUNCTION_SUCCESS;
}

// Функция проверки active_low режима пина GPIO
int check_active_low_state (int pin_number) {

	ssize_t read_result;
	int     file_descriptor;
	char    READ_BUFFER[2];
	char 	path[40];
	int gpio_port = 0;

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	gpio_port = calculate_pin_number(pin_number);
    // Добавить debug и release
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if (gpio_port == -1) {
		#ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function check_active_low_state() ERROR: Incorrect Pin number! Please choose another pin!" << std::endl;
		#endif // DEBUG
		return FUNC_ERR_PIN_NUM;
	}

	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/active_low", gpio_port);

	file_descriptor = open(path, O_RDONLY);
	if (file_descriptor == - 1)	{
		#ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function check_active_low_state() ERROR: Can't open file " << path << " for read!" << std::endl;
		#endif // DEBUG
		return FUNC_ERR_OPEN_ACTIVE_LOW_RD;
	}

    read_result = read(file_descriptor, READ_BUFFER, sizeof(READ_BUFFER));
    if (read_result == -1) {
		#ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function check_active_low_state() ERROR: Can't read from file " << path << " !" << std::endl;
		#endif // DEBUG
		close(file_descriptor);
		return FUNC_ERR_RD_FROM_ACTIVE_LOW;
	}

    close(file_descriptor);

    if ((strstr(READ_BUFFER,"1") != 0)) {return PIN_ACTIVE_LOW_ON;}
    if ((strstr(READ_BUFFER,"0") != 0)) { return PIN_ACTIVE_LOW_OFF;}
	else {
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function  check_active_low_state () ERROR: Unknown value in file " << path << " !" << std::endl;
		#endif // DEBUG
		return FUNC_ERR_UNK_ACTIVE_LOW_RET;
	}
}

// Функция задания active_low режима пина GPIO
int set_active_low_state (int pin_number, int active_low_state) {

	int 	gpio_port = 0;
	char 	path[40];
	int     file_descriptor;
	ssize_t	write_result;
	char    WRITE_BUFFER[2];

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	gpio_port = calculate_pin_number(pin_number);
	// Добавить debug и release
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if (gpio_port == -1) {
		#ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function set_active_low_state() ERROR: Incorrect Pin number! Please choose another pin!" << std::endl;
		#endif // DEBUG
		return FUNC_ERR_PIN_NUM;
	}

	if (check_pin_direction(pin_number) == 1) {
		#ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function set_active_low_state() ERROR: Incorrect direction for pin. Set pin direction to OUT first!" << std::endl;
		#endif // DEBUG
		return FUNC_ERR_INC_PIN_DIR;
	}

	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/active_low", gpio_port);

	file_descriptor = open(path, O_WRONLY);
	if (file_descriptor == - 1)	{
		#ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function set_active_low_state() ERROR: Can't open file " << path << " for write!" << std::endl;
		#endif // DEBUG
		return FUNC_ERR_OPEN_ACTIVE_LOW_WR;
	}

	if (active_low_state == PIN_ACTIVE_LOW_ON) {
		snprintf(WRITE_BUFFER, sizeof(WRITE_BUFFER), "%d", 1);
	}
	if (active_low_state == PIN_ACTIVE_LOW_OFF) {
		snprintf(WRITE_BUFFER, sizeof(WRITE_BUFFER), "%d", 0);
	}
	if ((active_low_state != PIN_ACTIVE_LOW_ON) && (active_low_state != PIN_ACTIVE_LOW_OFF)) {
		#ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function set_active_low_state() ERROR: Incorrect value for pin! Use ON for 1 or OFF for 0!" << std::endl;
		#endif // DEBUG
		close(file_descriptor);
		return FUNC_ERR_UNK_ACTIVE_LOW_SENT;
	}

	write_result = write(file_descriptor,WRITE_BUFFER,sizeof(WRITE_BUFFER));
	if (write_result == -1) {
        #ifdef  DEBUG
		std::cout << "SENSUS FS_GPIO LIB - function set_active_low_state() ERROR: Can't write to file " << path << " !" << std::endl;
		#endif // DEBUG
		close(file_descriptor);
		return FUNC_ERR_WR_TO_ACTIVE_LOW;
	}

	close(file_descriptor);
	return FUNCTION_SUCCESS;

}
