################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/controlador/AsistenteAtributo.cpp \
../src/controlador/AsistenteEntGlobal.cpp \
../src/controlador/AsistenteEntidad.cpp \
../src/controlador/AsistenteIdentificador.cpp \
../src/controlador/AsistenteJerarquia.cpp \
../src/controlador/AsistenteRelacion.cpp \
../src/controlador/ComponentsBuilder.cpp \
../src/controlador/ControladorMenu.cpp \
../src/controlador/ControladorPanelHerramientas.cpp \
../src/controlador/ControladorTreePanel.cpp \
../src/controlador/ControladorVistaDiagramas.cpp 

OBJS += \
./src/controlador/AsistenteAtributo.o \
./src/controlador/AsistenteEntGlobal.o \
./src/controlador/AsistenteEntidad.o \
./src/controlador/AsistenteIdentificador.o \
./src/controlador/AsistenteJerarquia.o \
./src/controlador/AsistenteRelacion.o \
./src/controlador/ComponentsBuilder.o \
./src/controlador/ControladorMenu.o \
./src/controlador/ControladorPanelHerramientas.o \
./src/controlador/ControladorTreePanel.o \
./src/controlador/ControladorVistaDiagramas.o 

CPP_DEPS += \
./src/controlador/AsistenteAtributo.d \
./src/controlador/AsistenteEntGlobal.d \
./src/controlador/AsistenteEntidad.d \
./src/controlador/AsistenteIdentificador.d \
./src/controlador/AsistenteJerarquia.d \
./src/controlador/AsistenteRelacion.d \
./src/controlador/ComponentsBuilder.d \
./src/controlador/ControladorMenu.d \
./src/controlador/ControladorPanelHerramientas.d \
./src/controlador/ControladorTreePanel.d \
./src/controlador/ControladorVistaDiagramas.d 


# Each subdirectory must supply rules for building sources it contributes
src/controlador/%.o: ../src/controlador/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ `pkg-config --cflags --libs gtkmm-2.4 libxml-2.0` -I/usr/include/gtkmm-2.4 -I/usr/include/cairomm-1.0 -I/usr/include/gdkmm-2.4 -I/usr/include/libxml2 -I/usr/include/giomm-2.4 -I/usr/include/glibmm-2.4 -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


