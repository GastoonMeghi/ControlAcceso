################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/codigo_personal/codigo_personal.c 

OBJS += \
./src/codigo_personal/codigo_personal.o 

C_DEPS += \
./src/codigo_personal/codigo_personal.d 


# Each subdirectory must supply rules for building sources it contributes
src/codigo_personal/%.o: ../src/codigo_personal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Gaston\proyectos\proyInfo2\ControlAcceso\test\inc\systick" -I"C:\Users\Gaston\proyectos\proyInfo2\ControlAcceso\test\inc\kit_infotronic" -I"C:\Users\Gaston\proyectos\proyInfo2\ControlAcceso\test\inc\expansion3" -I"C:\Users\Gaston\proyectos\proyInfo2\ControlAcceso\test\inc" -I"C:\Users\Gaston\proyectos\proyInfo2\ControlAcceso\test\inc\codigo_personal" -I"C:\Users\Gaston\proyectos\proyInfo2\ControlAcceso\test\inc\GPIO" -I"C:\Users\Gaston\proyectos\proyInfo2\ControlAcceso\test\inc\interrupciones" -I"C:\Users\Gaston\proyectos\proyInfo2\ControlAcceso\test\inc\timers" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


