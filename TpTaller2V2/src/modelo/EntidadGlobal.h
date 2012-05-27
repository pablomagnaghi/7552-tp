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
	int codigoEntidadNueva; // Codigo de la EntidadNueva en el diagrama ancestro.

public:

	EntidadGlobal();
	virtual ~EntidadGlobal();

	void setDiagramaAncestro(const std::string);
	std::string getDiagramaAncestro() const;

	void setCodigoEntidadNueva(int);
	int getCodigoEntidadNueva() const;

};

#endif /* ENTIDADGLOBAL_H_ */
