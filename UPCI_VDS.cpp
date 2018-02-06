//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
	Nombre Clase : 	  UPCI_I_DS (Unidad de procesos Cognitivos Integradora Limitada tipo 'DS'). 
	Date	    :	  12:58 pm 12-06-2017.
	Diseñador    :	  Jesús
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include "UPCI_I_DS.h"

//-------------------------------------------------------------------------------------  
//-------------------------------------------------------------------------------------
//espacio de nombres.
using namespace UPC;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método constructor 1.
UPCI_I_DS::UPCI_I_DS()
{

}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método constructor 2 para cargar desde interfaz.
UPCI_I_DS::UPCI_I_DS(in _id, in _nat, in _storage_flag, in _seed, UPCI_SDS_ARG &_upci_i_ds_arg)
{	
	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## PARÁMETROS ################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los parámetros estructurales.
	this->GUPCI_ID									=	_upci_i_ds_arg.gupci_id;								//puntero a id de la gupci.
	this->UPCI_ID									=	_id;												//id de la upci.
	this->UPCI_NAT									=	_nat;												//naturaleza de la unidad ('a','b','c'...'z').
	this->INIS_AMOUNT_ALLOWED						=	_upci_i_ds_arg.inis_amount_allowed;				//cantidad de estructuras INIS permitidas.
	this->ACIS_AMOUNT_ALLOWED						=	_upci_i_ds_arg.lacis_amount_allowed;				//cantidad de estructuras ACIS permitidas.
	this->RLIS_AMOUNT_ALLOWED						=	_upci_i_ds_arg.rlis_amount_allowed;					//cantidad de estructuras de relaciones permitidas por tipo.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//parámetros de actividad.
	this->DEFAULT_ACTIVITY_LEVEL					=	_upci_i_ds_arg.default_activity_level;				//nivel de actividad por defecto.
	this->MAX_ACTIVITY_LEVEL_ALLOWED				=	_upci_i_ds_arg.max_activity_level_allowed;			//nivel de actividad máximo permitido.
	this->MIN_ACTIVITY_LEVEL_ALLOWED				=	_upci_i_ds_arg.min_activity_level_allowed;			//nivel de actividad mínimo permitido.

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//incialización de umbrales.
	this->KERNEL_RAW_INPUT_THRESHOLD				=	_upci_i_ds_arg.kernel_raw_input_threshold;			//umbral de entrada cruda para control del núcleo.
	this->DIF_RAW_INPUT_THRESHOLD					=	_upci_i_ds_arg.dif_raw_input_threshold;				//umbral de entrada cruda para focalización de la atención (%).
	this->STR_CONGRUENCE_SR_THRESHOLD				=	_upci_i_ds_arg.str_congruence_sr_threshold;			//umbral de congruencia de registros unidimensionales (%).	
	this->PFRLIS_STRENGTH_THRESHOLD					=	_upci_i_ds_arg.pfrlis_strength_threshold;			//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
	this->INDFRLIS_STRENGTH_THRESHOLD				=	_upci_i_ds_arg.indfrlis_strength_threshold;			//umbral de fortaleza de relación INDFRLIS para eliminar relación por N.A.
	this->TRANSITION_EVALUATION_THRESHOLD						=	_upci_i_ds_arg.transition_evaluation_threshold;					//umbral para transiciones de evaluaciones.	

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
	//inicialización de punteros a banderas para funcionalidades.
	this->SUSPENDED_ACTIONS_MAXIMIZATION_FLAG		=	_upci_i_ds_arg.suspended_actions_maximization_flag;	//puntero a bandera para utilizar reactivación acción suspendida con máxima asociación positiva.
	this->STRUCTURES_RECOGNITION_FLAG				=	_upci_i_ds_arg.structures_recognition_flag;			//puntero a bandrea para utilizar reconocimiento de estructuras.
	this->STRUCTURES_PROJECTIONS_FLAG				=	_upci_i_ds_arg.structures_projections_flag;			//puntero a bandera para utilizar proyección de estructuras.	
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de las banderas del kernel.
	this->KERNEL_INTEGRATION_FLAG					=	OFF;												//bandera del estado de integración del kernel (ON: integrando, OFF: libre).
	this->KERNEL_CONTROL_INTEGRATION_FLAG			=	OFF;												//bandera del estado de integración del control del kernel (ON: integrando, OFF: no controlando).
	this->KERNEL_CONTROL_INTEGRATION_FINISHED_FLAG	=	ON;													//bandera de aviso del término de la integración del control del kernel.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de las banderas del integrador de Hilos.
	this->THREAD_INTEGRATION_FLAG					=	OFF;												//bandera del estado de integración del Hilo (ON: integrando, OFF: libre).
	this->THREAD_INTEGRATION_LATENCY_FLAG			=	OFF;												//bandera del estado de latencia de la integración del Hilo.
	this->THREAD_INTEGRATION_FINISHED_FLAG			=	ON;													//bandera de aviso del término de la integración del Hilo.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de bandera de la existencia de estructuras en estado de suspensión.
	this->SUSPENDED_STRUCTURES_FLAG					=	OFF;												
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de las banderas para estructuras creadas
	this->NEW_INPUT_FLAG							=	OFF;												//bandera de alerta de una nueva entrada.
	this->NEW_INPUT_DIFFERENCE_RELATION_FLAG		=	OFF;												//bandera de alerta de la creación de una nueva relación de diferencia de entradas.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de banderas para threads activos.
	this->CLOSE_ACTIVE_THREADS_FLAG					=	_upci_i_ds_arg.close_active_threads_flag;			//bandera para cerrar threads activos.
	this->PAUSE_ACTIVE_THREADS_FLAG					=	_upci_i_ds_arg.pause_active_threads_flag;			//bandera para pausar threads activos.
	
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
	this->TIMEOUT_CLEAN_IS							=	_upci_i_ds_arg.timeout_clean_is;						//tiempo de espera de limpieza de IS.
	this->TIMEOUT_UPDATE_AL_IS						=	_upci_i_ds_arg.timeout_update_al_is;					//tiempo de espera para actualizar niveles de actividad en IS (ms).

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################### BUFFERS ##################################### 
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de puntero a buffer del grupo de upci.	
	this->BUFF_UPCI_I_DS								=	(deque<UPCI_I_DS>*)_upci_i_ds_arg.buff_upci_i_ds;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------  
	//seteo de puntero a buffer para el id de la upci que puede almacenar estructuras.
	this->BUFF_UPCI_ID_STORAGE_FLAG_ACT				=	_upci_i_ds_arg.buff_upci_id_storage_flag_act;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para las IS.
	this->BUFF_INIS								=	new INIS[this->INIS_AMOUNT_ALLOWED];			//buffer de estructuras de entrada.
	this->BUFF_ACIS								=	new ACIS[this->ACIS_AMOUNT_ALLOWED];			//buffer de estructuras de acción.
	this->BUFF_PFRLIS								=	new PFRLIS[this->RLIS_AMOUNT_ALLOWED];				//buffer de estructuras de relación de flujo puro.
	this->BUFF_INDFRLIS								=	new INDFRLIS[this->RLIS_AMOUNT_ALLOWED];			//buffer de estructuras de relación de flujo diferencial de entradas.
	this->BUFF_INPRRLIS								=	new INPRRLIS[this->RLIS_AMOUNT_ALLOWED];			//buffer de estructuras de relación de flujo proporcional de entradas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para almacenar registros.
	this->BUFF_IN_RG								=	_upci_i_ds_arg.buff_in_rg;							//puntero a buffer para registro de entrada.
	this->BUFF_EV_RG								=	_upci_i_ds_arg.buff_ev_rg;							//puntero a buffer para registro de evaluación de entrada.
	this->BUFF_AC_RG								=	_upci_i_ds_arg.buff_ac_rg;							//puntero a buffer para registro de acción.
	this->BUFF_IN_DIF_RG							=	_upci_i_ds_arg.buff_in_dif_rg;						//puntero a buffer para registro de diferencia de entradas.
	this->BUFF_IN_PRO_RG							=	_upci_i_ds_arg.buff_in_pro_rg;						//puntero a buffer para registro de proporción de diferencia de entradas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de punteros a buffers para acciones.
	this->BUFF_SET_OF_SUPPORTED_ACTIONS				=	_upci_i_ds_arg.buff_set_of_supported_actions;		//puntero a buffer para el conjunto de acciones soportadas.	
	this->BUFF_SUPPORTED_ACTIONS_AMOUNT				=	_upci_i_ds_arg.buff_supported_actions_amount;		//puntero a buffer para la cantidad de acciones soportadas.		

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura con evaluación máxima.
	this->BUFF_STR_MAX_EVAL							=	_upci_i_ds_arg.buff_str_max_eval;					//puntero a buffer para la estructura INIS con máxima evaluación.
	this->BUFF_MAX_EVALUATION						=	_upci_i_ds_arg.buff_max_evaluation;					//puntero a buffer para la máxima evaluación.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura con nivel de actividad máximo.
	this->BUFF_STR_MAX_AL							=	_upci_i_ds_arg.buff_str_max_al;						//puntero a buffer para la estructura con nivel de actividad máximo.
	this->BUFF_MAX_ACTIVITY_LEVEL					=	_upci_i_ds_arg.buff_max_activity_level;				//puntero a buffer para el máximo nivel de actividad.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura con fortaleza de la relación máximo.
	this->BUFF_STR_MAX_RS							=	_upci_i_ds_arg.buff_str_max_rs;						//puntero a buffer para la estructura con fortaleza de la relación máximo.
	this->BUFF_MAX_RELATION_STRENGTH				=	_upci_i_ds_arg.buff_max_relation_strength;			//puntero a buffer para el máximo fortaleza de la relación.	

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de puntero a buffer para las estructuras de acción ejecutadas.
	this->BUFF_EXECUTE_ACIS						=	_upci_i_ds_arg.buff_execute_lacis;	
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para los id de las estructuras disponibles.
	this->BUFF_INIS_ID_AV[0]						=	0;													//buffer del id de INIS disponible actual.
	this->BUFF_INIS_ID_AV[1]						=	-1;													//buffer del id de INIS disponible anterior.
	this->BUFF_ACIS_ID_AV[0]						=	0;													//buffer del id de ACIS disponible actual.
	this->BUFF_ACIS_ID_AV[1]						=	-1;													//buffer del id de ACIS disponible anterior.
	this->BUFF_PFRLIS_ID_AV[0]						=	0;													//buffer del id de PFRLIS disponible actual.
	this->BUFF_PFRLIS_ID_AV[1]						=	-1;													//buffer del id de PFRLIS disponible anterior.
	this->BUFF_INDFRLIS_ID_AV[0]					=	0;													//buffer del id de INDFRLIS disponible actual.
	this->BUFF_INDFRLIS_ID_AV[1]					=	-1;													//buffer del id de INDFRLIS disponible anterior.
	this->BUFF_INPRRLIS_ID_AV[0]					=	0;													//buffer del id de INPRRLIS disponible actual.
	this->BUFF_INPRRLIS_ID_AV[1]					=	-1;													//buffer del id de INPRRLIS disponible anterior.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo a punteros a buffers para los ids de las estructuras creadas.
	this->BUFF_INIS_CRE							=	_upci_i_ds_arg.buff_inis_cre;						//puntero a buffer para id de INIS creada.
	this->BUFF_ACIS_CRE							=	_upci_i_ds_arg.buff_lacis_cre;						//puntero a buffer para id de ACIS creada.
	this->BUFF_PFRLIS_CRE							=	_upci_i_ds_arg.buff_pfrlis_cre;						//puntero a buffer para id de PFRLIS creada.
	this->BUFF_INDFRLIS_CRE							=	_upci_i_ds_arg.buff_indfrlis_cre;					//puntero a buffer para id de INDFRLIS creada.
	this->BUFF_INPRRLIS_CRE							=	_upci_i_ds_arg.buff_inprrlis_cre;					//puntero a buffer para id de INPRRLIS creada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para las estructuras activadas.
	this->BUFF_STR_ACTIVATED						=	_upci_i_ds_arg.buff_str_activated;					//puntero a buffer para las estructuras activadas.
	this->BUFF_INIS_ACTIVATED						=	_upci_i_ds_arg.buff_inis_activated;				//puntero a buffer para las estructuras INIS activadas.
	this->BUFF_ACIS_ACTIVATED						=	_upci_i_ds_arg.buff_lacis_activated;				//puntero a buffer para las estructuras ACIS activadas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para las estructuras en estado de suspensión.		
	this->BUFF_INIS_SUS							=	_upci_i_ds_arg.buff_inis_sus;						//puntero a buffer para las estructuras INIS suspendidas.
	this->BUFF_ACIS_SUS							=	_upci_i_ds_arg.buff_lacis_sus;						//puntero a buffer para las estructuras ACIS suspendidas.
	this->BUFF_PFRLIS_SUS							=	_upci_i_ds_arg.buff_pfrlis_sus;						//puntero a buffer para las estructuras PFRLIS suspendidas.
	this->BUFF_INDFRLIS_SUS							=	_upci_i_ds_arg.buff_indfrlis_sus;					//puntero a buffer para las estructuras INDFRLIS suspendidas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para los id de las upci candidatas. 
	//[a][b]: a: tiempo, b: upci.
	this->BUFF_UPCI_ID_INIS_CAN					=	_upci_i_ds_arg.buff_upci_id_inis_can;				//puntero a buffer de id de las upci candidatas para INIS.
	this->BUFF_UPCI_ID_ACIS_CAN					=	_upci_i_ds_arg.buff_upci_id_lacis_can;				//puntero a buffer de id de las upci candidatas para ACIS.
	this->BUFF_UPCI_ID_INDFRLIS_CAN					=	_upci_i_ds_arg.buff_upci_id_indfrlis_can;			//puntero a buffer de id de las upci candidatas para INDFRLIS.
	this->BUFF_UPCI_ID_INPRRLIS_CAN					=	_upci_i_ds_arg.buff_upci_id_inprrlis_can;			//puntero a buffer de id de las upci candidatas para INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a punteros a buffer de estructuras candidatas. 
	//[a][b][c]: a: tiempo, b: upci, c: buffer de estructura.
	this->BUFF_INIS_ID_CAN						=	_upci_i_ds_arg.buff_inis_id_can;					//puntero a buffer de ids de estructuras tipo INIS candidatas.
	this->BUFF_ACIS_ID_CAN						=	_upci_i_ds_arg.buff_lacis_id_can;					//puntero a buffer de ids de estructuras tipo ACIS candidatas.
	this->BUFF_INDFRLIS_ID_CAN						=	_upci_i_ds_arg.buff_indfrlis_id_can;					//puntero a buffer de ids de estructuras tipo INDFRLIS candidatas.
	this->BUFF_INPRRLIS_ID_CAN						=	_upci_i_ds_arg.buff_inprrlis_id_can;					//puntero a buffer de ids de estructuras tipo INPRRLIS candidatas.

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de puntero a buffer para índice de relación utilizada en reconocimiento.
	this->BUFF_RL_INDEX_USED_IN_RECOGNITION			=	_upci_i_ds_arg.buff_rl_index_used_in_recognition;

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de punteros a buffers para las estructuras reconocidas.
	this->BUFF_INIS_RE							=	_upci_i_ds_arg.buff_inis_re;						//puntero a buffer para estructura reconocida INIS.
	this->BUFF_ACIS_RE							=	_upci_i_ds_arg.buff_lacis_re;						//puntero a buffer para estructura reconocida ACIS.
	this->BUFF_INDFRLIS_RE							=	_upci_i_ds_arg.buff_indfrlis_re;						//puntero a buffer para estructura reconocida INDFRLIS.
	this->BUFF_INPRRLIS_RE							=	_upci_i_ds_arg.buff_inprrlis_re;						//puntero a buffer para estructura reconocida INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para los máximos ids.
	this->BUFF_INIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras INIS.
	this->BUFF_INIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras INIS.
	this->BUFF_ACIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras ACIS.
	this->BUFF_ACIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras ACIS.	
	this->BUFF_PFRLIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras PFRLIS.
	this->BUFF_PFRLIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras PFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[0]					=	-1;													//buffer del máximo id de las estructuras INDFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[1]					=	-1;													//buffer del segundo máximo id de las estructuras INDFRLIS.
	this->BUFF_INPRRLIS_MAX_ID[0]					=	-1;													//buffer del máximo id de las estructuras INPRRLIS.
	this->BUFF_INPRRLIS_MAX_ID[1]					=	-1;													//buffer del segundo máximo id de las estructuras INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para la cantidad de estructuras inicializadas.
	this->BUFF_INIS_INI_AMOUNT					=	NULL;												//buffer de la cantidad de INIS inicializadas.
	this->BUFF_ACIS_INI_AMOUNT					=	NULL;												//buffer de la cantidad de ACIS inicializadas.
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
	//############################ VARIABLES AUXILIARES ############################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//semilla para generación números pseudo aleatorios.
	this->SEED										= _seed;

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## THREADS ###################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//lanzamiento del thread para actualización de nivel de actividad de IS.
	this->TH_UPDATE_AL_STR_BUFFERS					=	thread(&UPC::UPCI_I_DS::UpdateActivityLevelIS, this);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si se ha definifo el tiempo de limpieza, lanzar del thread de limpieza de IS.
	if (this->TIMEOUT_CLEAN_IS != -1)	this->TH_CLEAN_STR_BUFFERS = thread(&UPC::UPCI_I_DS::CleanISBuffers, this);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método destructor.
UPCI_I_DS::~UPCI_I_DS()
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
in	UPCI_I_DS::Initialize(in _nat, UPCI_SDS_ARG &_upci_i_ds_arg)
{	
	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## PARÁMETROS ################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los parámetros estructurales.
	this->GUPCI_ID									=	_upci_i_ds_arg.gupci_id;								//puntero a id de la gupci.
	this->UPCI_NAT									=	_nat;												//naturaleza de la unidad ('a','b','c'...'z').
	this->INIS_AMOUNT_ALLOWED						=	_upci_i_ds_arg.inis_amount_allowed;				//cantidad de estructuras INIS permitidas.
	this->ACIS_AMOUNT_ALLOWED						=	_upci_i_ds_arg.lacis_amount_allowed;				//cantidad de estructuras ACIS permitidas.
	this->RLIS_AMOUNT_ALLOWED						=	_upci_i_ds_arg.rlis_amount_allowed;					//cantidad de estructuras de relaciones permitidas por tipo.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//parámetros de actividad.
	this->DEFAULT_ACTIVITY_LEVEL					=	_upci_i_ds_arg.default_activity_level;				//nivel de actividad por defecto.
	this->MAX_ACTIVITY_LEVEL_ALLOWED				=	_upci_i_ds_arg.max_activity_level_allowed;			//nivel de actividad máximo permitido.
	this->MIN_ACTIVITY_LEVEL_ALLOWED				=	_upci_i_ds_arg.min_activity_level_allowed;			//nivel de actividad mínimo permitido.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de umbrales.
	this->KERNEL_RAW_INPUT_THRESHOLD				=	_upci_i_ds_arg.kernel_raw_input_threshold;			//umbral de entrada cruda para control del núcleo.
	this->DIF_RAW_INPUT_THRESHOLD					=	_upci_i_ds_arg.dif_raw_input_threshold;				//umbral de entrada cruda para focalización de la atención (%).
	this->STR_CONGRUENCE_SR_THRESHOLD				=	_upci_i_ds_arg.str_congruence_sr_threshold;			//umbral de congruencia de registros unidimensionales (%).	
	this->PFRLIS_STRENGTH_THRESHOLD					=	_upci_i_ds_arg.pfrlis_strength_threshold;			//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
	this->INDFRLIS_STRENGTH_THRESHOLD				=	_upci_i_ds_arg.indfrlis_strength_threshold;			//umbral de fortaleza de relación INDFRLIS para eliminar relación por N.A.
	this->EVALUATION_THRESHOLD						=	_upci_i_ds_arg.evaluation_threshold;					//umbral para evaluaciones.	
	this->TRANSITION_EVALUATION_THRESHOLD			=	_upci_i_ds_arg.transition_evaluation_threshold;		//umbral para transiciones de evaluaciones.	

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## BANDERAS ##################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de punteros a banderas para funcionalidades.
	this->SUSPENDED_ACTIONS_MAXIMIZATION_FLAG		=	_upci_i_ds_arg.suspended_actions_maximization_flag;	//puntero a bandera para utilizar reactivación acción suspendida con máxima asociación positiva.
	this->STRUCTURES_RECOGNITION_FLAG				=	_upci_i_ds_arg.structures_recognition_flag;			//puntero a bandrea para utilizar reconocimiento de estructuras.
	this->STRUCTURES_PROJECTIONS_FLAG				=	_upci_i_ds_arg.structures_projections_flag;			//puntero a bandera para utilizar proyección de estructuras.	
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de las banderas del kernel.
	this->KERNEL_INTEGRATION_FLAG					=	OFF;												//bandera del estado de integración del kernel (ON: integrando, OFF: libre).
	this->KERNEL_CONTROL_INTEGRATION_FLAG			=	OFF;												//bandera del estado de integración del control del kernel (ON: integrando, OFF: no controlando).
	this->KERNEL_CONTROL_INTEGRATION_FINISHED_FLAG	=	ON;													//bandera de aviso del término de la integración del control del kernel.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de las banderas del integrador de Hilos.
	this->THREAD_INTEGRATION_FLAG					=	OFF;												//bandera del estado de integración del Hilo (ON: integrando, OFF: libre).
	this->THREAD_INTEGRATION_LATENCY_FLAG			=	OFF;												//bandera del estado de latencia de la integración del Hilo.
	this->THREAD_INTEGRATION_FINISHED_FLAG			=	ON;													//bandera de aviso del término de la integración del Hilo.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de bandera de la existencia de estructuras en estado de suspensión.
	this->SUSPENDED_STRUCTURES_FLAG					=	OFF;												
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de las banderas para estructuras creadas
	this->NEW_INPUT_FLAG							=	OFF;												//bandera de alerta de una nueva entrada.
	this->NEW_INPUT_DIFFERENCE_RELATION_FLAG		=	OFF;												//bandera de alerta de la creación de una nueva relación de diferencia de entradas.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de banderas para threads activos.
	this->CLOSE_ACTIVE_THREADS_FLAG					=	_upci_i_ds_arg.close_active_threads_flag;			//bandera para cerrar threads activos.
	this->PAUSE_ACTIVE_THREADS_FLAG					=	_upci_i_ds_arg.pause_active_threads_flag;			//bandera para pausar threads activos.
	
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
	this->TIMEOUT_CLEAN_IS							=	_upci_i_ds_arg.timeout_clean_is;						//tiempo de espera de limpieza de IS.
	this->TIMEOUT_UPDATE_AL_IS						=	_upci_i_ds_arg.timeout_update_al_is;					//tiempo de espera para actualizar niveles de actividad en IS (ms).

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################### BUFFERS ##################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de puntero a buffer del grupo de upci.	
	this->BUFF_UPCI_I_DS								=	(deque<UPCI_I_DS>*)_upci_i_ds_arg.buff_upci_i_ds;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para las IS.
	this->BUFF_INIS								=	new INIS[this->INIS_AMOUNT_ALLOWED];			//buffer de estructuras de entrada.
	this->BUFF_ACIS								=	new ACIS[this->ACIS_AMOUNT_ALLOWED];			//buffer de estructuras de acción.
	this->BUFF_PFRLIS								=	new PFRLIS[this->RLIS_AMOUNT_ALLOWED];				//buffer de estructuras de relación de flujo puro.
	this->BUFF_INDFRLIS								=	new INDFRLIS[this->RLIS_AMOUNT_ALLOWED];			//buffer de estructuras de relación de flujo diferencial de entradas.
	this->BUFF_INPRRLIS								=	new INPRRLIS[this->RLIS_AMOUNT_ALLOWED];			//buffer de estructuras de relación de flujo proporcional de entradas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para almacenar registros.
	this->BUFF_IN_RG								=	_upci_i_ds_arg.buff_in_rg;							//puntero a buffer para registro de entrada.
	this->BUFF_EV_RG								=	_upci_i_ds_arg.buff_ev_rg;							//puntero a buffer para registro de evaluación de entrada.
	this->BUFF_AC_RG								=	_upci_i_ds_arg.buff_ac_rg;							//puntero a buffer para registro de acción.
	this->BUFF_IN_DIF_RG							=	_upci_i_ds_arg.buff_in_dif_rg;						//puntero a buffer para registro de diferencia de entradas.
	this->BUFF_IN_PRO_RG							=	_upci_i_ds_arg.buff_in_pro_rg;						//puntero a buffer para registro de proporción de diferencia de entradas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de punteros a buffers para acciones.
	this->BUFF_SET_OF_SUPPORTED_ACTIONS				=	_upci_i_ds_arg.buff_set_of_supported_actions;		//puntero a buffer para el conjunto de acciones soportadas.	
	this->BUFF_SUPPORTED_ACTIONS_AMOUNT				=	_upci_i_ds_arg.buff_supported_actions_amount;		//puntero a buffer para la cantidad de acciones soportadas.				

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura con evaluación máxima.
	this->BUFF_STR_MAX_EVAL							=	_upci_i_ds_arg.buff_str_max_eval;					//puntero a buffer para la estructura INIS con máxima evaluación.
	this->BUFF_MAX_EVALUATION						=	_upci_i_ds_arg.buff_max_evaluation;					//puntero a buffer para la máxima evaluación.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura con nivel de actividad máximo.
	this->BUFF_STR_MAX_AL							=	_upci_i_ds_arg.buff_str_max_al;						//puntero a buffer para la estructura con nivel de actividad máximo.
	this->BUFF_MAX_ACTIVITY_LEVEL					=	_upci_i_ds_arg.buff_max_activity_level;				//puntero a buffer para el máximo nivel de actividad.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura con fortaleza de la relación máximo.
	this->BUFF_STR_MAX_RS							=	_upci_i_ds_arg.buff_str_max_rs;						//puntero a buffer para la estructura con fortaleza de la relación máximo.
	this->BUFF_MAX_RELATION_STRENGTH				=	_upci_i_ds_arg.buff_max_relation_strength;			//puntero a buffer para el máximo fortaleza de la relación.		

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de puntero a buffer para las estructuras de acción ejecutadas.
	this->BUFF_EXECUTE_ACIS						=	_upci_i_ds_arg.buff_execute_lacis;		

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para los id de las estructuras disponibles.
	this->BUFF_INIS_ID_AV[0]						=	0;													//buffer del id de INIS disponible actual.
	this->BUFF_INIS_ID_AV[1]						=	-1;													//buffer del id de INIS disponible anterior.
	this->BUFF_ACIS_ID_AV[0]						=	0;													//buffer del id de ACIS disponible actual.
	this->BUFF_ACIS_ID_AV[1]						=	-1;													//buffer del id de ACIS disponible anterior.
	this->BUFF_PFRLIS_ID_AV[0]						=	0;													//buffer del id de PFRLIS disponible actual.
	this->BUFF_PFRLIS_ID_AV[1]						=	-1;													//buffer del id de PFRLIS disponible anterior.
	this->BUFF_INDFRLIS_ID_AV[0]					=	0;													//buffer del id de INDFRLIS disponible actual.
	this->BUFF_INDFRLIS_ID_AV[1]					=	-1;													//buffer del id de INDFRLIS disponible anterior.
	this->BUFF_INPRRLIS_ID_AV[0]					=	0;													//buffer del id de INPRRLIS disponible actual.
	this->BUFF_INPRRLIS_ID_AV[1]					=	-1;													//buffer del id de INPRRLIS disponible anterior.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para los ids de las estructuras creadas.
	this->BUFF_INIS_CRE							=	_upci_i_ds_arg.buff_inis_cre;						//puntero a buffer para id de INIS creada.
	this->BUFF_ACIS_CRE							=	_upci_i_ds_arg.buff_lacis_cre;						//puntero a buffer para id de ACIS creada.
	this->BUFF_PFRLIS_CRE							=	_upci_i_ds_arg.buff_pfrlis_cre;						//puntero a buffer para id de PFRLIS creada.
	this->BUFF_INDFRLIS_CRE							=	_upci_i_ds_arg.buff_indfrlis_cre;					//puntero a buffer para id de INDFRLIS creada.
	this->BUFF_INPRRLIS_CRE							=	_upci_i_ds_arg.buff_inprrlis_cre;					//puntero a buffer para id de INPRRLIS creada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para las estructuras activadas.
	this->BUFF_STR_ACTIVATED						=	_upci_i_ds_arg.buff_str_activated;					//puntero a buffer para las estructuras activadas.
	this->BUFF_INIS_ACTIVATED						=	_upci_i_ds_arg.buff_inis_activated;				//puntero a buffer para las estructuras INIS activadas.
	this->BUFF_ACIS_ACTIVATED						=	_upci_i_ds_arg.buff_lacis_activated;				//puntero a buffer para las estructuras ACIS activadas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para las estructuras en estado de suspensión.		
	this->BUFF_INIS_SUS							=	_upci_i_ds_arg.buff_inis_sus;						//puntero a buffer para las estructuras INIS suspendidas.
	this->BUFF_ACIS_SUS							=	_upci_i_ds_arg.buff_lacis_sus;						//puntero a buffer para las estructuras ACIS suspendidas.
	this->BUFF_PFRLIS_SUS							=	_upci_i_ds_arg.buff_pfrlis_sus;						//puntero a buffer para las estructuras PFRLIS suspendidas.
	this->BUFF_INDFRLIS_SUS							=	_upci_i_ds_arg.buff_indfrlis_sus;					//puntero a buffer para las estructuras INDFRLIS suspendidas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para los id de las upci candidatas. 
	//[a][b]: a: tiempo, b: upci.
	this->BUFF_UPCI_ID_INIS_CAN					=	_upci_i_ds_arg.buff_upci_id_inis_can;				//puntero a buffer de id de las upci candidatas para INIS.
	this->BUFF_UPCI_ID_ACIS_CAN					=	_upci_i_ds_arg.buff_upci_id_lacis_can;				//puntero a buffer de id de las upci candidatas para ACIS.
	this->BUFF_UPCI_ID_INDFRLIS_CAN					=	_upci_i_ds_arg.buff_upci_id_indfrlis_can;			//puntero a buffer de id de las upci candidatas para INDFRLIS.
	this->BUFF_UPCI_ID_INPRRLIS_CAN					=	_upci_i_ds_arg.buff_upci_id_inprrlis_can;			//puntero a buffer de id de las upci candidatas para INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffer de estructuras candidatas. 
	//[a][b][c]: a: tiempo, b: upci, c: buffer de estructura.
	this->BUFF_INIS_ID_CAN						=	_upci_i_ds_arg.buff_inis_id_can;					//puntero a buffer de ids de estructuras tipo INIS candidatas.
	this->BUFF_ACIS_ID_CAN						=	_upci_i_ds_arg.buff_lacis_id_can;					//puntero a buffer de ids de estructuras tipo ACIS candidatas.
	this->BUFF_INDFRLIS_ID_CAN						=	_upci_i_ds_arg.buff_indfrlis_id_can;					//puntero a buffer de ids de estructuras tipo INDFRLIS candidatas.
	this->BUFF_INPRRLIS_ID_CAN						=	_upci_i_ds_arg.buff_inprrlis_id_can;					//puntero a buffer de ids de estructuras tipo INPRRLIS candidatas.

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de puntero a buffer para índice de relación utilizada en reconocimiento.
	this->BUFF_RL_INDEX_USED_IN_RECOGNITION			=	_upci_i_ds_arg.buff_rl_index_used_in_recognition;

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de punteros a buffers para las estructuras reconocidas.
	this->BUFF_INIS_RE							=	_upci_i_ds_arg.buff_inis_re;						//puntero a buffer para estructura reconocida INIS.
	this->BUFF_ACIS_RE							=	_upci_i_ds_arg.buff_lacis_re;						//puntero a buffer para estructura reconocida ACIS.
	this->BUFF_INDFRLIS_RE							=	_upci_i_ds_arg.buff_indfrlis_re;						//puntero a buffer para estructura reconocida INDFRLIS.
	this->BUFF_INPRRLIS_RE							=	_upci_i_ds_arg.buff_inprrlis_re;						//puntero a buffer para estructura reconocida INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para los máximos ids.
	this->BUFF_INIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras INIS.
	this->BUFF_INIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras INIS.
	this->BUFF_ACIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras ACIS.
	this->BUFF_ACIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras ACIS.	
	this->BUFF_PFRLIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras PFRLIS.
	this->BUFF_PFRLIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras PFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[0]					=	-1;													//buffer del máximo id de las estructuras INDFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[1]					=	-1;													//buffer del segundo máximo id de las estructuras INDFRLIS.
	this->BUFF_INPRRLIS_MAX_ID[0]					=	-1;													//buffer del máximo id de las estructuras INPRRLIS.
	this->BUFF_INPRRLIS_MAX_ID[1]					=	-1;													//buffer del segundo máximo id de las estructuras INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para la cantidad de estructuras inicializadas.
	this->BUFF_INIS_INI_AMOUNT					=	NULL;												//buffer de la cantidad de INIS inicializadas.
	this->BUFF_ACIS_INI_AMOUNT					=	NULL;												//buffer de la cantidad de ACIS inicializadas.
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
	//this->TH_UPDATE_AL_STR_BUFFERS					=	thread(&UPC::UPCI_I_DS::UpdateActivityLevelIS, this);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si se ha definifo el tiempo de limpieza, lanzar del thread de limpieza de IS.
	if (this->TIMEOUT_CLEAN_IS != -1)	this->TH_CLEAN_STR_BUFFERS = thread(&UPC::UPCI_I_DS::CleanISBuffers, this);

	//---------------------------------------------------------------------------------
	//successful execution.
	return SUCCESS;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método de inicialización 2 para cargar desde interfaz.
in	UPCI_I_DS::Initialize(in _id, in _nat, in _storage_flag, in _seed, UPCI_SDS_ARG &_upci_i_ds_arg)
{
	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## PARÁMETROS ################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los parámetros estructurales.
	this->GUPCI_ID									=	_upci_i_ds_arg.gupci_id;								//puntero a id de la gupci.
	this->UPCI_ID									=	_id;												//id de la upci.
	this->UPCI_NAT									=	_nat;												//naturaleza de la unidad ('a','b','c'...'z').
	this->INIS_AMOUNT_ALLOWED						=	_upci_i_ds_arg.inis_amount_allowed;				//cantidad de estructuras INIS permitidas.
	this->ACIS_AMOUNT_ALLOWED						=	_upci_i_ds_arg.lacis_amount_allowed;				//cantidad de estructuras ACIS permitidas.
	this->RLIS_AMOUNT_ALLOWED						=	_upci_i_ds_arg.rlis_amount_allowed;					//cantidad de estructuras de relaciones permitidas por tipo.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//parámetros de actividad.
	this->DEFAULT_ACTIVITY_LEVEL					=	_upci_i_ds_arg.default_activity_level;				//nivel de actividad por defecto.
	this->MAX_ACTIVITY_LEVEL_ALLOWED				=	_upci_i_ds_arg.max_activity_level_allowed;			//nivel de actividad máximo permitido.
	this->MIN_ACTIVITY_LEVEL_ALLOWED				=	_upci_i_ds_arg.min_activity_level_allowed;			//nivel de actividad mínimo permitido.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de umbrales.
	this->KERNEL_RAW_INPUT_THRESHOLD				=	_upci_i_ds_arg.kernel_raw_input_threshold;			//umbral de entrada cruda para control del núcleo.
	this->DIF_RAW_INPUT_THRESHOLD					=	_upci_i_ds_arg.dif_raw_input_threshold;				//umbral de entrada cruda para focalización de la atención (%).
	this->STR_CONGRUENCE_SR_THRESHOLD				=	_upci_i_ds_arg.str_congruence_sr_threshold;			//umbral de congruencia de registros unidimensionales (%).	
	this->PFRLIS_STRENGTH_THRESHOLD					=	_upci_i_ds_arg.pfrlis_strength_threshold;			//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
	this->INDFRLIS_STRENGTH_THRESHOLD				=	_upci_i_ds_arg.indfrlis_strength_threshold;			//umbral de fortaleza de relación INDFRLIS para eliminar relación por N.A.
	this->EVALUATION_THRESHOLD						=	_upci_i_ds_arg.evaluation_threshold;					//umbral para evaluaciones.	
	this->TRANSITION_EVALUATION_THRESHOLD			=	_upci_i_ds_arg.transition_evaluation_threshold;		//umbral para transiciones de evaluaciones.	

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
	//inicialización de punteros a banderas para funcionalidades.
	this->SUSPENDED_ACTIONS_MAXIMIZATION_FLAG		=	_upci_i_ds_arg.suspended_actions_maximization_flag;	//puntero a bandera para utilizar reactivación acción suspendida con máxima asociación positiva.
	this->STRUCTURES_RECOGNITION_FLAG				=	_upci_i_ds_arg.structures_recognition_flag;			//puntero a bandrea para utilizar reconocimiento de estructuras.
	this->STRUCTURES_PROJECTIONS_FLAG				=	_upci_i_ds_arg.structures_projections_flag;			//puntero a bandera para utilizar proyección de estructuras.	
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de las banderas del kernel.
	this->KERNEL_INTEGRATION_FLAG					=	OFF;												//bandera del estado de integración del kernel (ON: integrando, OFF: libre).
	this->KERNEL_CONTROL_INTEGRATION_FLAG			=	OFF;												//bandera del estado de integración del control del kernel (ON: integrando, OFF: no controlando).
	this->KERNEL_CONTROL_INTEGRATION_FINISHED_FLAG	=	ON;													//bandera de aviso del término de la integración del control del kernel.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de las banderas del integrador de Hilos.
	this->THREAD_INTEGRATION_FLAG					=	OFF;												//bandera del estado de integración del Hilo (ON: integrando, OFF: libre).
	this->THREAD_INTEGRATION_LATENCY_FLAG			=	OFF;												//bandera del estado de latencia de la integración del Hilo.
	this->THREAD_INTEGRATION_FINISHED_FLAG			=	ON;													//bandera de aviso del término de la integración del Hilo.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de bandera de la existencia de estructuras en estado de suspensión.
	this->SUSPENDED_STRUCTURES_FLAG					=	OFF;												
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de las banderas para estructuras creadas
	this->NEW_INPUT_FLAG							=	OFF;												//bandera de alerta de una nueva entrada.
	this->NEW_INPUT_DIFFERENCE_RELATION_FLAG		=	OFF;												//bandera de alerta de la creación de una nueva relación de diferencia de entradas.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de banderas para threads activos.
	this->CLOSE_ACTIVE_THREADS_FLAG					=	_upci_i_ds_arg.close_active_threads_flag;			//bandera para cerrar threads activos.
	this->PAUSE_ACTIVE_THREADS_FLAG					=	_upci_i_ds_arg.pause_active_threads_flag;			//bandera para pausar threads activos.
	
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
	this->TIMEOUT_CLEAN_IS							=	_upci_i_ds_arg.timeout_clean_is;						//tiempo de espera de limpieza de IS.
	this->TIMEOUT_UPDATE_AL_IS						=	_upci_i_ds_arg.timeout_update_al_is;					//tiempo de espera para actualizar niveles de actividad en IS (ms).

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################### BUFFERS ##################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de puntero a buffer del grupo de upci.	
	this->BUFF_UPCI_I_DS								=	(deque<UPCI_I_DS>*)_upci_i_ds_arg.buff_upci_i_ds;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------  
	//seteo de puntero a buffer para el id de la upci que puede almacenar estructuras.
	this->BUFF_UPCI_ID_STORAGE_FLAG_ACT				=	_upci_i_ds_arg.buff_upci_id_storage_flag_act;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para las IS.
	this->BUFF_INIS								=	new INIS[this->INIS_AMOUNT_ALLOWED];			//buffer de estructuras de entrada.
	this->BUFF_ACIS								=	new ACIS[this->ACIS_AMOUNT_ALLOWED];			//buffer de estructuras de acción.
	this->BUFF_PFRLIS								=	new PFRLIS[this->RLIS_AMOUNT_ALLOWED];				//buffer de estructuras de relación de flujo puro.
	this->BUFF_INDFRLIS								=	new INDFRLIS[this->RLIS_AMOUNT_ALLOWED];			//buffer de estructuras de relación de flujo diferencial de entradas.
	this->BUFF_INPRRLIS								=	new INPRRLIS[this->RLIS_AMOUNT_ALLOWED];			//buffer de estructuras de relación de flujo proporcional de entradas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para almacenar registros.
	this->BUFF_IN_RG								=	_upci_i_ds_arg.buff_in_rg;							//puntero a buffer para registro de entrada.
	this->BUFF_EV_RG								=	_upci_i_ds_arg.buff_ev_rg;							//puntero a buffer para registro de evaluación de entrada.
	this->BUFF_AC_RG								=	_upci_i_ds_arg.buff_ac_rg;							//puntero a buffer para registro de acción.
	this->BUFF_IN_DIF_RG							=	_upci_i_ds_arg.buff_in_dif_rg;						//puntero a buffer para registro de diferencia de entradas.
	this->BUFF_IN_PRO_RG							=	_upci_i_ds_arg.buff_in_pro_rg;						//puntero a buffer para registro de proporción de diferencia de entradas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de punteros a buffers para acciones.
	this->BUFF_SET_OF_SUPPORTED_ACTIONS				=	_upci_i_ds_arg.buff_set_of_supported_actions;		//puntero a buffer para el conjunto de acciones soportadas.	
	this->BUFF_SUPPORTED_ACTIONS_AMOUNT				=	_upci_i_ds_arg.buff_supported_actions_amount;		//puntero a buffer para la cantidad de acciones soportadas.	
	
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura con evaluación máxima.
	this->BUFF_STR_MAX_EVAL							=	_upci_i_ds_arg.buff_str_max_eval;					//puntero a buffer para la estructura INIS con máxima evaluación.
	this->BUFF_MAX_EVALUATION						=	_upci_i_ds_arg.buff_max_evaluation;					//puntero a buffer para la máxima evaluación.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura con nivel de actividad máximo.
	this->BUFF_STR_MAX_AL							=	_upci_i_ds_arg.buff_str_max_al;						//puntero a buffer para la estructura con nivel de actividad máximo.
	this->BUFF_MAX_ACTIVITY_LEVEL					=	_upci_i_ds_arg.buff_max_activity_level;				//puntero a buffer para el máximo nivel de actividad.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//seteo de punteros a buffers para estructura con fortaleza de la relación máximo.
	this->BUFF_STR_MAX_RS							=	_upci_i_ds_arg.buff_str_max_rs;						//puntero a buffer para la estructura con fortaleza de la relación máximo.
	this->BUFF_MAX_RELATION_STRENGTH				=	_upci_i_ds_arg.buff_max_relation_strength;			//puntero a buffer para el máximo fortaleza de la relación.		

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de puntero a buffer para las estructuras de acción ejecutadas.
	this->BUFF_EXECUTE_ACIS						=	_upci_i_ds_arg.buff_execute_lacis;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para los id de las estructuras disponibles.
	this->BUFF_INIS_ID_AV[0]						=	0;													//buffer del id de INIS disponible actual.
	this->BUFF_INIS_ID_AV[1]						=	-1;													//buffer del id de INIS disponible anterior.
	this->BUFF_ACIS_ID_AV[0]						=	0;													//buffer del id de ACIS disponible actual.
	this->BUFF_ACIS_ID_AV[1]						=	-1;													//buffer del id de ACIS disponible anterior.
	this->BUFF_PFRLIS_ID_AV[0]						=	0;													//buffer del id de PFRLIS disponible actual.
	this->BUFF_PFRLIS_ID_AV[1]						=	-1;													//buffer del id de PFRLIS disponible anterior.
	this->BUFF_INDFRLIS_ID_AV[0]					=	0;													//buffer del id de INDFRLIS disponible actual.
	this->BUFF_INDFRLIS_ID_AV[1]					=	-1;													//buffer del id de INDFRLIS disponible anterior.
	this->BUFF_INPRRLIS_ID_AV[0]					=	0;													//buffer del id de INPRRLIS disponible actual.
	this->BUFF_INPRRLIS_ID_AV[1]					=	-1;													//buffer del id de INPRRLIS disponible anterior.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para los ids de las estructuras creadas.
	this->BUFF_INIS_CRE							=	_upci_i_ds_arg.buff_inis_cre;						//puntero a buffer para id de INIS creada.
	this->BUFF_ACIS_CRE							=	_upci_i_ds_arg.buff_lacis_cre;						//puntero a buffer para id de ACIS creada.
	this->BUFF_PFRLIS_CRE							=	_upci_i_ds_arg.buff_pfrlis_cre;						//puntero a buffer para id de PFRLIS creada.
	this->BUFF_INDFRLIS_CRE							=	_upci_i_ds_arg.buff_indfrlis_cre;					//puntero a buffer para id de INDFRLIS creada.
	this->BUFF_INPRRLIS_CRE							=	_upci_i_ds_arg.buff_inprrlis_cre;					//puntero a buffer para id de INPRRLIS creada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para las estructuras activadas.
	this->BUFF_STR_ACTIVATED						=	_upci_i_ds_arg.buff_str_activated;					//puntero a buffer para las estructuras activadas.
	this->BUFF_INIS_ACTIVATED						=	_upci_i_ds_arg.buff_inis_activated;				//puntero a buffer para las estructuras INIS activadas.
	this->BUFF_ACIS_ACTIVATED						=	_upci_i_ds_arg.buff_lacis_activated;				//puntero a buffer para las estructuras ACIS activadas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para las estructuras en estado de suspensión.		
	this->BUFF_INIS_SUS							=	_upci_i_ds_arg.buff_inis_sus;						//puntero a buffer para las estructuras INIS suspendidas.
	this->BUFF_ACIS_SUS							=	_upci_i_ds_arg.buff_lacis_sus;						//puntero a buffer para las estructuras ACIS suspendidas.
	this->BUFF_PFRLIS_SUS							=	_upci_i_ds_arg.buff_pfrlis_sus;						//puntero a buffer para las estructuras PFRLIS suspendidas.
	this->BUFF_INDFRLIS_SUS							=	_upci_i_ds_arg.buff_indfrlis_sus;					//puntero a buffer para las estructuras INDFRLIS suspendidas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para los id de las upci candidatas. 
	//[a][b]: a: tiempo, b: upci.
	this->BUFF_UPCI_ID_INIS_CAN					=	_upci_i_ds_arg.buff_upci_id_inis_can;				//puntero a buffer de id de las upci candidatas para INIS.
	this->BUFF_UPCI_ID_ACIS_CAN					=	_upci_i_ds_arg.buff_upci_id_lacis_can;				//puntero a buffer de id de las upci candidatas para ACIS.
	this->BUFF_UPCI_ID_INDFRLIS_CAN					=	_upci_i_ds_arg.buff_upci_id_indfrlis_can;			//puntero a buffer de id de las upci candidatas para INDFRLIS.
	this->BUFF_UPCI_ID_INPRRLIS_CAN					=	_upci_i_ds_arg.buff_upci_id_inprrlis_can;			//puntero a buffer de id de las upci candidatas para INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de punteros a punteros a buffer de estructuras candidatas. 
	//[a][b][c]: a: tiempo, b: upci, c: buffer de estructura.
	this->BUFF_INIS_ID_CAN						=	_upci_i_ds_arg.buff_inis_id_can;					//puntero a buffer de ids de estructuras tipo INIS candidatas.
	this->BUFF_ACIS_ID_CAN						=	_upci_i_ds_arg.buff_lacis_id_can;					//puntero a buffer de ids de estructuras tipo ACIS candidatas.
	this->BUFF_INDFRLIS_ID_CAN						=	_upci_i_ds_arg.buff_indfrlis_id_can;					//puntero a buffer de ids de estructuras tipo INDFRLIS candidatas.
	this->BUFF_INPRRLIS_ID_CAN						=	_upci_i_ds_arg.buff_inprrlis_id_can;					//puntero a buffer de ids de estructuras tipo INPRRLIS candidatas.

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de puntero a buffer para índice de relación utilizada en reconocimiento.
	this->BUFF_RL_INDEX_USED_IN_RECOGNITION			=	_upci_i_ds_arg.buff_rl_index_used_in_recognition;

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de punteros a buffers para las estructuras reconocidas.
	this->BUFF_INIS_RE							=	_upci_i_ds_arg.buff_inis_re;						//puntero a buffer para estructura reconocida INIS.
	this->BUFF_ACIS_RE							=	_upci_i_ds_arg.buff_lacis_re;						//puntero a buffer para estructura reconocida ACIS.
	this->BUFF_INDFRLIS_RE							=	_upci_i_ds_arg.buff_indfrlis_re;						//puntero a buffer para estructura reconocida INDFRLIS.
	this->BUFF_INPRRLIS_RE							=	_upci_i_ds_arg.buff_inprrlis_re;						//puntero a buffer para estructura reconocida INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para los máximos ids.
	this->BUFF_INIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras INIS.
	this->BUFF_INIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras INIS.
	this->BUFF_ACIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras ACIS.
	this->BUFF_ACIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras ACIS.	
	this->BUFF_PFRLIS_MAX_ID[0]						=	-1;													//buffer del máximo id de las estructuras PFRLIS.
	this->BUFF_PFRLIS_MAX_ID[1]						=	-1;													//buffer del segundo máximo id de las estructuras PFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[0]					=	-1;													//buffer del máximo id de las estructuras INDFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[1]					=	-1;													//buffer del segundo máximo id de las estructuras INDFRLIS.
	this->BUFF_INPRRLIS_MAX_ID[0]					=	-1;													//buffer del máximo id de las estructuras INPRRLIS.
	this->BUFF_INPRRLIS_MAX_ID[1]					=	-1;													//buffer del segundo máximo id de las estructuras INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de los buffers para la cantidad de estructuras inicializadas.
	this->BUFF_INIS_INI_AMOUNT					=	NULL;												//buffer de la cantidad de INIS inicializadas.
	this->BUFF_ACIS_INI_AMOUNT					=	NULL;												//buffer de la cantidad de ACIS inicializadas.
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
	//############################ VARIABLES AUXILIARES ############################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//semilla para generación números pseudo aleatorios.
	this->SEED										= _seed;
	
	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## THREADS ###################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//lanzamiento del thread para actualización de nivel de actividad de IS.
	//this->TH_UPDATE_AL_STR_BUFFERS					=	thread(&UPC::UPCI_I_DS::UpdateActivityLevelIS, this);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si se ha definifo el tiempo de limpieza, lanzar del thread de limpieza de IS.
	if (this->TIMEOUT_CLEAN_IS != -1)	this->TH_CLEAN_STR_BUFFERS = thread(&UPC::UPCI_I_DS::CleanISBuffers, this);

	//---------------------------------------------------------------------------------
	//successful execution.
	return SUCCESS;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para Clean upci.
in	UPCI_I_DS::Clean()
{		
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//seteo de la bandera para cerrar threads activos.
	this->SetCLOSE_ACTIVE_THREADS_FLAG(ON);
	
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//término de threads.
	if (this->TH_THREAD_INTEGRATION.joinable()				== ON)	this->TH_THREAD_INTEGRATION.join();
	if (this->TH_CLEAN_STR_BUFFERS.joinable()				== ON)	this->TH_CLEAN_STR_BUFFERS.join();
	if (this->TH_KERNEL_ACTION_CONTROL.joinable()			== ON)	this->TH_KERNEL_ACTION_CONTROL.join();
	if (this->TH_UPDATE_AL_STR_BUFFERS.joinable()			== ON)	this->TH_UPDATE_AL_STR_BUFFERS.join();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de los parámetros estructurales.
	this->UPCI_ID									=	-1;									//id de la upci.
	this->UPCI_NAT									=	-1;									//naturaleza de la unidad ('a','b','c'...'z').
	this->INIS_AMOUNT_ALLOWED						=	NULL;								//cantidad de estructuras INIS permitidas.
	this->ACIS_AMOUNT_ALLOWED						=	NULL;								//cantidad de estructuras ACIS permitidas.
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
	this->KERNEL_RAW_INPUT_THRESHOLD				=	NULL;								//umbral de entrada cruda para control del núcleo.
	this->DIF_RAW_INPUT_THRESHOLD					=	NULL;								//umbral de entrada cruda para focalización de la atención (%).
	this->STR_CONGRUENCE_SR_THRESHOLD				=	NULL;								//umbral de congruencia de registros unidimensionales (%).	
	this->PFRLIS_STRENGTH_THRESHOLD					=	NULL;								//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
	this->INDFRLIS_STRENGTH_THRESHOLD				=	NULL;								//umbral de fortaleza de relación INDFRLIS para eliminar relación por N.A.
	this->EVALUATION_THRESHOLD						=	NULL;								//umbral para evaluaciones.	
	this->TRANSITION_EVALUATION_THRESHOLD			=	NULL;								//umbral para transiciones de evaluaciones.	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de las banderas.
	this->STORAGE_FLAG								=	-1;									//bandera del estado del almacenamiento de la unidad (ON: salvar, OFF: no-salvar).
	this->KERNEL_INTEGRATION_FLAG					=	-1;									//bandera del estado de integración del kernel (ON: integrando, OFF: libre).
	this->KERNEL_CONTROL_INTEGRATION_FLAG			=	-1;									//bandera del estado de integración del control del kernel (ON: integrando, OFF: no controlando).
	this->KERNEL_CONTROL_INTEGRATION_FINISHED_FLAG	=	-1;									//bandera de aviso del término de la integración del control del kernel.
	this->THREAD_INTEGRATION_FLAG					=	-1;									//bandera del estado de integración de la unidad (ON: integrando, OFF: libre).
	this->THREAD_INTEGRATION_LATENCY_FLAG			=	-1;									//bandera del estado de latencia de la integración.
	this->THREAD_INTEGRATION_FINISHED_FLAG			=	-1;									//bandera de aviso del término de la integración del Hilo.
	this->SUSPENDED_STRUCTURES_FLAG					=	-1;									//bandera de la existencia de estructuras en estado de suspensión.
	this->NEW_INPUT_FLAG							=	-1;									//bandera de alerta de una nueva entrada.
	this->NEW_INPUT_DIFFERENCE_RELATION_FLAG		=	-1;									//bandera de alerta de la creación de una nueva relación INDFRLIS.
	this->PRINT_FLAG								=	-1;									//bandera para imprimir en pantalla.	
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de los buffers para las IS.
	delete[] this->BUFF_INIS;																//buffer para estructuras tipo INIS.
	delete[] this->BUFF_ACIS;																//buffer para estructuras tipo ACIS.
	delete[] this->BUFF_PFRLIS;																//buffer para estructuras tipo PFRLIS.	
	delete[] this->BUFF_INDFRLIS;															//buffer para estructuras tipo INDFRLIS.	
	delete[] this->BUFF_INPRRLIS;															//buffer para estructuras tipo INPRRLIS.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de los buffers para los id de las estructuras disponibles.
	this->BUFF_INIS_ID_AV[0]						=	-1;									//buffer para id de INIS disponible actual.
	this->BUFF_INIS_ID_AV[1]						=	-1;									//buffer para id de INIS disponible anterior.
	this->BUFF_ACIS_ID_AV[0]						=	-1;									//buffer para id de ACIS disponible actual.
	this->BUFF_ACIS_ID_AV[1]						=	-1;									//buffer para id de ACIS disponible anterior.
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
	this->BUFF_ACIS_MAX_ID[0]						=	-1;									//buffer del máximo id de las estructuras ACIS.
	this->BUFF_ACIS_MAX_ID[1]						=	-1;									//buffer del segundo máximo id de las estructuras ACIS.	
	this->BUFF_PFRLIS_MAX_ID[0]						=	-1;									//buffer del máximo id de las estructuras PFRLIS.
	this->BUFF_PFRLIS_MAX_ID[1]						=	-1;									//buffer del segundo máximo id de las estructuras PFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[0]					=	-1;									//buffer del máximo id de las estructuras INDFRLIS.
	this->BUFF_INDFRLIS_MAX_ID[1]					=	-1;									//buffer del segundo máximo id de las estructuras INDFRLIS.
	this->BUFF_INPRRLIS_MAX_ID[0]					=	-1;									//buffer del máximo id de las estructuras INPRRLIS.
	this->BUFF_INPRRLIS_MAX_ID[1]					=	-1;									//buffer del segundo máximo id de las estructuras INPRRLIS.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de los buffers para la cantidad de estructuras inicializadas.
	this->BUFF_INIS_INI_AMOUNT					=	NULL;								//buffer de la cantidad de INIS inicializadas.
	this->BUFF_ACIS_INI_AMOUNT					=	NULL;								//buffer de la cantidad de ACIS inicializadas.
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
vo	UPCI_I_DS::KernelInput(dou _input, dou _input_evaluation, st *_output_action)
{	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura activada anterior.
	in	inis_id		= NULL;																//id de la estructura INIS activada anteriormente.
	in	upci_id_inis	= NULL;																//id de la upci de la estructura INIS activada anteriormente.	
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//activación de la bandera de integración del Kernel.
	this->SetKERNEL_INTEGRATION_FLAG(ON);
	
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//término del thread de control del kernel.
	if (this->TH_KERNEL_ACTION_CONTROL.joinable() == ON) this->TH_KERNEL_ACTION_CONTROL.join();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la entrada cruda es crítica y si el hilo "KernelActionControl" no está 
	//integrando y ha finalizado.
	if (_input >= this->KERNEL_RAW_INPUT_THRESHOLD && this->GetKERNEL_CONTROL_INTEGRATION_FLAG() == OFF && this->GetKERNEL_CONTROL_INTEGRATION_FINISHED_FLAG() == ON)
	{
		//-----------------------------------------------------------------------------
		//el kernel entra en estado de control.
		this->TH_KERNEL_ACTION_CONTROL = thread(&UPC::UPCI_I_DS::KernelActionControl, this, _input, _output_action);
	}

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//si el hilo "KernelActionControl" no está integrando y no ha finalizado.
	else if (this->GetKERNEL_CONTROL_INTEGRATION_FLAG() == OFF && this->GetKERNEL_CONTROL_INTEGRATION_FINISHED_FLAG() == OFF)
	{
		//-----------------------------------------------------------------------------
		//seteo del registro de entrada.
		*this->BUFF_IN_RG = _input;
		
		//----------------------------------------------------------------------------- 
		//seteo de la bandera NEW_INPUT_FLAG para alertar a Hilo en suspensión si este existe.
		this->SetNEW_INPUT_FLAG(ON);
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seguir el curso normal de ejecución.
	else
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si el hilo "ThreadIntegrationInput" no está integrando y ha finalizado.
		if (this->GetTHREAD_INTEGRATION_FLAG() == OFF && this->GetTHREAD_INTEGRATION_FINISHED_FLAG() == ON)
		{			
			//-------------------------------------------------------------------------
			//obtención de datos para estructura activada anterior.
			inis_id								= this->BUFF_INIS_ACTIVATED[1].STR_ID;					
			upci_id_inis							= this->BUFF_INIS_ACTIVATED[1].UPCI_ID;	

			//-------------------------------------------------------------------------
			//seteo del registro de entrada.
			*this->BUFF_IN_RG						= _input;

			//-------------------------------------------------------------------------
			//término del thread.
			if (this->TH_THREAD_INTEGRATION.joinable() == ON)	this->TH_THREAD_INTEGRATION.join();
			
			//-------------------------------------------------------------------------  
			//integración de IS.
			this->TH_THREAD_INTEGRATION				= thread(&UPC::UPCI_I_DS::ThreadIntegrationInput, this, _input_evaluation, _output_action);
		}

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//si el hilo "ThreadIntegrationInput" no está integrando y no ha finalizado.
		else if (this->GetTHREAD_INTEGRATION_FLAG() == OFF && this->GetTHREAD_INTEGRATION_FINISHED_FLAG() == OFF)
		{
			//-------------------------------------------------------------------------
			//obtención de datos para estructura activada anterior.
			inis_id								= this->BUFF_INIS_ACTIVATED[1].STR_ID;					
			upci_id_inis							= this->BUFF_INIS_ACTIVATED[1].UPCI_ID;	

			//-------------------------------------------------------------------------
			//seteo del registro de entrada y de evaluación de entrada.
			*this->BUFF_IN_RG						= _input;
			*this->BUFF_EV_RG						= _input_evaluation;

			//-------------------------------------------------------------------------
			//activación de bandera para integrar entrada.
			this->SetNEW_INPUT_FLAG(ON);
		}		
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
//#2: método kernel de toma de control.
vo	UPCI_I_DS::KernelActionControl(dou _input, st *_output_action)
{
	//---------------------------------------------------------------------------------
	//el "KernelActionControl" entra en estado de control.
	this->SetKERNEL_CONTROL_INTEGRATION_FLAG(ON);

	//---------------------------------------------------------------------------------
	//el "KernelActionControl" sale del estado de control.
	this->SetKERNEL_CONTROL_INTEGRATION_FLAG(OFF);
	this->SetKERNEL_CONTROL_INTEGRATION_FINISHED_FLAG(ON);	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------  

//-------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------- 
//#1: método de entrada para la integración de Hilos.
vo	UPCI_I_DS::ThreadIntegrationInput(dou _input_evaluation, st *_output_action)
{
	//--------------------------------------------------------------------------------- 
	//--------------------------------------------------------------------------------- 
	//variable auxiliar para diferencia de evaluación presente.	
	dou	input_evaluation_difference			= NULL;							

	//--------------------------------------------------------------------------------- 
	//--------------------------------------------------------------------------------- 
	//variables auxiliares para estructura INIS reconocida indirectamente.
	in	upci_id_inis_ire					= NULL;											//id de la upci de la estructura INIS reconocida indirectamente.
	in	inis_id_ire						= NULL;											//id de la estructura INIS reconocida indirectamente.

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
	this->Print("> integracion THREAD tipo III iniciada.");
	this->Print("> upci id   ", this->UPCI_ID);
	this->Print("> iteracion ", this->GetTHREAD_ITERATION_COUNTER());

	//---------------------------------------------------------------------------------
	//diferenciación global de la entrada.
	this->GlobalDifferentiationINIS();
	
	//---------------------------------------------------------------------------------
	//impresión de la evaluación y transición de evaluación de entradas.
	this->Print("    > Evaluacion              ", _input_evaluation);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existe reconocimimento de una estructura INIS, entonces.
	if (this->BUFF_INIS_RE->STR_ID != -1)
	{
		//-----------------------------------------------------------------------------
		//reactivación y relacionamiento de la estructura INIS reconocida.
		this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).ReactiveINIS(this->BUFF_INIS_RE->STR_ID);
		this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).RelateINIS_CR(this->BUFF_INIS_RE->STR_ID);
		
		//-----------------------------------------------------------------------------
		//integración de Hilos por reconocimiento de INIS.
		this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).RecognizedThreadIntegrationINIS(_output_action);
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si no existe reconocimimento de una estructura INIS, entonces.
	else
	{
		//-----------------------------------------------------------------------------
		//creación de estructura de entrada.
		this->CreateINIS(*this->BUFF_IN_RG, _input_evaluation);

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
				this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_RE->UPCI_ID).ReactiveINDFRLIS(this->BUFF_INDFRLIS_RE->STR_ID);
				
				//---------------------------------------------------------------------
				//obtención de datos de la estructura INIS final de la relación.
				upci_id_inis_ire	= this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_RE->UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_RE->STR_ID].UPCI_ID_STR2_RG;
				inis_id_ire		= this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_RE->UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_RE->STR_ID].STR2_ID_RG;
				
				//---------------------------------------------------------------------
				//seteo de la estructura INIS reconocida indirectamente.
				this->BUFF_INIS_RE->Set(upci_id_inis_ire, inis_id_ire);

				//---------------------------------------------------------------------
				//reactivación de la estructura INIS reconocida indirectamente.
				this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).ReactiveINIS(this->BUFF_INIS_RE->STR_ID);

				//---------------------------------------------------------------------
				//seteo del índice de la relación INDFRLIS entrante en la estructura INIS.
				*this->BUFF_RL_INDEX_USED_IN_RECOGNITION = this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).BUFF_INIS[this->BUFF_INIS_RE->STR_ID].GetRelationIndex(INDFRLIS_TYPE,
																																											 this->BUFF_INDFRLIS_RE->STR_ID,
																																											 this->BUFF_INDFRLIS_RE->UPCI_ID);				
				
				//---------------------------------------------------------------------
				//relacionamiento de la estructura INIS reconocida indirectamente.
				this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).RelateINIS_CR(this->BUFF_INIS_RE->STR_ID);				
				
				//---------------------------------------------------------------------
				//integración de Hilos por reconocimiento indirecto de INIS.
				this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).RecognizedThreadIntegrationINIS(_output_action);
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
				upci_id_indfrlis_re	= this->BUFF_UPCI_I_DS->at(this->BUFF_INPRRLIS_RE->UPCI_ID).BUFF_INPRRLIS[this->BUFF_INPRRLIS_RE->STR_ID].UPCI_ID_STR2_RG;
				indfrlis_id_re		= this->BUFF_UPCI_I_DS->at(this->BUFF_INPRRLIS_RE->UPCI_ID).BUFF_INPRRLIS[this->BUFF_INPRRLIS_RE->STR_ID].STR2_ID_RG;
				
				//---------------------------------------------------------------------
				//seteo de la estructura INDFRLIS reconocida indirectamente.
				this->BUFF_INDFRLIS_RE->Set(upci_id_indfrlis_re, indfrlis_id_re);
				
				//---------------------------------------------------------------------
				//reactivación de la estructura INDFRLIS reconocida indirectamente.
				this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_RE->UPCI_ID).ReactiveINDFRLIS(this->BUFF_INDFRLIS_RE->STR_ID);

				//---------------------------------------------------------------------
				//obtención de datos de la estructura INIS final de la relación.
				upci_id_inis_ire	= this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_RE->UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_RE->STR_ID].UPCI_ID_STR2_RG;
				inis_id_ire		= this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_RE->UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_RE->STR_ID].STR2_ID_RG;
				
				//---------------------------------------------------------------------
				//seteo de la estructura INIS reconocida indirectamente.
				this->BUFF_INIS_RE->Set(upci_id_inis_ire, inis_id_ire);
				
				//---------------------------------------------------------------------
				//reactivación de la estructura INIS reconocida indirectamente.
				this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).ReactiveINIS(this->BUFF_INIS_RE->STR_ID);				
				
				//---------------------------------------------------------------------
				//seteo del índice de la relación INDFRLIS entrante en la estructura INIS.
				*this->BUFF_RL_INDEX_USED_IN_RECOGNITION = this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).BUFF_INIS[this->BUFF_INIS_RE->STR_ID].GetRelationIndex(INDFRLIS_TYPE,
																																											 this->BUFF_INDFRLIS_RE->STR_ID,
																																											 this->BUFF_INDFRLIS_RE->UPCI_ID);
				
				//---------------------------------------------------------------------
				//relacionamiento de la estructura INIS reconocida indirectamente.
				this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).RelateINIS_CR(this->BUFF_INIS_RE->STR_ID);

				//---------------------------------------------------------------------
				//integración de Hilos por reconocimiento indirecto de INIS.
				this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).RecognizedThreadIntegrationINIS(_output_action);
			}	

			//-------------------------------------------------------------------------
			//si no existe reconocimimento de una estructura, entonces.
			else
			{
				//---------------------------------------------------------------------
				//si la estructura de diferencia de entradas está en suspensión.
				if (this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_CRE[0].UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_CRE[0].STR_ID].AL_SRG > 0)
				{
					//-----------------------------------------------------------------
					//seteo de la diferencias de evaluaciones de entrada.
					input_evaluation_difference = this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_CRE[0].UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_CRE[0].STR_ID].EV_DIF_RG;

					//-----------------------------------------------------------------
					//impresión de la transición de evaluación de entradas.
					this->Print("    > Transion de evaluacion  ", input_evaluation_difference);
					this->Print("    > Transion de evaluacion  ", this->GetInputTransitionEvaluationTypeSt(_input_evaluation, input_evaluation_difference));

					//-----------------------------------------------------------------
					//integración de transición de evaluación de entradas.
					this->InputTransitionEvaluationIntegration(_output_action);
				}
			}
		}	

		//-----------------------------------------------------------------------------
		//si no se verifica la creación de una estructura INDFRLIS, entonces.
		else
		{			
			//-------------------------------------------------------------------------
			//integración de evaluación de entradas.
			this->InputEvaluationIntegration(_output_action);
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
//#1: método de integración de evaluación de entradas.
vo	UPCI_I_DS::InputEvaluationIntegration(st *_output_action)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para INIS activada actual.
	in current_inis_activated_id			= NULL;											//id de la estructura INIS activada actual.
	in upci_id_current_inis_activated		= NULL;											//id de la upci de la estructura INIS activada actual.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para la evaluación de la entrada actual.
	dou current_input_evaluation			= NULL;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares estructura ACIS causal.
	in	upci_id_causal_lacis				= -1;											//id de la upci de la estructura ACIS causal de INIS creado presente.						
	in	causal_lacis_id					= -1;											//id de la estructura ACIS causal de INIS creado presente.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para nuevo registro de acción.
	st	new_action_register					= "";

	//---------------------------------------------------------------------------------
	//seteo de los datos de la estructura INIS activada actual.
	current_inis_activated_id				= this->BUFF_INIS_ACTIVATED[0].STR_ID;
	upci_id_current_inis_activated		= this->BUFF_INIS_ACTIVATED[0].UPCI_ID;

	//---------------------------------------------------------------------------------
	//obtención de la evaluación de la entrada actual.
	current_input_evaluation				= this->BUFF_UPCI_I_DS->at(upci_id_current_inis_activated).BUFF_INIS[current_inis_activated_id].EV_RG;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//obtención de la estructura ACIS causal.
	this->BUFF_UPCI_I_DS->at(upci_id_current_inis_activated).GetCausalAction(current_inis_activated_id, causal_lacis_id, upci_id_causal_lacis);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura ACIS causal actual existe.
	if (upci_id_causal_lacis != -1 && causal_lacis_id != -1)
	{		
		//-----------------------------------------------------------------------------
		//reactivación y relacionamiento de la estructura ACIS actual.
		this->BUFF_UPCI_I_DS->at(upci_id_causal_lacis).ReactiveACIS(causal_lacis_id);
		this->BUFF_UPCI_I_DS->at(upci_id_causal_lacis).RelateACIS(causal_lacis_id);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la evaluación es positiva.
		if (current_input_evaluation > this->EVALUATION_THRESHOLD)
		{
			//-------------------------------------------------------------------------
			//se repite la ejecución de la acción ACIS causal.
			this->BUFF_UPCI_I_DS->at(upci_id_causal_lacis).ExecuteActionRegister(causal_lacis_id, _output_action);
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la evaluación es negativa.
		else if(current_input_evaluation < -this->EVALUATION_THRESHOLD)
		{
			//-------------------------------------------------------------------------
			//seteo de la acción a discriminar.
			this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.push_back("");

			//-------------------------------------------------------------------------
			//creación de un registro de acción aleatorio.
			new_action_register = this->CreateActionRegister();

			//-------------------------------------------------------------------------
			//integración del registro de acción creado.
			this->ActionRegisterIntegration(new_action_register, _output_action);
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura ACIS actual no existe.
	else
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la evaluación es negativa.
		if (current_input_evaluation < 0)
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si es la primera iteración del integrador de Hilo, entonces.
			if (this->GetTHREAD_ITERATION_COUNTER() == 1)
			{
				//---------------------------------------------------------------------
				//creación de un registro de acción por defecto.
				new_action_register = this->BUFF_SET_OF_SUPPORTED_ACTIONS->at(2);

				//---------------------------------------------------------------------
				//integración del registro de acción creado.
				this->ActionRegisterIntegration(new_action_register, _output_action);
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si no es la primera iteración del integrador de Hilo, entonces.
			else
			{
				//---------------------------------------------------------------------
				//seteo de la acción a discriminar.
				this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.push_back("");

				//---------------------------------------------------------------------
				//creación de un registro de acción aleatorio.
				new_action_register = this->CreateActionRegister();

				//---------------------------------------------------------------------
				//integración del registro de acción creado.
				this->ActionRegisterIntegration(new_action_register, _output_action);
			}			
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método de integración de transición de evaluación de entradas.
vo	UPCI_I_DS::InputTransitionEvaluationIntegration(st *_output_action)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para INIS activada actual.
	in current_inis_activated_id			= NULL;											//id de la estructura INIS activada actual.
	in upci_id_current_inis_activated		= NULL;											//id de la upci de la estructura INIS activada actual.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para INDFRLIS creada actual.
	in current_indfrlis_created_id			= NULL;											//id de la estructura INDFRLIS creada actual.
	in upci_id_current_indfrlis_created		= NULL;											//id de la upci de la estructura INDFRLIS creada actual.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para evaluaciones.
	dou current_input_evaluation			= NULL;											//evaluación de la entrada actual.
	dou current_input_evaluation_difference = NULL;											//diferencia de evaluaciones de entradas.
	in	evaluation_transition_type			= NULL;											//tipo de evaluación de transición de entradas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para nuevo registro de acción.
	st	new_action_register					= "";											

	//---------------------------------------------------------------------------------
	//seteo de los datos de la estructura INIS activada actual.
	current_inis_activated_id				= this->BUFF_INIS_ACTIVATED[0].STR_ID;
	upci_id_current_inis_activated		= this->BUFF_INIS_ACTIVATED[0].UPCI_ID;

	//---------------------------------------------------------------------------------
	//seteo de los datos de la estructura INIS activada actual.
	current_indfrlis_created_id				= this->BUFF_INDFRLIS_CRE[0].STR_ID;
	upci_id_current_indfrlis_created		= this->BUFF_INDFRLIS_CRE[0].UPCI_ID;

	//---------------------------------------------------------------------------------
	//obtención de la evaluación de la entrada actual.
	current_input_evaluation				= this->BUFF_UPCI_I_DS->at(upci_id_current_inis_activated).BUFF_INIS[current_inis_activated_id].EV_RG;

	//---------------------------------------------------------------------------------
	//obtención de la diferencia de evaluaciones de entradas actual.
	current_input_evaluation_difference		= this->BUFF_UPCI_I_DS->at(upci_id_current_indfrlis_created).BUFF_INDFRLIS[current_indfrlis_created_id].EV_DIF_RG;
	
	//---------------------------------------------------------------------------------
	//obtención del tipo de evaluación de transición.
	evaluation_transition_type				= this->GetInputTransitionEvaluationTypeIn(current_input_evaluation, current_input_evaluation_difference);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la transición de evaluación es positiva, entonces.
	if		(evaluation_transition_type	== POSITIVE_TRANSITION)			this->PositiveTransitionIntegration(_output_action);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la transición de evaluación es negativa, entonces.
	else if (evaluation_transition_type == NEGATIVE_TRANSITION)			this->NegativeTransitionIntegration(_output_action);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la transición de evaluación es neutral negativa, entonces.
	else if (evaluation_transition_type == NEUTRAL_NEGATIVE_TRANSITION)	this->NeutralNegativeTransitionIntegration(_output_action);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para integrar transición evaluación positiva.
vo	UPCI_I_DS::PositiveTransitionIntegration(st *_output_action)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para INIS activada actual.
	in current_inis_activated_id			= NULL;											//id de la estructura INIS activada actual.
	in upci_id_current_inis_activated		= NULL;											//id de la upci de la estructura INIS activada actual.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares estructura ACIS causal.
	in	upci_id_causal_lacis				= -1;											//id de la upci de la estructura ACIS causal de INIS creado presente.						
	in	causal_lacis_id					= -1;											//id de la estructura ACIS causal de INIS creado presente.	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para registros de acción.
	st	causal_action_register				= "";											//registro de acción causal.
	st	new_action_register					= "";											//nuevo registro de acción.

	//---------------------------------------------------------------------------------
	//seteo de los datos de la estructura INIS activada actual.
	current_inis_activated_id				= this->BUFF_INIS_ACTIVATED[0].STR_ID;
	upci_id_current_inis_activated		= this->BUFF_INIS_ACTIVATED[0].UPCI_ID;

	//---------------------------------------------------------------------------------
	//obtención de la estructura ACIS causal.
	this->BUFF_UPCI_I_DS->at(upci_id_current_inis_activated).GetCausalAction(current_inis_activated_id, causal_lacis_id, upci_id_causal_lacis);

	//---------------------------------------------------------------------------------
	//si la estructura ACIS causal actual existe.
	if (upci_id_causal_lacis != -1 && causal_lacis_id != -1)
	{
		//-----------------------------------------------------------------------------
		//reactivación y relacionamiento de la estructura ACIS actual.
		this->BUFF_UPCI_I_DS->at(upci_id_causal_lacis).ReactiveACIS(causal_lacis_id);
		this->BUFF_UPCI_I_DS->at(upci_id_causal_lacis).RelateACIS(causal_lacis_id);

		//-----------------------------------------------------------------------------
		//obtención del registro de acción causal.
		causal_action_register = this->BUFF_UPCI_I_DS->at(upci_id_causal_lacis).BUFF_ACIS[causal_lacis_id].AC_RG;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si el registro de acción no se encuentra en buffer de acciones a discriminar.
		if (this->CheckDiscrimination(causal_action_register) == OFF)
		{
			//-------------------------------------------------------------------------
			//se repite la ejecución de la acción ACIS causal.
			this->BUFF_UPCI_I_DS->at(upci_id_causal_lacis).ExecuteActionRegister(causal_lacis_id, _output_action);
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si el registro de acción se encuentra en buffer de acciones a discriminar.
		else
		{
			//-------------------------------------------------------------------------
			//creación de un registro de acción aleatorio.
			new_action_register = this->CreateActionRegister();

			//-------------------------------------------------------------------------
			//integración del registro de acción creado.
			this->ActionRegisterIntegration(new_action_register, _output_action);
		}	
	}

	//---------------------------------------------------------------------------------
	//si la estructura ACIS causal actual no existe.
	else
	{
		//-----------------------------------------------------------------------------
		//impresión.
		this->Print("    > no hay accion resultante porque no se hallo accion causal");
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para integrar transición evaluación negativa.
vo	UPCI_I_DS::NegativeTransitionIntegration(st *_output_action)
{			
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para INIS activada actual.
	in current_inis_activated_id			= NULL;											//id de la estructura INIS activada actual.
	in upci_id_current_inis_activated		= NULL;											//id de la upci de la estructura INIS activada actual.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para relación INDFRLIS entrante de INIS actual.
	in	upci_id_rl_inis					= NULL;											//id de la upci de la relación INDFRLIS entrante de la estructura INIS actual.
	in	rl_id_inis						= NULL;											//id de la relación INDFRLIS entrante de la estructura INIS actual.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura INIS creada anteriormente.
	in	upci_id_previous_inis				= NULL;											//id de la upci de la estructura INIS creada anteriormente.
	in	previous_inis_id					= NULL;											//id de la estructura INIS creada anteriormente.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares estructura ACIS causal previo.
	in	upci_id_previous_causal_lacis		= -1;											//id de la upci de la estructura ACIS causal previo.						
	in	previous_causal_lacis_id			= -1;											//id de la estructura ACIS causal previo.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares estructura ACIS causal actual.
	in	upci_id_current_causal_lacis		= -1;											//id de la upci de la estructura ACIS causal actual.						
	in	current_causal_lacis_id			= -1;											//id de la estructura ACIS causal actual.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para registros de acción de acciones causales.
	st	previous_causal_action_register		= "";											//registro de acción causal previo.
	st	current_causal_action_register		= "";											//registro de acción causal actual.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para nuevo registro de acción.
	st	new_action_register					= "";

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares estructura ACIS suspendida ganadora.
	in	upci_id_winning_sus_lacis			= -1;											//id de la upci de la estructura ACIS suspendida ganadora.						
	in	winning_sus_lacis_id				= -1;											//id de la estructura ACIS suspendida ganadora.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para índice de la última relación INDFRLIS entrante en INIS actual.
	in	indfrlis_index						= NULL;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para obtener cantidad de relaciones.
	in	rl_amount							= NULL;	

	//---------------------------------------------------------------------------------
	//seteo de los datos de la estructura INIS activada actual.
	current_inis_activated_id				= this->BUFF_INIS_ACTIVATED[0].STR_ID;
	upci_id_current_inis_activated		= this->BUFF_INIS_ACTIVATED[0].UPCI_ID;

	//---------------------------------------------------------------------------------
	//obtención del índice de la última relación INDFRLIS entrante en INIS actual.
	indfrlis_index							= this->BUFF_UPCI_I_DS->at(upci_id_current_inis_activated).BUFF_INIS[current_inis_activated_id].GetLastInputDifferentialRelationIndex();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si se encuentra el índice de la relación INDFRLIS entrante en INIS actual, entonces.
	if (indfrlis_index != -1)
	{
		//-----------------------------------------------------------------------------
		//obtención de datos de la relación diferencial de entradas de INIS actual.
		rl_id_inis							= this->BUFF_UPCI_I_DS->at(upci_id_current_inis_activated).BUFF_INIS[current_inis_activated_id].RL.at(indfrlis_index).at(1);
		upci_id_rl_inis						= this->BUFF_UPCI_I_DS->at(upci_id_current_inis_activated).BUFF_INIS[current_inis_activated_id].RL.at(indfrlis_index).at(2);
	
		//-----------------------------------------------------------------------------
		//reactivación de la relación diferencial de entrada a utilizar.
		this->BUFF_UPCI_I_DS->at(upci_id_rl_inis).ReactiveINDFRLIS(rl_id_inis);
	
		//-----------------------------------------------------------------------------
		//obtención de los datos de la estructura de inicio de la relación diferencial.
		upci_id_previous_inis					= this->BUFF_UPCI_I_DS->at(upci_id_rl_inis).BUFF_INDFRLIS[rl_id_inis].UPCI_ID_STR1_RG;
		previous_inis_id						= this->BUFF_UPCI_I_DS->at(upci_id_rl_inis).BUFF_INDFRLIS[rl_id_inis].STR1_ID_RG;
	
		//-----------------------------------------------------------------------------
		//reactivación de la estructura INIS previa.
		this->BUFF_UPCI_I_DS->at(upci_id_previous_inis).ReactiveINIS(previous_inis_id);
	
		//-----------------------------------------------------------------------------
		//obtención de la estructura ACIS causal previo.
		this->BUFF_UPCI_I_DS->at(upci_id_previous_inis).GetCausalAction(previous_inis_id, previous_causal_lacis_id, upci_id_previous_causal_lacis);	
	
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura ACIS causal previo se encontró, entonces.
		if (upci_id_previous_causal_lacis != -1 && previous_causal_lacis_id != -1)
		{
			//-------------------------------------------------------------------------
			//reactivación de la estructura ACIS causal previo.
			this->BUFF_UPCI_I_DS->at(upci_id_previous_causal_lacis).ReactiveACIS(previous_causal_lacis_id);

			//-------------------------------------------------------------------------
			//obtención del registro de acción de la acción causal previa.
			previous_causal_action_register = this->BUFF_UPCI_I_DS->at(upci_id_previous_causal_lacis).BUFF_ACIS[previous_causal_lacis_id].AC_RG;
		}
	}	
	
	//---------------------------------------------------------------------------------
	//reactivación de la estructura INIS actual.
	this->BUFF_UPCI_I_DS->at(upci_id_current_inis_activated).ReactiveINIS(current_inis_activated_id);
	
	//---------------------------------------------------------------------------------
	//obtención de la estructura ACIS causal actual.
	this->BUFF_UPCI_I_DS->at(upci_id_current_inis_activated).GetCausalAction(current_inis_activated_id, current_causal_lacis_id, upci_id_current_causal_lacis);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura ACIS causal actual se encontró, entonces.
	if (upci_id_current_causal_lacis != -1 && current_causal_lacis_id != -1)
	{
		//-----------------------------------------------------------------------------
		//reactivación y relacionamiento de la estructura ACIS causal actual.
		this->BUFF_UPCI_I_DS->at(upci_id_current_causal_lacis).ReactiveACIS(current_causal_lacis_id);
		this->BUFF_UPCI_I_DS->at(upci_id_current_causal_lacis).RelateACIS(current_causal_lacis_id);

		//-----------------------------------------------------------------------------
		//obtención del registro de acción de la acción causal actual.
		current_causal_action_register = this->BUFF_UPCI_I_DS->at(upci_id_current_causal_lacis).BUFF_ACIS[current_causal_lacis_id].AC_RG;
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura ACIS causal previo se encontró, entonces.
		if (upci_id_previous_causal_lacis != -1 && previous_causal_lacis_id != -1)
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la estructura de acción causal actual no coincide con la acción causal previa, entonces.
			if (upci_id_current_causal_lacis != upci_id_previous_causal_lacis || current_causal_lacis_id != previous_causal_lacis_id)
			{
				//---------------------------------------------------------------------
				//---------------------------------------------------------------------
				//si el registro de acción causal actual coincide con el registro acción 
				//causal previa inverso, entonces.
				if (current_causal_action_register == this->GetInverseAction(previous_causal_action_register))
				{
					//-----------------------------------------------------------------
					//reset del buffer para registros de acciones a discriminar.
					this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.clear();

					//-----------------------------------------------------------------
					//seteo de la acción a discriminar.
					this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.push_back(previous_causal_action_register);
					this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.push_back(current_causal_action_register);

					//-----------------------------------------------------------------
					//creación de un registro de acción aleatorio.
					new_action_register = this->CreateActionRegister();
					
					//-----------------------------------------------------------------
					//integración del registro de acción creado.
					this->ActionRegisterIntegration(new_action_register, _output_action);
				}

				//---------------------------------------------------------------------
				//---------------------------------------------------------------------
				//si el registro de acción causal actual no coincide con el registro acción 
				//causal previa inverso, entonces.
				else
				{
					//-----------------------------------------------------------------
					//creación de registro de acción inverso.
					new_action_register = this->GetInverseAction(current_causal_action_register);

					//-----------------------------------------------------------------
					//-----------------------------------------------------------------
					//si el registro de acción no se encuentra en buffer de acciones a discriminar.
					if (this->CheckDiscrimination(new_action_register) == OFF)
					{
						//-------------------------------------------------------------
						//integración del registro de acción creado.
						this->ActionRegisterIntegration(new_action_register, _output_action);
					}

					//-----------------------------------------------------------------
					//-----------------------------------------------------------------
					//si el registro de acción se encuentra en buffer de acciones a discriminar.
					else
					{
						//-------------------------------------------------------------
						//creación de un registro de acción aleatorio.
						new_action_register = this->CreateActionRegister();

						//-------------------------------------------------------------
						//integración del registro de acción creado.
						this->ActionRegisterIntegration(new_action_register, _output_action);
					}
				}				
			}		

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la estructura es de acción causal actual coincide con la acción causal previa, entonces.
			else
			{
				//---------------------------------------------------------------------
				//creación de registro de acción inverso.
				new_action_register = this->GetInverseAction(current_causal_action_register);

				//---------------------------------------------------------------------
				//---------------------------------------------------------------------
				//si el registro de acción no se encuentra en buffer de acciones a discriminar.
				if (this->CheckDiscrimination(new_action_register) == OFF)
				{
					//-----------------------------------------------------------------
					//integración del registro de acción creado.
					this->ActionRegisterIntegration(new_action_register, _output_action);
				}

				//---------------------------------------------------------------------
				//---------------------------------------------------------------------
				//si el registro de acción se encuentra en buffer de acciones a discriminar.
				else
				{
					//-----------------------------------------------------------------
					//creación de un registro de acción aleatorio.
					new_action_register = this->CreateActionRegister();

					//-----------------------------------------------------------------
					//integración del registro de acción creado.
					this->ActionRegisterIntegration(new_action_register, _output_action);
				}
			}
		}		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura ACIS causal previo no se encontró, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//creación de registro de acción inverso.
			new_action_register = this->GetInverseAction(current_causal_action_register);

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si el registro de acción no se encuentra en buffer de acciones a discriminar.
			if (this->CheckDiscrimination(new_action_register) == OFF)
			{
				//---------------------------------------------------------------------
				//integración del registro de acción creado.
				this->ActionRegisterIntegration(new_action_register, _output_action);
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si el registro de acción se encuentra en buffer de acciones a discriminar.
			else
			{
				//---------------------------------------------------------------------
				//creación de un registro de acción aleatorio.
				new_action_register = this->CreateActionRegister();

				//---------------------------------------------------------------------
				//integración del registro de acción creado.
				this->ActionRegisterIntegration(new_action_register, _output_action);
			}
		}
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura ACIS causal actual y previo no se encontraron, entonces.
	else if (upci_id_previous_causal_lacis == -1 && previous_causal_lacis_id == -1)
	{
		//-----------------------------------------------------------------------------
		//seteo de la acción a discriminar.
		this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.push_back("");

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existen estructuras ACIS suspendidas, entonces.
		if (this->BUFF_ACIS_SUS->size() > 0)
		{
			//-------------------------------------------------------------------------
			//obtención de la acción suspendida con la mejor evaluación.
			this->GetWinningSuspendedAction(winning_sus_lacis_id, upci_id_winning_sus_lacis);

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si se ha hallado una estructura ACIS suspendida ganadora, entonces.
			if (winning_sus_lacis_id != -1 && upci_id_winning_sus_lacis != -1)
			{
				//---------------------------------------------------------------------
				//reactivación y relacionamiento de la estructura ACIS suspendida ganadora.
				this->BUFF_UPCI_I_DS->at(upci_id_winning_sus_lacis).ReactiveACIS(winning_sus_lacis_id);
				this->BUFF_UPCI_I_DS->at(upci_id_winning_sus_lacis).RelateACIS(winning_sus_lacis_id);

				//---------------------------------------------------------------------
				//ejecución de la acción ACIS suspendida ganadora.
				this->BUFF_UPCI_I_DS->at(upci_id_winning_sus_lacis).ExecuteActionRegister(winning_sus_lacis_id, _output_action);
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si no se ha hallado una estructura ACIS suspendida ganadora, entonces.
			else
			{
				//---------------------------------------------------------------------
				//creación de un registro de acción aleatorio.
				new_action_register = this->CreateActionRegister();

				//---------------------------------------------------------------------
				//integración del registro de acción creado.
				this->ActionRegisterIntegration(new_action_register, _output_action);
			}
		}		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si no existen estructuras ACIS suspendidas, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//creación de un registro de acción aleatorio.
			new_action_register = this->CreateActionRegister();

			//-------------------------------------------------------------------------
			//integración del registro de acción.
			this->ActionRegisterIntegration(new_action_register, _output_action);
		}
	}	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si solo la estructura ACIS causal actual no se encontró, entonces.
	else
	{
		//-----------------------------------------------------------------------------
		//seteo de la acción a discriminar.
		this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.push_back(previous_causal_action_register);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existen estructuras ACIS suspendidas, entonces.
		if (this->BUFF_ACIS_SUS->size() > 1)
		{
			//-------------------------------------------------------------------------
			//obtención de la acción suspendida con la mejor evaluación.
			this->GetWinningSuspendedAction(winning_sus_lacis_id, upci_id_winning_sus_lacis);

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si se ha hallado una estructura ACIS suspendida ganadora, entonces.
			if (winning_sus_lacis_id != -1 && upci_id_winning_sus_lacis != -1)
			{
				//---------------------------------------------------------------------
				//reactivación y relacionamiento de la estructura ACIS suspendida ganadora.
				this->BUFF_UPCI_I_DS->at(upci_id_winning_sus_lacis).ReactiveACIS(winning_sus_lacis_id);
				this->BUFF_UPCI_I_DS->at(upci_id_winning_sus_lacis).RelateACIS(winning_sus_lacis_id);

				//---------------------------------------------------------------------
				//ejecución de la acción ACIS suspendida ganadora.
				this->BUFF_UPCI_I_DS->at(upci_id_winning_sus_lacis).ExecuteActionRegister(winning_sus_lacis_id, _output_action);
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si no se ha hallado una estructura ACIS suspendida ganadora, entonces.
			else
			{
				//---------------------------------------------------------------------
				//creación de un registro de acción aleatorio.
				new_action_register = this->CreateActionRegister();

				//---------------------------------------------------------------------
				//integración del registro de acción creado.
				this->ActionRegisterIntegration(new_action_register, _output_action);
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si no existen estructuras ACIS suspendidas, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//creación de un registro de acción aleatorio.
			new_action_register = this->CreateActionRegister();

			//-------------------------------------------------------------------------
			//integración del registro de acción.
			this->ActionRegisterIntegration(new_action_register, _output_action);
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para integrar transición evaluación neutral negativa.
vo	UPCI_I_DS::NeutralNegativeTransitionIntegration(st *_output_action)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para INIS activada actual.
	in current_inis_activated_id			= NULL;											//id de la estructura INIS activada actual.
	in upci_id_current_inis_activated		= NULL;											//id de la upci de la estructura INIS activada actual.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares estructura ACIS causal.
	in	upci_id_causal_lacis				= -1;											//id de la upci de la estructura ACIS causal de INIS creado presente.						
	in	causal_lacis_id					= -1;											//id de la estructura ACIS causal de INIS creado presente.	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares estructura ACIS suspendida ganadora.
	in	upci_id_winning_sus_lacis			= -1;											//id de la upci de la estructura ACIS suspendida ganadora.						
	in	winning_sus_lacis_id				= -1;											//id de la estructura ACIS suspendida ganadora.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para registros de acción.
	st	causal_action_register				= "";											//registro de acción causal.
	st	new_action_register					= "";											//nuevo registro de acción.

	//---------------------------------------------------------------------------------
	//seteo de los datos de la estructura INIS activada actual.
	current_inis_activated_id				= this->BUFF_INIS_ACTIVATED[0].STR_ID;
	upci_id_current_inis_activated		= this->BUFF_INIS_ACTIVATED[0].UPCI_ID;

	//---------------------------------------------------------------------------------
	//obtención de la estructura ACIS causal.
	this->BUFF_UPCI_I_DS->at(upci_id_current_inis_activated).GetCausalAction(current_inis_activated_id, causal_lacis_id, upci_id_causal_lacis);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura ACIS causal actual existe.
	if (upci_id_causal_lacis != -1 && causal_lacis_id != -1)
	{
		//-----------------------------------------------------------------------------
		//reactivación y relacionamiento de la estructura ACIS actual.
		this->BUFF_UPCI_I_DS->at(upci_id_causal_lacis).ReactiveACIS(causal_lacis_id);
		this->BUFF_UPCI_I_DS->at(upci_id_causal_lacis).RelateACIS(causal_lacis_id);		

		//-----------------------------------------------------------------------------
		//obtención del registro de acción de la acción causal.
		causal_action_register = this->BUFF_UPCI_I_DS->at(upci_id_causal_lacis).BUFF_ACIS[causal_lacis_id].AC_RG;

		//-----------------------------------------------------------------------------
		//seteo de la acción a discriminar.
		this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.push_back(causal_action_register);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existen estructuras ACIS suspendidas, entonces.
		if (this->BUFF_ACIS_SUS->size() > 1)
		{
			//-------------------------------------------------------------------------
			//obtención de la acción suspendida con la mejor evaluación.
			this->GetWinningSuspendedAction(winning_sus_lacis_id, upci_id_winning_sus_lacis);
			
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si se ha hallado una estructura ACIS suspendida ganadora, entonces.
			if (winning_sus_lacis_id != -1 && upci_id_winning_sus_lacis != -1)
			{
				//---------------------------------------------------------------------
				//reactivación y relacionamiento de la estructura ACIS suspendida ganadora.
				this->BUFF_UPCI_I_DS->at(upci_id_winning_sus_lacis).ReactiveACIS(winning_sus_lacis_id);
				this->BUFF_UPCI_I_DS->at(upci_id_winning_sus_lacis).RelateACIS(winning_sus_lacis_id);

				//---------------------------------------------------------------------
				//ejecución de la acción ACIS suspendida ganadora.
				this->BUFF_UPCI_I_DS->at(upci_id_winning_sus_lacis).ExecuteActionRegister(winning_sus_lacis_id, _output_action);				
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si no se ha hallado una estructura ACIS suspendida ganadora, entonces.
			else
			{
				//---------------------------------------------------------------------
				//creación de un registro de acción aleatorio.
				new_action_register = this->CreateActionRegister();

				//---------------------------------------------------------------------
				//integración del registro de acción creado.
				this->ActionRegisterIntegration(new_action_register, _output_action);
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si no existen estructuras ACIS suspendidas, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//creación de un registro de acción aleatorio.
			new_action_register = this->CreateActionRegister();

			//-------------------------------------------------------------------------
			//integración del registro de acción.
			this->ActionRegisterIntegration(new_action_register, _output_action);
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura ACIS causal actual no existe.
	else
	{
		//-----------------------------------------------------------------------------
		//seteo de la acción a discriminar.
		this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.push_back("");

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existen estructuras ACIS suspendidas, entonces.
		if (this->BUFF_ACIS_SUS->size() > 0)
		{
			//-------------------------------------------------------------------------
			//obtención de la acción suspendida con la mejor evaluación.
			this->GetWinningSuspendedAction(winning_sus_lacis_id, upci_id_winning_sus_lacis);

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si se ha hallado una estructura ACIS suspendida ganadora, entonces.
			if (winning_sus_lacis_id != -1 && upci_id_winning_sus_lacis != -1)
			{
				//---------------------------------------------------------------------
				//reactivación y relacionamiento de la estructura ACIS suspendida ganadora.
				this->BUFF_UPCI_I_DS->at(upci_id_winning_sus_lacis).ReactiveACIS(winning_sus_lacis_id);
				this->BUFF_UPCI_I_DS->at(upci_id_winning_sus_lacis).RelateACIS(winning_sus_lacis_id);

				//---------------------------------------------------------------------
				//ejecución de la acción ACIS suspendida ganadora.
				this->BUFF_UPCI_I_DS->at(upci_id_winning_sus_lacis).ExecuteActionRegister(winning_sus_lacis_id, _output_action);
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si no se ha hallado una estructura ACIS suspendida ganadora, entonces.
			else
			{
				//---------------------------------------------------------------------
				//creación de un registro de acción aleatorio.
				new_action_register = this->CreateActionRegister();

				//---------------------------------------------------------------------
				//integración del registro de acción.
				this->ActionRegisterIntegration(new_action_register, _output_action);
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si no existen estructuras ACIS suspendidas, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//creación de un registro de acción aleatorio.
			new_action_register = this->CreateActionRegister();

			//-------------------------------------------------------------------------
			//integración del registro de acción.
			this->ActionRegisterIntegration(new_action_register, _output_action);
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------- 
//#1: método para integrar registro de acción creado.
vo	UPCI_I_DS::ActionRegisterIntegration(st _action_register, st *_output_action)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para la estructura ACIS a ejecutar.
	in	upci_id_lacis_to_execute			= NULL;											//id de la upci de la estructura ACIS a ejecutar. 
	in	lacis_id_to_execute				= NULL;											//id de la estructura ACIS a ejecutar. 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la acción es nula, entonces, salir.
	if (_action_register == "") return;
		
	//---------------------------------------------------------------------------------
	//creación del registro de acción.
	*this->BUFF_AC_RG = _action_register;	

	//---------------------------------------------------------------------------------
	//impresión de la creación de una nueva acción.
	this->Print("    > se ha creado la accion ", *this->BUFF_AC_RG);

	//---------------------------------------------------------------------------------
	//diferenciación global de la acción.
	this->GlobalDifferentiationACIS();	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existe reconocimimento de una estructura ACIS, entonces.
	if (this->BUFF_ACIS_RE->STR_ID != -1 && false)
	{
		//-----------------------------------------------------------------------------
		//reactivación y relacionamiento de la estructura ACIS reconocida.
		this->BUFF_UPCI_I_DS->at(this->BUFF_ACIS_RE->UPCI_ID).ReactiveACIS(this->BUFF_ACIS_RE->STR_ID);
		this->BUFF_UPCI_I_DS->at(this->BUFF_ACIS_RE->UPCI_ID).RelateACIS(this->BUFF_ACIS_RE->STR_ID);

		//-----------------------------------------------------------------------------
		//si se ha definido el índice de la relación utiliza en reconocimiento, entonces.
		if (*this->BUFF_RL_INDEX_USED_IN_RECOGNITION != -1)
		{
			//-------------------------------------------------------------------------
			//integración de Hilos por reconocimiento de ACIS.
			this->BUFF_UPCI_I_DS->at(this->BUFF_ACIS_RE->UPCI_ID).RecognizedThreadIntegrationACIS(_output_action);
		}	

		//-----------------------------------------------------------------------------
		//si no se ha definido el índice de la relación utilizada en reconocimiento, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//obtención de datos de la estructura ACIS a ejecutar.
			upci_id_lacis_to_execute	= this->BUFF_ACIS_RE->UPCI_ID;
			lacis_id_to_execute		= this->BUFF_ACIS_RE->STR_ID;

			//-------------------------------------------------------------------------
			//ejecución de la acción.
			this->BUFF_UPCI_I_DS->at(upci_id_lacis_to_execute).ExecuteActionRegister(lacis_id_to_execute, _output_action);
		}
	}	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si no existe reconocimimento de una estructura ACIS, entonces.
	else
	{
		//-----------------------------------------------------------------------------
		//creación de la acción.
		this->CreateACIS(_action_register);

		//-----------------------------------------------------------------------------
		//obtención de datos de la estructura ACIS a ejecutar.
		upci_id_lacis_to_execute	= this->UPCI_ID;
		lacis_id_to_execute		= this->BUFF_ACIS_CRE[0].STR_ID;

		//-----------------------------------------------------------------------------
		//ejecución de la acción.
		this->BUFF_UPCI_I_DS->at(upci_id_lacis_to_execute).ExecuteActionRegister(lacis_id_to_execute, _output_action);
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------   
//#1: método para la integración de Hilos reconocidos por INIS.
vo	UPCI_I_DS::RecognizedThreadIntegrationINIS(st *_output_action)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//impresión del reconocimiento de una estructura INIS.
	this->Print("    > hay reconocimiento de una estructura INIS con id", this->BUFF_INIS_RE->STR_ID);
	//cout << "hay reconocimiento de una estructura INIS: "<< this->BUFF_INIS_RE->STR_ID << endl;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para INIS activada actual.
	in					current_inis_activated_id				= NULL;						//id de la estructura INIS activada actual.
	in					upci_id_current_inis_activated		= NULL;						//id de la upci de la estructura INIS activada actual.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura reconocida.
	in					rl_to_use_amount						= 0;						//cantidad de relaciones a utilizar de la estructura reconocida.
	in 					rl_index_to_use_aux						= 0;						//índice de la relación a utilizar de la estructura reconocida auxiliar.
	vein 				rl_index_to_use;													//índices de las relaciones a utilizar de la estructura reconocida.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para índice de la acción potencial ganadora.
	in					potential_action_index					= NULL;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura INIS activada anterior.
	in					previous_inis_id						= NULL;						//id de la estructura INIS activada anteriormente.
	in					previous_upci_id_inis					= NULL;						//id de la upci de la estructura INIS activada anteriormente.	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para evaluación del Hilo actual
	dou					current_thread_evaluation				= NULL;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliares para la acción potencial ganadora.
	in					upci_id_winning_lacis					= NULL;						//id de la upci de la acción potencial ganadora.
	in					winning_lacis_id						= NULL;						//id de la acción potencial ganadora.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para bandera de acción potencial ganadora.
	in					winning_potential_action_flag			= OFF;

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
	current_inis_activated_id				= this->BUFF_INIS_ACTIVATED[0].STR_ID;
	upci_id_current_inis_activated		= this->BUFF_INIS_ACTIVATED[0].UPCI_ID;

	//---------------------------------------------------------------------------------
	//obtención de la evaluación de Hilo actual.
	current_thread_evaluation				= this->BUFF_UPCI_I_DS->at(upci_id_current_inis_activated).BUFF_INIS[current_inis_activated_id].EV_RG;

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
			//reset del buffer para registros de acciones a discriminar.
			this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.clear();

			//-------------------------------------------------------------------------
			//obtención de los datos de la acción potencial ganadora.
			upci_id_winning_lacis			= potential_actions.at(potential_action_index).GetUPCI_ID();
			winning_lacis_id				= potential_actions.at(potential_action_index).GetSTR_ID();

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la acción potencial ganadora está definida, entonces.
			if (upci_id_winning_lacis != -1 && winning_lacis_id != -1)
			{
				//---------------------------------------------------------------------
				//se ejecuta la acción del Hilo ganador.
				this->BUFF_UPCI_I_DS->at(upci_id_winning_lacis).ExecuteActionRegister(winning_lacis_id, _output_action);
				//cout << "#accion: " << this->BUFF_UPCI_I_DS->at(upci_id_winning_lacis).BUFF_ACIS[winning_lacis_id].AC_RG << "ev: " << potential_actions.at(potential_action_index).GetEVALUATION() <<endl;
			}			
			//else cout << "#accion: nada" << "ev: "<< potential_actions.at(potential_action_index).GetEVALUATION() <<endl;
			//-------------------------------------------------------------------------
			//seteo de la bandera de acción potencial ganadora.
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
		this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).ReactiveINIS(this->BUFF_INIS_RE->STR_ID);
		
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
vo	UPCI_I_DS::RecognizedThreadIntegrationACIS(st *_output_action)
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
	BUFF_DS_STR_IITE	lacis_data;																		

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
	current_thread_evaluation				= this->BUFF_UPCI_I_DS->at(upci_id_current_inis_activated).BUFF_INIS[current_inis_activated_id].EV_RG;

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
		lacis_data.Set(this->BUFF_ACIS_RE->UPCI_ID,
					    this->BUFF_ACIS_RE->STR_ID, 
					    ACIS_TYPE, 
					    current_thread_evaluation,
					    current_thread_evaluation,
					    1);
		
		//-----------------------------------------------------------------------------
		//carga de la estructura inicial en buffer del Hilo reconocido i1.
		potential_threads.push_back(lacis_data);

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
			this->ExecuteActionRegister(this->BUFF_ACIS_RE->STR_ID, _output_action);
		}
	}		

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si no existe una relación saliente para obtener Hilo potenciales, entonces.
	else
	{
		//-----------------------------------------------------------------------------
		//ejecución de la acción.
		this->ExecuteActionRegister(this->BUFF_ACIS_RE->STR_ID, _output_action);
	}*/
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------  
//-------------------------------------------------------------------------------------   
//#1: método para obtener acciones potenciales por INIS.
vo	UPCI_I_DS::GetPotentialActionsINIS(in _inis_id, in _rl_index_to_use, BUFF_STR_IIE *_potential_action)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las relaciones de la estructura siguiente.
	in					upci_id_rl_next	= NULL;												//id de la upci de la relación de la estructura siguiente
	in					rl_next_id		= NULL;												//id de la relación de la estructura siguiente									
	in					rl_next_type	= NULL;												//tipo de relación de la estructura siguiente

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para la estructura auxiliar.
	in					upci_id_str_aux	= NULL;												//id de la upci de la estructura auxiliar.
	in					str_aux_id		= NULL;												//id de la estructura auxiliar.
	in					str_aux_type	= NULL;												//tipo de estructura auxiliar.

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
		this->BUFF_UPCI_I_DS->at(upci_id_rl_next).ReactivePFRLIS(rl_next_id);
		
		//-----------------------------------------------------------------------------
		//siguiente lectura del Hilo reconocido por medio de PFRLIS.
		this->BUFF_UPCI_I_DS->at(upci_id_rl_next).GetPotentialActionsPFRLIS(rl_next_id, _potential_action);
	}	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la relación es del tipo diferencial de entrada, entonces.
	else if (rl_next_type == INDFRLIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//obtención de datos de la relación INDFRLIS.
		upci_id_str_aux	= this->BUFF_UPCI_I_DS->at(upci_id_rl_next).BUFF_INDFRLIS[rl_next_id].UPCI_ID_STR2_RG;
		str_aux_id		= this->BUFF_UPCI_I_DS->at(upci_id_rl_next).BUFF_INDFRLIS[rl_next_id].STR2_ID_RG;
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la relación INDFRLIS no es circular, entonces.
		if (_inis_id != str_aux_id || this->UPCI_ID != upci_id_str_aux)
		{
			//-------------------------------------------------------------------------
			//reactivación de la relación diferencial de entrada a utilizar.
			this->BUFF_UPCI_I_DS->at(upci_id_rl_next).ReactiveINDFRLIS(rl_next_id);

			//-------------------------------------------------------------------------
			//siguiente lectura del Hilo reconocido por medio de INDFRLIS.
			this->BUFF_UPCI_I_DS->at(upci_id_rl_next).GetPotentialActionsINDFRLIS(rl_next_id, _potential_action);
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
//#2: método para obtener acciones potenciales por ACIS.
vo	UPCI_I_DS::GetPotentialActionsACIS(in _lacis_id, in _rl_index_to_use, BUFF_STR_IIE *_potential_action)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las relaciones de la estructura siguiente.
	in	upci_id_rl_next	= NULL;																//id de la upci de la relación de la estructura siguiente
	in	rl_next_id		= NULL;																//id de la relación de la estructura siguiente									
	in	rl_next_type	= NULL;																//tipo de relación de la estructura siguiente

	//---------------------------------------------------------------------------------
	//obtención de datos de la relación de la estructura siguiente.
	rl_next_type		= this->BUFF_ACIS[_lacis_id].RL.at(_rl_index_to_use).at(0);
	rl_next_id			= this->BUFF_ACIS[_lacis_id].RL.at(_rl_index_to_use).at(1);
	upci_id_rl_next		= this->BUFF_ACIS[_lacis_id].RL.at(_rl_index_to_use).at(2);

	//---------------------------------------------------------------------------------
	//reactivación de la relación de flujo puro a utilizar.
	this->BUFF_UPCI_I_DS->at(upci_id_rl_next).ReactivePFRLIS(rl_next_id);
	
	//---------------------------------------------------------------------------------
	//obtención de la siguiente estructura por medio de PFRLIS.
	this->BUFF_UPCI_I_DS->at(upci_id_rl_next).GetPotentialActionsPFRLIS(rl_next_id, _potential_action);
}

//-------------------------------------------------------------------------------------  
//-------------------------------------------------------------------------------------   
//#3: método para obtener acciones potenciales por PFRLIS.
vo	UPCI_I_DS::GetPotentialActionsPFRLIS(in _pfrlis_id, BUFF_STR_IIE *_potential_action)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para la estructura siguiente.
	in					upci_id_str_next			= NULL;											//id de la upci de la estructura siguiente.
	in					str_next_id					= NULL;											//id de la estructura siguiente.
	in					str_next_type				= NULL;											//tipo de estructura siguiente.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para índices de relaciones en siguiente estructura.
	in					rl_index_in_str				= NULL;											//índice de la relación entrante en estructura siguiente.
	in 					rl_index_to_use				= NULL;											//índice de la relación a utilizar en siguiente estructura.

	//---------------------------------------------------------------------------------
	//obtención de datos de la relación de flujo puro.
	upci_id_str_next	= this->BUFF_PFRLIS[_pfrlis_id].UPCI_ID_STR2_RG;
	str_next_id			= this->BUFF_PFRLIS[_pfrlis_id].STR2_ID_RG;
	str_next_type		= this->BUFF_PFRLIS[_pfrlis_id].STR2_TYPE_RG;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura siguiente es del tipo entrada, entonces.
	if (str_next_type == INIS_TYPE)
	{	
		//-----------------------------------------------------------------------------
		//reactivación de la estructura de entrada a utilizar.
		this->BUFF_UPCI_I_DS->at(upci_id_str_next).ReactiveINIS(str_next_id);

		//---------------------------------------------------------------------------------
		//seteo de la evaluación del Hilo reconocido.
		_potential_action->SetEVALUATION(this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_INIS[str_next_id].EV_RG);	
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura siguiente es del tipo acción, entonces.
	else if (str_next_type == ACIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//obtención del índice de la relación utilizada en estructura ACIS.
		rl_index_in_str			= this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_ACIS[str_next_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);

		//-----------------------------------------------------------------------------
		//obtenención del índice de la relación a utilizar en ACIS.
		rl_index_to_use			= this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_ACIS[str_next_id].GetNextOutputRelationS(rl_index_in_str);

		//-----------------------------------------------------------------------------
		//reactivación de la estructura de acción a utilizar.
		this->BUFF_UPCI_I_DS->at(upci_id_str_next).ReactiveACIS(str_next_id);

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
			this->BUFF_UPCI_I_DS->at(upci_id_str_next).GetPotentialActionsACIS(str_next_id, rl_index_to_use, _potential_action);
		}
	}
}

//-------------------------------------------------------------------------------------  
//-------------------------------------------------------------------------------------   
//#4: método para obtener acciones potenciales por INDFRLIS.
vo	UPCI_I_DS::GetPotentialActionsINDFRLIS(in _indfrlis_id, BUFF_STR_IIE *_potential_action)
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
	this->BUFF_UPCI_I_DS->at(upci_id_str_next).ReactiveINIS(str_next_id);

	//---------------------------------------------------------------------------------
	//seteo de la evaluación del Hilo reconocido.
	_potential_action->SetEVALUATION(this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_INIS[str_next_id].EV_RG);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------  
//-------------------------------------------------------------------------------------
//#1: método para obtener índice de la acción potencial ganadora.
in	UPCI_I_DS::GetWinningPotentialActionIndex(dou _input_evaluation, deBUFF_STR_IIE &_potential_actions)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para cantidad de acciones potenciales.
	in		potentital_actions_amount			= NULL;										

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para evaluación máxima de acciones potenciales.										
	dou		max_evaluation						= NULL;		

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliares para acciones potenciales.
	in		upci_id_potential_lacis			= NULL;										//id de la upci de acción potencial.
	in		potential_lacis_id					= NULL;										//id de acción potencial.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//buffer auxiliares para acciones potenciales máximos.
	vein	maximun_potential_actions;														//buffer para acciones potenciales máximas.									
	in		maximun_potential_actions_amount	= NULL;										//cantidad de acciones potenciales máximas.										

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
		//else												cout << ">>>> accion: " << this->BUFF_UPCI_I_DS->at(_potential_actions.at(i1).GetUPCI_ID()).BUFF_ACIS[_potential_actions.at(i1).GetSTR_ID()].AC_RG << endl;
		//cout << "_input_evaluation + this->TRANSITION_EVALUATION_THRESHOLD: " << _input_evaluation + this->TRANSITION_EVALUATION_THRESHOLD << endl;
		//cout << "_potential_actions.at(" << i1 << ").GetEVALUATION(): " << _potential_actions.at(i1).GetEVALUATION() << endl;		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la acción no supera la evaluación actual, entonces
		if (_potential_actions.at(i1).GetEVALUATION() < _input_evaluation + this->TRANSITION_EVALUATION_THRESHOLD)
		{
			//-------------------------------------------------------------------------
			//obtención de datos de acción potencial.
			upci_id_potential_lacis	= _potential_actions.at(i1).GetUPCI_ID();
			potential_lacis_id			= _potential_actions.at(i1).GetSTR_ID();
			
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si existe una acción potencial i1, entonces.
			if (upci_id_potential_lacis != -1 && potential_lacis_id != -1)
			{
				//---------------------------------------------------------------------
				//seteo de la acción a discriminar.
				this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.push_back(this->BUFF_UPCI_I_DS->at(upci_id_potential_lacis).BUFF_ACIS[potential_lacis_id].AC_RG);
			}			
		}

		//-----------------------------------------------------------------------------
		//si existe una nueva acción potencial máxima, entonces.
		if (_potential_actions.at(i1).GetEVALUATION() > max_evaluation)
		{
			//if (_potential_actions.at(i1).GetSTR_ID() == -1)	cout << "$$$$ accion: nada" << endl;
			//else												cout << "$$$$ accion: " << this->BUFF_UPCI_I_DS->at(_potential_actions.at(i1).GetUPCI_ID()).BUFF_ACIS[_potential_actions.at(i1).GetSTR_ID()].AC_RG << endl;;


			//-------------------------------------------------------------------------
			//limpieza del buffer para acciones potenciales máximas.
			maximun_potential_actions.clear();

			//-------------------------------------------------------------------------
			//seteo de la nueva acción potencial máxima.
			maximun_potential_actions.push_back(i1);

			//-------------------------------------------------------------------------
			//actualización de la evaluación máxima.
			max_evaluation = _potential_actions.at(i1).GetEVALUATION();
		}	

		//-----------------------------------------------------------------------------
		//si existe una nueva acción potencial máxima, entonces.
		else if (_potential_actions.at(i1).GetEVALUATION() == max_evaluation && i1 > 0)
		{
			//if (_potential_actions.at(i1).GetSTR_ID() == -1)	cout << "$$$$ accion: nada" << endl;
			//else												cout << "$$$$ accion: " << this->BUFF_UPCI_I_DS->at(_potential_actions.at(i1).GetUPCI_ID()).BUFF_ACIS[_potential_actions.at(i1).GetSTR_ID()].AC_RG << endl;

			//-------------------------------------------------------------------------
			//seteo de otra acción potencial máxima.
			maximun_potential_actions.push_back(i1);
		}
	}
	
	//---------------------------------------------------------------------------------
	//obtención de la cantidad de acciones potenciales máximas.
	maximun_potential_actions_amount = in(maximun_potential_actions.size());
	//cout << "maximun_potential_actions_amount: " << maximun_potential_actions_amount << endl;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existe una acción potencial ganadora, entonces.
	if (maximun_potential_actions_amount > 0)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para seleccionar acción definida preferentemente.
		for (in i1 = 0; i1 < maximun_potential_actions_amount; i1++)
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la acción potencial está definida, entonces.
			if (_potential_actions.at(maximun_potential_actions.at(i1)).GetUPCI_ID() != -1)
			{
				//---------------------------------------------------------------------
				//retorno del índice de la acción potencial ganadora.
				return maximun_potential_actions.at(i1);
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la acción potencial no está definida, entonces.
		return maximun_potential_actions.front();
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si no existe una acción potencial ganadora, entonces retornar índice de la acción.
	else										return -1;
}

/*//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para obtener el Hilo potencial por expansión de flujo directo por INIS.
vo UPCI_I_DS::GetPotentialThreadsINIS(in _inis_id, in _rl_index_to_use, deBUFF_STR_IITE *_potential_thread)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las relaciones de la estructura siguiente
	in					upci_id_rl_next	= NULL;												//id de la upci de la relación de la estructura siguiente
	in					rl_next_id		= NULL;												//id de la relación de la estructura siguiente									
	in					rl_next_type	= NULL;												//tipo de relación de la estructura siguiente

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para la estructura auxiliar.
	in					upci_id_str_aux	= NULL;												//id de la upci de la estructura auxiliar.
	in					str_aux_id		= NULL;												//id de la estructura auxiliar.
	in					str_aux_type	= NULL;												//tipo de estructura auxiliar.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//buffer auxiliar para cargar estructuras.
	BUFF_DS_STR_IITE	BUFF_STR_AUX;			

	//---------------------------------------------------------------------------------
	//obtención de datos de la relación de la estructura siguiente
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
		this->BUFF_UPCI_I_DS->at(upci_id_rl_next).ReactivePFRLIS(rl_next_id);

		//-----------------------------------------------------------------------------
		//carga de la estructura siguiente en buffer auxiliar.
		BUFF_STR_AUX.Set(upci_id_rl_next,
						 rl_next_id, 
						 PFRLIS_TYPE, 
						 _potential_thread->back().MAX_EV,
						 _potential_thread->back().INPUT_EVALUATION,						 
						 _potential_thread->back().POSITIVE_STATES_AMOUNT);

		//-----------------------------------------------------------------------------
		//seteo de la estructura siguiente en buffer de Hilo potencial.
		_potential_thread->push_back(BUFF_STR_AUX);

		//-----------------------------------------------------------------------------
		//obtención de la siguiente estructura por medio de PFRLIS.
		this->BUFF_UPCI_I_DS->at(upci_id_rl_next).GetPotentialThreadsPFRLIS(rl_next_id, _potential_thread);
	}	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la relación es del tipo diferencial de entrada, entonces.
	else if (rl_next_type == INDFRLIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//obtención de datos de la relación INDFRLIS.
		upci_id_str_aux	= this->BUFF_UPCI_I_DS->at(upci_id_rl_next).BUFF_INDFRLIS[rl_next_id].UPCI_ID_STR2_RG;
		str_aux_id		= this->BUFF_UPCI_I_DS->at(upci_id_rl_next).BUFF_INDFRLIS[rl_next_id].STR2_ID_RG;
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la relación INDFRLIS no es circular, entonces.
		if (_inis_id != str_aux_id || this->UPCI_ID != upci_id_str_aux)
		{
			//-------------------------------------------------------------------------
			//reactivación de la relación diferencial de entrada a utilizar.
			this->BUFF_UPCI_I_DS->at(upci_id_rl_next).ReactiveINDFRLIS(rl_next_id);

			//-------------------------------------------------------------------------
			//carga de la estructura siguiente en buffer auxiliar.
			BUFF_STR_AUX.Set(upci_id_rl_next,
							 rl_next_id, 
							 INDFRLIS_TYPE, 
							 _potential_thread->back().MAX_EV,
							 _potential_thread->back().INPUT_EVALUATION,							 
							 _potential_thread->back().POSITIVE_STATES_AMOUNT);

			//-------------------------------------------------------------------------
			//seteo de la estructura siguiente en buffer de Hilo potencial.
			_potential_thread->push_back(BUFF_STR_AUX);

			//-------------------------------------------------------------------------
			//obtención de la siguiente estructura por medio de INDFRLIS.
			this->BUFF_UPCI_I_DS->at(upci_id_rl_next).GetPotentialThreadsINDFRLIS(rl_next_id, _potential_thread);
		}		
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para obtener el Hilo potencial por expansión de flujo directo por ACIS 
vo UPCI_I_DS::GetPotentialThreadsACIS(in _lacis_id, in _rl_index_to_use, deBUFF_STR_IITE *_potential_thread)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las relaciones de la estructura siguiente
	in					upci_id_rl_next	= NULL;												//id de la upci de la relación de la estructura siguiente
	in					rl_next_id		= NULL;												//id de la relación de la estructura siguiente									
	in					rl_next_type	= NULL;												//tipo de relación de la estructura siguiente

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//buffer auxiliar para cargar estructuras.
	BUFF_DS_STR_IITE	BUFF_STR_AUX;									

	//---------------------------------------------------------------------------------
	//obtención de datos de la relación de la estructura siguiente
	rl_next_type		= this->BUFF_ACIS[_lacis_id].RL.at(_rl_index_to_use).at(0);
	rl_next_id			= this->BUFF_ACIS[_lacis_id].RL.at(_rl_index_to_use).at(1);
	upci_id_rl_next		= this->BUFF_ACIS[_lacis_id].RL.at(_rl_index_to_use).at(2);

	//---------------------------------------------------------------------------------
	//reactivación de la relación de flujo puro a utilizar.
	this->BUFF_UPCI_I_DS->at(upci_id_rl_next).ReactivePFRLIS(rl_next_id);

	//---------------------------------------------------------------------------------
	//carga de la estructura siguiente en buffer auxiliar.
	BUFF_STR_AUX.Set(upci_id_rl_next,
					 rl_next_id, 
					 PFRLIS_TYPE, 
					  _potential_thread->back().MAX_EV,
					 _potential_thread->back().INPUT_EVALUATION,					
					 _potential_thread->back().POSITIVE_STATES_AMOUNT);

	//---------------------------------------------------------------------------------
	//seteo de la estructura siguiente en buffer de Hilo potencial.
	_potential_thread->push_back(BUFF_STR_AUX);

	//---------------------------------------------------------------------------------
	//obtención de la siguiente estructura por medio de PFRLIS.
	this->BUFF_UPCI_I_DS->at(upci_id_rl_next).GetPotentialThreadsPFRLIS(rl_next_id, _potential_thread);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para obtener el Hilo potencial por expansión de flujo directo por PFRLIS.
vo UPCI_I_DS::GetPotentialThreadsPFRLIS(in _pfrlis_id, deBUFF_STR_IITE *_potential_thread)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para la estructura siguiente.
	in					upci_id_str_next			= NULL;											//id de la upci de la estructura siguiente.
	in					str_next_id					= NULL;											//id de la estructura siguiente.
	in					str_next_type				= NULL;											//tipo de estructura siguiente.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para evaluación de Hilo potencial.
	dou					max_evaluation				= NULL;											//evaluación máxima del Hilo potencial.
	dou					input_evaluation			= NULL;											//evaluación de entrada para obtener transiciones del Hilo potencial.	
	in					positive_states_amount		= NULL;											//cantidad de estados positivos (transiciones y entradas).

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para diferencia de evaluación de entradas.
	dou					input_evaluation_difference	= NULL;						

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para índices de relaciones en siguiente estructura.
	in					rl_index_in_str				= NULL;											//índice de la relación entrante en estructura siguiente.
	in 					rl_index_to_use				= NULL;											//índice de la relación a utilizar en siguiente estructura.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//buffer auxiliar para cargar estructuras.
	BUFF_DS_STR_IITE	BUFF_STR_AUX;

	//---------------------------------------------------------------------------------
	//obtención de datos de la relación de flujo puro.
	upci_id_str_next	= this->BUFF_PFRLIS[_pfrlis_id].UPCI_ID_STR2_RG;
	str_next_id			= this->BUFF_PFRLIS[_pfrlis_id].STR2_ID_RG;
	str_next_type		= this->BUFF_PFRLIS[_pfrlis_id].STR2_TYPE_RG;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura siguiente es del tipo entrada, entonces.
	if (str_next_type == INIS_TYPE)
	{	
		//-----------------------------------------------------------------------------
		//si el Hilo potencial posee una evaluación máxima inferior a INIS.
		if (_potential_thread->back().MAX_EV < this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_INIS[str_next_id].EV_RG)
		{
			//-------------------------------------------------------------------------
			//actualización de la máxima evaluación.
			max_evaluation = this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_INIS[str_next_id].EV_RG;
		}
			
		//-----------------------------------------------------------------------------
		//si el Hilo potencial posee una evaluación máxima superior a INIS.
		else
		{
			//-------------------------------------------------------------------------
			//actualización de la máxima evaluación.
			max_evaluation = _potential_thread->back().MAX_EV;
		}

		//-----------------------------------------------------------------------------
		//seteo de la evaluación de entrada.
		input_evaluation = this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_INIS[str_next_id].EV_RG;
		//cout << "INIS id: " << str_next_id << ",  con evaluacion: " << input_evaluation << endl;
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------   
		//si la evaluación de la entrada es positiva, entonces.
		if (input_evaluation > 0)
		{
			//cout << "INIS con evaluacion positiva en obtencion de Hilo potencial con id: " << str_next_id << endl;
			//-------------------------------------------------------------------------
			//seteo de la cantidad de estados positivos del Hilo potencial.
			positive_states_amount	= _potential_thread->back().POSITIVE_STATES_AMOUNT + 1;	
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la evaluación de la entrada no es positiva, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//obtención de la diferencia de las evaluaciones de entradas.
			input_evaluation_difference = input_evaluation - _potential_thread->back().INPUT_EVALUATION;

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la transición de las evaluaciones de entradas es postiva, entonces.
			if (this->GetInputTransitionEvaluationTypeIn(input_evaluation, input_evaluation_difference) == POSITIVE_TRANSITION)
			{
				//cout << "INIS con transicion positiva en obtencion de Hilo potencial con id: " << str_next_id << endl;
				//---------------------------------------------------------------------
				//seteo de la cantidad de estados positivos del Hilo potencial.
				positive_states_amount = _potential_thread->back().POSITIVE_STATES_AMOUNT + 1;
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la transición de las evaluaciones de entradas no es postiva, entonces.
			else
			{
				//---------------------------------------------------------------------
				//seteo de la cantidad de estados positivos del Hilo potencial.
				positive_states_amount = _potential_thread->back().POSITIVE_STATES_AMOUNT;
			}
		}		
		
		//-----------------------------------------------------------------------------
		//obtención del índice de la relación utilizada en estructura INIS.
		rl_index_in_str = this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_INIS[str_next_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);
		
		//-----------------------------------------------------------------------------
		//obtenención del índice de la relación a utilizar en INIS.
		rl_index_to_use = this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_INIS[str_next_id].GetNextOutputRelationS(rl_index_in_str);
		
		//-----------------------------------------------------------------------------
		//reactivación de la estructura de entrada a utilizar.
		this->BUFF_UPCI_I_DS->at(upci_id_str_next).ReactiveINIS(str_next_id);
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura siguiente es del tipo acción, entonces.
	else if (str_next_type == ACIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//seteo de la evaluación máxima del Hilo.
		max_evaluation			= _potential_thread->back().MAX_EV;

		//-----------------------------------------------------------------------------
		//seteo de la evaluación de entrada.
		input_evaluation		= _potential_thread->back().INPUT_EVALUATION;

		//-----------------------------------------------------------------------------
		//cálculo de la suma acumulada de acciones.
		positive_states_amount	= _potential_thread->back().POSITIVE_STATES_AMOUNT;

		//-----------------------------------------------------------------------------
		//obtención del índice de la relación utilizada en estructura ACIS.
		rl_index_in_str			= this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_ACIS[str_next_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);

		//-----------------------------------------------------------------------------
		//obtenención del índice de la relación a utilizar en ACIS.
		rl_index_to_use			= this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_ACIS[str_next_id].GetNextOutputRelationS(rl_index_in_str);

		//-----------------------------------------------------------------------------
		//reactivación de la estructura de acción a utilizar.
		this->BUFF_UPCI_I_DS->at(upci_id_str_next).ReactiveACIS(str_next_id);
	}		
	
	
	//---------------------------------------------------------------------------------
	//carga de la estructura siguiente en buffer auxiliar.
	BUFF_STR_AUX.Set(upci_id_str_next,
					 str_next_id, 
					 str_next_type, 					 
					 max_evaluation,
					 input_evaluation,
					 positive_states_amount);

	//---------------------------------------------------------------------------------
	//seteo de la estructura siguiente en buffer de Hilo potencial.
	_potential_thread->push_back(BUFF_STR_AUX);
		
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existe una relación a utilizar en la siguiente relación, entonces.
	if (rl_index_to_use != -1)
	{
		//-----------------------------------------------------------------------------
		//obtención de la siguiente estructura por medio de estructura según tipo.
		if		(str_next_type == INIS_TYPE)	this->BUFF_UPCI_I_DS->at(upci_id_str_next).GetPotentialThreadsINIS(str_next_id, rl_index_to_use, _potential_thread);
		else if (str_next_type == ACIS_TYPE)	this->BUFF_UPCI_I_DS->at(upci_id_str_next).GetPotentialThreadsACIS(str_next_id, rl_index_to_use, _potential_thread);
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para obtener el Hilo potencial por expansión de flujo directo por INDFRLIS.
vo UPCI_I_DS::GetPotentialThreadsINDFRLIS(in _indfrlis_id, deBUFF_STR_IITE *_potential_thread)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para la estructura siguiente.
	in					upci_id_str_next			= NULL;									//id de la upci de la estructura siguiente.
	in					str_next_id					= NULL;									//id de la estructura siguiente.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para índices de relaciones en siguiente estructura.
	in					rl_index_in_str				= NULL;									//índice de la relación entrante en estructura siguiente.
	in 					rl_index_to_use				= NULL;									//índice de la relación a utilizar en siguiente estructura.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para evaluación de Hilo potencial.	
	dou					max_evaluation				= NULL;									//evaluación máxima del Hilo potencial.
	dou					input_evaluation			= NULL;									//evaluación de entrada para obtener transiciones del Hilo potencial.
	in					positive_states_amount		= NULL;									//suma acumulativa del Hilo potencial.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para diferencia de evaluación de entradas.
	dou					input_evaluation_difference	= NULL;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//buffer auxiliar para cargar estructuras.
	BUFF_DS_STR_IITE	BUFF_STR_AUX;	

	//---------------------------------------------------------------------------------
	//obtención de datos de la relación diferencial de entrada.
	upci_id_str_next	= this->BUFF_INDFRLIS[_indfrlis_id].UPCI_ID_STR2_RG;
	str_next_id			= this->BUFF_INDFRLIS[_indfrlis_id].STR2_ID_RG;

	//---------------------------------------------------------------------------------
	//si el Hilo potencial posee una evaluación máxima inferior a INIS.
	if (_potential_thread->back().MAX_EV < this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_INIS[str_next_id].EV_RG)
	{
		//-----------------------------------------------------------------------------
		//actualización de la máxima evaluación.
		max_evaluation = this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_INIS[str_next_id].EV_RG;
	}

	//---------------------------------------------------------------------------------
	//si el Hilo potencial posee una evaluación máxima superior a INIS.
	else
	{
		//-----------------------------------------------------------------------------
		//actualización de la máxima evaluación.
		max_evaluation = _potential_thread->back().MAX_EV;
	}

	//---------------------------------------------------------------------------------
	//seteo de la evaluación de entrada.
	input_evaluation = this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_INIS[str_next_id].EV_RG;
	//cout << "INIS id: " << str_next_id << ",  con evaluacion: " << input_evaluation << endl;
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------   
	//si la evaluación de la entrada es positiva, entonces.
	if (input_evaluation > 0)
	{
		//cout << "INIS con evaluacion positiva en obtencion de Hilo potencial con id: " << str_next_id << endl;
		//-----------------------------------------------------------------------------
		//seteo de la cantidad de estados positivos del Hilo potencial.
		positive_states_amount = _potential_thread->back().POSITIVE_STATES_AMOUNT + 1;
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la evaluación de la entrada no es positiva, entonces.
	else
	{
		//-----------------------------------------------------------------------------
		//obtención de la diferencia de las evaluaciones de entradas.
		input_evaluation_difference = input_evaluation - _potential_thread->back().INPUT_EVALUATION;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la transición de las evaluaciones de entradas es postiva, entonces.
		if (this->GetInputTransitionEvaluationTypeIn(input_evaluation, input_evaluation_difference) == POSITIVE_TRANSITION)
		{
			//cout << "INIS con transicion positiva en obtencion de Hilo potencial con id: " << str_next_id << endl;
			//-------------------------------------------------------------------------
			//seteo de la cantidad de estados positivos del Hilo potencial.
			positive_states_amount = _potential_thread->back().POSITIVE_STATES_AMOUNT + 1;
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la transición de las evaluaciones de entradas no es postiva, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//seteo de la cantidad de estados positivos del Hilo potencial.
			positive_states_amount = _potential_thread->back().POSITIVE_STATES_AMOUNT;
		}				
	}

	//---------------------------------------------------------------------------------
	//obtención del índice de la relación utilizada en estructura INIS.
	rl_index_in_str = this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_INIS[str_next_id].GetRelationIndex(INDFRLIS_TYPE, _indfrlis_id, this->UPCI_ID);

	//---------------------------------------------------------------------------------
	//obtenención del índice de la relación a utilizar en INIS.
	rl_index_to_use = this->BUFF_UPCI_I_DS->at(upci_id_str_next).BUFF_INIS[str_next_id].GetNextOutputRelationS(rl_index_in_str);

	//---------------------------------------------------------------------------------
	//reactivación de la estructura de entrada a utilizar.
	this->BUFF_UPCI_I_DS->at(upci_id_str_next).ReactiveINIS(str_next_id);

	//---------------------------------------------------------------------------------
	//carga de la estructura siguiente en buffer auxiliar.
	BUFF_STR_AUX.Set(upci_id_str_next,
					 str_next_id, 
					 INIS_TYPE, 					 
					 max_evaluation,
					 input_evaluation,
					 positive_states_amount);

	//---------------------------------------------------------------------------------
	//seteo de la estructura siguiente en buffer de Hilo potencial.
	_potential_thread->push_back(BUFF_STR_AUX);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existe una relación a utilizar en la siguiente relación, entonces.
	if (rl_index_to_use != -1)
	{
		//-----------------------------------------------------------------------------
		//obtención de la siguiente estructura por medio de INIS.
		this->BUFF_UPCI_I_DS->at(upci_id_str_next).GetPotentialThreadsINIS(str_next_id, rl_index_to_use, _potential_thread);
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------  
//-------------------------------------------------------------------------------------
//#1: método para obtener Hilo ganador.
in UPCI_I_DS::GetWinningPotentialThread(dedeBUFF_STR_IITE *_potential_thread)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para cantidades.
	in		potentital_thread_amount		= in(_potential_thread->size());				//cantidad de Hilos potenciales.
	in		maximun_potential_thread_amount = NULL;											//cantidad de Hilos potenciales máximos.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//buffer auxiliares para Hilos potenciales máximos.
	vein	maximun_potential_thread;														//buffer para id de Hilos potenciales máximos según máxima evaluación.
	in		winning_potential_thread_id;													//buffer para id de Hilo potencial ganador según mínima suma acumulada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para evaluaciones.										
	dou		max_evaluation					= NULL;											//evaluación máxima de Hilo potencial.
	in		max_positive_states				= NULL;											//cantidad máxima de estados positivos de Hilo potencial.

	//---------------------------------------------------------------------------------
	//inicialización de la evaluación máxima del Hilo potencial.
	max_evaluation = _potential_thread->at(0).back().MAX_EV;

	//---------------------------------------------------------------------------------
	//inicialización del buffer para Hilo potencial máximo.
	maximun_potential_thread.push_back(0);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para hallar Hilos potenciales máximos.
	for (in i1 = 1; i1 < potentital_thread_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si existe un nuevo Hilo potencial máximos, entonces.
		if (max_evaluation < _potential_thread->at(i1).back().MAX_EV)
		{
			//-------------------------------------------------------------------------
			//limpieza del buffer para Hilos potenciales máximos.
			maximun_potential_thread.clear();

			//-------------------------------------------------------------------------
			//seteo del nuevo Hilo potencial máximo.
			maximun_potential_thread.push_back(i1);

			//-------------------------------------------------------------------------
			//actualización de la evaluación máxima del Hilo potencial.
			max_evaluation = _potential_thread->at(i1).back().MAX_EV;
		}	

		//-----------------------------------------------------------------------------
		//si existe un nuevo Hilo potencial máximos, entonces.
		else if (max_evaluation == _potential_thread->at(i1).back().MAX_EV)
		{
			//-------------------------------------------------------------------------
			//seteo del nuevo Hilo potencial máximo.
			maximun_potential_thread.push_back(i1);
		}
	}

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de Hilos potenciales máximos.
	maximun_potential_thread_amount = in(maximun_potential_thread.size());

	//--------------------------------------------------------------------------------
	//inicialización del id del Hilos potencial ganador.
	winning_potential_thread_id		= maximun_potential_thread.at(0);

	//---------------------------------------------------------------------------------
	//inicialización de máxima cantidad de estados postivos del Hilo potencial máximo.
	max_positive_states				= _potential_thread->at(maximun_potential_thread.at(0)).back().POSITIVE_STATES_AMOUNT;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para hallar Hilo potencial máximo con la máxima cantidad de estados postivos.
	for (in i1 = 1; i1 < maximun_potential_thread_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si existe una nueva máxima cantidad de estados positivos, entonces.
		if (max_positive_states < _potential_thread->at(maximun_potential_thread.at(i1)).back().POSITIVE_STATES_AMOUNT)
		{
			//-------------------------------------------------------------------------
			//seteo del nuevo Hilo potencial máximo.
			winning_potential_thread_id	= maximun_potential_thread.at(i1);

			//-------------------------------------------------------------------------
			//actualización de la máxima cantidad de estados positivos del Hilo potencial.
			max_positive_states			= _potential_thread->at(maximun_potential_thread.at(i1)).back().POSITIVE_STATES_AMOUNT;
		}	
	}

	//---------------------------------------------------------------------------------
	//retorno del id del Hilo potencial máximo ganador.
	return winning_potential_thread_id;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para integrar Hilo ganador.
vo UPCI_I_DS::winningThreadIntegration(deBUFF_STR_IITE *_winning_thread, dou _input_evaluation, st *_output_action)
{
	//--------------------------------------------------------------------------------- 
	//--------------------------------------------------------------------------------- 
	//variable auxiliares para bandera para alertar ejecución de integración de Hilos P.
	in					potential_thread_integration_flag		= OFF;						

	//--------------------------------------------------------------------------------- 
	//--------------------------------------------------------------------------------- 
	//variables auxiliares para Hilo ganador entre Hilos ganadores presente y pasado.
	in					winning_thread							= NULL;						

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para evaluación del Hilo actual.
	dou					current_thread_evaluation				= NULL;						

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para lectura de evaluaciones de Hilo ganador.
	dou					input_evaluation_rwt					= NULL;						//evaluación de entradas.
	dou					input_evaluation_difference_rwt			= NULL;						//diferencia de evaluación de entradas.
	in					evaluation_transition_type_rwt			= NULL;						//tipo de evaluación de transición de entradas.		
	in					evaluation_transition_rwt_used_flag		= ON;						//bandera de transición de evaluación utilizada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para evaluaciones de acciones ejecutadas.
	dou					input_evaluation_post_action			= NULL;						//buffer para evaluación de entradas para acciones ejecutadas.
	dou					input_evaluation_difference_post_action	= NULL;						//buffer para diferencia de evaluación de entradas para acciones ejecutadas.
	in					evaluation_transition_type_post_action	= NULL;						//tipo de evaluación de transición de entradas para acciones ejecutadas.	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para lectura de estructuras de Hilo ganador.	
	in					upci_id_str_rwt							= NULL;						//id de la upci de una estructura del Hilo ganador.
	in					str_id_rwt								= NULL;						//id de una estructura del Hilo ganador.									
	in					str_type_rwt							= NULL;						//tipo de una estructura del Hilo ganador.	

	//--------------------------------------------------------------------------------- 
	//--------------------------------------------------------------------------------- 
	//variables auxiliares para estructura INIS reconocida.
	in					upci_id_inis_re_aux					= NULL;						//id de la upci de la estructura INIS reconocida auxiliar.
	in					inis_id_re_aux						= NULL;						//id de la estructura INIS reconocida auxiliar.

	//--------------------------------------------------------------------------------- 
	//--------------------------------------------------------------------------------- 
	//variables auxiliares para estructura INIS reconocida indirectamente.
	in					upci_id_inis_ire						= NULL;						//id de la upci de la estructura INIS reconocida indirectamente.
	in					inis_id_ire							= NULL;						//id de la estructura INIS reconocida indirectamente.

	//--------------------------------------------------------------------------------- 
	//--------------------------------------------------------------------------------- 
	//variables auxiliares para estructura INDFRLIS reconocida indirectamente.
	in					upci_id_indfrlis_re						= NULL;						//id de la upci de la estructura INDFRLIS reconocida indirectamente.
	in					indfrlis_id_re							= NULL;						//id de la estructura INDFRLIS reconocida indirectamente.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para puntero de upci de estructura reconocida.
	UPCI_I_DS			*upci_ptr_str							= NULL;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliares para la cantidad de estructuras para Hilo ganador.
	in					str_amount_winning_thread				= NULL;		

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para thread de integración de Hilos ganadores.
	thread				th_thread_integration_wr;													

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de tiempo de espera para la espera de una nueva entrada.
	chrono::milliseconds timeout_loop_very_fast(TIMEOUT_LOOP_VERY_FAST);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//declaración de puntero a método de integración de Hilos potenciales.
	vo(UPC::UPCI_I_DS::*potentialThreadIntegration)(deBUFF_STR_IITE *, in *, st *);

	//---------------------------------------------------------------------------------
	//seteo de la estructura INIS reconocida auxiliar.
	upci_id_inis_re_aux		= this->BUFF_INIS_RE->UPCI_ID;
	inis_id_re_aux			= this->BUFF_INIS_RE->STR_ID;

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de estructuras del Hilo ganador.
	str_amount_winning_thread	= in(_winning_thread->size());

	//--------------------------------------------------------------------------------- 
	//seteo de la evaluación del Hilo actual
	current_thread_evaluation	= _input_evaluation;

	//---------------------------------------------------------------------------------
	//inicialización de evaluación de entrada en lectura del Hilo ganador.
	input_evaluation_rwt		= _input_evaluation;
	//cout << "str_amount_winning_thread: " << str_amount_winning_thread << endl;
	//cout << "lectura de Hilo ganador" << endl;
	//cout << "INIS id: " << inis_id_re_aux << ",  con evaluacion: " << current_thread_evaluation << endl;
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para lectura de Hilo ganador obtenido.
	for (in i1 = 2; i1 < str_amount_winning_thread; i1++)
	{
		//cout << "lectura de la estructura i1: " << i1 << endl;
		//-----------------------------------------------------------------------------
		//obtención de datos de la estructura del Hilo ganador.
		upci_id_str_rwt	= _winning_thread->at(i1).UPCI_ID;
		str_id_rwt		= _winning_thread->at(i1).STR_ID;
		str_type_rwt	= _winning_thread->at(i1).STR_TYPE;

		//-----------------------------------------------------------------------------
		//reactivación de estructura.
		if		(str_type_rwt == INIS_TYPE)	this->BUFF_UPCI_I_DS->at(upci_id_str_rwt).ReactiveINIS(str_id_rwt);
		else if (str_type_rwt == ACIS_TYPE)	this->BUFF_UPCI_I_DS->at(upci_id_str_rwt).ReactiveACIS(str_id_rwt);
		else if (str_type_rwt == PFRLIS_TYPE)	this->BUFF_UPCI_I_DS->at(upci_id_str_rwt).ReactivePFRLIS(str_id_rwt);
		else if (str_type_rwt == INDFRLIS_TYPE)	this->BUFF_UPCI_I_DS->at(upci_id_str_rwt).ReactiveINDFRLIS(str_id_rwt);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura es de entrada, entonces.
		if (str_type_rwt == INIS_TYPE)
		{
			//cout << "INIS id: " << str_id_rwt << ",  con evaluacion: " << this->BUFF_UPCI_I_DS->at(upci_id_str_rwt).BUFF_INIS[str_id_rwt].EV_RG << endl;
			//cout << "se lee INIS id: " << str_id_rwt << endl;
			//-------------------------------------------------------------------------
			//seteo de la diferencia de evaluación de entrada actual.
			input_evaluation_difference_rwt		= this->BUFF_UPCI_I_DS->at(upci_id_str_rwt).BUFF_INIS[str_id_rwt].EV_RG - input_evaluation_rwt;
			//cout << "etapa 1" << endl;
			//-------------------------------------------------------------------------
			//obtención del tipo de evaluación de transición de INIS.
			evaluation_transition_type_rwt		= this->GetInputTransitionEvaluationTypeIn(input_evaluation_rwt, input_evaluation_difference_rwt);
			//cout << "etapa 2" << endl;
			//-------------------------------------------------------------------------
			//seteo de la evaluación de entrada actual.
			input_evaluation_rwt				= this->BUFF_UPCI_I_DS->at(upci_id_str_rwt).BUFF_INIS[str_id_rwt].EV_RG;
			//cout << "etapa 3" << endl;
			//cout << "Transicion en lectura de Hilo ganador: " << this->GetInputTransitionEvaluationTypeSt(input_evaluation_rwt, input_evaluation_difference_rwt) << endl;
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la transición es positiva, entonces.
			if (evaluation_transition_type_rwt == POSITIVE_TRANSITION)
			{
				//cout << "etapa 4" << endl;
				//---------------------------------------------------------------------
				//reactivación y relacionamiento de la estructura INIS reconocida.
				this->BUFF_UPCI_I_DS->at(upci_id_inis_re_aux).ReactiveINIS(inis_id_re_aux);
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si se han contado tres estructuras INIS y la transición es positiva, entonces.
			if (evaluation_transition_rwt_used_flag		== OFF && 
				evaluation_transition_type_rwt			== POSITIVE_TRANSITION		|| 
				evaluation_transition_type_rwt			== NEUTRAL_POSITIVE_TRANSITION)
			{
				//cout << "accion: nada" << endl;
				//---------------------------------------------------------------------
				//desactivación de la bandera de integración de Hilos.
				this->SetTHREAD_INTEGRATION_FLAG(OFF);
			}						

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la estructura INIS leída es la última, entonces.
			else if ((i1 + 1) == str_amount_winning_thread)
			{
				//cout << "ultima estructura leida" << endl;

				//---------------------------------------------------------------------
				//---------------------------------------------------------------------
				//si la transición es positiva, entonces.
				if (evaluation_transition_type_rwt == POSITIVE_TRANSITION		|| 
					evaluation_transition_type_rwt == NEUTRAL_POSITIVE_TRANSITION)
				{
					//cout << "etapa 5" << endl;
					//-----------------------------------------------------------------
					//obtención de datos de la estructura del Hilo ganador.
					upci_id_str_rwt		= _winning_thread->at(i1 - 2).UPCI_ID;
					str_id_rwt			= _winning_thread->at(i1 - 2).STR_ID;
					str_type_rwt		= _winning_thread->at(i1 - 2).STR_TYPE;
					
					//-----------------------------------------------------------------
					//-----------------------------------------------------------------
					//si la estructura es del tipo acción, entonces.
					if (str_type_rwt == ACIS_TYPE)
					{
						//-------------------------------------------------------------
						//reactivación de estructura ACIS.
						this->BUFF_UPCI_I_DS->at(upci_id_str_rwt).ReactiveACIS(str_id_rwt);

						//cout << "ultima accion a ejecutar" << endl;
						//cout << "#accion: " << this->BUFF_ACIS[str_id_rwt].AC_RG << endl;
						//-------------------------------------------------------------
						//repetir acción de Hilo ganador.
						this->BUFF_UPCI_I_DS->at(upci_id_str_rwt).ExecuteActionRegister(str_id_rwt, _output_action);

						//-------------------------------------------------------------
						//desactivación de la bandera de integración de Hilos.
						this->SetTHREAD_INTEGRATION_FLAG(OFF);
					}					
				}
			}

			//-------------------------------------------------------------------------
			//desactivación de la bandera de utilización de la evaluación.
			else evaluation_transition_rwt_used_flag = OFF;
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura es de acción, entonces.
		if (str_type_rwt == ACIS_TYPE && evaluation_transition_rwt_used_flag == OFF)
		{
			//-------------------------------------------------------------------------
			//activación de la bandera de utilización de la evaluación.
			evaluation_transition_rwt_used_flag = ON;	
			//cout << "se lee ACIS id: " << str_id_rwt << endl;
			cout << "evaluation_transition_type_rwt: " << evaluation_transition_type_rwt << endl;
			cout << "input_evaluation_rwt: " << input_evaluation_rwt << endl;
			cout << "current_thread_evaluation: " << current_thread_evaluation << endl;
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la transición es positiva, entonces.
			if (evaluation_transition_type_rwt == POSITIVE_TRANSITION		|| 
				evaluation_transition_type_rwt == NEUTRAL_POSITIVE_TRANSITION)
			{
				//cout << "accion: "<<this->BUFF_ACIS[str_id_rwt].AC_RG << endl;
				//---------------------------------------------------------------------
				//repetir acción de Hilo ganador.
				this->BUFF_UPCI_I_DS->at(upci_id_str_rwt).ExecuteActionRegister(str_id_rwt, _output_action);				

				//---------------------------------------------------------------------
				//desactivación de la bandera de integración de Hilos.
				this->SetTHREAD_INTEGRATION_FLAG(OFF);				
			}
		}
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la bandera de integración de Hilos está desactivada, entonces.
		if (this->GetTHREAD_INTEGRATION_FLAG() == OFF)
		{
			//cout << "en espera por una entrada" << endl;
			//-------------------------------------------------------------------------
			//bucle de espera hasta que ingrese otra entrada.
			while (this->GetNEW_INPUT_FLAG() == OFF)	this_thread::sleep_for(timeout_loop_very_fast);
			//cout << "fin de la espera por una entrada" << endl;
			//-------------------------------------------------------------------------
			//activación de la bandera de integración de Hilos.
			this->SetTHREAD_INTEGRATION_FLAG(ON);

			//-------------------------------------------------------------------------
			//desactivación de bandera para integrar entrada.
			this->SetNEW_INPUT_FLAG(OFF);

			//-------------------------------------------------------------------------
			//diferenciación global de la entrada.
			this->GlobalDifferentiationINIS();

			//-------------------------------------------------------------------------
			//------------------------------------------------------------------------- ############## quitar false al depurar.
			//si existe reconocimimento de una estructura INIS, entonces.
			if (this->BUFF_INIS_RE->STR_ID != -1 && false)
			{
				//---------------------------------------------------------------------
				//reactivación de la estructura INIS reconocida.
				this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).ReactiveINIS(this->BUFF_INIS_RE->STR_ID);

				//---------------------------------------------------------------------
				//relacionamiento de la estructura INIS reconocida.
				this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).RelateINIS_CR(this->BUFF_INIS_RE->STR_ID);

				//---------------------------------------------------------------------
				//seteo de punteros a métodos de integración de Hilos.
				potentialThreadIntegration			= &UPC::UPCI_I_DS::RecognizedThreadIntegrationINIS;

				//---------------------------------------------------------------------
				//seteo del puntero de la upci de la estructura reconocida.
				upci_ptr_str						= &this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID);

				//---------------------------------------------------------------------
				//integración de Hilos por reconocimiento de INIS.
				th_thread_integration_wr			= thread(potentialThreadIntegration, upci_ptr_str, _winning_thread, &winning_thread, _output_action);

				//---------------------------------------------------------------------
				//activación de la bandera de alerta de ejecución de integración de Hilos potenciales.
				potential_thread_integration_flag	= ON;
			}

			//-------------------------------------------------------------------------
			//si no existe reconocimimento de una estructura INIS.
			else
			{
				//---------------------------------------------------------------------
				//creación de estructura de entrada.
				this->CreateINIS(*this->BUFF_IN_RG, *this->BUFF_EV_RG);
				//cout << "this->BUFF_INIS_ID_CRE[0]: " << this->BUFF_INIS_ID_CRE[0] << endl;
				//---------------------------------------------------------------------
				//seteo de la evaluación del Hilo actual
				current_thread_evaluation = *this->BUFF_EV_RG;
				
				//---------------------------------------------------------------------
				//---------------------------------------------------------------------
				//si se verifica la creación de una estructura INDFRLIS.
				if (this->GetNEW_INPUT_DIFFERENCE_RELATION_FLAG() == ON)
				{
					//-----------------------------------------------------------------
					//-----------------------------------------------------------------
					//si existe reconocimimento de una estructura INDFRLIS.
					if (this->BUFF_INDFRLIS_RE->STR_ID != -1)
					{
						//-------------------------------------------------------------
						//reactivación de la estructura INDFRLIS reconocida.
						this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_RE->UPCI_ID).ReactiveINDFRLIS(this->BUFF_INDFRLIS_RE->STR_ID);

						//-------------------------------------------------------------
						//obtención de datos de la estructura INIS final de la relación.
						upci_id_inis_ire	= this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_RE->UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_RE->STR_ID].UPCI_ID_STR2_RG;
						inis_id_ire		= this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_RE->UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_RE->STR_ID].STR2_ID_RG;

						//-------------------------------------------------------------
						//seteo de la estructura INIS reconocida indirectamente.
						this->BUFF_INIS_RE->Set(upci_id_inis_ire, inis_id_ire);

						//-------------------------------------------------------------
						//reactivación de la estructura INIS reconocida indirectamente.
						this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).ReactiveINIS(this->BUFF_INIS_RE->STR_ID);						

						//-------------------------------------------------------------
						//seteo del índice de la relación INDFRLIS entrante en la estructura INIS.
						*this->BUFF_RL_INDEX_USED_IN_RECOGNITION	= this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).BUFF_INIS[this->BUFF_INIS_RE->STR_ID].GetRelationIndex(INDFRLIS_TYPE,
																																																  this->BUFF_INDFRLIS_RE->STR_ID,
																																																  this->BUFF_INDFRLIS_RE->UPCI_ID);
						//-------------------------------------------------------------
						//relacionamiento de la estructura INIS reconocida indirectamente.
						this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).RelateINIS_CR(this->BUFF_INIS_RE->STR_ID);

						//-------------------------------------------------------------
						//seteo de punteros a métodos de integración de Hilos.
						potentialThreadIntegration					= &UPC::UPCI_I_DS::RecognizedThreadIntegrationINIS;

						//-------------------------------------------------------------
						//seteo del puntero de la upci de la estructura reconocida.
						upci_ptr_str								= &this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_RE->UPCI_ID);

						//-------------------------------------------------------------
						//integración de Hilos por reconocimiento de INDFRLIS.
						th_thread_integration_wr					= thread(potentialThreadIntegration, upci_ptr_str, _winning_thread, &winning_thread, _output_action);

						//-------------------------------------------------------------
						//activación de la bandera de alerta de ejecución de integración de Hilos potenciales.
						potential_thread_integration_flag			= ON;
					}

					//-----------------------------------------------------------------
					//-----------------------------------------------------------------
					//si existe reconocimimento de una estructura INPRRLIS.
					else if (this->BUFF_INPRRLIS_RE->STR_ID != -1)
					{
						//-------------------------------------------------------------
						//obtención de datos de la estructura INDFRLIS final de la relación.
						upci_id_indfrlis_re		= this->BUFF_UPCI_I_DS->at(this->BUFF_INPRRLIS_RE->UPCI_ID).BUFF_INPRRLIS[this->BUFF_INPRRLIS_RE->STR_ID].UPCI_ID_STR2_RG;
						indfrlis_id_re			= this->BUFF_UPCI_I_DS->at(this->BUFF_INPRRLIS_RE->UPCI_ID).BUFF_INPRRLIS[this->BUFF_INPRRLIS_RE->STR_ID].STR2_ID_RG;

						//-------------------------------------------------------------
						//seteo de la estructura INDFRLIS reconocida indirectamente.
						this->BUFF_INDFRLIS_RE->Set(upci_id_indfrlis_re, indfrlis_id_re);

						//-------------------------------------------------------------
						//reactivación de la estructura INDFRLIS reconocida indirectamente.
						this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_RE->UPCI_ID).ReactiveINDFRLIS(this->BUFF_INDFRLIS_RE->STR_ID);

						//-------------------------------------------------------------
						//obtención de datos de la estructura INIS final de la relación.
						upci_id_inis_ire		= this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_RE->UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_RE->STR_ID].UPCI_ID_STR2_RG;
						inis_id_ire			= this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_RE->UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_RE->STR_ID].STR2_ID_RG;

						//-------------------------------------------------------------
						//seteo de la estructura INIS reconocida indirectamente.
						this->BUFF_INIS_RE->Set(upci_id_inis_ire, inis_id_ire);

						//-------------------------------------------------------------
						//reactivación de la estructura INIS reconocida indirectamente.
						this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).ReactiveINIS(this->BUFF_INIS_RE->STR_ID);						

						//-------------------------------------------------------------
						//seteo del índice de la relación INDFRLIS entrante en la estructura INIS.
						*this->BUFF_RL_INDEX_USED_IN_RECOGNITION	= this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).BUFF_INIS[this->BUFF_INIS_RE->STR_ID].GetRelationIndex(INDFRLIS_TYPE,
																																																  this->BUFF_INDFRLIS_RE->STR_ID,
																																																  this->BUFF_INDFRLIS_RE->UPCI_ID);
						//-------------------------------------------------------------
						//relacionamiento de la estructura INIS reconocida indirectamente.
						this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_RE->UPCI_ID).RelateINIS_CR(this->BUFF_INIS_RE->STR_ID);

						//-------------------------------------------------------------
						//seteo de punteros a métodos de integración de Hilos.
						potentialThreadIntegration					= &UPC::UPCI_I_DS::RecognizedThreadIntegrationINIS;

						//-------------------------------------------------------------
						//seteo del puntero de la upci de la estructura reconocida.
						upci_ptr_str								= &this->BUFF_UPCI_I_DS->at(this->BUFF_INPRRLIS_RE->UPCI_ID);

						//-------------------------------------------------------------
						//integración de Hilos por reconocimiento de INPRRLIS.
						th_thread_integration_wr					= thread(potentialThreadIntegration, upci_ptr_str, _winning_thread, &winning_thread, _output_action);

						//-------------------------------------------------------------
						//activación de la bandera de alerta de ejecución de integración de Hilos potenciales.
						potential_thread_integration_flag			= ON;
					}
				}	
			}									

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si existe integración de Hilos potenciales, entonces.
			if (potential_thread_integration_flag == ON)
			{
				//---------------------------------------------------------------------
				//bucle de espera hasta que se obtenga la evaluación del Hilo reconocido.
				while (winning_thread == NULL)	this_thread::sleep_for(timeout_loop_very_fast);

				//---------------------------------------------------------------------
				//si el segundo Hilo reconocido es superior, entonces.
				if (winning_thread == SECOND_THREAD_HAS_WON)
				{
					//-----------------------------------------------------------------
					//espera a que el thread de integración termine.
					th_thread_integration_wr.join();

					//-----------------------------------------------------------------
					//salir del método.
					return;
				}

				//---------------------------------------------------------------------
				//espera a que el thread de integración termine.
				th_thread_integration_wr.join();
			}			

			//-------------------------------------------------------------------------
			//seteo de la evaluación de la entrada obtenida.
			input_evaluation_post_action = this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_ACTIVATED[0].UPCI_ID).BUFF_INIS[this->BUFF_INIS_ACTIVATED[0].STR_ID].EV_RG;

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si se verifica la creación de una estructura INDFRLIS.
			if (this->GetNEW_INPUT_DIFFERENCE_RELATION_FLAG() == ON)
			{			
				//cout << "input_evaluation_post_action: " << input_evaluation_post_action << endl;

				//---------------------------------------------------------------------
				//seteo de la diferencia de evaluación de la entrada obtenida.
				input_evaluation_difference_post_action	= this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_CRE[0].UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_CRE[0].STR_ID].EV_DIF_RG;

				in str1 = this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_CRE[0].UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_CRE[0].STR_ID].STR1_ID_RG;
				in str2 = this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS_CRE[0].UPCI_ID).BUFF_INDFRLIS[this->BUFF_INDFRLIS_CRE[0].STR_ID].STR2_ID_RG;

				//cout << "this->BUFF_INIS["<<str1<<"].EV_RG: " << this->BUFF_INIS[str1].EV_RG << endl;
				//cout << "this->BUFF_INIS["<<str2<<"].EV_RG: " << this->BUFF_INIS[str2].EV_RG << endl;
			
				//---------------------------------------------------------------------
				//obtención del tipo de evaluación de transición.
				evaluation_transition_type_post_action	= this->GetInputTransitionEvaluationTypeIn(input_evaluation_post_action, input_evaluation_difference_post_action);
				//cout << "input_evaluation_post_action: " << input_evaluation_post_action << endl;
				cout << "input_evaluation_difference_post_action: " << input_evaluation_difference_post_action << endl;
				cout << "evaluation_transition_type_post_action: " << evaluation_transition_type_post_action << endl;
				//cout << "transicion post accion :" << this->GetInputTransitionEvaluationTypeSt(input_evaluation_post_action, input_evaluation_difference_post_action) << endl;

				
				//---------------------------------------------------------------------
				//si el tipo de transición de evaluación no es congruente.
				if (evaluation_transition_type_post_action == NEGATIVE_TRANSITION		|| 
					evaluation_transition_type_post_action == NEUTRAL_NEGATIVE_TRANSITION)
				{
					//cout << "transicion post accion NEGATIVA" << endl;
					//-----------------------------------------------------------------
					//integración de transición de evaluación de entradas.
					this->InputTransitionEvaluationIntegration(_output_action);

					//-----------------------------------------------------------------
					//salir del método.
					return;
				}

				//---------------------------------------------------------------------
				//--------------------------------------------------------------------- ######## PROBLEMAS CON OBTENER ACIS CAUSAL DESPUÉS DE LA INTEGRACIÓN.
				//si la estructura INIS leída es la última, entonces.
				else if ((i1 + 1) == str_amount_winning_thread)
				{
					//cout << "despues de la ejecucion de la ultima accion" << endl;
					//cout << "this->BUFF_INIS_ACTIVATED[0].STR_ID: " << this->BUFF_INIS_ACTIVATED[0].STR_ID << endl;
					//cout << "Tipo de transicion: " << this->GetInputTransitionEvaluationTypeSt(input_evaluation_post_action, input_evaluation_difference_post_action) << endl;
					//-----------------------------------------------------------------
					//integración de transición de evaluación de entradas.
					this->InputTransitionEvaluationIntegration(_output_action);
				}		
				//cout << "la accion resulto ser positiva" << endl;
			}			

			//-------------------------------------------------------------------------
			//si no se verifica la creación de una estructura INDFRLIS, entonces.
			else
			{
				//---------------------------------------------------------------------
				//integración de evaluación de entradas.
				this->InputEvaluationIntegration(_output_action);
			}
		}
	}

	//cout << "fin de lectura del Hilo ganador" << endl;
}*/

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para obtener estructura ACIS causal de una entrada.
vo	UPCI_I_DS::GetCausalAction(in _inis_id, in & _causal_lacis_id, in &_upci_id_causal_lacis)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las relaciones de _inis_id.
	in	upci_id_rl					= NULL;													//id de la upci de la relación de _inis_id.
	in	rl_type						= NULL;													//tipo de relación de _inis_id.
	in	rl_id						= NULL;													//id de la relación de _inis_id.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para el tipo de estructura de inicio de la relación PFRLIS.
	in  rl_str1_type				= NULL;													

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para la estructura ACIS causal.
	in	upci_id_causal_lacis_aux	= NULL;													//id auxiliar de la upci de la estructura ACIS causal. 
	in	causal_lacis_id_aux		= NULL;													//id auxiliar de la estructura ACIS causal. 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para cantidad de relaciones.
	in rl_amount					= NULL;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//contador de relaciones INDFRLIS.
	in indfrlis_counter			= 0;

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de relaciones de _inis_id.
	rl_amount		= this->BUFF_INIS[_inis_id].GetRelationAmount();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para hallar la estructura ACIS causal por medio de _inis_id.
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
			this->BUFF_UPCI_I_DS->at(upci_id_rl).ReactivePFRLIS(rl_id);

			//-------------------------------------------------------------------------
			//obtención del tipo de estructura de inicio de la relación.
			rl_str1_type = this->BUFF_UPCI_I_DS->at(upci_id_rl).BUFF_PFRLIS[rl_id].STR1_TYPE_RG;
			
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la estructura es del tipo acción.
			if (rl_str1_type == ACIS_TYPE)
			{
				//---------------------------------------------------------------------
				//obtención de los datos de la estructura ACIS causal.
				upci_id_causal_lacis_aux	= this->BUFF_UPCI_I_DS->at(upci_id_rl).BUFF_PFRLIS[rl_id].UPCI_ID_STR1_RG;;
				causal_lacis_id_aux		= this->BUFF_UPCI_I_DS->at(upci_id_rl).BUFF_PFRLIS[rl_id].STR1_ID_RG;

				//---------------------------------------------------------------------
				//si la estructura ACIS causal está suspendida.
				if (this->BUFF_UPCI_I_DS->at(upci_id_causal_lacis_aux).BUFF_ACIS[causal_lacis_id_aux].AL_SRG > 0)
				{
					//-----------------------------------------------------------------
					//seteo de los datos de la estructura ACIS causal.
					_upci_id_causal_lacis	= upci_id_causal_lacis_aux;
					_causal_lacis_id		= causal_lacis_id_aux;

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
vo	UPCI_I_DS::GetWinningSuspendedAction(in &_winning_sus_lacis_id, in &_upci_id_winning_sus_lacis)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la bandera para utilizar reactivación acción suspendida con máxima asociación 
	//positiva está desactivada, entonces.
	if (this->GetSUSPENDED_ACTIONS_MAXIMIZATION_FLAG() == OFF)	return;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las estructuras ACIS suspendidas.
	in				upci_id_sus_lacis				= NULL;									//id de la upci de estructura ACIS suspendida.
	in				sus_lacis_id					= NULL;									//id de la estructura ACIS suspendida.
	dou				sus_lacis_evaluation			= 0;									//evaluación de la estructura ACIS suspendida.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura ACIS ganadora.
	in				upci_id_winning_sus_lacis		= NULL;									//id de la upci de estructura ACIS suspendida con máxima evaluación.
	in				winning_sus_lacis_id			= NULL;									//id de la estructura ACIS suspendida con máxima evaluación.
	dou				winning_sus_lacis_evaluation	= 0;									//evaluación de la estructura ACIS suspendida con máxima evaluación.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para la cantidad de estructuras ACIS suspendidas.
	in				lacis_suspended_amount			= NULL;									//cantidad de estructuras ACIS suspendidas del buffer original.
	in				lacis_suspended_amount_aux		= NULL;									//cantidad de estructuras ACIS suspendidas del buffer auxiliar.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliares para cantidades registros de acción.
	in				ac_rg_to_discriminate_amount	= NULL;									//cantidad de registros de acción a discriminar.
	in				admissible_action_amount		= NULL;									//cantidad de registros admisibles.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliares para bandera de acción admisible.
	in				admissible_action_flag			= NULL;											

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliares para buffer auxiliar de Set de acciones.
	deBUFF_STR_II	buff_lacis_sus_aux;

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de estructuras ACIS suspendidas del buffer original.
	lacis_suspended_amount					= in(this->BUFF_ACIS_SUS->size());
	
	//---------------------------------------------------------------------------------
	//obtención de la cantidad de registros de acciones a discriminar.
	ac_rg_to_discriminate_amount			= in(this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.size());

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de acciones admisibles.
	admissible_action_amount				= *this->BUFF_SUPPORTED_ACTIONS_AMOUNT - ac_rg_to_discriminate_amount;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para elminar estructuras acción a discriminar de buffer auxiliar.
	for (in i1 = 0; i1 < lacis_suspended_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//reset de la bandera de acción admisible.
		admissible_action_flag = ON;

		//-----------------------------------------------------------------------------
		//obtención de datos de estructura ACIS suspendida.
		upci_id_sus_lacis		= this->BUFF_ACIS_SUS->at(i1).UPCI_ID;
		sus_lacis_id			= this->BUFF_ACIS_SUS->at(i1).STR_ID;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para comparar con buffer de registros de acción discriminados.
		for (in i2 = 0; i2 < ac_rg_to_discriminate_amount; i2++)
		{
			//-------------------------------------------------------------------------
			//si la acción suspendida posee un registro a discriminar, entonces.
			if (this->BUFF_UPCI_I_DS->at(upci_id_sus_lacis).BUFF_ACIS[sus_lacis_id].AC_RG == this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.at(i2)) admissible_action_flag = OFF;
		}

		//-----------------------------------------------------------------------------
		//si la acción suspendida no posee un registro a discriminar, entonces.
		if (admissible_action_flag == ON)	buff_lacis_sus_aux.push_back(this->BUFF_ACIS_SUS->at(i1));
	}	

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de estructuras ACIS suspendidas del buffer auxiliar.
	lacis_suspended_amount_aux = in(buff_lacis_sus_aux.size());

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existen estructuras de acción suspendidas candidatas, entonces.
	if (lacis_suspended_amount_aux > 0)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//inicialización del la estructura de acción suspendida ganadora.
		upci_id_winning_sus_lacis		= buff_lacis_sus_aux.at(0).UPCI_ID;
		winning_sus_lacis_id			= buff_lacis_sus_aux.at(0).STR_ID;
		winning_sus_lacis_evaluation	= this->BUFF_UPCI_I_DS->at(upci_id_winning_sus_lacis).GetActionEvaluation(winning_sus_lacis_id);		
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para hallar la estructura ACIS con mejor evaluación.
		for (in i1 = 1; i1 < lacis_suspended_amount_aux; i1++)
		{
			//-------------------------------------------------------------------------
			//obtención de datos de estructura ACIS suspendida.
			upci_id_sus_lacis		= buff_lacis_sus_aux.at(i1).UPCI_ID;
			sus_lacis_id			= buff_lacis_sus_aux.at(i1).STR_ID;
			sus_lacis_evaluation	= this->BUFF_UPCI_I_DS->at(upci_id_sus_lacis).GetActionEvaluation(sus_lacis_id);

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la evaluación de la estructura ACIS suspendida i1 es superior. 
			if (sus_lacis_evaluation > winning_sus_lacis_evaluation)
			{
				//---------------------------------------------------------------------
				//reset de la estructura ACIS ganadora.
				upci_id_winning_sus_lacis		= upci_id_sus_lacis;
				winning_sus_lacis_id			= sus_lacis_id;
				winning_sus_lacis_evaluation	= sus_lacis_evaluation;
			}
		}
	
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la evaluación ganadora es mayor que el umbral de transición, entonces.
		if (winning_sus_lacis_evaluation > this->TRANSITION_EVALUATION_THRESHOLD)
		{
			//-------------------------------------------------------------------------
			//seteo de la estructura ACIS ganadora.
			_winning_sus_lacis_id		= winning_sus_lacis_id;
			_upci_id_winning_sus_lacis = upci_id_winning_sus_lacis;
			//cout << "#accion ganadora: " << this->BUFF_UPCI_I_DS->at(upci_id_winning_sus_lacis).BUFF_ACIS[winning_sus_lacis_id].AC_RG << endl;
		}	
	}	

	//---------------------------------------------------------------------------------
	//reset del buffer para registros de acciones a discriminar.
	this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.clear();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para obtener la evaluación una estructura ACIS en función de sus relaciones.
dou UPCI_I_DS::GetActionEvaluation(in _lacis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las relaciones de _lacis_id.
	in	upci_id_rl_lacis			= NULL;													//id de la upci de la relación de _lacis_id.
	in	rl_id_lacis				= NULL;													//id de la relación de _lacis_id.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para estructura final de una relación PFRLIS saliente.
	in	upci_id_str2_pfrlis			= NULL;													//id de la upci de una estructura final de la relación PFRLIS saliente.
	in	str2_id_pfrlis				= NULL;													//id de una estructura final de la relación PFRLIS saliente.
	in	str2_type_pfrlis			= NULL;													//tipo de estructura final de la relación PFRLIS saliente.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las relaciones de la estructura de entrada hallada.
	in	upci_id_rl_inis			= NULL;													//id de la upci de la relación de la estructura de entrada hallada.
	in  rl_type_inis				= NULL;													//tipo de relación de la estructura de entrada hallada.
	in	rl_id_inis				= NULL;													//id de la relación de la estructura de entrada hallada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para índice de relación a utilizar.
	in rl_index_lacis				= NULL;													//índice de relación para _lacis_id.
	in rl_index_inis				= NULL;													//índice de relación para inis hallada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para evaluaciones de entradas.
	dou	input_evaluation			= NULL;													//buffer para evaluación de entradas.
	dou	input_evaluation_difference	= NULL;													//buffer para diferencia de evaluación de entradas.
	in	evaluation_transition_type	= NULL;													//tipo de evaluación de transición de entradas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para evaluación de la estructura _lacis_id.
	dou lacis_evaluation			= 0;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliar para cantidad de relaciones.
	in rl_amount					= NULL;

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de relaciones de la estructura _lacis_id.
	rl_amount						= this->BUFF_ACIS[_lacis_id].GetRelationAmount();

	//---------------------------------------------------------------------------------
	//inicialización del índice de relación de _lacis_id.
	rl_index_lacis					= rl_amount - 1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para hallar estructuras INIS para obtener evaluaciones de _lacis_id.
	while (true)
	{
		//-----------------------------------------------------------------------------
		//obtención del índice de una relación saliente previa.
		rl_index_lacis		= this->BUFF_ACIS[_lacis_id].GetPreviousOutputRelationS(rl_index_lacis);
		
		//-----------------------------------------------------------------------------
		//si ya no existen más relaciones salientes, entonces retornar evaluación.
		if(rl_index_lacis == -1)	return lacis_evaluation;

		//-----------------------------------------------------------------------------
		//obtención de datos de la relación de _lacis_id.
		rl_id_lacis		= this->BUFF_ACIS[_lacis_id].RL.at(rl_index_lacis).at(1);
		upci_id_rl_lacis	= this->BUFF_ACIS[_lacis_id].RL.at(rl_index_lacis).at(2);

		//-----------------------------------------------------------------------------
		//reactivación de la relación de flujo puro a utilizar.
		this->BUFF_UPCI_I_DS->at(upci_id_rl_lacis).ReactivePFRLIS(rl_id_lacis);

		//-----------------------------------------------------------------------------
		//obtención del tipo de estructura final de la relación PFRLIS.
		str2_type_pfrlis	= this->BUFF_UPCI_I_DS->at(upci_id_rl_lacis).BUFF_PFRLIS[rl_id_lacis].STR2_TYPE_RG;
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura final es el tipo entrada, entonces.
		if (str2_type_pfrlis == INIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//obtención de los datos faltantes de la estructura de entrada.
			upci_id_str2_pfrlis = this->BUFF_UPCI_I_DS->at(upci_id_rl_lacis).BUFF_PFRLIS[rl_id_lacis].UPCI_ID_STR2_RG;
			str2_id_pfrlis		= this->BUFF_UPCI_I_DS->at(upci_id_rl_lacis).BUFF_PFRLIS[rl_id_lacis].STR2_ID_RG;

			//-------------------------------------------------------------------------
			//obtención del índice de la relación entrante PFRLIS en INIS hallada.
			rl_index_inis		= this->BUFF_UPCI_I_DS->at(upci_id_str2_pfrlis).BUFF_INIS[str2_id_pfrlis].GetRelationIndex(PFRLIS_TYPE, rl_id_lacis, upci_id_rl_lacis);
			
			//-------------------------------------------------------------------------
			//obtención de los datos de la relación de la estructura INIS hallada.
			rl_type_inis		= this->BUFF_UPCI_I_DS->at(upci_id_str2_pfrlis).BUFF_INIS[str2_id_pfrlis].RL.at(rl_index_inis + 1).at(0);
			rl_id_inis		= this->BUFF_UPCI_I_DS->at(upci_id_str2_pfrlis).BUFF_INIS[str2_id_pfrlis].RL.at(rl_index_inis + 1).at(1);
			upci_id_rl_inis	= this->BUFF_UPCI_I_DS->at(upci_id_str2_pfrlis).BUFF_INIS[str2_id_pfrlis].RL.at(rl_index_inis + 1).at(2);
			
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la relación hallada en la estructura de entrada es del tipo INDFRLIS, entonces.
			if (rl_type_inis == -INDFRLIS_TYPE)
			{
				//---------------------------------------------------------------------
				//obtención de la evaluación de la entrada.
				input_evaluation			= this->BUFF_UPCI_I_DS->at(upci_id_str2_pfrlis).BUFF_INIS[str2_id_pfrlis].EV_RG;

				//---------------------------------------------------------------------
				//obtención de la diferencia de las evaluaciones de entradas.
				input_evaluation_difference = this->BUFF_UPCI_I_DS->at(upci_id_rl_inis).BUFF_INDFRLIS[rl_id_inis].EV_DIF_RG;

				//---------------------------------------------------------------------
				//obtención del tipo de transición de entradas.
				evaluation_transition_type	= this->GetInputTransitionEvaluationTypeIn(input_evaluation, input_evaluation_difference);

				//---------------------------------------------------------------------
				//si la evaluación es negativa o neutral negativa, entonces.
				//if (evaluation_transition_type == NEGATIVE_TRANSITION || evaluation_transition_type == NEUTRAL_NEGATIVE_TRANSITION)	return -1;

				//---------------------------------------------------------------------
				//si la evaluación es postiva o neutral positiva, entonces.
				lacis_evaluation += input_evaluation_difference;
			}
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para crear un registro de acción aleatorio.
st  UPCI_I_DS::CreateActionRegister()
{	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliares para registros de acción.
	in		action_register_index				= NULL;										//índice para el registro de acción.
	st		action_register_aux					= "";										//registro de acción auxiliar.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliares para cantidades registros de acción.
	in		ac_rg_to_discriminate_amount		= NULL;										//cantidad de registros de acción a discriminar.
	in		admissible_action_amount			= NULL;										//cantidad de registros admisibles.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliares para banderas registros de acción.
	in		admissible_action_flag				= NULL;										//bandera de acción admisible.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variable auxiliares para buffer auxiliar de Set de acciones.
	dest	buff_set_of_supported_actions_aux;	

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de registros de acciones a discriminar.
	ac_rg_to_discriminate_amount				= in(this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.size());

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para elminar registros de acciones a discriminar de buffer auxiliar.
	for (in i1 = 0; i1 < *this->BUFF_SUPPORTED_ACTIONS_AMOUNT; i1++)
	{
		//----------------------------------------------------------------------------- 
		//reset de la bandera de acción admisible.
		admissible_action_flag = ON;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para comparar con buffer de registros de acción discriminados.
		for (in i2 = 0; i2 < ac_rg_to_discriminate_amount; i2++)
		{
			//-------------------------------------------------------------------------
			//si el registro de acción pertenece a un registro a discriminar, entonces.
			if (this->BUFF_SET_OF_SUPPORTED_ACTIONS->at(i1) == this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.at(i2)) admissible_action_flag = OFF;
		}		

		//-----------------------------------------------------------------------------
		//si el registro de acción no pertenece a un registro a discriminar, entonces.
		if (admissible_action_flag == ON)	buff_set_of_supported_actions_aux.push_back(this->BUFF_SET_OF_SUPPORTED_ACTIONS->at(i1));
	}

	//---------------------------------------------------------------------------------
	//reset del buffer para registros de acciones a discriminar.
	this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.clear();

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de acciones admisibles.
	admissible_action_amount = in(buff_set_of_supported_actions_aux.size());
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si no existen acciones admisibles, entonces.
	if (admissible_action_amount == 0) return "";

	//---------------------------------------------------------------------------------
	//configuración para valores aleatorios.
	srand(this->SEED + this->GetTHREAD_ITERATION_COUNTER());

	//---------------------------------------------------------------------------------
	//obtencion de un número aleatorio.
	action_register_index	= rand() % admissible_action_amount;
	
	//---------------------------------------------------------------------------------
	//seteo de la acción aleatoria.
	action_register_aux		= buff_set_of_supported_actions_aux.at(action_register_index);
	
	//---------------------------------------------------------------------------------
	//retorno de la acción aleatoria.
	return action_register_aux;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método para checkear si un registro de acción existe en el buffer de registros 
//de acciones a discriminar.
in  UPCI_I_DS::CheckDiscrimination(st _action_register)
{
	//---------------------------------------------------------------------------------
	//cantidad de acciones a discriminar.
	in actions_to_discriminate_amount = in(this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.size());

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para verificar si un registro de acción debe discrminarse.
	for (in i1 = 0; i1 < actions_to_discriminate_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si el registro de acción se encuentra en buffer de registros de acciones
		//discriminadas, entonces.
		if (_action_register == this->BUFF_ACTION_REGISTERS_TO_DISCRIMINATE.at(i1))	return ON;
	}

	//---------------------------------------------------------------------------------
	//el registro de acción no se halló en buffer de registros de acciones discriminadas
	return OFF;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#6: método para repetir la ejecución de una estructura de acción.
vo	UPCI_I_DS::ExecuteActionRegister(in _lacis_id, st *_output_action)
{
	//---------------------------------------------------------------------------------
	//ejecutar acción.
	*_output_action = this->BUFF_ACIS[_lacis_id].AC_RG;

	//---------------------------------------------------------------------------------
	//actualización de buffer de estructuras de acción ejecutadas.
	this->BUFF_EXECUTE_ACIS[1] = this->BUFF_EXECUTE_ACIS[0];
	this->BUFF_EXECUTE_ACIS[0].Set(this->UPCI_ID, _lacis_id);

	//---------------------------------------------------------------------------------
	//impresión de la acción efectuada.
	this->Print("    > se ejecuta lacis id   ", _lacis_id);
	this->Print("    > con la accion          ", *_output_action);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para crear estructura entrada INIS.
vo	UPCI_I_DS::CreateINIS(dou _input, dou _input_evaluation)
{	
	//---------------------------------------------------------------------------------
	//bloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.lock();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares
	in	created_id	= this->BUFF_INIS_ID_AV[0];											//id de estructura creado.
	dou	al_srg		= this->ActivityLevelFunction(_input_evaluation);						//nivel de actividad.

	//---------------------------------------------------------------------------------
	//creación de la estructura.
	this->BUFF_INIS[created_id].create(_input, _input_evaluation, al_srg);

	//---------------------------------------------------------------------------------
	//actualización de buffers después de la creación de la estructura INIS.
	this->UpdateBuffersAfterCreatingINIS(created_id, _input_evaluation, al_srg);
	
	//---------------------------------------------------------------------------------
	//relacionamiento de la estructura INIS creada.
	this->RelateINIS_CR(created_id);

	//---------------------------------------------------------------------------------
	//desbloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.unlock();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para crear estructura entrada ACIS.
vo	UPCI_I_DS::CreateACIS(st _ac_rg)
{
	//---------------------------------------------------------------------------------
	//bloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.lock();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	in	created_id	= this->BUFF_ACIS_ID_AV[0];											//id de estructura creado.
	dou	al_srg		= this->DEFAULT_ACTIVITY_LEVEL;											//nivel de actividad.

	//---------------------------------------------------------------------------------
	//creación de la estructura ACIS.
	this->BUFF_ACIS[created_id].create(_ac_rg, al_srg);

	//---------------------------------------------------------------------------------
	//actualización después de la creación de la estructura ACIS.
	this->UpdateBuffersAfterCreatingACIS(created_id, al_srg);

	//---------------------------------------------------------------------------------
	//relacionamiento de la estructura ACIS creada.
	this->RelateACIS(created_id);

	//---------------------------------------------------------------------------------
	//desbloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.unlock();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para crear estructura de relación PFRLIS.
vo	UPCI_I_DS::CreatePFRLIS(in _str1_type, in _str2_type, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2)
{
	//---------------------------------------------------------------------------------
	//si existe una misma relación anterior, entonces salir.
	if (this->CheckPreviousPFRLIS(_str1_type, _str2_type, _str1_id, _str2_id, _upci_id_str1, _upci_id_str2) == ON) return;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	UPCI_I_DS	*upci_ptr1		= &this->BUFF_UPCI_I_DS->at(_upci_id_str1);					//puntero a upci de la estructura 1.
	UPCI_I_DS	*upci_ptr2		= &this->BUFF_UPCI_I_DS->at(_upci_id_str2);					//puntero a upci de la estructura 2.
	in			created_id		= this->BUFF_PFRLIS_ID_AV[0];								//id de estructura creado.
	dou			rs_srg			= 1;														//fuerza de relación inicial.
	dou			al_srg			= NULL;														//nivel de actividad para la relación pfrlis.
	dou			al_srg_str1		= NULL;														//nivel de actividad de la estructura 1.
	dou			al_srg_str2		= NULL;														//nivel de actividad de la estructura 2.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del nivel de actividad de la primera estructura.
	if		(_str1_type == INIS_TYPE)		al_srg_str1 = upci_ptr1->BUFF_INIS[_str1_id].AL_SRG;
	else if (_str1_type == ACIS_TYPE)		al_srg_str1 = upci_ptr1->BUFF_ACIS[_str1_id].AL_SRG;
	else if (_str1_type == INDFRLIS_TYPE)	al_srg_str1 = upci_ptr1->BUFF_INDFRLIS[_str1_id].AL_SRG;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del nivel de actividad de la segunda estructura.
	if		(_str2_type == INIS_TYPE)		al_srg_str2 = upci_ptr2->BUFF_INIS[_str2_id].AL_SRG;
	else if (_str2_type == ACIS_TYPE)		al_srg_str2 = upci_ptr2->BUFF_ACIS[_str2_id].AL_SRG;
	else if (_str2_type == INDFRLIS_TYPE)	al_srg_str2 = upci_ptr2->BUFF_INDFRLIS[_str2_id].AL_SRG;
	
	//---------------------------------------------------------------------------------
	//seteo del nivel de actividad.
	if (al_srg_str1 >= al_srg_str2)	al_srg = al_srg_str1;
	else							al_srg = al_srg_str2;
	
	//---------------------------------------------------------------------------------
	//creación de la estructura relación.
	this->BUFF_PFRLIS[created_id].create(_str1_type, _str2_type, _str1_id, _str2_id, _upci_id_str1, _upci_id_str2, rs_srg, al_srg);
	
	//---------------------------------------------------------------------------------
	//actualización después de la creación de la estructura PFRLIS.
	this->UpdateBuffersAfterCreatingPFRLIS(created_id);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de la relación creada en la primera estructura relacionada.
	if		(_str1_type == INIS_TYPE)		upci_ptr1->BUFF_INIS[_str1_id].createRelation(PFRLIS_TYPE, Created_id, this->UPCI_ID);
	else if (_str1_type == ACIS_TYPE)		upci_ptr1->BUFF_ACIS[_str1_id].createRelation(PFRLIS_TYPE, Created_id, this->UPCI_ID);
	else if (_str1_type == INDFRLIS_TYPE)	upci_ptr1->BUFF_INDFRLIS[_str1_id].createRelation(PFRLIS_TYPE, Created_id, this->UPCI_ID);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de la relación creada en la segunda estructura relacionada.
	if		(_str2_type == INIS_TYPE)		upci_ptr2->BUFF_INIS[_str2_id].createRelation(-PFRLIS_TYPE, Created_id, this->UPCI_ID);
	else if (_str2_type == ACIS_TYPE)		upci_ptr2->BUFF_ACIS[_str2_id].createRelation(-PFRLIS_TYPE, Created_id, this->UPCI_ID);
	else if (_str2_type == INDFRLIS_TYPE)	upci_ptr2->BUFF_INDFRLIS[_str2_id].createRelation(-PFRLIS_TYPE, Created_id, this->UPCI_ID);
	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para crear estructura de relación INDFRLIS.
vo	UPCI_I_DS::CreateINDFRLIS(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2)
{
	//---------------------------------------------------------------------------------
	//si existe una misma relación anterior, entonces salir.
	if (this->CheckPreviousINDFRLIS(_str1_id, _str2_id, _upci_id_str1, _upci_id_str2) == ON) return;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	UPCI_I_DS	*upci_ptr1				= &this->BUFF_UPCI_I_DS->at(_upci_id_str1);			//puntero a upci de la estructura 1.
	UPCI_I_DS	*upci_ptr2				= &this->BUFF_UPCI_I_DS->at(_upci_id_str2);			//puntero a upci de la estructura 2.
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
	else																					al_srg = upci_ptr2->BUFF_INIS[_str2_id].AL_SRG;

	//---------------------------------------------------------------------------------
	//seteo del registro de diferencia de entradas.
	*this->BUFF_IN_DIF_RG	= difference_inputs;

	//---------------------------------------------------------------------------------
	//diferenciación global de la estructura INDFRLIS.
	this->GlobalDifferentiationINDFRLIS();
	
	//---------------------------------------------------------------------------------
	//creación de la estructura relación.
	this->BUFF_INDFRLIS[created_id].create(difference_inputs, diff_input_evaluations, _str1_id, _str2_id, _upci_id_str1, _upci_id_str2, rs_srg, al_srg);
	
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
		upci_ptr1->BUFF_INIS[_str1_id].createRelation(INDFRLIS_TYPE, Created_id, this->UPCI_ID);
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la primera y segunda estructura INIS no son las mismas, entonces.
	else
	{
		//-----------------------------------------------------------------------------
		//seteo de la relación creada en las estructuras relacionadas.
		upci_ptr1->BUFF_INIS[_str1_id].createRelation(INDFRLIS_TYPE, Created_id, this->UPCI_ID);
		upci_ptr2->BUFF_INIS[_str2_id].createRelation(-INDFRLIS_TYPE, Created_id, this->UPCI_ID);
	}	

	

	//---------------------------------------------------------------------------------
	//seteo de la bandera de alerta de la creación de INDFRLIS.
	this->SetNEW_INPUT_DIFFERENCE_RELATION_FLAG(ON);
	
	//---------------------------------------------------------------------------------
	//relacionamiento de la estructura INDFRLIS creada.
	this->RelateINDFRLIS(created_id);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método para crear estructura de relación INPRRLIS.
vo	UPCI_I_DS::CreateINPRRLIS(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2)
{
	//---------------------------------------------------------------------------------
	//si existe una misma relación anterior, entonces salir.
	if (this->CheckPreviousINPRRLIS(_str1_id, _str2_id, _upci_id_str1, _upci_id_str2) == ON) return;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	UPCI_I_DS	*upci_ptr1			= &this->BUFF_UPCI_I_DS->at(_upci_id_str1);				//puntero a upci de la estructura 1.
	UPCI_I_DS	*upci_ptr2			= &this->BUFF_UPCI_I_DS->at(_upci_id_str2);				//puntero a upci de la estructura 2.
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
	this->BUFF_INPRRLIS[created_id].create(proportion_inputs, _str1_id, _str2_id, _upci_id_str1, _upci_id_str2);

	//---------------------------------------------------------------------------------
	//actualización después de la creación de la estructura INPRRLIS.
	this->UpdateBuffersAfterCreatingINPRRLIS(created_id);

	//---------------------------------------------------------------------------------
	//seteo de la relación creada en las estructuras relacionadas.
	upci_ptr1->BUFF_INDFRLIS[_str1_id].createRelation(INPRRLIS_TYPE, Created_id, this->UPCI_ID);
	upci_ptr2->BUFF_INDFRLIS[_str2_id].createRelation(-INPRRLIS_TYPE, Created_id, this->UPCI_ID);	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para Delete estructura INIS.
vo	UPCI_I_DS::DeleteINIS(in _inis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	in			rl_type			=	NULL;													//tipo de relación.
	in			rl_id			=	NULL;													//id de la relación.
	UPCI_I_DS	*upci_ptr_rl	=	NULL;													//puntero de la upci de la relación.
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
		upci_ptr_rl		= &this->BUFF_UPCI_I_DS->at(this->BUFF_INIS[_inis_id].RL.at(i1).at(2));
		
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
//#2: método para Delete estructura ACIS.
vo	UPCI_I_DS::DeleteACIS(in _lacis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	in			rl_type			=	NULL;													//tipo de relación.
	in			rl_id			=	NULL;													//id de la relación.
	UPCI_I_DS	*upci_ptr_rl	=	NULL;													//puntero de la upci de la relación.
	in			rl_amount		=	NULL;													//cantidad de relaciones.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//actualización de buffers para la eliminación de la IS.
	this->UpdateBuffersToDeleteACIS(_lacis_id);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//obtención de la cantidad de relaciones de _lacis_id.
	rl_amount	= this->BUFF_ACIS[_lacis_id].GetRelationAmount();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para Delete estructuras de relación de la estructura de entrada _lacis_id.
	for (in i1 = 0; i1 < rl_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención de los datos de la relación de la estructura _lacis_id.
		rl_type			= abs(this->BUFF_ACIS[_lacis_id].RL.at(i1).at(0));
		rl_id			= this->BUFF_ACIS[_lacis_id].RL.at(i1).at(1);
		upci_ptr_rl		= &this->BUFF_UPCI_I_DS->at(this->BUFF_ACIS[_lacis_id].RL.at(i1).at(2));
		
		//-----------------------------------------------------------------------------
		//eliminación de la estructura PFRLIS.
		upci_ptr_rl->DeletePFRLIS(rl_id, ACIS_TYPE, _lacis_id, this->UPCI_ID);
	}
		
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//eliminación de la estrucura _lacis_id.
	this->BUFF_ACIS[_lacis_id].Clean();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para Delete estructura PFRLIS.
vo	UPCI_I_DS::DeletePFRLIS(in _pfrlis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las estructuras relacionadas.
	UPCI_I_DS	*upci_ptr_str1		=	NULL;												//puntero de la upci de la estructura relacionada 1.
	UPCI_I_DS	*upci_ptr_str2		=	NULL;												//puntero de la upci de la estructura relacionada 2.
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
	upci_ptr_str1	= &this->BUFF_UPCI_I_DS->at(this->BUFF_PFRLIS[_pfrlis_id].UPCI_ID_STR1_RG);
	upci_ptr_str2	= &this->BUFF_UPCI_I_DS->at(this->BUFF_PFRLIS[_pfrlis_id].UPCI_ID_STR2_RG);
	
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
			upci_ptr_str1->BUFF_INIS[str1_id].deleteRelation(rl_index_in_str);
			
			//-------------------------------------------------------------------------
			//si str1_id queda sin relaciones se elimina.
			if (upci_ptr_str1->BUFF_INIS[str1_id].GetRelationAmount() == 0)	upci_ptr_str1->DeleteINIS(str1_id);
			
			//-------------------------------------------------------------------------
			//salida.
			break;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//para estructura de acción.
		case ACIS_TYPE:
			
			//-------------------------------------------------------------------------
			//obtención del índice de la relación en la estructura ACIS.
			rl_index_in_str = upci_ptr_str1->BUFF_ACIS[str1_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);
			
			//-------------------------------------------------------------------------
			//eliminación de la relación en str1_id.
			upci_ptr_str1->BUFF_ACIS[str1_id].deleteRelation(rl_index_in_str);
			
			//-------------------------------------------------------------------------
			//si str1_id queda sin relaciones se elimina.
			if (upci_ptr_str1->BUFF_ACIS[str1_id].GetRelationAmount() == 0)	upci_ptr_str1->DeleteACIS(str1_id);
			
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
			upci_ptr_str1->BUFF_INDFRLIS[str1_id].deleteRelation(rl_index_in_str);
			
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
			upci_ptr_str2->BUFF_INIS[str2_id].deleteRelation(rl_index_in_str);
			
			//-------------------------------------------------------------------------
			//si str2_id queda sin relaciones se elimina.
			if (upci_ptr_str2->BUFF_INIS[str2_id].GetRelationAmount() == 0)	upci_ptr_str2->DeleteINIS(str2_id);
			
			//-------------------------------------------------------------------------
			//salida.
			break;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//para estructura de acción.
		case ACIS_TYPE:
			
			//-------------------------------------------------------------------------
			//obtención del índice de la relación en la estructura ACIS.
			rl_index_in_str = upci_ptr_str2->BUFF_ACIS[str2_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);
			
			//-------------------------------------------------------------------------
			//eliminación de la relación en str2_id.
			upci_ptr_str2->BUFF_ACIS[str2_id].deleteRelation(rl_index_in_str);
			
			//-------------------------------------------------------------------------
			//si str2_id queda sin relaciones se elimina.
			if (upci_ptr_str2->BUFF_ACIS[str2_id].GetRelationAmount() == 0)	upci_ptr_str2->DeleteACIS(str2_id);
			
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
			upci_ptr_str2->BUFF_INDFRLIS[str2_id].deleteRelation(rl_index_in_str);
			
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
//#4: método para Delete estructura INDFRLIS.
vo	UPCI_I_DS::DeleteINDFRLIS(in _indfrlis_id)	
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las estructuras relacionadas.
	UPCI_I_DS	*upci_ptr_str1		=	NULL;												//puntero de la upci de la estructura relacionada 1.
	UPCI_I_DS	*upci_ptr_str2		=	NULL;												//puntero de la upci de la estructura relacionada 2.
	in			str1_id				=	NULL;												//id de la estructura relacionada 1.
	in			str2_id				=	NULL;												//id de la estructura relacionada 2.											
	in			rl_index_in_str		=	NULL;												//índice de la relación en una estructura.
	              
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares de la relación _indfrlis_id.
	in			rl_type				=	NULL;												//tipo de las relaciones de la relación _indfrlis_id.
	in			rl_id				=	NULL;												//id de las relaciones de la relación _indfrlis_id.
	UPCI_I_DS	*upci_ptr_rl		=	NULL;												//puntero de la upci de la relación _indfrlis_id.

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
	upci_ptr_str1	= &this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS[_indfrlis_id].UPCI_ID_STR1_RG);
	upci_ptr_str2	= &this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS[_indfrlis_id].UPCI_ID_STR2_RG);

	//---------------------------------------------------------------------------------
	//obtención del índice de la relación en la estructura INIS.
	rl_index_in_str = upci_ptr_str1->BUFF_INIS[str1_id].GetRelationIndex(INDFRLIS_TYPE, _indfrlis_id, this->UPCI_ID);

	//---------------------------------------------------------------------------------
	//eliminación de la relación en str1_id.
	upci_ptr_str1->BUFF_INIS[str1_id].deleteRelation(rl_index_in_str);

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
		upci_ptr_str2->BUFF_INIS[str2_id].deleteRelation(rl_index_in_str);

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
		upci_ptr_rl = &this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS[_indfrlis_id].RL.at(i1).at(2));

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
//#5: método para Delete estructura INPRRLIS.
vo	UPCI_I_DS::DeleteINPRRLIS(in _inprrlis_id)	
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las estructuras relacionadas.
	UPCI_I_DS	*upci_ptr_str1		=	NULL;												//puntero de la upci de la estructura relacionada 1.
	UPCI_I_DS	*upci_ptr_str2		=	NULL;												//puntero de la upci de la estructura relacionada 2.
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
	upci_ptr_str1	= &this->BUFF_UPCI_I_DS->at(this->BUFF_INPRRLIS[_inprrlis_id].UPCI_ID_STR1_RG);
	upci_ptr_str2	= &this->BUFF_UPCI_I_DS->at(this->BUFF_INPRRLIS[_inprrlis_id].UPCI_ID_STR2_RG);

	//---------------------------------------------------------------------------------
	//obtención del índice de la relación en la estructura INDFRLIS.
	rl_index_in_str = upci_ptr_str1->BUFF_INDFRLIS[str1_id].GetRelationIndex(INPRRLIS_TYPE, _inprrlis_id, this->UPCI_ID);

	//---------------------------------------------------------------------------------
	//eliminación de la relación en str1_id.
	upci_ptr_str1->BUFF_INDFRLIS[str1_id].deleteRelation(rl_index_in_str);

	//---------------------------------------------------------------------------------
	//obtención del índice de la relación en la estructura INDFRLIS.
	rl_index_in_str = upci_ptr_str2->BUFF_INDFRLIS[str2_id].GetRelationIndex(INPRRLIS_TYPE, _inprrlis_id, this->UPCI_ID);

	//---------------------------------------------------------------------------------
	//eliminación de la relación en str2_id.
	upci_ptr_str2->BUFF_INDFRLIS[str2_id].deleteRelation(rl_index_in_str);

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
vo	UPCI_I_DS::DeletePFRLIS(in _pfrlis_id, in _str_type, in _str_id, in _upci_id_str)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las estructuras relacionadas.
	UPCI_I_DS	*upci_ptr_str1		=	NULL;												//puntero de la upci de la estructura relacionada 1.
	UPCI_I_DS	*upci_ptr_str2		=	NULL;												//puntero de la upci de la estructura relacionada 2.
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
	upci_ptr_str1	= &this->BUFF_UPCI_I_DS->at(this->BUFF_PFRLIS[_pfrlis_id].UPCI_ID_STR1_RG);
	upci_ptr_str2	= &this->BUFF_UPCI_I_DS->at(this->BUFF_PFRLIS[_pfrlis_id].UPCI_ID_STR2_RG);
	
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
				upci_ptr_str1->BUFF_INIS[str1_id].deleteRelation(rl_index_in_str);

				//---------------------------------------------------------------------
				//si str1_id queda sin relaciones se elimina.
				if (upci_ptr_str1->BUFF_INIS[str1_id].GetRelationAmount() == 0)	upci_ptr_str1->DeleteINIS(str1_id);

				//---------------------------------------------------------------------
				//salida.
				break;

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//para estructura de acción.
			case ACIS_TYPE:

				//---------------------------------------------------------------------
				//obtención del índice de la relación en la estructura ACIS.
				rl_index_in_str = upci_ptr_str1->BUFF_ACIS[str1_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);

				//---------------------------------------------------------------------
				//eliminación de la relación en str1_id.
				upci_ptr_str1->BUFF_ACIS[str1_id].deleteRelation(rl_index_in_str);

				//---------------------------------------------------------------------
				//si str1_id queda sin relaciones se elimina.
				if (upci_ptr_str1->BUFF_ACIS[str1_id].GetRelationAmount() == 0) upci_ptr_str1->DeleteACIS(str1_id);

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
				upci_ptr_str1->BUFF_INDFRLIS[str1_id].deleteRelation(rl_index_in_str);

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
				upci_ptr_str2->BUFF_INIS[str2_id].deleteRelation(rl_index_in_str);

				//---------------------------------------------------------------------
				//si str2_id queda sin relaciones se elimina.
				if (upci_ptr_str2->BUFF_INIS[str2_id].GetRelationAmount() == 0) upci_ptr_str2->DeleteINIS(str2_id);

				//---------------------------------------------------------------------
				//salida.
				break;

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//para estructura de acción.
			case ACIS_TYPE:

				//---------------------------------------------------------------------
				//obtención del índice de la relación en la estructura ACIS.
				rl_index_in_str = upci_ptr_str2->BUFF_ACIS[str2_id].GetRelationIndex(PFRLIS_TYPE, _pfrlis_id, this->UPCI_ID);

				//---------------------------------------------------------------------
				//eliminación de la relación en str2_id.
				upci_ptr_str2->BUFF_ACIS[str2_id].deleteRelation(rl_index_in_str);

				//---------------------------------------------------------------------
				//si str2_id queda sin relaciones se elimina.
				if (upci_ptr_str2->BUFF_ACIS[str2_id].GetRelationAmount() == 0) upci_ptr_str2->DeleteACIS(str2_id);

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
				upci_ptr_str2->BUFF_INDFRLIS[str2_id].deleteRelation(rl_index_in_str);

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
vo	UPCI_I_DS::DeleteINDFRLIS(in _indfrlis_id, in _str_id, in _upci_id_str)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las estructuras relacionadas.
	UPCI_I_DS	*upci_ptr_str1		=	NULL;												//puntero de la upci de la estructura relacionada 1.
	UPCI_I_DS	*upci_ptr_str2		=	NULL;												//puntero de la upci de la estructura relacionada 2.
	in			str1_id				=	NULL;												//id de la estructura relacionada 1.
	in			str2_id				=	NULL;												//id de la estructura relacionada 2.	
	in			rl_index_in_str		=	NULL;												//índice de la relación en una estructura.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares de la relación _indfrlis_id.
	in			rl_type				=	NULL;												//tipo de las relaciones de la relación _indfrlis_id.
	in			rl_id				=	NULL;												//id de las relaciones de la relación _indfrlis_id.
	UPCI_I_DS	*upci_ptr_rl		=	NULL;												//puntero de la upci de la relación _indfrlis_id.

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
	upci_ptr_str1	= &this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS[_indfrlis_id].UPCI_ID_STR1_RG);
	upci_ptr_str2	= &this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS[_indfrlis_id].UPCI_ID_STR2_RG);
	
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
			upci_ptr_str1->BUFF_INIS[str1_id].deleteRelation(rl_index_in_str);

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
			upci_ptr_str2->BUFF_INIS[str2_id].deleteRelation(rl_index_in_str);

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
		upci_ptr_rl = &this->BUFF_UPCI_I_DS->at(this->BUFF_INDFRLIS[_indfrlis_id].RL.at(i1).at(2));
		
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
vo	UPCI_I_DS::DeleteINPRRLIS(in _inprrlis_id, in _str_id, in _upci_id_str)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para las estructuras relacionadas.
	UPCI_I_DS	*upci_ptr_str1		=	NULL;												//puntero de la upci de la estructura relacionada 1.
	UPCI_I_DS	*upci_ptr_str2		=	NULL;												//puntero de la upci de la estructura relacionada 2.
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
	upci_ptr_str1	= &this->BUFF_UPCI_I_DS->at(this->BUFF_INPRRLIS[_inprrlis_id].UPCI_ID_STR1_RG);
	upci_ptr_str2	= &this->BUFF_UPCI_I_DS->at(this->BUFF_INPRRLIS[_inprrlis_id].UPCI_ID_STR2_RG);

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
		upci_ptr_str1->BUFF_INDFRLIS[str1_id].deleteRelation(rl_index_in_str);
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
		upci_ptr_str2->BUFF_INDFRLIS[str2_id].deleteRelation(rl_index_in_str);
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
//#1: método thread para limpiar buffer de IS.
vo	UPCI_I_DS::CleanISBuffers()
{
	//---------------------------------------------------------------------------------
	//seteo de tiempos de espera de los bucles.
	chrono::milliseconds timeout_clean_is(this->TIMEOUT_CLEAN_IS);
	chrono::milliseconds timeout_loop_fast(TIMEOUT_LOOP_FAST);

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
		IS[0] = thread(&UPC::UPCI_I_DS::CleanPFRLIS, this);
		IS[1] = thread(&UPC::UPCI_I_DS::CleanINDFRLIS, this);
		IS[2] = thread(&UPC::UPCI_I_DS::CleanActivityLevelIS, this);

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
		this->BUFF_INIS_CRE[0].Clean();													//buffer para INIS creada actual.
		this->BUFF_INIS_CRE[1].Clean();													//buffer para INIS creada anterior.
		this->BUFF_ACIS_CRE[0].Clean();													//buffer para ACIS creada actual.
		this->BUFF_ACIS_CRE[1].Clean();													//buffer para ACIS creada anterior.
		this->BUFF_PFRLIS_CRE[0].Clean();													//buffer para PFRLIS creada actual.
		this->BUFF_PFRLIS_CRE[1].Clean();													//buffer para PFRLIS creada anterior.
		this->BUFF_INDFRLIS_CRE[0].Clean();													//buffer para INDFRLIS creada actual.
		this->BUFF_INDFRLIS_CRE[1].Clean();													//buffer para INDFRLIS creada anterior.
		this->BUFF_INPRRLIS_CRE[0].Clean();													//buffer para INPRRLIS creada actual.
		this->BUFF_INPRRLIS_CRE[1].Clean();													//buffer para INPRRLIS creada anterior.

		//-----------------------------------------------------------------------------
		//limpieza de los buffers para los ids y tipos del flujo de estructuras activadas.
		this->BUFF_STR_ACTIVATED[0].Clean();												//buffer presente.
		this->BUFF_STR_ACTIVATED[1].Clean();												//buffer pasado.

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
vo	UPCI_I_DS::CleanPFRLIS()
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
vo	UPCI_I_DS::CleanINDFRLIS()
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
vo	UPCI_I_DS::RelateINIS_CR(in _inis_id)
{	
	//---------------------------------------------------------------------------------
	//reset de la bandera de alerta de la creación de INDFRLIS.
	this->SetNEW_INPUT_DIFFERENCE_RELATION_FLAG(OFF);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura activada anterior está definida y en suspensión.
	if (this->GetPastStrActiveStatus() == ON)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura activada anterior corresponde a INIS, entonces.
		if (this->BUFF_STR_ACTIVATED[1].STR_TYPE ==	INIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//creación de relación de flujo diferencial de entradas.
			this->CreateINDFRLIS(this->BUFF_STR_ACTIVATED[1].STR_ID, _inis_id, this->BUFF_STR_ACTIVATED[1].UPCI_ID, this->UPCI_ID);
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura activada anterior no corresponde a INIS, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//si la estructura activada anterior corresponde a ACIS, entonces.
			if (this->BUFF_STR_ACTIVATED[1].STR_TYPE == ACIS_TYPE)
			{				
				//---------------------------------------------------------------------
				//creación de la relación del tipo flujo puro.
				this->CreatePFRLIS(ACIS_TYPE, INIS_TYPE, this->BUFF_STR_ACTIVATED[1].STR_ID, _inis_id, this->BUFF_STR_ACTIVATED[1].UPCI_ID, this->UPCI_ID);
			}
			
			//-------------------------------------------------------------------------
			//si la estructura INIS activada anterior está definida, entonces.
			if (this->BUFF_INIS_ACTIVATED[1].STR_ID != -1)
			{
				//---------------------------------------------------------------------
				//si la estructura INIS anterior está suspendida.
				if (this->BUFF_UPCI_I_DS->at(this->BUFF_INIS_ACTIVATED[1].UPCI_ID).BUFF_INIS[this->BUFF_INIS_ACTIVATED[1].STR_ID].AL_SRG > 0)
				{
					//-----------------------------------------------------------------
					//creación de relación de flujo diferencial de entradas.
					this->CreateINDFRLIS(this->BUFF_INIS_ACTIVATED[1].STR_ID, _inis_id, this->BUFF_INIS_ACTIVATED[1].UPCI_ID, this->UPCI_ID);
				}				
			}								
		}	
	}
}

//------------------------------------------------------------------------------------- 
//-------------------------------------------------------------------------------------  
//#2: método para relacionar estructura INIS reactivada en flujo.
vo	UPCI_I_DS::RelateINIS_F(in _inis_id)
{
	//---------------------------------------------------------------------------------
	//reset de la bandera de alerta de la creación de INDFRLIS.
	this->SetNEW_INPUT_DIFFERENCE_RELATION_FLAG(OFF);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura activada anterior está definida y en suspensión.
	if (this->GetPastStrActiveStatus() == ON)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura activada anterior corresponde a INIS, entonces.
		if (this->BUFF_STR_ACTIVATED[1].STR_TYPE ==	INIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//creación de relación de flujo diferencial de entradas.
			this->CreateINDFRLIS(this->BUFF_STR_ACTIVATED[1].STR_ID, _inis_id, this->BUFF_STR_ACTIVATED[1].UPCI_ID, this->UPCI_ID);
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura activada anterior corresponde a ACIS, entonces.
		else
		{
			//-------------------------------------------------------------------------
			//creación de la relación del tipo flujo puro.
			this->CreatePFRLIS(ACIS_TYPE, INIS_TYPE, this->BUFF_STR_ACTIVATED[1].STR_ID, _inis_id, this->BUFF_STR_ACTIVATED[1].UPCI_ID, this->UPCI_ID);
		}
	}
}

//------------------------------------------------------------------------------------- 
//------------------------------------------------------------------------------------- 
//#3: método para relacionar estructura ACIS creada o reactivada.
vo	UPCI_I_DS::RelateACIS(in _lacis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura activada anterior está definida y en suspensión.
	if (this->GetPastStrActiveStatus() == ON)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura activada anterior corresponde a ACIS, entonces.
		if (this->BUFF_STR_ACTIVATED[1].STR_TYPE ==	ACIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//creación de la relación del tipo flujo puro.
			this->CreatePFRLIS(ACIS_TYPE, ACIS_TYPE, this->BUFF_STR_ACTIVATED[1].STR_ID, _lacis_id, this->BUFF_STR_ACTIVATED[1].UPCI_ID, this->UPCI_ID);
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura activada anterior corresponde a INIS, entonces.
		else if (this->BUFF_STR_ACTIVATED[1].STR_TYPE == INIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//creación de la relación del tipo flujo puro.
			this->CreatePFRLIS(INIS_TYPE, ACIS_TYPE, this->BUFF_STR_ACTIVATED[1].STR_ID, _lacis_id, this->BUFF_STR_ACTIVATED[1].UPCI_ID, this->UPCI_ID);
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------  
//#4: método para relacionar estructura INDFRLIS creada.
vo	UPCI_I_DS::RelateINDFRLIS(in _indfrlis_id)
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
	rl_amount = this->BUFF_UPCI_I_DS->at(upci_id_str1).BUFF_INIS[str1_id].GetRelationAmount();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para hallar una relación INDFRLIS en la estructura INIS str1_id.
	for (in i1 = 0; i1 < rl_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si se encuentra una relación diferencial de entrada entrante, entonces.
		if (this->BUFF_UPCI_I_DS->at(upci_id_str1).BUFF_INIS[str1_id].RL.at(rl_amount - (i1 + 1)).at(0) == -INDFRLIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//id de la relación INDFRLIS hallada.
			indfrlis_id_found		= this->BUFF_UPCI_I_DS->at(upci_id_str1).BUFF_INIS[str1_id].RL.at(rl_amount - (i1 + 1)).at(1);

			//-------------------------------------------------------------------------
			//seteo del id de la upci de la relación INDFRLIS hallada.
			upci_id_indfrlis_found	= this->BUFF_UPCI_I_DS->at(upci_id_str1).BUFF_INIS[str1_id].RL.at(rl_amount - (i1 + 1)).at(2);

			//-------------------------------------------------------------------------
			//si el inicio es distinto de str2_id, entonces crear relación.
			if (str2_id != this->BUFF_UPCI_I_DS->at(upci_id_indfrlis_found).BUFF_INDFRLIS[indfrlis_id_found].STR1_ID_RG)
			{
				//---------------------------------------------------------------------
				//si los dos registros son diferentes de '0', entonces relacionar.
				if (this->BUFF_UPCI_I_DS->at(upci_id_indfrlis_found).BUFF_INDFRLIS[indfrlis_id_found].IN_DIF_RG != 0 &&
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
in	UPCI_I_DS::CheckPreviousPFRLIS(in _str1_type, in _str2_type, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	UPCI_I_DS	*upci_ptr_str1		=	&this->BUFF_UPCI_I_DS->at(_upci_id_str1);			//puntero de la upci de la estructura relacionada 1.				
	in			rl_type_str1		=	NULL;												//tipo de relación de la estructura relacionada 1.
	in			rl_id_str1			=	NULL;												//id de la relación de la estructura relacionada 1.	
	UPCI_I_DS	*upci_ptr_rl_str1	=	NULL;												//puntero de la upci de la relación de la estructura relacionada 1. 
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
				upci_ptr_rl_str1	= &this->BUFF_UPCI_I_DS->at(upci_ptr_str1->BUFF_INIS[_str1_id].RL.back().at(2));
			}						
			
			//-------------------------------------------------------------------------
			//salida.
			break;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//para estructura de acción.
		case ACIS_TYPE:

			//-------------------------------------------------------------------------
			//si la estructura tiene relaciones, entonces.
			if (upci_ptr_str1->BUFF_ACIS[_str1_id].GetRelationAmount() > 0)
			{
				//---------------------------------------------------------------------
				//obtención de datos de la relación de lastructure 
				//str1_id.
				rl_type_str1		= abs(upci_ptr_str1->BUFF_ACIS[_str1_id].RL.back().at(0));
				rl_id_str1			= upci_ptr_str1->BUFF_ACIS[_str1_id].RL.back().at(1);
				upci_ptr_rl_str1	= &this->BUFF_UPCI_I_DS->at(upci_ptr_str1->BUFF_ACIS[_str1_id].RL.back().at(2));
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
				upci_ptr_rl_str1	= &this->BUFF_UPCI_I_DS->at(upci_ptr_str1->BUFF_INDFRLIS[_str1_id].RL.back().at(2));
			}			

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
in	UPCI_I_DS::CheckPreviousINDFRLIS(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	UPCI_I_DS	*upci_ptr_str1		=	&this->BUFF_UPCI_I_DS->at(_upci_id_str1);			//puntero de la upci de la estructura relacionada 1.				
	in			rl_type_str1		=	0;													//tipo de relación de la estructura relacionada 1.
	in			rl_id_str1			=	0;													//id de la relación de la estructura relacionada 1.	
	UPCI_I_DS	*upci_ptr_rl_str1	=	NULL;												//puntero de la upci de la relación de la estructura relacionada 1. 
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
		upci_ptr_rl_str1	= &this->BUFF_UPCI_I_DS->at(upci_ptr_str1->BUFF_INIS[_str1_id].RL.back().at(2));
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
in	UPCI_I_DS::CheckPreviousINPRRLIS(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	UPCI_I_DS	*upci_ptr_str1		=	&this->BUFF_UPCI_I_DS->at(_upci_id_str1);			//puntero de la upci de la estructura relacionada 1.				
	in			rl_type_str1		=	0;													//tipo de relación de la estructura relacionada 1.
	in			rl_id_str1			=	0;													//id de la relación de la estructura relacionada 1.	
	UPCI_I_DS	*upci_ptr_rl_str1	=	NULL;												//puntero de la upci de la relación de la estructura relacionada 1. 
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
		upci_ptr_rl_str1	= &this->BUFF_UPCI_I_DS->at(upci_ptr_str1->BUFF_INDFRLIS[_str1_id].RL.back().at(2));
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
vo	UPCI_I_DS::ReactiveINIS(in _inis_id)
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
	if (*this->BUFF_MAX_EVALUATION < this->BUFF_INIS[_inis_id].EV_RG)		this->SetBUFF_STR_MAX_EVAL(_inis_id, this->BUFF_INIS[_inis_id].EV_RG);

	//---------------------------------------------------------------------------------
	//si la IS reactivada posee el mayor nivel de actividad, entonces setear nueva estructura.
	if (*this->BUFF_MAX_ACTIVITY_LEVEL < this->BUFF_INIS[_inis_id].AL_SRG)	this->SetBUFF_STR_MAX_AL(_inis_id, INIS_TYPE, this->BUFF_INIS[_inis_id].AL_SRG);

	//---------------------------------------------------------------------------------
	//impresión de la reactivación de la entrada.
	//this->Print("    > se reactiva inis id", _inis_id);

	//---------------------------------------------------------------------------------
	//desbloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.unlock();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para reactivar ACIS.
vo	UPCI_I_DS::ReactiveACIS(in _lacis_id)
{
	//---------------------------------------------------------------------------------
	//bloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.lock();

	//---------------------------------------------------------------------------------
	//si le nivel de actividad es igual a "0", setear en buffer de IS en suspensión.
	if (this->BUFF_ACIS[_lacis_id].AL_SRG == 0) this->SetBUFF_STR_SUS(_lacis_id, ACIS_TYPE);

	//---------------------------------------------------------------------------------
	//incremento del nivel de actividad de la estructura "_lacis_id".
	this->BUFF_ACIS[_lacis_id].AL_SRG =	this->DEFAULT_ACTIVITY_LEVEL;

	//---------------------------------------------------------------------------------
	//seteo de la estructura ACIS activada.
	this->SetBUFF_ACIS_ACTIVATED(_lacis_id);

	//---------------------------------------------------------------------------------
	//si la IS reactivada posee el mayor nivel de actividad, entonces setear nueva estructura.
	if (*this->BUFF_MAX_ACTIVITY_LEVEL < this->BUFF_ACIS[_lacis_id].AL_SRG)	this->SetBUFF_STR_MAX_AL(_lacis_id, ACIS_TYPE, this->BUFF_ACIS[_lacis_id].AL_SRG);

	//---------------------------------------------------------------------------------
	//impresión de la reactivación de la acción.
	this->Print("    > se reactiva lacis id", _lacis_id);

	//---------------------------------------------------------------------------------
	//desbloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.unlock();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para reactivar PFRLIS.
vo	UPCI_I_DS::ReactivePFRLIS(in _pfrlis_id)
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
//#4: método para reactivar INDFRLIS.
vo	UPCI_I_DS::ReactiveINDFRLIS(in _indfrlis_id)
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
vo	UPCI_I_DS::GlobalDifferentiationINIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la bandera para reconocimiento de estructuras está desactivada, entonces.
	if(this->GetSTRUCTURES_RECOGNITION_FLAG() == OFF)	return;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variablea auxiliares para estructuras candidatas.	
	in upci_id_candidate		= NULL;														//id de la upci candidata.
	in inis_id_candidate		= NULL;														//id de la estructura candidata.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variablea auxiliares para estructuras candidatas.	
	in winning_upci_id			= NULL;														//id de la upci ganadora.		
	in winning_inis_id		= NULL;														//id de la estructura ganadora.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variablea auxiliares para cantidades.
	in upci_amount				= NULL;														//cantidad de upci existentes en el grupo.
	in upci_candidates_amount	= NULL;														//cantidad de upci con estructuras candidatas.
	in inis_candidates_amout  = NULL;														//cantidad de estructuras cadidatas.			
	in inis_with_fcc_amount	= NULL;														//cantidad de estructuras con F.C.C.	

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
		if (this->BUFF_UPCI_I_DS->at(i1).BUFF_INIS_INI_AMOUNT > 0)
		{
			//-------------------------------------------------------------------------
			//diferenciación de BUFF_IN_RG en la upci "i1".
			this->BUFF_UPCI_I_DS->at(i1).LocalDifferentiationINIS();
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
		//si existe solo una estructura candidata.
		if (this->BUFF_UPCI_ID_INIS_CAN->front().size() == 1 && this->BUFF_INIS_ID_CAN->front().at(this->BUFF_UPCI_ID_INIS_CAN->front().at(0)).size() == 1)
		{		
			//-------------------------------------------------------------------------
			//actualización del estado de congruencia de estructuras candidatas anteriores.
			this->UpdateToNotCongruentBUFF_INIS();			

			//-------------------------------------------------------------------------
			//obtención del id de la upci ganadora y del id de la estructura ganadora.
			winning_upci_id		= this->BUFF_UPCI_ID_INIS_CAN->front().at(0);
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
					if (this->BUFF_UPCI_I_DS->at(upci_id_candidate).ContinuousFlowOfCongruencesINIS(inis_id_candidate))
					{
						//-------------------------------------------------------------
						//seteo de id de upci y estructura ganadora.
						winning_upci_id		= upci_id_candidate;
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
//#2: método de diferenciación global para estructura ACIS.
vo	UPCI_I_DS::GlobalDifferentiationACIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la bandera para reconocimiento de estructuras está desactivada, entonces.
	if (this->GetSTRUCTURES_RECOGNITION_FLAG() == OFF || true)	return;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variablea auxiliares para estructuras candidatas.	
	in upci_id_candidate		= NULL;														//id de la upci candidata.
	in lacis_id_candidate		= NULL;														//id de la estructura candidata.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variablea auxiliares para estructuras candidatas.	
	in winning_upci_id			= NULL;														//id de la upci ganadora.		
	in winning_lacis_id		= NULL;														//id de la estructura ganadora.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variablea auxiliares para cantidades.
	in upci_amount				= NULL;														//cantidad de upci existentes en el grupo.
	in upci_candidates_amount	= NULL;														//cantidad de upci con estructuras candidatas.
	in lacis_candidates_amout	= NULL;														//cantidad de estructuras cadidatas.			
	in lacis_with_fcc_amount	= NULL;														//cantidad de estructuras con F.C.C.	

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de upci existentes en el grupo.
	upci_amount					= this->GetAmountUpcGro();							

	//---------------------------------------------------------------------------------
	//incremento del contador de diferenciaciones globales.
	++this->GLOBAL_DIFFERENTIATION_COUNTER;

	//---------------------------------------------------------------------------------
	//inicialización de buffers para candidatos.
	this->BUFF_UPCI_ID_ACIS_CAN->push_front(deque<in>(0));
	this->BUFF_ACIS_ID_CAN->push_front(deque<deque<in>>(0));
	this->BUFF_ACIS_ID_CAN->front().resize(upci_amount);

	//---------------------------------------------------------------------------------
	//limpieza del buffer de estructura reconocida.
	this->BUFF_ACIS_RE->Clean();

	//---------------------------------------------------------------------------------
	//limpieza de buffer para el índice de relación utilizada en reconocimiento.
	*this->BUFF_RL_INDEX_USED_IN_RECOGNITION = -1;
	
	//---------------------------------------------------------------------------------
	//paralelización del bucle for.
	#pragma omp parallel for

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para diferenciar BUFF_AC_RG con todas las upci.
	for (in i1 = 0; i1 < upci_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si existen estructuras ACIS entonces diferenciar en la upci "i1".
		if (this->BUFF_UPCI_I_DS->at(i1).BUFF_ACIS_INI_AMOUNT > 0)
		{
			//-------------------------------------------------------------------------
			//diferenciación de BUFF_AC_RG en la upci "i1".
			this->BUFF_UPCI_I_DS->at(i1).LocalDifferentiationACIS();
		}		
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para setear upci candidatas en buffer BUFF_UPCI_ID_ACIS_CAN.
	for (in i1 = 0; i1 < upci_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si la upci "i1" contiene estructuras candidatas, entonces. 
		if (this->BUFF_ACIS_ID_CAN->front().at(i1).size() > 0)
		{
			//-------------------------------------------------------------------------
			//seteo en buffer BUFF_UPCI_ID_ACIS_CAN.
			this->BUFF_UPCI_ID_ACIS_CAN->front().push_back(i1);
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existe alguna upci candidata, entonces.
	if (this->BUFF_UPCI_ID_ACIS_CAN->front().size() > 0)
	{
		//-----------------------------------------------------------------------------
		//actualización del estado de congruencia de estructuras candidatas presentes.
		this->UpdateToCongruentBUFF_ACIS();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existe solo una estructura candidata.
		if (this->BUFF_UPCI_ID_ACIS_CAN->front().size() == 1 && this->BUFF_ACIS_ID_CAN->front().at(this->BUFF_UPCI_ID_ACIS_CAN->front().at(0)).size() == 1)
		{		
			//-------------------------------------------------------------------------
			//actualización del estado de congruencia de estructuras candidatas anteriores.
			this->UpdateToNotCongruentBUFF_ACIS();			

			//-------------------------------------------------------------------------
			//obtención del id de la upci ganadora y del id de la estructura ganadora.
			winning_upci_id		= this->BUFF_UPCI_ID_ACIS_CAN->front().at(0);
			winning_lacis_id	= this->BUFF_ACIS_ID_CAN->front().at(upci_id_candidate).at(0);

			//-------------------------------------------------------------------------
			//seteo de la estructura reconocida.
			this->BUFF_ACIS_RE->Set(winning_upci_id, winning_lacis_id);
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existe más de una estructura candidata, entonces analizar la existencia de F.C.C.
		else
		{
			//-------------------------------------------------------------------------
			//obtención de la cantidad de estructuras candidatas.
			upci_candidates_amount = in(this->BUFF_UPCI_ID_ACIS_CAN->front().size());
			
			//-------------------------------------------------------------------------
			//paralelización del bucle for.
			#pragma omp parallel for

			//-------------------------------------------------------------------------  
			//bucle para conocer si existe F.C.C de las estructuras candidatas en upci i1.
			for (in i1 = 0; i1 < upci_candidates_amount; i1++)
			{
				//---------------------------------------------------------------------
				//obtención de id upci candidato.
				upci_id_candidate		= this->BUFF_UPCI_ID_ACIS_CAN->front().at(i1);

				//---------------------------------------------------------------------
				//obtención de la cantidad de candidatos ACIS en upci "i1".
				lacis_candidates_amout	= in(this->BUFF_ACIS_ID_CAN->front().at(upci_id_candidate).size());
				
				//---------------------------------------------------------------------
				//bucle para conocer si existe F.C.C en la estructura candidata i2.
				for (in i2 = 0; i2 < lacis_candidates_amout; i2++)
				{
					//-----------------------------------------------------------------
					//obtención del id de la estructura.
					lacis_id_candidate = this->BUFF_ACIS_ID_CAN->front().at(upci_id_candidate).at(i2);

					//-----------------------------------------------------------------
					//si la estructura tiene flujo de congruencias continuo, entonces.
					if (this->BUFF_UPCI_I_DS->at(upci_id_candidate).ContinuousFlowOfCongruencesACIS(lacis_id_candidate))
					{
						//-------------------------------------------------------------
						//seteo de id de upci y estructura ganadora.
						winning_upci_id		= upci_id_candidate;
						winning_lacis_id	= lacis_id_candidate;

						//-------------------------------------------------------------
						//incremento de los ids ACIS candidatos con F.C.C. 
						++lacis_with_fcc_amount;
					}
				}					
			}

			//-------------------------------------------------------------------------
			//actualización del estado de congruencia de estructuras candidatas anteriores.
			this->UpdateToNotCongruentBUFF_ACIS();

			//-------------------------------------------------------------------------
			//si existe solo una estructura con F.C.C, entonces existe reconocimiento.
			if (lacis_with_fcc_amount == 1)
			{
				//---------------------------------------------------------------------
				//seteo de la estructura reconocida.
				this->BUFF_ACIS_RE->Set(winning_upci_id, winning_lacis_id);
			}
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método de diferenciación global para estructura INDFRLIS.
vo	UPCI_I_DS::GlobalDifferentiationINDFRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la bandera para reconocimiento de estructuras está desactivada, entonces.
	if (this->GetSTRUCTURES_RECOGNITION_FLAG() == OFF || true)	return;

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
		if (this->BUFF_UPCI_I_DS->at(i1).BUFF_INDFRLIS_INI_AMOUNT > 0)
		{
			//-------------------------------------------------------------------------
			//diferenciación de BUFF_IN_DIF_RG en la upci "i1".
			this->BUFF_UPCI_I_DS->at(i1).LocalDifferentiationINDFRLIS();
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
					if (this->BUFF_UPCI_I_DS->at(upci_id_candidate).ContinuousFlowOfCongruencesINDFRLIS(indfrlis_id_candidate))
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
//#4: método de diferenciación global para estructura INPRRLIS.
vo	UPCI_I_DS::GlobalDifferentiationINPRRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la bandera para reconocimiento de estructuras está desactivada, entonces.
	if (this->GetSTRUCTURES_RECOGNITION_FLAG() == OFF || true)	return;

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
		if (this->BUFF_UPCI_I_DS->at(i1).BUFF_INPRRLIS_INI_AMOUNT > 0)
		{
			//-------------------------------------------------------------------------
			//diferenciación de BUFF_IN_PRO_RG en la upci "i1".
			this->BUFF_UPCI_I_DS->at(i1).LocalDifferentiationINPRRLIS();
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
					if (this->BUFF_UPCI_I_DS->at(upci_id_candidate).ContinuousFlowOfCongruencesINPRRLIS(inprrlis_id_candidate))
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
vo	UPCI_I_DS::LocalDifferentiationINIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	dou		differentiation		= NULL;														//diferenciación.
	in		congruence_flag		= OFF;														//bandera de congruencia. 
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
		//si la estructura no ha sido inicializada no se diferencia.
		if (this->BUFF_INIS[i1].AL_SRG != -1)
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si BUFF_IN_RG es mayor, entonces.
			if (abs(*this->BUFF_IN_RG) > abs(this->BUFF_INIS[i1].IN_RG))
			{
				//---------------------------------------------------------------------
				//diferenciación.
				differentiation = ((abs(*this->BUFF_IN_RG - this->BUFF_INIS[i1].IN_RG) / abs(*this->BUFF_IN_RG)) * 100.0);

				//---------------------------------------------------------------------
				//si la diferencia es menor o igual al umbral, existe congruencia.
				if (differentiation <= this->STR_CONGRUENCE_SR_THRESHOLD)	congruence_flag = ON;				
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si BUFF_IN_RG es menor o igual, entonces.
			else
			{
				//---------------------------------------------------------------------
				//diferenciación.
				differentiation = ((abs(*this->BUFF_IN_RG - this->BUFF_INIS[i1].IN_RG) / abs(this->BUFF_INIS[i1].IN_RG)) * 100.0);

				//---------------------------------------------------------------------
				//si la diferencia es menor o igual al umbral, existe congruencia.
				if (differentiation <= this->STR_CONGRUENCE_SR_THRESHOLD)	congruence_flag = ON;
			}	

			//-------------------------------------------------------------------------
			//seteo de la estructura candidata en buffer.
			if (congruence_flag == ON)
			{
				//---------------------------------------------------------------------
				//reset de la bandera de congruencia.
				congruence_flag = OFF;

				//---------------------------------------------------------------------
				//bloqueo del hilo.
				mut.lock();

				//---------------------------------------------------------------------
				//seteo del candidato.
				this->BUFF_INIS_ID_CAN->front().at(this->UPCI_ID).push_back(i1);

				//---------------------------------------------------------------------
				//desbloqueo del hilo.
				mut.unlock();
			}
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método de diferenciación local para estructura ACIS.
vo	UPCI_I_DS::LocalDifferentiationACIS()  
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliar mutex.
	mutex	mut;																			

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//paralelización del bucle for.
	#pragma omp parallel for

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para diferenciar BUFF_AC_RG con todas las estructuras ACIS.
	for (in i1 = 0; i1 < this->BUFF_ACIS_MAX_ID[0] + 1; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la estructura no ha sido inicializada no se diferencia.
		if (this->BUFF_ACIS[i1].AL_SRG != -1)
		{
			//-------------------------------------------------------------------------
			//si existe congruencia, entonces.
			if (*this->BUFF_AC_RG == this->BUFF_ACIS[i1].AC_RG)
			{
				//---------------------------------------------------------------------
				//bloqueo del hilo.
				mut.lock();

				//---------------------------------------------------------------------
				//seteo del candidato.
				this->BUFF_ACIS_ID_CAN->front().at(this->UPCI_ID).push_back(i1);

				//---------------------------------------------------------------------
				//desbloqueo del hilo.
				mut.unlock();
			}
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método de diferenciación local para estructura INDFRLIS.
vo	UPCI_I_DS::LocalDifferentiationINDFRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	dou		differentiation		= NULL;														//diferenciación.
	in		congruence_flag		= OFF;														//bandera de congruencia.
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
		//si la estructura no ha sido inicializada no se diferencia.
		if (this->BUFF_INDFRLIS[i1].AL_SRG != -1)
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si BUFF_IN_DIF_RG es mayor, entonces.
			if (abs(*this->BUFF_IN_DIF_RG) > abs(this->BUFF_INDFRLIS[i1].IN_DIF_RG))
			{
				//---------------------------------------------------------------------
				//diferenciación.
				differentiation = ((abs(*this->BUFF_IN_DIF_RG - this->BUFF_INDFRLIS[i1].IN_DIF_RG) / abs(*this->BUFF_IN_DIF_RG)) * 100.0);

				//---------------------------------------------------------------------
				//si la diferencia es menor o igual al umbral, existe congruencia.
				if (differentiation <= this->STR_CONGRUENCE_SR_THRESHOLD)	congruence_flag = ON;
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si BUFF_IN_DIF_RG es menor o igual, entonces.
			else
			{
				//---------------------------------------------------------------------
				//diferenciación.
				differentiation = ((abs(*this->BUFF_IN_DIF_RG - this->BUFF_INDFRLIS[i1].IN_DIF_RG) / abs(this->BUFF_INDFRLIS[i1].IN_DIF_RG)) * 100.0);

				//---------------------------------------------------------------------
				//si la diferencia es menor o igual al umbral, existe congruencia.
				if (differentiation <= this->STR_CONGRUENCE_SR_THRESHOLD)	congruence_flag = ON;
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//seteo de la estructura candidata en buffer.
			if (congruence_flag == ON)
			{
				//---------------------------------------------------------------------
				//reset de la bandera de congruencia.
				congruence_flag = OFF;

				//---------------------------------------------------------------------
				//bloqueo del hilo.
				mut.lock();

				this->BUFF_INDFRLIS_ID_CAN->front().at(this->UPCI_ID).push_back(i1);

				//---------------------------------------------------------------------
				//desbloqueo del hilo.
				mut.unlock();
			}
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método de diferenciación local para estructura INPRRLIS.
vo	UPCI_I_DS::LocalDifferentiationINPRRLIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	dou		differentiation		= NULL;														//diferenciación.
	in		congruence_flag		= OFF;														//bandera de congruencia.
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
		//si la estructura no ha sido inicializada no se diferencia.
		if (this->BUFF_INPRRLIS[i1].CS_SRG != -1)
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si BUFF_IN_PRO_RG es mayor, entonces.
			if (abs(*this->BUFF_IN_PRO_RG) > abs(this->BUFF_INPRRLIS[i1].IN_PRO_RG))
			{
				//---------------------------------------------------------------------
				//diferenciación.
				differentiation = ((abs(*this->BUFF_IN_PRO_RG - this->BUFF_INPRRLIS[i1].IN_PRO_RG) / abs(*this->BUFF_IN_PRO_RG)) * 100.0);

				//---------------------------------------------------------------------
				//si la diferencia es menor o igual al umbral, existe congruencia.
				if (differentiation <= this->STR_CONGRUENCE_SR_THRESHOLD)	congruence_flag = ON;
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si BUFF_IN_PRO_RG es menor o igual, entonces.
			else
			{
				//---------------------------------------------------------------------
				//diferenciación.
				differentiation = ((abs(*this->BUFF_IN_PRO_RG - this->BUFF_INPRRLIS[i1].IN_PRO_RG) / abs(this->BUFF_INPRRLIS[i1].IN_PRO_RG)) * 100.0);

				//---------------------------------------------------------------------
				//si la diferencia es menor o igual al umbral, existe congruencia.
				if (differentiation <= this->STR_CONGRUENCE_SR_THRESHOLD)	congruence_flag = ON;
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//seteo de la estructura candidata en buffer.
			if (congruence_flag == ON)
			{
				//---------------------------------------------------------------------
				//reset de la bandera de congruencia.
				congruence_flag = OFF;

				//---------------------------------------------------------------------
				//bloqueo del hilo.
				mut.lock();

				this->BUFF_INPRRLIS_ID_CAN->front().at(this->UPCI_ID).push_back(i1);

				//---------------------------------------------------------------------
				//desbloqueo del hilo.
				mut.unlock();
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
//#1: método para conocer si exite flujo continuo de congruencias en estructuras 
//candidatas tipo INIS.
in	UPCI_I_DS::ContinuousFlowOfCongruencesINIS(in _inis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//declaraciones auxiliares.
	in			str_id				=   NULL;												//id auxiliar para estructuras.
	in			rl_type				=   NULL;												//id auxiliar para una estructura de relación de la estructura _inis_id.
	in			rl_id				=   NULL;												//id auxiliar para una estructura de relación de la estructura _inis_id.
	UPCI_I_DS	*upci_ptr_rl_str	=	NULL;												//puntero auxiliar de la upci de la relación de la estructura _inis_id. 
	UPCI_I_DS	*upci_id_rl_rl_str	=	NULL;												//puntero auxiliar de la upci de la relación de la relación de la estructura _inis_id.
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
		upci_ptr_rl_str	= &this->BUFF_UPCI_I_DS->at(this->BUFF_INIS[_inis_id].RL.at(i1).at(2));

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si la relación es el tipo de flujo puro entrante, entonces.
		if (rl_type == -PFRLIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//obtención de datos de la primera estructura.
			upci_id_rl_rl_str	= &this->BUFF_UPCI_I_DS->at(upci_ptr_rl_str->BUFF_PFRLIS[rl_id].UPCI_ID_STR1_RG);
			str_id				= upci_ptr_rl_str->BUFF_PFRLIS[rl_id].STR1_ID_RG;
			
			//-------------------------------------------------------------------------
			//si la estructura está en estado congruente, entonces la estructura 
			//tiene F.C.C.
			if (upci_id_rl_rl_str->BUFF_ACIS[str_id].CS_SRG == ON)
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
			upci_id_rl_rl_str	= &this->BUFF_UPCI_I_DS->at(upci_ptr_rl_str->BUFF_INDFRLIS[rl_id].UPCI_ID_STR1_RG);

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
//candidatas tipo ACIS.
in	UPCI_I_DS::ContinuousFlowOfCongruencesACIS(in _lacis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//declaraciones auxiliares.
	in			str_id				=   NULL;												//id auxiliar para estructuras.
	in			rl_type				=   NULL;												//id auxiliar para una estructura de relación de la estructura _lacis_id.
	in			rl_id				=   NULL;												//id auxiliar para una estructura de relación de la estructura _lacis_id.
	UPCI_I_DS	*upci_ptr_rl_str	=	NULL;												//puntero auxiliar de la upci de la relación de la estructura _lacis_id. 
	UPCI_I_DS	*upci_id_rl_rl_str	=	NULL;												//puntero de la relación de la relación de la estructura _lacis_id.
	in			rl_amount			=   NULL;												//cantidad de relaciones.

	//---------------------------------------------------------------------------------
	//obtención de la cantidad de relaciones de la estructura.
	rl_amount = this->BUFF_ACIS[_lacis_id].GetRelationAmount();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para verificar si existe una estructura congruente anterior contigua.
	for (in i1 = 0; i1 < rl_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del datos de la relación.
		rl_type				= this->BUFF_ACIS[_lacis_id].RL.at(i1).at(0);
		rl_id				= this->BUFF_ACIS[_lacis_id].RL.at(i1).at(1);
		upci_ptr_rl_str		= &this->BUFF_UPCI_I_DS->at(this->BUFF_ACIS[_lacis_id].RL.at(i1).at(2));

		//-----------------------------------------------------------------------------
		//id de la upci de la primera estructura.
		upci_id_rl_rl_str	= &this->BUFF_UPCI_I_DS->at(upci_ptr_rl_str->BUFF_PFRLIS[rl_id].UPCI_ID_STR1_RG);

		//-----------------------------------------------------------------------------
		//carga del id del registro relacionado.
		str_id				= upci_ptr_rl_str->BUFF_PFRLIS[rl_id].STR1_ID_RG;

		//-----------------------------------------------------------------------------
		//si la estructura anterior es del tipo entrada.
		if (upci_ptr_rl_str->BUFF_PFRLIS[rl_id].STR1_TYPE_RG == INIS_TYPE)
		{
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
		//si la estructura anterior es del tipo acción.
		else if (upci_ptr_rl_str->BUFF_PFRLIS[rl_id].STR1_TYPE_RG == ACIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//si la estructura está en estado congruente, entonces la estructura 
			//tiene F.C.C.
			if (upci_id_rl_rl_str->BUFF_ACIS[str_id].CS_SRG == ON)
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
//#3: método para conocer si exite flujo continuo de congruencias en estructuras 
//candidatas tipo INDFRLIS.
in	UPCI_I_DS::ContinuousFlowOfCongruencesINDFRLIS(in _indfrlis_id)
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
	rl_amount					= this->BUFF_UPCI_I_DS->at(upci_id_str1).BUFF_INIS[str1_id].GetRelationAmount();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para verificar si existe una estructura congruente anterior contigua.
	for (in i1 = 0; i1 < rl_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si se encuentra una relación diferencial de entrada, entonces.
		if (abs(this->BUFF_UPCI_I_DS->at(upci_id_str1).BUFF_INIS[str1_id].RL.at(i1).at(0)) == INDFRLIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//id de la relación INDFRLIS hallada.
			indfrlis_id_found		= this->BUFF_UPCI_I_DS->at(upci_id_str1).BUFF_INIS[str1_id].RL.at(i1).at(1);

			//-------------------------------------------------------------------------
			//seteo del id de la upci de la relación INDFRLIS hallada.
			upci_id_indfrlis_found	= this->BUFF_UPCI_I_DS->at(upci_id_str1).BUFF_INIS[str1_id].RL.at(i1).at(2);

			//-------------------------------------------------------------------------
			//obtención de datos de las estructuras relacionadas en INDFRLIS hallada.
			str1_id_aux				= this->BUFF_UPCI_I_DS->at(upci_id_indfrlis_found).BUFF_INDFRLIS[indfrlis_id_found].STR1_ID_RG;
			str2_id_aux				= this->BUFF_UPCI_I_DS->at(upci_id_indfrlis_found).BUFF_INDFRLIS[indfrlis_id_found].STR2_ID_RG;
			upci_id_str1_aux		= this->BUFF_UPCI_I_DS->at(upci_id_indfrlis_found).BUFF_INDFRLIS[indfrlis_id_found].UPCI_ID_STR1_RG;
			upci_id_str2_aux		= this->BUFF_UPCI_I_DS->at(upci_id_indfrlis_found).BUFF_INDFRLIS[indfrlis_id_found].UPCI_ID_STR2_RG;

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si las estructuras relacionadas son distintas, entonces.
			if(str1_id_aux != str1_id_aux && upci_id_str1_aux != upci_id_str1_aux)
			{ 
				//---------------------------------------------------------------------
				//si la relación encontrada es entrante, entonces.
				if (this->BUFF_UPCI_I_DS->at(upci_id_str1).BUFF_INIS[str1_id].RL.at(i1).at(0) == -INDFRLIS_TYPE)
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
				if (this->BUFF_UPCI_I_DS->at(upci_id_indfrlis_found).BUFF_INDFRLIS[indfrlis_id_found].CS_SRG == ON)
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
						rl_index_in_str = this->BUFF_UPCI_I_DS->at(upci_id_str2).BUFF_INIS[str2_id].GetRelationIndex(INDFRLIS_TYPE, _indfrlis_id, this->UPCI_ID);

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
//#4: método para conocer si exite flujo continuo de congruencias en estructuras 
//candidatas tipo INPRRLIS.
in	UPCI_I_DS::ContinuousFlowOfCongruencesINPRRLIS(in _inprrlis_id)
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
	rl_amount					= this->BUFF_UPCI_I_DS->at(upci_id_str1).BUFF_INDFRLIS[str1_id].GetRelationAmount();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para verificar si existe una estructura congruente anterior contigua.
	for (in i1 = 0; i1 < rl_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si se encuentra una relación proporcional de entrada entrante, entonces.
		if (this->BUFF_UPCI_I_DS->at(upci_id_str1).BUFF_INDFRLIS[str1_id].RL.at(i1).at(0) == -INPRRLIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//id de la relación INPRRLIS hallada.
			inprrlis_id_found		= this->BUFF_UPCI_I_DS->at(upci_id_str1).BUFF_INDFRLIS[str1_id].RL.at(i1).at(1);

			//-------------------------------------------------------------------------
			//seteo del id de la upci de la relación INPRRLIS hallada.
			upci_id_inprrlis_found	= this->BUFF_UPCI_I_DS->at(upci_id_str1).BUFF_INDFRLIS[str1_id].RL.at(i1).at(2);

			//-------------------------------------------------------------------------
			//si la estructura está en estado congruente, entonces la estructura tiene F.C.C.
			if (this->BUFF_UPCI_I_DS->at(upci_id_inprrlis_found).BUFF_INPRRLIS[inprrlis_id_found].CS_SRG == ON)
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
					rl_index_in_str = this->BUFF_UPCI_I_DS->at(upci_id_str2).BUFF_INDFRLIS[str2_id].GetRelationIndex(INPRRLIS_TYPE, _inprrlis_id, this->UPCI_ID);

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
vo	UPCI_I_DS::CleanBuffersOfPreviousCandidatesINIS()
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
//#2: método para Clean buffer BUFF_ACIS_ID_CAN y BUFF_UPCI_ID_ACIS_CAN pasados.
vo	UPCI_I_DS::CleanBuffersOfPreviousCandidatesACIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existen estructuras candidatas anteriores, Clean buffers.
	if (this->BUFF_ACIS_ID_CAN->size() > 1)
	{
		//-----------------------------------------------------------------------------
		//se limpian buffers en tiempo [1].
		this->BUFF_ACIS_ID_CAN->pop_back();
		this->BUFF_UPCI_ID_ACIS_CAN->pop_back();
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para Clean buffer BUFF_INDFRLIS_ID_CAN y BUFF_UPCI_ID_INDFRLIS_CAN pasados.
vo	UPCI_I_DS::CleanBuffersOfPreviousCandidatesINDFRLIS()
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
//#4: método para Clean buffer BUFF_INPRRLIS_ID_CAN y BUFF_UPCI_ID_INPRRLIS_CAN pasados.
vo	UPCI_I_DS::CleanBuffersOfPreviousCandidatesINPRRLIS()
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
vo	UPCI_I_DS::CleanActivityLevelIS()
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
			this->BUFF_UPCI_I_DS->at(upci_id_str_sus).BUFF_INIS[str_id_sus].AL_SRG = 0;
		}

		//-----------------------------------------------------------------------------
		//obtención de la cantidad de estructuras ACIS en suspensión.
		str_sus_amount = in(this->BUFF_ACIS_SUS->size());			

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para limpiar niveles de actividad de estructuras ACIS.
		for (in i1 = 0; i1 < str_sus_amount; i1++)
		{
			//-------------------------------------------------------------------------
			//seteo del id de la upci en suspensión y el id de estructura en suspensión.
			upci_id_str_sus		= this->BUFF_ACIS_SUS->at(i1).UPCI_ID;
			str_id_sus			= this->BUFF_ACIS_SUS->at(i1).STR_ID;

			//-------------------------------------------------------------------------
			//se limpia el nivel de actividad.
			this->BUFF_UPCI_I_DS->at(upci_id_str_sus).BUFF_ACIS[str_id_sus].AL_SRG = 0;
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
			this->BUFF_UPCI_I_DS->at(upci_id_str_sus).BUFF_PFRLIS[str_id_sus].AL_SRG = 0;
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
			this->BUFF_UPCI_I_DS->at(upci_id_str_sus).BUFF_INDFRLIS[str_id_sus].AL_SRG = 0;
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//limpieza del buffer de IS en suspensión.
		this->BUFF_INIS_SUS->clear();
		this->BUFF_ACIS_SUS->clear();
		this->BUFF_PFRLIS_SUS->clear();
		this->BUFF_INDFRLIS_SUS->clear();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//reset del buffer para el flujo de estructuras activadas.
		this->BUFF_STR_ACTIVATED[0].Clean();
		this->BUFF_STR_ACTIVATED[1].Clean();
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//desbloqueo de la limpieza.
		this->RED_LIGHT_MUTEX.unlock();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//se desactiva la bandera de la existencia de estructuras en estado de suspensión.
		this->SetSUSPENDED_STRUCTURES_FLAG(OFF);
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método thread para actualizar niveles de actividad de IS.
vo	UPCI_I_DS::UpdateActivityLevelIS()
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
				this->BUFF_UPCI_I_DS->at(upci_id_str_sus).BUFF_INIS[str_id_sus].AL_SRG -= 1;
				
				//---------------------------------------------------------------------
				//si nivel de actividad es "0", quitar de buffer IS en suspensión.
				if (this->BUFF_UPCI_I_DS->at(upci_id_str_sus).BUFF_INIS[str_id_sus].AL_SRG == 0)
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
			//obtención de la cantidad de estructuras ACIS en suspensión.
			str_sus_amount = in(this->BUFF_ACIS_SUS->size());			
			
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para limpiar niveles de actividad de estructuras ACIS.
			for (in i1 = 0; i1 < str_sus_amount;)
			{
				//---------------------------------------------------------------------
				//seteo del id de la upci en suspensión y el id de estructura en suspensión.
				upci_id_str_sus		= this->BUFF_ACIS_SUS->at(i1).UPCI_ID;
				str_id_sus			= this->BUFF_ACIS_SUS->at(i1).STR_ID;

				//---------------------------------------------------------------------
				//se decrementa el nivel de actividad.
				this->BUFF_UPCI_I_DS->at(upci_id_str_sus).BUFF_ACIS[str_id_sus].AL_SRG -= 1;

				//---------------------------------------------------------------------
				//si nivel de actividad es "0", quitar de buffer IS en suspensión.
				if (this->BUFF_UPCI_I_DS->at(upci_id_str_sus).BUFF_ACIS[str_id_sus].AL_SRG == 0)
				{
					//-----------------------------------------------------------------
					//eliminación del elemento de los buffers de IS en suspensión.
					this->BUFF_ACIS_SUS->erase(this->BUFF_ACIS_SUS->begin() + i1);

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
				this->BUFF_UPCI_I_DS->at(upci_id_str_sus).BUFF_PFRLIS[str_id_sus].AL_SRG -= 1;
				
				//---------------------------------------------------------------------
				//si nivel de actividad es "0", quitar de buffer IS en suspensión.
				if (this->BUFF_UPCI_I_DS->at(upci_id_str_sus).BUFF_PFRLIS[str_id_sus].AL_SRG == 0)
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
					if (this->BUFF_UPCI_I_DS->at(upci_id_str_sus).BUFF_PFRLIS[str_id_sus].RS_SRG < this->PFRLIS_STRENGTH_THRESHOLD)
					{
						//-------------------------------------------------------------
						//eliminación de la estructura de información.
						this->BUFF_UPCI_I_DS->at(upci_id_str_sus).DeletePFRLIS(str_id_sus);
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
				this->BUFF_UPCI_I_DS->at(upci_id_str_sus).BUFF_INDFRLIS[str_id_sus].AL_SRG -= 1;

				//---------------------------------------------------------------------
				//si nivel de actividad es "0", quitar de buffer IS en suspensión.
				if (this->BUFF_UPCI_I_DS->at(upci_id_str_sus).BUFF_INDFRLIS[str_id_sus].AL_SRG == 0)
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
					if (this->BUFF_UPCI_I_DS->at(upci_id_str_sus).BUFF_INDFRLIS[str_id_sus].RS_SRG < this->INDFRLIS_STRENGTH_THRESHOLD)
					{
						//-------------------------------------------------------------
						//eliminación de la estructura de información.
						this->BUFF_UPCI_I_DS->at(upci_id_str_sus).DeleteINDFRLIS(str_id_sus);
					}
				}

				//---------------------------------------------------------------------
				//incremento de i1.
				else ++i1;
			}
			
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si ya no existen estructuras en estado de suspensión.
			if (this->BUFF_INIS_SUS->size()	== 0	&&
				this->BUFF_ACIS_SUS->size()	== 0	&&
				this->BUFF_PFRLIS_SUS->size()	== 0	&&
				this->BUFF_INDFRLIS_SUS->size()	== 0)
			{
				//---------------------------------------------------------------------
				//reset del buffer para el flujo de estructuras activadas.
				this->BUFF_STR_ACTIVATED[0].Clean();
				this->BUFF_STR_ACTIVATED[1].Clean();

				//---------------------------------------------------------------------
				//se desactiva la bandera de la existencia de estructuras en estado de suspensión
				this->SetSUSPENDED_STRUCTURES_FLAG(OFF);
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
vo	UPCI_I_DS::UpdateBuffersAfterCreatingINIS(in _inis_id, dou _input_evaluation, dou _al_srg)
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
	if (*this->BUFF_MAX_EVALUATION	< _input_evaluation)	this->SetBUFF_STR_MAX_EVAL(_inis_id, _input_evaluation);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si el nivel de actividad actual es mayor al máximo, entonces setear el nuevo 
	//máximo nivel de actividad.
	if (*this->BUFF_MAX_ACTIVITY_LEVEL < _al_srg)		this->SetBUFF_STR_MAX_AL(_inis_id, INIS_TYPE, _al_srg);

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
						candidate_id								!=	i1)
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
				if (this->BUFF_INIS_CRE[0].STR_ID	!= i1 && this->BUFF_INIS_CRE[1].STR_ID != i1)
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
					this->BUFF_INIS_CRE[0].STR_ID				!=		i1			&&
					this->BUFF_INIS_CRE[1].STR_ID				!=		i1			&&
					candidate_id								!=		i1)
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
//#2: método para actualizar buffer tras eliminar IS ACIS.
vo	UPCI_I_DS::UpdateBuffersAfterCreatingACIS(in _lacis_id, dou _al_srg)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//declaración del id candidato para una nueva creación.
	in candidate_id				= -1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incremento de la cantidad existente de estructuras.
	++this->BUFF_ACIS_INI_AMOUNT;
	++this->BUFF_TOTAL_STR_INI_AMOUNT;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//reset del id disponible utilizado.
	this->BUFF_ACIS_ID_AV[0]	= -1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de estructura ACIS creada.
	this->SetBUFF_ACIS_CRE(_lacis_id);	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de la estructura ACIS activada.
	this->SetBUFF_ACIS_ACTIVATED(_lacis_id);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de la estructura suspendida.
	this->SetBUFF_STR_SUS(_lacis_id, ACIS_TYPE);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si el id es mayor que el máximo id, update BUFF_ACIS_MAX_ID.
	if (this->BUFF_ACIS_MAX_ID[0] < _lacis_id)
	{
		//-----------------------------------------------------------------------------
		//actualización de BUFF_ACIS_MAX_ID.
		this->BUFF_ACIS_MAX_ID[1] = this->BUFF_ACIS_MAX_ID[0];
		this->BUFF_ACIS_MAX_ID[0] = _lacis_id;
	}

	//---------------------------------------------------------------------------------
	//si el id es mayor que el segundo máximo id, update BUFF_ACIS_MAX_ID.
	else if (this->BUFF_ACIS_MAX_ID[1] < _lacis_id)
	{
		//-----------------------------------------------------------------------------
		//actualización de BUFF_ACIS_MAX_ID.
		this->BUFF_ACIS_MAX_ID[1] = _lacis_id;
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si el nivel de actividad actual es mayor al máximo, entonces setear el nuevo 
	//máximo nivel de actividad.
	if (*this->BUFF_MAX_ACTIVITY_LEVEL < _al_srg) this->SetBUFF_STR_MAX_AL(_lacis_id, ACIS_TYPE, _al_srg);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si se ha definido el id en la posición [1], entonces setear [0].
	if (this->BUFF_ACIS_ID_AV[1] != -1)
	{
		//-----------------------------------------------------------------------------
		//seteo del id candidato para la creación de una nueva estructura.
		this->BUFF_ACIS_ID_AV[0] = this->BUFF_ACIS_ID_AV[1];
		this->BUFF_ACIS_ID_AV[1] = -1;
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del id de la estructura ACIS disponible, si no se ha llenado el buffer.
	else if (this->BUFF_ACIS_INI_AMOUNT < this->ACIS_AMOUNT_ALLOWED)
	{
		//-----------------------------------------------------------------------------
		//bucle para hallar el id de una estructura sin inicializar.
		for (in i1 = 0; i1 < this->ACIS_AMOUNT_ALLOWED; i1++)
		{
			//-------------------------------------------------------------------------
			//si la estructura no se ha inicializado, entonces.
			if (this->BUFF_ACIS[i1].AL_SRG == -1)
			{
				//---------------------------------------------------------------------
				//seteo del id candidato para la creación de una nueva estructura.
				this->BUFF_ACIS_ID_AV[0] = i1;

				//---------------------------------------------------------------------
				//salir del bucle.
				break;
			}
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del id de la estructura ACIS disponible, si se ha llenado el buffer.
	else
	{
		//-----------------------------------------------------------------------------
		//declaración de la cantidad de relaciones de la estructura candidata.
		in rl_amount	= NULL;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si existen estructuras no suspendidas, entonces.
		if (this->BUFF_ACIS_SUS->size() < this->BUFF_ACIS_INI_AMOUNT)
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para inicializar id y cantidad de relaciones de la estructura candidata.
			for (in i1 = 0; i1 < this->BUFF_ACIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//si la estructura está no está suspendida, entonces. 
				if (this->BUFF_ACIS[i1].AL_SRG == 0)
				{
					//-----------------------------------------------------------------
					//seteo.
					candidate_id	= i1;
					rl_amount		= this->BUFF_ACIS[i1].GetRelationAmount();

					//-----------------------------------------------------------------
					//salida del bucle.
					break;
				}
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para hallar la estructura con la menor cantidad de relaciones.
			for (in i1 = 0; i1 < this->BUFF_ACIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//si la estructura no está en suspensión.
				if (this->BUFF_ACIS[i1].AL_SRG == 0)
				{
					//-----------------------------------------------------------------
					//si la estructura posee una menor fortaleza de relación
					if (this->BUFF_ACIS[i1].GetRelationAmount()	<	rl_amount &&
						candidate_id								!=	i1)
					{
						//-------------------------------------------------------------
						//seteo de un nuevo id candidato.
						candidate_id	= i1;
						rl_amount		= this->BUFF_ACIS[i1].GetRelationAmount();
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
			for (in i1 = 0; i1 < this->BUFF_ACIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//si la estructura es distinta de las creadas, entonces. 
				if (this->BUFF_ACIS_CRE[0].STR_ID	!= i1 && this->BUFF_ACIS_CRE[1].STR_ID != i1)
				{
					//-----------------------------------------------------------------
					//seteo.
					candidate_id	= i1;
					rl_amount		= this->BUFF_ACIS[i1].GetRelationAmount();

					//-----------------------------------------------------------------
					//salida del bucle.
					break;
				}
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para hallar la estructura con la menor cantidad de relaciones.
			for (in i1 = 0; i1 < this->BUFF_ACIS_MAX_ID[0] + 1; i1++)
			{
				//---------------------------------------------------------------------
				//emparejamiento para selección de la estructura con menor cantidad de relaciones.
				if (this->BUFF_ACIS[i1].GetRelationAmount()	<		rl_amount	&&
					this->BUFF_ACIS_CRE[0].STR_ID				!=		i1			&&
					this->BUFF_ACIS_CRE[1].STR_ID				!=		i1			&&
					candidate_id								!=		i1)
				{
					//-----------------------------------------------------------------
					//seteo de un nuevo id candidato.
					candidate_id	= i1;
					rl_amount		= this->BUFF_ACIS[i1].GetRelationAmount();
				}
			}
		}		
		
		//-----------------------------------------------------------------------------
		//limpieza de la estructura con id candidato.
		this->DeleteACIS(candidate_id);
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------  
//#3: método para actualizar buffer tras eliminar IS PFRLIS.
vo	UPCI_I_DS::UpdateBuffersAfterCreatingPFRLIS(in _pfrlis_id)
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
//#4: método para actualizar buffer tras eliminar IS INDFRLIS.
vo	UPCI_I_DS::UpdateBuffersAfterCreatingINDFRLIS(in _indfrlis_id)
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
//#5: método para actualizar buffer tras eliminar IS INPRRLIS.
vo	UPCI_I_DS::UpdateBuffersAfterCreatingINPRRLIS(in _inprrlis_id)
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
				rs_indfrlis1		= this->BUFF_UPCI_I_DS->at(upci_id_indfrlis1).BUFF_INDFRLIS[indfrlis1_id].RS_SRG;
				rs_indfrlis1		= this->BUFF_UPCI_I_DS->at(upci_id_indfrlis2).BUFF_INDFRLIS[indfrlis2_id].RS_SRG;

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
			rs_indfrlis1		= this->BUFF_UPCI_I_DS->at(upci_id_indfrlis1).BUFF_INDFRLIS[indfrlis1_id].RS_SRG;
			rs_indfrlis1		= this->BUFF_UPCI_I_DS->at(upci_id_indfrlis2).BUFF_INDFRLIS[indfrlis2_id].RS_SRG;

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
vo	UPCI_I_DS::UpdateBuffersToDeleteINIS(in _inis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con la IS con mayor evaluación, update.
	if (this->BUFF_STR_MAX_EVAL->UPCI_ID		==	this->UPCI_ID &&
		this->BUFF_STR_MAX_EVAL->STR_ID			==	_inis_id)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer para estructura con máxima evaluación.
		this->BUFF_STR_MAX_EVAL->Clean();
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con la IS con mayor nivel de actividad, update.
	if (this->BUFF_STR_MAX_AL->UPCI_ID			==	this->UPCI_ID	&&
		this->BUFF_STR_MAX_AL->STR_ID			==	_inis_id		&&
		this->BUFF_STR_MAX_AL->STR_TYPE			==	INIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//reset de buffers para estructura con máximo nivel de actividad.
		this->BUFF_STR_MAX_AL->Clean();
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el flujo de IS activa presente, entonces.
	if (this->BUFF_STR_ACTIVATED[0].UPCI_ID		==	this->UPCI_ID	&&
		this->BUFF_STR_ACTIVATED[0].STR_ID		==	_inis_id		&&
		this->BUFF_STR_ACTIVATED[0].STR_TYPE	==	INIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de flujo de estructura activada presente.
		this->BUFF_STR_ACTIVATED[0].Clean();
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el flujo de IS activa anterior, entonces.
	else if (this->BUFF_STR_ACTIVATED[1].UPCI_ID	==	this->UPCI_ID	&&
			 this->BUFF_STR_ACTIVATED[1].STR_ID		==	_inis_id		&&
			 this->BUFF_STR_ACTIVATED[1].STR_TYPE	==	INIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de flujo de estructura activada presente.
		this->BUFF_STR_ACTIVATED[1].Clean();
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
			this->BUFF_INIS_MAX_ID[0]		= this->BUFF_INIS_MAX_ID[1];
			this->BUFF_INIS_MAX_ID[1]		= -1;
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
				this->BUFF_INIS_SUS->at(i1).STR_ID		==	_inis_id)
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
//#2: método para actualizar buffer tras eliminar IS ACIS.
vo	UPCI_I_DS::UpdateBuffersToDeleteACIS(in _lacis_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con la IS con mayor nivel de actividad, update.
	if (this->BUFF_STR_MAX_AL->UPCI_ID			==	this->UPCI_ID	&&
		this->BUFF_STR_MAX_AL->STR_ID			==	_lacis_id		&&
		this->BUFF_STR_MAX_AL->STR_TYPE			==	ACIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//reset de buffers para estructura con máximo nivel de actividad.
		this->BUFF_STR_MAX_AL->Clean();
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el flujo de IS activa presente, entonces.
	if (this->BUFF_STR_ACTIVATED[0].UPCI_ID		==	this->UPCI_ID	&&
		this->BUFF_STR_ACTIVATED[0].STR_ID		==	_lacis_id		&&
		this->BUFF_STR_ACTIVATED[0].STR_TYPE	==	ACIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de flujo de estructura activada presente.
		this->BUFF_STR_ACTIVATED[0].Clean();
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el flujo de IS activa anterior, entonces.
	else if (this->BUFF_STR_ACTIVATED[1].UPCI_ID	==	this->UPCI_ID	&&
			 this->BUFF_STR_ACTIVATED[1].STR_ID		==	_lacis_id		&&
			 this->BUFF_STR_ACTIVATED[1].STR_TYPE	==	ACIS_TYPE)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de flujo de estructura activada presente.
		this->BUFF_STR_ACTIVATED[1].Clean();
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada correponde con la IS creada presente.
	if (this->BUFF_ACIS_CRE[0].UPCI_ID	== this->UPCI_ID &&	this->BUFF_ACIS_CRE[0].STR_ID	== _lacis_id)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de estructura creada presente.
		this->BUFF_ACIS_CRE[0].Clean();
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada correponde con la IS creada anterior.
	if (this->BUFF_ACIS_CRE[1].UPCI_ID	== this->UPCI_ID &&	this->BUFF_ACIS_CRE[1].STR_ID	== _lacis_id)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de estructura creada anterior.
		this->BUFF_ACIS_CRE[1].Clean();
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el id máximo, update.
	if (_lacis_id == this->BUFF_ACIS_MAX_ID[0])
	{
		//-----------------------------------------------------------------------------
		//si existe segun mayor, traspasar segundo mayor a primero.
		if (this->BUFF_ACIS_MAX_ID[1] != -1)
		{
			//-------------------------------------------------------------------------
			//actualización del buffer de máximo id.
			this->BUFF_ACIS_MAX_ID[0] = this->BUFF_ACIS_MAX_ID[1];
			this->BUFF_ACIS_MAX_ID[1] = -1;
		}		

		//-----------------------------------------------------------------------------
		//reset, sino existe segundo mayor id.
		else this->BUFF_ACIS_MAX_ID[0] = -1;
	}

	//---------------------------------------------------------------------------------
	//si la IS eliminada corresponde con el segundo id mayor, entonces actualizar.
	else if (_lacis_id == this->BUFF_ACIS_MAX_ID[1])	this->BUFF_ACIS_MAX_ID[1] = -1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de ID disponible si hay cupo.
	if		(this->BUFF_ACIS_ID_AV[0] == -1) this->BUFF_ACIS_ID_AV[0] = _lacis_id;
	else if (this->BUFF_ACIS_ID_AV[1] == -1) this->BUFF_ACIS_ID_AV[1] = _lacis_id;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la IS está en suspensión.
	if (this->BUFF_ACIS[_lacis_id].AL_SRG > 0)
	{
		//-----------------------------------------------------------------------------
		//cantidad de estructuras suspendidas.
		in	str_sus_amount = in(this->BUFF_ACIS_SUS->size());						

		//-----------------------------------------------------------------------------
		//búsqueda de la relación en los buffers de IS en suspensión.
		for (in i1 = 0; i1 < str_sus_amount; i1++)
		{
			//-------------------------------------------------------------------------
			//si la IS a eliminar corresponde con un elemnento de los buffers.
			if (this->BUFF_ACIS_SUS->at(i1).UPCI_ID	==	this->UPCI_ID	&&
				this->BUFF_ACIS_SUS->at(i1).STR_ID	==	_lacis_id)
			{
				//---------------------------------------------------------------------
				//eliminación del elemento de los buffers de IS en suspensión.
				this->BUFF_ACIS_SUS->erase(this->BUFF_ACIS_SUS->begin() + i1);

				//---------------------------------------------------------------------
				//salida del bucle.
				break;
			}
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//decremento de la cantidad existente de estructuras.	
	--this->BUFF_ACIS_INI_AMOUNT;
	--this->BUFF_TOTAL_STR_INI_AMOUNT;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para actualizar buffer tras eliminar IS PFRLIS.
vo	UPCI_I_DS::UpdateBuffersToDeletePFRLIS(in _pfrlis_id)
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
				this->BUFF_PFRLIS_SUS->at(i1).STR_ID		==	_pfrlis_id)
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
//#4: método para actualizar buffer tras eliminar IS INDFRLIS.
vo	UPCI_I_DS::UpdateBuffersToDeleteINDFRLIS(in _indfrlis_id)
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
//#5: método para actualizar buffer tras eliminar IS INPRRLIS.
vo	UPCI_I_DS::UpdateBuffersToDeleteINPRRLIS(in _inprrlis_id)
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
vo	UPCI_I_DS::UpdateToCongruentBUFF_INIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	in	upci_candidates_present_amount		= in(this->BUFF_UPCI_ID_INIS_CAN->front().size());		//cantidad de upci candidatas presentes.	
	in	INIS_candidates_present_amount	= NULL;														//cantidad de candidatos por upci presentes.
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
			this->BUFF_UPCI_I_DS->at(upci_id_candidate).BUFF_INIS[str_id_candidate].CS_SRG = ON;

			//-------------------------------------------------------------------------
			//impresión de la estructura en estado de congruencia.
			this->Print("    > entra en estado de congruencia inis id ", str_id_candidate);
		}		
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para update de estado de actividad no congruente a estado congruente
//en estructuras presentes del buffer BUFF_ACIS mediante BUFF_ACIS_ID_CAN.
vo	UPCI_I_DS::UpdateToCongruentBUFF_ACIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	in	upci_candidates_present_amount		= in(this->BUFF_UPCI_ID_ACIS_CAN->front().size());			//cantidad de upci candidatas presentes.	
	in	ACIS_candidates_present_amount		= 0;														//cantidad de candidatos por upci presentes.
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
		upci_id_candidate					= this->BUFF_UPCI_ID_ACIS_CAN->front().at(i1);

		//-----------------------------------------------------------------------------
		//cantidad de estructuras candidatas presentes en la upci i1.
		ACIS_candidates_present_amount		= in(this->BUFF_ACIS_ID_CAN->front().at(upci_id_candidate).size());

		//-----------------------------------------------------------------------------
		//bucle para actualizar estado de congruencia de las estructuras candidatas presentes.
		for (in i2 = 0; i2 < ACIS_candidates_present_amount; i2++)
		{
			//-------------------------------------------------------------------------
			//obtención del id de la estructura candidata.
			str_id_candidate = this->BUFF_ACIS_ID_CAN->front().at(upci_id_candidate).at(i2);

			//-------------------------------------------------------------------------
			//actualización de congruencia de la estructura candidata presente i2.
			this->BUFF_UPCI_I_DS->at(upci_id_candidate).BUFF_ACIS[str_id_candidate].CS_SRG = ON;

			//-------------------------------------------------------------------------
			//impresión de la estructura en estado de congruencia.
			this->Print("    > entra en estado de congruencia lacis id ", str_id_candidate);
		}		
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para update de estado de actividad no congruente a estado congruente
//en estructuras presentes del buffer BUFF_INDFRLIS mediante BUFF_INDFRLIS_ID_CAN.
vo	UPCI_I_DS::UpdateToCongruentBUFF_INDFRLIS()
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
			this->BUFF_UPCI_I_DS->at(upci_id_candidate).BUFF_INDFRLIS[str_id_candidate].CS_SRG = ON;

			//-------------------------------------------------------------------------
			//impresión de la estructura en estado de congruencia.
			this->Print("    > entra en estado de congruencia indfrlis id ", str_id_candidate);
		}		
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para update de estado de actividad no congruente a estado congruente
//en estructuras presentes del buffer BUFF_INPRRLIS mediante BUFF_INPRRLIS_ID_CAN.
vo	UPCI_I_DS::UpdateToCongruentBUFF_INPRRLIS()
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
			this->BUFF_UPCI_I_DS->at(upci_id_candidate).BUFF_INPRRLIS[str_id_candidate].CS_SRG = ON;

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
vo	UPCI_I_DS::UpdateToNotCongruentBUFF_INIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existen estructuras candidatas anteriores, update estructuras.
	if (this->BUFF_INIS_ID_CAN->size() > 1)
	{
		//-----------------------------------------------------------------------------
		//variables auxiliares.
		in	previous_upci_candidates_amount		= in(this->BUFF_UPCI_ID_INIS_CAN->back().size());			//cantidad de upci candidatas anteriores.
		in	previous_inis_candidates_amount	= 0;														//cantidad de candidatos por upci anteriores.
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
				this->BUFF_UPCI_I_DS->at(upci_id_candidate).BUFF_INIS[str_id_candidate].CS_SRG = OFF;
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
//en estructuras anteriores del buffer BUFF_ACIS mediante BUFF_ACIS_ID_CAN.
vo	UPCI_I_DS::UpdateToNotCongruentBUFF_ACIS()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si existen estructuras candidatas anteriores, update estructuras.
	if (this->BUFF_ACIS_ID_CAN->size() > 1)
	{
		//-----------------------------------------------------------------------------
		//variables auxiliares.
		in	previous_upci_candidates_amount		= in(this->BUFF_UPCI_ID_ACIS_CAN->back().size());			//cantidad de upci candidatas anteriores.
		in	previous_lacis_candidates_amount	= 0;														//cantidad de candidatos por upci anteriores.
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
			upci_id_candidate					= this->BUFF_UPCI_ID_ACIS_CAN->back().at(i1);

			//-------------------------------------------------------------------------
			//cantidad de estructuras candidatas en la upci i1.
			previous_lacis_candidates_amount	= in(this->BUFF_ACIS_ID_CAN->back().at(upci_id_candidate).size());

			//-------------------------------------------------------------------------
			//bucle para actualizar estado de congruencia de las estructuras candidatas anteriores.
			for (in i2 = 0; i2 < previous_lacis_candidates_amount; i2++)
			{
				//---------------------------------------------------------------------
				//obtención del id de la estructura candidata.
				str_id_candidate = this->BUFF_ACIS_ID_CAN->back().at(upci_id_candidate).at(i2);

				//---------------------------------------------------------------------
				//actualización de congruencia de estructura  de la estructura candidata anterior i2.
				this->BUFF_UPCI_I_DS->at(upci_id_candidate).BUFF_ACIS[str_id_candidate].CS_SRG = OFF;
			}		
		}

		//-----------------------------------------------------------------------------
		//Clean buffer BUFF_ACIS_ID_CAN.
		this->CleanBuffersOfPreviousCandidatesACIS();
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para update el estado de actividad congruente a estado no congruente 
//en estructuras anteriores del buffer BUFF_INDFRLIS mediante BUFF_INDFRLIS_ID_CAN.
vo	UPCI_I_DS::UpdateToNotCongruentBUFF_INDFRLIS()
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
				this->BUFF_UPCI_I_DS->at(upci_id_candidate).BUFF_INDFRLIS[str_id_candidate].CS_SRG = OFF;
			}		
		}

		//-----------------------------------------------------------------------------
		//Clean buffer BUFF_INDFRLIS_ID_CAN.
		this->CleanBuffersOfPreviousCandidatesINDFRLIS();
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para update el estado de actividad congruente a estado no congruente 
//en estructuras anteriores del buffer BUFF_INPRRLIS mediante BUFF_INPRRLIS_ID_CAN.
vo	UPCI_I_DS::UpdateToNotCongruentBUFF_INPRRLIS()
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
				this->BUFF_UPCI_I_DS->at(upci_id_candidate).BUFF_INPRRLIS[str_id_candidate].CS_SRG = OFF;
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
dou	UPCI_I_DS::ActivityLevelFunction(dou _seed)
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
dou	UPCI_I_DS::ActivityLevelFunction(in _seed)
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
in	UPCI_I_DS::GetSTORAGE_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'STORAGE_FLAG'.
	return this->STORAGE_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para obtener el estado de la bandera 'SUSPENDED_ACTIONS_MAXIMIZATION_FLAG'. 
in	UPCI_I_DS::GetSUSPENDED_ACTIONS_MAXIMIZATION_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'SUSPENDED_ACTIONS_MAXIMIZATION_FLAG'.
	return *this->SUSPENDED_ACTIONS_MAXIMIZATION_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para obtener el estado de la bandera 'STRUCTURES_RECOGNITION_FLAG'. 
in	UPCI_I_DS::GetSTRUCTURES_RECOGNITION_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'STRUCTURES_RECOGNITION_FLAG'.
	return *this->STRUCTURES_RECOGNITION_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para obtener el estado de la bandera 'STRUCTURES_PROJECTIONS_FLAG'. 
in	UPCI_I_DS::GetSTRUCTURES_PROJECTIONS_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'STRUCTURES_PROJECTIONS_FLAG'.
	return *this->STRUCTURES_PROJECTIONS_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método para obtener el estado de la bandera 'KERNEL_INTEGRATION_FLAG'. 
in	UPCI_I_DS::GetKERNEL_INTEGRATION_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'KERNEL_INTEGRATION_FLAG'.
	return this->KERNEL_INTEGRATION_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#6: método para obtener el estado de la bandera 'KERNEL_CONTROL_INTEGRATION_FLAG'. 
in	UPCI_I_DS::GetKERNEL_CONTROL_INTEGRATION_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'KERNEL_CONTROL_INTEGRATION_FLAG'.
	return this->KERNEL_CONTROL_INTEGRATION_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#7: método para obtener el estado de la bandera 'KERNEL_CONTROL_INTEGRATION_FINISHED_FLAG'. 
in	UPCI_I_DS::GetKERNEL_CONTROL_INTEGRATION_FINISHED_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'KERNEL_CONTROL_INTEGRATION_FINISHED_FLAG'.
	return this->KERNEL_CONTROL_INTEGRATION_FINISHED_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#8: método para obtener el estado de la bandera 'THREAD_INTEGRATION_FLAG'.
in	UPCI_I_DS::GetTHREAD_INTEGRATION_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'THREAD_INTEGRATION_FLAG'.
	return this->THREAD_INTEGRATION_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#9: método para obtener el estado de la bandera 'THREAD_INTEGRATION_LATENCY_FLAG'. 
in	UPCI_I_DS::GetTHREAD_INTEGRATION_LATENCY_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'THREAD_INTEGRATION_LATENCY_FLAG'.
	return this->THREAD_INTEGRATION_LATENCY_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#10: método para obtener el estado de la bandera 'THREAD_INTEGRATION_FINISHED_FLAG'. 
in	UPCI_I_DS::GetTHREAD_INTEGRATION_FINISHED_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'THREAD_INTEGRATION_FINISHED_FLAG'.
	return this->THREAD_INTEGRATION_FINISHED_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#11: método para obtener el estado de la bandera 'SUSPENDED_STRUCTURES_FLAG'.
in	UPCI_I_DS::CheckSUSPENDED_STRUCTURES()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'SUSPENDED_STRUCTURES_FLAG'.
	return this->SUSPENDED_STRUCTURES_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#12: método para obtener el estado de al bandera 'NEW_INPUT_FLAG'.
in	UPCI_I_DS::GetNEW_INPUT_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'NEW_INPUT_FLAG'.
	return this->NEW_INPUT_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#13: método para obtener el estado de al bandera 'NEW_INPUT_DIFFERENCE_RELATION_FLAG'.
in	UPCI_I_DS::GetNEW_INPUT_DIFFERENCE_RELATION_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'NEW_INPUT_DIFFERENCE_RELATION_FLAG'.
	return this->NEW_INPUT_DIFFERENCE_RELATION_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#14: método para obtener el estado de al bandera 'CLOSE_ACTIVE_THREADS_FLAG'.
in	UPCI_I_DS::GetCLOSE_ACTIVE_THREADS_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'CLOSE_ACTIVE_THREADS_FLAG'.
	return *this->CLOSE_ACTIVE_THREADS_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#15: método para obtener el estado de al bandera 'PAUSE_ACTIVE_THREADS_FLAG'.
in	UPCI_I_DS::GetPAUSE_ACTIVE_THREADS_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'PAUSE_ACTIVE_THREADS_FLAG'.
	return *this->PAUSE_ACTIVE_THREADS_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#16: método para obtener el estado de la bandera 'PRINT_FLAG'.
in	UPCI_I_DS::GetPRINT_FLAG()
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
//método Get para obtener cantidad de upci en el grupo.
in	UPCI_I_DS::GetAmountUpcGro()
{
	//---------------------------------------------------------------------------------
	//retorno de la cantidad de upci existentes en el grupo.
	return in(this->BUFF_UPCI_I_DS->size());
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para obtener el tipo de evaluación de transiciones de entradas.
in	UPCI_I_DS::GetInputTransitionEvaluationTypeIn(dou _input_evaluation, dou _input_evaluation_difference)
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
	else if (_input_evaluation_difference < -this->TRANSITION_EVALUATION_THRESHOLD)
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
	//---------------------------------------------------------------------------------
	//si la transición de evaluación es neutral y la evaluación es negativa, entonces.
	else if (_input_evaluation_difference	>=	-this->TRANSITION_EVALUATION_THRESHOLD	&&
			 _input_evaluation_difference	<=	this->TRANSITION_EVALUATION_THRESHOLD	&&
			 _input_evaluation				<	0)
	{
		//-----------------------------------------------------------------------------
		//devolver transición neutral negativa.
		return NEUTRAL_NEGATIVE_TRANSITION;
	}	

	//---------------------------------------------------------------------------------
	//retorno fallido.
	return -1;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para obtener el tipo de evaluación de transiciones de entradas.
st	UPCI_I_DS::GetInputTransitionEvaluationTypeSt(dou _input_evaluation, dou _input_evaluation_difference)
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
	else if (_input_evaluation_difference < -this->TRANSITION_EVALUATION_THRESHOLD)
	{
		//-----------------------------------------------------------------------------
		//devolver transición negativa.
		return "NEGATIVE_TRANSITION";
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la transición es neutral y la evaluación es positiva, entonces.
	if (_input_evaluation_difference  >=  -this->TRANSITION_EVALUATION_THRESHOLD	&&
		_input_evaluation_difference  <=  this->TRANSITION_EVALUATION_THRESHOLD	&&
		_input_evaluation			  >	  0)
	{
		//-----------------------------------------------------------------------------
		//devolver transición neutral positiva.
		return "NEUTRAL_POSITIVE_TRANSITION";
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la transición de evaluación es neutral y la evaluación es negativa, entonces.
	else if (_input_evaluation_difference	>=	-this->TRANSITION_EVALUATION_THRESHOLD	&&
			 _input_evaluation_difference	<=	this->TRANSITION_EVALUATION_THRESHOLD	&&
			 _input_evaluation				<	0)
	{
		//-----------------------------------------------------------------------------
		//devolver transición neutral negativa.
		return "NEUTRAL_NEGATIVE_TRANSITION";
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
//#1: método para obtener acción inversa de una acción.
st	UPCI_I_DS::GetInverseAction(st _action_register)
{
	//---------------------------------------------------------------------------------
	//cantidad de acciones posibles auxiliares.
	in	supported_actions_amount_aux = *this->BUFF_SUPPORTED_ACTIONS_AMOUNT / 2;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para obtener el acción inversa.
	for (in i1 = 0; i1 < supported_actions_amount_aux; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención de la acción inversa.
		if (_action_register == this->BUFF_SET_OF_SUPPORTED_ACTIONS->at(2*i1))	return this->BUFF_SET_OF_SUPPORTED_ACTIONS->at(2*i1 + 1);
	}	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para obtener el acción inversa.
	for (in i1 = 0; i1 < supported_actions_amount_aux; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención de la acción inversa.
		if (_action_register == this->BUFF_SET_OF_SUPPORTED_ACTIONS->at(2 * i1 + 1))	return this->BUFF_SET_OF_SUPPORTED_ACTIONS->at(2 * i1);
	}

	//---------------------------------------------------------------------------------
	//retorno por defecto.
	return "";
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método Get para obtener el estado de actividad de la estructura activada presente.
in	UPCI_I_DS::GetCurrentStrActiveStatus()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	in upci_id_str_activated	= this->BUFF_STR_ACTIVATED[0].UPCI_ID;						//id de la upci de la estructura activada.
	in str_id_activated			= this->BUFF_STR_ACTIVATED[0].STR_ID;						//id de la estructura activada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura activada presente está definida.
	if (this->BUFF_STR_ACTIVATED[0].STR_ID != -1)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//búsqueda del tipo de estructura.
		switch (this->BUFF_STR_ACTIVATED[0].STR_TYPE)
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la estructura es del tipo entrada.
			case	INIS_TYPE:

				//---------------------------------------------------------------------
				//si la estructura posee nivel de actividad.
				if (this->BUFF_UPCI_I_DS->at(upci_id_str_activated).BUFF_INIS[str_id_activated].AL_SRG > 0)	return ON;
				else																							return OFF;

				//---------------------------------------------------------------------
				//salida del bucle.
				break;

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la estructura es del tipo acción.
			case	ACIS_TYPE:
				
				//---------------------------------------------------------------------
				//si la estructura posee nivel de actividad.
				if (this->BUFF_UPCI_I_DS->at(upci_id_str_activated).BUFF_ACIS[str_id_activated].AL_SRG > 0)	return ON;
				else																						return OFF;

				//---------------------------------------------------------------------
				//salida del bucle.
				break;

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si no cumple con ninguna condición.
			default:

				//---------------------------------------------------------------------
				//no existe correspondencia.
				return OFF;
				break;
		}
	}
	else
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//no existe correspondencia.
		return OFF;
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método Get para obtener el estado de actividad de la estructura activada pasado.
in	UPCI_I_DS::GetPastStrActiveStatus()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	in upci_id_str_activated	= this->BUFF_STR_ACTIVATED[1].UPCI_ID;						//id de la upci de la estructura activada.
	in str_id_activated			= this->BUFF_STR_ACTIVATED[1].STR_ID;						//id de la estructura activada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si la estructura activada pasado está definida.
	if (this->BUFF_STR_ACTIVATED[1].STR_ID != -1)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//búsqueda del tipo de estructura.
		switch (this->BUFF_STR_ACTIVATED[1].STR_TYPE)
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la estructura es del tipo entrada.
			case	INIS_TYPE:

				//---------------------------------------------------------------------
				//si la estructura posee nivel de actividad.
				if (this->BUFF_UPCI_I_DS->at(upci_id_str_activated).BUFF_INIS[str_id_activated].AL_SRG > 0)	return ON;
				else																							return OFF;
				
				//---------------------------------------------------------------------
				//salida del bucle.
				break;

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la estructura es del tipo acción.
			case	ACIS_TYPE:
				
				//---------------------------------------------------------------------
				//si la estructura posee nivel de actividad.
				if (this->BUFF_UPCI_I_DS->at(upci_id_str_activated).BUFF_ACIS[str_id_activated].AL_SRG > 0)	return ON;
				else																						return OFF;

				//---------------------------------------------------------------------
				//salida del bucle.
				break;

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si no cumple con ninguna condición.
			default:

				//---------------------------------------------------------------------
				//no existe correspondencia.
				return OFF;
				break;
		}
	}
	else
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//no existe correspondencia.
		return OFF;
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//método para obtener el máximo nivel de actividad.
dou	UPCI_I_DS::GetMaxActivityLevel()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//búsqueda del tipo estructura con el máximo nivel de actividad.
	switch (this->BUFF_STR_MAX_AL->STR_TYPE)
	{
		//-----------------------------------------------------------------------------
		//si la estructura es del tipo entrada.
		case	INIS_TYPE:
			return (this->BUFF_UPCI_I_DS->at(this->BUFF_STR_MAX_AL->UPCI_ID).BUFF_INIS[this->BUFF_STR_MAX_AL->STR_ID].AL_SRG);
			break;

		//-----------------------------------------------------------------------------
		//si la estructura es del tipo acción.
		case	ACIS_TYPE:
			return (this->BUFF_UPCI_I_DS->at(this->BUFF_STR_MAX_AL->UPCI_ID).BUFF_ACIS[this->BUFF_STR_MAX_AL->STR_ID].AL_SRG);
			break;

		//-----------------------------------------------------------------------------
		//si no cumple con ninguna condición.
		default:
			return FAILURE;
			break;
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para obtener el contador de iteraciones del kernel.
in	UPCI_I_DS::GetKERNEL_ITERATION_COUNTER()
{
	//---------------------------------------------------------------------------------
	//retorno del contador de iteraciones del kernel.
	return this->KERNEL_ITERATION_COUNTER;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para obtener el contador de iteraciones del Hilo.
in	UPCI_I_DS::GetTHREAD_ITERATION_COUNTER()
{
	//---------------------------------------------------------------------------------
	//retorno del contador de iteraciones del Hilo.
	return this->THREAD_ITERATION_COUNTER;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para obtener el contador de diferenciaciones globales de estructuras.
in	UPCI_I_DS::GetGLOBAL_DIFFERENTIATION_COUNTER()
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
//#1: método para setear la bandera 'STORAGE_FLAG'. 
vo	UPCI_I_DS::SetSTORAGE_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'STORAGE_FLAG'.
	this->STORAGE_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para setear el estado de la bandera 'SUSPENDED_ACTIONS_MAXIMIZATION_FLAG'. 
vo	UPCI_I_DS::SetSUSPENDED_ACTIONS_MAXIMIZATION_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'SUSPENDED_ACTIONS_MAXIMIZATION_FLAG'.
	*this->SUSPENDED_ACTIONS_MAXIMIZATION_FLAG	= _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para setear el estado de la bandera 'STRUCTURES_RECOGNITION_FLAG'. 
vo	UPCI_I_DS::SetSTRUCTURES_RECOGNITION_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'STRUCTURES_RECOGNITION_FLAG'.
	*this->STRUCTURES_RECOGNITION_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para setear el estado de la bandera 'STRUCTURES_PROJECTIONS_FLAG'. 
vo	UPCI_I_DS::SetSTRUCTURES_PROJECTIONS_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'STRUCTURES_PROJECTIONS_FLAG'.
	*this->STRUCTURES_PROJECTIONS_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método para setear la bandera 'KERNEL_INTEGRATION_FLAG';
vo	UPCI_I_DS::SetKERNEL_INTEGRATION_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'KERNEL_INTEGRATION_FLAG'.
	this->KERNEL_INTEGRATION_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#6: método para setear la bandera 'KERNEL_CONTROL_INTEGRATION_FLAG'. 
vo	UPCI_I_DS::SetKERNEL_CONTROL_INTEGRATION_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'KERNEL_CONTROL_INTEGRATION_FLAG'.
	this->KERNEL_CONTROL_INTEGRATION_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#7: método para setear la bandera 'KERNEL_CONTROL_INTEGRATION_FINISHED_FLAG'. 
vo	UPCI_I_DS::SetKERNEL_CONTROL_INTEGRATION_FINISHED_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'KERNEL_CONTROL_INTEGRATION_FINISHED_FLAG'.
	this->KERNEL_CONTROL_INTEGRATION_FINISHED_FLAG	= _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#8: método para setear la bandera 'THREAD_INTEGRATION_FLAG'. 
vo	UPCI_I_DS::SetTHREAD_INTEGRATION_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'THREAD_INTEGRATION_FLAG'.
	this->THREAD_INTEGRATION_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#9: método para setear la bandera 'THREAD_INTEGRATION_LATENCY_FLAG'. 
vo	UPCI_I_DS::SetTHREAD_INTEGRATION_LATENCY_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'THREAD_INTEGRATION_LATENCY_FLAG'.
	this->THREAD_INTEGRATION_LATENCY_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#10: método para setear la bandera 'THREAD_INTEGRATION_FINISHED_FLAG'. 
vo	UPCI_I_DS::SetTHREAD_INTEGRATION_FINISHED_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'THREAD_INTEGRATION_FINISHED_FLAG'.
	this->THREAD_INTEGRATION_FINISHED_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#11: método para setear la bandera 'SUSPENDED_STRUCTURES_FLAG'. 
vo UPCI_I_DS::SetSUSPENDED_STRUCTURES_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'SUSPENDED_STRUCTURES_FLAG'.
	this->SUSPENDED_STRUCTURES_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#12: método para setear la bandera 'NEW_INPUT_FLAG'.
vo	UPCI_I_DS::SetNEW_INPUT_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'NEW_INPUT_FLAG'.
	this->NEW_INPUT_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#13: método para setear la bandera 'NEW_INPUT_DIFFERENCE_RELATION_FLAG'.
vo	UPCI_I_DS::SetNEW_INPUT_DIFFERENCE_RELATION_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'NEW_INPUT_DIFFERENCE_RELATION_FLAG'.
	this->NEW_INPUT_DIFFERENCE_RELATION_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#14: método para setear el estado de al bandera 'CLOSE_ACTIVE_THREADS_FLAG'.
vo	UPCI_I_DS::SetCLOSE_ACTIVE_THREADS_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'CLOSE_ACTIVE_THREADS_FLAG'.
	*this->CLOSE_ACTIVE_THREADS_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#15: método para setear el estado de al bandera 'PAUSE_ACTIVE_THREADS_FLAG'.
vo	UPCI_I_DS::SetPAUSE_ACTIVE_THREADS_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'PAUSE_ACTIVE_THREADS_FLAG'.
	*this->PAUSE_ACTIVE_THREADS_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#16: método para setear la bandera 'PRINT_FLAG'.
vo	UPCI_I_DS::SetPRINT_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'PRINT_FLAG'.
	this->PRINT_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para setear estructura INIS con máximo nivel de evaluación.
vo	UPCI_I_DS::SetBUFF_STR_MAX_EVAL(in _inis_id, dou _max_evaluation)
{
	//---------------------------------------------------------------------------------
	//seteo de la máxima evaluación de entrada.
	this->BUFF_STR_MAX_EVAL->Set(this->UPCI_ID, _inis_id);
	*this->BUFF_MAX_EVALUATION	= _max_evaluation;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para setear estructura con máximo nivel de actividad.
vo	UPCI_I_DS::SetBUFF_STR_MAX_AL(in _str_id, in _str_type, dou _max_activity_level)
{
	//---------------------------------------------------------------------------------
	//seteo del máximo nivel de actividad.
	this->BUFF_STR_MAX_AL->Set(this->UPCI_ID, _str_id, _str_type);
	*this->BUFF_MAX_ACTIVITY_LEVEL	= _max_activity_level;	
}

//-------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------- 
//#3: método para setear estructura con máximo fortaleza de la relación
vo	UPCI_I_DS::SetBUFF_STR_MAX_RS(in _str_id, in _str_type, in _max_activity_counter)
{
	//---------------------------------------------------------------------------------
	//seteo del máximo fortaleza de la relación.
	this->BUFF_STR_MAX_RS->Set(this->UPCI_ID, _str_id, _str_type);
	*this->BUFF_MAX_RELATION_STRENGTH	= _max_activity_counter;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para setear estructura activada.
vo	UPCI_I_DS::SetBUFF_STR_ACTIVATED(in _str_id, in _str_type)
{
	//---------------------------------------------------------------------------------
	//seteo de la estructura activada anterior.
	this->BUFF_STR_ACTIVATED[1].Set(this->BUFF_STR_ACTIVATED[0].UPCI_ID, this->BUFF_STR_ACTIVATED[0].STR_ID, this->BUFF_STR_ACTIVATED[0].STR_TYPE);

	//---------------------------------------------------------------------------------
	//seteo de la estructura activada presente.
	this->BUFF_STR_ACTIVATED[0].Set(this->UPCI_ID, _str_id, _str_type);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método para setear estructura INIS activada.
vo	UPCI_I_DS::SetBUFF_INIS_ACTIVATED(in _inis_id)
{
	//---------------------------------------------------------------------------------
	//seteo de la estructura activada general.
	this->SetBUFF_STR_ACTIVATED(_inis_id, INIS_TYPE);

	//---------------------------------------------------------------------------------
	//seteo de la estructura activada anterior.
	this->BUFF_INIS_ACTIVATED[1].Set(this->BUFF_INIS_ACTIVATED[0].UPCI_ID, this->BUFF_INIS_ACTIVATED[0].STR_ID);

	//---------------------------------------------------------------------------------
	//seteo de la estructura activada presente.
	this->BUFF_INIS_ACTIVATED[0].Set(this->UPCI_ID, _inis_id);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#6: método para setear estructura ACIS activada.
vo	UPCI_I_DS::SetBUFF_ACIS_ACTIVATED(in _lacis_id)
{
	//---------------------------------------------------------------------------------
	//seteo de la estructura activada general.
	this->SetBUFF_STR_ACTIVATED(_lacis_id, ACIS_TYPE);

	//---------------------------------------------------------------------------------
	//seteo del flujo de la estructura activada anterior.
	this->BUFF_ACIS_ACTIVATED[1].Set(this->BUFF_ACIS_ACTIVATED[0].UPCI_ID, this->BUFF_ACIS_ACTIVATED[0].STR_ID);

	//---------------------------------------------------------------------------------
	//seteo del flujo de la estructura activada presente.
	this->BUFF_ACIS_ACTIVATED[0].Set(this->UPCI_ID, _lacis_id);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#7: método para setear estructura INIS creada.
vo	UPCI_I_DS::SetBUFF_INIS_CRE(in _inis_id)
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
//#8: método para setear estructura ACIS creada.
vo	UPCI_I_DS::SetBUFF_ACIS_CRE(in _lacis_id)
{
	//---------------------------------------------------------------------------------
	//seteo de la estructura creada anterior.
	this->BUFF_ACIS_CRE[1].Set(this->BUFF_ACIS_CRE[0].UPCI_ID, this->BUFF_ACIS_CRE[0].STR_ID);

	//---------------------------------------------------------------------------------
	//seteo de la estructura creada presente.
	this->BUFF_ACIS_CRE[0].Set(this->UPCI_ID, _lacis_id);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#9: método para setear estructura PFRLIS creada.
vo	UPCI_I_DS::SetBUFF_PFRLIS_CRE(in _pfrlis_id)
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
//#10: método para setear estructura INDFRLIS creada.
vo	UPCI_I_DS::SetBUFF_INDFRLIS_CRE(in _indfrlis_id)
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
//#11: método para setear estructura INPRRLIS creada.
vo	UPCI_I_DS::SetBUFF_INPRRLIS_CRE(in _inprrlis_id)
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
//#12: método para setear estructuras en suspensión.
vo	UPCI_I_DS::SetBUFF_STR_SUS(in _str_id, in _str_type)
{
	//---------------------------------------------------------------------------------
	//buffer auxiliar.
	this->BUFF_STR_SUS_AUX.Set(this->UPCI_ID, _str_id);

	//---------------------------------------------------------------------------------
	//seteo de la estructura en suspensión.
	if		(_str_type == INIS_TYPE)		this->BUFF_INIS_SUS->push_back(this->BUFF_STR_SUS_AUX);
	else if (_str_type == ACIS_TYPE)		this->BUFF_ACIS_SUS->push_back(this->BUFF_STR_SUS_AUX);
	else if (_str_type == PFRLIS_TYPE)		this->BUFF_PFRLIS_SUS->push_back(this->BUFF_STR_SUS_AUX);
	else if (_str_type == INDFRLIS_TYPE)	this->BUFF_INDFRLIS_SUS->push_back(this->BUFF_STR_SUS_AUX);

	//---------------------------------------------------------------------------------
	//limpieza del buffer auxiliar.
	this->BUFF_STR_SUS_AUX.Clean();

	//---------------------------------------------------------------------------------
	//se activa la bandera de la existencia de estructuras en estado de suspendido.
	this->SetSUSPENDED_STRUCTURES_FLAG(ON);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método Print para debug.
vo	UPCI_I_DS::Print(st _message)
{
	//---------------------------------------------------------------------------------
	//impresión de mensaje.
	if (this->GetPRINT_FLAG() == ON) cout << _message << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método Print para debug.
vo	UPCI_I_DS::Print(st _message, dou _data)
{
	//---------------------------------------------------------------------------------
	//impresión de mensaje.
	if (this->GetPRINT_FLAG() == ON) cout << _message << ": " << _data<<endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método Print para debug.
vo	UPCI_I_DS::Print(st _message, st _data)
{
	//---------------------------------------------------------------------------------
	//impresión de mensaje.
	if (this->GetPRINT_FLAG() == ON) cout << _message << ": " << _data << endl;
}