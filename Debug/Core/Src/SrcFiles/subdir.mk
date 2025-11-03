################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/SrcFiles/FreeRTOS_priority_settings.c \
../Core/Src/SrcFiles/FreeRTOS_project.c 

OBJS += \
./Core/Src/SrcFiles/FreeRTOS_priority_settings.o \
./Core/Src/SrcFiles/FreeRTOS_project.o 

C_DEPS += \
./Core/Src/SrcFiles/FreeRTOS_priority_settings.d \
./Core/Src/SrcFiles/FreeRTOS_project.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/SrcFiles/%.o Core/Src/SrcFiles/%.su Core/Src/SrcFiles/%.cyclo: ../Core/Src/SrcFiles/%.c Core/Src/SrcFiles/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/stm32cubeide workspace/RP/FreeRTOS/config" -I"D:/stm32cubeide workspace/RP/FreeRTOS/include" -I"D:/stm32cubeide workspace/RP/FreeRTOS/portable/GCC/ARM_CM3" -I"D:/stm32cubeide workspace/RP/Core/Inc/IncFiles" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-SrcFiles

clean-Core-2f-Src-2f-SrcFiles:
	-$(RM) ./Core/Src/SrcFiles/FreeRTOS_priority_settings.cyclo ./Core/Src/SrcFiles/FreeRTOS_priority_settings.d ./Core/Src/SrcFiles/FreeRTOS_priority_settings.o ./Core/Src/SrcFiles/FreeRTOS_priority_settings.su ./Core/Src/SrcFiles/FreeRTOS_project.cyclo ./Core/Src/SrcFiles/FreeRTOS_project.d ./Core/Src/SrcFiles/FreeRTOS_project.o ./Core/Src/SrcFiles/FreeRTOS_project.su

.PHONY: clean-Core-2f-Src-2f-SrcFiles

