/*
 * GeneradorCodigo.h
 *
 *  Created on: 26/05/2012
 */

#ifndef GENERADORCODIGO_H_
#define GENERADORCODIGO_H_

#include <stddef.h>

class GeneradorCodigo {

private:

	GeneradorCodigo();
	static GeneradorCodigo* instance;
	int codigo;

public:

	static GeneradorCodigo* getInstance();
	static void destruir();
	void setCodigo(int);
	int getCodigo() const;
	int getSiguienteCodigo();
	static int siguienteCodigo();

};

#endif /* GENERADORCODIGO_H_ */
