################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DHT20/Src/dht20.c 

OBJS += \
./Drivers/DHT20/Src/dht20.o 

C_DEPS += \
./Drivers/DHT20/Src/dht20.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DHT20/Src/%.o Drivers/DHT20/Src/%.su Drivers/DHT20/Src/%.cyclo: ../Drivers/DHT20/Src/%.c Drivers/DHT20/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Bane/Documents/Embedded Programming/Project_01/DHT20_Driver/Drivers/GPIO/Inc" -I"C:/Users/Bane/Documents/Embedded Programming/Project_01/DHT20_Driver/Drivers/DHT20/Inc" -I"C:/Users/Bane/Documents/Embedded Programming/Project_01/DHT20_Driver/Drivers/I2C/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-DHT20-2f-Src

clean-Drivers-2f-DHT20-2f-Src:
	-$(RM) ./Drivers/DHT20/Src/dht20.cyclo ./Drivers/DHT20/Src/dht20.d ./Drivers/DHT20/Src/dht20.o ./Drivers/DHT20/Src/dht20.su

.PHONY: clean-Drivers-2f-DHT20-2f-Src

