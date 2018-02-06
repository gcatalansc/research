//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
	Nombre Clase : 	  UPCI_SDS (Unidad de procesos cognitivos integradora tipo 'SDS'). 
	Date	    :	  12:58 pm 12-06-2017.
	Diseñador    :	  Jesús
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include "UPCI_SDS.h"

//-------------------------------------------------------------------------------------  
//-------------------------------------------------------------------------------------
//espacio de nombres.
using namespace UPC;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método constructor 1.
UPCI_SDS::UPCI_SDS()
{

}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método constructor 2 para cargar desde interfaz.
UPCI_SDS::UPCI_SDS(in _upci_id, in _storage_flag, UPCI_SDS_ARG &_upci_arg)
{	
	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## PARÁMETROS ################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los parámetros estructurales.
	this->GUPCI_ID									=	_upci_arg.gupci_id;									//puntero a id de la gupci.
	this->UPCI_ID									=	_upci_id;											//id de la upci.
	this->INIS_AMOUNT_ALLOWED						=	_upci_arg.inis_amount_allowed;						//cantidad de estructuras INIS permitidas.
	this->RLIS_AMOUNT_ALLOWED						=	_upci_arg.rlis_amount_allowed;						//cantidad de estructuras de relaciones permitidas por tipo.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//parámetros de actividad.
	this->DEFAULT_ACTIVITY_LEVEL					=	_upci_arg.default_activity_level;					//nivel de actividad por defecto.
	this->MAX_ACTIVITY_LEVEL_ALLOWED				=	_upci_arg.max_activity_level_allowed;				//nivel de actividad máximo permitido.
	this->MIN_ACTIVITY_LEVEL_ALLOWED				=	_upci_arg.min_activity_level_allowed;				//nivel de actividad mínimo permitido.

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//incialización de umbrales.
	this->DIF_RAW_INPUT_THRESHOLD					=	_upci_arg.dif_raw_input_threshold;					//umbral de entrada cruda para focalización de la atención (%).
	this->STR_CONGRUENCE_THRESHOLD					=	_upci_arg.str_congruence_threshold;					//umbral de congruencia para estructuras candidatas (%).	
	this->PFRLIS_STRENGTH_THRESHOLD					=	_upci_arg.pfrlis_strength_threshold;				//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
	this->INDFRLIS_STRENGTH_THRESHOLD				=	_upci_arg.indfrlis_strength_threshold;				//umbral de fortaleza de relación INDFRLIS para eliminar relación por N.A.
	this->TRANSITION_EVALUATION_THRESHOLD			=	_upci_arg.transition_evaluation_threshold;			//umbral para transición de evaluaciones.	

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## BANDERAS ##################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de bandera del estado del almacenamiento de la unidad (ON: salvar, OFF: no-salvar).
	this->STORAGE_FLAG								=	_storage_flag;									

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de la bandera del estado de integración del kernel (ON: integrando, OFF: libre).
	this->KERNEL_INTEGRATION_FLAG					=	OFF;												
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de las banderas del integrador de Hilos.
	this->THREAD_INTEGRATION_FLAG					=	OFF;												//bandera del estado de integración del Hilo (ON: integrando, OFF: libre).
	this->THREAD_INTEGRATION_LATENCY_FLAG			=	OFF;												//bandera del estado de latencia de la integración del Hilo.
	this->THREAD_INTEGRATION_FINISHED_FLAG			=	ON;													//bandera de aviso del término de la integración del Hilo.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de las banderas para estructuras creadas
	this->NEW_INPUT_FLAG							=	OFF;												//bandera de alerta de una nueva entrada.
	this->NEW_INPUT_DIFFERENCE_RELATION_FLAG		=	OFF;												//bandera de alerta de la creación de una nueva relación de diferencia de entradas.
	
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//inicialización de banderas para estructuras que superen umbral de congruencia.
	this->INIS_CONGRUENCE_ACCOMPLISHED				=	OFF;												//bandera para estructuras INIS que superen umbral de congruencia.
	this->INDFRLIS_CONGRUENCE_ACCOMPLISHED			=	OFF;												//bandera para estructuras INDFRLIS que superen umbral de congruencia.
	this->INPRRLIS_CONGRUENCE_ACCOMPLISHED			=	OFF;												//bandera para estructuras INPRRLIS que superen umbral de congruencia.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de banderas para threads activos.
	this->CLOSE_ACTIVE_THREADS_FLAG					=	_upci_arg.close_active_threads_flag;				//bandera para cerrar threads activos.
	this->PAUSE_ACTIVE_THREADS_FLAG					=	_upci_arg.pause_active_threads_flag;				//bandera para pausar threads activos.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de bandera para imprimir en pantalla.
	this->PRINT_FLAG								=	OFF;												
	
	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################### TIEMPOS ##################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de tiempos para threads de limpieza y actualización.
	this->TIMEOUT_CLEAN_IS							=	_upci_arg.timeout_clean_is;							//tiempo de espera de limpieza de IS.
	this->TIMEOUT_UPDATE_AL_IS						=	_upci_arg.timeout_update_al_is;						//tiempo de espera para actualizar niveles de actividad en IS (ms).

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################### BUFFERS ##################################### 
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de puntero a buffer del grupo de upci.	
	this->BUFF_UPCI									=	(deque<UPCI_SDS>*)_upci_arg.buff_upci;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------  
	//seteo de puntero a buffer para el id de la upci que puede almacenar estructuras.
	this->BUFF_UPCI_ID_STORAGE_FLAG_ACT				=	_upci_arg.buff_upci_id_storage_flag_act;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para las IS.
	this->BUFF_INIS									=	new INIS_SD[this->INIS_AMOUNT_ALLOWED];				//buffer de estructuras de entrada.
	this->BUFF_SRLIS								=	new SRLIS[this->RLIS_AMOUNT_ALLOWED];				//buffer de estructuras de relación simple.
	this->BUFF_PFRLIS								=	new PFRLIS[this->RLIS_AMOUNT_ALLOWED];				//buffer de estructuras de relación de flujo puro.
	this->BUFF_INDFRLIS								=	new INDFRLIS_SD[this->RLIS_AMOUNT_ALLOWED];			//buffer de estructuras de relación de flujo diferencial de entradas.
	this->BUFF_INPRRLIS								=	new INPRRLIS_SD[this->RLIS_AMOUNT_ALLOWED];			//buffer de estructuras de relación de flujo proporcional de entradas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para registros.
	this->BUFF_IN_RG								=	_upci_arg.buff_in_rg;								//puntero a buffer para registro de entrada.
	this->BUFF_EV_RG								=	_upci_arg.buff_ev_rg;								//puntero a buffer para registro de evaluación de entrada.
	this->BUFF_IN_DIF_RG							=	_upci_arg.buff_in_dif_rg;							//puntero a buffer para registro de diferencia de entradas.
	this->BUFF_IN_PRO_RG							=	_upci_arg.buff_in_pro_rg;							//puntero a buffer para registro de proporción de diferencia de entradas.
	this->BUFF_OUTPUT_PROJECTION					=	_upci_arg.buff_output_projection;					//puntero a buffer para registro de proyección de salida.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura INIS con evaluación máxima.
	this->BUFF_INIS_MAX_EVAL						=	_upci_arg.buff_inis_max_eval;						//puntero a buffer para la estructura INIS con máxima evaluación.
	this->BUFF_MAX_EVALUATION						=	_upci_arg.buff_max_evaluation;						//puntero a buffer para la máxima evaluación.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura INIS con nivel de actividad máximo.
	this->BUFF_INIS_MAX_AL							=	_upci_arg.buff_inis_max_al;							//puntero a buffer para la estructura INIS con nivel de actividad máximo.
	this->BUFF_MAX_ACTIVITY_LEVEL					=	_upci_arg.buff_max_activity_level;					//puntero a buffer para el máximo nivel de actividad.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura con fortaleza de la relación máximo.
	this->BUFF_STR_MAX_RS							=	_upci_arg.buff_str_max_rs;							//puntero a buffer para la estructura con fortaleza de la relación máximo.
	this->BUFF_MAX_RELATION_STRENGTH				=	_upci_arg.buff_max_relation_strength;				//puntero a buffer para el máximo fortaleza de la relación.	

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de puntero a buffer para las estructuras proyectadas de salida.
	this->BUFF_OUTPUT_PROJECTION					=	_upci_arg.buff_output_projection;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para los id de las estructuras disponibles.
	this->BUFF_INIS_ID_AV[0]						=	0;													//buffer del id de INIS disponible actual.
	this->BUFF_INIS_ID_AV[1]						=	-1;													//buffer del id de INIS disponible anterior.
	this->BUFF_SRLIS_ID_AV[0]						=	0;													//buffer del id de SRLIS disponible actual.
	this->BUFF_SRLIS_ID_AV[1]						=	-1;													//buffer del id de SRLIS disponible anterior.
	this->BUFF_PFRLIS_ID_AV[0]						=	0;													//buffer del id de PFRLIS disponible actual.
	this->BUFF_PFRLIS_ID_AV[1]						=	-1;													//buffer del id de PFRLIS disponible anterior.
	this->BUFF_INDFRLIS_ID_AV[0]					=	0;													//buffer del id de INDFRLIS disponible actual.
	this->BUFF_INDFRLIS_ID_AV[1]					=	-1;													//buffer del id de INDFRLIS disponible anterior.
	this->BUFF_INPRRLIS_ID_AV[0]					=	0;													//buffer del id de INPRRLIS disponible actual.
	this->BUFF_INPRRLIS_ID_AV[1]					=	-1;													//buffer del id de INPRRLIS disponible anterior.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo a punteros a buffers para los ids de las estructuras creadas.
	this->BUFF_INIS_CRE								=	_upci_arg.buff_inis_cre;							//puntero a buffer para id de INIS creada.
	this->BUFF_SRLIS_CRE							=	_upci_arg.buff_srlis_cre;							//puntero a buffer para id de SRLIS creada.
	this->BUFF_PFRLIS_CRE							=	_upci_arg.buff_pfrlis_cre;							//puntero a buffer para id de PFRLIS creada.
	this->BUFF_INDFRLIS_CRE							=	_upci_arg.buff_indfrlis_cre;						//puntero a buffer para id de INDFRLIS creada.
	this->BUFF_INPRRLIS_CRE							=	_upci_arg.buff_inprrlis_cre;						//puntero a buffer para id de INPRRLIS creada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de puntero a buffer para las estructuras INIS activadas.
	this->BUFF_INIS_ACTIVATED						=	_upci_arg.buff_inis_activated;						

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para las estructuras en estado de suspensión.		
	this->BUFF_INIS_SUS								=	_upci_arg.buff_inis_sus;							//puntero a buffer para las estructuras INIS suspendidas.
	this->BUFF_SRLIS_SUS							=	_upci_arg.buff_srlis_sus;							//puntero a buffer para las estructuras SRLIS suspendidas.
	this->BUFF_PFRLIS_SUS							=	_upci_arg.buff_pfrlis_sus;							//puntero a buffer para las estructuras PFRLIS suspendidas.
	this->BUFF_INDFRLIS_SUS							=	_upci_arg.buff_indfrlis_sus;						//puntero a buffer para las estructuras INDFRLIS suspendidas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para los id de las upci candidatas. 
	//[a][b]: a: tiempo, b: upci.
	this->BUFF_UPCI_ID_INIS_CAN						=	_upci_arg.buff_upci_id_inis_can;					//puntero a buffer de id de las upci candidatas para INIS.
	this->BUFF_UPCI_ID_INDFRLIS_CAN					=	_upci_arg.buff_upci_id_indfrlis_can;				//puntero a buffer de id de las upci candidatas para INDFRLIS.
	this->BUFF_UPCI_ID_INPRRLIS_CAN					=	_upci_arg.buff_upci_id_inprrlis_can;				//puntero a buffer de id de las upci candidatas para INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a punteros a buffer de estructuras candidatas. 
	//[a][b][c]: a: tiempo, b: upci, c: buffer de estructura.
	this->BUFF_INIS_ID_CAN							=	_upci_arg.buff_inis_id_can;							//puntero a buffer de ids de estructuras tipo INIS candidatas.
	this->BUFF_INDFRLIS_ID_CAN						=	_upci_arg.buff_indfrlis_id_can;						//puntero a buffer de ids de estructuras tipo INDFRLIS candidatas.
	this->BUFF_INPRRLIS_ID_CAN						=	_upci_arg.buff_inprrlis_id_can;						//puntero a buffer de ids de estructuras tipo INPRRLIS candidatas.

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de puntero a buffer para índice de relación utilizada en reconocimiento.
	this->BUFF_RL_INDEX_USED_IN_RECOGNITION			=	_upci_arg.buff_rl_index_used_in_recognition;

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de punteros a buffers para las estructuras reconocidas.
	this->BUFF_INIS_RE								=	_upci_arg.buff_inis_re;								//puntero a buffer para estructura reconocida INIS.
	this->BUFF_INDFRLIS_RE							=	_upci_arg.buff_indfrlis_re;							//puntero a buffer para estructura reconocida INDFRLIS.
	this->BUFF_INPRRLIS_RE							=	_upci_arg.buff_inprrlis_re;							//puntero a buffer para estructura reconocida INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para los máximos ids.
	this->BUFF_INIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras INIS.
	this->BUFF_INIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras INIS.
	this->BUFF_SRLIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras SRLIS.
	this->BUFF_SRLIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras SRLIS.
	this->BUFF_PFRLIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras PFRLIS.
	this->BUFF_PFRLIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras PFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[0]					=	-1;													//buffer del máximo id de las estructuras INDFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[1]					=	-1;													//buffer del segundo máximo id de las estructuras INDFRLIS.
	this->BUFF_INPRRLIS_MAX_ID[0]					=	-1;													//buffer del máximo id de las estructuras INPRRLIS.
	this->BUFF_INPRRLIS_MAX_ID[1]					=	-1;													//buffer del segundo máximo id de las estructuras INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para la cantidad de estructuras inicializadas.
	this->BUFF_INIS_INI_AMOUNT						=	NULL;												//buffer de la cantidad de INIS inicializadas.
	this->BUFF_SRLIS_INI_AMOUNT						=	NULL;												//buffer de la cantidad de SRLIS inicializadas.
	this->BUFF_PFRLIS_INI_AMOUNT					=	NULL;												//buffer de la cantidad de PFRLIS inicializadas.
	this->BUFF_INDFRLIS_INI_AMOUNT					=	NULL;												//buffer de la cantidad de INDFRLIS inicializadas.
	this->BUFF_INPRRLIS_INI_AMOUNT					=	NULL;												//buffer de la cantidad de INPRRLIS inicializadas.
	this->BUFF_TOTAL_STR_INI_AMOUNT					=	NULL;												//buffer para la cantidad total de IS inicializadas.

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################# CONTADORES ####################################

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de contadores.
	this->KERNEL_ITERATION_COUNTER					=	NULL;												//contador de iteraciones del kernel.
	this->THREAD_ITERATION_COUNTER					=	NULL;												//contador de iteraciones del Hilo.
	this->GLOBAL_DIFFERENTIATION_COUNTER			=	NULL;												//contador de diferenciaciones globales.

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## THREADS ###################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//lanzamiento del thread para actualización de nivel de actividad de IS.
	this->TH_UPDATE_AL_STR_BUFFERS					=	thread(&UPC::UPCI_SDS::UpdateActivityLevelIS, this);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si se ha definifo el tiempo de limpieza, lanzar del thread de limpieza de IS.
	if (this->TIMEOUT_CLEAN_IS != -1)	this->TH_CLEAN_STR_BUFFERS = thread(&UPC::UPCI_SDS::CleanISBuffers, this);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método destructor.
UPCI_SDS::~UPCI_SDS()
{
	//---------------------------------------------------------------------------------
	//limpieza de upci.
	this->Clean();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método de inicialización 1 para cargar desde archivo.
in	UPCI_SDS::Initialize(UPCI_SDS_ARG &_upci_arg)
{	
	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## PARÁMETROS ################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los parámetros estructurales.
	this->GUPCI_ID									=	_upci_arg.gupci_id;									//puntero a id de la gupci.
	this->INIS_AMOUNT_ALLOWED						=	_upci_arg.inis_amount_allowed;						//cantidad de estructuras INIS permitidas.
	this->RLIS_AMOUNT_ALLOWED						=	_upci_arg.rlis_amount_allowed;						//cantidad de estructuras de relaciones permitidas por tipo.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//parámetros de actividad.
	this->DEFAULT_ACTIVITY_LEVEL					=	_upci_arg.default_activity_level;					//nivel de actividad por defecto.
	this->MAX_ACTIVITY_LEVEL_ALLOWED				=	_upci_arg.max_activity_level_allowed;				//nivel de actividad máximo permitido.
	this->MIN_ACTIVITY_LEVEL_ALLOWED				=	_upci_arg.min_activity_level_allowed;				//nivel de actividad mínimo permitido.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de umbrales.
	this->DIF_RAW_INPUT_THRESHOLD					=	_upci_arg.dif_raw_input_threshold;					//umbral de entrada cruda para focalización de la atención (%).
	this->STR_CONGRUENCE_THRESHOLD					=	_upci_arg.str_congruence_threshold;					//umbral de congruencia para estructuras candidatas (%).	
	this->PFRLIS_STRENGTH_THRESHOLD					=	_upci_arg.pfrlis_strength_threshold;				//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
	this->INDFRLIS_STRENGTH_THRESHOLD				=	_upci_arg.indfrlis_strength_threshold;				//umbral de fortaleza de relación INDFRLIS para eliminar relación por N.A.
	this->EVALUATION_THRESHOLD						=	_upci_arg.evaluation_threshold;						//umbral para evaluaciones.	
	this->TRANSITION_EVALUATION_THRESHOLD			=	_upci_arg.transition_evaluation_threshold;			//umbral para transición de evaluaciones.	

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## BANDERAS ##################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de la bandera del estado de integración del kernel (ON: integrando, OFF: libre).
	this->KERNEL_INTEGRATION_FLAG					=	OFF;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de las banderas del integrador de Hilos.
	this->THREAD_INTEGRATION_FLAG					=	OFF;												//bandera del estado de integración del Hilo (ON: integrando, OFF: libre).
	this->THREAD_INTEGRATION_LATENCY_FLAG			=	OFF;												//bandera del estado de latencia de la integración del Hilo.
	this->THREAD_INTEGRATION_FINISHED_FLAG			=	ON;													//bandera de aviso del término de la integración del Hilo.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de las banderas para estructuras creadas
	this->NEW_INPUT_FLAG							=	OFF;												//bandera de alerta de una nueva entrada.
	this->NEW_INPUT_DIFFERENCE_RELATION_FLAG		=	OFF;												//bandera de alerta de la creación de una nueva relación de diferencia de entradas.
	
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//inicialización de banderas para estructuras que superen umbral de congruencia.
	this->INIS_CONGRUENCE_ACCOMPLISHED				=	OFF;												//bandera para estructuras INIS que superen umbral de congruencia.
	this->INDFRLIS_CONGRUENCE_ACCOMPLISHED			=	OFF;												//bandera para estructuras INDFRLIS que superen umbral de congruencia.
	this->INPRRLIS_CONGRUENCE_ACCOMPLISHED			=	OFF;												//bandera para estructuras INPRRLIS que superen umbral de congruencia.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de banderas para threads activos.
	this->CLOSE_ACTIVE_THREADS_FLAG					=	_upci_arg.close_active_threads_flag;				//bandera para cerrar threads activos.
	this->PAUSE_ACTIVE_THREADS_FLAG					=	_upci_arg.pause_active_threads_flag;				//bandera para pausar threads activos.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de bandera para imprimir en pantalla.
	this->PRINT_FLAG								=	OFF;

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################### TIEMPOS ##################################### 
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de tiempos para threads de limpieza y actualización.
	this->TIMEOUT_CLEAN_IS							=	_upci_arg.timeout_clean_is;							//tiempo de espera de limpieza de IS.
	this->TIMEOUT_UPDATE_AL_IS						=	_upci_arg.timeout_update_al_is;						//tiempo de espera para actualizar niveles de actividad en IS (ms).

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################### BUFFERS ##################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de puntero a buffer del grupo de upci.	
	this->BUFF_UPCI									=	(deque<UPCI_SDS>*)_upci_arg.buff_upci;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para las IS.
	this->BUFF_INIS									=	new INIS_SD[this->INIS_AMOUNT_ALLOWED];				//buffer de estructuras de entrada.
	this->BUFF_SRLIS								=	new SRLIS[this->RLIS_AMOUNT_ALLOWED];				//buffer de estructuras de relación simple.
	this->BUFF_PFRLIS								=	new PFRLIS[this->RLIS_AMOUNT_ALLOWED];				//buffer de estructuras de relación de flujo puro.
	this->BUFF_INDFRLIS								=	new INDFRLIS_SD[this->RLIS_AMOUNT_ALLOWED];			//buffer de estructuras de relación de flujo diferencial de entradas.
	this->BUFF_INPRRLIS								=	new INPRRLIS_SD[this->RLIS_AMOUNT_ALLOWED];			//buffer de estructuras de relación de flujo proporcional de entradas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para registros.
	this->BUFF_IN_RG								=	_upci_arg.buff_in_rg;								//puntero a buffer para registro de entrada.
	this->BUFF_EV_RG								=	_upci_arg.buff_ev_rg;								//puntero a buffer para registro de evaluación de entrada.
	this->BUFF_IN_DIF_RG							=	_upci_arg.buff_in_dif_rg;							//puntero a buffer para registro de diferencia de entradas.
	this->BUFF_IN_PRO_RG							=	_upci_arg.buff_in_pro_rg;							//puntero a buffer para registro de proporción de diferencia de entradas.
	this->BUFF_OUTPUT_PROJECTION					=	_upci_arg.buff_output_projection;					//puntero a buffer para registro de proyección de salida.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura INIS con evaluación máxima.
	this->BUFF_INIS_MAX_EVAL						=	_upci_arg.buff_inis_max_eval;						//puntero a buffer para la estructura INIS con máxima evaluación.
	this->BUFF_MAX_EVALUATION						=	_upci_arg.buff_max_evaluation;						//puntero a buffer para la máxima evaluación.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura INIS con nivel de actividad máximo.
	this->BUFF_INIS_MAX_AL							=	_upci_arg.buff_inis_max_al;							//puntero a buffer para la estructura INIS con nivel de actividad máximo.
	this->BUFF_MAX_ACTIVITY_LEVEL					=	_upci_arg.buff_max_activity_level;					//puntero a buffer para el máximo nivel de actividad.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura con fortaleza de la relación máximo.
	this->BUFF_STR_MAX_RS							=	_upci_arg.buff_str_max_rs;							//puntero a buffer para la estructura con fortaleza de la relación máximo.
	this->BUFF_MAX_RELATION_STRENGTH				=	_upci_arg.buff_max_relation_strength;				//puntero a buffer para el máximo fortaleza de la relación.		

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de puntero a buffer para las estructuras proyectadas de salida.
	this->BUFF_OUTPUT_PROJECTION					=	_upci_arg.buff_output_projection;		

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para los id de las estructuras disponibles.
	this->BUFF_INIS_ID_AV[0]						=	0;													//buffer del id de INIS disponible actual.
	this->BUFF_INIS_ID_AV[1]						=	-1;													//buffer del id de INIS disponible anterior.
	this->BUFF_SRLIS_ID_AV[0]						=	0;													//buffer del id de SRLIS disponible actual.
	this->BUFF_SRLIS_ID_AV[1]						=	-1;													//buffer del id de SRLIS disponible anterior.
	this->BUFF_PFRLIS_ID_AV[0]						=	0;													//buffer del id de PFRLIS disponible actual.
	this->BUFF_PFRLIS_ID_AV[1]						=	-1;													//buffer del id de PFRLIS disponible anterior.
	this->BUFF_INDFRLIS_ID_AV[0]					=	0;													//buffer del id de INDFRLIS disponible actual.
	this->BUFF_INDFRLIS_ID_AV[1]					=	-1;													//buffer del id de INDFRLIS disponible anterior.
	this->BUFF_INPRRLIS_ID_AV[0]					=	0;													//buffer del id de INPRRLIS disponible actual.
	this->BUFF_INPRRLIS_ID_AV[1]					=	-1;													//buffer del id de INPRRLIS disponible anterior.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para los ids de las estructuras creadas.
	this->BUFF_INIS_CRE								=	_upci_arg.buff_inis_cre;							//puntero a buffer para id de INIS creada.
	this->BUFF_SRLIS_CRE							=	_upci_arg.buff_srlis_cre;							//puntero a buffer para id de SRLIS creada.
	this->BUFF_PFRLIS_CRE							=	_upci_arg.buff_pfrlis_cre;							//puntero a buffer para id de PFRLIS creada.
	this->BUFF_INDFRLIS_CRE							=	_upci_arg.buff_indfrlis_cre;						//puntero a buffer para id de INDFRLIS creada.
	this->BUFF_INPRRLIS_CRE							=	_upci_arg.buff_inprrlis_cre;						//puntero a buffer para id de INPRRLIS creada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de puntero a buffer para las estructuras INIS activadas.
	this->BUFF_INIS_ACTIVATED						=	_upci_arg.buff_inis_activated;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para las estructuras en estado de suspensión.		
	this->BUFF_INIS_SUS								=	_upci_arg.buff_inis_sus;							//puntero a buffer para las estructuras INIS suspendidas.
	this->BUFF_SRLIS_SUS							=	_upci_arg.buff_srlis_sus;							//puntero a buffer para las estructuras SRLIS suspendidas.
	this->BUFF_PFRLIS_SUS							=	_upci_arg.buff_pfrlis_sus;							//puntero a buffer para las estructuras PFRLIS suspendidas.
	this->BUFF_INDFRLIS_SUS							=	_upci_arg.buff_indfrlis_sus;						//puntero a buffer para las estructuras INDFRLIS suspendidas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para los id de las upci candidatas. 
	//[a][b]: a: tiempo, b: upci.
	this->BUFF_UPCI_ID_INIS_CAN						=	_upci_arg.buff_upci_id_inis_can;					//puntero a buffer de id de las upci candidatas para INIS.
	this->BUFF_UPCI_ID_INDFRLIS_CAN					=	_upci_arg.buff_upci_id_indfrlis_can;				//puntero a buffer de id de las upci candidatas para INDFRLIS.
	this->BUFF_UPCI_ID_INPRRLIS_CAN					=	_upci_arg.buff_upci_id_inprrlis_can;				//puntero a buffer de id de las upci candidatas para INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffer de estructuras candidatas. 
	//[a][b][c]: a: tiempo, b: upci, c: buffer de estructura.
	this->BUFF_INIS_ID_CAN							=	_upci_arg.buff_inis_id_can;							//puntero a buffer de ids de estructuras tipo INIS candidatas.
	this->BUFF_INDFRLIS_ID_CAN						=	_upci_arg.buff_indfrlis_id_can;						//puntero a buffer de ids de estructuras tipo INDFRLIS candidatas.
	this->BUFF_INPRRLIS_ID_CAN						=	_upci_arg.buff_inprrlis_id_can;						//puntero a buffer de ids de estructuras tipo INPRRLIS candidatas.

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de puntero a buffer para índice de relación utilizada en reconocimiento.
	this->BUFF_RL_INDEX_USED_IN_RECOGNITION			=	_upci_arg.buff_rl_index_used_in_recognition;

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de punteros a buffers para las estructuras reconocidas.
	this->BUFF_INIS_RE								=	_upci_arg.buff_inis_re;								//puntero a buffer para estructura reconocida INIS.
	this->BUFF_INDFRLIS_RE							=	_upci_arg.buff_indfrlis_re;							//puntero a buffer para estructura reconocida INDFRLIS.
	this->BUFF_INPRRLIS_RE							=	_upci_arg.buff_inprrlis_re;							//puntero a buffer para estructura reconocida INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para los máximos ids.
	this->BUFF_INIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras INIS.
	this->BUFF_INIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras INIS.
	this->BUFF_SRLIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras SRLIS.
	this->BUFF_SRLIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras SRLIS.
	this->BUFF_PFRLIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras PFRLIS.
	this->BUFF_PFRLIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras PFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[0]					=	-1;													//buffer del máximo id de las estructuras INDFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[1]					=	-1;													//buffer del segundo máximo id de las estructuras INDFRLIS.
	this->BUFF_INPRRLIS_MAX_ID[0]					=	-1;													//buffer del máximo id de las estructuras INPRRLIS.
	this->BUFF_INPRRLIS_MAX_ID[1]					=	-1;													//buffer del segundo máximo id de las estructuras INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para la cantidad de estructuras inicializadas.
	this->BUFF_INIS_INI_AMOUNT						=	NULL;												//buffer de la cantidad de INIS inicializadas.
	this->BUFF_SRLIS_INI_AMOUNT						=	NULL;												//buffer de la cantidad de SRLIS inicializadas.
	this->BUFF_PFRLIS_INI_AMOUNT					=	NULL;												//buffer de la cantidad de PFRLIS inicializadas.
	this->BUFF_INDFRLIS_INI_AMOUNT					=	NULL;												//buffer de la cantidad de INDFRLIS inicializadas.
	this->BUFF_INPRRLIS_INI_AMOUNT					=	NULL;												//buffer de la cantidad de INPRRLIS inicializadas.
	this->BUFF_TOTAL_STR_INI_AMOUNT					=	NULL;												//buffer para la cantidad total de IS inicializadas.

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## THREADS ###################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//lanzamiento del thread para actualización de nivel de actividad de IS.
	this->TH_UPDATE_AL_STR_BUFFERS					=	thread(&UPC::UPCI_SDS::UpdateActivityLevelIS, this);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si se ha definifo el tiempo de limpieza, lanzar del thread de limpieza de IS.
	if (this->TIMEOUT_CLEAN_IS != -1)	this->TH_CLEAN_STR_BUFFERS = thread(&UPC::UPCI_SDS::CleanISBuffers, this);

	//---------------------------------------------------------------------------------
	//successful execution.
	return SUCCESS;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método de inicialización 2 para cargar desde interfaz.
in	UPCI_SDS::Initialize(in _upci_id, in _storage_flag, UPCI_SDS_ARG &_upci_arg)
{
	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## PARÁMETROS ################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los parámetros estructurales.
	this->GUPCI_ID									=	_upci_arg.gupci_id;									//puntero a id de la gupci.
	this->UPCI_ID									=	_upci_id;											//id de la upci.
	this->INIS_AMOUNT_ALLOWED						=	_upci_arg.inis_amount_allowed;						//cantidad de estructuras INIS permitidas.
	this->RLIS_AMOUNT_ALLOWED						=	_upci_arg.rlis_amount_allowed;						//cantidad de estructuras de relaciones permitidas por tipo.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//parámetros de actividad.
	this->DEFAULT_ACTIVITY_LEVEL					=	_upci_arg.default_activity_level;					//nivel de actividad por defecto.
	this->MAX_ACTIVITY_LEVEL_ALLOWED				=	_upci_arg.max_activity_level_allowed;				//nivel de actividad máximo permitido.
	this->MIN_ACTIVITY_LEVEL_ALLOWED				=	_upci_arg.min_activity_level_allowed;				//nivel de actividad mínimo permitido.

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//incialización de umbrales.
	this->DIF_RAW_INPUT_THRESHOLD					=	_upci_arg.dif_raw_input_threshold;					//umbral de entrada cruda para focalización de la atención (%).
	this->STR_CONGRUENCE_THRESHOLD					=	_upci_arg.str_congruence_threshold;					//umbral de congruencia para estructuras candidatas (%).	
	this->PFRLIS_STRENGTH_THRESHOLD					=	_upci_arg.pfrlis_strength_threshold;				//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
	this->INDFRLIS_STRENGTH_THRESHOLD				=	_upci_arg.indfrlis_strength_threshold;				//umbral de fortaleza de relación INDFRLIS para eliminar relación por N.A.
	this->TRANSITION_EVALUATION_THRESHOLD			=	_upci_arg.transition_evaluation_threshold;			//umbral para transición de evaluaciones.	

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## BANDERAS ##################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de bandera del estado del almacenamiento de la unidad (ON: salvar, OFF: no-salvar).
	this->STORAGE_FLAG								=	_storage_flag;									

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de la bandera del estado de integración del kernel (ON: integrando, OFF: libre).
	this->KERNEL_INTEGRATION_FLAG					=	OFF;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de las banderas del integrador de Hilos.
	this->THREAD_INTEGRATION_FLAG					=	OFF;												//bandera del estado de integración del Hilo (ON: integrando, OFF: libre).
	this->THREAD_INTEGRATION_LATENCY_FLAG			=	OFF;												//bandera del estado de latencia de la integración del Hilo.
	this->THREAD_INTEGRATION_FINISHED_FLAG			=	ON;													//bandera de aviso del término de la integración del Hilo.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de las banderas para estructuras creadas
	this->NEW_INPUT_FLAG							=	OFF;												//bandera de alerta de una nueva entrada.
	this->NEW_INPUT_DIFFERENCE_RELATION_FLAG		=	OFF;												//bandera de alerta de la creación de una nueva relación de diferencia de entradas.
	
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//inicialización de banderas para estructuras que superen umbral de congruencia.
	this->INIS_CONGRUENCE_ACCOMPLISHED				=	OFF;												//bandera para estructuras INIS que superen umbral de congruencia.
	this->INDFRLIS_CONGRUENCE_ACCOMPLISHED			=	OFF;												//bandera para estructuras INDFRLIS que superen umbral de congruencia.
	this->INPRRLIS_CONGRUENCE_ACCOMPLISHED			=	OFF;												//bandera para estructuras INPRRLIS que superen umbral de congruencia.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de banderas para threads activos.
	this->CLOSE_ACTIVE_THREADS_FLAG					=	_upci_arg.close_active_threads_flag;				//bandera para cerrar threads activos.
	this->PAUSE_ACTIVE_THREADS_FLAG					=	_upci_arg.pause_active_threads_flag;				//bandera para pausar threads activos.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de bandera para imprimir en pantalla.
	this->PRINT_FLAG								=	OFF;												
	
	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################### TIEMPOS ##################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de tiempos para threads de limpieza y actualización.
	this->TIMEOUT_CLEAN_IS							=	_upci_arg.timeout_clean_is;							//tiempo de espera de limpieza de IS.
	this->TIMEOUT_UPDATE_AL_IS						=	_upci_arg.timeout_update_al_is;						//tiempo de espera para actualizar niveles de actividad en IS (ms).

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################### BUFFERS ##################################### 
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de puntero a buffer del grupo de upci.	
	this->BUFF_UPCI									=	(deque<UPCI_SDS>*)_upci_arg.buff_upci;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------  
	//seteo de puntero a buffer para el id de la upci que puede almacenar estructuras.
	this->BUFF_UPCI_ID_STORAGE_FLAG_ACT				=	_upci_arg.buff_upci_id_storage_flag_act;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para las IS.
	this->BUFF_INIS									=	new INIS_SD[this->INIS_AMOUNT_ALLOWED];				//buffer de estructuras de entrada.
	this->BUFF_SRLIS								=	new SRLIS[this->RLIS_AMOUNT_ALLOWED];				//buffer de estructuras de relación simple.
	this->BUFF_PFRLIS								=	new PFRLIS[this->RLIS_AMOUNT_ALLOWED];				//buffer de estructuras de relación de flujo puro.
	this->BUFF_INDFRLIS								=	new INDFRLIS_SD[this->RLIS_AMOUNT_ALLOWED];			//buffer de estructuras de relación de flujo diferencial de entradas.
	this->BUFF_INPRRLIS								=	new INPRRLIS_SD[this->RLIS_AMOUNT_ALLOWED];			//buffer de estructuras de relación de flujo proporcional de entradas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para registros.
	this->BUFF_IN_RG								=	_upci_arg.buff_in_rg;								//puntero a buffer para registro de entrada.
	this->BUFF_EV_RG								=	_upci_arg.buff_ev_rg;								//puntero a buffer para registro de evaluación de entrada.
	this->BUFF_IN_DIF_RG							=	_upci_arg.buff_in_dif_rg;							//puntero a buffer para registro de diferencia de entradas.
	this->BUFF_IN_PRO_RG							=	_upci_arg.buff_in_pro_rg;							//puntero a buffer para registro de proporción de diferencia de entradas.
	this->BUFF_OUTPUT_PROJECTION					=	_upci_arg.buff_output_projection;					//puntero a buffer para registro de proyección de salida.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura INIS con evaluación máxima.
	this->BUFF_INIS_MAX_EVAL						=	_upci_arg.buff_inis_max_eval;						//puntero a buffer para la estructura INIS con máxima evaluación.
	this->BUFF_MAX_EVALUATION						=	_upci_arg.buff_max_evaluation;						//puntero a buffer para la máxima evaluación.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura INIS con nivel de actividad máximo.
	this->BUFF_INIS_MAX_AL							=	_upci_arg.buff_inis_max_al;							//puntero a buffer para la estructura INIS con nivel de actividad máximo.
	this->BUFF_MAX_ACTIVITY_LEVEL					=	_upci_arg.buff_max_activity_level;					//puntero a buffer para el máximo nivel de actividad.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura con fortaleza de la relación máximo.
	this->BUFF_STR_MAX_RS							=	_upci_arg.buff_str_max_rs;							//puntero a buffer para la estructura con fortaleza de la relación máximo.
	this->BUFF_MAX_RELATION_STRENGTH				=	_upci_arg.buff_max_relation_strength;				//puntero a buffer para el máximo fortaleza de la relación.	

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de puntero a buffer para las estructuras proyectadas de salida.
	this->BUFF_OUTPUT_PROJECTION					=	_upci_arg.buff_output_projection;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para los id de las estructuras disponibles.
	this->BUFF_INIS_ID_AV[0]						=	0;													//buffer del id de INIS disponible actual.
	this->BUFF_INIS_ID_AV[1]						=	-1;													//buffer del id de INIS disponible anterior.
	this->BUFF_SRLIS_ID_AV[0]						=	0;													//buffer del id de SRLIS disponible actual.
	this->BUFF_SRLIS_ID_AV[1]						=	-1;													//buffer del id de SRLIS disponible anterior.
	this->BUFF_PFRLIS_ID_AV[0]						=	0;													//buffer del id de PFRLIS disponible actual.
	this->BUFF_PFRLIS_ID_AV[1]						=	-1;													//buffer del id de PFRLIS disponible anterior.
	this->BUFF_INDFRLIS_ID_AV[0]					=	0;													//buffer del id de INDFRLIS disponible actual.
	this->BUFF_INDFRLIS_ID_AV[1]					=	-1;													//buffer del id de INDFRLIS disponible anterior.
	this->BUFF_INPRRLIS_ID_AV[0]					=	0;													//buffer del id de INPRRLIS disponible actual.
	this->BUFF_INPRRLIS_ID_AV[1]					=	-1;													//buffer del id de INPRRLIS disponible anterior.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo a punteros a buffers para los ids de las estructuras creadas.
	this->BUFF_INIS_CRE								=	_upci_arg.buff_inis_cre;							//puntero a buffer para id de INIS creada.
	this->BUFF_SRLIS_CRE							=	_upci_arg.buff_srlis_cre;							//puntero a buffer para id de SRLIS creada.
	this->BUFF_PFRLIS_CRE							=	_upci_arg.buff_pfrlis_cre;							//puntero a buffer para id de PFRLIS creada.
	this->BUFF_INDFRLIS_CRE							=	_upci_arg.buff_indfrlis_cre;						//puntero a buffer para id de INDFRLIS creada.
	this->BUFF_INPRRLIS_CRE							=	_upci_arg.buff_inprrlis_cre;						//puntero a buffer para id de INPRRLIS creada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de puntero a buffer para las estructuras INIS activadas.
	this->BUFF_INIS_ACTIVATED						=	_upci_arg.buff_inis_activated;						

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para las estructuras en estado de suspensión.		
	this->BUFF_INIS_SUS								=	_upci_arg.buff_inis_sus;							//puntero a buffer para las estructuras INIS suspendidas.
	this->BUFF_SRLIS_SUS							=	_upci_arg.buff_srlis_sus;							//puntero a buffer para las estructuras SRLIS suspendidas.
	this->BUFF_PFRLIS_SUS							=	_upci_arg.buff_pfrlis_sus;							//puntero a buffer para las estructuras PFRLIS suspendidas.
	this->BUFF_INDFRLIS_SUS							=	_upci_arg.buff_indfrlis_sus;						//puntero a buffer para las estructuras INDFRLIS suspendidas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para los id de las upci candidatas. 
	//[a][b]: a: tiempo, b: upci.
	this->BUFF_UPCI_ID_INIS_CAN						=	_upci_arg.buff_upci_id_inis_can;					//puntero a buffer de id de las upci candidatas para INIS.
	this->BUFF_UPCI_ID_INDFRLIS_CAN					=	_upci_arg.buff_upci_id_indfrlis_can;				//puntero a buffer de id de las upci candidatas para INDFRLIS.
	this->BUFF_UPCI_ID_INPRRLIS_CAN					=	_upci_arg.buff_upci_id_inprrlis_can;				//puntero a buffer de id de las upci candidatas para INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a punteros a buffer de estructuras candidatas. 
	//[a][b][c]: a: tiempo, b: upci, c: buffer de estructura.
	this->BUFF_INIS_ID_CAN							=	_upci_arg.buff_inis_id_can;							//puntero a buffer de ids de estructuras tipo INIS candidatas.
	this->BUFF_INDFRLIS_ID_CAN						=	_upci_arg.buff_indfrlis_id_can;						//puntero a buffer de ids de estructuras tipo INDFRLIS candidatas.
	this->BUFF_INPRRLIS_ID_CAN						=	_upci_arg.buff_inprrlis_id_can;						//puntero a buffer de ids de estructuras tipo INPRRLIS candidatas.

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de puntero a buffer para índice de relación utilizada en reconocimiento.
	this->BUFF_RL_INDEX_USED_IN_RECOGNITION			=	_upci_arg.buff_rl_index_used_in_recognition;

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de punteros a buffers para las estructuras reconocidas.
	this->BUFF_INIS_RE								=	_upci_arg.buff_inis_re;								//puntero a buffer para estructura reconocida INIS.
	this->BUFF_INDFRLIS_RE							=	_upci_arg.buff_indfrlis_re;							//puntero a buffer para estructura reconocida INDFRLIS.
	this->BUFF_INPRRLIS_RE							=	_upci_arg.buff_inprrlis_re;							//puntero a buffer para estructura reconocida INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para los máximos ids.
	this->BUFF_INIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras INIS.
	this->BUFF_INIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras INIS.
	this->BUFF_SRLIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras SRLIS.
	this->BUFF_SRLIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras SRLIS.
	this->BUFF_PFRLIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras PFRLIS.
	this->BUFF_PFRLIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras PFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[0]					=	-1;													//buffer del máximo id de las estructuras INDFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[1]					=	-1;													//buffer del segundo máximo id de las estructuras INDFRLIS.
	this->BUFF_INPRRLIS_MAX_ID[0]					=	-1;													//buffer del máximo id de las estructuras INPRRLIS.
	this->BUFF_INPRRLIS_MAX_ID[1]					=	-1;													//buffer del segundo máximo id de las estructuras INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para la cantidad de estructuras inicializadas.
	this->BUFF_INIS_INI_AMOUNT						=	NULL;												//buffer de la cantidad de INIS inicializadas.
	this->BUFF_SRLIS_INI_AMOUNT						=	NULL;												//buffer de la cantidad de SRLIS inicializadas.
	this->BUFF_PFRLIS_INI_AMOUNT					=	NULL;												//buffer de la cantidad de PFRLIS inicializadas.
	this->BUFF_INDFRLIS_INI_AMOUNT					=	NULL;												//buffer de la cantidad de INDFRLIS inicializadas.
	this->BUFF_INPRRLIS_INI_AMOUNT					=	NULL;												//buffer de la cantidad de INPRRLIS inicializadas.
	this->BUFF_TOTAL_STR_INI_AMOUNT					=	NULL;												//buffer para la cantidad total de IS inicializadas.

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################# CONTADORES ####################################

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de contadores.
	this->KERNEL_ITERATION_COUNTER					=	NULL;												//contador de iteraciones del kernel.
	this->THREAD_ITERATION_COUNTER					=	NULL;												//contador de iteraciones del Hilo.
	this->GLOBAL_DIFFERENTIATION_COUNTER			=	NULL;												//contador de diferenciaciones globales.

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## THREADS ###################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//lanzamiento del thread para actualización de nivel de actividad de IS.
	this->TH_UPDATE_AL_STR_BUFFERS					=	thread(&UPC::UPCI_SDS::UpdateActivityLevelIS, this);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si se ha definifo el tiempo de limpieza, lanzar del thread de limpieza de IS.
	if (this->TIMEOUT_CLEAN_IS != -1)	this->TH_CLEAN_STR_BUFFERS = thread(&UPC::UPCI_SDS::CleanISBuffers, this);

	//---------------------------------------------------------------------------------
	//successful execution.
	return SUCCESS;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para Clean upci.
in	UPCI_SDS::Clean()
{		
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo del estado de la bandera para cerrar threads activos.
	this->SetCLOSE_ACTIVE_THREADS_FLAG(ON);
	
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//término de threads.
	if (this->TH_THREAD_INTEGRATION.joinable()				== ON)	this->TH_THREAD_INTEGRATION.join();
	if (this->TH_CLEAN_STR_BUFFERS.joinable()				== ON)	this->TH_CLEAN_STR_BUFFERS.join();
	if (this->TH_UPDATE_AL_STR_BUFFERS.joinable()			== ON)	this->TH_UPDATE_AL_STR_BUFFERS.join();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de los parámetros estructurales.
	this->UPCI_ID									=	-1;									//id de la upci.
	this->INIS_AMOUNT_ALLOWED						=	NULL;								//cantidad de estructuras INIS permitidas.
	this->RLIS_AMOUNT_ALLOWED						=	NULL;								//cantidad de estructuras PFRLIS y eiRFD permitidas.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de los parámetros de actividad.
	this->DEFAULT_ACTIVITY_LEVEL					=	NULL;								//nivel de actividad por defecto.
	this->MAX_ACTIVITY_LEVEL_ALLOWED				=	NULL;								//nivel de actividad máximo permitido.
	this->MIN_ACTIVITY_LEVEL_ALLOWED				=	NULL;								//nivel de actividad mínimo permitido.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de los umbrales.
	this->DIF_RAW_INPUT_THRESHOLD					=	NULL;								//umbral de entrada cruda para focalización de la atención (%).
	this->STR_CONGRUENCE_THRESHOLD					=	NULL;								//umbral de congruencia para estructuras candidatas (%).	
	this->PFRLIS_STRENGTH_THRESHOLD					=	NULL;								//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
	this->INDFRLIS_STRENGTH_THRESHOLD				=	NULL;								//umbral de fortaleza de relación INDFRLIS para eliminar relación por N.A.
	this->EVALUATION_THRESHOLD						=	NULL;								//umbral para evaluaciones.	
	this->TRANSITION_EVALUATION_THRESHOLD			=	NULL;								//umbral para transición de evaluaciones.	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de las banderas.
	this->STORAGE_FLAG								=	-1;									//bandera del estado del almacenamiento de la unidad (ON: salvar, OFF: no-salvar).
	this->KERNEL_INTEGRATION_FLAG					=	-1;									//bandera del estado de integración del kernel (ON: integrando, OFF: libre).
	this->THREAD_INTEGRATION_FLAG					=	-1;									//bandera del estado de integración de la unidad (ON: integrando, OFF: libre).
	this->THREAD_INTEGRATION_LATENCY_FLAG			=	-1;									//bandera del estado de latencia de la integración.
	this->THREAD_INTEGRATION_FINISHED_FLAG			=	-1;									//bandera de aviso del término de la integración del Hilo.
	this->NEW_INPUT_FLAG							=	-1;									//bandera de alerta de una nueva entrada.
	this->NEW_INPUT_DIFFERENCE_RELATION_FLAG		=	-1;									//bandera de alerta de la creación de una nueva relación INDFRLIS.
	this->INIS_CONGRUENCE_ACCOMPLISHED				=	-1;									//bandera para estructuras INIS que superen umbral de congruencia.
	this->INDFRLIS_CONGRUENCE_ACCOMPLISHED			=	-1;									//bandera para estructuras INDFRLIS que superen umbral de congruencia.
	this->INPRRLIS_CONGRUENCE_ACCOMPLISHED			=	-1;									//bandera para estructuras INPRRLIS que superen umbral de congruencia.
	this->PRINT_FLAG								=	-1;									//bandera para imprimir en pantalla.	
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de los buffers para las IS.
	delete[] this->BUFF_INIS;																//buffer para estructuras tipo INIS.
	delete[] this->BUFF_SRLIS;																//buffer para estructuras tipo SRLIS.
	delete[] this->BUFF_PFRLIS;																//buffer para estructuras tipo PFRLIS.	
	delete[] this->BUFF_INDFRLIS;															//buffer para estructuras tipo INDFRLIS.	
	delete[] this->BUFF_INPRRLIS;															//buffer para estructuras tipo INPRRLIS.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de los buffers para los id de las estructuras disponibles.
	this->BUFF_INIS_ID_AV[0]						=	-1;									//buffer para id de INIS disponible actual.
	this->BUFF_INIS_ID_AV[1]						=	-1;									//buffer para id de INIS disponible anterior.
	this->BUFF_PFRLIS_ID_AV[0]						=	-1;									//buffer para id de PFRLIS disponible actual.
	this->BUFF_PFRLIS_ID_AV[1]						=	-1;									//buffer para id de PFRLIS disponible anterior.
	this->BUFF_INDFRLIS_ID_AV[0]					=	-1;									//buffer para id de INDFRLIS disponible actual.
	this->BUFF_INDFRLIS_ID_AV[1]					=	-1;									//buffer para id de INDFRLIS disponible anterior.
	this->BUFF_INPRRLIS_ID_AV[0]					=	-1;									//buffer para id de INPRRLIS disponible actual.
	this->BUFF_INPRRLIS_ID_AV[1]					=	-1;									//buffer para id de INPRRLIS disponible anterior.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de los buffers para los máximos ids.
	this->BUFF_INIS_MAX_ID[0]						=	-1;									//buffer del máximo id de las estructuras INIS.
	this->BUFF_INIS_MAX_ID[1]						=	-1;									//buffer del segundo máximo id de las estructuras INIS.
	this->BUFF_PFRLIS_MAX_ID[0]						=	-1;									//buffer del máximo id de las estructuras PFRLIS.
	this->BUFF_PFRLIS_MAX_ID[1]						=	-1;									//buffer del segundo máximo id de las estructuras PFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[0]					=	-1;									//buffer del máximo id de las estructuras INDFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[1]					=	-1;									//buffer del segundo máximo id de las estructuras INDFRLIS.
	this->BUFF_INPRRLIS_MAX_ID[0]					=	-1;									//buffer del máximo id de las estructuras INPRRLIS.
	this->BUFF_INPRRLIS_MAX_ID[1]					=	-1;									//buffer del segundo máximo id de las estructuras INPRRLIS.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de los buffers para la cantidad de estructuras inicializadas.
	this->BUFF_INIS_INI_AMOUNT						=	NULL;								//buffer de la cantidad de INIS inicializadas.
	this->BUFF_PFRLIS_INI_AMOUNT					=	NULL;								//buffer de la cantidad de PFRLIS inicializadas.
	this->BUFF_INDFRLIS_INI_AMOUNT					=	NULL;								//buffer de la cantidad de INDFRLIS inicializadas.
	this->BUFF_INPRRLIS_INI_AMOUNT					=	NULL;								//buffer de la cantidad de INPRRLIS inicializadas.
	this->BUFF_TOTAL_STR_INI_AMOUNT					=	NULL;								//buffer para la cantidad total de IS inicializadas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de buffers auxiliares.
	this->BUFF_STR_SUS_AUX.Clean();															//buffer auxiliar para estructuras en suspensión.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de tiempos para threads de limpieza y actualización.
	this->TIMEOUT_CLEAN_IS							=	-1;									//tiempo de espera de limpieza de IS.
	this->TIMEOUT_UPDATE_AL_IS						=	-1;									//tiempo de espera para actualizar niveles de actividad en IS (ms).

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de contadores.
	this->KERNEL_ITERATION_COUNTER					=	NULL;								//contador de iteraciones del kernel.
	this->THREAD_ITERATION_COUNTER					=	NULL;								//contador de iteraciones del Hilo.
	this->GLOBAL_DIFFERENTIATION_COUNTER			=	NULL;								//contador de diferenciaciones globales.	

	//---------------------------------------------------------------------------------
	//successful execution.
	return SUCCESS;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método de entrada y salida del kernel.
vo	UPCI_SDS::KernelInput()
{	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//activación de la bandera de integración del Kernel.
	this->SetKERNEL_INTEGRATION_FLAG(ON);	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si el hilo "ThreadIntegrationInput" no está integrando y ha finalizado.
	if (this->GetTHREAD_INTEGRATION_FLAG() == OFF && this->GetTHREAD_INTEGRATION_FINISHED_FLAG() == ON)
	{			
		//-----------------------------------------------------------------------------
		//término del thread.
		if (this->TH_THREAD_INTEGRATION.joinable() == ON)	this->TH_THREAD_INTEGRATION.join();
			
		//-----------------------------------------------------------------------------  
		//integración de Hilos.
		this->TH_THREAD_INTEGRATION	= thread(&UPC::UPCI_SDS::ThreadIntegrationInput, this);
	}

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//si el hilo "ThreadIntegrationInput" no está integrando y no ha finalizado.
	else if (this->GetTHREAD_INTEGRATION_FLAG() == OFF && this->GetTHREAD_INTEGRATION_FINISHED_FLAG() == OFF)
	{
		//-----------------------------------------------------------------------------
		//activación de bandera para integrar entrada.
		this->SetNEW_INPUT_FLAG(ON);
	}	

	//---------------------------------------------------------------------------------
	//incremento del contador de iteraciones del kernel.
	++this->KERNEL_ITERATION_COUNTER;

	//---------------------------------------------------------------------------------
	//desactivación de la bandera de integración del Kernel.
	this->SetKERNEL_INTEGRATION_FLAG(OFF);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------  

//-------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------- 
//#1: método de entrada para la integración de Hilos.
vo	UPCI_SDS::ThreadIntegrationInput()
{
	//--------------------------------------------------------------------------------- 
	//--------------------------------------------------------------------------------- 
	//variable auxiliar para diferencia de evaluación presente.	
	dou	input_evaluation_difference			= NULL;							

	//--------------------------------------------------------------------------------- 
	//--------------------------------------------------------------------------------- 
	//variables auxiliares para estructura INIS reconocida indirectamente.
	in	upci_id_inis_ire					= NULL;											//id de la upci de la estructura INIS reconocida indirectamente.
	in	inis_id_ire							= NULL;											//id de la estructura INIS reconocida indirectamente.

	//--------------------------------------------------------------------------------- 
	//--------------------------------------------------------------------------------- 
	//variables auxiliares para estructura INDFRLIS reconocida indirectamente.
	in	upci_id_indfrlis_re					= NULL;											//id de la upci de la estructura INDFRLIS reconocida indirectamente.
	in	indfrlis_id_re						= NULL;											//id de la estructura INDFRLIS reconocida indirectamente.
	
	//---------------------------------------------------------------------------------
	//activación de la bandera de integración de Hilos.
	this->SetTHREAD_INTEGRATION_FLAG(ON);

	//---------------------------------------------------------------------------------
	//desactivación de bandera de finalización de integración de Hilos.
	this->SetTHREAD_INTEGRATION_FINISHED_FLAG(OFF);

	//---------------------------------------------------------------------------------
	//incremento del contador de iteraciones del Hilo.
	++this->THREAD_ITERATION_COUNTER;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//####################### INICIO DE INTEGRACIÓN DE HILOS ##########################	
	
	//---------------------------------------------------------------------------------
	//impresión de la inicialización de la integración de la upci.
	this->Print("--------------------------------------------------------------------");
	this->Print("> integracion THREAD iniciada.");
	this->Print("> upci id   ", this->UPCI_ID);
	this->Print("> iteracion ", this->GetTHREAD_ITERATION_COUNTER());

	//---------------------------------------------------------------------------------
	//impresión de la evaluación de la entrada.
	this->Print("    > Evaluacion              ", *this->BUFF_EV_RG);

	//---------------------------------------------------------------------------------
	//diferenciación global de la entrada.
	this->GlobalDifferentiationINIS();	

	//---------------------------------------------------------------------------------
	//reactivación y relacionamiento de la estructura INIS reconocida.
	this->BUFF_UPCI->at(this->BUFF_INIS_RE->UPCI_ID).ReactiveINIS(this->BUFF_INIS_RE->STR_ID);
	this->BUFF_UPCI->at(this->BUFF_INIS_RE->UPCI_ID).RelateINIS_CR(this->BUFF_INIS_RE->STR_ID);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si el nivel de congruencia no supera el umbral de congruencia, entonces.
	if (this->GetINIS_CONGRUENCE_ACCOMPLISHED() == OFF)
	{
		//-----------------------------------------------------------------------------
		//creación de estructura de entrada.
		this->CreateINIS(this->BUFF_IN_RG, *this->BUFF_EV_RG, RS_EFFECTIVE);
	}

	//---------------------------------------------------------------------------------
	//integración de Hilos por reconocimiento de INIS.
	this->BUFF_UPCI->at(this->BUFF_INIS_RE->UPCI_ID).RecognizedThreadIntegrationINIS();

	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existe reconocimimento de una estructura INIS, entonces.
	if (this->BUFF_INIS_RE->STR_ID != -1)
	{
		
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si no existe reconocimimento de una estructura INIS, entonces.
	else
	{
		//-----------------------------------------------------------------------------
		//creación de estructura de entrada.
		this->CreateINIS(this->BUFF_IN_RG, *this->BUFF_EV_RG, RS_EFFECTIVE);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si se verifica la creación de una estructura INDFRLIS, entonces.
		if (this->GetNEW_INPUT_DIFFERENCE_RELATION_FLAG() == ON)
		{
			//-------------------------------------------------------------------------
			//si existe reconocimimento de una estructura INDFRLIS, entonces.
			if (this->BUFF_INDFRLIS_RE->STR_ID != -1)
			{
				//---------------------------------------------------------------------
				//impresión del reconocimiento de una estructura INDFRLIS.
				this->Print("    > hay reconocimiento de una estructura INDFRLIS con id", this->BUFF_INDFRLIS_RE->STR_ID);
				
				//---------------------------------------------------------------------
				//reactivación de la estructura INDFRLIS reconocida.
				this->BUFF_UPCI->at(this->BUFF_INDFRLIS_RE->UPCI_ID).ReactiveINDFRLIS(this->BUFF_INDFRLIS_RE->STR_ID);
				
				//---------------------------------------------------------------------
				//obtención de datos de la estructura INIS final de la relación.
				upci_id_inis_ire	= this->BUFF_UPCI->at(this->BUFF_INDFRLIS_RE->UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_RE->STR_ID].UPCI_ID_STR2_RG;
				inis_id_ire			= this->BUFF_UPCI->at(this->BUFF_INDFRLIS_RE->UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_RE->STR_ID].STR2_ID_RG;
				
				//---------------------------------------------------------------------
				//seteo de la estructura INIS reconocida indirectamente.
				this->BUFF_INIS_RE->Set(upci_id_inis_ire, inis_id_ire);

				//---------------------------------------------------------------------
				//reactivación de la estructura INIS reconocida indirectamente.
				this->BUFF_UPCI->at(this->BUFF_INIS_RE->UPCI_ID).ReactiveINIS(this->BUFF_INIS_RE->STR_ID);

				//---------------------------------------------------------------------
				//seteo del índice de la relación INDFRLIS entrante en la estructura INIS.
				*this->BUFF_RL_INDEX_USED_IN_RECOGNITION = this->BUFF_UPCI->at(this->BUFF_INIS_RE->UPCI_ID).BUFF_INIS[this->BUFF_INIS_RE->STR_ID].GetRelationIndex(INDFRLIS_TYPE,
																																								   this->BUFF_INDFRLIS_RE->STR_ID,
																																								   this->BUFF_INDFRLIS_RE->UPCI_ID);				
				
				//---------------------------------------------------------------------
				//relacionamiento de la estructura INIS reconocida indirectamente.
				this->BUFF_UPCI->at(this->BUFF_INIS_RE->UPCI_ID).RelateINIS_CR(this->BUFF_INIS_RE->STR_ID);				
				
				//---------------------------------------------------------------------
				//integración de Hilos por reconocimiento indirecto de INIS.
				this->BUFF_UPCI->at(this->BUFF_INIS_RE->UPCI_ID).RecognizedThreadIntegrationINIS();
			}

			//-------------------------------------------------------------------------
			//si existe reconocimimento de una estructura INPRRLIS, entonces.
			else if (this->BUFF_INPRRLIS_RE->STR_ID != -1)
			{
				//---------------------------------------------------------------------
				//impresión del reconocimiento de una estructura INPRRLIS.
				this->Print("    > hay reconocimiento de una estructura INPRRLIS con id", this->BUFF_INPRRLIS_RE->STR_ID);

				//---------------------------------------------------------------------
				//obtención de datos de la estructura INDFRLIS final de la relación.
				upci_id_indfrlis_re	= this->BUFF_UPCI->at(this->BUFF_INPRRLIS_RE->UPCI_ID).BUFF_INPRRLIS[this->BUFF_INPRRLIS_RE->STR_ID].UPCI_ID_STR2_RG;
				indfrlis_id_re		= this->BUFF_UPCI->at(this->BUFF_INPRRLIS_RE->UPCI_ID).BUFF_INPRRLIS[this->BUFF_INPRRLIS_RE->STR_ID].STR2_ID_RG;
				
				//---------------------------------------------------------------------
				//seteo de la estructura INDFRLIS reconocida indirectamente.
				this->BUFF_INDFRLIS_RE->Set(upci_id_indfrlis_re, indfrlis_id_re);
				
				//---------------------------------------------------------------------
				//reactivación de la estructura INDFRLIS reconocida indirectamente.
				this->BUFF_UPCI->at(this->BUFF_INDFRLIS_RE->UPCI_ID).ReactiveINDFRLIS(this->BUFF_INDFRLIS_RE->STR_ID);

				//---------------------------------------------------------------------
				//obtención de datos de la estructura INIS final de la relación.
				upci_id_inis_ire	= this->BUFF_UPCI->at(this->BUFF_INDFRLIS_RE->UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_RE->STR_ID].UPCI_ID_STR2_RG;
				inis_id_ire			= this->BUFF_UPCI->at(this->BUFF_INDFRLIS_RE->UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_RE->STR_ID].STR2_ID_RG;
				
				//---------------------------------------------------------------------
				//seteo de la estructura INIS reconocida indirectamente.
				this->BUFF_INIS_RE->Set(upci_id_inis_ire, inis_id_ire);
				
				//---------------------------------------------------------------------
				//reactivación de la estructura INIS reconocida indirectamente.
				this->BUFF_UPCI->at(this->BUFF_INIS_RE->UPCI_ID).ReactiveINIS(this->BUFF_INIS_RE->STR_ID);				
				
				//---------------------------------------------------------------------
				//seteo del índice de la relación INDFRLIS entrante en la estructura INIS.
				*this->BUFF_RL_INDEX_USED_IN_RECOGNITION = this->BUFF_UPCI->at(this->BUFF_INIS_RE->UPCI_ID).BUFF_INIS[this->BUFF_INIS_RE->STR_ID].GetRelationIndex(INDFRLIS_TYPE,
																																								   this->BUFF_INDFRLIS_RE->STR_ID,
																																								   this->BUFF_INDFRLIS_RE->UPCI_ID);
				
				//---------------------------------------------------------------------
				//relacionamiento de la estructura INIS reconocida indirectamente.
				this->BUFF_UPCI->at(this->BUFF_INIS_RE->UPCI_ID).RelateINIS_CR(this->BUFF_INIS_RE->STR_ID);

				//---------------------------------------------------------------------
				//integración de Hilos por reconocimiento indirecto de INIS.
				this->BUFF_UPCI->at(this->BUFF_INIS_RE->UPCI_ID).RecognizedThreadIntegrationINIS();
			}				
		}		
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//##################### FIN ALGORITMO DE INTEGRACIÓN DE HILOS #####################	

	//---------------------------------------------------------------------------------
	//desactivación de la bandera de integración de Hilos.
	this->SetTHREAD_INTEGRATION_FLAG(OFF);	
	this->SetTHREAD_INTEGRATION_FINISHED_FLAG(ON);

	//---------------------------------------------------------------------------------
	//impresión de la finalización de la integración de la upci.
	this->Print("> integracion THREAD finalizada.");
	this->Print("--------------------------------------------------------------------");
	this->Print("--------------------------------------------------------------------");
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------   
//#1: método para la integración de Hilos reconocidos por INIS.
vo	UPCI_SDS::RecognizedThreadIntegrationINIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//impresión del reconocimiento de una estructura INIS.
	this->Print("    > hay reconocimiento de una estructura INIS con id", this->BUFF_INIS_RE->STR_ID);
	//cout << "hay reconocimiento de una estructura INIS: "<< this->BUFF_INIS_RE->STR_ID << endl;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para INIS activada actual.
	in					current_inis_activated_id			= NULL;							//id de la estructura INIS activada actual.
	in					upci_id_current_inis_activated		= NULL;							//id de la upci de la estructura INIS activada actual.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura reconocida.
	in					rl_to_use_amount					= 0;							//cantidad de relaciones a utilizar de la estructura reconocida.
	in 					rl_index_to_use_aux					= 0;							//índice de la relación a utilizar de la estructura reconocida auxiliar.
	vein 				rl_index_to_use;													//índices de las relaciones a utilizar de la estructura reconocida.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para índice de la acción potencial ganadora.
	in					potential_action_index				= NULL;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura INIS activada anterior.
	in					previous_inis_id					= NULL;							//id de la estructura INIS activada anteriormente.
	in					previous_upci_id_inis				= NULL;							//id de la upci de la estructura INIS activada anteriormente.	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para evaluación del Hilo actual
	dou					current_thread_evaluation			= NULL;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliares para la acción potencial ganadora.
	in					upci_id_winning_acis				= NULL;							//id de la upci de la acción potencial ganadora.
	in					winning_acis_id						= NULL;							//id de la acción potencial ganadora.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para bandera de acción potencial ganadora.
	in					winning_potential_action_flag		= OFF;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------  
	//buffer para acciones potenciales.
	deBUFF_STR_IIE		potential_actions;													

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de tiempo de espera para la espera de una nueva entrada.
	chrono::milliseconds timeout_loop_very_fast(TIMEOUT_LOOP_VERY_FAST);	
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//################# INICIO DE INTEGRACIÓN DE HILOS POTENCIALES ####################	
	//cout << "*this->BUFF_RL_INDEX_USED_IN_RECOGNITION : " << *this->BUFF_RL_INDEX_USED_IN_RECOGNITION << endl;

	//---------------------------------------------------------------------------------
	//seteo de los datos de la estructura INIS activada actual.
	current_inis_activated_id			= this->BUFF_INIS_ACTIVATED[0].STR_ID;
	upci_id_current_inis_activated		= this->BUFF_INIS_ACTIVATED[0].UPCI_ID;

	//---------------------------------------------------------------------------------
	//obtención de la evaluación de Hilo actual.
	current_thread_evaluation			= this->BUFF_UPCI->at(upci_id_current_inis_activated).BUFF_INIS[current_inis_activated_id].EV_RG;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si se ha definido el índice de la relación utiliza en reconocimiento, entonces.
	if (*this->BUFF_RL_INDEX_USED_IN_RECOGNITION != -1)
	{
		//-----------------------------------------------------------------------------
		//obtención del índice de la relación saliente a utilizar si existe.
		rl_index_to_use_aux = this->BUFF_INIS[this->BUFF_INIS_RE->STR_ID].GetNextOutputRelationS(*this->BUFF_RL_INDEX_USED_IN_RECOGNITION);

		//-----------------------------------------------------------------------------
		//si se ha obtenido un índice, entonces setear en buffer.
		if (rl_index_to_use_aux != -1)	rl_index_to_use.push_back(rl_index_to_use_aux);
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si no se ha definido el índice de la relación utiliza en reconocimiento, entonces.
	else
	{
		//-----------------------------------------------------------------------------
		//bucle para obtener índices de relaciones a utilizar.
		while (true)
		{
			//-------------------------------------------------------------------------
			//obtención del índice de la relación saliente a utilizar si existe.
			rl_index_to_use_aux = this->BUFF_INIS[this->BUFF_INIS_RE->STR_ID].GetNextOutputRelationS(rl_index_to_use_aux);

			//-------------------------------------------------------------------------
			//si se ha obtenido un índice, entonces setear en buffer.
			if (rl_index_to_use_aux != -1)	rl_index_to_use.push_back(rl_index_to_use_aux);

			//-------------------------------------------------------------------------
			//si no se ha obtenido un índice, entonces salir del bucle.
			else break;
		}
	}

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de relaciones a utilizar de la estructura reconocida.
	rl_to_use_amount = in(rl_index_to_use.size());
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existen relaciones salientes para obtener acciones potenciales, entonces.
	if (rl_to_use_amount > 0)
	{
		//-----------------------------------------------------------------------------
		//inicialización de la cantidad de acciones potenciales.
		potential_actions.resize(rl_to_use_amount);

		//-----------------------------------------------------------------------------
		//paralelización del bucle for.
		#pragma omp parallel for

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para obtener acciones potenciales por expansión de flujo directo sobre la
		//estructura INIS reconocida.
		for (in i1 = 0; i1 < rl_to_use_amount; i1++)
		{
			//-------------------------------------------------------------------------
			//obtención de Hilo pontencial i1.
			this->GetPotentialActionsINIS(this->BUFF_INIS_RE->STR_ID, rl_index_to_use.at(i1), &potential_actions.at(i1));
		}	
		
		//-----------------------------------------------------------------------------
		//obtención del índice de la acción potencial ganadora.
		potential_action_index	= this->GetWinningPotentialActionIndex(current_thread_evaluation, potential_actions);
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existe una acción potencial a ejecutar, entonces.
		if (potential_action_index != -1)
		{
			//-------------------------------------------------------------------------
			//obtención de los datos de la acción potencial ganadora.
			upci_id_winning_acis		= potential_actions.at(potential_action_index).GetUPCI_ID();
			winning_acis_id				= potential_actions.at(potential_action_index).GetSTR_ID();

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la acción potencial ganadora está definida, entonces.
			if (upci_id_winning_acis != -1 && winning_acis_id != -1)
			{
				//---------------------------------------------------------------------
				//se ejecuta la acción del Hilo ganador.
				this->BUFF_UPCI->at(upci_id_winning_acis).OutputEstructure(winning_acis_id, _output_action);
				//cout << "#accion: " << this->BUFF_UPCI->at(upci_id_winning_acis).BUFF_ACIS[winning_acis_id].AC_RG << "ev: " << potential_actions.at(potential_action_index).GetEVALUATION() <<endl;
			}			
			//else cout << "#accion: nada" << "ev: "<< potential_actions.at(potential_action_index).GetEVALUATION() <<endl;
			//-------------------------------------------------------------------------
			//seteo del estado de la bandera de acción potencial ganadora.
			winning_potential_action_flag	= ON;
		}		
	}		

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existe una acción potencial ganadora, entonces.
	if(winning_potential_action_flag == OFF)
	{
		//-----------------------------------------------------------------------------
		//reactivación de la estructura INIS reconocida.
		this->BUFF_UPCI->at(this->BUFF_INIS_RE->UPCI_ID).ReactiveINIS(this->BUFF_INIS_RE->STR_ID);
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si se verifica la creación de una estructura INDFRLIS, entonces.
		if (this->GetNEW_INPUT_DIFFERENCE_RELATION_FLAG() == ON)
		{
			//-------------------------------------------------------------------------
			//si la estructura de diferencia de entradas está en suspensión.
			if (this->BUFF_INDFRLIS[this->BUFF_INDFRLIS_CRE[0].STR_ID].AL_SRG > 0)
			{
				//---------------------------------------------------------------------
				//integración de evaluación o transición de evaluación de entradas.
				this->InputTransitionEvaluationIntegration(_output_action);
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//integración de evaluación o transición de evaluación de entradas.
		else this->InputEvaluationIntegration(_output_action);
	}
} 

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para la integración de Hilos reconocidos por ACIS.
vo	UPCI_SDS::RecognizedThreadIntegrationACIS()
{
	/*
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//impresión del reconocimiento de una estructura ACIS.
	this->Print("    > hay reconocimiento por flujo de una estructura ACIS con id", this->BUFF_ACIS_RE->STR_ID);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para INIS activada actual.
	in					current_inis_activated_id			= NULL;							//id de la estructura INIS activada actual.
	in					upci_id_current_inis_activated	= NULL;							//id de la upci de la estructura INIS activada actual.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura reconocida.
	in 					rl_index_to_use						= NULL;							//índices de la relación a utilizar de la estructura reconocida.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para evaluaciones de Hilos.
	dou					current_thread_evaluation			= NULL;							//evaluación del Hilo actual.
	dou					recognized_thread_evaluation		= NULL;							//evaluación del Hilo reconocido.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------  
	//buffer para Hilos potenciales.
	deBUFF_STR_IITE		potential_threads;													

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//buffer para datos de estructura ACIS de inicio de Hilos potenciales.
	BUFF_DS_STR_IITE	acis_data;																		

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de tiempo de espera para la espera de una nueva entrada.
	chrono::milliseconds timeout_loop_very_fast(TIMEOUT_LOOP_VERY_FAST);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//################# INICIO DE INTEGRACIÓN DE HILOS POTENCIALES ####################		

	//---------------------------------------------------------------------------------
	//seteo de los datos de la estructura INIS activada actual.
	current_inis_activated_id				= this->BUFF_INIS_ACTIVATED[0].STR_ID;
	upci_id_current_inis_activated		= this->BUFF_INIS_ACTIVATED[0].UPCI_ID;

	//---------------------------------------------------------------------------------
	//obtención de la evaluación de Hilo actual.
	current_thread_evaluation				= this->BUFF_UPCI->at(upci_id_current_inis_activated).BUFF_INIS[current_inis_activated_id].EV_RG;

	//---------------------------------------------------------------------------------
	//obtención del índice de la relación saliente a utilizar si existe.
	rl_index_to_use = this->BUFF_ACIS[this->BUFF_ACIS_RE->STR_ID].GetNextOutputRelationS(*this->BUFF_RL_INDEX_USED_IN_RECOGNITION);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existe una relación saliente para obtener Hilo potenciales, entonces.
	if (rl_index_to_use != -1)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//carga de la estructura inicial.
		acis_data.Set(this->BUFF_ACIS_RE->UPCI_ID,
					    this->BUFF_ACIS_RE->STR_ID, 
					    ACIS_TYPE, 
					    current_thread_evaluation,
					    current_thread_evaluation,
					    1);
		
		//-----------------------------------------------------------------------------
		//carga de la estructura inicial en buffer del Hilo reconocido i1.
		potential_threads.push_back(acis_data);

		//-----------------------------------------------------------------------------
		//obtención del Hilo pontencial.
		this->GetPotentialThreadsACIS(this->BUFF_ACIS_RE->STR_ID, rl_index_to_use, &potential_threads);
		
		//-----------------------------------------------------------------------------
		//obtención de la evaluación del Hilo reconocido.
		recognized_thread_evaluation	= potential_threads.back().MAX_EV;
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la evaluación del Hilo reconocido es superior al Hilo actual, entonces.
		if(recognized_thread_evaluation > current_thread_evaluation)
		{
			//-------------------------------------------------------------------------
			//lectura del Hilo reconocido.
			this->winningThreadIntegration(&potential_threads, current_thread_evaluation, _output_action);

		}	

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la bandera de lectura del Hilo reconocido no está activada, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//ejecución de la acción.
			this->OutputEstructure(this->BUFF_ACIS_RE->STR_ID, _output_action);
		}
	}		

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si no existe una relación saliente para obtener Hilo potenciales, entonces.
	else
	{
		//-----------------------------------------------------------------------------
		//ejecución de la acción.
		this->OutputEstructure(this->BUFF_ACIS_RE->STR_ID, _output_action);
	}*/
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------  
//-------------------------------------------------------------------------------------   
//#1: método para obtener acciones potenciales por INIS.
vo	UPCI_SDS::GetPotentialActionsINIS(in _inis_id, in _rl_index_to_use, BUFF_STR_IIE *_potential_action)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las relaciones de la estructura siguiente.
	in	upci_id_rl_next	= NULL;																//id de la upci de la relación de la estructura siguiente
	in	rl_next_id		= NULL;																//id de la relación de la estructura siguiente									
	in	rl_next_type	= NULL;																//tipo de relación de la estructura siguiente

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para la estructura auxiliar.
	in	upci_id_str_aux	= NULL;																//id de la upci de la estructura auxiliar.
	in	str_aux_id		= NULL;																//id de la estructura auxiliar.
	in	str_aux_type	= NULL;																//tipo de estructura auxiliar.

	//---------------------------------------------------------------------------------
	//obtención de datos de la relación de la estructura siguiente.
	rl_next_type		= this->BUFF_INIS[_inis_id].RL.at(_rl_index_to_use).at(0);
	rl_next_id			= this->BUFF_INIS[_inis_id].RL.at(_rl_index_to_use).at(1);
	upci_id_rl_next		= this->BUFF_INIS[_inis_id].RL.at(_rl_index_to_use).at(2);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la relación es del tipo flujo puro, entonces.
	if (rl_next_type == PFRLIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//reactivación de la relación de flujo puro a utilizar.
		this->BUFF_UPCI->at(upci_id_rl_next).ReactivePFRLIS(rl_next_id);
		
		//-----------------------------------------------------------------------------
		//siguiente lectura del Hilo reconocido por medio de PFRLIS.
		this->BUFF_UPCI->at(upci_id_rl_next).GetPotentialActionsPFRLIS(rl_next_id, _potential_action);
	}	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la relación es del tipo diferencial de entrada, entonces.
	else if (rl_next_type == INDFRLIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//obtención de datos de la relación INDFRLIS.
		upci_id_str_aux	= this->BUFF_UPCI->at(upci_id_rl_next).BUFF_INDFRLIS[rl_next_id].UPCI_ID_STR2_RG;
		str_aux_id		= this->BUFF_UPCI->at(upci_id_rl_next).BUFF_INDFRLIS[rl_next_id].STR2_ID_RG;
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la relación INDFRLIS no es circular, entonces.
		if (_inis_id != str_aux_id || this->UPCI_ID != upci_id_str_aux)
		{
			//-------------------------------------------------------------------------
			//reactivación de la relación diferencial de entrada a utilizar.
			this->BUFF_UPCI->at(upci_id_rl_next).ReactiveINDFRLIS(rl_next_id);

			//-------------------------------------------------------------------------
			//siguiente lectura del Hilo reconocido por medio de INDFRLIS.
			this->BUFF_UPCI->at(upci_id_rl_next).GetPotentialActionsINDFRLIS(rl_next_id, _potential_action);
		}		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la relación INDFRLIS es circular, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//actualización del buffer del Hilo reconocido.
			_potential_action->SetEVALUATION(this->BUFF_INIS[_inis_id].EV_RG);
		}
	}
}

//-------------------------------------------------------------------------------------  
//-------------------------------------------------------------------------------------   
//#2: método para obtener acciones potenciales por PFRLIS.
vo	UPCI_SDS::GetPotentialActionsPFRLIS(in _pfrlis_id, BUFF_STR_IIE *_potential_action)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para la estructura siguiente.
	in	upci_id_str_next	= NULL;															//id de la upci de la estructura siguiente.
	in	str_next_id			= NULL;															//id de la estructura siguiente.
	in	str_next_type		= NULL;															//tipo de estructura siguiente.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para índices de relaciones en siguiente estructura.
	in	rl_index_in_str		= NULL;															//índice de la relación entrante en estructura siguiente.
	in	rl_index_to_use		= NULL;															//índice de la relación a utilizar en siguiente estructura.

	//---------------------------------------------------------------------------------
	//obtención de datos de la relación de flujo puro.
	upci_id_str_next		= this->BUFF_PFRLIS[_pfrlis_id].UPCI_ID_STR2_RG;
	str_next_id				= this->BUFF_PFRLIS[_pfrlis_id].STR2_ID_RG;
	str_next_type			= this->BUFF_PFRLIS[_pfrlis_id].STR2_TYPE_RG;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura siguiente es del tipo entrada, entonces.
	if (str_next_type == INIS_TYPE)
	{	
		//-----------------------------------------------------------------------------
		//reactivación de la estructura de entrada a utilizar.
		this->BUFF_UPCI->at(upci_id_str_next).ReactiveINIS(str_next_id);

		//---------------------------------------------------------------------------------
		//seteo de la evaluación del Hilo reconocido.
		_potential_action->SetEVALUATION(this->BUFF_UPCI->at(upci_id_str_next).BUFF_INIS[str_next_id].EV_RG);	
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura siguiente es del tipo acción, entonces.
	else if (str_next_type == ACIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//obtención del índice de la relación utilizada en estructura ACIS.
		rl_index_in_str	= this->BUFF_UPCI->at(upci_id_str_next).BUFF_ACIS[str_next_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);

		//-----------------------------------------------------------------------------
		//obtenención del índice de la relación a utilizar en ACIS.
		rl_index_to_use	= this->BUFF_UPCI->at(upci_id_str_next).BUFF_ACIS[str_next_id].GetNextOutputRelationS(rl_index_in_str);

		//-----------------------------------------------------------------------------
		//reactivación de la estructura de acción a utilizar.
		this->BUFF_UPCI->at(upci_id_str_next).ReactiveACIS(str_next_id);

		//-----------------------------------------------------------------------------
		//seteo de la estructura ACIS en buffer de Hilo reconocido.
		_potential_action->SetUPCI_ID(upci_id_str_next);
		_potential_action->SetSTR_ID(str_next_id);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existe una relación a utilizar en la siguiente relación, entonces.
		if (rl_index_to_use != -1)
		{
			//-------------------------------------------------------------------------
			//siguiente lectura del Hilo reconocido por medio de ACIS.
			this->BUFF_UPCI->at(upci_id_str_next).GetPotentialActionsACIS(str_next_id, rl_index_to_use, _potential_action);
		}
	}
}

//-------------------------------------------------------------------------------------  
//-------------------------------------------------------------------------------------   
//#3: método para obtener acciones potenciales por INDFRLIS.
vo	UPCI_SDS::GetPotentialActionsINDFRLIS(in _indfrlis_id, BUFF_STR_IIE *_potential_action)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para la estructura siguiente.
	in	upci_id_str_next	= NULL;															//id de la upci de la estructura siguiente.
	in	str_next_id			= NULL;															//id de la estructura siguiente.

	//---------------------------------------------------------------------------------
	//obtención de datos de la relación diferencial de entrada.
	upci_id_str_next		= this->BUFF_INDFRLIS[_indfrlis_id].UPCI_ID_STR2_RG;
	str_next_id				= this->BUFF_INDFRLIS[_indfrlis_id].STR2_ID_RG;
	
	//---------------------------------------------------------------------------------
	//reactivación de la estructura de entrada a utilizar.
	this->BUFF_UPCI->at(upci_id_str_next).ReactiveINIS(str_next_id);

	//---------------------------------------------------------------------------------
	//seteo de la evaluación del Hilo reconocido.
	_potential_action->SetEVALUATION(this->BUFF_UPCI->at(upci_id_str_next).BUFF_INIS[str_next_id].EV_RG);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------  
//-------------------------------------------------------------------------------------
//#1: método para obtener índice de la acción potencial ganadora.
in	UPCI_SDS::GetWinningPotentialActionIndex(dou _input_evaluation, deBUFF_STR_IIE &_potential_actions)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para cantidad de acciones potenciales.
	in	potentital_actions_amount			= NULL;										

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para evaluación máxima de acciones potenciales.										
	dou	max_evaluation						= NULL;		

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para id de la acción potencial máxima.
	in	maximun_potential_action_index		= -1;																							

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de acciones potenciales.
	potentital_actions_amount	= in(_potential_actions.size());			
	
	//---------------------------------------------------------------------------------
	//inicialización de la evaluación máxima de las acciones potenciales.
	max_evaluation				= _input_evaluation + this->TRANSITION_EVALUATION_THRESHOLD;
	//cout << "potentital_actions_amount: " << potentital_actions_amount << endl;
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para hallar acciones potenciales máximas.
	for (in i1 = 0; i1 < potentital_actions_amount; i1++)
	{
		//if (_potential_actions.at(i1).GetSTR_ID() == -1)	cout << ">>>> accion: nada" << endl;
		//else												cout << ">>>> accion: " << this->BUFF_UPCI->at(_potential_actions.at(i1).GetUPCI_ID()).BUFF_ACIS[_potential_actions.at(i1).GetSTR_ID()].AC_RG << endl;
		//cout << "_input_evaluation + this->TRANSITION_EVALUATION_THRESHOLD: " << _input_evaluation + this->TRANSITION_EVALUATION_THRESHOLD << endl;
		//cout << "_potential_actions.at(" << i1 << ").GetEVALUATION(): " << _potential_actions.at(i1).GetEVALUATION() << endl;		
		
		//-----------------------------------------------------------------------------
		//si existe una nueva acción potencial máxima, entonces.
		if (_potential_actions.at(i1).GetEVALUATION() > max_evaluation)
		{
			//if (_potential_actions.at(i1).GetSTR_ID() == -1)	cout << "$$$$ accion: nada" << endl;
			//else												cout << "$$$$ accion: " << this->BUFF_UPCI->at(_potential_actions.at(i1).GetUPCI_ID()).BUFF_ACIS[_potential_actions.at(i1).GetSTR_ID()].AC_RG << endl;;
			
			//-------------------------------------------------------------------------
			//seteo de la nueva acción potencial máxima.
			maximun_potential_action_index = i1;

			//-------------------------------------------------------------------------
			//actualización de la evaluación máxima.
			max_evaluation = _potential_actions.at(i1).GetEVALUATION();
		}	
	}

	//---------------------------------------------------------------------
	//retorno del índice de la acción potencial ganadora.
	return maximun_potential_action_index;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para obtener estructura INIS causal de una entrada.
vo	UPCI_SDS::GetCausalEstructure(in _inis_id, in & _causal_inis_id, in &_upci_id_causal_inis)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las relaciones de _inis_id.
	in	upci_id_rl				= NULL;														//id de la upci de la relación de _inis_id.
	in	rl_type					= NULL;														//tipo de relación de _inis_id.
	in	rl_id					= NULL;														//id de la relación de _inis_id.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para el tipo de estructura de inicio de la relación PFRLIS.
	in  rl_str1_type			= NULL;													

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para la estructura INIS causal.
	in	upci_id_causal_acis_aux	= NULL;														//id auxiliar de la upci de la estructura INIS causal. 
	in	causal_acis_id_aux		= NULL;														//id auxiliar de la estructura INIS causal. 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para cantidad de relaciones.
	in rl_amount				= NULL;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//contador de relaciones INDFRLIS.
	in indfrlis_counter			= 0;

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de relaciones de _inis_id.
	rl_amount					= this->BUFF_INIS[_inis_id].GetRelationAmount();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para hallar la estructura INIS causal por medio de _inis_id.
	for (in i1 = rl_amount - 1; i1 >= 0; i1--)
	{
		//-----------------------------------------------------------------------------
		//obtención de los datos de la relación de _inis_id.
		rl_type		= this->BUFF_INIS[_inis_id].RL.at(i1).at(0);
		rl_id		= this->BUFF_INIS[_inis_id].RL.at(i1).at(1);
		upci_id_rl	= this->BUFF_INIS[_inis_id].RL.at(i1).at(2);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la relación es del tipo INDFRLIS, entonces.
		if (abs(rl_type) == INDFRLIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//incremento del contador de INDFRLIS.
			++indfrlis_counter;

			//-------------------------------------------------------------------------
			//si existen dos relaciones INDFRLIS seguidas, entonces salir.
			if (indfrlis_counter == 2)	return;
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la relación no es del tipo INDFRLIS, reSetear contador de INDFRLIS.
		else	indfrlis_counter = 0;		
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la relación del tipo flujo puro entrante.
		if (rl_type == -PFRLIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//reactivación de la relación de flujo puro a utilizar.
			this->BUFF_UPCI->at(upci_id_rl).ReactivePFRLIS(rl_id);

			//-------------------------------------------------------------------------
			//obtención del tipo de estructura de inicio de la relación.
			rl_str1_type = this->BUFF_UPCI->at(upci_id_rl).BUFF_PFRLIS[rl_id].STR1_TYPE_RG;
			
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la estructura es del tipo acción.
			if (rl_str1_type == ACIS_TYPE)
			{
				//---------------------------------------------------------------------
				//obtención de los datos de la estructura INIS causal.
				upci_id_causal_acis_aux	= this->BUFF_UPCI->at(upci_id_rl).BUFF_PFRLIS[rl_id].UPCI_ID_STR1_RG;;
				causal_acis_id_aux		= this->BUFF_UPCI->at(upci_id_rl).BUFF_PFRLIS[rl_id].STR1_ID_RG;

				//---------------------------------------------------------------------
				//si la estructura INIS causal está suspendida.
				if (this->BUFF_UPCI->at(upci_id_causal_acis_aux).BUFF_ACIS[causal_acis_id_aux].AL_SRG > 0)
				{
					//-----------------------------------------------------------------
					//seteo de los datos de la estructura INIS causal.
					_upci_id_causal_inis	= upci_id_causal_acis_aux;
					_causal_inis_id			= causal_acis_id_aux;

					//-----------------------------------------------------------------
					//salida del bucle.
					break;
				}				
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la estructura no es del tipo acción.
			else return;
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para obtener la acción suspendida con la mejor evaluación.
vo	UPCI_SDS::GetWinningSuspendedAction(in &_winning_sus_acis_id, in &_upci_id_winning_sus_acis)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la bandera para utilizar reactivación acción suspendida con máxima asociación 
	//positiva está desactivada, entonces.
	if (this->GetSUSPENDED_ACTIONS_MAXIMIZATION_FLAG() == OFF)	return;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las estructuras ACIS suspendidas.
	in				upci_id_sus_acis				= NULL;									//id de la upci de estructura ACIS suspendida.
	in				sus_acis_id						= NULL;									//id de la estructura ACIS suspendida.
	dou				sus_acis_evaluation				= 0;									//evaluación de la estructura ACIS suspendida.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura ACIS ganadora.
	in				upci_id_winning_sus_acis		= NULL;									//id de la upci de estructura ACIS suspendida con máxima evaluación.
	in				winning_sus_acis_id				= NULL;									//id de la estructura ACIS suspendida con máxima evaluación.
	dou				winning_sus_acis_evaluation		= 0;									//evaluación de la estructura ACIS suspendida con máxima evaluación.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para la cantidad de estructuras ACIS suspendidas.
	in				acis_suspended_amount			= NULL;									//cantidad de estructuras ACIS suspendidas del buffer original.
	in				acis_suspended_amount_aux		= NULL;									//cantidad de estructuras ACIS suspendidas del buffer auxiliar.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliares para bandera de acción admisible.
	in				admissible_action_flag			= NULL;											

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de estructuras ACIS suspendidas del buffer original.
	acis_suspended_amount = in(this->BUFF_ACIS_SUS->size());
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existen estructuras de acción suspendidas candidatas, entonces.
	if (acis_suspended_amount > 0)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//inicialización del la estructura de acción suspendida ganadora.
		upci_id_winning_sus_acis	= this->BUFF_ACIS_SUS->at(0).UPCI_ID;
		winning_sus_acis_id			= this->BUFF_ACIS_SUS->at(0).STR_ID;
		winning_sus_acis_evaluation	= this->BUFF_UPCI->at(upci_id_winning_sus_acis).GetActionEvaluation(winning_sus_acis_id);		
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para hallar la estructura ACIS con mejor evaluación.
		for (in i1 = 1; i1 < acis_suspended_amount; i1++)
		{
			//-------------------------------------------------------------------------
			//obtención de datos de estructura ACIS suspendida.
			upci_id_sus_acis	= this->BUFF_ACIS_SUS->at(i1).UPCI_ID;
			sus_acis_id			= this->BUFF_ACIS_SUS->at(i1).STR_ID;
			sus_acis_evaluation	= this->BUFF_UPCI->at(upci_id_sus_acis).GetActionEvaluation(sus_acis_id);

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la evaluación de la estructura ACIS suspendida i1 es superior. 
			if (sus_acis_evaluation > winning_sus_acis_evaluation)
			{
				//---------------------------------------------------------------------
				//reset de la estructura ACIS ganadora.
				upci_id_winning_sus_acis	= upci_id_sus_acis;
				winning_sus_acis_id			= sus_acis_id;
				winning_sus_acis_evaluation	= sus_acis_evaluation;
			}
		}
	
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la evaluación ganadora es mayor que el umbral de transición, entonces.
		if (winning_sus_acis_evaluation > this->TRANSITION_EVALUATION_THRESHOLD)
		{
			//-------------------------------------------------------------------------
			//seteo de la estructura ACIS ganadora.
			_winning_sus_acis_id		= winning_sus_acis_id;
			_upci_id_winning_sus_acis	= upci_id_winning_sus_acis;
			//cout << "#accion ganadora: " << this->BUFF_UPCI->at(upci_id_winning_sus_acis).BUFF_ACIS[winning_sus_acis_id].AC_RG << endl;
		}	
	}	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para obtener la evaluación una estructura ACIS en función de sus relaciones.
dou UPCI_SDS::GetActionEvaluation(in _acis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las relaciones de _acis_id.
	in	upci_id_rl_acis				= NULL;													//id de la upci de la relación de _acis_id.
	in	rl_id_acis					= NULL;													//id de la relación de _acis_id.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura final de una relación PFRLIS saliente.
	in	upci_id_str2_pfrlis			= NULL;													//id de la upci de una estructura final de la relación PFRLIS saliente.
	in	str2_id_pfrlis				= NULL;													//id de una estructura final de la relación PFRLIS saliente.
	in	str2_type_pfrlis			= NULL;													//tipo de estructura final de la relación PFRLIS saliente.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las relaciones de la estructura de entrada hallada.
	in	upci_id_rl_inis				= NULL;													//id de la upci de la relación de la estructura de entrada hallada.
	in  rl_type_inis				= NULL;													//tipo de relación de la estructura de entrada hallada.
	in	rl_id_inis					= NULL;													//id de la relación de la estructura de entrada hallada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para índice de relación a utilizar.
	in rl_index_acis				= NULL;													//índice de relación para _acis_id.
	in rl_index_inis				= NULL;													//índice de relación para inis hallada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para evaluaciones de entradas.
	dou	input_evaluation			= NULL;													//buffer para evaluación de entradas.
	dou	input_evaluation_difference	= NULL;													//buffer para diferencia de evaluación de entradas.
	in	evaluation_transition_type	= NULL;													//tipo de evaluación de transición de entradas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para evaluación de la estructura _acis_id.
	dou acis_evaluation				= 0;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para cantidad de relaciones.
	in rl_amount					= NULL;

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de relaciones de la estructura _acis_id.
	rl_amount						= this->BUFF_ACIS[_acis_id].GetRelationAmount();

	//---------------------------------------------------------------------------------
	//inicialización del índice de relación de _acis_id.
	rl_index_acis					= rl_amount - 1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para hallar estructuras INIS para obtener evaluaciones de _acis_id.
	while (true)
	{
		//-----------------------------------------------------------------------------
		//obtención del índice de una relación saliente previa.
		rl_index_acis		= this->BUFF_ACIS[_acis_id].GetPreviousOutputRelationS(rl_index_acis);
		
		//-----------------------------------------------------------------------------
		//si ya no existen más relaciones salientes, entonces retornar evaluación.
		if(rl_index_acis == -1)	return acis_evaluation;

		//-----------------------------------------------------------------------------
		//obtención de datos de la relación de _acis_id.
		rl_id_acis		= this->BUFF_ACIS[_acis_id].RL.at(rl_index_acis).at(1);
		upci_id_rl_acis	= this->BUFF_ACIS[_acis_id].RL.at(rl_index_acis).at(2);

		//-----------------------------------------------------------------------------
		//reactivación de la relación de flujo puro a utilizar.
		this->BUFF_UPCI->at(upci_id_rl_acis).ReactivePFRLIS(rl_id_acis);

		//-----------------------------------------------------------------------------
		//obtención del tipo de estructura final de la relación PFRLIS.
		str2_type_pfrlis	= this->BUFF_UPCI->at(upci_id_rl_acis).BUFF_PFRLIS[rl_id_acis].STR2_TYPE_RG;
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura final es el tipo entrada, entonces.
		if (str2_type_pfrlis == INIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//obtención de los datos faltantes de la estructura de entrada.
			upci_id_str2_pfrlis = this->BUFF_UPCI->at(upci_id_rl_acis).BUFF_PFRLIS[rl_id_acis].UPCI_ID_STR2_RG;
			str2_id_pfrlis		= this->BUFF_UPCI->at(upci_id_rl_acis).BUFF_PFRLIS[rl_id_acis].STR2_ID_RG;

			//-------------------------------------------------------------------------
			//obtención del índice de la relación entrante PFRLIS en INIS hallada.
			rl_index_inis		= this->BUFF_UPCI->at(upci_id_str2_pfrlis).BUFF_INIS[str2_id_pfrlis].GetRelationIndex(PFRLIS_TYPE, rl_id_acis, upci_id_rl_acis);
			
			//-------------------------------------------------------------------------
			//obtención de los datos de la relación de la estructura INIS hallada.
			rl_type_inis		= this->BUFF_UPCI->at(upci_id_str2_pfrlis).BUFF_INIS[str2_id_pfrlis].RL.at(rl_index_inis + 1).at(0);
			rl_id_inis			= this->BUFF_UPCI->at(upci_id_str2_pfrlis).BUFF_INIS[str2_id_pfrlis].RL.at(rl_index_inis + 1).at(1);
			upci_id_rl_inis		= this->BUFF_UPCI->at(upci_id_str2_pfrlis).BUFF_INIS[str2_id_pfrlis].RL.at(rl_index_inis + 1).at(2);
			
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la relación hallada en la estructura de entrada es del tipo INDFRLIS, entonces.
			if (rl_type_inis == -INDFRLIS_TYPE)
			{
				//---------------------------------------------------------------------
				//obtención de la evaluación de la entrada.
				input_evaluation			= this->BUFF_UPCI->at(upci_id_str2_pfrlis).BUFF_INIS[str2_id_pfrlis].EV_RG;

				//---------------------------------------------------------------------
				//obtención de la diferencia de las evaluaciones de entradas.
				input_evaluation_difference = this->BUFF_UPCI->at(upci_id_rl_inis).BUFF_INDFRLIS[rl_id_inis].EV_DIF_RG;

				//---------------------------------------------------------------------
				//obtención del tipo de transición de entradas.
				evaluation_transition_type	= this->GetInputTransitionEvaluationTypeIn(input_evaluation, input_evaluation_difference);

				//---------------------------------------------------------------------
				//si la evaluación es negativa, entonces.
				//if (evaluation_transition_type == NEGATIVE_TRANSITION)	return -1;

				//---------------------------------------------------------------------
				//si la evaluación es postiva, entonces.
				if (evaluation_transition_type == POSITIVE_TRANSITION) acis_evaluation += input_evaluation_difference;
			}
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método para ordenar ejecución de una proyección.
vo	UPCI_SDS::OutputEstructure(in _inis_id)
{
	//---------------------------------------------------------------------------------
	//limpieza de buffer de estructura de salida.
	*this->BUFF_OUTPUT_PROJECTION = NULL;

	//---------------------------------------------------------------------------------
	//escritura en buffer de salida.
	*this->BUFF_OUTPUT_PROJECTION = this->BUFF_INIS[_inis_id].IN_RG;

	//---------------------------------------------------------------------------------
	//impresión de la acción efectuada.
	this->Print("    > se ejecuta inis pro id   ", _inis_id);
	this->Print("    > con el registro          ", *this->BUFF_OUTPUT_PROJECTION);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para crear estructura entrada INIS.
vo	UPCI_SDS::CreateINIS(dou *_in_rg, dou _ev_rg, coin _rs_srg)
{	
	//---------------------------------------------------------------------------------
	//bloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.lock();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares
	in	created_id	= this->BUFF_INIS_ID_AV[0];												//id de estructura creado.
	dou	al_srg		= this->ActivityLevelFunction(_ev_rg);									//nivel de actividad.

	//---------------------------------------------------------------------------------
	//creación de la estructura.
	this->BUFF_INIS[created_id].Create(*_in_rg, _ev_rg, _rs_srg, al_srg);

	//---------------------------------------------------------------------------------
	//actualización de buffers después de la creación de la estructura INIS.
	this->UpdateBuffersAfterCreatingINIS(created_id, al_srg);
	
	//---------------------------------------------------------------------------------
	//relacionamiento de la estructura INIS creada.
	this->RelateINIS_CR(created_id);

	//---------------------------------------------------------------------------------
	//desbloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.unlock();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para crear estructura de relación PFRLIS.
vo	UPCI_SDS::CreatePFRLIS(in _str1_type, in _str2_type, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2)
{
	//---------------------------------------------------------------------------------
	//si existe una misma relación anterior, entonces salir.
	if (this->CheckPreviousPFRLIS(_str1_type, _str2_type, _str1_id, _str2_id, _upci_id_str1, _upci_id_str2) == ON) return;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	UPCI_SDS	*upci_ptr1		= &this->BUFF_UPCI->at(_upci_id_str1);						//puntero a upci de la estructura 1.
	UPCI_SDS	*upci_ptr2		= &this->BUFF_UPCI->at(_upci_id_str2);						//puntero a upci de la estructura 2.
	in			created_id		= this->BUFF_PFRLIS_ID_AV[0];								//id de estructura creado.
	dou			rs_srg			= 1;														//fuerza de relación inicial.
	dou			al_srg			= NULL;														//nivel de actividad para la relación pfrlis.
	dou			al_srg_str1		= NULL;														//nivel de actividad de la estructura 1.
	dou			al_srg_str2		= NULL;														//nivel de actividad de la estructura 2.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del nivel de actividad de la primera estructura.
	if		(_str1_type == INIS_TYPE)		al_srg_str1 = upci_ptr1->BUFF_INIS[_str1_id].AL_SRG;
	else if (_str1_type == INDFRLIS_TYPE)	al_srg_str1 = upci_ptr1->BUFF_INDFRLIS[_str1_id].AL_SRG;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del nivel de actividad de la segunda estructura.
	if		(_str2_type == INIS_TYPE)		al_srg_str2 = upci_ptr2->BUFF_INIS[_str2_id].AL_SRG;
	else if (_str2_type == INDFRLIS_TYPE)	al_srg_str2 = upci_ptr2->BUFF_INDFRLIS[_str2_id].AL_SRG;
	
	//---------------------------------------------------------------------------------
	//seteo del nivel de actividad.
	if (al_srg_str1 >= al_srg_str2)	al_srg = al_srg_str1;
	else							al_srg = al_srg_str2;
	
	//---------------------------------------------------------------------------------
	//creación de la estructura relación.
	this->BUFF_PFRLIS[created_id].Create(_str1_type, _str2_type, _str1_id, _str2_id, _upci_id_str1, _upci_id_str2, rs_srg, al_srg);
	
	//---------------------------------------------------------------------------------
	//actualización después de la creación de la estructura PFRLIS.
	this->UpdateBuffersAfterCreatingPFRLIS(created_id);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de la relación creada en la primera estructura relacionada.
	if		(_str1_type == INIS_TYPE)		upci_ptr1->BUFF_INIS[_str1_id].CreateRelation(PFRLIS_TYPE, created_id, this->UPCI_ID);
	else if (_str1_type == INDFRLIS_TYPE)	upci_ptr1->BUFF_INDFRLIS[_str1_id].CreateRelation(PFRLIS_TYPE, created_id, this->UPCI_ID);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de la relación creada en la segunda estructura relacionada.
	if		(_str2_type == INIS_TYPE)		upci_ptr2->BUFF_INIS[_str2_id].CreateRelation(-PFRLIS_TYPE, created_id, this->UPCI_ID);
	else if (_str2_type == INDFRLIS_TYPE)	upci_ptr2->BUFF_INDFRLIS[_str2_id].CreateRelation(-PFRLIS_TYPE, created_id, this->UPCI_ID);
	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para crear estructura de relación INDFRLIS.
vo	UPCI_SDS::CreateINDFRLIS(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2)
{
	//---------------------------------------------------------------------------------
	//si existe una misma relación anterior, entonces salir.
	if (this->CheckPreviousINDFRLIS(_str1_id, _str2_id, _upci_id_str1, _upci_id_str2) == ON) return;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	UPCI_SDS	*upci_ptr1				= &this->BUFF_UPCI->at(_upci_id_str1);				//puntero a upci de la estructura 1.
	UPCI_SDS	*upci_ptr2				= &this->BUFF_UPCI->at(_upci_id_str2);				//puntero a upci de la estructura 2.
	in			created_id				= this->BUFF_INDFRLIS_ID_AV[0];						//id de estructura creado.
	dou			difference_inputs		= NULL;												//diferencia de entradas.
	dou			diff_input_evaluations	= NULL;												//diferencia de evaluaciones.
	dou			rs_srg					= 1;												//fuerza de relación inicial.
	dou			al_srg					= NULL;												//nivel de actividad.

	//---------------------------------------------------------------------------------
	//diferencia de registros de entrada de las estructuras relacionadas.
	difference_inputs		= upci_ptr2->BUFF_INIS[_str2_id].IN_RG - upci_ptr1->BUFF_INIS[_str1_id].IN_RG;
	
	//---------------------------------------------------------------------------------
	//diferencia de registros de evaluación de las estructuras relacionadas.
	diff_input_evaluations	= upci_ptr2->BUFF_INIS[_str2_id].EV_RG - upci_ptr1->BUFF_INIS[_str1_id].EV_RG;

	//---------------------------------------------------------------------------------
	//seteo del nivel de actividad.
	if (upci_ptr1->BUFF_INIS[_str1_id].AL_SRG >= upci_ptr2->BUFF_INIS[_str2_id].AL_SRG)	al_srg = upci_ptr1->BUFF_INIS[_str1_id].AL_SRG;
	else																				al_srg = upci_ptr2->BUFF_INIS[_str2_id].AL_SRG;

	//---------------------------------------------------------------------------------
	//seteo del registro de diferencia de entradas.
	*this->BUFF_IN_DIF_RG	= difference_inputs;

	//---------------------------------------------------------------------------------
	//diferenciación global de la estructura INDFRLIS.
	this->GlobalDifferentiationINDFRLIS();
	
	//---------------------------------------------------------------------------------
	//creación de la estructura relación.
	this->BUFF_INDFRLIS[created_id].Create(difference_inputs, diff_input_evaluations, _str1_id, _str2_id, _upci_id_str1, _upci_id_str2, rs_srg, al_srg);
	
	//---------------------------------------------------------------------------------
	//actualización después de la creación de la estructura INDFRLIS.
	this->UpdateBuffersAfterCreatingINDFRLIS(created_id);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la primera y segunda estructura INIS son las mismas, entonces.
	if (_str1_id == _str2_id && _upci_id_str1 == _upci_id_str2)
	{
		//-----------------------------------------------------------------------------
		//seteo de la relación creada en las estructuras relacionadas.
		upci_ptr1->BUFF_INIS[_str1_id].CreateRelation(INDFRLIS_TYPE, created_id, this->UPCI_ID);
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la primera y segunda estructura INIS no son las mismas, entonces.
	else
	{
		//-----------------------------------------------------------------------------
		//seteo de la relación creada en las estructuras relacionadas.
		upci_ptr1->BUFF_INIS[_str1_id].CreateRelation(INDFRLIS_TYPE, created_id, this->UPCI_ID);
		upci_ptr2->BUFF_INIS[_str2_id].CreateRelation(-INDFRLIS_TYPE, created_id, this->UPCI_ID);
	}		

	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera de alerta de la creación de INDFRLIS.
	this->SetNEW_INPUT_DIFFERENCE_RELATION_FLAG(ON);
	
	//---------------------------------------------------------------------------------
	//relacionamiento de la estructura INDFRLIS creada.
	this->RelateINDFRLIS(created_id);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para crear estructura de relación INPRRLIS.
vo	UPCI_SDS::CreateINPRRLIS(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2)
{
	//---------------------------------------------------------------------------------
	//si existe una misma relación anterior, entonces salir.
	if (this->CheckPreviousINPRRLIS(_str1_id, _str2_id, _upci_id_str1, _upci_id_str2) == ON) return;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	UPCI_SDS	*upci_ptr1			= &this->BUFF_UPCI->at(_upci_id_str1);					//puntero a upci de la estructura 1.
	UPCI_SDS	*upci_ptr2			= &this->BUFF_UPCI->at(_upci_id_str2);					//puntero a upci de la estructura 2.
	in			created_id			= this->BUFF_INPRRLIS_ID_AV[0];							//id de estructura creado.
	dou			proportion_inputs	= NULL;													//proporción de entradas.

	//---------------------------------------------------------------------------------
	//proporción de registros de diferencia de entradas de las estructuras relacionadas.
	proportion_inputs = upci_ptr2->BUFF_INDFRLIS[_str2_id].IN_DIF_RG / upci_ptr1->BUFF_INDFRLIS[_str1_id].IN_DIF_RG;

	//---------------------------------------------------------------------------------
	//seteo del registro de proporción de diferencias de entradas.
	*this->BUFF_IN_PRO_RG = proportion_inputs;

	//---------------------------------------------------------------------------------
	//diferenciación global de la estructura INPRRLIS creada.
	this->GlobalDifferentiationINPRRLIS();

	//---------------------------------------------------------------------------------
	//creación de la estructura relación.
	this->BUFF_INPRRLIS[created_id].Create(proportion_inputs, _str1_id, _str2_id, _upci_id_str1, _upci_id_str2);

	//---------------------------------------------------------------------------------
	//actualización después de la creación de la estructura INPRRLIS.
	this->UpdateBuffersAfterCreatingINPRRLIS(created_id);

	//---------------------------------------------------------------------------------
	//seteo de la relación creada en las estructuras relacionadas.
	upci_ptr1->BUFF_INDFRLIS[_str1_id].CreateRelation(INPRRLIS_TYPE, created_id, this->UPCI_ID);
	upci_ptr2->BUFF_INDFRLIS[_str2_id].CreateRelation(-INPRRLIS_TYPE, created_id, this->UPCI_ID);	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para Delete estructura INIS.
vo	UPCI_SDS::DeleteINIS(in _inis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	in			rl_type			=	NULL;													//tipo de relación.
	in			rl_id			=	NULL;													//id de la relación.
	UPCI_SDS	*upci_ptr_rl	=	NULL;													//puntero de la upci de la relación.
	in			rl_amount		=	NULL;													//cantidad de relaciones.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//actualización de buffers para la eliminación de la IS.	
	this->UpdateBuffersToDeleteINIS(_inis_id);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//obtención de la cantidad de relaciones de _inis_id.
	rl_amount	= this->BUFF_INIS[_inis_id].GetRelationAmount();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para Delete estructuras de relación de la estructura de entrada _inis_id.
	for (in i1 = 0; i1 < rl_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención de los datos de la relación de la estructura _inis_id.
		rl_type			= abs(this->BUFF_INIS[_inis_id].RL.at(i1).at(0));
		rl_id			= this->BUFF_INIS[_inis_id].RL.at(i1).at(1);
		upci_ptr_rl		= &this->BUFF_UPCI->at(this->BUFF_INIS[_inis_id].RL.at(i1).at(2));
		
		//-----------------------------------------------------------------------------
		//búsqueda del tipo de relación rl_type a eliminar.
		switch (rl_type)
		{
			//-------------------------------------------------------------------------
			//si la estructura es del tipo relación de flujo puro.
			case	PFRLIS_TYPE:	
				upci_ptr_rl->DeletePFRLIS(rl_id, INIS_TYPE, _inis_id, this->UPCI_ID);
				break;

			//-------------------------------------------------------------------------
			//si la estructura es del tipo relación diferencial de entradas.
			case	INDFRLIS_TYPE:
				upci_ptr_rl->DeleteINDFRLIS(rl_id, _inis_id, this->UPCI_ID);
				break;

			//-------------------------------------------------------------------------
			//si no cumple con ninguna condición.
			default:
				break;
		}
	}	
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//eliminación de memoria la estructura _inis_id.
	this->BUFF_INIS[_inis_id].Clean();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para Delete estructura PFRLIS.
vo	UPCI_SDS::DeletePFRLIS(in _pfrlis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las estructuras relacionadas.
	UPCI_SDS	*upci_ptr_str1		=	NULL;												//puntero de la upci de la estructura relacionada 1.
	UPCI_SDS	*upci_ptr_str2		=	NULL;												//puntero de la upci de la estructura relacionada 2.
	in			str1_id				=	NULL;												//id de la estructura relacionada 1.
	in			str2_id				=	NULL;												//id de la estructura relacionada 2.			
	in			rl_index_in_str		=	NULL;												//índice de la relación en una estructura.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//actualización de buffers para la eliminación de la IS.
	this->UpdateBuffersToDeletePFRLIS(_pfrlis_id);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de los ids de las estructuras relacionadas. 
	str1_id			= this->BUFF_PFRLIS[_pfrlis_id].STR1_ID_RG;
	str2_id			= this->BUFF_PFRLIS[_pfrlis_id].STR2_ID_RG;
	
	//---------------------------------------------------------------------------------  
	//carga de los ids de las upci de las estructuras relacionadas.
	upci_ptr_str1	= &this->BUFF_UPCI->at(this->BUFF_PFRLIS[_pfrlis_id].UPCI_ID_STR1_RG);
	upci_ptr_str2	= &this->BUFF_UPCI->at(this->BUFF_PFRLIS[_pfrlis_id].UPCI_ID_STR2_RG);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//búsqueda del tipo de estructura str1_id.
	switch (this->BUFF_PFRLIS[_pfrlis_id].STR1_TYPE_RG)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//para estructura de entrada.
		case INIS_TYPE:	
			
			//-------------------------------------------------------------------------
			//obtención del índice de la relación en la estructura INIS.
			rl_index_in_str	= upci_ptr_str1->BUFF_INIS[str1_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);
			
			//-------------------------------------------------------------------------
			//eliminación de la relación en str1_id.
			upci_ptr_str1->BUFF_INIS[str1_id].DeleteRelation(rl_index_in_str);
			
			//-------------------------------------------------------------------------
			//si str1_id queda sin relaciones se elimina.
			if (upci_ptr_str1->BUFF_INIS[str1_id].GetRelationAmount() == 0)	upci_ptr_str1->DeleteINIS(str1_id);
			
			//-------------------------------------------------------------------------
			//salida.
			break;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//para estructura de relación de flujo diferencial de entradas.
		case INDFRLIS_TYPE:
			
			//-------------------------------------------------------------------------
			//obtención del índice de la relación en la estructura INDFRLIS.
			rl_index_in_str = upci_ptr_str1->BUFF_INDFRLIS[str1_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);
			
			//-------------------------------------------------------------------------
			//eliminación de la relación en str1_id.
			upci_ptr_str1->BUFF_INDFRLIS[str1_id].DeleteRelation(rl_index_in_str);
			
			//-------------------------------------------------------------------------
			//salida.
			break;
				
		//-----------------------------------------------------------------------------
		//si no cumple con ninguna condición.
		default:
						
			//-------------------------------------------------------------------------
			//salida.
			break;
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//búsqueda del tipo de estructura str2_id.
	switch (this->BUFF_PFRLIS[_pfrlis_id].STR2_TYPE_RG)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//para estructura de entrada.
		case INIS_TYPE		:	
			
			//-------------------------------------------------------------------------
			//obtención del índice de la relación en la estructura INIS.
			rl_index_in_str = upci_ptr_str2->BUFF_INIS[str2_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);
			
			//-------------------------------------------------------------------------
			//eliminación de la relación en str2_id.
			upci_ptr_str2->BUFF_INIS[str2_id].DeleteRelation(rl_index_in_str);
			
			//-------------------------------------------------------------------------
			//si str2_id queda sin relaciones se elimina.
			if (upci_ptr_str2->BUFF_INIS[str2_id].GetRelationAmount() == 0)	upci_ptr_str2->DeleteINIS(str2_id);
			
			//-------------------------------------------------------------------------
			//salida.
			break;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//para estructura de relación de flujo diferencial de entradas.
		case INDFRLIS_TYPE:
			
			//-------------------------------------------------------------------------
			//obtención del índice de la relación en la estructura INDFRLIS.
			rl_index_in_str = upci_ptr_str2->BUFF_INDFRLIS[str2_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);
			
			//-------------------------------------------------------------------------
			//eliminación de la relación en str2_id.
			upci_ptr_str2->BUFF_INDFRLIS[str2_id].DeleteRelation(rl_index_in_str);
			
			//-------------------------------------------------------------------------
			//salida.
			break;
				
		//-----------------------------------------------------------------------------
		//si no cumple con ninguna condición.
		default:
						
			//-------------------------------------------------------------------------
			//salida.
			break;
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//eliminación de la estrucura _pfrlis_id.
	this->BUFF_PFRLIS[_pfrlis_id].Clean();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para Delete estructura INDFRLIS.
vo	UPCI_SDS::DeleteINDFRLIS(in _indfrlis_id)	
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las estructuras relacionadas.
	UPCI_SDS	*upci_ptr_str1		=	NULL;												//puntero de la upci de la estructura relacionada 1.
	UPCI_SDS	*upci_ptr_str2		=	NULL;												//puntero de la upci de la estructura relacionada 2.
	in			str1_id				=	NULL;												//id de la estructura relacionada 1.
	in			str2_id				=	NULL;												//id de la estructura relacionada 2.											
	in			rl_index_in_str		=	NULL;												//índice de la relación en una estructura.
	              
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares de la relación _indfrlis_id.
	in			rl_type				=	NULL;												//tipo de las relaciones de la relación _indfrlis_id.
	in			rl_id				=	NULL;												//id de las relaciones de la relación _indfrlis_id.
	UPCI_SDS	*upci_ptr_rl		=	NULL;												//puntero de la upci de la relación _indfrlis_id.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares generales.
	in			rl_amount			=	NULL;												//cantidad de relaciones.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//actualización de buffers para la eliminación de la IS.
	this->UpdateBuffersToDeleteINDFRLIS(_indfrlis_id);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de los id del registro relacionado. 
	str1_id			= this->BUFF_INDFRLIS[_indfrlis_id].STR1_ID_RG;
	str2_id			= this->BUFF_INDFRLIS[_indfrlis_id].STR2_ID_RG;

	//---------------------------------------------------------------------------------
	//id de upci.
	upci_ptr_str1	= &this->BUFF_UPCI->at(this->BUFF_INDFRLIS[_indfrlis_id].UPCI_ID_STR1_RG);
	upci_ptr_str2	= &this->BUFF_UPCI->at(this->BUFF_INDFRLIS[_indfrlis_id].UPCI_ID_STR2_RG);

	//---------------------------------------------------------------------------------
	//obtención del índice de la relación en la estructura INIS.
	rl_index_in_str = upci_ptr_str1->BUFF_INIS[str1_id].GetRelationIndex(INDFRLIS_TYPE, _indfrlis_id, this->UPCI_ID);

	//---------------------------------------------------------------------------------
	//eliminación de la relación en str1_id.
	upci_ptr_str1->BUFF_INIS[str1_id].DeleteRelation(rl_index_in_str);

	//---------------------------------------------------------------------------------
	//si str1_id queda sin relaciones se elimina.
	if (upci_ptr_str1->BUFF_INIS[str1_id].GetRelationAmount() == 0)	upci_ptr_str1->DeleteINIS(str1_id);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si las estructuras INIS son distintas, entonces.
	if (str1_id != str2_id || upci_ptr_str1 != upci_ptr_str2)
	{
		//-----------------------------------------------------------------------------
		//obtención del índice de la relación en la estructura INIS.
		rl_index_in_str = upci_ptr_str2->BUFF_INIS[str2_id].GetRelationIndex(INDFRLIS_TYPE, _indfrlis_id, this->UPCI_ID);

		//-----------------------------------------------------------------------------
		//eliminación de la relación en str2_id.
		upci_ptr_str2->BUFF_INIS[str2_id].DeleteRelation(rl_index_in_str);

		//-----------------------------------------------------------------------------
		//si str2_id queda sin relaciones se elimina.
		if (upci_ptr_str2->BUFF_INIS[str2_id].GetRelationAmount() == 0)	upci_ptr_str2->DeleteINIS(str2_id);
	}	

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de relaciones de _indfrlis_id.
	rl_amount = this->BUFF_INDFRLIS[_indfrlis_id].GetRelationAmount();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para Delete estructuras de relación de la estructura de relación _indfrlis_id.
	for (in i1 = 0; i1 < rl_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención de los datos de la relación de la estructura _indfrlis_id.
		rl_type		= abs(this->BUFF_INDFRLIS[_indfrlis_id].RL.at(i1).at(0));
		rl_id		= this->BUFF_INDFRLIS[_indfrlis_id].RL.at(i1).at(1);
		upci_ptr_rl = &this->BUFF_UPCI->at(this->BUFF_INDFRLIS[_indfrlis_id].RL.at(i1).at(2));

		//-----------------------------------------------------------------------------
		//búsqueda del tipo de relación rl_type a eliminar.
		switch (rl_type)
		{
			//-------------------------------------------------------------------------
			//si la estructura es del tipo relación de flujo puro.
			case	PFRLIS_TYPE:
				upci_ptr_rl->DeletePFRLIS(rl_id, INDFRLIS_TYPE, _indfrlis_id, this->UPCI_ID);
				break;

			//-------------------------------------------------------------------------
			//si la estructura es del tipo relación proporcional de entradas.
			case	INPRRLIS_TYPE:
				upci_ptr_rl->DeleteINPRRLIS(rl_id, _indfrlis_id, this->UPCI_ID);
				break;

			//-------------------------------------------------------------------------
			//si no cumple con ninguna condición.
			default:
				break;
		}
	}	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//eliminación de la estrucura _indfrlis_id.
	this->BUFF_INDFRLIS[_indfrlis_id].Clean();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para Delete estructura INPRRLIS.
vo	UPCI_SDS::DeleteINPRRLIS(in _inprrlis_id)	
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las estructuras relacionadas.
	UPCI_SDS	*upci_ptr_str1		=	NULL;												//puntero de la upci de la estructura relacionada 1.
	UPCI_SDS	*upci_ptr_str2		=	NULL;												//puntero de la upci de la estructura relacionada 2.
	in			str1_id				=	NULL;												//id de la estructura relacionada 1.
	in			str2_id				=	NULL;												//id de la estructura relacionada 2.												
	in			rl_index_in_str		=	NULL;												//índice de la relación en una estructura.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//actualización de buffers para la eliminación de la IS.
	this->UpdateBuffersToDeleteINPRRLIS(_inprrlis_id);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de los id del registro relacionado. 
	str1_id			= this->BUFF_INPRRLIS[_inprrlis_id].STR1_ID_RG;
	str2_id			= this->BUFF_INPRRLIS[_inprrlis_id].STR2_ID_RG;

	//---------------------------------------------------------------------------------
	//id de upci.
	upci_ptr_str1	= &this->BUFF_UPCI->at(this->BUFF_INPRRLIS[_inprrlis_id].UPCI_ID_STR1_RG);
	upci_ptr_str2	= &this->BUFF_UPCI->at(this->BUFF_INPRRLIS[_inprrlis_id].UPCI_ID_STR2_RG);

	//---------------------------------------------------------------------------------
	//obtención del índice de la relación en la estructura INDFRLIS.
	rl_index_in_str = upci_ptr_str1->BUFF_INDFRLIS[str1_id].GetRelationIndex(INPRRLIS_TYPE, _inprrlis_id, this->UPCI_ID);

	//---------------------------------------------------------------------------------
	//eliminación de la relación en str1_id.
	upci_ptr_str1->BUFF_INDFRLIS[str1_id].DeleteRelation(rl_index_in_str);

	//---------------------------------------------------------------------------------
	//obtención del índice de la relación en la estructura INDFRLIS.
	rl_index_in_str = upci_ptr_str2->BUFF_INDFRLIS[str2_id].GetRelationIndex(INPRRLIS_TYPE, _inprrlis_id, this->UPCI_ID);

	//---------------------------------------------------------------------------------
	//eliminación de la relación en str2_id.
	upci_ptr_str2->BUFF_INDFRLIS[str2_id].DeleteRelation(rl_index_in_str);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//eliminación de la estrucura _inprrlis_id.
	this->BUFF_INPRRLIS[_inprrlis_id].Clean();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para Delete estructura PFRLIS con excepción a una estructura.
vo	UPCI_SDS::DeletePFRLIS(in _pfrlis_id, in _str_type, in _str_id, in _upci_id_str)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las estructuras relacionadas.
	UPCI_SDS	*upci_ptr_str1		=	NULL;												//puntero de la upci de la estructura relacionada 1.
	UPCI_SDS	*upci_ptr_str2		=	NULL;												//puntero de la upci de la estructura relacionada 2.
	in			str1_id				=	NULL;												//id de la estructura relacionada 1.
	in			str2_id				=	NULL;												//id de la estructura relacionada 2.										
	in			rl_index_in_str		=	NULL;												//índice de la relación en una estructura.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//actualización de buffers para la eliminación de la IS.
	this->UpdateBuffersToDeletePFRLIS(_pfrlis_id);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de los ids de las estructuras relacionadas. 
	str1_id			= this->BUFF_PFRLIS[_pfrlis_id].STR1_ID_RG;
	str2_id			= this->BUFF_PFRLIS[_pfrlis_id].STR2_ID_RG;
	
	//---------------------------------------------------------------------------------  
	//carga de los ids de las upci de las estructuras relacionadas.
	upci_ptr_str1	= &this->BUFF_UPCI->at(this->BUFF_PFRLIS[_pfrlis_id].UPCI_ID_STR1_RG);
	upci_ptr_str2	= &this->BUFF_UPCI->at(this->BUFF_PFRLIS[_pfrlis_id].UPCI_ID_STR2_RG);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la str2_id corresponde con la estructura a eliminar, entonces.
	if (_str_id == str2_id && _str_type == this->BUFF_PFRLIS[_pfrlis_id].STR2_TYPE_RG)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//búsqueda del tipo de estructura str1_id.
		switch (this->BUFF_PFRLIS[_pfrlis_id].STR1_TYPE_RG)
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//para estructura de entrada.
			case INIS_TYPE:	
				
				//---------------------------------------------------------------------
				//obtención del índice de la relación en la estructura INIS.
				rl_index_in_str = upci_ptr_str1->BUFF_INIS[str1_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);

				//---------------------------------------------------------------------
				//eliminación de la relación en str1_id.
				upci_ptr_str1->BUFF_INIS[str1_id].DeleteRelation(rl_index_in_str);

				//---------------------------------------------------------------------
				//si str1_id queda sin relaciones se elimina.
				if (upci_ptr_str1->BUFF_INIS[str1_id].GetRelationAmount() == 0)	upci_ptr_str1->DeleteINIS(str1_id);

				//---------------------------------------------------------------------
				//salida.
				break;

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//para estructura de relación de flujo diferencial de entradas.
			case INDFRLIS_TYPE:
			
				//---------------------------------------------------------------------
				//obtención del índice de la relación en la estructura INDFRLIS.
				rl_index_in_str = upci_ptr_str1->BUFF_INDFRLIS[str1_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);

				//---------------------------------------------------------------------
				//eliminación de la relación en str1_id.
				upci_ptr_str1->BUFF_INDFRLIS[str1_id].DeleteRelation(rl_index_in_str);

				//---------------------------------------------------------------------
				//salida.
				break;

			//-------------------------------------------------------------------------
			//si no cumple con ninguna condición.
			default:
						
				//---------------------------------------------------------------------
				//salida.
				break;
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la str1_id corresponde con la estructura a eliminar, entonces.
	else
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//búsqueda del tipo de estructura str2_id.
		switch (this->BUFF_PFRLIS[_pfrlis_id].STR2_TYPE_RG)
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//para estructura de entrada.
			case INIS_TYPE:	
				
				//---------------------------------------------------------------------
				//obtención del índice de la relación en la estructura INIS.
				rl_index_in_str = upci_ptr_str2->BUFF_INIS[str2_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);

				//---------------------------------------------------------------------
				//eliminación de la relación en str2_id.
				upci_ptr_str2->BUFF_INIS[str2_id].DeleteRelation(rl_index_in_str);

				//---------------------------------------------------------------------
				//si str2_id queda sin relaciones se elimina.
				if (upci_ptr_str2->BUFF_INIS[str2_id].GetRelationAmount() == 0) upci_ptr_str2->DeleteINIS(str2_id);

				//---------------------------------------------------------------------
				//salida.
				break;

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//para estructura de relación de flujo diferencial de entradas.
			case INDFRLIS_TYPE:
			
				//---------------------------------------------------------------------
				//obtención del índice de la relación en la estructura INDFRLIS.
				rl_index_in_str = upci_ptr_str2->BUFF_INDFRLIS[str2_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);

				//---------------------------------------------------------------------
				//eliminación de la relación en str2_id.
				upci_ptr_str2->BUFF_INDFRLIS[str2_id].DeleteRelation(rl_index_in_str);

				//---------------------------------------------------------------------
				//salida.
				break;
								
			//-------------------------------------------------------------------------
			//si no cumple con ninguna condición.
			default:
						
				//---------------------------------------------------------------------
				//salida.
				break;
		}
	}		
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//eliminación de la estrucura _pfrlis_id.
	this->BUFF_PFRLIS[_pfrlis_id].Clean();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para Delete estructura INDFRLIS con excepción a una estructura.
vo	UPCI_SDS::DeleteINDFRLIS(in _indfrlis_id, in _str_id, in _upci_id_str)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las estructuras relacionadas.
	UPCI_SDS	*upci_ptr_str1		=	NULL;												//puntero de la upci de la estructura relacionada 1.
	UPCI_SDS	*upci_ptr_str2		=	NULL;												//puntero de la upci de la estructura relacionada 2.
	in			str1_id				=	NULL;												//id de la estructura relacionada 1.
	in			str2_id				=	NULL;												//id de la estructura relacionada 2.	
	in			rl_index_in_str		=	NULL;												//índice de la relación en una estructura.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares de la relación _indfrlis_id.
	in			rl_type				=	NULL;												//tipo de las relaciones de la relación _indfrlis_id.
	in			rl_id				=	NULL;												//id de las relaciones de la relación _indfrlis_id.
	UPCI_SDS	*upci_ptr_rl		=	NULL;												//puntero de la upci de la relación _indfrlis_id.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares generales.
	in			rl_amount			=	NULL;												//cantidad de relaciones.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//actualización de buffers para la eliminación de la IS.
	this->UpdateBuffersToDeleteINDFRLIS(_indfrlis_id);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de los id del registro relacionado. 
	str1_id			= this->BUFF_INDFRLIS[_indfrlis_id].STR1_ID_RG;
	str2_id			= this->BUFF_INDFRLIS[_indfrlis_id].STR2_ID_RG;

	//---------------------------------------------------------------------------------
	//id de upci.
	upci_ptr_str1	= &this->BUFF_UPCI->at(this->BUFF_INDFRLIS[_indfrlis_id].UPCI_ID_STR1_RG);
	upci_ptr_str2	= &this->BUFF_UPCI->at(this->BUFF_INDFRLIS[_indfrlis_id].UPCI_ID_STR2_RG);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si las estructuras INIS son distintas, entonces.
	if (str1_id != str2_id || upci_ptr_str1 != upci_ptr_str2)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la str2_id corresponde con la estructura a eliminar, entonces.
		if (_str_id == str2_id)
		{
			//-------------------------------------------------------------------------
			//obtención del índice de la relación en la estructura INIS.
			rl_index_in_str = upci_ptr_str1->BUFF_INIS[str1_id].GetRelationIndex(INDFRLIS_TYPE, _indfrlis_id, this->UPCI_ID);

			//-------------------------------------------------------------------------
			//eliminación de la relación en str1_id.
			upci_ptr_str1->BUFF_INIS[str1_id].DeleteRelation(rl_index_in_str);

			//-------------------------------------------------------------------------
			//si str1_id queda sin relaciones se elimina.
			if (upci_ptr_str1->BUFF_INIS[str1_id].GetRelationAmount() == 0)	upci_ptr_str1->DeleteINIS(str1_id);
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la str1_id corresponde con la estructura a eliminar, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//obtención del índice de la relación en la estructura INIS.
			rl_index_in_str = upci_ptr_str2->BUFF_INIS[str2_id].GetRelationIndex(INDFRLIS_TYPE, _indfrlis_id, this->UPCI_ID);

			//-------------------------------------------------------------------------
			//eliminación de la relación en str2_id.
			upci_ptr_str2->BUFF_INIS[str2_id].DeleteRelation(rl_index_in_str);

			//-------------------------------------------------------------------------
			//si str2_id queda sin relaciones se elimina.
			if (upci_ptr_str2->BUFF_INIS[str1_id].GetRelationAmount() == 0)	upci_ptr_str2->DeleteINIS(str2_id);
		}	
	}	

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de relaciones de _indfrlis_id.
	rl_amount = this->BUFF_INDFRLIS[_indfrlis_id].GetRelationAmount();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para Delete estructuras de relación de la estructura de relación _indfrlis_id.
	for (in i1 = 0; i1 < rl_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención de los datos de la relación de la estructura _indfrlis_id.
		rl_type		= abs(this->BUFF_INDFRLIS[_indfrlis_id].RL.at(i1).at(0));
		rl_id		= this->BUFF_INDFRLIS[_indfrlis_id].RL.at(i1).at(1);
		upci_ptr_rl = &this->BUFF_UPCI->at(this->BUFF_INDFRLIS[_indfrlis_id].RL.at(i1).at(2));
		
		//-----------------------------------------------------------------------------
		//búsqueda del tipo de relación rl_type a eliminar.
		switch (rl_type)
		{
			//-------------------------------------------------------------------------
			//si la estructura es del tipo relación de flujo puro.
			case	PFRLIS_TYPE:
				upci_ptr_rl->DeletePFRLIS(rl_id, INDFRLIS_TYPE, _indfrlis_id, this->UPCI_ID);
				break;

			//-------------------------------------------------------------------------
			//si la estructura es del tipo relación proporcional de entradas.
			case	INPRRLIS_TYPE:
				upci_ptr_rl->DeleteINPRRLIS(rl_id, _indfrlis_id, this->UPCI_ID);
				break;

			//-------------------------------------------------------------------------
			//si no cumple con ninguna condición.
			default:
				break;
		}
	}	
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//eliminación de la estrucura _indfrlis_id.
	this->BUFF_INDFRLIS[_indfrlis_id].Clean();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para Delete estructura INPRRLIS con excepción a una estructura.
vo	UPCI_SDS::DeleteINPRRLIS(in _inprrlis_id, in _str_id, in _upci_id_str)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las estructuras relacionadas.
	UPCI_SDS	*upci_ptr_str1		=	NULL;												//puntero de la upci de la estructura relacionada 1.
	UPCI_SDS	*upci_ptr_str2		=	NULL;												//puntero de la upci de la estructura relacionada 2.
	in			str1_id				=	NULL;												//id de la estructura relacionada 1.
	in			str2_id				=	NULL;												//id de la estructura relacionada 2.												
	in			rl_index_in_str		=	NULL;												//índice de la relación en una estructura.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//actualización de buffers para la eliminación de la IS.
	this->UpdateBuffersToDeleteINPRRLIS(_inprrlis_id);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de los id del registro relacionado. 
	str1_id			= this->BUFF_INPRRLIS[_inprrlis_id].STR1_ID_RG;
	str2_id			= this->BUFF_INPRRLIS[_inprrlis_id].STR2_ID_RG;

	//---------------------------------------------------------------------------------
	//id de upci.
	upci_ptr_str1	= &this->BUFF_UPCI->at(this->BUFF_INPRRLIS[_inprrlis_id].UPCI_ID_STR1_RG);
	upci_ptr_str2	= &this->BUFF_UPCI->at(this->BUFF_INPRRLIS[_inprrlis_id].UPCI_ID_STR2_RG);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la str2_id corresponde con la estructura a eliminar, entonces.
	if (_str_id == str2_id)
	{
		//-----------------------------------------------------------------------------
		//obtención del índice de la relación en la estructura INDFRLIS.
		rl_index_in_str = upci_ptr_str1->BUFF_INDFRLIS[str1_id].GetRelationIndex(INPRRLIS_TYPE, _inprrlis_id, this->UPCI_ID);

		//-----------------------------------------------------------------------------
		//eliminación de la relación en str1_id.
		upci_ptr_str1->BUFF_INDFRLIS[str1_id].DeleteRelation(rl_index_in_str);
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la str1_id corresponde con la estructura a eliminar, entonces.
	else
	{
		//-----------------------------------------------------------------------------
		//obtención del índice de la relación en la estructura INDFRLIS.
		rl_index_in_str = upci_ptr_str2->BUFF_INDFRLIS[str2_id].GetRelationIndex(INPRRLIS_TYPE, _inprrlis_id, this->UPCI_ID);

		//-----------------------------------------------------------------------------
		//eliminación de la relación en str2_id.
		upci_ptr_str2->BUFF_INDFRLIS[str2_id].DeleteRelation(rl_index_in_str);
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//eliminación de la estrucura _inprrlis_id.
	this->BUFF_INPRRLIS[_inprrlis_id].Clean();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para limpiar buffer de proyección de salida.
vo	UPCI_SDS::CleanBUFF_OUTPUT_PROJECTION()
{
	//---------------------------------------------------------------------------------
	//limpieza de buffer de proyección de salida.
	*this->BUFF_OUTPUT_PROJECTION = NULL;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método thread para limpiar buffer de IS.
vo	UPCI_SDS::CleanISBuffers()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de tiempos de espera de los bucles.
	chrono::milliseconds timeout_clean_is(this->TIMEOUT_CLEAN_IS);
	chrono::milliseconds timeout_loop_fast(TIMEOUT_LOOP_FAST);

	//--------------------------------------------------------------------------------- 
	//--------------------------------------------------------------------------------- 
	//bucle para limpieza.
	while (true)
	{
		//-----------------------------------------------------------------------------
		//espera para ejecutar limpieza.
		this_thread::sleep_for(timeout_clean_is);

		//-----------------------------------------------------------------------------
		//espera que acabe de integrar la upci.
		while (this->GetTHREAD_INTEGRATION_FLAG() == ON)	this_thread::sleep_for(timeout_loop_fast);

		//-----------------------------------------------------------------------------
		//bloqueo para limpieza.
		this->RED_LIGHT_MUTEX.lock();

		//-----------------------------------------------------------------------------
		//la upci entra en estado de integración.
		this->SetTHREAD_INTEGRATION_FLAG(ON);

		//-----------------------------------------------------------------------------
		//threads para limpieza.
		thread IS[3];		

		//-----------------------------------------------------------------------------
		//impresión del comienzo de la limpieza de los buffers de la upci.
		this->Print("> limpieza de buffers iniciada...");
		
		//-----------------------------------------------------------------------------
		//se hacen correr threads de limpieza de IS.
		IS[0] = thread(&UPC::UPCI_SDS::CleanPFRLIS, this);
		IS[1] = thread(&UPC::UPCI_SDS::CleanINDFRLIS, this);
		IS[2] = thread(&UPC::UPCI_SDS::CleanActivityLevelIS, this);

		//-----------------------------------------------------------------------------
		//bucle para terminar threads.
		for (in i1 = 0; i1 < 3; i1++)
		{
			//-------------------------------------------------------------------------
			//finalización del thread.
			IS[i1].join();
		}

		//-----------------------------------------------------------------------------
		//limpieza de los buffers para los ids y tipo de las estructuras creadas.
		this->BUFF_INIS_CRE[0].Clean();														//buffer para INIS creada actual.
		this->BUFF_INIS_CRE[1].Clean();														//buffer para INIS creada anterior.
		this->BUFF_PFRLIS_CRE[0].Clean();													//buffer para PFRLIS creada actual.
		this->BUFF_PFRLIS_CRE[1].Clean();													//buffer para PFRLIS creada anterior.
		this->BUFF_INDFRLIS_CRE[0].Clean();													//buffer para INDFRLIS creada actual.
		this->BUFF_INDFRLIS_CRE[1].Clean();													//buffer para INDFRLIS creada anterior.
		this->BUFF_INPRRLIS_CRE[0].Clean();													//buffer para INPRRLIS creada actual.
		this->BUFF_INPRRLIS_CRE[1].Clean();													//buffer para INPRRLIS creada anterior.

		//-----------------------------------------------------------------------------
		//reset del buffer para el flujo de estructuras activadas.
		this->BUFF_INIS_ACTIVATED[0].Clean();												//buffer presente.
		this->BUFF_INIS_ACTIVATED[1].Clean();												//buffer pasado.

		//-----------------------------------------------------------------------------
		//la upci sale del estado de integración.
		this->SetTHREAD_INTEGRATION_FLAG(OFF);		

		//-----------------------------------------------------------------------------
		//impresión de la finalización de la limpieza de los buffers de la upci.
		this->Print("> limpieza de buffers finalizada.");

		//-----------------------------------------------------------------------------
		//desbloqueo para limpieza.
		this->RED_LIGHT_MUTEX.unlock();
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para limpieza de buffer PFRLIS.
vo	UPCI_SDS::CleanPFRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de estructuras PFRLIS.
	for (in i1 = 0; i1 < this->BUFF_PFRLIS_MAX_ID[0] + 1; i1++)
	{
		//-----------------------------------------------------------------------------  #### DEFINIR OTRO UMBRAL PARA LIMPIEZA DE ESTRUCTURAS EN ESTADO INCONSCIENTE.
		//si la estructura está definida y no sobrepasa el umbral, entonces.
		if (this->BUFF_PFRLIS[i1].RS_SRG != -1 && this->BUFF_PFRLIS[i1].RS_SRG < this->PFRLIS_STRENGTH_THRESHOLD)
		{
			cout << "//XX5 se va a eliminar PFRLIS con id: " << i1 << endl;
			//-------------------------------------------------------------------------
			//se elimina la estructura.
			this->DeletePFRLIS(i1);
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para limpieza de buffer INDFRLIS.
vo	UPCI_SDS::CleanINDFRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de estructuras INDFRLIS.
	for (in i1 = 0; i1 < this->BUFF_INDFRLIS_MAX_ID[0] + 1; i1++)
	{
		//----------------------------------------------------------------------------- #### DEFINIR OTRO UMBRAL PARA LIMPIEZA DE ESTRUCTURAS EN ESTADO INCONSCIENTE.
		//si la estructura está definida y no sobrepasa el umbral, entonces.
		if (this->BUFF_INDFRLIS[i1].RS_SRG != -1 && this->BUFF_INDFRLIS[i1].RS_SRG < this->INDFRLIS_STRENGTH_THRESHOLD)
		{
			//-------------------------------------------------------------------------
			//se elimina la estructura.
			this->DeleteINDFRLIS(i1);
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------- 
//-------------------------------------------------------------------------------------  
//#1: método para relacionar estructura INIS creadas o reconocidas.
vo	UPCI_SDS::RelateINIS_CR(in _inis_id)
{	
	//---------------------------------------------------------------------------------
	//reset de la bandera de alerta de la creación de INDFRLIS.
	this->SetNEW_INPUT_DIFFERENCE_RELATION_FLAG(OFF);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura activada anterior está definida y en suspensión.
	if (this->GetPastActivityStatus_INIS() == ON)
	{
		//-----------------------------------------------------------------------------
		//creación de relación de flujo diferencial de entradas.
		this->CreateINDFRLIS(this->BUFF_INIS_ACTIVATED[1].STR_ID, _inis_id, this->BUFF_INIS_ACTIVATED[1].UPCI_ID, this->UPCI_ID);
	}
}

//------------------------------------------------------------------------------------- 
//-------------------------------------------------------------------------------------  
//#2: método para relacionar estructura INIS reactivada en flujo.
vo	UPCI_SDS::RelateINIS_F(in _inis_id)
{
	//---------------------------------------------------------------------------------
	//reset de la bandera de alerta de la creación de INDFRLIS.
	this->SetNEW_INPUT_DIFFERENCE_RELATION_FLAG(OFF);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura activada anterior está definida y en suspensión.
	if (this->GetPastActivityStatus_INIS() == ON)
	{
		//-----------------------------------------------------------------------------
		//creación de relación de flujo diferencial de entradas.
		this->CreateINDFRLIS(this->BUFF_INIS_ACTIVATED[1].STR_ID, _inis_id, this->BUFF_INIS_ACTIVATED[1].UPCI_ID, this->UPCI_ID);
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------  
//#3: método para relacionar estructura INDFRLIS creada.
vo	UPCI_SDS::RelateINDFRLIS(in _indfrlis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	in str1_id					= this->BUFF_INDFRLIS[_indfrlis_id].STR1_ID_RG;				//id de la estructura INIS de inicio de la relación INDFRLIS.
	in str2_id					= this->BUFF_INDFRLIS[_indfrlis_id].STR2_ID_RG;				//id de la estructura INIS de fin de la relación INDFRLIS.
	in upci_id_str1				= this->BUFF_INDFRLIS[_indfrlis_id].UPCI_ID_STR1_RG;		//id de la upci de la estructura INIS de inicio de la relación INDFRLIS.
	in rl_amount				= NULL;														//cantidad de relaciones de la estructura INIS str1_id.
	in indfrlis_id_found		= NULL;														//id de la relación INDFRLIS encontrada en la estructura INIS str1_id.
	in upci_id_indfrlis_found	= NULL;														//id de la upci de la relación diferencial de entradas INDFRLIS encontrada.

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de relaciones de la estructura INIS str1_id.
	rl_amount = this->BUFF_UPCI->at(upci_id_str1).BUFF_INIS[str1_id].GetRelationAmount();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para hallar una relación INDFRLIS en la estructura INIS str1_id.
	for (in i1 = 0; i1 < rl_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si se encuentra una relación diferencial de entrada entrante, entonces.
		if (this->BUFF_UPCI->at(upci_id_str1).BUFF_INIS[str1_id].RL.at(rl_amount - (i1 + 1)).at(0) == -INDFRLIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//id de la relación INDFRLIS hallada.
			indfrlis_id_found		= this->BUFF_UPCI->at(upci_id_str1).BUFF_INIS[str1_id].RL.at(rl_amount - (i1 + 1)).at(1);

			//-------------------------------------------------------------------------
			//seteo del id de la upci de la relación INDFRLIS hallada.
			upci_id_indfrlis_found	= this->BUFF_UPCI->at(upci_id_str1).BUFF_INIS[str1_id].RL.at(rl_amount - (i1 + 1)).at(2);

			//-------------------------------------------------------------------------
			//si el inicio es distinto de str2_id, entonces crear relación.
			if (str2_id != this->BUFF_UPCI->at(upci_id_indfrlis_found).BUFF_INDFRLIS[indfrlis_id_found].STR1_ID_RG)
			{
				//---------------------------------------------------------------------
				//si los dos registros son diferentes de '0', entonces relacionar.
				if (this->BUFF_UPCI->at(upci_id_indfrlis_found).BUFF_INDFRLIS[indfrlis_id_found].IN_DIF_RG != 0 &&
					this->BUFF_INDFRLIS[_indfrlis_id].IN_DIF_RG != 0)
				{
					//-----------------------------------------------------------------
					//crear una relación proporcional de diferencias de entradas.
					this->CreateINPRRLIS(indfrlis_id_found, _indfrlis_id, upci_id_indfrlis_found, this->UPCI_ID);
				}

				//---------------------------------------------------------------------
				//salida del bucle.
				break;
			}			
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para chekear una relación PFRLIS antes de ser creada para no duplicarse.
in	UPCI_SDS::CheckPreviousPFRLIS(in _str1_type, in _str2_type, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	UPCI_SDS	*upci_ptr_str1		=	&this->BUFF_UPCI->at(_upci_id_str1);				//puntero de la upci de la estructura relacionada 1.				
	in			rl_type_str1		=	NULL;												//tipo de relación de la estructura relacionada 1.
	in			rl_id_str1			=	NULL;												//id de la relación de la estructura relacionada 1.	
	UPCI_SDS	*upci_ptr_rl_str1	=	NULL;												//puntero de la upci de la relación de la estructura relacionada 1. 
	in			rl_found			=	OFF;												//verificador de la existencia de la relación.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//búsqueda del tipo de estructura str1.
	switch (_str1_type)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//para estructura de entrada.
		case INIS_TYPE		:	
			
			//-------------------------------------------------------------------------
			//si la estructura tiene relaciones, entonces.
			if (upci_ptr_str1->BUFF_INIS[_str1_id].GetRelationAmount() > 0)
			{
				//---------------------------------------------------------------------
				//obtención de datos de la relación de la estructura str1_id.
				rl_type_str1		= abs(upci_ptr_str1->BUFF_INIS[_str1_id].RL.back().at(0));
				rl_id_str1			= upci_ptr_str1->BUFF_INIS[_str1_id].RL.back().at(1);
				upci_ptr_rl_str1	= &this->BUFF_UPCI->at(upci_ptr_str1->BUFF_INIS[_str1_id].RL.back().at(2));
			}						
			
			//-------------------------------------------------------------------------
			//salida.
			break;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//para estructura de relación de flujo diferencial de entradas.
		case INDFRLIS_TYPE:
			
			//-------------------------------------------------------------------------
			//si la estructura tiene relaciones, entonces.
			if (upci_ptr_str1->BUFF_INDFRLIS[_str1_id].GetRelationAmount() > 0)
			{
				//---------------------------------------------------------------------
				//obtención de datos de la relación de lastructure 
				//str1_id.
				rl_type_str1		= abs(upci_ptr_str1->BUFF_INDFRLIS[_str1_id].RL.back().at(0));
				rl_id_str1			= upci_ptr_str1->BUFF_INDFRLIS[_str1_id].RL.back().at(1);
				upci_ptr_rl_str1	= &this->BUFF_UPCI->at(upci_ptr_str1->BUFF_INDFRLIS[_str1_id].RL.back().at(2));
			}			

			//-------------------------------------------------------------------------
			//salida.
			break;
				
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si no cumple con ninguna condición.
		default:
						
			//-------------------------------------------------------------------------
			//salida.
			break;
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//comprobando igualdad de la relación en tipo.
	if (rl_type_str1 == PFRLIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//comprobando igualdad de la relación.
		if (abs(upci_ptr_rl_str1->BUFF_PFRLIS[rl_id_str1].STR2_TYPE_RG)		==	_str2_type		&&
				upci_ptr_rl_str1->BUFF_PFRLIS[rl_id_str1].STR2_ID_RG		==	_str2_id		&&
				upci_ptr_rl_str1->BUFF_PFRLIS[rl_id_str1].UPCI_ID_STR2_RG	==	_upci_id_str2)
		{
			//-------------------------------------------------------------------------
			//se ha hallado la relación que se piensa crear.
			rl_found = ON;
		}
	}	

	//---------------------------------------------------------------------------------
	//retorno de la comprobación.
	return rl_found;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para chekear una relación INDFRLIS antes de ser creada para no duplicarse.
in	UPCI_SDS::CheckPreviousINDFRLIS(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	UPCI_SDS	*upci_ptr_str1		=	&this->BUFF_UPCI->at(_upci_id_str1);				//puntero de la upci de la estructura relacionada 1.				
	in			rl_type_str1		=	0;													//tipo de relación de la estructura relacionada 1.
	in			rl_id_str1			=	0;													//id de la relación de la estructura relacionada 1.	
	UPCI_SDS	*upci_ptr_rl_str1	=	NULL;												//puntero de la upci de la relación de la estructura relacionada 1. 
	in			rl_found			=	OFF;												//verificador de la existencia de la relación.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura tiene relaciones, entonces.
	if (upci_ptr_str1->BUFF_INIS[_str1_id].GetRelationAmount() > 0)
	{
		//-----------------------------------------------------------------------------
		//obtención de datos de la relación de lastructure str1_id.
		rl_type_str1		= abs(upci_ptr_str1->BUFF_INIS[_str1_id].RL.back().at(0));
		rl_id_str1			= upci_ptr_str1->BUFF_INIS[_str1_id].RL.back().at(1);
		upci_ptr_rl_str1	= &this->BUFF_UPCI->at(upci_ptr_str1->BUFF_INIS[_str1_id].RL.back().at(2));
	}	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//comprobando igualdad de la relación en tipo.
	if (rl_type_str1 == INDFRLIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//comprobando igualdad de la relación.
		if (upci_ptr_rl_str1->BUFF_INDFRLIS[rl_id_str1].STR2_ID_RG		==	_str2_id		&&
			upci_ptr_rl_str1->BUFF_INDFRLIS[rl_id_str1].UPCI_ID_STR2_RG	==	_upci_id_str2)
		{
			//-------------------------------------------------------------------------
			//se ha hallado la relación que se piensa crear.
			rl_found = ON;
		}
	}	

	//---------------------------------------------------------------------------------
	//retorno de la comprobación.
	return rl_found;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para chekear una relación INPRRLIS antes de ser creada para no duplicarse.
in	UPCI_SDS::CheckPreviousINPRRLIS(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	UPCI_SDS	*upci_ptr_str1		=	&this->BUFF_UPCI->at(_upci_id_str1);				//puntero de la upci de la estructura relacionada 1.				
	in			rl_type_str1		=	0;													//tipo de relación de la estructura relacionada 1.
	in			rl_id_str1			=	0;													//id de la relación de la estructura relacionada 1.	
	UPCI_SDS	*upci_ptr_rl_str1	=	NULL;												//puntero de la upci de la relación de la estructura relacionada 1. 
	in			rl_found			=	OFF;												//verificador de la existencia de la relación.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura tiene relaciones, entonces.
	if (upci_ptr_str1->BUFF_INDFRLIS[_str1_id].GetRelationAmount() > 0)
	{
		//-----------------------------------------------------------------------------
		//obtención de datos de la relación de lastructure str1_id.
		rl_type_str1		= abs(upci_ptr_str1->BUFF_INDFRLIS[_str1_id].RL.back().at(0));
		rl_id_str1			= upci_ptr_str1->BUFF_INDFRLIS[_str1_id].RL.back().at(1);
		upci_ptr_rl_str1	= &this->BUFF_UPCI->at(upci_ptr_str1->BUFF_INDFRLIS[_str1_id].RL.back().at(2));
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//comprobando igualdad de la relación en tipo.
	if (rl_type_str1 == INPRRLIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//comprobando igualdad de la relación.
		if (upci_ptr_rl_str1->BUFF_INPRRLIS[rl_id_str1].STR2_ID_RG		==	_str2_id		&&
			upci_ptr_rl_str1->BUFF_INPRRLIS[rl_id_str1].UPCI_ID_STR2_RG	==	_upci_id_str2)
		{
			//-------------------------------------------------------------------------
			//se ha hallado la relación que se piensa crear.
			rl_found = ON;
		}
	}	

	//---------------------------------------------------------------------------------
	//retorno de la comprobación.
	return rl_found;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para reactivar INIS.
vo	UPCI_SDS::ReactiveINIS(in _inis_id)
{
	//---------------------------------------------------------------------------------
	//bloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.lock();

	//---------------------------------------------------------------------------------
	//si le nivel de actividad es igual a "0", setear en buffer de IS en suspensión.
	if (this->BUFF_INIS[_inis_id].AL_SRG == 0)	this->SetBUFF_STR_SUS(_inis_id, INIS_TYPE);

	//---------------------------------------------------------------------------------
	//incremento del nivel de actividad de la estructura "_inis_id".
	this->BUFF_INIS[_inis_id].AL_SRG =	this->DEFAULT_ACTIVITY_LEVEL;	

	//---------------------------------------------------------------------------------
	//seteo de la estructura INIS activada.
	this->SetBUFF_INIS_ACTIVATED(_inis_id);

	//---------------------------------------------------------------------------------
	//si la IS reactivada posee la mayor evaluación, entonces setear nueva estructura.
	if (*this->BUFF_MAX_EVALUATION < this->BUFF_INIS[_inis_id].EV_RG)		this->SetBUFF_INIS_MAX_EVAL(_inis_id, this->BUFF_INIS[_inis_id].EV_RG);

	//---------------------------------------------------------------------------------
	//si la IS reactivada posee el mayor nivel de actividad, entonces setear nueva estructura.
	if (*this->BUFF_MAX_ACTIVITY_LEVEL < this->BUFF_INIS[_inis_id].AL_SRG)	this->SetBUFF_INIS_MAX_AL(_inis_id, this->BUFF_INIS[_inis_id].AL_SRG);

	//---------------------------------------------------------------------------------
	//impresión de la reactivación de la entrada.
	//this->Print("    > se reactiva inis id", _inis_id);

	//---------------------------------------------------------------------------------
	//desbloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.unlock();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para reactivar PFRLIS.
vo	UPCI_SDS::ReactivePFRLIS(in _pfrlis_id)
{
	//---------------------------------------------------------------------------------
	//bloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.lock();

	//---------------------------------------------------------------------------------
	//si le nivel de actividad es igual a "0", setear en buffer de IS en suspensión.
	if (this->BUFF_PFRLIS[_pfrlis_id].AL_SRG == 0)	this->SetBUFF_STR_SUS(_pfrlis_id, PFRLIS_TYPE);

	//---------------------------------------------------------------------------------
	//incremento de la fuerza de la relación y del nivel de actividad de la relación de "_pfrlis_id".
	this->BUFF_PFRLIS[_pfrlis_id].RS_SRG	+= 1;
	this->BUFF_PFRLIS[_pfrlis_id].AL_SRG	=	this->DEFAULT_ACTIVITY_LEVEL;	

	//---------------------------------------------------------------------------------
	//impresión de la reactivación de la relación de flujo puro.
	//this->Print("    > se reactiva pfrlis id", _pfrlis_id);

	//---------------------------------------------------------------------------------
	//desbloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.unlock();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para reactivar INDFRLIS.
vo	UPCI_SDS::ReactiveINDFRLIS(in _indfrlis_id)
{
	//---------------------------------------------------------------------------------
	//bloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.lock();

	//---------------------------------------------------------------------------------
	//si le nivel de actividad es igual a "0", setear en buffer de IS en suspensión.
	if (this->BUFF_INDFRLIS[_indfrlis_id].AL_SRG == 0)	this->SetBUFF_STR_SUS(_indfrlis_id, INDFRLIS_TYPE);

	//---------------------------------------------------------------------------------
	//incremento de la fuerza de la relación y del nivel de actividad de la relación de "_indfrlis_id".
	this->BUFF_INDFRLIS[_indfrlis_id].RS_SRG	+=	1;
	this->BUFF_INDFRLIS[_indfrlis_id].AL_SRG	= this->DEFAULT_ACTIVITY_LEVEL;

	//---------------------------------------------------------------------------------
	//impresión de la reactivación de la relación diferencial de entradas.
	//this->Print("    > se reactiva indfrlis id", _indfrlis_id);

	//---------------------------------------------------------------------------------
	//desbloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.unlock();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método de diferenciación global para estructura INIS.
vo	UPCI_SDS::GlobalDifferentiationINIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variablea auxiliares para estructuras candidatas.	
	in upci_id_candidate		= NULL;														//id de la upci candidata.
	in inis_id_candidate		= NULL;														//id de la estructura candidata.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variablea auxiliares para estructuras candidatas.	
	in winning_upci_id			= NULL;														//id de la upci ganadora.		
	in winning_inis_id			= NULL;														//id de la estructura ganadora.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variablea auxiliares para cantidades.
	in upci_amount				= NULL;														//cantidad de upci existentes en el grupo.
	in upci_candidates_amount	= NULL;														//cantidad de upci con estructuras candidatas.
	in inis_candidates_amout	= NULL;														//cantidad de estructuras cadidatas.			
	in inis_with_fcc_amount		= NULL;														//cantidad de estructuras con F.C.C.	

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de upci existentes en el grupo.
	upci_amount					= this->GetAmountUpcGro();													
	
	//---------------------------------------------------------------------------------
	//incremento del contador de diferenciaciones globales.
	++this->GLOBAL_DIFFERENTIATION_COUNTER;

	//---------------------------------------------------------------------------------
	//inicialización de buffers para candidatos.
	this->BUFF_UPCI_ID_INIS_CAN->push_front(deque<in>(0));
	this->BUFF_INIS_ID_CAN->push_front(deque<deque<in>>(0));
	this->BUFF_INIS_ID_CAN->front().resize(upci_amount);
	
	//---------------------------------------------------------------------------------
	//limpieza del buffer de estructura reconocida.
	this->BUFF_INIS_RE->Clean();

	//---------------------------------------------------------------------------------
	//limpieza de buffer para el índice de relación utilizada en reconocimiento.
	*this->BUFF_RL_INDEX_USED_IN_RECOGNITION = -1;

	//---------------------------------------------------------------------------------
	//paralelización del bucle for.
	#pragma omp parallel for

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para diferenciar BUFF_IN_RG con todas las upci.
	for (in i1 = 0; i1 < upci_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si existen estructuras INIS entonces diferenciar en la upci "i1".
		if (this->BUFF_UPCI->at(i1).BUFF_INIS_INI_AMOUNT > 0)
		{
			//-------------------------------------------------------------------------
			//diferenciación de BUFF_IN_RG en la upci "i1".
			this->BUFF_UPCI->at(i1).LocalDifferentiationINIS();
		}		
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para setear upci candidatas en buffer BUFF_UPCI_ID_INIS_CAN.
	for (in i1 = 0; i1 < upci_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si la upci "i1" contiene estructuras candidatas, entonces. 
		if (this->BUFF_INIS_ID_CAN->front().at(i1).size() > 0)
		{
			//-------------------------------------------------------------------------
			//seteo en buffer BUFF_UPCI_ID_INIS_CAN.
			this->BUFF_UPCI_ID_INIS_CAN->front().push_back(i1);
		}
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existe alguna upci candidata, entonces.
	if (this->BUFF_UPCI_ID_INIS_CAN->front().size() > 0)
	{
		//-----------------------------------------------------------------------------
		//actualización del estado de congruencia de estructuras candidatas presentes.
		this->UpdateToCongruentBUFF_INIS();		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existe solo una estructura UPCI con un solo candidato, entonces.
		if (this->BUFF_UPCI_ID_INIS_CAN->front().size() == 1 && this->BUFF_INIS_ID_CAN->front().at(this->BUFF_UPCI_ID_INIS_CAN->front().at(0)).size() == 1)
		{		
			//-------------------------------------------------------------------------
			//actualización del estado de congruencia de estructuras candidatas anteriores.
			this->UpdateToNotCongruentBUFF_INIS();			

			//-------------------------------------------------------------------------
			//obtención del id de la upci ganadora y del id de la estructura ganadora.
			winning_upci_id	= this->BUFF_UPCI_ID_INIS_CAN->front().at(0);
			winning_inis_id	= this->BUFF_INIS_ID_CAN->front().at(upci_id_candidate).at(0);			

			//-------------------------------------------------------------------------
			//seteo de la estructura reconocida.
			this->BUFF_INIS_RE->Set(winning_upci_id, winning_inis_id);
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existe más de una estructura candidata, entonces analizar la existencia de F.C.C.
		else
		{
			//-------------------------------------------------------------------------
			//obtención de la cantidad de estructuras candidatas.
			upci_candidates_amount	= in(this->BUFF_UPCI_ID_INIS_CAN->front().size());	
			
			//-------------------------------------------------------------------------
			//paralelización del bucle for.
			#pragma omp parallel for

			//-------------------------------------------------------------------------  
			//bucle para conocer si existe F.C.C de las estructuras candidatas en upci i1.
			for (in i1 = 0; i1 < upci_candidates_amount; i1++)
			{
				//---------------------------------------------------------------------
				//obtención de id upci candidato.
				upci_id_candidate		= this->BUFF_UPCI_ID_INIS_CAN->front().at(i1);

				//---------------------------------------------------------------------
				//obtención de la cantidad de candidatos INIS en upci "i1".
				inis_candidates_amout	= in(this->BUFF_INIS_ID_CAN->front().at(upci_id_candidate).size());
				
				//---------------------------------------------------------------------
				//bucle para conocer si existe F.C.C en la estructura candidata i2.
				for (in i2 = 0; i2 < inis_candidates_amout; i2++)
				{
					//-----------------------------------------------------------------
					//obtención del id de la estructura.
					inis_id_candidate = this->BUFF_INIS_ID_CAN->front().at(upci_id_candidate).at(i2);

					//-----------------------------------------------------------------
					//si la estructura tiene flujo de congruencias continuo, entonces.
					if (this->BUFF_UPCI->at(upci_id_candidate).ContinuousFlowOfCongruencesINIS(inis_id_candidate))
					{
						//-------------------------------------------------------------
						//seteo de id de upci y estructura ganadora.
						winning_upci_id	= upci_id_candidate;
						winning_inis_id	= inis_id_candidate;

						//-------------------------------------------------------------
						//incremento de los ids INIS candidatos con F.C.C. 
						++inis_with_fcc_amount;
					}
				}					
			}

			//-------------------------------------------------------------------------
			//actualización del estado de congruencia de estructuras candidatas anteriores.
			this->UpdateToNotCongruentBUFF_INIS();
		
			//-------------------------------------------------------------------------
			//si existe solo una estructura con F.C.C, hay reconocimiento de un Hilo.
			if (inis_with_fcc_amount == 1)
			{
				//---------------------------------------------------------------------
				//seteo de la estructura reconocida.
				this->BUFF_INIS_RE->Set(winning_upci_id, winning_inis_id);
			}
		}				
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método de diferenciación global para estructura INDFRLIS.
vo	UPCI_SDS::GlobalDifferentiationINDFRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variablea auxiliares para estructuras candidatas.	
	in upci_id_candidate			= NULL;													//id de la upci candidata.
	in indfrlis_id_candidate		= NULL;													//id de la estructura candidata.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variablea auxiliares para estructuras candidatas.	
	in winning_upci_id				= NULL;													//id de la upci ganadora.		
	in winning_indfrlis_id			= NULL;													//id de la estructura ganadora.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variablea auxiliares para cantidades.
	in upci_amount					= NULL;													//cantidad de upci existentes en el grupo.
	in upci_candidates_amount		= NULL;													//cantidad de upci con estructuras candidatas.
	in indfrlis_candidates_amout	= NULL;													//cantidad de estructuras cadidatas.			
	in indfrlis_with_fcc_amount		= NULL;													//cantidad de estructuras con F.C.C.	

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de upci existentes en el grupo.
	upci_amount						= this->GetAmountUpcGro();

	//---------------------------------------------------------------------------------
	//incremento del contador de diferenciaciones globales.
	++this->GLOBAL_DIFFERENTIATION_COUNTER;

	//---------------------------------------------------------------------------------
	//inicialización de buffers para candidatos.
	this->BUFF_UPCI_ID_INDFRLIS_CAN->push_front(deque<in>(0));
	this->BUFF_INDFRLIS_ID_CAN->push_front(deque<deque<in>>(0));
	this->BUFF_INDFRLIS_ID_CAN->front().resize(upci_amount);

	//---------------------------------------------------------------------------------
	//limpieza del buffer de estructura reconocida.
	this->BUFF_INDFRLIS_RE->Clean();
	
	//---------------------------------------------------------------------------------
	//paralelización del bucle for.
	#pragma omp parallel for

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para diferenciar BUFF_IN_DIF_RG con todas las upci.
	for (in i1 = 0; i1 < upci_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si existen estructuras INDFRLIS entonces diferenciar en la upci "i1".
		if (this->BUFF_UPCI->at(i1).BUFF_INDFRLIS_INI_AMOUNT > 0)
		{
			//-------------------------------------------------------------------------
			//diferenciación de BUFF_IN_DIF_RG en la upci "i1".
			this->BUFF_UPCI->at(i1).LocalDifferentiationINDFRLIS();
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para setear upci candidatas en buffer BUFF_UPCI_ID_INDFRLIS_CAN.
	for (in i1 = 0; i1 < upci_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si la upci "i1" contiene estructuras candidatas, entonces. 
		if (this->BUFF_INDFRLIS_ID_CAN->front().at(i1).size() > 0)
		{
			//-------------------------------------------------------------------------
			//seteo en buffer BUFF_UPCI_ID_INDFRLIS_CAN.
			this->BUFF_UPCI_ID_INDFRLIS_CAN->front().push_back(i1);
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existe alguna upci candidata, entonces.
	if (this->BUFF_UPCI_ID_INDFRLIS_CAN->front().size() > 0)
	{
		//-----------------------------------------------------------------------------
		//actualización del estado de congruencia de estructuras candidatas presentes.
		this->UpdateToCongruentBUFF_INDFRLIS();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existe solo una estructura candidata.
		if (this->BUFF_UPCI_ID_INDFRLIS_CAN->front().size() == 1 && this->BUFF_INDFRLIS_ID_CAN->front().at(this->BUFF_UPCI_ID_INDFRLIS_CAN->front().at(0)).size() == 1)
		{
			//-------------------------------------------------------------------------
			//actualización del estado de congruencia de estructuras candidatas anteriores.
			this->UpdateToNotCongruentBUFF_INDFRLIS();

			//-------------------------------------------------------------------------
			//obtención del id de la upci ganadora y del id de la estructura ganadora.
			winning_upci_id		= this->BUFF_UPCI_ID_INDFRLIS_CAN->front().at(0);
			winning_indfrlis_id	= this->BUFF_INDFRLIS_ID_CAN->front().at(upci_id_candidate).at(0);

			//-------------------------------------------------------------------------
			//seteo de la estructura reconocida.
			this->BUFF_INDFRLIS_RE->Set(winning_upci_id, winning_indfrlis_id);
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existe más de una estructura candidata, entonces analizar la existencia de F.C.C.
		else
		{
			//-------------------------------------------------------------------------
			//obtención de la cantidad de estructuras candidatas.
			upci_candidates_amount = in(this->BUFF_UPCI_ID_INDFRLIS_CAN->front().size());
			
			//-------------------------------------------------------------------------
			//paralelización del bucle for.
			#pragma omp parallel for

			//-------------------------------------------------------------------------  
			//bucle para conocer si existe F.C.C de las estructuras candidatas en upci i1.
			for (in i1 = 0; i1 < upci_candidates_amount; i1++)
			{
				//---------------------------------------------------------------------
				//obtención de id upci candidato.
				upci_id_candidate			= this->BUFF_UPCI_ID_INDFRLIS_CAN->front().at(i1);

				//---------------------------------------------------------------------
				//obtención de la cantidad de candidatos INDFRLIS en upci "i1".
				indfrlis_candidates_amout	= in(this->BUFF_INDFRLIS_ID_CAN->front().at(upci_id_candidate).size());
				
				//---------------------------------------------------------------------
				//bucle para conocer si existe F.C.C en la estructura candidata i2.
				for (in i2 = 0; i2 < indfrlis_candidates_amout; i2++)
				{
					//-----------------------------------------------------------------
					//obtención del id de la estructura.
					indfrlis_id_candidate = this->BUFF_INDFRLIS_ID_CAN->front().at(upci_id_candidate).at(i2);

					//-----------------------------------------------------------------
					//si la estructura tiene flujo de congruencias continuo, entonces.
					if (this->BUFF_UPCI->at(upci_id_candidate).ContinuousFlowOfCongruencesINDFRLIS(indfrlis_id_candidate))
					{
						//-------------------------------------------------------------
						//seteo de id de upci y estructura ganadora.
						winning_upci_id		= upci_id_candidate;
						winning_indfrlis_id	= indfrlis_id_candidate;

						//-------------------------------------------------------------
						//incremento de los ids INDFRLIS candidatos con F.C.C. 
						++indfrlis_with_fcc_amount;
					}
				}					
			}

			//-------------------------------------------------------------------------
			//actualización del estado de congruencia de estructuras candidatas anteriores.
			this->UpdateToNotCongruentBUFF_INDFRLIS();

			//-------------------------------------------------------------------------
			//si existe solo una estructura con F.C.C, entonces existe reconocimiento.
			if (indfrlis_with_fcc_amount == 1)
			{
				//---------------------------------------------------------------------
				//seteo de la estructura reconocida.
				this->BUFF_INDFRLIS_RE->Set(winning_upci_id, winning_indfrlis_id);
			}	
		}			
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método de diferenciación global para estructura INPRRLIS.
vo	UPCI_SDS::GlobalDifferentiationINPRRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variablea auxiliares para estructuras candidatas.	
	in upci_id_candidate			= NULL;													//id de la upci candidata.
	in inprrlis_id_candidate		= NULL;													//id de la estructura candidata.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variablea auxiliares para estructuras candidatas.	
	in winning_upci_id				= NULL;													//id de la upci ganadora.		
	in winning_inprrlis_id			= NULL;													//id de la estructura ganadora.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variablea auxiliares para cantidades.
	in upci_amount					= NULL;													//cantidad de upci existentes en el grupo.
	in upci_candidates_amount		= NULL;													//cantidad de upci con estructuras candidatas.
	in inprrlis_candidates_amout	= NULL;													//cantidad de estructuras cadidatas.			
	in inprrlis_with_fcc_amount		= NULL;													//cantidad de estructuras con F.C.C.	

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de upci existentes en el grupo.
	upci_amount						= this->GetAmountUpcGro();

	//---------------------------------------------------------------------------------
	//incremento del contador de diferenciaciones globales.
	++this->GLOBAL_DIFFERENTIATION_COUNTER;

	//---------------------------------------------------------------------------------
	//inicialización de buffers para candidatos.
	this->BUFF_UPCI_ID_INPRRLIS_CAN->push_front(deque<in>(0));
	this->BUFF_INPRRLIS_ID_CAN->push_front(deque<deque<in>>(0));
	this->BUFF_INPRRLIS_ID_CAN->front().resize(upci_amount);

	//---------------------------------------------------------------------------------
	//limpieza del buffer de estructura reconocida.
	this->BUFF_INPRRLIS_RE->Clean();
	
	//---------------------------------------------------------------------------------
	//paralelización del bucle for.
	#pragma omp parallel for

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para diferenciar BUFF_IN_PRO_RG con todas las upci.
	for (in i1 = 0; i1 < upci_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si existen estructuras INPRRLIS entonces diferenciar en la upci "i1".
		if (this->BUFF_UPCI->at(i1).BUFF_INPRRLIS_INI_AMOUNT > 0)
		{
			//-------------------------------------------------------------------------
			//diferenciación de BUFF_IN_PRO_RG en la upci "i1".
			this->BUFF_UPCI->at(i1).LocalDifferentiationINPRRLIS();
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para setear upci candidatas en buffer BUFF_UPCI_ID_INPRRLIS_CAN.
	for (in i1 = 0; i1 < upci_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si la upci "i1" contiene estructuras candidatas, entonces. 
		if (this->BUFF_INPRRLIS_ID_CAN->front().at(i1).size() > 0)
		{
			//-------------------------------------------------------------------------
			//seteo en buffer BUFF_UPCI_ID_INPRRLIS_CAN.
			this->BUFF_UPCI_ID_INPRRLIS_CAN->front().push_back(i1);
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existe alguna upci candidata, entonces.
	if (this->BUFF_UPCI_ID_INPRRLIS_CAN->front().size() > 0)
	{
		//-----------------------------------------------------------------------------
		//actualización del estado de congruencia de estructuras candidatas presentes.
		this->UpdateToCongruentBUFF_INPRRLIS();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existe solo una estructura candidata.
		if (this->BUFF_UPCI_ID_INPRRLIS_CAN->front().size() == 1 && this->BUFF_INPRRLIS_ID_CAN->front().at(this->BUFF_UPCI_ID_INPRRLIS_CAN->front().at(0)).size() == 1)
		{
			//-------------------------------------------------------------------------
			//actualización del estado de congruencia de estructuras candidatas anteriores.
			this->UpdateToNotCongruentBUFF_INPRRLIS();

			//-------------------------------------------------------------------------
			//obtención del id de la upci ganadora y del id de la estructura ganadora.
			winning_upci_id		= this->BUFF_UPCI_ID_INPRRLIS_CAN->front().at(0);
			winning_inprrlis_id	= this->BUFF_INPRRLIS_ID_CAN->front().at(upci_id_candidate).at(0);

			//-------------------------------------------------------------------------
			//seteo de la estructura reconocida.
			this->BUFF_INPRRLIS_RE->Set(winning_upci_id, winning_inprrlis_id);
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existe más de una estructura candidata, entonces analizar la existencia de F.C.C.
		else
		{
			//-------------------------------------------------------------------------
			//obtención de la cantidad de estructuras candidatas.
			upci_candidates_amount = in(this->BUFF_UPCI_ID_INPRRLIS_CAN->front().size());
			
			//-------------------------------------------------------------------------
			//paralelización del bucle for.
			#pragma omp parallel for

			//-------------------------------------------------------------------------  
			//bucle para conocer si existe F.C.C de las estructuras candidatas en upci i1.
			for (in i1 = 0; i1 < upci_candidates_amount; i1++)
			{
				//---------------------------------------------------------------------
				//obtención de id upci candidato.
				upci_id_candidate			= this->BUFF_UPCI_ID_INPRRLIS_CAN->front().at(i1);

				//---------------------------------------------------------------------
				//obtención de la cantidad de candidatos INPRRLIS en upci "i1".
				inprrlis_candidates_amout	= in(this->BUFF_INPRRLIS_ID_CAN->front().at(upci_id_candidate).size());
				
				//---------------------------------------------------------------------
				//bucle para conocer si existe F.C.C en la estructura candidata i2.
				for (in i2 = 0; i2 < inprrlis_candidates_amout; i2++)
				{
					//-----------------------------------------------------------------
					//obtención del id de la estructura.
					inprrlis_id_candidate = this->BUFF_INPRRLIS_ID_CAN->front().at(upci_id_candidate).at(i2);

					//-----------------------------------------------------------------
					//si la estructura tiene flujo de congruencias continuo, entonces.
					if (this->BUFF_UPCI->at(upci_id_candidate).ContinuousFlowOfCongruencesINPRRLIS(inprrlis_id_candidate))
					{
						//-------------------------------------------------------------
						//seteo de id de upci y estructura ganadora.
						winning_upci_id		= upci_id_candidate;
						winning_inprrlis_id	= inprrlis_id_candidate;

						//-------------------------------------------------------------
						//incremento de los ids INPRRLIS candidatos con F.C.C. 
						++inprrlis_with_fcc_amount;
					}
				}					
			}

			//-------------------------------------------------------------------------
			//actualización del estado de congruencia de estructuras candidatas anteriores.
			this->UpdateToNotCongruentBUFF_INPRRLIS();

			//-------------------------------------------------------------------------
			//si existe solo una estructura con F.C.C, entonces existe reconocimiento.
			if (inprrlis_with_fcc_amount == 1)
			{
				//---------------------------------------------------------------------
				//seteo de la estructura reconocida.
				this->BUFF_INPRRLIS_RE->Set(winning_upci_id, winning_inprrlis_id);
			}	
		}		
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método de diferenciación local para estructura INIS.
vo	UPCI_SDS::LocalDifferentiationINIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliares.	
	dou		congruence		= 0;															//nivel de congruencia de las estructuras.
	dou		best_congruence = 0;															//mejor nivel de congruencia.
	mutex	mut;																			//mutex.				

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//paralelización del bucle for.
	#pragma omp parallel for

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para diferenciar BUFF_IN_RG con todas las estructuras INIS.
	for (in i1 = 0; i1 < this->BUFF_INIS_MAX_ID[0] + 1; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura ha sido inicializada, entonces diferenciar.
		if (this->BUFF_INIS[i1].AL_SRG != -1)
		{
			//-------------------------------------------------------------------------
			//diferenciación.
			congruence = this->BUFF_INIS[i1].Differentiate(*this->BUFF_IN_RG);

			//-------------------------------------------------------------------------
			//bloqueo del hilo.
			mut.lock();

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si al congruencia en mejor, entonces.
			if(congruence > best_congruence)
			{			
				//---------------------------------------------------------------------
				//limpieza del buffer de candidatos.
				this->BUFF_INIS_ID_CAN->front().at(this->UPCI_ID).clear();

				//---------------------------------------------------------------------
				//seteo del nuevo candidato.
				this->BUFF_INIS_ID_CAN->front().at(this->UPCI_ID).push_back(i1);		

				//---------------------------------------------------------------------
				//actualización de la mejor congruencia.
				best_congruence = congruence;
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si al congruencia en igual, entonces.
			else if (congruence == best_congruence)
			{
				//---------------------------------------------------------------------
				//seteo de otro candidato.
				this->BUFF_INIS_ID_CAN->front().at(this->UPCI_ID).push_back(i1);
			}

			//-------------------------------------------------------------------------
			//desbloqueo del hilo.
			mut.unlock();
		}		
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la mejor congruencia supera el umbral de congruencia, entonces.
	if (best_congruence >= this->STR_CONGRUENCE_THRESHOLD && this->GetINIS_CONGRUENCE_ACCOMPLISHED() == OFF)
	{
		//-----------------------------------------------------------------------------
		//seteo del estado de la bandera 'INIS_CONGRUENCE_ACCOMPLISHED'.
		this->SetINIS_CONGRUENCE_ACCOMPLISHED(ON);
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método de diferenciación local para estructura INDFRLIS.
vo	UPCI_SDS::LocalDifferentiationINDFRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliares.	
	dou		congruence		= 0;															//nivel de congruencia de las estructuras.
	dou		best_congruence = 0;															//mejor nivel de congruencia.
	mutex	mut;																			//mutex.			

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//paralelización del bucle for.
	#pragma omp parallel for

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para diferenciar BUFF_IN_DIF_RG con todas las estructuras INDFRLIS.
	for (in i1 = 0; i1 < this->BUFF_INDFRLIS_MAX_ID[0] + 1; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura ha sido inicializada, entonces diferenciar.
		if (this->BUFF_INDFRLIS[i1].AL_SRG != -1)
		{
			//-------------------------------------------------------------------------
			//diferenciación.
			congruence = this->BUFF_INDFRLIS[i1].Differentiate(*this->BUFF_IN_DIF_RG);

			//-------------------------------------------------------------------------
			//bloqueo del hilo.
			mut.lock();

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si al congruencia en mejor, entonces.
			if (congruence > best_congruence)
			{
				//---------------------------------------------------------------------
				//limpieza del buffer de candidatos.
				this->BUFF_INDFRLIS_ID_CAN->front().at(this->UPCI_ID).clear();

				//---------------------------------------------------------------------
				//seteo del nuevo candidato.
				this->BUFF_INDFRLIS_ID_CAN->front().at(this->UPCI_ID).push_back(i1);

				//---------------------------------------------------------------------
				//actualización de la mejor congruencia.
				best_congruence = congruence;
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si al congruencia en igual, entonces.
			else if (congruence == best_congruence)
			{
				//---------------------------------------------------------------------
				//seteo de otro candidato.
				this->BUFF_INDFRLIS_ID_CAN->front().at(this->UPCI_ID).push_back(i1);
			}

			//-------------------------------------------------------------------------
			//desbloqueo del hilo.
			mut.unlock();
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la mejor congruencia supera el umbral de congruencia, entonces.
	if (best_congruence >= this->STR_CONGRUENCE_THRESHOLD && this->GetINDFRLIS_CONGRUENCE_ACCOMPLISHED() == OFF)
	{
		//-----------------------------------------------------------------------------
		//seteo del estado de la bandera 'INDFRLIS_CONGRUENCE_ACCOMPLISHED'.
		this->SetINDFRLIS_CONGRUENCE_ACCOMPLISHED(ON);
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método de diferenciación local para estructura INPRRLIS.
vo	UPCI_SDS::LocalDifferentiationINPRRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliares.	
	dou		congruence		= 0;															//nivel de congruencia de las estructuras.
	dou		best_congruence = 0;															//mejor nivel de congruencia.
	mutex	mut;																			//mutex.			

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//paralelización del bucle for.
	#pragma omp parallel for

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para diferenciar BUFF_IN_PRO_RG con todas las estructuras INPRRLIS.
	for (in i1 = 0; i1 < this->BUFF_INPRRLIS_MAX_ID[0] + 1; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura ha sido inicializada, entonces diferenciar.
		if (this->BUFF_INPRRLIS[i1].CS_SRG != -1)
		{
			//-------------------------------------------------------------------------
			//diferenciación.
			congruence = this->BUFF_INPRRLIS[i1].Differentiate(*this->BUFF_IN_PRO_RG);

			//-------------------------------------------------------------------------
			//bloqueo del hilo.
			mut.lock();

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si al congruencia en mejor, entonces.
			if (congruence > best_congruence)
			{
				//---------------------------------------------------------------------
				//limpieza del buffer de candidatos.
				this->BUFF_INPRRLIS_ID_CAN->front().at(this->UPCI_ID).clear();

				//---------------------------------------------------------------------
				//seteo del nuevo candidato.
				this->BUFF_INPRRLIS_ID_CAN->front().at(this->UPCI_ID).push_back(i1);

				//---------------------------------------------------------------------
				//actualización de la mejor congruencia.
				best_congruence = congruence;
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si al congruencia en igual, entonces.
			else if (congruence == best_congruence)
			{
				//---------------------------------------------------------------------
				//seteo de otro candidato.
				this->BUFF_INPRRLIS_ID_CAN->front().at(this->UPCI_ID).push_back(i1);
			}

			//-------------------------------------------------------------------------
			//desbloqueo del hilo.
			mut.unlock();
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la mejor congruencia supera el umbral de congruencia, entonces.
	if (best_congruence >= this->STR_CONGRUENCE_THRESHOLD && this->GetINPRRLIS_CONGRUENCE_ACCOMPLISHED() == OFF)
	{
		//-----------------------------------------------------------------------------
		//seteo del estado de la bandera 'INPRRLIS_CONGRUENCE_ACCOMPLISHED'.
		this->SetINPRRLIS_CONGRUENCE_ACCOMPLISHED(ON);
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para conocer si exite flujo continuo de congruencias en estructuras 
//candidatas tipo INIS.
in	UPCI_SDS::ContinuousFlowOfCongruencesINIS(in _inis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//declaraciones auxiliares.
	in			str_id				=   NULL;												//id auxiliar para estructuras.
	in			rl_type				=   NULL;												//id auxiliar para una estructura de relación de la estructura _inis_id.
	in			rl_id				=   NULL;												//id auxiliar para una estructura de relación de la estructura _inis_id.
	UPCI_SDS	*upci_ptr_rl_str	=	NULL;												//puntero auxiliar de la upci de la relación de la estructura _inis_id. 
	UPCI_SDS	*upci_id_rl_rl_str	=	NULL;												//puntero auxiliar de la upci de la relación de la relación de la estructura _inis_id.
	in			rl_amount			=   NULL;												//cantidad de relaciones.

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de relaciones de la estructura.
	rl_amount = this->BUFF_INIS[_inis_id].GetRelationAmount();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para verificar si existe una estructura congruente anterior contigua.
	for (in i1 = 0; i1 < rl_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del datos de la relación.
		rl_type			= this->BUFF_INIS[_inis_id].RL.at(i1).at(0);
		rl_id			= this->BUFF_INIS[_inis_id].RL.at(i1).at(1);
		upci_ptr_rl_str	= &this->BUFF_UPCI->at(this->BUFF_INIS[_inis_id].RL.at(i1).at(2));

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la relación es el tipo de flujo puro entrante, entonces.
		if (rl_type == -PFRLIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//obtención de datos de la primera estructura.
			upci_id_rl_rl_str	= &this->BUFF_UPCI->at(upci_ptr_rl_str->BUFF_PFRLIS[rl_id].UPCI_ID_STR1_RG);
			str_id				= upci_ptr_rl_str->BUFF_PFRLIS[rl_id].STR1_ID_RG;
			
			//-------------------------------------------------------------------------
			//si la estructura está en estado congruente, entonces la estructura 
			//tiene F.C.C.
			if (upci_id_rl_rl_str->BUFF_INIS[str_id].CS_SRG == ON)
			{
				//---------------------------------------------------------------------
				//seteo del índice de la relación utilizada en flujo de estructuras.
				*this->BUFF_RL_INDEX_USED_IN_RECOGNITION = i1;

				//---------------------------------------------------------------------
				//retornar.
				return ON;
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la relación es el tipo de flujo diferencial de entradas entrante, entonces.
		else if (rl_type == -INDFRLIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//id de la upci de la primera estructura.
			upci_id_rl_rl_str	= &this->BUFF_UPCI->at(upci_ptr_rl_str->BUFF_INDFRLIS[rl_id].UPCI_ID_STR1_RG);

			//-------------------------------------------------------------------------
			//carga del id del registro relacionado.
			str_id				= upci_ptr_rl_str->BUFF_INDFRLIS[rl_id].STR1_ID_RG;

			//-------------------------------------------------------------------------
			//si la estructura está en estado congruente, entonces la estructura tiene F.C.C.
			if (upci_id_rl_rl_str->BUFF_INIS[str_id].CS_SRG == ON)
			{
				//---------------------------------------------------------------------
				//seteo del índice de la relación utilizada en flujo de estructuras.
				*this->BUFF_RL_INDEX_USED_IN_RECOGNITION = i1;

				//---------------------------------------------------------------------
				//retornar.
				return ON;
			}
		}
	}	

	//---------------------------------------------------------------------------------
	//retorno de la no existencia de F.C.C.
	return OFF;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para conocer si exite flujo continuo de congruencias en estructuras 
//candidatas tipo INDFRLIS.
in	UPCI_SDS::ContinuousFlowOfCongruencesINDFRLIS(in _indfrlis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura INIS de inicio de relación _indfrlis_id.
	in str1_id					= NULL;														//id de la estructura INIS de inicio de la relación _indfrlis_id.
	in upci_id_str1				= NULL;														//id de la upci de la estructura INIS de inicio de la relación _indfrlis_id.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura INDFRLIS encontrada en INIS de inicio.
	in indfrlis_id_found		= NULL;														//id de la relación INDFRLIS encontrada en la estructura INIS str1_id.
	in upci_id_indfrlis_found	= NULL;														//id de la upci de la relación INDFRLIS encontrada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura INIS en relación encontrada.
	in str1_id_aux				= NULL;														//id de la estructura INIS de inicio de la relación INDFRLIS encontrada.
	in str2_id_aux				= NULL;														//id de la estructura INIS de fin de la relación INDFRLIS encontrada.
	in upci_id_str1_aux			= NULL;														//id de la upci de la estructura INIS de inicio de la relación INDFRLIS encontrada.
	in upci_id_str2_aux			= NULL;														//id de la upci de la estructura INIS de fin de la relación INDFRLIS encontrada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura INIS de fin de relación _indfrlis_id.
	in str2_id					= NULL;														//id de la estructura INIS de fin de la relación _indfrlis_id.
	in upci_id_str2				= NULL;														//id de la upci de la estructura INIS de fin de la relación _indfrlis_id.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bandera para chekear congruencia en estructura anterior.
	in check_congruence_flag	= OFF;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliar para índice de la relación entrante en estructura siguiente.
	in rl_index_in_str			= NULL;														

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para cantidad de relaciones.
	in rl_amount				= NULL;		

	//---------------------------------------------------------------------------------
	//obtención de datos de la estructura inicial.
	str1_id						= this->BUFF_INDFRLIS[_indfrlis_id].STR1_ID_RG;			
	upci_id_str1				= this->BUFF_INDFRLIS[_indfrlis_id].UPCI_ID_STR1_RG;		
	
	//---------------------------------------------------------------------------------
	//obtención de la cantidad de relaciones de la estructura INIS str1_id.
	rl_amount					= this->BUFF_UPCI->at(upci_id_str1).BUFF_INIS[str1_id].GetRelationAmount();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para verificar si existe una estructura congruente anterior contigua.
	for (in i1 = 0; i1 < rl_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si se encuentra una relación diferencial de entrada, entonces.
		if (abs(this->BUFF_UPCI->at(upci_id_str1).BUFF_INIS[str1_id].RL.at(i1).at(0)) == INDFRLIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//id de la relación INDFRLIS hallada.
			indfrlis_id_found		= this->BUFF_UPCI->at(upci_id_str1).BUFF_INIS[str1_id].RL.at(i1).at(1);

			//-------------------------------------------------------------------------
			//seteo del id de la upci de la relación INDFRLIS hallada.
			upci_id_indfrlis_found	= this->BUFF_UPCI->at(upci_id_str1).BUFF_INIS[str1_id].RL.at(i1).at(2);

			//-------------------------------------------------------------------------
			//obtención de datos de las estructuras relacionadas en INDFRLIS hallada.
			str1_id_aux				= this->BUFF_UPCI->at(upci_id_indfrlis_found).BUFF_INDFRLIS[indfrlis_id_found].STR1_ID_RG;
			str2_id_aux				= this->BUFF_UPCI->at(upci_id_indfrlis_found).BUFF_INDFRLIS[indfrlis_id_found].STR2_ID_RG;
			upci_id_str1_aux		= this->BUFF_UPCI->at(upci_id_indfrlis_found).BUFF_INDFRLIS[indfrlis_id_found].UPCI_ID_STR1_RG;
			upci_id_str2_aux		= this->BUFF_UPCI->at(upci_id_indfrlis_found).BUFF_INDFRLIS[indfrlis_id_found].UPCI_ID_STR2_RG;

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si las estructuras relacionadas son distintas, entonces.
			if(str1_id_aux != str1_id_aux && upci_id_str1_aux != upci_id_str1_aux)
			{ 
				//---------------------------------------------------------------------
				//si la relación encontrada es entrante, entonces.
				if (this->BUFF_UPCI->at(upci_id_str1).BUFF_INIS[str1_id].RL.at(i1).at(0) == -INDFRLIS_TYPE)
				{
					//-----------------------------------------------------------------
					//activación de la bandera para chekear congruencia.
					check_congruence_flag = ON;
				}
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si las estructuras relacionadas son iguales, entonces.
			else
			{
				//---------------------------------------------------------------------
				//activación de la bandera para chekear congruencia.
				check_congruence_flag = ON;
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la bandera para chekear congruencia está activada entonces.
			if (check_congruence_flag == ON)
			{
				//---------------------------------------------------------------------
				//si la estructura está en estado congruente, entonces la estructura tiene F.C.C.
				if (this->BUFF_UPCI->at(upci_id_indfrlis_found).BUFF_INDFRLIS[indfrlis_id_found].CS_SRG == ON)
				{
					//-----------------------------------------------------------------
					//si no existe una estructura INIS reconocida, entonces.
					if(this->BUFF_INIS_RE->STR_ID != -1)
					{
						//-------------------------------------------------------------
						//obtención de datos de la estructura final de _indfrlis_id.
						str2_id			= this->BUFF_INDFRLIS[_indfrlis_id].STR2_ID_RG;
						upci_id_str2	= this->BUFF_INDFRLIS[_indfrlis_id].UPCI_ID_STR2_RG;

						//-------------------------------------------------------------
						//obtención del índice de la relación utilizada en estructura INIS final.
						rl_index_in_str = this->BUFF_UPCI->at(upci_id_str2).BUFF_INIS[str2_id].GetRelationIndex(INDFRLIS_TYPE, _indfrlis_id, this->UPCI_ID);

						//-------------------------------------------------------------
						//seteo del índice de la relación utilizada en flujo de estructuras.
						*this->BUFF_RL_INDEX_USED_IN_RECOGNITION = rl_index_in_str;
					}

					//-----------------------------------------------------------------
					//retornar.
					return ON;
				}
			}			
		}
	}

	//---------------------------------------------------------------------------------
	//retorno de la no existencia de F.C.C.
	return OFF;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para conocer si exite flujo continuo de congruencias en estructuras 
//candidatas tipo INPRRLIS.
in	UPCI_SDS::ContinuousFlowOfCongruencesINPRRLIS(in _inprrlis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura INDFRLIS de inicio de relación _inprrlis_id.
	in str1_id					= NULL;														//id de la estructura INDFRLIS de inicio de la relación _inprrlis_id.
	in upci_id_str1				= NULL;														//id de la upci de la estructura INDFRLIS de inicio de la relación _inprrlis_id.		

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura INPRRLIS encontrada en INDFRLIS de inicio.
	in inprrlis_id_found		= NULL;														//id de la relación INPRRLIS encontrada en la estructura INDFRLIS str1_id.
	in upci_id_inprrlis_found	= NULL;														//id de la upci de la relación INPRRLIS encontrada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura INDFRLIS de fin de relación _inprrlis_id.
	in str2_id					= NULL;														//id de la estructura INDFRLIS de fin de la relación _inprrlis_id.
	in upci_id_str2				= NULL;														//id de la upci de la estructura INDFRLIS de fin de la relación _inprrlis_id.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliar para índice de la relación entrante en estructura siguiente.
	in rl_index_in_str			= NULL;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para cantidad de relaciones.
	in rl_amount				= NULL;	

	//---------------------------------------------------------------------------------
	//obtención de datos de la estructura inicial.
	str1_id						= this->BUFF_INPRRLIS[_inprrlis_id].STR1_ID_RG;			
	upci_id_str1				= this->BUFF_INPRRLIS[_inprrlis_id].UPCI_ID_STR1_RG;

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de relaciones de la estructura INDFRLIS str1_id.
	rl_amount					= this->BUFF_UPCI->at(upci_id_str1).BUFF_INDFRLIS[str1_id].GetRelationAmount();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para verificar si existe una estructura congruente anterior contigua.
	for (in i1 = 0; i1 < rl_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si se encuentra una relación proporcional de entrada entrante, entonces.
		if (this->BUFF_UPCI->at(upci_id_str1).BUFF_INDFRLIS[str1_id].RL.at(i1).at(0) == -INPRRLIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//id de la relación INPRRLIS hallada.
			inprrlis_id_found		= this->BUFF_UPCI->at(upci_id_str1).BUFF_INDFRLIS[str1_id].RL.at(i1).at(1);

			//-------------------------------------------------------------------------
			//seteo del id de la upci de la relación INPRRLIS hallada.
			upci_id_inprrlis_found	= this->BUFF_UPCI->at(upci_id_str1).BUFF_INDFRLIS[str1_id].RL.at(i1).at(2);

			//-------------------------------------------------------------------------
			//si la estructura está en estado congruente, entonces la estructura tiene F.C.C.
			if (this->BUFF_UPCI->at(upci_id_inprrlis_found).BUFF_INPRRLIS[inprrlis_id_found].CS_SRG == ON)
			{
				//---------------------------------------------------------------------
				//si no existe una estructura INIS reconocida, entonces.
				if (this->BUFF_INIS_RE->STR_ID != -1)
				{
					//-----------------------------------------------------------------
					//obtención de datos de la estructura final de _inprrlis_id.
					str2_id			= this->BUFF_INPRRLIS[_inprrlis_id].STR2_ID_RG;
					upci_id_str2	= this->BUFF_INPRRLIS[_inprrlis_id].UPCI_ID_STR2_RG;

					//-----------------------------------------------------------------
					//obtención del índice de la relación utilizada en estructura INDFRLIS final.
					rl_index_in_str = this->BUFF_UPCI->at(upci_id_str2).BUFF_INDFRLIS[str2_id].GetRelationIndex(INPRRLIS_TYPE, _inprrlis_id, this->UPCI_ID);

					//-----------------------------------------------------------------
					//seteo del índice de la relación utilizada en flujo de estructuras.
					*this->BUFF_RL_INDEX_USED_IN_RECOGNITION = rl_index_in_str;
				}				

				//---------------------------------------------------------------------
				//retornar.
				return ON;
			}
		}
	}

	//---------------------------------------------------------------------------------
	//retorno de la no existencia de F.C.C.
	return OFF;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para Clean buffer BUFF_INIS_ID_CAN y BUFF_UPCI_ID_INIS_CAN pasados.
vo	UPCI_SDS::CleanBuffersOfPreviousCandidatesINIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existen estructuras candidatas anteriores, Clean buffers.
	if (this->BUFF_INIS_ID_CAN->size() > 1)
	{ 		
		//-----------------------------------------------------------------------------
		//se limpiam buffers en tiempo [1].
		this->BUFF_INIS_ID_CAN->pop_back();
		this->BUFF_UPCI_ID_INIS_CAN->pop_back();
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para Clean buffer BUFF_INDFRLIS_ID_CAN y BUFF_UPCI_ID_INDFRLIS_CAN pasados.
vo	UPCI_SDS::CleanBuffersOfPreviousCandidatesINDFRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existen estructuras candidatas anteriores, Clean buffers.
	if (this->BUFF_INDFRLIS_ID_CAN->size() > 1)
	{
		//-----------------------------------------------------------------------------
		//se limpian buffers en tiempo [1].
		this->BUFF_INDFRLIS_ID_CAN->pop_back();
		this->BUFF_UPCI_ID_INDFRLIS_CAN->pop_back();
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para Clean buffer BUFF_INPRRLIS_ID_CAN y BUFF_UPCI_ID_INPRRLIS_CAN pasados.
vo	UPCI_SDS::CleanBuffersOfPreviousCandidatesINPRRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existen estructuras candidatas anteriores, Clean buffers.
	if (this->BUFF_INPRRLIS_ID_CAN->size() > 1)
	{
		//-----------------------------------------------------------------------------
		//se limpian buffers en tiempo [1].
		this->BUFF_INPRRLIS_ID_CAN->pop_back();
		this->BUFF_UPCI_ID_INPRRLIS_CAN->pop_back();
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para limpiar niveles de actividad de IS.
vo	UPCI_SDS::CleanActivityLevelIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existen estructuras en suspensión, actualizar niveles de actividad.
	if (this->CheckSUSPENDED_STRUCTURES() == ON)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//variables auxiliares.
		in			upci_id_str_sus		= NULL;												//id de la upci de la estructura en suspensión.
		in			str_id_sus			= NULL;												//id de la estructura en suspensión.
		in			str_sus_amount		= NULL;												//cantidad de estructuras suspendidas.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bloqueo para limpieza.
		this->RED_LIGHT_MUTEX.lock();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//obtención de la cantidad de estructuras INIS en suspensión.
		str_sus_amount = in(this->BUFF_INIS_SUS->size());			

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para limpiar niveles de actividad de estructuras INIS.
		for (in i1 = 0; i1 < str_sus_amount; i1++)
		{
			//-------------------------------------------------------------------------
			//seteo del id de la upci en suspensión y el id de estructura en suspensión.
			upci_id_str_sus		= this->BUFF_INIS_SUS->at(i1).UPCI_ID;
			str_id_sus			= this->BUFF_INIS_SUS->at(i1).STR_ID;

			//-------------------------------------------------------------------------
			//se limpia el nivel de actividad.
			this->BUFF_UPCI->at(upci_id_str_sus).BUFF_INIS[str_id_sus].AL_SRG = 0;
		}

		//-----------------------------------------------------------------------------
		//obtención de la cantidad de estructuras PFRLIS en suspensión.
		str_sus_amount = in(this->BUFF_PFRLIS_SUS->size());			

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para limpiar niveles de actividad de estructuras PFRLIS.
		for (in i1 = 0; i1 < str_sus_amount; i1++)
		{
			//-------------------------------------------------------------------------
			//seteo del id de la upci en suspensión y el id de estructura en suspensión.
			upci_id_str_sus		= this->BUFF_PFRLIS_SUS->at(i1).UPCI_ID;
			str_id_sus			= this->BUFF_PFRLIS_SUS->at(i1).STR_ID;

			//-------------------------------------------------------------------------
			//se limpia el nivel de actividad.
			this->BUFF_UPCI->at(upci_id_str_sus).BUFF_PFRLIS[str_id_sus].AL_SRG = 0;
		}

		//-----------------------------------------------------------------------------
		//obtención de la cantidad de estructuras INDFRLIS en suspensión.
		str_sus_amount = in(this->BUFF_INDFRLIS_SUS->size());			

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para limpiar niveles de actividad de estructuras INDFRLIS.
		for (in i1 = 0; i1 < str_sus_amount; i1++)
		{
			//-------------------------------------------------------------------------
			//seteo del id de la upci en suspensión y el id de estructura en suspensión.
			upci_id_str_sus		= this->BUFF_INDFRLIS_SUS->at(i1).UPCI_ID;
			str_id_sus			= this->BUFF_INDFRLIS_SUS->at(i1).STR_ID;

			//-------------------------------------------------------------------------
			//se limpia el nivel de actividad.
			this->BUFF_UPCI->at(upci_id_str_sus).BUFF_INDFRLIS[str_id_sus].AL_SRG = 0;
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//limpieza del buffer de IS en suspensión.
		this->BUFF_INIS_SUS->clear();
		this->BUFF_PFRLIS_SUS->clear();
		this->BUFF_INDFRLIS_SUS->clear();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//reset del buffer para el flujo de estructuras activadas.
		this->BUFF_INIS_ACTIVATED[0].Clean();
		this->BUFF_INIS_ACTIVATED[1].Clean();
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//desbloqueo de la limpieza.
		this->RED_LIGHT_MUTEX.unlock();
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método thread para actualizar niveles de actividad de IS.
vo	UPCI_SDS::UpdateActivityLevelIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del tiempos de espera.
	chrono::milliseconds timeout_update_al_is(this->TIMEOUT_UPDATE_AL_IS);
	chrono::milliseconds timeout_update_al_slow(TIMEOUT_LOOP_SLOW);
	
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//bucle para actualización.
	while (this->GetCLOSE_ACTIVE_THREADS_FLAG() == OFF)
	{
		//-----------------------------------------------------------------------------
		//espera para ejecutar actualización.
		this_thread::sleep_for(timeout_update_al_is);
		
		//-----------------------------------------------------------------------------
		//si la gupci esta en pausa, entonces esperar.
		while (this->GetPAUSE_ACTIVE_THREADS_FLAG() == ON && this->GetCLOSE_ACTIVE_THREADS_FLAG() == OFF)	this_thread::sleep_for(timeout_update_al_slow);
	
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existen estructuras en suspensión, actualizar niveles de actividad.
		if (this->CheckSUSPENDED_STRUCTURES() == ON)
		{
			//-------------------------------------------------------------------------
			//bloqueo para actualización de buffers.
			this->RED_LIGHT_MUTEX.lock();

			//-------------------------------------------------------------------------
			//impresión del comienzo de la actualización del nivel de actividad de los buffers.
			//this->Print("> actualizacion de niveles de actividad de buffers iniciada...");

			//-------------------------------------------------------------------------
			//variables auxiliares.
			in			upci_id_str_sus		= NULL;											//id de la upci de la estructura en suspensión.
			in			str_id_sus			= NULL;											//id de la estructura en suspensión.
			in			str_sus_amount		= NULL;											//cantidad de estructuras suspendidas.

			//-------------------------------------------------------------------------
			//obtención de la cantidad de estructuras INIS en suspensión.
			str_sus_amount = in(this->BUFF_INIS_SUS->size());			
			
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para limpiar niveles de actividad de estructuras INIS.
			for (in i1 = 0; i1 < str_sus_amount;)
			{
				//---------------------------------------------------------------------
				//seteo del id de la upci en suspensión y el id de estructura en suspensión.
				upci_id_str_sus		= this->BUFF_INIS_SUS->at(i1).UPCI_ID;
				str_id_sus			= this->BUFF_INIS_SUS->at(i1).STR_ID;

				//---------------------------------------------------------------------
				//se decrementa el nivel de actividad.
				this->BUFF_UPCI->at(upci_id_str_sus).BUFF_INIS[str_id_sus].AL_SRG -= 1;
				
				//---------------------------------------------------------------------
				//si nivel de actividad es "0", quitar de buffer IS en suspensión.
				if (this->BUFF_UPCI->at(upci_id_str_sus).BUFF_INIS[str_id_sus].AL_SRG == 0)
				{
					//-----------------------------------------------------------------
					//eliminación del elemento de los buffers de IS en suspensión.
					this->BUFF_INIS_SUS->erase(this->BUFF_INIS_SUS->begin() + i1);

					//-----------------------------------------------------------------
					//actualización de la cantidad de relaciones.
					str_sus_amount -= 1;
				}

				//---------------------------------------------------------------------
				//incremento de i1.
				else ++i1;
			}

			//-------------------------------------------------------------------------
			//obtención de la cantidad de estructuras PFRLIS en suspensión.
			str_sus_amount = in(this->BUFF_PFRLIS_SUS->size());			
			
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para limpiar niveles de actividad de estructuras PFRLIS.
			for (in i1 = 0; i1 < str_sus_amount;)
			{
				//---------------------------------------------------------------------
				//seteo del id de la upci en suspensión y el id de estructura en suspensión.
				upci_id_str_sus		= this->BUFF_PFRLIS_SUS->at(i1).UPCI_ID;
				str_id_sus			= this->BUFF_PFRLIS_SUS->at(i1).STR_ID;

				//---------------------------------------------------------------------
				//se decrementa el nivel de actividad.
				this->BUFF_UPCI->at(upci_id_str_sus).BUFF_PFRLIS[str_id_sus].AL_SRG -= 1;
				
				//---------------------------------------------------------------------
				//si nivel de actividad es "0", quitar de buffer IS en suspensión.
				if (this->BUFF_UPCI->at(upci_id_str_sus).BUFF_PFRLIS[str_id_sus].AL_SRG == 0)
				{					
					//-----------------------------------------------------------------
					//eliminación del elemento de los buffers de IS en suspensión.
					this->BUFF_PFRLIS_SUS->erase(this->BUFF_PFRLIS_SUS->begin() + i1);

					//-----------------------------------------------------------------
					//actualización de la cantidad de relaciones.
					str_sus_amount -= 1;

					//-----------------------------------------------------------------
					//si la IS al salir del estado en suspensión no supera el 
					//umbral del fortaleza de la relación, entonces.
					if (this->BUFF_UPCI->at(upci_id_str_sus).BUFF_PFRLIS[str_id_sus].RS_SRG < this->PFRLIS_STRENGTH_THRESHOLD)
					{
						//-------------------------------------------------------------
						//eliminación de la estructura de información.
						this->BUFF_UPCI->at(upci_id_str_sus).DeletePFRLIS(str_id_sus);
					}
				}

				//---------------------------------------------------------------------
				//incremento de i1.
				else ++i1;
			}

			//-------------------------------------------------------------------------
			//obtención de la cantidad de estructuras INDFRLIS en suspensión.
			str_sus_amount = in(this->BUFF_INDFRLIS_SUS->size());			
			
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para limpiar niveles de actividad de estructuras INDFRLIS.
			for (in i1 = 0; i1 < str_sus_amount;)
			{
				//---------------------------------------------------------------------
				//seteo del id de la upci en suspensión y el id de estructura en suspensión.
				upci_id_str_sus		= this->BUFF_INDFRLIS_SUS->at(i1).UPCI_ID;
				str_id_sus			= this->BUFF_INDFRLIS_SUS->at(i1).STR_ID;

				//---------------------------------------------------------------------
				//se decrementa el nivel de actividad.
				this->BUFF_UPCI->at(upci_id_str_sus).BUFF_INDFRLIS[str_id_sus].AL_SRG -= 1;

				//---------------------------------------------------------------------
				//si nivel de actividad es "0", quitar de buffer IS en suspensión.
				if (this->BUFF_UPCI->at(upci_id_str_sus).BUFF_INDFRLIS[str_id_sus].AL_SRG == 0)
				{
					//-----------------------------------------------------------------
					//eliminación del elemento de los buffers de IS en suspensión.
					this->BUFF_INDFRLIS_SUS->erase(this->BUFF_INDFRLIS_SUS->begin() + i1);

					//-----------------------------------------------------------------
					//actualización de la cantidad de relaciones.
					str_sus_amount -= 1;

					//-----------------------------------------------------------------
					//si la IS al salir del estado en suspensión no supera el 
					//umbral del fortaleza de la relación, entonces.
					if (this->BUFF_UPCI->at(upci_id_str_sus).BUFF_INDFRLIS[str_id_sus].RS_SRG < this->INDFRLIS_STRENGTH_THRESHOLD)
					{
						//-------------------------------------------------------------
						//eliminación de la estructura de información.
						this->BUFF_UPCI->at(upci_id_str_sus).DeleteINDFRLIS(str_id_sus);
					}
				}

				//---------------------------------------------------------------------
				//incremento de i1.
				else ++i1;
			}
			
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si ya no existen estructuras en estado de suspensión.
			if (this->BUFF_INIS_SUS->size()		== 0	&&
				this->BUFF_PFRLIS_SUS->size()	== 0	&&
				this->BUFF_INDFRLIS_SUS->size()	== 0)
			{
				//---------------------------------------------------------------------
				//reset del buffer para el flujo de estructuras activadas.
				this->BUFF_INIS_ACTIVATED[0].Clean();
				this->BUFF_INIS_ACTIVATED[1].Clean();
			}

			//-------------------------------------------------------------------------
			//carga de buffers para la cantidad de estructuras existentes.
			//cout << "BUFF_INIS_INI_AMOUNT     : " << this->BUFF_INIS_INI_AMOUNT << endl;
			//cout << "BUFF_ACIS_INI_AMOUNT      : " << this->BUFF_ACIS_INI_AMOUNT << endl;
			//cout << "BUFF_PFRLIS_INI_AMOUNT     : " << this->BUFF_PFRLIS_INI_AMOUNT << endl;
			//cout << "BUFF_INDFRLIS_INI_AMOUNT   : " << this->BUFF_INDFRLIS_INI_AMOUNT << endl;
			//cout << "BUFF_INPRRLIS_INI_AMOUNT   : " << this->BUFF_INPRRLIS_INI_AMOUNT << endl;

			////-------------------------------------------------------------------------
			////carga de buffers para la cantidad de estructuras suspendidas.
			//cout << "cantidad INIS suspendidas: "<< this->BUFF_INIS_SUS->size() << endl;
			//cout << "cantidad ACIS suspendidas :" << this->BUFF_ACIS_SUS->size() << endl;
			//cout << "cantidad PFRLIS suspendidas :"<< this->BUFF_PFRLIS_SUS->size() << endl;
			//cout << "cantidad INDFRLIS suspendidas :"<< this->BUFF_INDFRLIS_SUS->size() << endl;

			//-------------------------------------------------------------------------
			//impresión de la finalización de la actualización del nivel de actividad de los buffers.
			//this->Print("> actualizacion de niveles de actividad de buffers finalizada.");

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//desbloqueo para actualización de buffers.
			this->RED_LIGHT_MUTEX.unlock();
		}			
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------  
//#1: método para actualizar buffer tras eliminar IS INIS.
vo	UPCI_SDS::UpdateBuffersAfterCreatingINIS(in _inis_id, dou _al_srg)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//declaración del id candidato para una nueva creación.
	in candidate_id				= -1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incremento de la cantidad existente de estructuras.
	++this->BUFF_INIS_INI_AMOUNT;
	++this->BUFF_TOTAL_STR_INI_AMOUNT;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//reset del id disponible utilizado.
	this->BUFF_INIS_ID_AV[0]	= -1;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de estructura INIS creada.
	this->SetBUFF_INIS_CRE(_inis_id);	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de la estructura INIS activada.
	this->SetBUFF_INIS_ACTIVATED(_inis_id);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de la estructura suspendida.
	this->SetBUFF_STR_SUS(_inis_id, INIS_TYPE);	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si el id es mayor que el máximo id, update BUFF_INIS_MAX_ID.
	if (this->BUFF_INIS_MAX_ID[0] < _inis_id)
	{
		//-----------------------------------------------------------------------------
		//actualización de BUFF_INIS_MAX_ID.
		this->BUFF_INIS_MAX_ID[1] = this->BUFF_INIS_MAX_ID[0];
		this->BUFF_INIS_MAX_ID[0] = _inis_id;
	}

	//---------------------------------------------------------------------------------
	//si el id es mayor que el segundo máximo id, update BUFF_INIS_MAX_ID.
	else if (this->BUFF_INIS_MAX_ID[1] < _inis_id)
	{
		//-----------------------------------------------------------------------------
		//actualización de BUFF_INIS_MAX_ID.
		this->BUFF_INIS_MAX_ID[1] = _inis_id;
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la evaluación actual es mayor al máximo, entonces setear la nueva máxima 
	//evaluación de entrada.
	if (*this->BUFF_MAX_EVALUATION		< *this->BUFF_EV_RG)	this->SetBUFF_INIS_MAX_EVAL(_inis_id, *this->BUFF_EV_RG);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si el nivel de actividad actual es mayor al máximo, entonces setear el nuevo 
	//máximo nivel de actividad.
	if (*this->BUFF_MAX_ACTIVITY_LEVEL < _al_srg)				this->SetBUFF_INIS_MAX_AL(_inis_id, _al_srg);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si se ha definido el id en la posición [1], entonces setear [0].
	if (this->BUFF_INIS_ID_AV[1] != -1)
	{
		//-----------------------------------------------------------------------------
		//seteo del id candidato para la creación de una nueva estructura.
		this->BUFF_INIS_ID_AV[0] = this->BUFF_INIS_ID_AV[1];
		this->BUFF_INIS_ID_AV[1] = -1;
	}	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del id de la estructura INIS disponible, si no se ha llenado el buffer.
	else if (this->BUFF_INIS_INI_AMOUNT < this->INIS_AMOUNT_ALLOWED)
	{
		//-----------------------------------------------------------------------------
		//bucle para hallar el id de una estructura sin inicializar.
		for (in i1 = 0; i1 < this->INIS_AMOUNT_ALLOWED; i1++)
		{
			//-------------------------------------------------------------------------
			//si la estructura no se ha inicializado, entonces.
			if (this->BUFF_INIS[i1].AL_SRG == -1)
			{
				//---------------------------------------------------------------------
				//seteo del id candidato para la creación de una nueva estructura.
				this->BUFF_INIS_ID_AV[0] = i1;
					
				//---------------------------------------------------------------------
				//salir del bucle.
				break;
			}
		}	
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del id de la estructura INIS disponible, si se ha llenado el buffer.
	else
	{
		//-----------------------------------------------------------------------------
		//declaración de la cantidad de relaciones de la estructura candidata.
		in rl_amount	= NULL;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existen estructuras no suspendidas, entonces.
		if (this->BUFF_INIS_SUS->size() < this->BUFF_INIS_INI_AMOUNT)
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para inicializar id y cantidad de relaciones de la estructura candidata.
			for (in i1 = 0; i1 < this->BUFF_INIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//si la estructura está no está suspendida, entonces. 
				if (this->BUFF_INIS[i1].AL_SRG == 0)
				{
					//-----------------------------------------------------------------
					//seteo.
					candidate_id	= i1;
					rl_amount		= this->BUFF_INIS[i1].GetRelationAmount();

					//-----------------------------------------------------------------
					//salida del bucle.
					break;
				}
			}
			
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para hallar la estructura con la menor cantidad de relaciones.
			for (in i1 = 0; i1 < this->BUFF_INIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//si la estructura no está en suspensión.
				if (this->BUFF_INIS[i1].AL_SRG == 0)
				{
					//-----------------------------------------------------------------
					//si la estructura posee una menor fortaleza de relación
					if (this->BUFF_INIS[i1].GetRelationAmount()	<	rl_amount &&
						candidate_id							!=	i1)
					{
						//-------------------------------------------------------------
						//seteo de un nuevo id candidato.
						candidate_id	= i1;
						rl_amount		= this->BUFF_INIS[i1].GetRelationAmount();
					}
				}
			}
		}	

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existen estructuras no suspendidas, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para inicializar id y cantidad de relaciones de la estructura candidata.
			for (in i1 = 0; i1 < this->BUFF_INIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//si la estructura es distinta de las creadas, entonces. 
				if (this->BUFF_INIS_CRE[0].STR_ID != i1 && this->BUFF_INIS_CRE[1].STR_ID != i1)
				{
					//-----------------------------------------------------------------
					//seteo.
					candidate_id	= i1;
					rl_amount		= this->BUFF_INIS[i1].GetRelationAmount();

					//-----------------------------------------------------------------
					//salida del bucle.
					break;
				}
			}
			
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para hallar la estructura con la menor cantidad de relaciones.
			for (in i1 = 0; i1 < this->BUFF_INIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//emparejamiento para selección de la estructura con menor cantidad de relaciones.
				if (this->BUFF_INIS[i1].GetRelationAmount()	<		rl_amount	&&
					this->BUFF_INIS_CRE[0].STR_ID			!=		i1			&&
					this->BUFF_INIS_CRE[1].STR_ID			!=		i1			&&
					candidate_id							!=		i1)
				{
					//-----------------------------------------------------------------
					//seteo de un nuevo id candidato.
					candidate_id	= i1;
					rl_amount		= this->BUFF_INIS[i1].GetRelationAmount();
				}
			}
		}

		//-----------------------------------------------------------------------------
		//limpieza de la estructura con id candidato.		
		this->DeleteINIS(candidate_id);
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------  
//#2: método para actualizar buffer tras eliminar IS PFRLIS.
vo	UPCI_SDS::UpdateBuffersAfterCreatingPFRLIS(in _pfrlis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//declaración del id candidato para una nueva creación.
	in candidate_id				= -1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incremento de la cantidad existente de estructuras.
	++this->BUFF_PFRLIS_INI_AMOUNT;
	++this->BUFF_TOTAL_STR_INI_AMOUNT;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//reset del id disponible utilizado.
	this->BUFF_PFRLIS_ID_AV[0]	= -1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de estructura PFRLIS creada.
	this->SetBUFF_PFRLIS_CRE(_pfrlis_id);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de la estructura suspendida.
	this->SetBUFF_STR_SUS(_pfrlis_id, PFRLIS_TYPE);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si el id es mayor que el máximo id, update BUFF_PFRLIS_MAX_ID.
	if (this->BUFF_PFRLIS_MAX_ID[0] < _pfrlis_id)
	{
		//-----------------------------------------------------------------------------
		//actualización de BUFF_PFRLIS_MAX_ID.
		this->BUFF_PFRLIS_MAX_ID[1] = this->BUFF_PFRLIS_MAX_ID[0];
		this->BUFF_PFRLIS_MAX_ID[0] = _pfrlis_id;
	}

	//---------------------------------------------------------------------------------
	//si el id es mayor que el segundo máximo id, update BUFF_PFRLIS_MAX_ID.
	else if (this->BUFF_PFRLIS_MAX_ID[1] < _pfrlis_id)
	{
		//-----------------------------------------------------------------------------
		//actualización de BUFF_PFRLIS_MAX_ID.
		this->BUFF_PFRLIS_MAX_ID[1] = _pfrlis_id;
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si se ha definido el id en la posición [1], entonces setear [0].
	if (this->BUFF_PFRLIS_ID_AV[1] != -1)
	{
		//-----------------------------------------------------------------------------
		//seteo del id candidato para la creación de una nueva estructura.
		this->BUFF_PFRLIS_ID_AV[0] = this->BUFF_PFRLIS_ID_AV[1];
		this->BUFF_PFRLIS_ID_AV[1] = -1;
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del id de la estructura PFRLIS disponible, si no se ha llenado el buffer.
	else if (this->BUFF_PFRLIS_INI_AMOUNT < this->RLIS_AMOUNT_ALLOWED)
	{
		//-----------------------------------------------------------------------------
		//bucle para hallar el id de una estructura sin inicializar.
		for (in i1 = 0; i1 < this->RLIS_AMOUNT_ALLOWED; i1++)
		{
			//-------------------------------------------------------------------------
			//si la estructura no se ha inicializado, entonces.
			if (this->BUFF_PFRLIS[i1].RS_SRG == -1)
			{
				//---------------------------------------------------------------------
				//seteo del id candidato para la creación de una nueva estructura.
				this->BUFF_PFRLIS_ID_AV[0] = i1;

				//---------------------------------------------------------------------
				//salir del bucle.
				break;
			}
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del id de la estructura PFRLIS disponible, si se ha llenado el buffer.
	else
	{
		//-----------------------------------------------------------------------------
		//declaración de la fortaleza de la relación de la estructura candidata.
		dou relation_strength   = NULL;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existen estructuras no suspendidas, entonces.
		if (this->BUFF_PFRLIS_SUS->size() < this->BUFF_PFRLIS_INI_AMOUNT)
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para inicializar id y fortaleza de la relación de la estructura candidata.
			for (in i1 = 0; i1 < this->BUFF_PFRLIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//si la estructura está no está suspendida, entonces. 
				if (this->BUFF_PFRLIS[i1].AL_SRG == 0)
				{
					//-----------------------------------------------------------------
					//seteo.
					candidate_id		= i1;
					relation_strength	= this->BUFF_PFRLIS[i1].RS_SRG;

					//-----------------------------------------------------------------
					//salida del bucle.
					break;
				}
			}
		
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para hallar la estructura con la menor fortaleza de la relación.
			for (in i1 = 0; i1 < this->BUFF_PFRLIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//si la estructura no está en suspensión.
				if (this->BUFF_PFRLIS[i1].AL_SRG == 0)
				{
					//-----------------------------------------------------------------
					//si la estructura posee una menor fortaleza de relación
					if (this->BUFF_PFRLIS[i1].RS_SRG	<	relation_strength && 
						candidate_id					!=	i1)
					{
						//-------------------------------------------------------------
						//seteo de un nuevo id candidato.
						candidate_id		= i1;
						relation_strength	= this->BUFF_PFRLIS[i1].RS_SRG;
					}
				}
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existen estructuras no suspendidas, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para inicializar id y fortaleza de la relación de la estructura candidata.
			for (in i1 = 0; i1 < this->BUFF_PFRLIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//si la estructura es distinta de las creadas, entonces. 
				if (this->BUFF_PFRLIS_CRE[0].STR_ID	!= i1 && this->BUFF_PFRLIS_CRE[1].STR_ID != i1)
				{
					//-----------------------------------------------------------------
					//seteo.
					candidate_id		= i1;
					relation_strength	= this->BUFF_PFRLIS[i1].RS_SRG;

					//-----------------------------------------------------------------
					//salida del bucle.
					break;
				}
			}
		
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para hallar la estructura con la menor fortaleza de la relación.
			for (in i1 = 0; i1 < this->BUFF_PFRLIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//emparejamiento para selección de la estructura con menor fortaleza de la relación.
				if (this->BUFF_PFRLIS[i1].RS_SRG		<		relation_strength	&&	
					this->BUFF_PFRLIS_CRE[0].STR_ID		!=		i1					&&
					this->BUFF_PFRLIS_CRE[1].STR_ID		!=		i1					&&
					candidate_id						!=		i1)
				{
					//-----------------------------------------------------------------
					//seteo de un nuevo id candidato.
					candidate_id		= i1;
					relation_strength	= this->BUFF_PFRLIS[i1].RS_SRG;
				}
			}
		}		
		
		//-----------------------------------------------------------------------------
		//limpieza de la estructura con id candidato.
		this->DeletePFRLIS(candidate_id);
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------  
//#3: método para actualizar buffer tras eliminar IS INDFRLIS.
vo	UPCI_SDS::UpdateBuffersAfterCreatingINDFRLIS(in _indfrlis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//declaración del id candidato para una nueva creación.
	in candidate_id					= -1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incremento de la cantidad existente de estructuras.
	++this->BUFF_INDFRLIS_INI_AMOUNT;
	++this->BUFF_TOTAL_STR_INI_AMOUNT;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//reset del id disponible utilizado.
	this->BUFF_INDFRLIS_ID_AV[0]	= -1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de estructura INDFRLIS creada.
	this->SetBUFF_INDFRLIS_CRE(_indfrlis_id);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de la estructura suspendida.
	this->SetBUFF_STR_SUS(_indfrlis_id, INDFRLIS_TYPE);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si el id es mayor que el máximo id, update BUFF_INDFRLIS_MAX_ID.
	if (this->BUFF_INDFRLIS_MAX_ID[0] < _indfrlis_id)
	{
		//-----------------------------------------------------------------------------
		//actualización de BUFF_INDFRLIS_MAX_ID.
		this->BUFF_INDFRLIS_MAX_ID[1] = this->BUFF_INDFRLIS_MAX_ID[0];
		this->BUFF_INDFRLIS_MAX_ID[0] = _indfrlis_id;
	}

	//---------------------------------------------------------------------------------
	//si el id es mayor que el segundo máximo id, update BUFF_INDFRLIS_MAX_ID.
	else if (this->BUFF_INDFRLIS_MAX_ID[1] < _indfrlis_id)
	{
		//-----------------------------------------------------------------------------
		//actualización de BUFF_INDFRLIS_MAX_ID.
		this->BUFF_INDFRLIS_MAX_ID[1] = _indfrlis_id;
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si se ha definido el id en la posición [1], entonces setear [0].
	if (this->BUFF_INDFRLIS_ID_AV[1] != -1)
	{
		//-----------------------------------------------------------------------------
		//seteo del id candidato para la creación de una nueva estructura.
		this->BUFF_INDFRLIS_ID_AV[0] = this->BUFF_INDFRLIS_ID_AV[1];
		this->BUFF_INDFRLIS_ID_AV[1] = -1;
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del id de la estructura INDFRLIS disponible, si no se ha llenado el buffer.
	else if (this->BUFF_INDFRLIS_INI_AMOUNT < this->RLIS_AMOUNT_ALLOWED)
	{
		//-----------------------------------------------------------------------------
		//bucle para hallar el id de una estructura sin inicializar.
		for (in i1 = 0; i1 < this->RLIS_AMOUNT_ALLOWED; i1++)
		{
			//-------------------------------------------------------------------------
			//si la estructura no se ha inicializado, entonces.
			if (this->BUFF_INDFRLIS[i1].RS_SRG == -1)
			{
				//---------------------------------------------------------------------
				//seteo del id candidato para la creación de una nueva estructura.
				this->BUFF_INDFRLIS_ID_AV[0] = i1;

				//---------------------------------------------------------------------
				//salir del bucle.
				break;
			}
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del id de la estructura INDFRLIS disponible, si se ha llenado el buffer.
	else
	{
		//-----------------------------------------------------------------------------
		//declaración de la fortaleza de la relación de la estructura candidata.
		dou relation_strength   = NULL;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existen estructuras no suspendidas, entonces.
		if (this->BUFF_INDFRLIS_SUS->size() < this->BUFF_INDFRLIS_INI_AMOUNT)
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para inicializar id y fortaleza de la relación de la estructura candidata.
			for (in i1 = 0; i1 < this->BUFF_INDFRLIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//si la estructura está no está suspendida, entonces. 
				if (this->BUFF_INDFRLIS[i1].AL_SRG == 0)
				{
					//-----------------------------------------------------------------
					//seteo.
					candidate_id		= i1;
					relation_strength	= this->BUFF_INDFRLIS[i1].RS_SRG;

					//-----------------------------------------------------------------
					//salida del bucle.
					break;
				}
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para hallar la estructura con la menor fortaleza de la relación.
			for (in i1 = 0; i1 < this->BUFF_INDFRLIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//si la estructura no está en suspensión.
				if (this->BUFF_INDFRLIS[i1].AL_SRG == 0)
				{
					//-----------------------------------------------------------------
					//si la estructura posee una menor fortaleza de relación
					if (this->BUFF_INDFRLIS[i1].RS_SRG	<	relation_strength &&
						candidate_id					!=	i1)
					{
						//-------------------------------------------------------------
						//seteo de un nuevo id candidato.
						candidate_id		= i1;
						relation_strength	= this->BUFF_INDFRLIS[i1].RS_SRG;
					}
				}
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existen estructuras no suspendidas, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para inicializar id y fortaleza de la relación de la estructura candidata.
			for (in i1 = 0; i1 < this->BUFF_INDFRLIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//si la estructura es distinta de las creadas, entonces. 
				if (this->BUFF_INDFRLIS_CRE[0].STR_ID != i1 && this->BUFF_INDFRLIS_CRE[1].STR_ID != i1)
				{
					//-----------------------------------------------------------------
					//seteo.
					candidate_id		= i1;
					relation_strength	= this->BUFF_INDFRLIS[i1].RS_SRG;

					//-----------------------------------------------------------------
					//salida del bucle.
					break;
				}
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para hallar la estructura con la menor fortaleza de la relación.
			for (in i1 = 0; i1 < this->BUFF_INDFRLIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//emparejamiento para selección de la estructura con menor fortaleza de la relación.
				if (this->BUFF_INDFRLIS[i1].RS_SRG		<		relation_strength	&&
					this->BUFF_INDFRLIS_CRE[0].STR_ID	!=		i1					&&
					this->BUFF_INDFRLIS_CRE[1].STR_ID	!=		i1					&&
					candidate_id						!=		i1)
				{
					//-----------------------------------------------------------------
					//seteo de un nuevo id candidato.
					candidate_id		= i1;
					relation_strength	= this->BUFF_INDFRLIS[i1].RS_SRG;
				}
			}
		}		

		//-----------------------------------------------------------------------------
		//limpieza de la estructura con id candidato.
		this->DeleteINDFRLIS(candidate_id);
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------  
//#4: método para actualizar buffer tras eliminar IS INPRRLIS.
vo	UPCI_SDS::UpdateBuffersAfterCreatingINPRRLIS(in _inprrlis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//declaración del id candidato para una nueva creación.
	in candidate_id					= -1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incremento de la cantidad existente de estructuras.
	++this->BUFF_INPRRLIS_INI_AMOUNT;
	++this->BUFF_TOTAL_STR_INI_AMOUNT;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//reset del id disponible utilizado.
	this->BUFF_INPRRLIS_ID_AV[0]	= -1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de estructura INPRRLIS creada.
	this->SetBUFF_INPRRLIS_CRE(_inprrlis_id);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si el id es mayor que el máximo id, update BUFF_INPRRLIS_MAX_ID.
	if (this->BUFF_INPRRLIS_MAX_ID[0] < _inprrlis_id)
	{
		//-----------------------------------------------------------------------------
		//actualización de BUFF_INPRRLIS_MAX_ID.
		this->BUFF_INPRRLIS_MAX_ID[1] = this->BUFF_INPRRLIS_MAX_ID[0];
		this->BUFF_INPRRLIS_MAX_ID[0] = _inprrlis_id;
	}

	//---------------------------------------------------------------------------------
	//si el id es mayor que el segundo máximo id, update BUFF_INPRRLIS_MAX_ID.
	else if (this->BUFF_INPRRLIS_MAX_ID[1] < _inprrlis_id)
	{
		//-----------------------------------------------------------------------------
		//actualización de BUFF_INPRRLIS_MAX_ID.
		this->BUFF_INPRRLIS_MAX_ID[1] = _inprrlis_id;
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si se ha definido el id en la posición [1], entonces setear [0].
	if (this->BUFF_INPRRLIS_ID_AV[1] != -1)
	{
		//-----------------------------------------------------------------------------
		//seteo del id candidato para la creación de una nueva estructura.
		this->BUFF_INPRRLIS_ID_AV[0] = this->BUFF_INPRRLIS_ID_AV[1];
		this->BUFF_INPRRLIS_ID_AV[1] = -1;
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del id de la estructura INPRRLIS disponible, si no se ha llenado el buffer.
	else if (this->BUFF_INPRRLIS_INI_AMOUNT < this->RLIS_AMOUNT_ALLOWED)
	{
		//-----------------------------------------------------------------------------
		//bucle para hallar el id de una estructura sin inicializar.
		for (in i1 = 0; i1 < this->RLIS_AMOUNT_ALLOWED; i1++)
		{
			//-------------------------------------------------------------------------
			//si la estructura no se ha inicializado, entonces.
			if (this->BUFF_INPRRLIS[i1].CS_SRG == -1)
			{
				//---------------------------------------------------------------------
				//seteo del id candidato para la creación de una nueva estructura.
				this->BUFF_INPRRLIS_ID_AV[0] = i1;

				//---------------------------------------------------------------------
				//salir del bucle.
				break;
			}
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del id de la estructura INPRRLIS disponible, si se ha llenado el buffer.
	else
	{
		//-----------------------------------------------------------------------------
		//declaración de la fortaleza de la relación de la estructura candidata.
		dou relation_strength   = NULL;

		//-----------------------------------------------------------------------------
		//declaración de los datos de las relaciones INDFRLIS relacionadas.
		in  upci_id_indfrlis1	= NULL;													//id de la upci de la estructura indfrlis 1.
		in  upci_id_indfrlis2	= NULL;													//id de la upci de la estructura indfrlis 2.
		in  indfrlis1_id		= NULL;													//id de la estructura indfrlis 1.
		in  indfrlis2_id		= NULL;													//id de la estructura indfrlis 2.
		dou rs_indfrlis1		= NULL;													//fortaleza de la relación indfrlis1.
		dou rs_indfrlis2		= NULL;													//fortaleza de la relación indfrlis2.
		dou rs_indfrlis_win		= NULL;													//fortaleza de la relación indfrlis ganadora.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para inicializar id y fortaleza de la relación de la estructura candidata.
		for (in i1 = 0; i1 < this->BUFF_INPRRLIS_MAX_ID[0] + 1; i1++)
		{
			//-------------------------------------------------------------------------
			//si la estructura está inicializada y es distinta de las creadas, entonces. 
			if (this->BUFF_INPRRLIS[i1].CS_SRG		!= -1	&& 
				this->BUFF_INPRRLIS_CRE[0].STR_ID	!= i1	&&
				this->BUFF_INPRRLIS_CRE[1].STR_ID	!= i1)
			{
				//---------------------------------------------------------------------
				//seteo.
				candidate_id		= i1;

				//---------------------------------------------------------------------
				//seteo de los datos de las relaciones INDFRLIS relacionadas.
				upci_id_indfrlis1	= this->BUFF_INPRRLIS[i1].UPCI_ID_STR1_RG;
				upci_id_indfrlis2	= this->BUFF_INPRRLIS[i1].UPCI_ID_STR2_RG;
				indfrlis1_id		= this->BUFF_INPRRLIS[i1].STR1_ID_RG;
				indfrlis2_id		= this->BUFF_INPRRLIS[i1].STR2_ID_RG;
				rs_indfrlis1		= this->BUFF_UPCI->at(upci_id_indfrlis1).BUFF_INDFRLIS[indfrlis1_id].RS_SRG;
				rs_indfrlis1		= this->BUFF_UPCI->at(upci_id_indfrlis2).BUFF_INDFRLIS[indfrlis2_id].RS_SRG;

				//---------------------------------------------------------------------
				//si la fortaleza de la relación 1 es mayor o igual, entonces setear.
				if(rs_indfrlis1 >= rs_indfrlis1)	rs_indfrlis_win = rs_indfrlis1;
				else								rs_indfrlis_win = rs_indfrlis2;

				//---------------------------------------------------------------------
				//seteo de la fortaleza de relación inicial.
				relation_strength = rs_indfrlis_win;

				//---------------------------------------------------------------------
				//salida del bucle.
				break;
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para hallar la estructura con la menor fortaleza de la relación.
		for (in i1 = 0; i1 < this->BUFF_INPRRLIS_MAX_ID[0] + 1; i1++)
		{
			//-------------------------------------------------------------------------
			//seteo de los datos de las relaciones INDFRLIS relacionadas.
			upci_id_indfrlis1	= this->BUFF_INPRRLIS[i1].UPCI_ID_STR1_RG;
			upci_id_indfrlis2	= this->BUFF_INPRRLIS[i1].UPCI_ID_STR2_RG;
			indfrlis1_id		= this->BUFF_INPRRLIS[i1].STR1_ID_RG;
			indfrlis2_id		= this->BUFF_INPRRLIS[i1].STR2_ID_RG;
			rs_indfrlis1		= this->BUFF_UPCI->at(upci_id_indfrlis1).BUFF_INDFRLIS[indfrlis1_id].RS_SRG;
			rs_indfrlis1		= this->BUFF_UPCI->at(upci_id_indfrlis2).BUFF_INDFRLIS[indfrlis2_id].RS_SRG;

			//-------------------------------------------------------------------------
			//si la fortaleza de la relación 1 es mayor o igual, entonces setear.
			if (rs_indfrlis1 >= rs_indfrlis1)	rs_indfrlis_win = rs_indfrlis1;
			else								rs_indfrlis_win = rs_indfrlis2;

			//-------------------------------------------------------------------------
			//emparejamiento para selección de la estructura con menor fortaleza de la relación.
			if (this->BUFF_INPRRLIS[i1].CS_SRG		!=		-1					&&
				rs_indfrlis_win						<		relation_strength	&&
				this->BUFF_INPRRLIS_CRE[0].STR_ID	!=		i1					&&
				this->BUFF_INPRRLIS_CRE[1].STR_ID	!=		i1					&&
				candidate_id						!=		i1)
			{
				//---------------------------------------------------------------------
				//seteo de un nuevo id candidato.
				candidate_id		= i1;
				relation_strength	= rs_indfrlis_win;
			}
		}

		//-----------------------------------------------------------------------------
		//limpieza de la estructura con id candidato.
		this->DeleteINPRRLIS(candidate_id);
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------  
//#1: método para actualizar buffer tras eliminar IS INIS.
vo	UPCI_SDS::UpdateBuffersToDeleteINIS(in _inis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con la IS con mayor evaluación, update.
	if (this->BUFF_INIS_MAX_EVAL->UPCI_ID		==	this->UPCI_ID &&
		this->BUFF_INIS_MAX_EVAL->STR_ID			==	_inis_id)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer para estructura con máxima evaluación.
		this->BUFF_INIS_MAX_EVAL->Clean();
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con la IS con mayor nivel de actividad, update.
	if (this->BUFF_INIS_MAX_AL->UPCI_ID			==	this->UPCI_ID	&&
		this->BUFF_INIS_MAX_AL->STR_ID			==	_inis_id)
	{
		//-----------------------------------------------------------------------------
		//reset de buffers para estructura con máximo nivel de actividad.
		this->BUFF_INIS_MAX_AL->Clean();
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el flujo de IS activa presente, entonces.
	if (this->BUFF_INIS_ACTIVATED[0].UPCI_ID	==	this->UPCI_ID	&&
		this->BUFF_INIS_ACTIVATED[0].STR_ID		==	_inis_id)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de flujo de estructura activada presente.
		this->BUFF_INIS_ACTIVATED[0].Clean();
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el flujo de IS activa anterior, entonces.
	else if (this->BUFF_INIS_ACTIVATED[1].UPCI_ID	==	this->UPCI_ID	&&
			 this->BUFF_INIS_ACTIVATED[1].STR_ID	==	_inis_id)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de flujo de estructura activada presente.
		this->BUFF_INIS_ACTIVATED[1].Clean();
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada correponde con la IS creada presente.
	if (this->BUFF_INIS_CRE[0].UPCI_ID	== this->UPCI_ID &&	this->BUFF_INIS_CRE[0].STR_ID	== _inis_id)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de estructura creada presente.
		this->BUFF_INIS_CRE[0].Clean();
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada correponde con la IS creada anterior.
	if (this->BUFF_INIS_CRE[1].UPCI_ID	== this->UPCI_ID &&	this->BUFF_INIS_CRE[1].STR_ID	== _inis_id)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de estructura creada anterior.
		this->BUFF_INIS_CRE[1].Clean();
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el id máximo, update.
	if (_inis_id == this->BUFF_INIS_MAX_ID[0])
	{
		//-----------------------------------------------------------------------------
		//si existe segun mayor, traspasar segundo mayor a primero.
		if (this->BUFF_INIS_MAX_ID[1] != -1)
		{
			//-------------------------------------------------------------------------
			//actualización del buffer de máximo id.
			this->BUFF_INIS_MAX_ID[0]	= this->BUFF_INIS_MAX_ID[1];
			this->BUFF_INIS_MAX_ID[1]	= -1;
		}		

		//-----------------------------------------------------------------------------
		//reset, sino existe segundo mayor id.
		else this->BUFF_INIS_MAX_ID[0]	= -1;
	}

	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el segundo id mayor, entonces actualizar.
	else if (_inis_id == this->BUFF_INIS_MAX_ID[1])	this->BUFF_INIS_MAX_ID[1] = -1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de ID disponible si hay cupo.
	if		(this->BUFF_INIS_ID_AV[0] == -1) this->BUFF_INIS_ID_AV[0] = _inis_id;
	else if (this->BUFF_INIS_ID_AV[1] == -1) this->BUFF_INIS_ID_AV[1] = _inis_id;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS está en suspensión.
	if (this->BUFF_INIS[_inis_id].AL_SRG > 0)
	{
		//-----------------------------------------------------------------------------
		//cantidad de estructuras suspendidas.
		in	str_sus_amount = in(this->BUFF_INIS_SUS->size());						

		//-----------------------------------------------------------------------------
		//búsqueda de la relación en los buffers de IS en suspensión.
		for (in i1 = 0; i1 < str_sus_amount; i1++)
		{
			//-------------------------------------------------------------------------
			//si la IS a eliminar corresponde con un elemnento de los buffers.
			if (this->BUFF_INIS_SUS->at(i1).UPCI_ID	==	this->UPCI_ID	&&
				this->BUFF_INIS_SUS->at(i1).STR_ID	==	_inis_id)
			{
				//---------------------------------------------------------------------
				//eliminación del elemento de los buffers de IS en suspensión.
				this->BUFF_INIS_SUS->erase(this->BUFF_INIS_SUS->begin() + i1);

				//---------------------------------------------------------------------
				//salida del bucle.
				break;
			}
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//decremento de la cantidad existente de estructuras.	
	--this->BUFF_INIS_INI_AMOUNT;
	--this->BUFF_TOTAL_STR_INI_AMOUNT;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para actualizar buffer tras eliminar IS PFRLIS.
vo	UPCI_SDS::UpdateBuffersToDeletePFRLIS(in _pfrlis_id)
{	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la relación eliminada corresponde con la relación con fortaleza máxima, update.
	if (this->BUFF_STR_MAX_RS->UPCI_ID	==	this->UPCI_ID	&&
		this->BUFF_STR_MAX_RS->STR_ID	==	_pfrlis_id		&&
		this->BUFF_STR_MAX_RS->STR_TYPE ==	PFRLIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer para estructura con fortaleza de la relación máximo.
		this->BUFF_STR_MAX_RS->Clean();
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada correponde con la IS creada presente.
	if (this->BUFF_PFRLIS_CRE[0].UPCI_ID == this->UPCI_ID &&	this->BUFF_PFRLIS_CRE[0].STR_ID == _pfrlis_id)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de estructura creada presente.
		this->BUFF_PFRLIS_CRE[0].Clean();
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada correponde con la IS creada anterior.
	if (this->BUFF_PFRLIS_CRE[1].UPCI_ID == this->UPCI_ID &&	this->BUFF_PFRLIS_CRE[1].STR_ID == _pfrlis_id)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de estructura creada anterior.
		this->BUFF_PFRLIS_CRE[1].Clean();
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el id máximo, update.
	if (_pfrlis_id == this->BUFF_PFRLIS_MAX_ID[0])
	{
		//-----------------------------------------------------------------------------
		//si existe segun mayor, traspasar segundo mayor a primero.
		if (this->BUFF_PFRLIS_MAX_ID[1] != -1)
		{
			//-------------------------------------------------------------------------
			//actualización del buffer de máximo id.
			this->BUFF_PFRLIS_MAX_ID[0] = this->BUFF_PFRLIS_MAX_ID[1];
			this->BUFF_PFRLIS_MAX_ID[1] = -1;
		}		

		//-----------------------------------------------------------------------------
		//reset, si no existe segundo mayor id.
		else this->BUFF_PFRLIS_MAX_ID[0] = -1;
	}

	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el segundo id mayor, entonces actualizar.
	else if (_pfrlis_id == this->BUFF_PFRLIS_MAX_ID[1])	this->BUFF_PFRLIS_MAX_ID[1] = -1;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de ID disponible si hay cupo.
	if		(this->BUFF_PFRLIS_ID_AV[0] == -1) this->BUFF_PFRLIS_ID_AV[0] = _pfrlis_id;
	else if (this->BUFF_PFRLIS_ID_AV[1] == -1) this->BUFF_PFRLIS_ID_AV[1] = _pfrlis_id;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS está en suspensión.
	if (this->BUFF_PFRLIS[_pfrlis_id].AL_SRG > 0)
	{
		//-----------------------------------------------------------------------------
		//cantidad de estructuras suspendidas.
		in	str_sus_amount = in(this->BUFF_PFRLIS_SUS->size());						

		//-----------------------------------------------------------------------------
		//búsqueda de la relación en los buffers de IS en suspensión.
		for (in i1 = 0; i1 < str_sus_amount; i1++)
		{
			//-------------------------------------------------------------------------
			//si la IS a eliminar corresponde con un elemnento de los buffers.
			if (this->BUFF_PFRLIS_SUS->at(i1).UPCI_ID	==	this->UPCI_ID	&&
				this->BUFF_PFRLIS_SUS->at(i1).STR_ID	==	_pfrlis_id)
			{
				//---------------------------------------------------------------------
				//eliminación del elemento de los buffers de IS en suspensión.
				this->BUFF_PFRLIS_SUS->erase(this->BUFF_PFRLIS_SUS->begin() + i1);

				//---------------------------------------------------------------------
				//salida del bucle.
				break;
			}
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//decremento de la cantidad existente de estructuras.	
	--this->BUFF_PFRLIS_INI_AMOUNT;
	--this->BUFF_TOTAL_STR_INI_AMOUNT;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para actualizar buffer tras eliminar IS INDFRLIS.
vo	UPCI_SDS::UpdateBuffersToDeleteINDFRLIS(in _indfrlis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la relación eliminada corresponde con la relación con fortaleza máxima, update.
	if (this->BUFF_STR_MAX_RS->UPCI_ID	==	this->UPCI_ID	&&
		this->BUFF_STR_MAX_RS->STR_ID	==	_indfrlis_id	&&
		this->BUFF_STR_MAX_RS->STR_TYPE ==	INDFRLIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer para estructura con fortaleza de la relación máximo.
		this->BUFF_STR_MAX_RS->Clean();
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada correponde con la IS creada presente.
	if (this->BUFF_INDFRLIS_CRE[0].UPCI_ID == this->UPCI_ID && this->BUFF_INDFRLIS_CRE[0].STR_ID == _indfrlis_id)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de estructura creada presente.
		this->BUFF_INDFRLIS_CRE[0].Clean();
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada correponde con la IS creada anterior.
	if (this->BUFF_INDFRLIS_CRE[1].UPCI_ID == this->UPCI_ID && this->BUFF_INDFRLIS_CRE[1].STR_ID == _indfrlis_id)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de estructura creada anterior.
		this->BUFF_INDFRLIS_CRE[1].Clean();
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el id máximo, update.
	if (_indfrlis_id == this->BUFF_INDFRLIS_MAX_ID[0])
	{
		//-----------------------------------------------------------------------------
		//si existe segun mayor, traspasar segundo mayor a primero.
		if (this->BUFF_INDFRLIS_MAX_ID[1] != -1)
		{
			//-------------------------------------------------------------------------
			//actualización del buffer de máximo id.
			this->BUFF_INDFRLIS_MAX_ID[0] = this->BUFF_INDFRLIS_MAX_ID[1];
			this->BUFF_INDFRLIS_MAX_ID[1] = -1;
		}		

		//-----------------------------------------------------------------------------
		//reset, sino existe segundo mayor id.
		else this->BUFF_INDFRLIS_MAX_ID[0] = -1;
	}

	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el segundo id mayor, entonces actualizar.
	else if (_indfrlis_id == this->BUFF_INDFRLIS_MAX_ID[1])	this->BUFF_INDFRLIS_MAX_ID[1] = -1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de ID disponible si hay cupo.
	if		(this->BUFF_INDFRLIS_ID_AV[0] == -1) this->BUFF_INDFRLIS_ID_AV[0] = _indfrlis_id;
	else if (this->BUFF_INDFRLIS_ID_AV[1] == -1) this->BUFF_INDFRLIS_ID_AV[1] = _indfrlis_id;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS está en suspensión.
	if (this->BUFF_INDFRLIS[_indfrlis_id].AL_SRG > 0)
	{
		//-----------------------------------------------------------------------------
		//cantidad de estructuras suspendidas.
		in	str_sus_amount = in(this->BUFF_INDFRLIS_SUS->size());						

		//-----------------------------------------------------------------------------
		//búsqueda de la relación en los buffers de IS en suspensión.
		for (in i1 = 0; i1 < str_sus_amount; i1++)
		{
			//-------------------------------------------------------------------------
			//si la IS a eliminar corresponde con un elemnento de los buffers.
			if (this->BUFF_INDFRLIS_SUS->at(i1).UPCI_ID	==	this->UPCI_ID	&&
				this->BUFF_INDFRLIS_SUS->at(i1).STR_ID	==	_indfrlis_id)
			{
				//---------------------------------------------------------------------
				//eliminación del elemento de los buffers de IS en suspensión.
				this->BUFF_INDFRLIS_SUS->erase(this->BUFF_INDFRLIS_SUS->begin() + i1);

				//---------------------------------------------------------------------
				//salida del bucle.
				break;
			}
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//decremento de la cantidad existente de estructuras.	
	--this->BUFF_INDFRLIS_INI_AMOUNT;
	--this->BUFF_TOTAL_STR_INI_AMOUNT;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para actualizar buffer tras eliminar IS INPRRLIS.
vo	UPCI_SDS::UpdateBuffersToDeleteINPRRLIS(in _inprrlis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la relación eliminada corresponde con la relación con fortaleza máxima, update.
	if (this->BUFF_STR_MAX_RS->UPCI_ID	==	this->UPCI_ID	&&
		this->BUFF_STR_MAX_RS->STR_ID	==	_inprrlis_id	&&
		this->BUFF_STR_MAX_RS->STR_TYPE ==	INPRRLIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer para estructura con fortaleza de la relación máximo.
		this->BUFF_STR_MAX_RS->Clean();
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada correponde con la IS creada presente.
	if (this->BUFF_INPRRLIS_CRE[0].UPCI_ID == this->UPCI_ID && this->BUFF_INPRRLIS_CRE[0].STR_ID == _inprrlis_id)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de estructura creada presente.
		this->BUFF_INPRRLIS_CRE[0].Clean();
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada correponde con la IS creada anterior.
	if (this->BUFF_INPRRLIS_CRE[1].UPCI_ID == this->UPCI_ID && this->BUFF_INPRRLIS_CRE[1].STR_ID == _inprrlis_id)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de estructura creada anterior.
		this->BUFF_INPRRLIS_CRE[1].Clean();
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el id máximo, update.
	if (_inprrlis_id == this->BUFF_INPRRLIS_MAX_ID[0])
	{
		//-----------------------------------------------------------------------------
		//si existe segun mayor, traspasar segundo mayor a primero.
		if (this->BUFF_INPRRLIS_MAX_ID[1] != -1)
		{
			//-------------------------------------------------------------------------
			//actualización del buffer de máximo id.
			this->BUFF_INPRRLIS_MAX_ID[0] = this->BUFF_INPRRLIS_MAX_ID[1];
			this->BUFF_INPRRLIS_MAX_ID[1] = -1;
		}		

		//-----------------------------------------------------------------------------
		//reset, sino existe segundo mayor id.
		else this->BUFF_INPRRLIS_MAX_ID[0] = -1;
	}

	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el segundo id mayor, entonces actualizar.
	else if (_inprrlis_id == this->BUFF_INPRRLIS_MAX_ID[1])	this->BUFF_INPRRLIS_MAX_ID[1] = -1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de ID disponible si hay cupo.
	if		(this->BUFF_INPRRLIS_ID_AV[0] == -1) this->BUFF_INPRRLIS_ID_AV[0] = _inprrlis_id;
	else if (this->BUFF_INPRRLIS_ID_AV[1] == -1) this->BUFF_INPRRLIS_ID_AV[1] = _inprrlis_id;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//decremento de la cantidad existente de estructuras.	
	--this->BUFF_INPRRLIS_INI_AMOUNT;
	--this->BUFF_TOTAL_STR_INI_AMOUNT;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para update de estado de actividad no congruente a estado congruente
//en estructuras presentes del buffer BUFF_INIS mediante BUFF_INIS_ID_CAN.
vo	UPCI_SDS::UpdateToCongruentBUFF_INIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	in	upci_candidates_present_amount	= in(this->BUFF_UPCI_ID_INIS_CAN->front().size());		//cantidad de upci candidatas presentes.	
	in	INIS_candidates_present_amount	= NULL;													//cantidad de candidatos por upci presentes.
	in	upci_id_candidate				= NULL;													//id de la upci candidata.
	in	str_id_candidate				= NULL;													//id de la estructura candidata.

	//---------------------------------------------------------------------------------
	//paralelización del bucle for.
	#pragma omp parallel for

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para obtener cantidad de estructuras candidatas presentes en cada upci candidata.
	for (in i1 = 0; i1 < upci_candidates_present_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del id de la upci candidata.
		upci_id_candidate					= this->BUFF_UPCI_ID_INIS_CAN->front().at(i1);		

		//-----------------------------------------------------------------------------
		//cantidad de estructuras candidatas presentes en la upci i1.
		INIS_candidates_present_amount	= in(this->BUFF_INIS_ID_CAN->front().at(upci_id_candidate).size());

		//-----------------------------------------------------------------------------
		//bucle para actualizar estado de congruencia de las estructuras candidatas presentes.
		for (in i2 = 0; i2 < INIS_candidates_present_amount; i2++)
		{
			//-------------------------------------------------------------------------
			//obtención del id de la estructura candidata.
			str_id_candidate = this->BUFF_INIS_ID_CAN->front().at(upci_id_candidate).at(i2);

			//-------------------------------------------------------------------------
			//actualización de congruencia de la estructura candidata presente i2.
			this->BUFF_UPCI->at(upci_id_candidate).BUFF_INIS[str_id_candidate].CS_SRG = ON;

			//-------------------------------------------------------------------------
			//impresión de la estructura en estado de congruencia.
			this->Print("    > entra en estado de congruencia inis id ", str_id_candidate);
		}		
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para update de estado de actividad no congruente a estado congruente
//en estructuras presentes del buffer BUFF_INDFRLIS mediante BUFF_INDFRLIS_ID_CAN.
vo	UPCI_SDS::UpdateToCongruentBUFF_INDFRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	in	upci_candidates_present_amount		= in(this->BUFF_UPCI_ID_INDFRLIS_CAN->front().size());		//cantidad de upci candidatas presentes.	
	in	INDFRLIS_candidates_present_amount	= 0;														//cantidad de candidatos por upci presentes.
	in	upci_id_candidate					= NULL;														//id de la upci candidata.
	in	str_id_candidate					= NULL;														//id de la estructura candidata.

	//---------------------------------------------------------------------------------
	//paralelización del bucle for.
	#pragma omp parallel for

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para obtener cantidad de estructuras candidatas presentes en cada upci candidata.
	for (in i1 = 0; i1 < upci_candidates_present_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del id de la upci candidata.
		upci_id_candidate					= this->BUFF_UPCI_ID_INDFRLIS_CAN->front().at(i1);

		//-----------------------------------------------------------------------------
		//cantidad de estructuras candidatas presentes en la upci i1.
		INDFRLIS_candidates_present_amount	= in(this->BUFF_INDFRLIS_ID_CAN->front().at(upci_id_candidate).size());

		//-----------------------------------------------------------------------------
		//bucle para actualizar estado de congruencia de las estructuras candidatas presentes.
		for (in i2 = 0; i2 < INDFRLIS_candidates_present_amount; i2++)
		{
			//-------------------------------------------------------------------------
			//obtención del id de la estructura candidata.
			str_id_candidate = this->BUFF_INDFRLIS_ID_CAN->front().at(upci_id_candidate).at(i2);

			//-------------------------------------------------------------------------
			//actualización de congruencia de la estructura candidata presente i2.
			this->BUFF_UPCI->at(upci_id_candidate).BUFF_INDFRLIS[str_id_candidate].CS_SRG = ON;

			//-------------------------------------------------------------------------
			//impresión de la estructura en estado de congruencia.
			this->Print("    > entra en estado de congruencia indfrlis id ", str_id_candidate);
		}		
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para update de estado de actividad no congruente a estado congruente
//en estructuras presentes del buffer BUFF_INPRRLIS mediante BUFF_INPRRLIS_ID_CAN.
vo	UPCI_SDS::UpdateToCongruentBUFF_INPRRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	in	upci_candidates_present_amount		= in(this->BUFF_UPCI_ID_INPRRLIS_CAN->front().size());		//cantidad de upci candidatas presentes.	
	in	INPRRLIS_candidates_present_amount	= 0;														//cantidad de candidatos por upci presentes.
	in	upci_id_candidate					= NULL;														//id de la upci candidata.
	in	str_id_candidate					= NULL;														//id de la estructura candidata.

	//---------------------------------------------------------------------------------
	//paralelización del bucle for.
	#pragma omp parallel for

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para obtener cantidad de estructuras candidatas presentes en cada upci candidata.
	for (in i1 = 0; i1 < upci_candidates_present_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del id de la upci candidata.
		upci_id_candidate					= this->BUFF_UPCI_ID_INPRRLIS_CAN->front().at(i1);

		//-----------------------------------------------------------------------------
		//cantidad de estructuras candidatas presentes en la upci i1.
		INPRRLIS_candidates_present_amount	= in(this->BUFF_INPRRLIS_ID_CAN->front().at(upci_id_candidate).size());

		//-----------------------------------------------------------------------------
		//bucle para actualizar estado de congruencia de las estructuras candidatas presentes.
		for (in i2 = 0; i2 < INPRRLIS_candidates_present_amount; i2++)
		{
			//-------------------------------------------------------------------------
			//obtención del id de la estructura candidata.
			str_id_candidate = this->BUFF_INPRRLIS_ID_CAN->front().at(upci_id_candidate).at(i2);

			//-------------------------------------------------------------------------
			//actualización de congruencia de la estructura candidata presente i2.
			this->BUFF_UPCI->at(upci_id_candidate).BUFF_INPRRLIS[str_id_candidate].CS_SRG = ON;

			//-------------------------------------------------------------------------
			//impresión de la estructura en estado de congruencia.
			this->Print("    > entra en estado de congruencia inprrlis id ", str_id_candidate);
		}		
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para update el estado de actividad congruente a estado no congruente 
//en estructuras anteriores del buffer BUFF_INIS mediante BUFF_INIS_ID_CAN.
vo	UPCI_SDS::UpdateToNotCongruentBUFF_INIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existen estructuras candidatas anteriores, update estructuras.
	if (this->BUFF_INIS_ID_CAN->size() > 1)
	{
		//-----------------------------------------------------------------------------
		//variables auxiliares.
		in	previous_upci_candidates_amount		= in(this->BUFF_UPCI_ID_INIS_CAN->back().size());			//cantidad de upci candidatas anteriores.
		in	previous_inis_candidates_amount		= 0;														//cantidad de candidatos por upci anteriores.
		in	upci_id_candidate					= NULL;														//id de la upci candidata.
		in	str_id_candidate					= NULL;														//id de la estructura candidata.
		
		//-----------------------------------------------------------------------------
		//paralelización del bucle for.
		#pragma omp parallel for

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para obtener cantidad de estructuras candidatas anteriores en cada upci candidata.
		for (in i1 = 0; i1 < previous_upci_candidates_amount; i1++)
		{
			//-------------------------------------------------------------------------
			//obtención del id de la upci candidata.
			upci_id_candidate					= this->BUFF_UPCI_ID_INIS_CAN->back().at(i1);
			
			//-------------------------------------------------------------------------
			//cantidad de estructuras candidatas en la upci i1.
			previous_inis_candidates_amount	= in(this->BUFF_INIS_ID_CAN->back().at(upci_id_candidate).size());
			
			//-------------------------------------------------------------------------
			//bucle para actualizar estado de congruencia de las estructuras candidatas anteriores.
			for (in i2 = 0; i2 < previous_inis_candidates_amount; i2++)
			{
				//---------------------------------------------------------------------
				//obtención del id de la estructura candidata.
				str_id_candidate = this->BUFF_INIS_ID_CAN->back().at(upci_id_candidate).at(i2);

				//---------------------------------------------------------------------
				//actualización de congruencia de estructura  de la estructura candidata anterior i2.
				this->BUFF_UPCI->at(upci_id_candidate).BUFF_INIS[str_id_candidate].CS_SRG = OFF;
			}		
		}

		//-----------------------------------------------------------------------------
		//Clean buffer BUFF_INIS_ID_CAN.
		this->CleanBuffersOfPreviousCandidatesINIS();
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para update el estado de actividad congruente a estado no congruente 
//en estructuras anteriores del buffer BUFF_INDFRLIS mediante BUFF_INDFRLIS_ID_CAN.
vo	UPCI_SDS::UpdateToNotCongruentBUFF_INDFRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existen estructuras candidatas anteriores, update estructuras.
	if (this->BUFF_INDFRLIS_ID_CAN->size() > 1)
	{
		//-----------------------------------------------------------------------------
		//variables auxiliares.
		in	previous_upci_candidates_amount		= in(this->BUFF_UPCI_ID_INDFRLIS_CAN->back().size());		//cantidad de upci candidatas anteriores.
		in	previous_indfrlis_candidates_amount	= 0;														//cantidad de candidatos por upci anteriores.
		in	upci_id_candidate					= NULL;														//id de la upci candidata.
		in	str_id_candidate					= NULL;														//id de la estructura candidata.

		//-----------------------------------------------------------------------------
		//paralelización del bucle for.
		#pragma omp parallel for

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para obtener cantidad de estructuras candidatas anteriores en cada upci candidata.
		for (in i1 = 0; i1 < previous_upci_candidates_amount; i1++)
		{
			//-------------------------------------------------------------------------
			//obtención del id de la upci candidata.
			upci_id_candidate					= this->BUFF_UPCI_ID_INDFRLIS_CAN->back().at(i1);

			//-------------------------------------------------------------------------
			//cantidad de estructuras candidatas en la upci i1.
			previous_indfrlis_candidates_amount = in(this->BUFF_INDFRLIS_ID_CAN->back().at(upci_id_candidate).size());

			//-------------------------------------------------------------------------
			//bucle para actualizar estado de congruencia de las estructuras candidatas anteriores.
			for (in i2 = 0; i2 < previous_indfrlis_candidates_amount; i2++)
			{
				//---------------------------------------------------------------------
				//obtención del id de la estructura candidata.
				str_id_candidate = this->BUFF_INDFRLIS_ID_CAN->back().at(upci_id_candidate).at(i2);

				//---------------------------------------------------------------------
				//actualización de congruencia de estructura  de la estructura candidata anterior i2.
				this->BUFF_UPCI->at(upci_id_candidate).BUFF_INDFRLIS[str_id_candidate].CS_SRG = OFF;
			}		
		}

		//-----------------------------------------------------------------------------
		//Clean buffer BUFF_INDFRLIS_ID_CAN.
		this->CleanBuffersOfPreviousCandidatesINDFRLIS();
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para update el estado de actividad congruente a estado no congruente 
//en estructuras anteriores del buffer BUFF_INPRRLIS mediante BUFF_INPRRLIS_ID_CAN.
vo	UPCI_SDS::UpdateToNotCongruentBUFF_INPRRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existen estructuras candidatas anteriores, update estructuras.
	if (this->BUFF_INPRRLIS_ID_CAN->size() > 1)
	{
		//-----------------------------------------------------------------------------
		//variables auxiliares.
		in	previous_upci_candidates_amount		= in(this->BUFF_UPCI_ID_INPRRLIS_CAN->back().size());		//cantidad de upci candidatas anteriores.
		in	previous_inprrlis_candidates_amount	= 0;														//cantidad de candidatos por upci anteriores.
		in	upci_id_candidate					= NULL;														//id de la upci candidata.
		in	str_id_candidate					= NULL;														//id de la estructura candidata.

		//-----------------------------------------------------------------------------
		//paralelización del bucle for.
		#pragma omp parallel for

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para obtener cantidad de estructuras candidatas anteriores en cada upci candidata.
		for (in i1 = 0; i1 < previous_upci_candidates_amount; i1++)
		{
			//-------------------------------------------------------------------------
			//obtención del id de la upci candidata.
			upci_id_candidate					= this->BUFF_UPCI_ID_INPRRLIS_CAN->back().at(i1);

			//-------------------------------------------------------------------------
			//cantidad de estructuras candidatas en la upci i1.
			previous_inprrlis_candidates_amount = in(this->BUFF_INPRRLIS_ID_CAN->back().at(upci_id_candidate).size());

			//-------------------------------------------------------------------------
			//bucle para actualizar estado de congruencia de las estructuras candidatas anteriores.
			for (in i2 = 0; i2 < previous_inprrlis_candidates_amount; i2++)
			{
				//---------------------------------------------------------------------
				//obtención del id de la estructura candidata.
				str_id_candidate = this->BUFF_INPRRLIS_ID_CAN->back().at(upci_id_candidate).at(i2);

				//---------------------------------------------------------------------
				//actualización de congruencia de estructura  de la estructura candidata anterior i2.
				this->BUFF_UPCI->at(upci_id_candidate).BUFF_INPRRLIS[str_id_candidate].CS_SRG = OFF;
			}		
		}

		//-----------------------------------------------------------------------------
		//Clean buffer BUFF_INPRRLIS_ID_CAN.
		this->CleanBuffersOfPreviousCandidatesINPRRLIS();
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para calcular el nivel de actividad.
dou	UPCI_SDS::ActivityLevelFunction(dou _seed)
{
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	dou activitylevel	= 0;																//nivel de actividad.
	dou amplitude		= 15;																//amplitud.
	
	//---------------------------------------------------------------------------------
	//cálculo del nivel de actividad.
	if (_seed < 0)	activitylevel = this->MAX_ACTIVITY_LEVEL_ALLOWED - ceil((this->MAX_ACTIVITY_LEVEL_ALLOWED - this->MIN_ACTIVITY_LEVEL_ALLOWED) / (1 + exp(-_seed*amplitude - 6)));
	else			activitylevel = this->MAX_ACTIVITY_LEVEL_ALLOWED - ceil((this->MAX_ACTIVITY_LEVEL_ALLOWED - this->MIN_ACTIVITY_LEVEL_ALLOWED) / (1 + exp(_seed*amplitude - 6)));

	//---------------------------------------------------------------------------------
	//retorno del nivel de actividad.
	return activitylevel;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para calcular el nivel de actividad.
dou	UPCI_SDS::ActivityLevelFunction(in _seed)
{
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	dou activitylevel	= 0.2;																//nivel de actividad.
	dou amplitude		= 0.2;																//amplitud.

	//---------------------------------------------------------------------------------
	//cálculo del nivel de actividad.
	if (_seed < 0)	activitylevel = this->MAX_ACTIVITY_LEVEL_ALLOWED - ceil((this->MAX_ACTIVITY_LEVEL_ALLOWED - this->MIN_ACTIVITY_LEVEL_ALLOWED) / (1 + exp(-_seed*amplitude - 6)));
	else			activitylevel = this->MAX_ACTIVITY_LEVEL_ALLOWED - ceil((this->MAX_ACTIVITY_LEVEL_ALLOWED - this->MIN_ACTIVITY_LEVEL_ALLOWED) / (1 + exp(_seed*amplitude - 6)));

	//---------------------------------------------------------------------------------
	//retorno del nivel de actividad.
	return activitylevel;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para obtener el estado de la bandera 'STORAGE_FLAG'. 
in	UPCI_SDS::GetSTORAGE_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'STORAGE_FLAG'.
	return this->STORAGE_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para obtener el estado de la bandera 'KERNEL_INTEGRATION_FLAG'. 
in	UPCI_SDS::GetKERNEL_INTEGRATION_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'KERNEL_INTEGRATION_FLAG'.
	return this->KERNEL_INTEGRATION_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para obtener el estado de la bandera 'THREAD_INTEGRATION_FLAG'.
in	UPCI_SDS::GetTHREAD_INTEGRATION_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'THREAD_INTEGRATION_FLAG'.
	return this->THREAD_INTEGRATION_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para obtener el estado de la bandera 'THREAD_INTEGRATION_LATENCY_FLAG'. 
in	UPCI_SDS::GetTHREAD_INTEGRATION_LATENCY_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'THREAD_INTEGRATION_LATENCY_FLAG'.
	return this->THREAD_INTEGRATION_LATENCY_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método para obtener el estado de la bandera 'THREAD_INTEGRATION_FINISHED_FLAG'. 
in	UPCI_SDS::GetTHREAD_INTEGRATION_FINISHED_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'THREAD_INTEGRATION_FINISHED_FLAG'.
	return this->THREAD_INTEGRATION_FINISHED_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#6: método para obtener el estado de la bandera 'NEW_INPUT_FLAG'.
in	UPCI_SDS::GetNEW_INPUT_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'NEW_INPUT_FLAG'.
	return this->NEW_INPUT_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#7: método para obtener el estado de la bandera 'NEW_INPUT_DIFFERENCE_RELATION_FLAG'.
in	UPCI_SDS::GetNEW_INPUT_DIFFERENCE_RELATION_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'NEW_INPUT_DIFFERENCE_RELATION_FLAG'.
	return this->NEW_INPUT_DIFFERENCE_RELATION_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#8: método para obtener el estado de la bandera 'INIS_CONGRUENCE_ACCOMPLISHED'.
in	UPCI_SDS::GetINIS_CONGRUENCE_ACCOMPLISHED()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'INIS_CONGRUENCE_ACCOMPLISHED'.
	return this->INIS_CONGRUENCE_ACCOMPLISHED;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#9: método para obtener el estado de la bandera 'INDFRLIS_CONGRUENCE_ACCOMPLISHED'.
in	UPCI_SDS::GetINDFRLIS_CONGRUENCE_ACCOMPLISHED()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'INDFRLIS_CONGRUENCE_ACCOMPLISHED'.
	return this->INDFRLIS_CONGRUENCE_ACCOMPLISHED;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#10: método para obtener el estado de la bandera 'INPRRLIS_CONGRUENCE_ACCOMPLISHED'.
in	UPCI_SDS::GetINPRRLIS_CONGRUENCE_ACCOMPLISHED()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'INPRRLIS_CONGRUENCE_ACCOMPLISHED'.
	return this->INPRRLIS_CONGRUENCE_ACCOMPLISHED;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#11: método para obtener el estado de la bandera 'CLOSE_ACTIVE_THREADS_FLAG'.
in	UPCI_SDS::GetCLOSE_ACTIVE_THREADS_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'CLOSE_ACTIVE_THREADS_FLAG'.
	return *this->CLOSE_ACTIVE_THREADS_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#12: método para obtener el estado de la bandera 'PAUSE_ACTIVE_THREADS_FLAG'.
in	UPCI_SDS::GetPAUSE_ACTIVE_THREADS_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'PAUSE_ACTIVE_THREADS_FLAG'.
	return *this->PAUSE_ACTIVE_THREADS_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#13: método para obtener el estado de la bandera 'PRINT_FLAG'.
in	UPCI_SDS::GetPRINT_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'PRINT_FLAG'.
	return this->PRINT_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método Get para obtener cantidad de upci en el grupo.
in	UPCI_SDS::GetAmountUpcGro()
{
	//---------------------------------------------------------------------------------
	//retorno de la cantidad de upci existentes en el grupo.
	return in(this->BUFF_UPCI->size());
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para obtener el tipo de evaluación de transiciones de entradas.
in	UPCI_SDS::GetInputTransitionEvaluationTypeIn(dou _input_evaluation, dou _input_evaluation_difference)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la transición de evaluación es positiva, entonces.
	if (_input_evaluation_difference > this->TRANSITION_EVALUATION_THRESHOLD)
	{
		//-----------------------------------------------------------------------------
		//devolver transición positiva.
		return POSITIVE_TRANSITION;
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la transición de evaluación es negativa.
	else if (_input_evaluation_difference	<	-this->TRANSITION_EVALUATION_THRESHOLD	||
			(_input_evaluation_difference	>=	-this->TRANSITION_EVALUATION_THRESHOLD	&&
			 _input_evaluation_difference	<=	this->TRANSITION_EVALUATION_THRESHOLD	&&
			 _input_evaluation				<	0))
	{
		//-----------------------------------------------------------------------------
		//devolver transición negativa.
		return NEGATIVE_TRANSITION;
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la transición es neutral y la evaluación es positiva, entonces.
	if (_input_evaluation_difference  >=  -this->TRANSITION_EVALUATION_THRESHOLD	&&
		_input_evaluation_difference  <=  this->TRANSITION_EVALUATION_THRESHOLD		&&
		_input_evaluation			  >	  0)
	{
		//-----------------------------------------------------------------------------
		//devolver transición neutral positiva.
		return NEUTRAL_POSITIVE_TRANSITION;
	}	

	//---------------------------------------------------------------------------------
	//retorno fallido.
	return -1;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para obtener el tipo de evaluación de transiciones de entradas.
st	UPCI_SDS::GetInputTransitionEvaluationTypeSt(dou _input_evaluation, dou _input_evaluation_difference)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la transición de evaluación es positiva, entonces.
	if (_input_evaluation_difference > this->TRANSITION_EVALUATION_THRESHOLD)
	{
		//-----------------------------------------------------------------------------
		//devolver transición positiva.
		return "POSITIVE_TRANSITION";
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la transición de evaluación es negativa.
	else if (_input_evaluation_difference	<	-this->TRANSITION_EVALUATION_THRESHOLD	||
			(_input_evaluation_difference	>=	-this->TRANSITION_EVALUATION_THRESHOLD	&&
			 _input_evaluation_difference	<=	this->TRANSITION_EVALUATION_THRESHOLD	&&
			 _input_evaluation				<	0))
	{
		//-----------------------------------------------------------------------------
		//devolver transición negativa.
		return "NEGATIVE_TRANSITION";
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la transición es neutral y la evaluación es positiva, entonces.
	if (_input_evaluation_difference  >=  -this->TRANSITION_EVALUATION_THRESHOLD	&&
		_input_evaluation_difference  <=  this->TRANSITION_EVALUATION_THRESHOLD		&&
		_input_evaluation			  >	  0)
	{
		//-----------------------------------------------------------------------------
		//devolver transición neutral positiva.
		return "NEUTRAL_POSITIVE_TRANSITION";
	}	

	//---------------------------------------------------------------------------------
	//retorno fallido.
	return "";
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método Get para obtener el estado de actividad de actividad de la estructura INIS 
//activada presente.
in	UPCI_SDS::GetCurrentActivityStatus_INIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura activada presente está definida.
	if (this->BUFF_INIS_ACTIVATED[0].STR_ID != -1)
	{
		//-----------------------------------------------------------------------------
		//si la estructura posee nivel de actividad.
		if (this->BUFF_UPCI->at(this->BUFF_INIS_ACTIVATED[0].UPCI_ID).BUFF_INIS[this->BUFF_INIS_ACTIVATED[0].STR_ID].AL_SRG > 0)	return ON;
		else																														return OFF;
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura activada presente no está definida.
	else
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//no existe actividad
		return OFF;
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método Get para obtener el estado de actividad de actividad de la estructura INIS 
//activada pasada.
in	UPCI_SDS::GetPastActivityStatus_INIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura activada pasada está definida.
	if (this->BUFF_INIS_ACTIVATED[1].STR_ID != -1)
	{
		//-----------------------------------------------------------------------------
		//si la estructura posee nivel de actividad.
		if (this->BUFF_UPCI->at(this->BUFF_INIS_ACTIVATED[1].UPCI_ID).BUFF_INIS[this->BUFF_INIS_ACTIVATED[1].STR_ID].AL_SRG > 0)	return ON;
		else																														return OFF;
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura activada pasada no está definida.
	else
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//no existe actividad
		return OFF;
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para obtener el máximo nivel de actividad.
dou	UPCI_SDS::GetMaxActivityLevel()
{
	//---------------------------------------------------------------------------------
	//retorno del máximo nivel de actividad.
	return (this->BUFF_UPCI->at(this->BUFF_INIS_MAX_AL->UPCI_ID).BUFF_INIS[this->BUFF_INIS_MAX_AL->STR_ID].AL_SRG);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------  #### VER POR QUÉ NO SE AGREGÓ PFRLIS EN ESTRUCTURAS SUSPENDIDAS.
//#1: método para checkear si existen estructuras en estado de suspensión.
in	UPCI_SDS::CheckSUSPENDED_STRUCTURES()
{
	//---------------------------------------------------------------------------------
	//retorno de la existencia de estructuras suspendidas.
	if (this->BUFF_INIS_SUS->size() > 0 || this->BUFF_INDFRLIS_SUS->size() > 0)	return ON;
	else																		return OFF;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para checkear si existen estructuras INIS en estado de suspensión.
in	UPCI_SDS::CheckSUSPENDED_INIS()
{
	//---------------------------------------------------------------------------------
	//retorno de la existencia de estructuras INIS suspendidas.
	if (this->BUFF_INIS_SUS->size() > 0)	return ON;
	else									return OFF;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para checkear si existen estructuras INDFRLIS en estado de suspensión.
in	UPCI_SDS::CheckSUSPENDED_INDFRLIS()
{
	//---------------------------------------------------------------------------------
	//retorno de la existencia de estructuras INDFRLIS suspendidas.
	if (this->BUFF_INDFRLIS_SUS->size() > 0)	return ON;
	else										return OFF;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para obtener el contador de iteraciones del kernel.
in	UPCI_SDS::GetKERNEL_ITERATION_COUNTER()
{
	//---------------------------------------------------------------------------------
	//retorno del contador de iteraciones del kernel.
	return this->KERNEL_ITERATION_COUNTER;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para obtener el contador de iteraciones del Hilo.
in	UPCI_SDS::GetTHREAD_ITERATION_COUNTER()
{
	//---------------------------------------------------------------------------------
	//retorno del contador de iteraciones del Hilo.
	return this->THREAD_ITERATION_COUNTER;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para obtener el contador de diferenciaciones globales de estructuras.
in	UPCI_SDS::GetGLOBAL_DIFFERENTIATION_COUNTER()
{
	//---------------------------------------------------------------------------------
	//retorno del contador de diferenciaciones gloables.
	return this->GLOBAL_DIFFERENTIATION_COUNTER;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para setear el estado de la bandera 'STORAGE_FLAG'. 
vo	UPCI_SDS::SetSTORAGE_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'STORAGE_FLAG'.
	this->STORAGE_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para setear el estado de la bandera 'KERNEL_INTEGRATION_FLAG';
vo	UPCI_SDS::SetKERNEL_INTEGRATION_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'KERNEL_INTEGRATION_FLAG'.
	this->KERNEL_INTEGRATION_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para setear el estado de la bandera 'THREAD_INTEGRATION_FLAG'. 
vo	UPCI_SDS::SetTHREAD_INTEGRATION_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'THREAD_INTEGRATION_FLAG'.
	this->THREAD_INTEGRATION_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para setear el estado de la bandera 'THREAD_INTEGRATION_LATENCY_FLAG'. 
vo	UPCI_SDS::SetTHREAD_INTEGRATION_LATENCY_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'THREAD_INTEGRATION_LATENCY_FLAG'.
	this->THREAD_INTEGRATION_LATENCY_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método para setear el estado de la bandera 'THREAD_INTEGRATION_FINISHED_FLAG'. 
vo	UPCI_SDS::SetTHREAD_INTEGRATION_FINISHED_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'THREAD_INTEGRATION_FINISHED_FLAG'.
	this->THREAD_INTEGRATION_FINISHED_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#6: método para setear el estado de la bandera 'NEW_INPUT_FLAG'.
vo	UPCI_SDS::SetNEW_INPUT_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'NEW_INPUT_FLAG'.
	this->NEW_INPUT_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#7: método para setear el estado de la bandera 'NEW_INPUT_DIFFERENCE_RELATION_FLAG'.
vo	UPCI_SDS::SetNEW_INPUT_DIFFERENCE_RELATION_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'NEW_INPUT_DIFFERENCE_RELATION_FLAG'.
	this->NEW_INPUT_DIFFERENCE_RELATION_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#8: método para setear el estado de la bandera 'INIS_CONGRUENCE_ACCOMPLISHED'.
in	UPCI_SDS::SetINIS_CONGRUENCE_ACCOMPLISHED(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'INIS_CONGRUENCE_ACCOMPLISHED'.
	this->INIS_CONGRUENCE_ACCOMPLISHED = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#9: método para setear el estado de la bandera 'INDFRLIS_CONGRUENCE_ACCOMPLISHED'.
in	UPCI_SDS::SetINDFRLIS_CONGRUENCE_ACCOMPLISHED(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'INDFRLIS_CONGRUENCE_ACCOMPLISHED'.
	this->INDFRLIS_CONGRUENCE_ACCOMPLISHED = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#10: método para setear el estado de la bandera 'INPRRLIS_CONGRUENCE_ACCOMPLISHED'.
in	UPCI_SDS::SetINPRRLIS_CONGRUENCE_ACCOMPLISHED(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'INPRRLIS_CONGRUENCE_ACCOMPLISHED'.
	this->INPRRLIS_CONGRUENCE_ACCOMPLISHED = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#11: método para setear el estado de la bandera 'CLOSE_ACTIVE_THREADS_FLAG'.
vo	UPCI_SDS::SetCLOSE_ACTIVE_THREADS_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'CLOSE_ACTIVE_THREADS_FLAG'.
	*this->CLOSE_ACTIVE_THREADS_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#12: método para setear el estado de la bandera 'PAUSE_ACTIVE_THREADS_FLAG'.
vo	UPCI_SDS::SetPAUSE_ACTIVE_THREADS_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'PAUSE_ACTIVE_THREADS_FLAG'.
	*this->PAUSE_ACTIVE_THREADS_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#13: método para setear el estado de la bandera 'PRINT_FLAG'.
vo	UPCI_SDS::SetPRINT_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'PRINT_FLAG'.
	this->PRINT_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para setear estructura INIS con máximo nivel de evaluación.
vo	UPCI_SDS::SetBUFF_INIS_MAX_EVAL(in _inis_id, dou _max_evaluation)
{
	//---------------------------------------------------------------------------------
	//seteo de la máxima evaluación de entrada.
	this->BUFF_INIS_MAX_EVAL->Set(this->UPCI_ID, _inis_id);
	*this->BUFF_MAX_EVALUATION	= _max_evaluation;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para setear estructura INIS con máximo nivel de actividad.
vo	UPCI_SDS::SetBUFF_INIS_MAX_AL(in _str_id, dou _max_activity_level)
{
	//---------------------------------------------------------------------------------
	//seteo del máximo nivel de actividad.
	this->BUFF_INIS_MAX_AL->Set(this->UPCI_ID, _str_id);
	*this->BUFF_MAX_ACTIVITY_LEVEL	= _max_activity_level;	
}

//-------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------- 
//#3: método para setear estructura con máximo fortaleza de la relación
vo	UPCI_SDS::SetBUFF_STR_MAX_RS(in _str_id, in _str_type, in _max_activity_counter)
{
	//---------------------------------------------------------------------------------
	//seteo del máximo fortaleza de la relación.
	this->BUFF_STR_MAX_RS->Set(this->UPCI_ID, _str_id, _str_type);
	*this->BUFF_MAX_RELATION_STRENGTH	= _max_activity_counter;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para setear estructura INIS activada.
vo	UPCI_SDS::SetBUFF_INIS_ACTIVATED(in _inis_id)
{
	//---------------------------------------------------------------------------------
	//seteo de la estructura activada anterior.
	this->BUFF_INIS_ACTIVATED[1].Set(this->BUFF_INIS_ACTIVATED[0].UPCI_ID, this->BUFF_INIS_ACTIVATED[0].STR_ID);

	//---------------------------------------------------------------------------------
	//seteo de la estructura activada presente.
	this->BUFF_INIS_ACTIVATED[0].Set(this->UPCI_ID, _inis_id);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método para setear estructura INIS creada.
vo	UPCI_SDS::SetBUFF_INIS_CRE(in _inis_id)
{
	//---------------------------------------------------------------------------------
	//seteo de la estructura creada anterior.
	this->BUFF_INIS_CRE[1].Set(this->BUFF_INIS_CRE[0].UPCI_ID, this->BUFF_INIS_CRE[0].STR_ID);

	//---------------------------------------------------------------------------------
	//seteo de la estructura creada presente.
	this->BUFF_INIS_CRE[0].Set(this->UPCI_ID, _inis_id);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#6: método para setear estructura PFRLIS creada.
vo	UPCI_SDS::SetBUFF_PFRLIS_CRE(in _pfrlis_id)
{
	//---------------------------------------------------------------------------------
	//seteo de la estructura creada anterior.
	this->BUFF_PFRLIS_CRE[1].Set(this->BUFF_PFRLIS_CRE[0].UPCI_ID, this->BUFF_PFRLIS_CRE[0].STR_ID);

	//---------------------------------------------------------------------------------
	//seteo de la estructura creada presente.
	this->BUFF_PFRLIS_CRE[0].Set(this->UPCI_ID, _pfrlis_id);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#7: método para setear estructura INDFRLIS creada.
vo	UPCI_SDS::SetBUFF_INDFRLIS_CRE(in _indfrlis_id)
{
	//---------------------------------------------------------------------------------
	//seteo de la estructura creada anterior.
	this->BUFF_INDFRLIS_CRE[1].Set(this->BUFF_INDFRLIS_CRE[0].UPCI_ID, this->BUFF_INDFRLIS_CRE[0].STR_ID);

	//---------------------------------------------------------------------------------
	//seteo de la estructura creada presente.
	this->BUFF_INDFRLIS_CRE[0].Set(this->UPCI_ID, _indfrlis_id);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#8: método para setear estructura INPRRLIS creada.
vo	UPCI_SDS::SetBUFF_INPRRLIS_CRE(in _inprrlis_id)
{
	//---------------------------------------------------------------------------------
	//seteo de la estructura creada anterior.
	this->BUFF_INPRRLIS_CRE[1].Set(this->BUFF_INPRRLIS_CRE[0].UPCI_ID, this->BUFF_INPRRLIS_CRE[0].STR_ID);

	//---------------------------------------------------------------------------------
	//seteo de la estructura creada presente.
	this->BUFF_INPRRLIS_CRE[0].Set(this->UPCI_ID, _inprrlis_id);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#9: método para setear estructuras en suspensión.
vo	UPCI_SDS::SetBUFF_STR_SUS(in _str_id, in _str_type)
{
	//---------------------------------------------------------------------------------
	//buffer auxiliar.
	this->BUFF_STR_SUS_AUX.Set(this->UPCI_ID, _str_id);

	//---------------------------------------------------------------------------------
	//seteo de la estructura en suspensión.
	if		(_str_type == INIS_TYPE)		this->BUFF_INIS_SUS->push_back(this->BUFF_STR_SUS_AUX);
	else if (_str_type == PFRLIS_TYPE)		this->BUFF_PFRLIS_SUS->push_back(this->BUFF_STR_SUS_AUX);
	else if (_str_type == INDFRLIS_TYPE)	this->BUFF_INDFRLIS_SUS->push_back(this->BUFF_STR_SUS_AUX);

	//---------------------------------------------------------------------------------
	//limpieza del buffer auxiliar.
	this->BUFF_STR_SUS_AUX.Clean();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método print para debug.
vo	UPCI_SDS::Print(st _message)
{
	//---------------------------------------------------------------------------------
	//impresión de mensaje.
	if (this->GetPRINT_FLAG() == ON) cout << _message << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método print para debug.
vo	UPCI_SDS::Print(st _message, dou _data)
{
	//---------------------------------------------------------------------------------
	//impresión de mensaje.
	if (this->GetPRINT_FLAG() == ON) cout << _message << ": " << _data<<endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método print para debug.
vo	UPCI_SDS::Print(st _message, st _data)
{
	//---------------------------------------------------------------------------------
	//impresión de mensaje.
	if (this->GetPRINT_FLAG() == ON) cout << _message << ": " << _data << endl;
}