#include <stdio.h>
#include <gpiod.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

struct gpiod_chip* openGPIOChip(char *gpio) {
	struct gpiod_chip *chip = gpiod_chip_open(gpio);
	if (!chip) {
		fprintf(stderr, "falha ao abrir gpiochip[%s]  [%s]\n", gpio,
				strerror(errno));
		exit(EXIT_FAILURE);
	}
	return chip;
}

struct gpiod_line* openLine(struct gpiod_chip *chip, int lineNumber) {
	struct gpiod_line *line = gpiod_chip_get_line(chip, lineNumber);
	if (!line) {
		gpiod_chip_close(chip);
		fprintf(stderr, "falha ao obter gpiochip[?] linha [%d]  [%s]\n",
				lineNumber, strerror(errno));
		exit(EXIT_FAILURE);
	}
	return line;
}

void configOutput(struct gpiod_line *line) {
	int ret = gpiod_line_request_output(line, "gpio", 0);
	if (ret == -1) {
		fprintf(stderr, "falha no configOutput line[?] [%s]\n",
				strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void setValue(struct gpiod_line *line, int value) {
	int ret = gpiod_line_set_value(line, value);
	if (ret == -1) {
		fprintf(stderr, "falha no setValue line[?] value[%d]  [%s]\n", value,
				strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void teste() {
	struct gpiod_chip *chip1 = openGPIOChip("/dev/gpiochip1");
	struct gpiod_chip *chip3 = openGPIOChip("/dev/gpiochip3");

	struct gpiod_line *led1 = openLine(chip1, 12);
	configOutput(led1);
	struct gpiod_line *led2 = openLine(chip3, 20);
	configOutput(led2);
	struct gpiod_line *led3 = openLine(chip3, 17);
	configOutput(led3);
	struct gpiod_line *led4 = openLine(chip3, 16);
	configOutput(led4);
	struct gpiod_line *led5 = openLine(chip3, 19);
	configOutput(led5);

	struct gpiod_line *usb = openLine(chip3, 21);
	configOutput(usb);
	setValue(usb, 1);

	while (true) {
		setValue(led1, 1);
		setValue(led2, 0);
		setValue(led3, 1);
		setValue(led4, 0);
		setValue(led5, 1);
		printf("LED on\r\n");
		sleep(1);
		setValue(led1, 0);
		setValue(led2, 1);
		setValue(led3, 0);
		setValue(led4, 1);
		setValue(led5, 0);
		printf("LED off\r\n");
		sleep(1);
	}

	gpiod_line_release(led1);
	gpiod_line_release(led2);
	gpiod_line_release(led3);
	gpiod_line_release(led4);
	gpiod_line_release(led5);
	gpiod_chip_close(chip1);
	gpiod_chip_close(chip3);
}

int main() {

	teste();
}
