/*
 * ConstantesModelo.h
 *
 *  Created on: 26/05/2012
 */

#ifndef CONSTANTESMODELO_H_
#define CONSTANTESMODELO_H_

// Estados de validacion del diagrama
const char* const DIAGRAMA_SIN_VALIDAR = "sin_validar";
const char* const DIAGRAMA_VALIDADO_CON_OBSERVACIONES = "con_observaciones";
const char* const DIAGRAMA_VALIDADO = "validado";

// Tipos de entidad
const char* const TIPO_ENTIDAD_COSA = "cosa";
const char* const TIPO_ENTIDAD_DOMINIO = "dominio";
const char* const TIPO_ENTIDAD_HISTORICA = "historica";
const char* const TIPO_ENTIDAD_PROGRAMADA = "programada";

// Tipos de atributos
const char* const TIPO_ATRIBUTO_CARACTERIZACION = "caracterizacion";
const char* const TIPO_ATRIBUTO_COPIADO = "copiado";
const char* const TIPO_ATRIBUTO_CALCULADO = "calculado";

// Tipos de relaciones
const char* const TIPO_RELACION_ASOCIACION = "asociacion";
const char* const TIPO_RELACION_COMPOSICION = "composicion";

#endif /* CONSTANTESMODELO_H_ */
