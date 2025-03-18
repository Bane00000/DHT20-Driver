# DHT20-Driver

## Overview

This repository contains a bare-metal STM32 driver for the DHT20 temperature and humidity sensor. The driver communicates with the sensor over the I2C protocol and provides functions for initialization, reading sensor data, and checking the status word.

## Features

- Supports temperature and humidity readings.

- Uses I2C communication for interfacing.

- Implements status word checking and initialization sequence.

- Compatible with HAL (Hardware Abstraction Layer) drivers for STM32.


## Requirements

- Microcontroller: STM32 (tested on STM32F4xx series)

- DHT20 sensor

- I2C peripheral configured in STM32CubeMX

- STM32 HAL drivers

## Wiring
| DHT20 Pin | STM32 Pin |
|-----------|----------|
| VCC       | 3.3V     |
| GND       | GND      |
| SDA       | (I2Cx_SDA) |
| SCL       | (I2Cx_SCL) |

## Usage
1. Initialize the I2C Peripheral

Configure the I2C interface using STM32CubeMX or manually in your firmware.

2. Include the Driver in Your Project
```
#include "dht20.h"
```

3. Initialize the Sensor

```
DHT20_t sensor;
sensor.i2c_handle = &hi2c1; // Use the correct I2C handle
dht20_init(&sensor);
```

4. Read Temperature and Humidity
```
float temperature, humidity;
dht20_read_sensor(&sensor);
temperature = sensor.temperature;
humidity = sensor.humidity;
printf("Temperature: %.2f°C\n", temperature);
printf("Humidity: %.2f%%\n", humidity);
```

To see an example of using this driver, look at the example.c file.

## Status Handling

The driver checks the status word (0x71) before reading sensor data. If it is not 0x18, it sends an initialization sequence (0x1B, 0x1C, 0x1E) as recommended in the datasheet.

## Datasheet

https://cdn.sparkfun.com/assets/8/a/1/5/0/DHT20.pdf

## Contributing

Feel free to fork, submit issues, or contribute improvements to the driver.

## License

This project is licensed under the MIT License. See LICENSE for details.
