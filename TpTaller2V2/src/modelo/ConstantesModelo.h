/*
 * ConstantesModelo.h
 *
 *  Created on: 26/05/2012
 */

#ifndef CONSTANTESMODELO_H_
#define CONSTANTESMODELO_H_

// Estados de validacion del diagrama
const char* const DIAGRAMA_SIN_VALIDAR = "sin_validar";
const char* const DIAGRAMA_VALIDADO_CON_OBSERVACIONES = "validado_con_observaciones";
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

// Tipos de jerarquias
const char* const TIPO_COBERTURA_TOTAL = "total";
const char* const TIPO_COBERTURA_PARCIAL = "parcial";
const char* const TIPO_INTERSECCION_EXCLUSIVA = "exclusiva";
const char* const TIPO_INTERSECCION_SUPERPUESTA = "superpuesta";

// Cardinalidad
const char* const CARDINALIDAD_MINIMA = "1";

#endif /* CONSTANTESMODELO_H_ */
