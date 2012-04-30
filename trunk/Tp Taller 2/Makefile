
##### Definicion de variables #####

################ SOLO POR CONVENCION ##########################

GTKMMFLAGS:=$(shell pkg-config --cflags --libs gtkmm-2.4)
LIBXMLFLAGS:=$(shell pkg-config --cflags --libs libxml-2.0)
SHELL = /bin/sh
CXXFLAGS = -Wall -pedantic -pedantic-errors -O0 -DNDEBUG -g3 -ggdb $(GTKMMFLAGS) $(LIBXMLFLAGS) 
LD = $(CXX)


###############################################################

##### Directorios archivos fuente #####
SRC :=   ./src

##### ARCHIVOS FUENTE
##### HEADERS
#HEADERS := $(wildcard $(SRC)/*.h)
HEADERS := $(shell find $(SRC) -name "*.h") 

##### SOURCES
#SOURCES := $(wildcard $(SRC)/*.cpp)
SOURCES :=  $(shell find $(SRC) -name "*.cpp")
#SOURCES += test.cpp
DIR_SOURCES := $(sort $(dir $(SOURCES)))
##### Directorios destino
##### Destino archivos objeto
#DEST_OBJS := ./bin/OBJS/
DEST_OBJS := ./bin/

##### Destino ejecutables
#DEST_EX := ./bin
DEST_EX := .

##### Archivos objetos
OBJS :=   $(addprefix $(DEST_OBJS),$(notdir $(patsubst %.cpp,%.o,$(SOURCES))))

##### Targets
EDITOR := editor

##### TARGET DEFAULT
#.DEFAULT_GOAL = maketest
.DEFAULT_GOAL = all

TARGETS = $(EDITOR)

##### FIN DEFINICION VARIABLES #####

##### VERIFICACION VARIABLES #####

ifeq ($(SOURCES),)
$(error 'NO HAY FUENTES')
endif

$(TARGETS) : | folders

##### CREACION DE ARCHIVOS OBJETO

#$(DEST_OBJS)%.o: $(DIR_SOURCES)%.cpp | folders
#	$(CXX) -c $(CXXFLAGS) -o ./$@ ./$<

$(OBJS): $(filter %$(notdir $(patsubst %.o,%,$@)).cpp,$(SOURCES)) | folders
	$(CXX) -c $(CXXFLAGS) $(filter %/$(notdir $(patsubst %.o,%,$@)).cpp,$(SOURCES)) -o ./$@
#	#@echo "SUBST=$(patsubst %.o,%.cpp,$@)"
#	#@echo "NOTDIR=$(notdir $(patsubst %.o,%,$@))"
#	#@echo "SOURCES=$(SOURCES)"
#	#@echo "FILTER= $(filter %$(notdir $(patsubst %.o,%,$@)).cpp,$(SOURCES))"


##### CREACION DE EJECUTABLES

$(EDITOR)  : $(OBJS) | folders	
	$(CXX) $(CXXFLAGS)  $(OBJS) -o $(DEST_EX)/$@

MIVAR:= cualquierporonga ./laconchadelalora/test.cpp otra verga
test:
	@echo "SOURCES=$(SOURCES)"
	@echo
	@echo "DIR_SOURCES=$(DIR_SOURCES)"
	@echo
	@echo "OBJS=$(OBJS)"
	@echo
	@echo "HEADERS=$(HEADERS)"
	@echo
	@echo "DEST_OBJS=$(DEST_OBJS)"
	@echo
	@echo "SUBST=$(patsubst %.o,%.cpp,$@)"
	@echo
	@echo "NOTDIR=$(notdir $(patsubst %.o,%,$@))"
	@echo
	@echo "MIVAR=$(MIVAR)"
	@echo
	@echo "FILTER=$(filter %Proyecto.cpp,$(SOURCES))"

.PHONY : all clean folders

all :  $(TARGETS) 

# CREACION DE CARPETAS DESTINO
folders:
	@mkdir -p ./bin
	@mkdir -p $(DEST_OBJS)
	@#mkdir -p $(DEST_OBJS_CLIENTE)
	@#mkdir -p $(DEST_OBJS_GESTOR)

clean:
	@$(RM) $(DEST_OBJS)*.o
#	#$(RM) $(DEST_EX)/$(TARGET)
#	#$(RM) $(DEST_OBJS_GESTOR)/*
#	$(RM) # $(addprefix $(DEST_EX)/,$(TARGETS))

