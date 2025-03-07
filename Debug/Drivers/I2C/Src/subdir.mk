################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/I2C/Src/i2c_stm32f4xx.c 

OBJS += \
./Drivers/I2C/Src/i2c_stm32f4xx.o 

C_DEPS += \
./Drivers/I2C/Src/i2c_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/I2C/Src/%.o Drivers/I2C/Src/%.su Drivers/I2C/Src/%.cyclo: ../Drivers/I2C/Src/%.c Drivers/I2C/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Bane/Documents/Embedded Programming/Project_01/DHT20_Driver/Drivers/GPIO/Inc" -I"C:/Users/Bane/Documents/Embedded Programming/Project_01/DHT20_Driver/Drivers/DHT20/Inc" -I"C:/Users/Bane/Documents/Embedded Programming/Project_01/DHT20_Driver/Drivers/I2C/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-I2C-2f-Src

clean-Drivers-2f-I2C-2f-Src:
	-$(RM) ./Drivers/I2C/Src/i2c_stm32f4xx.cyclo ./Drivers/I2C/Src/i2c_stm32f4xx.d ./Drivers/I2C/Src/i2c_stm32f4xx.o ./Drivers/I2C/Src/i2c_stm32f4xx.su

.PHONY: clean-Drivers-2f-I2C-2f-Src

