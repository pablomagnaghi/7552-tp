/*
 * EntidadGlobal.h
 *
 *  Created on: 14/05/2012
 */

#ifndef ENTIDADGLOBAL_H_
#define ENTIDADGLOBAL_H_

#include <string>
#include "Componente.h"

class EntidadGlobal : public Componente {

private:

	std::string diagramaAncestro;

public:

	EntidadGlobal();
	virtual ~EntidadGlobal();

	void setDiagrama(std::string diagramaAncestro);
	std::string getDiagramaAncestro();

};

#endif /* ENTIDADGLOBAL_H_ */
