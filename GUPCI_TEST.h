#pragma once
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include "DEFINITIONS.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//tipos.
typedef		int			in;
typedef		double		dou;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//umbral de referencia de control.
dou	reference_threshold						= 0.05;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//argumentos: parámetros de gupci.
in	gupci_nat_test							= N_A;											//naturaleza de la unidad ('a','b','c'...'z').	
in	upci_amount_test						= 1;											//cantidad de upci por grupo.	
in	set_signal_flag_test					= OFF;											//bandera de almacenamiento de señales.

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//argumentos: parámetros de upci.
in  inis_amount_allowed_test				= 1024;											//cantidad de estructuras INIS permitidas.
in  acis_amount_allowed_test				= 0;											//cantidad de estructuras ACIS permitidas.
in  rlis_amount_allowed_test				= 1024;											//cantidad de estructuras de relación permitidas.
in  default_activity_level_test				= 6;											//nivel de actividad por defecto.
in  max_activity_level_allowed_test			= 10;											//nivel de actividad máximo permitido.
in  min_activity_level_allowed_test			= 5;											//nivel de actividad mínimo permitido.
dou kernel_raw_input_threshold_test			= 10000;										//umbral de entrada cruda para control del núcleo.
dou dif_raw_input_threshold_test			= 0.2;											//umbral de entrada cruda para focalización de la atención (%).
dou str_congruence_threshold_test		= 0.2;											//umbral de congruencia para estructuras candidatas (%).	
dou pfrlis_strength_threshold_test			= 3;											//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
dou indfrlis_strength_threshold_test		= 2;											//umbral de fortaleza de relación INDFRLIS para eliminar relación por N.A.
dou	evaluation_threshold_test				= 0.02;											//umbral para evaluaciones.	
dou transition_evaluation_threshold_test	= 0.02;											//umbral para transición de evaluaciones.
in  timeout_clean_is_test					= -1;											//tiempo de espera de limpieza de IS.
in  timeout_update_al_is_test				= 100;											//tiempo de espera para actualizar niveles de actividad en IS (ms).

