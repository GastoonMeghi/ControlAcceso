################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FW_InitOscilador.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/nb_LCD_prueba.c 

OBJS += \
./src/FW_InitOscilador.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/nb_LCD_prueba.o 

C_DEPS += \
./src/FW_InitOscilador.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/nb_LCD_prueba.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Gaston\proyectos\proyInfo2\ControlAcceso\nb_LCD_prueba\inc\GPIO" -I"C:\Users\Gaston\proyectos\proyInfo2\ControlAcceso\nb_LCD_prueba\inc\interrupciones" -I"C:\Users\Gaston\proyectos\proyInfo2\ControlAcceso\nb_LCD_prueba\inc\kit_infotronic" -I"C:\Users\Gaston\proyectos\proyInfo2\ControlAcceso\nb_LCD_prueba\inc\LCD" -I"C:\Users\Gaston\proyectos\proyInfo2\ControlAcceso\nb_LCD_prueba\inc\systick" -I"C:\Users\Gaston\proyectos\proyInfo2\ControlAcceso\nb_LCD_prueba\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


