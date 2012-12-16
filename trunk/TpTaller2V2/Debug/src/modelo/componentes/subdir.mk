################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/modelo/componentes/Atributo.cpp \
../src/modelo/componentes/Componente.cpp \
../src/modelo/componentes/Entidad.cpp \
../src/modelo/componentes/EntidadGlobal.cpp \
../src/modelo/componentes/EntidadNueva.cpp \
../src/modelo/componentes/Identificador.cpp \
../src/modelo/componentes/Jerarquia.cpp \
../src/modelo/componentes/Relacion.cpp \
../src/modelo/componentes/UnionEntidadRelacion.cpp 

OBJS += \
./src/modelo/componentes/Atributo.o \
./src/modelo/componentes/Componente.o \
./src/modelo/componentes/Entidad.o \
./src/modelo/componentes/EntidadGlobal.o \
./src/modelo/componentes/EntidadNueva.o \
./src/modelo/componentes/Identificador.o \
./src/modelo/componentes/Jerarquia.o \
./src/modelo/componentes/Relacion.o \
./src/modelo/componentes/UnionEntidadRelacion.o 

CPP_DEPS += \
./src/modelo/componentes/Atributo.d \
./src/modelo/componentes/Componente.d \
./src/modelo/componentes/Entidad.d \
./src/modelo/componentes/EntidadGlobal.d \
./src/modelo/componentes/EntidadNueva.d \
./src/modelo/componentes/Identificador.d \
./src/modelo/componentes/Jerarquia.d \
./src/modelo/componentes/Relacion.d \
./src/modelo/componentes/UnionEntidadRelacion.d 


# Each subdirectory must supply rules for building sources it contributes
src/modelo/componentes/%.o: ../src/modelo/componentes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ `pkg-config --cflags --libs gtkmm-2.4 libxml-2.0` -I/usr/include/gtkmm-2.4 -I/usr/include/cairomm-1.0 -I/usr/include/gdkmm-2.4 -I/usr/include/libxml2 -I/usr/include/giomm-2.4 -I/usr/include/glibmm-2.4 -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


