# name of your application
APPLICATION = adc

# If no BOARD is found in the environment, use this default:
BOARD ?= esp32-wroom-32

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

# Use a peripheral timer for the delay, if available
# FEATURES_OPTIONAL += periph_timer

# USEMODULE += gpio 

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
