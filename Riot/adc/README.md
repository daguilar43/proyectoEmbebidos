ADC
===


Instrucciones de construcción
=============================

Acivar variables de entorno:

```bash
. environment.bash
```

Construir, flashear y monitorear:

```bash
    make b f t
```
Revisión de la documentación para modificaciones
================================================

https://doc.riot-os.org/group__drivers__periph__adc.html

ADC_NUMOF



/home/johnny/gitPackages/RIOT/boards/esp32-wroom-32/include/periph_conf.h
```bash
// ADC_GPIOS wroover
#define ADC_GPIOS   { GPIO0 , GPIO2 , GPIO4 , GPIO12, GPIO13, GPIO14, \
                      GPIO15, GPIO25, GPIO26, GPIO27, GPIO32, GPIO33, \
                      GPIO34, GPIO35, GPIO36, GPIO39 }
```

ADC_LINE(x)
Donde x es la posición que ocupa el pin en el arreglo de ADC_GPIOS

```bash
#define ADC_GPIOS {GPIO0, ..., GPIO39}
GPIO0 -> 0
GPIO2
GPIO4
GPIO12
GPIO13
GPIO14
GPIO15
GPIO25 -> 7
GPIO26
GPIO27
GPIO32
GPIO33
GPIO34
GPIO35
GPIO36
GPIO39 -> 15
```

/home/johnny/gitPackages/RIOT/boards/common/esp32/include/periph_conf_common.h
