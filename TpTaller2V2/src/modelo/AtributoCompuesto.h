#ifndef ATRIBUTOCOMPUESTO_H_
#define ATRIBUTOCOMPUESTO_H_

#include "Atributo.h"

class AtributoCompuesto : public Atributo{
private:
	std::vector<Atributo*> atributosDerivables;
	void borrarAtributosDerivables();
public:
	AtributoCompuesto();
	virtual ~AtributoCompuesto();

	void agregarAtributoDerivable(Atributo*);
	void quitarAtributoDerivable(Atributo*);

	std::vector<Atributo*>::iterator atributosDerivablesBegin();
	std::vector<Atributo*>::iterator atributosDerivablesEnd();
};

#endif /* ATRIBUTOCOMPUESTO_H_ */
