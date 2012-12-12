#ifndef INTERFAZREMOVERATRIBUTO_H_
#define INTERFAZREMOVERATRIBUTO_H_

#include "VistaComponente.h"
#include "VistaAtributo.h"

class VistaAtributo;

class InterfazRemoverAtributo {
public:
	 virtual bool quitarAtributo(VistaAtributo * vistaAtributo) = 0;
	 InterfazRemoverAtributo(){}
	 virtual ~InterfazRemoverAtributo(){}
};


#endif /* INTERFAZREMOVERATRIBUTO_H_ */
