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
	// TODO evaluar si puede tener relaciones

public:

	EntidadGlobal();
	virtual ~EntidadGlobal();

	void setDiagramaAncestro(const std::string diagramaAncestro);
	std::string getDiagramaAncestro() const;

};

#endif /* ENTIDADGLOBAL_H_ */
