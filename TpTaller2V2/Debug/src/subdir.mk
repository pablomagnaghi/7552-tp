################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/EjemploBoleteriaTeatro.cpp \
../src/EjemploCompleto.cpp \
../src/EjemploDeCargaBoleteriaTeatro.cpp \
../src/EjemploDeCargaEjemploCompleto.cpp \
../src/main.cpp 

OBJS += \
./src/EjemploBoleteriaTeatro.o \
./src/EjemploCompleto.o \
./src/EjemploDeCargaBoleteriaTeatro.o \
./src/EjemploDeCargaEjemploCompleto.o \
./src/main.o 

CPP_DEPS += \
./src/EjemploBoleteriaTeatro.d \
./src/EjemploCompleto.d \
./src/EjemploDeCargaBoleteriaTeatro.d \
./src/EjemploDeCargaEjemploCompleto.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ `pkg-config --cflags --libs gtkmm-2.4 libxml-2.0` -I/usr/include/gtkmm-2.4 -I/usr/include/cairomm-1.0 -I/usr/include/gdkmm-2.4 -I/usr/include/libxml2 -I/usr/include/giomm-2.4 -I/usr/include/glibmm-2.4 -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


