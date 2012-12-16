################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/vista/componentes/Geometria.cpp \
../src/vista/componentes/VistaAtributo.cpp \
../src/vista/componentes/VistaComponente.cpp \
../src/vista/componentes/VistaEntidad.cpp \
../src/vista/componentes/VistaEntidadGlobal.cpp \
../src/vista/componentes/VistaEntidadNueva.cpp \
../src/vista/componentes/VistaIdentificador.cpp \
../src/vista/componentes/VistaJerarquia.cpp \
../src/vista/componentes/VistaLinea.cpp \
../src/vista/componentes/VistaRelacion.cpp \
../src/vista/componentes/VistaUnionEntidadRelacion.cpp 

OBJS += \
./src/vista/componentes/Geometria.o \
./src/vista/componentes/VistaAtributo.o \
./src/vista/componentes/VistaComponente.o \
./src/vista/componentes/VistaEntidad.o \
./src/vista/componentes/VistaEntidadGlobal.o \
./src/vista/componentes/VistaEntidadNueva.o \
./src/vista/componentes/VistaIdentificador.o \
./src/vista/componentes/VistaJerarquia.o \
./src/vista/componentes/VistaLinea.o \
./src/vista/componentes/VistaRelacion.o \
./src/vista/componentes/VistaUnionEntidadRelacion.o 

CPP_DEPS += \
./src/vista/componentes/Geometria.d \
./src/vista/componentes/VistaAtributo.d \
./src/vista/componentes/VistaComponente.d \
./src/vista/componentes/VistaEntidad.d \
./src/vista/componentes/VistaEntidadGlobal.d \
./src/vista/componentes/VistaEntidadNueva.d \
./src/vista/componentes/VistaIdentificador.d \
./src/vista/componentes/VistaJerarquia.d \
./src/vista/componentes/VistaLinea.d \
./src/vista/componentes/VistaRelacion.d \
./src/vista/componentes/VistaUnionEntidadRelacion.d 


# Each subdirectory must supply rules for building sources it contributes
src/vista/componentes/%.o: ../src/vista/componentes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ `pkg-config --cflags --libs gtkmm-2.4 libxml-2.0` -I/usr/include/gtkmm-2.4 -I/usr/include/cairomm-1.0 -I/usr/include/gdkmm-2.4 -I/usr/include/libxml2 -I/usr/include/giomm-2.4 -I/usr/include/glibmm-2.4 -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


