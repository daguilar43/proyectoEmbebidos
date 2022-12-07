# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..
# name of your application
APPLICATION = sd1306

# If no BOARD is found in the environment, use this default:
BOARD ?= esp32-wroom-32

# include $(RIOTBASE)/tests/Makefile.tests_common


USEPKG += u8g2

USEMODULE += periph_i2c

FEATURES_REQUIRED = periph_adc
USEMODULE += ztimer_msec



# set default device parameters in case they are undefined
TEST_OUTPUT ?= 4

INDEX_DRIVER_HW_I2C ?= 0

TEST_ADDR ?= 0x3c

TEST_PIN_CS ?= GPIO_UNDEF # Para el ejemplo está sin uso
TEST_PIN_DC ?= GPIO_UNDEF # Para el ejemplo está sin uso
TEST_PIN_RESET ?= GPIO_UNDEF # Para el ejemplo está sin uso

SETUP_DISPLAY ?= u8g2_Setup_ssd1306_i2c_128x64_noname_1

FEATURES_REQUIRED += periph_gpio periph_i2c

# export parameters
CFLAGS += -DTEST_OUTPUT=$(TEST_OUTPUT)

CFLAGS += -DINDEX_DRIVER_HW_I2C=$(INDEX_DRIVER_HW_I2C)

CFLAGS += -DTEST_ADDR=$(TEST_ADDR)

CFLAGS += -DTEST_PIN_CS=$(TEST_PIN_CS)
CFLAGS += -DTEST_PIN_DC=$(TEST_PIN_DC)
CFLAGS += -DTEST_PIN_RESET=$(TEST_PIN_RESET)

CFLAGS += -DSETUP_DISPLAY=$(SETUP_DISPLAY)

SERIALMONITOR?=picocom
SERIALMONITOR_GUI ?=gtkterm
SERIAL ?=/dev/ttyUSB0
BAUD ?=115200
OPT_IMAP=lfcrlf

c: clean
f: flash
gt:gtkterm
b: all
t:terminal

gtkterm:
	$(SERIALMONITOR_GUI) --port $(SERIAL) --speed $(BAUD) || \
		(printf "No tiene instalado el monitor serial picocom, puede instalarlo como sigue:\nsudo apt install gtkterm")

terminal:
	$(SERIALMONITOR) $(SERIAL) -b $(BAUD) --imap $(OPT_IMAP) || \
		(printf "No tiene instalado el monitor serial picocom, puede instalarlo como sigue:\nsudo apt install picocom")

compile_json:
	bear -- make b

include $(RIOTBASE)/Makefile.include
