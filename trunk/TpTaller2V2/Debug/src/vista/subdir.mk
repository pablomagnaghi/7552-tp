################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/vista/Ide.cpp \
../src/vista/ImpresionDiagrama.cpp \
../src/vista/TreePanel.cpp \
../src/vista/VistaDiagrama.cpp \
../src/vista/VistaProyecto.cpp 

OBJS += \
./src/vista/Ide.o \
./src/vista/ImpresionDiagrama.o \
./src/vista/TreePanel.o \
./src/vista/VistaDiagrama.o \
./src/vista/VistaProyecto.o 

CPP_DEPS += \
./src/vista/Ide.d \
./src/vista/ImpresionDiagrama.d \
./src/vista/TreePanel.d \
./src/vista/VistaDiagrama.d \
./src/vista/VistaProyecto.d 


# Each subdirectory must supply rules for building sources it contributes
src/vista/%.o: ../src/vista/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ `pkg-config --cflags --libs gtkmm-2.4 libxml-2.0` -I/usr/include/gtkmm-2.4 -I/usr/include/cairomm-1.0 -I/usr/include/gdkmm-2.4 -I/usr/include/libxml2 -I/usr/include/giomm-2.4 -I/usr/include/glibmm-2.4 -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


