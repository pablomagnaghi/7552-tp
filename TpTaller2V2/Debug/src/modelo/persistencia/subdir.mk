################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/modelo/persistencia/Xml.cpp \
../src/modelo/persistencia/XmlNodeSet.cpp \
../src/modelo/persistencia/XmlNodo.cpp 

OBJS += \
./src/modelo/persistencia/Xml.o \
./src/modelo/persistencia/XmlNodeSet.o \
./src/modelo/persistencia/XmlNodo.o 

CPP_DEPS += \
./src/modelo/persistencia/Xml.d \
./src/modelo/persistencia/XmlNodeSet.d \
./src/modelo/persistencia/XmlNodo.d 


# Each subdirectory must supply rules for building sources it contributes
src/modelo/persistencia/%.o: ../src/modelo/persistencia/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ `pkg-config --cflags --libs gtkmm-2.4 libxml-2.0` -I/usr/include/gtkmm-2.4 -I/usr/include/cairomm-1.0 -I/usr/include/gdkmm-2.4 -I/usr/include/libxml2 -I/usr/include/giomm-2.4 -I/usr/include/glibmm-2.4 -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


