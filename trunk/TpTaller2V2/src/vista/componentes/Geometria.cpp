/* Geometria.cpp
 *  Created on: 30/05/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Geometria.h"

Geometria::Geometria() {
	// TODO Auto-generated constructor stub

}

Geometria::~Geometria() {
	// TODO Auto-generated destructor stub
}

bool Geometria::estaContenidoEnRectangulo(double x, double y, double x_inicial,
		double y_inicial, double x_final, double y_final) {
	if (x >= x_inicial && x <= x_final) {
		if (y >= y_inicial && y <= y_final) {
			return true;
		}
	}
	return false;
}
