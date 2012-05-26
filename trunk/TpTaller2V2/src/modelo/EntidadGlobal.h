/*
 * EntidadGlobal.h
 *
 *  Created on: 14/05/2012
 */

#ifndef ENTIDADGLOBAL_H_
#define ENTIDADGLOBAL_H_

#include <string>
#include "Entidad.h"

class EntidadGlobal : public Entidad {

private:

	std::string diagramaAncestro;

public:

	EntidadGlobal();
	virtual ~EntidadGlobal();

	void setDiagramaAncestro(const std::string);
	std::string getDiagramaAncestro() const;

};

#endif /* ENTIDADGLOBAL_H_ */
