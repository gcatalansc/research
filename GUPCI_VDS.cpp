//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
Class Name	: 	  GUPCI_SDS (Limted Group Units Cognitive Processes, type 'DS').
Date	    :	  12:58 pm 12-06-2017.
Diseñador   :	  Gustavo Catalán Ulloa.
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include "GUPCI_SDS.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//espacio de nombres.
using namespace UPC;
using namespace std;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método constructor "1".
GUPCI_SDS::GUPCI_SDS()
{	

}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método constructor "2" para cargar desde interfaz.
GUPCI_SDS::GUPCI_SDS(in _gupci_id, in _gupci_nat, in _upci_amount, in _set_signal_flag, in _seed, dest &_buff_set_of_supported_actions, UPCI_SDS_ARG &_upci_i_ds_arg)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para bandera de almacenamiento.
	in	STORAGE_FLAG							=	NULL;										

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## PARÁMETROS ################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de parámetros de gupci.
	this->GUPCI_ID								=	_gupci_id;									//id de la gupci.
	this->GUPCI_NAT								=	_gupci_nat;									//naturaleza de la unidad ('a','b','c'...'z').	
	this->UPCI_AMOUNT							=	_upci_amount;								//cantidad de upci por grupo.		

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## BANDERAS ##################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de banderas para funcionalidades.
	this->SUSPENDED_ACTIONS_MAXIMIZATION_FLAG	=	OFF;										//bandera para utilizar reactivación acción suspendida con máxima asociación positiva.
	this->STRUCTURES_RECOGNITION_FLAG			=	OFF;										//bandrea para utilizar reconocimiento de estructuras.
	this->STRUCTURES_PROJECTIONS_FLAG			=	OFF;										//bandera para utilizar proyección de estructuras.

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//inicialización de banderas para threads activos.
	this->CLOSE_ACTIVE_THREADS_FLAG				=	OFF;										//bandera para cerrar threads activos.
	this->PAUSE_ACTIVE_THREADS_FLAG				=	OFF;										//bandera para pausar threads activos.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de la bandera de seteo de señales de la gupci.
	this->SET_SIGNAL_FLAG						=	_set_signal_flag;		

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################### BUFFERS #####################################	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización del id de la upc con almacenamiento activo.
	this->BUFF_UPCI_ID_STORAGE_FLAG_ACT			=	0;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de buffers para almacenar registros.
	this->BUFF_IN_RG							=	NULL;										//buffer para registro de entrada.
	this->BUFF_EV_RG							=	NULL;										//buffer para registro de evaluación de entrada.
	this->BUFF_AC_RG							=	"";											//buffer para registro de acción.
	this->BUFF_IN_DIF_RG						=	NULL;										//buffer para registro de diferencia de entradas.
	this->BUFF_IN_PRO_RG						=	NULL;										//buffer para registro de proporción de diferencia de entradas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de buffers para acciones.
	this->BUFF_SET_OF_SUPPORTED_ACTIONS			=	_buff_set_of_supported_actions;				//buffer para el conjunto de acciones soportadas.
	this->BUFF_SUPPORTED_ACTIONS_AMOUNT			=	in(_buff_set_of_supported_actions.size());	//buffer para la cantidad de acciones soportadas.
	
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//inicialización de buffer para la máxima evaluación.
	this->BUFF_MAX_EVALUATION					=	NULL;										

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//inicialización de buffer para el máximo nivel de actividad.
	this->BUFF_MAX_ACTIVITY_LEVEL				=	NULL;										

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//inicialización de buffer para el máximo fortaleza de la relación.
	this->BUFF_MAX_RELATION_STRENGTH			=	NULL;					

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//inicialización de buffer para índice de relación utilizada en reconocimiento.
	this->BUFF_RL_INDEX_USED_IN_RECOGNITION		=	-1;

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################# CONTADORES ####################################

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de contador de iteraciones de la gupci.
	this->GUPCI_ITERATION_COUNTER				=	0;	

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//############################ VARIABLES AUXILIARES ############################### 

	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	//semilla para generación números pseudo aleatorios.
	this->SEED									= _seed;
	
	//#################################################################################
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//########################### INICIALIZACIÓN DE GUPCI #############################

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de las upci.
	this->BUFF_UPCI_I_DS.resize(this->UPCI_AMOUNT);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de punteros para buffers de las upci.
	_upci_i_ds_arg.SetPtrBuff(&this->SUSPENDED_ACTIONS_MAXIMIZATION_FLAG,
							 &this->STRUCTURES_RECOGNITION_FLAG,
							 &this->STRUCTURES_PROJECTIONS_FLAG,
							 &this->CLOSE_ACTIVE_THREADS_FLAG,
							 &this->PAUSE_ACTIVE_THREADS_FLAG,
							 &this->GUPCI_ID,
							 &this->BUFF_UPCI_I_DS,
							 &this->BUFF_UPCI_ID_STORAGE_FLAG_ACT,
							 &this->BUFF_IN_RG,
							 &this->BUFF_EV_RG,
							 &this->BUFF_AC_RG,
							 &this->BUFF_IN_DIF_RG,
							 &this->BUFF_IN_PRO_RG,
							 &this->BUFF_SET_OF_SUPPORTED_ACTIONS,
							 &this->BUFF_SUPPORTED_ACTIONS_AMOUNT,
							 &this->BUFF_STR_MAX_EVAL,
							 &this->BUFF_MAX_EVALUATION,
							 &this->BUFF_STR_MAX_AL,
							 &this->BUFF_MAX_ACTIVITY_LEVEL,	
							 &this->BUFF_STR_MAX_RS,
							 &this->BUFF_MAX_RELATION_STRENGTH,
						     this->BUFF_STR_ACTIVATED,							 
							 this->BUFF_INIS_ACTIVATED,
							 this->BUFF_ACIS_ACTIVATED,
							 this->BUFF_EXECUTE_ACIS,
							 &this->BUFF_RL_INDEX_USED_IN_RECOGNITION,
							 &this->BUFF_INIS_SUS,
							 &this->BUFF_ACIS_SUS,
							 &this->BUFF_PFRLIS_SUS,
							 &this->BUFF_INDFRLIS_SUS,
							 this->BUFF_INIS_CRE,
							 this->BUFF_ACIS_CRE,
							 this->BUFF_PFRLIS_CRE,
							 this->BUFF_INDFRLIS_CRE,
							 this->BUFF_INPRRLIS_CRE,	
							 &this->BUFF_INIS_RE,
							 &this->BUFF_ACIS_RE,
							 &this->BUFF_INDFRLIS_RE,
							 &this->BUFF_INPRRLIS_RE,
							 &this->BUFF_UPCI_ID_INIS_CAN,
							 &this->BUFF_UPCI_ID_ACIS_CAN,
							 &this->BUFF_UPCI_ID_INDFRLIS_CAN,
							 &this->BUFF_UPCI_ID_INPRRLIS_CAN,
							 &this->BUFF_INIS_ID_CAN,
							 &this->BUFF_ACIS_ID_CAN,
							 &this->BUFF_INDFRLIS_ID_CAN,
							 &this->BUFF_INPRRLIS_ID_CAN);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializar upci.
	for (in i1 = 0; i1 < this->UPCI_AMOUNT; i1++)
	{
		//-----------------------------------------------------------------------------
		//seteo de la upci que almacenará las entradas inicialmente.
		if (this->BUFF_UPCI_ID_STORAGE_FLAG_ACT == i1) STORAGE_FLAG = 1; else STORAGE_FLAG = 0;

		//-----------------------------------------------------------------------------
		//inicialización de upci.
		this->BUFF_UPCI_I_DS.at(i1).Initialize(i1, this->GUPCI_NAT, this->SEED + i1, STORAGE_FLAG, _upci_i_ds_arg);
	}	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método destructor.
GUPCI_SDS::~GUPCI_SDS()
{
	//---------------------------------------------------------------------------------
	//limpieza de gupc.
	this->Clean();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método de inicialización para cargar desde archivo.
in GUPCI_SDS::Initialize(in _upci_amount, UPCI_SDS_ARG &_upci_i_ds_arg)
{
	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## PARÁMETROS ################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//cantidad de upci.	
	this->UPCI_AMOUNT							=	_upci_amount;				

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## BANDERAS ##################################### 

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//inicialización de banderas para threads activos.
	this->CLOSE_ACTIVE_THREADS_FLAG				=	OFF;									//bandera para cerrar threads activos.
	this->PAUSE_ACTIVE_THREADS_FLAG				=	OFF;									//bandera para pausar threads activos.

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################### BUFFERS #####################################

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de buffers para almacenar registros.
	this->BUFF_IN_RG							=	NULL;									//buffer para registro de entrada.
	this->BUFF_EV_RG							=	NULL;									//buffer para registro de evaluación de entrada.
	this->BUFF_AC_RG							=	"";										//buffer para registro de acción.
	this->BUFF_IN_DIF_RG						=	NULL;									//buffer para registro de diferencia de entradas.
	this->BUFF_IN_PRO_RG						=	NULL;									//buffer para registro de proporción de diferencia de entradas.
		
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//inicialización de buffer para la máxima evaluación.
	this->BUFF_MAX_EVALUATION					=	NULL;										

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//inicialización de buffer para el máximo nivel de actividad.
	this->BUFF_MAX_ACTIVITY_LEVEL				=	NULL;										

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//inicialización de buffer para el máximo fortaleza de la relación.
	this->BUFF_MAX_RELATION_STRENGTH			=	NULL;					

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//inicialización de buffer para índice de relación utilizada en reconocimiento.
	this->BUFF_RL_INDEX_USED_IN_RECOGNITION		=	-1;

	//#################################################################################
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//########################### INICIALIZACIÓN DE GUPCI #############################

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de las upci.
	this->BUFF_UPCI_I_DS.resize(this->UPCI_AMOUNT);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de punteros para buffers de las upci.
	_upci_i_ds_arg.SetPtrBuff(&this->SUSPENDED_ACTIONS_MAXIMIZATION_FLAG,
							 &this->STRUCTURES_RECOGNITION_FLAG,
							 &this->STRUCTURES_PROJECTIONS_FLAG,
							 &this->CLOSE_ACTIVE_THREADS_FLAG,
							 &this->PAUSE_ACTIVE_THREADS_FLAG,
							 &this->GUPCI_ID,
							 &this->BUFF_UPCI_I_DS,
							 &this->BUFF_UPCI_ID_STORAGE_FLAG_ACT,
							 &this->BUFF_IN_RG,
							 &this->BUFF_EV_RG,
							 &this->BUFF_AC_RG,
							 &this->BUFF_IN_DIF_RG,
							 &this->BUFF_IN_PRO_RG,
							 &this->BUFF_SET_OF_SUPPORTED_ACTIONS,
							 &this->BUFF_SUPPORTED_ACTIONS_AMOUNT,
							 &this->BUFF_STR_MAX_EVAL,
							 &this->BUFF_MAX_EVALUATION,
							 &this->BUFF_STR_MAX_AL,
							 &this->BUFF_MAX_ACTIVITY_LEVEL,	
							 &this->BUFF_STR_MAX_RS,
							 &this->BUFF_MAX_RELATION_STRENGTH,
						     this->BUFF_STR_ACTIVATED,							 
							 this->BUFF_INIS_ACTIVATED,
							 this->BUFF_ACIS_ACTIVATED,
							 this->BUFF_EXECUTE_ACIS,
							 &this->BUFF_RL_INDEX_USED_IN_RECOGNITION,
							 &this->BUFF_INIS_SUS,
							 &this->BUFF_ACIS_SUS,
							 &this->BUFF_PFRLIS_SUS,
							 &this->BUFF_INDFRLIS_SUS,
							 this->BUFF_INIS_CRE,
							 this->BUFF_ACIS_CRE,
							 this->BUFF_PFRLIS_CRE,
							 this->BUFF_INDFRLIS_CRE,
							 this->BUFF_INPRRLIS_CRE,	
							 &this->BUFF_INIS_RE,
							 &this->BUFF_ACIS_RE,
							 &this->BUFF_INDFRLIS_RE,
							 &this->BUFF_INPRRLIS_RE,
							 &this->BUFF_UPCI_ID_INIS_CAN,
							 &this->BUFF_UPCI_ID_ACIS_CAN,
							 &this->BUFF_UPCI_ID_INDFRLIS_CAN,
							 &this->BUFF_UPCI_ID_INPRRLIS_CAN,
							 &this->BUFF_INIS_ID_CAN,
							 &this->BUFF_ACIS_ID_CAN,
							 &this->BUFF_INDFRLIS_ID_CAN,
							 &this->BUFF_INPRRLIS_ID_CAN);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializar upci.
	for (in i1 = 0; i1 < this->UPCI_AMOUNT; i1++)
	{	
		//-----------------------------------------------------------------------------
		//inicialización de upci.
		this->BUFF_UPCI_I_DS.at(i1).Initialize(this->GUPCI_NAT, _upci_i_ds_arg);
	}

	//---------------------------------------------------------------------------------
	//successful execution.
	return SUCCESS;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método de inicialización para cargar desde interfaz.
in GUPCI_SDS::Initialize(in _gupci_id, in _gupci_nat, in _upci_amount, in _set_signal_flag, in _seed, dest &_buff_set_of_supported_actions, UPCI_SDS_ARG &_upci_i_ds_arg)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares para bandera de almacenamiento.
	in	STORAGE_FLAG							=	NULL;

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## PARÁMETROS ################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de parámetros de gupci.
	this->GUPCI_ID								=	_gupci_id;									//id de la gupci.
	this->GUPCI_NAT								=	_gupci_nat;									//naturaleza de la unidad ('a','b','c'...'z').	
	this->UPCI_AMOUNT							=	_upci_amount;								//cantidad de upci.	

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## BANDERAS ##################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización banderas para funcionalidades.
	this->SUSPENDED_ACTIONS_MAXIMIZATION_FLAG	=	ON;											//bandera para utilizar reactivación acción suspendida con máxima asociación positiva.
	this->STRUCTURES_RECOGNITION_FLAG			=	OFF;										//bandrea para utilizar reconocimiento de estructuras.
	this->STRUCTURES_PROJECTIONS_FLAG			=	OFF;										//bandera para utilizar proyección de estructuras.	

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//inicialización de banderas para threads activos.
	this->CLOSE_ACTIVE_THREADS_FLAG				=	OFF;										//bandera para cerrar threads activos.
	this->PAUSE_ACTIVE_THREADS_FLAG				=	OFF;										//bandera para pausar threads activos.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización de la bandera de seteo de señales de la gupci.
	this->SET_SIGNAL_FLAG						=	_set_signal_flag;	

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################### BUFFERS #####################################	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización del id de la upc con almacenamiento activo.
	this->BUFF_UPCI_ID_STORAGE_FLAG_ACT			=	0;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de buffers para almacenar registros.
	this->BUFF_IN_RG							=	NULL;										//buffer para registro de entrada.
	this->BUFF_EV_RG							=	NULL;										//buffer para registro de evaluación de entrada.
	this->BUFF_AC_RG							=	"";											//buffer para registro de acción.
	this->BUFF_IN_DIF_RG						=	NULL;										//buffer para registro de diferencia de entradas.
	this->BUFF_IN_PRO_RG						=	NULL;										//buffer para registro de proporción de diferencia de entradas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de buffers para acciones.
	this->BUFF_SET_OF_SUPPORTED_ACTIONS			=	_buff_set_of_supported_actions;				//buffer para el conjunto de acciones soportadas.
	this->BUFF_SUPPORTED_ACTIONS_AMOUNT			=	in(_buff_set_of_supported_actions.size());	//buffer para la cantidad de acciones soportadas.
	
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//inicialización de buffer para la máxima evaluación.
	this->BUFF_MAX_EVALUATION					=	NULL;										

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//inicialización de buffer para el máximo nivel de actividad.
	this->BUFF_MAX_ACTIVITY_LEVEL				=	NULL;										

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//inicialización de buffer para el máximo fortaleza de la relación.
	this->BUFF_MAX_RELATION_STRENGTH			=	NULL;					

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//inicialización de buffer para índice de relación utilizada en reconocimiento.
	this->BUFF_RL_INDEX_USED_IN_RECOGNITION		= -1;

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################# CONTADORES ####################################

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de contador de iteraciones de la gupci.
	this->GUPCI_ITERATION_COUNTER				=	0;	

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//############################ VARIABLES AUXILIARES ############################### 

	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	//semilla para generación números pseudo aleatorios.
	this->SEED									= _seed;
	
	//#################################################################################
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//########################### INICIALIZACIÓN DE GUPCI #############################

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de las upci.
	this->BUFF_UPCI_I_DS.resize(this->UPCI_AMOUNT);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de punteros para buffers de las upci.
	_upci_i_ds_arg.SetPtrBuff(&this->SUSPENDED_ACTIONS_MAXIMIZATION_FLAG,
							 &this->STRUCTURES_RECOGNITION_FLAG,
							 &this->STRUCTURES_PROJECTIONS_FLAG,
							 &this->CLOSE_ACTIVE_THREADS_FLAG,
							 &this->PAUSE_ACTIVE_THREADS_FLAG,
							 &this->GUPCI_ID,
							 &this->BUFF_UPCI_I_DS,
							 &this->BUFF_UPCI_ID_STORAGE_FLAG_ACT,
							 &this->BUFF_IN_RG,
							 &this->BUFF_EV_RG,
							 &this->BUFF_AC_RG,
							 &this->BUFF_IN_DIF_RG,
							 &this->BUFF_IN_PRO_RG,
							 &this->BUFF_SET_OF_SUPPORTED_ACTIONS,
							 &this->BUFF_SUPPORTED_ACTIONS_AMOUNT,
							 &this->BUFF_STR_MAX_EVAL,
							 &this->BUFF_MAX_EVALUATION,
							 &this->BUFF_STR_MAX_AL,
							 &this->BUFF_MAX_ACTIVITY_LEVEL,	
							 &this->BUFF_STR_MAX_RS,
							 &this->BUFF_MAX_RELATION_STRENGTH,
						     this->BUFF_STR_ACTIVATED,							 
							 this->BUFF_INIS_ACTIVATED,
							 this->BUFF_ACIS_ACTIVATED,
							 this->BUFF_EXECUTE_ACIS,
							 &this->BUFF_RL_INDEX_USED_IN_RECOGNITION,
							 &this->BUFF_INIS_SUS,
							 &this->BUFF_ACIS_SUS,
							 &this->BUFF_PFRLIS_SUS,
							 &this->BUFF_INDFRLIS_SUS,
							 this->BUFF_INIS_CRE,
							 this->BUFF_ACIS_CRE,
							 this->BUFF_PFRLIS_CRE,
							 this->BUFF_INDFRLIS_CRE,
							 this->BUFF_INPRRLIS_CRE,	
							 &this->BUFF_INIS_RE,
							 &this->BUFF_ACIS_RE,
							 &this->BUFF_INDFRLIS_RE,
							 &this->BUFF_INPRRLIS_RE,
							 &this->BUFF_UPCI_ID_INIS_CAN,
							 &this->BUFF_UPCI_ID_ACIS_CAN,
							 &this->BUFF_UPCI_ID_INDFRLIS_CAN,
							 &this->BUFF_UPCI_ID_INPRRLIS_CAN,
							 &this->BUFF_INIS_ID_CAN,
							 &this->BUFF_ACIS_ID_CAN,
							 &this->BUFF_INDFRLIS_ID_CAN,
							 &this->BUFF_INPRRLIS_ID_CAN);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializar upci.
	for (in i1 = 0; i1 < this->UPCI_AMOUNT; i1++)
	{
		//-----------------------------------------------------------------------------
		//seteo de la upci que almacenará las entradas inicialmente.
		if (this->BUFF_UPCI_ID_STORAGE_FLAG_ACT	 == i1) STORAGE_FLAG = 1; else STORAGE_FLAG = 0;

		//-----------------------------------------------------------------------------
		//inicialización de upci.
		this->BUFF_UPCI_I_DS.at(i1).Initialize(i1, this->GUPCI_NAT, STORAGE_FLAG, this->SEED + i1, _upci_i_ds_arg);
	}	

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
//#1: método para Clean totalmente la gupci.
in GUPCI_SDS::Clean()
{	
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//término de thread de entrada de la GUPCI.
	if (this->THREAD_GUPCI_INPUT.joinable()	== ON)	this->THREAD_GUPCI_INPUT.join();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de parámetros de gupci.
	this->GUPCI_ID									=	-1;									//id de la gupci.
	this->GUPCI_NAT									=	-1;									//naturaleza de la unidad ('a','b','c'...'z').	
	this->UPCI_AMOUNT								=	-1;									//cantidad de upci por grupo.			

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza banderas para funcionalidades.
	this->SUSPENDED_ACTIONS_MAXIMIZATION_FLAG		=	-1;									//bandera para utilizar reactivación acción suspendida con máxima asociación positiva.
	this->STRUCTURES_RECOGNITION_FLAG				=	-1;									//bandrea para utilizar reconocimiento de estructuras.
	this->STRUCTURES_PROJECTIONS_FLAG				=	-1;									//bandera para utilizar proyección de estructuras.	

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//limpieza de banderas para threads activos.
	this->CLOSE_ACTIVE_THREADS_FLAG					=	-1;									//bandera para cerrar threads activos.
	this->PAUSE_ACTIVE_THREADS_FLAG					=	-1;									//bandera para pausar threads activos.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de la bandera de seteo de señales de la gupci.
	this->SET_SIGNAL_FLAG							=	-1;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de UPCI.
	this->BUFF_UPCI_I_DS.clear();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza del buffer de argumentos de las upci.
	this->BUFF_UPCI_ARG.Clean();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza del buffer de gupci para banderas de almacenamiento.
	this->BUFF_UPCI_ID_STORAGE_FLAG_ACT				=	-1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de buffers para almacenar registros.
	this->BUFF_IN_RG								=	NULL;								//buffer para registro de entrada.
	this->BUFF_EV_RG								=	NULL;								//buffer para registro de evaluación de entrada.
	this->BUFF_AC_RG								=	"";									//buffer para registro de acción.
	this->BUFF_IN_DIF_RG							=	NULL;								//buffer para registro de diferencia de entradas.
	this->BUFF_IN_PRO_RG							=	NULL;								//buffer para registro de proporción de diferencia de entradas.

	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	//limpieza de buffers para acciones.
	this->BUFF_SET_OF_SUPPORTED_ACTIONS.clear();											//buffer para el conjunto de acciones soportadas.
	this->BUFF_SUPPORTED_ACTIONS_AMOUNT				=	-1;									//buffer para la cantidad de acciones soportadas.	

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//limpieza de buffers para estructura con evaluación máxima.
	this->BUFF_STR_MAX_EVAL.Clean();														//buffer para la estructura INIS con máxima evaluación.
	this->BUFF_MAX_EVALUATION						=	NULL;								//buffer para la máxima evaluación.
	
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//limpieza de buffers para estructura con nivel de actividad máximo.
	this->BUFF_STR_MAX_AL.Clean();															//buffer para la estructura con nivel de actividad máximo.
	this->BUFF_MAX_ACTIVITY_LEVEL					=	-1;									//buffer para el máximo nivel de actividad.
	
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//limpieza de buffers para estructura con fortaleza de la relación máximo.
	this->BUFF_STR_MAX_RS.Clean();															//buffer para la estructura con fortaleza de la relación máximo.
	this->BUFF_MAX_RELATION_STRENGTH				=	-1;									//buffer para el máximo fortaleza de la relación.	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de buffers para las estructuras activadas.
	this->BUFF_STR_ACTIVATED[0].Clean();													//buffer para estructura activada presente.
	this->BUFF_STR_ACTIVATED[1].Clean();													//buffer para estructura activada pasada.
	this->BUFF_INIS_ACTIVATED[0].Clean();													//buffer para estructura INIS activada presente.
	this->BUFF_INIS_ACTIVATED[1].Clean();													//buffer para estructura INIS activada pasada.
	this->BUFF_ACIS_ACTIVATED[0].Clean();													//buffer para estructura ACIS activada presente.
	this->BUFF_ACIS_ACTIVATED[1].Clean();													//buffer para estructura ACIS activada pasada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de buffer para las estructuras de acción ejecutadas.
	this->BUFF_EXECUTE_ACIS[0].Clean();
	this->BUFF_EXECUTE_ACIS[1].Clean();	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de los buffers para los ids de las estructuras creadas.
	this->BUFF_INIS_CRE[0].Clean();														//buffer para id de INIS creada actual.
	this->BUFF_INIS_CRE[1].Clean();														//buffer para id de INIS creada anterior.
	this->BUFF_ACIS_CRE[0].Clean();														//buffer para id de ACIS creada actual.
	this->BUFF_ACIS_CRE[1].Clean();														//buffer para id de ACIS creada anterior.
	this->BUFF_PFRLIS_CRE[0].Clean();														//buffer para id de PFRLIS creada actual.
	this->BUFF_PFRLIS_CRE[1].Clean();														//buffer para id de PFRLIS creada anterior.
	this->BUFF_INDFRLIS_CRE[0].Clean();														//buffer para id de INDFRLIS creada actual.
	this->BUFF_INDFRLIS_CRE[1].Clean();														//buffer para id de INDFRLIS creada anterior.
	this->BUFF_INPRRLIS_CRE[0].Clean();														//buffer para id de INPRRLIS creada actual.
	this->BUFF_INPRRLIS_CRE[1].Clean();														//buffer para id de INPRRLIS creada anterior.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de buffers para las estructuras en estado de suspensión.		
	this->BUFF_INIS_SUS.clear();															//buffer para las estructuras INIS suspendidas.
	this->BUFF_ACIS_SUS.clear();															//buffer para las estructuras ACIS suspendidas.
	this->BUFF_PFRLIS_SUS.clear();															//buffer para las estructuras PFRLIS suspendidas.
	this->BUFF_INDFRLIS_SUS.clear();														//buffer para las estructuras INDFRLIS suspendidas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de buffers para los id de las upci candidatas. [a][b]: a: tiempo, b: upci.
	this->BUFF_UPCI_ID_INIS_CAN.clear();													//buffer a id de las upci candidatas para INIS.
	this->BUFF_UPCI_ID_ACIS_CAN.clear();													//buffer a id de las upci candidatas para DACI.
	this->BUFF_UPCI_ID_INDFRLIS_CAN.clear();												//buffer a id de las upci candidatas para INDFRLIS.
	this->BUFF_UPCI_ID_INPRRLIS_CAN.clear();												//buffer a id de las upci candidatas para INPRRLIS.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de buffers de gupci a estructuras candidatas. 
	//[a][b][c]: a: tiempo, b: upci, c: buffer de estructura.
	this->BUFF_INIS_ID_CAN.clear();														//buffer de ids de estructuras tipo INIS candidatas.
	this->BUFF_ACIS_ID_CAN.clear();														//buffer de ids de estructuras tipo ACIS candidatas.
	this->BUFF_INDFRLIS_ID_CAN.clear();														//buffer de ids de estructuras tipo INDFRLIS candidatas.
	this->BUFF_INPRRLIS_ID_CAN.clear();														//buffer de ids de estructuras tipo INPRRLIS candidatas.

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//limpieza de buffer para índice de relación utilizada en reconocimiento.
	this->BUFF_RL_INDEX_USED_IN_RECOGNITION			=	-1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpíeza de buffers para las estructuras reconocidas.
	this->BUFF_INIS_RE.Clean();															//buffer para estructura reconocida INIS.
	this->BUFF_ACIS_RE.Clean();															//buffer para estructura reconocida ACIS.
	this->BUFF_INDFRLIS_RE.Clean();															//buffer para estructura reconocida INDFRLIS.
	this->BUFF_INPRRLIS_RE.Clean();															//buffer para estructura reconocida INPRRLIS.	
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	this->GUPCI_ITERATION_COUNTER					=	-1;									//contador de iteraciones de la gupci.
	
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
//#1: método de entrada y salida de datos visible por el usuario.
vo GUPCI_SDS::input(dou _input, dou _input_evaluation, st *_output_action)
{
	//---------------------------------------------------------------------------------
	//término del thread de entrada de la GUPCI.
	if (this->THREAD_GUPCI_INPUT.joinable() == ON)	this->THREAD_GUPCI_INPUT.join();
	
	//---------------------------------------------------------------------------------
	//entrada a la upci por kernel.
	this->THREAD_GUPCI_INPUT = thread(&UPC::GUPCI_SDS::ThreadInput, this, _input, _input_evaluation, _output_action);
}

//------------------------------------------------------------------------------------- 
//------------------------------------------------------------------------------------- 
//#2: método de entrada y salida de datos no visible por el usuario.
vo GUPCI_SDS::ThreadInput(dou _input, dou _input_evaluation, st *_output_action)
{	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si el kernel está disponible para operar, entonces.
	if (this->GetKERNEL_INTEGRATION_FLAG() == OFF)
	{		
		//----------------------------------------------------------------------------
		//si la bandera de seteo de señales de la gupci esta activa entonces setear.
		if (this->GetSET_SIGNAL_FLAG() == ON)	this->SetInputData(_input, _input_evaluation);
		
		//-----------------------------------------------------------------------------
		//entrada a la upci por kernel.
		this->BUFF_UPCI_I_DS[this->BUFF_UPCI_ID_STORAGE_FLAG_ACT].KernelInput(_input, _input_evaluation, _output_action);
		cout << "#accion: " << *_output_action << endl;
		//----------------------------------------------------------------------------
		//si la bandera de seteo de señales de la gupci esta activa entonces setear.
		if (this->GetSET_SIGNAL_FLAG() == ON)	this->SetOutputData(*_output_action);

		//-----------------------------------------------------------------------------
		//incremento del contador de iteraciones.
		++this->GUPCI_ITERATION_COUNTER;
	}	 
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método de entrada de comandos del usuario.
vo GUPCI_SDS::UserCommand(st _user_command)
{

}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para abrir GUPCI_SDS.
in GUPCI_SDS::Open(st _fileNameS)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación del objeto inf. 
	ifstream inf(_fileNameS + ".gu", ifstream::binary);
	
	//#################################################################################
	//---------------------------------------------------------------------------------
	//########################## VARIABLES DE INICIALIZACIÓN ##########################

	//---------------------------------------------------------------------------------
	//argumentos: parámetros de gupci.
	in		gupci_id_p							= NULL;										//id de gupci.	
	in		gupci_nat_p							= NULL;										//naturaleza de la unidad ('a','b','c'...'z').	
	in		upci_amount_p						= NULL;										//cantidad de upci por grupo.	
	in		set_signal_flag_p					= NULL;										//bandera de almacenamiento de señales.

	//---------------------------------------------------------------------------------
	//argumentos: parámetros de las upci.
	in		inis_amount_allowed_p				= NULL;										//cantidad de estructuras DINIS permitidas.
	in		lacis_amount_allowed_p				= NULL;										//cantidad de estructuras ACIS permitidas.
	in		rlis_amount_allowed_p				= NULL;										//cantidad de estructuras rlis permitidas.
	in		default_activity_level_p			= NULL;										//nivel de actividad por defecto.
	in		max_activity_level_allowed_p		= NULL;										//nivel de actividad máximo permitido.
	in		min_activity_level_allowed_p		= NULL;										//nivel de actividad mínimo permitido.
	dou		kernel_raw_input_threshold_p		= NULL;										//umbral de entrada cruda para control del núcleo.
	dou		dif_raw_input_threshold_p			= NULL;										//umbral de entrada cruda para focalización de la atención (%).
	dou		str_congruence_sr_threshold_p		= NULL;										//umbral de congruencia de registros unidimensionales (%).	
	dou		pfrlis_strength_threshold_p			= NULL;										//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
	dou		indfrlis_strength_threshold_p		= NULL;										//umbral de fortaleza de relación INDFRLIS para eliminar relación por N.A.
	dou		evaluation_threshold_p				= NULL;										//umbral para evaluaciones.	
	dou		transition_evaluation_threshold_p	= NULL;										//umbral para transiciones de evaluaciones.	
	in		timeout_clean_is_p					= NULL;										//tiempo de espera de limpieza de IS.
	in		timeout_update_al_is_p				= NULL;										//tiempo de espera para actualizar niveles de actividad en IS (ms).
	
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//variables internas.

	//---------------------------------------------------------------------------------
	//declaración de banderas para funcionalidades.
	in		suspended_actions_maximization_flag	= NULL;										//bandera para utilizar reactivación acción suspendida con máxima asociación positiva.
	in		structures_recognition_flag			= NULL;										//bandrea para utilizar reconocimiento de estructuras.
	in		structures_projections_flag			= NULL;										//bandera para utilizar proyección de estructuras.	

	//---------------------------------------------------------------------------------
	//declaración de buffer del id de la upci con bandera de almacenamiento en estado activo.
	in		buff_upci_id_storage_flag_act		= NULL;				

	//---------------------------------------------------------------------------------
	//declaración ids de la upci.
	in		upci_id								= NULL;																						

	//---------------------------------------------------------------------------------
	//declaración de bandera del estado del almacenamiento de la unidad (true: salvar, false: no-salvar).
	in		st_flag								= NULL;		

	//---------------------------------------------------------------------------------
	//declaración de buffer para la cantidad de acciones soportadas.
	in		buff_supported_actions_amount		= NULL;

	//---------------------------------------------------------------------------------
	//declaración de buffer para el conjunto de acciones soportadas.
	st		supported_action					= "";

	//---------------------------------------------------------------------------------
	//declaración de buffer para el contador de iteraciones de la gupci.
	in		gupci_iteration_counter				= NULL;

	//---------------------------------------------------------------------------------
	//declaración de otros buffers upci.	
	in		buff_INIS_id_av[2];															//buffer para id de INIS disponible.
	in		buff_ACIS_id_av[2];															//buffer para id de ACIS disponible.
	in		buff_PFRLIS_id_av[2];															//buffer para id de PFRLIS disponible.
	in		buff_INDFRLIS_id_av[2];															//buffer para id de INDFRLIS disponible.
	in		buff_INPRRLIS_id_av[2];															//buffer para id de INPRRLIS disponible.
	in		buff_max_id_INIS[2];															//buffer para máximos ids en estructuras INIS.
	in		buff_max_id_ACIS[2];															//buffer para máximos ids en estructuras ACIS.
	in		buff_max_id_PFRLIS[2];															//buffer para máximos ids en estructuras PFRLIS.
	in		buff_max_id_INDFRLIS[2];														//buffer para máximos ids en estructuras INDFRLIS.
	in		buff_max_id_INPRRLIS[2];														//buffer para máximos ids en estructuras INPRRLIS.
	in		buff_INIS_ini_amount				= NULL;										//buffer para la cantidad de INIS existentes.
	in		buff_ACIS_ini_amount				= NULL;										//buffer para la cantidad de ACIS existentes.
	in		buff_PFRLIS_ini_amount				= NULL;										//buffer para la cantidad de PFRLIS existentes.
	in		buff_INDFRLIS_ini_amount			= NULL;										//buffer para la cantidad de INDFRLIS existentes.
	in		buff_INPRRLIS_ini_amount			= NULL;										//buffer para la cantidad de INPRRLIS existentes.

	//---------------------------------------------------------------------------------
	//declaración de buffer para los contadores de iteraciones de la upci.
	in		kernel_iteration_counter			= NULL;										//contador de iteraciones del kernel de la upci.
	in		thread_iteration_counter			= NULL;										//contador de iteraciones del Hilo de la upci.

	//---------------------------------------------------------------------------------
	//declaración de buffer para semilla de generación de números pseudo aleatorios.
	in		seed								= NULL;

	//---------------------------------------------------------------------------------
	//declaración de registros para las estructuras.
	dou		in_rg								= NULL;										//registro de entrada.
	st		ac_rg								= "";										//registro de acción.
	dou		ev_rg								= NULL;										//registro de evaluación.
	dou		in_dif_rg							= NULL;										//diferencia de registros de entrada.
	dou		ev_dif_rg							= NULL;										//diferencia de registros de evaluación.
	dou		in_pro_rg							= NULL;										//proporción de registros de entrada.
	in		rl_type_rg							= NULL;										//tipo de relación.
	in		str_type_rg							= NULL;										//tipo de estructura.
	in		str1_type_rg						= NULL;										//tipo de estructura n°1.
	in		str2_type_rg						= NULL;										//tipo de estructura n°2.
	in		str_id_rg							= NULL;										//id estructura.
	in		str1_id_rg							= NULL;										//id estructura n°1.
	in		str2_id_rg							= NULL;										//id estructura n°2.
	in		upci_id_str_rg						= NULL;										//id upci de estructura.
	in		upci_id_str1_rg						= NULL;										//id upci de estructura n°1.
	in		upci_id_str2_rg						= NULL;										//id upci de estructura n°2.

	//---------------------------------------------------------------------------------
	//declaración de sub-registros para las estructuras.
	in		cs_srg								= NULL;										//estado de congruencia.
	dou		rs_srg								= NULL;										//fortaleza de la relación.
	dou		al_srg								= NULL;										//nivel de actividad.

	//---------------------------------------------------------------------------------
	//declaración de variables auxiliares para las relaciones.
	dedein	rl;
	in		rl_type								= NULL;
	in		rl_id								= NULL;	
	in		rl_upci_id							= NULL;

	//---------------------------------------------------------------------------------
	//declaración de variables auxiliares cantidad de relaciones.
	in		rl_amount							= NULL;								

	//#################################################################################
	//---------------------------------------------------------------------------------
	//################################## LECTURA ######################################
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//lectura parámetros de gupci.	
	inf >> gupci_id_p;
	inf >> gupci_nat_p;
	inf >> upci_amount_p;
	inf >> set_signal_flag_p;
	
	//---------------------------------------------------------------------------------  
	//---------------------------------------------------------------------------------  
	//lectura de parámetros de las upci.
	inf >> inis_amount_allowed_p;
	inf >> lacis_amount_allowed_p;
	inf >> rlis_amount_allowed_p;
	inf >> default_activity_level_p;
	inf >> max_activity_level_allowed_p;
	inf >> min_activity_level_allowed_p;
	inf >> kernel_raw_input_threshold_p;
	inf >> dif_raw_input_threshold_p;
	inf >> str_congruence_sr_threshold_p;
	inf >> pfrlis_strength_threshold_p;
	inf >> indfrlis_strength_threshold_p;
	inf >> evaluation_threshold_p;
	inf >> transition_evaluation_threshold_p;
	inf >> timeout_clean_is_p; 
	inf >> timeout_update_al_is_p;	

	//---------------------------------------------------------------------------------  
	//---------------------------------------------------------------------------------  
	//lectura de bandera de funcionalidades.
	inf >> suspended_actions_maximization_flag;
	inf >> structures_recognition_flag;
	inf >> structures_projections_flag;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------  
	//lectura de buffers de gupci para banderas de almacenamiento.
	inf >> buff_upci_id_storage_flag_act;
		
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza del grupo de unidad de proceso cognitivo.
	this->Clean();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de argumentos de inicialización del objeto upci.
	this->BUFF_UPCI_ARG.Initialize(inis_amount_allowed_p,
								   lacis_amount_allowed_p,
								   rlis_amount_allowed_p,
								   default_activity_level_p,
								   max_activity_level_allowed_p,
								   min_activity_level_allowed_p,
								   kernel_raw_input_threshold_p,
								   dif_raw_input_threshold_p,
								   str_congruence_sr_threshold_p,
								   pfrlis_strength_threshold_p,
								   indfrlis_strength_threshold_p,
								   evaluation_threshold_p,
								   transition_evaluation_threshold_p,
								   timeout_clean_is_p,
								   timeout_update_al_is_p);
	
	//---------------------------------------------------------------------------------
	//inicialización de la gupci.
	this->Initialize(upci_amount_p, BUFF_UPCI_ARG);

	//---------------------------------------------------------------------------------
	//seteo del id de la gupci.
	this->GUPCI_ID		= gupci_id_p;
	
	//---------------------------------------------------------------------------------
	//seteo de la naturaleza de la gupci.
	this->GUPCI_NAT		= gupci_nat_p;

	//---------------------------------------------------------------------------------
	//seteo de la bandera de almacenamiento de señales.
	this->SetSET_SIGNAL_FLAG(set_signal_flag_p);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización banderas para funcionalidades.
	this->SUSPENDED_ACTIONS_MAXIMIZATION_FLAG	= suspended_actions_maximization_flag;		//bandera para utilizar reactivación acción suspendida con máxima asociación positiva.
	this->STRUCTURES_RECOGNITION_FLAG			= structures_recognition_flag;				//bandrea para utilizar reconocimiento de estructuras.
	this->STRUCTURES_PROJECTIONS_FLAG			= structures_projections_flag;				//bandera para utilizar proyección de estructuras.	
	
	//---------------------------------------------------------------------------------
	//seteo de buffer del id de la upci con bandera de almacenamiento en estado activo.
	this->BUFF_UPCI_ID_STORAGE_FLAG_ACT			= buff_upci_id_storage_flag_act;

	//---------------------------------------------------------------------------------
	//se lee la cantidad de acciones soportadas.
	inf >> buff_supported_actions_amount;
	
	//---------------------------------------------------------------------------------
	//seteo de la cantidad de acciones soportadas.
	this->BUFF_SUPPORTED_ACTIONS_AMOUNT			= buff_supported_actions_amount;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para guardar buffer para el conjunto de acciones soportadas.
	for (in i1 = 0; i1 < this->BUFF_SUPPORTED_ACTIONS_AMOUNT; i1++)
	{
		//-----------------------------------------------------------------------------
		//se guarda el Set de acciones soportadas.
		inf >> supported_action;
		
		//-----------------------------------------------------------------------------
		//seteo de la acción en Set de acciones soportadas.
		this->BUFF_SET_OF_SUPPORTED_ACTIONS.push_back(supported_action);
	}

	//---------------------------------------------------------------------------------
	//se guarda el contador de iteraciones de la gupci.
	inf >> gupci_iteration_counter;
	
	//---------------------------------------------------------------------------------
	//seteo de la cantidad de iteraciones de la gupci.
	this->GUPCI_ITERATION_COUNTER				= gupci_iteration_counter;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para leer cada upci.
	for (in i1 = 0; i1 < this->UPCI_AMOUNT; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//lectura del id. 
		inf >> upci_id;
		
		//-----------------------------------------------------------------------------
		//lectura de los estados de las banderas.
		inf >> st_flag;
		
		//-----------------------------------------------------------------------------
		//lectura de algunos buffers.				
		inf >> buff_INIS_id_av[0];
		inf >> buff_ACIS_id_av[0];
		inf >> buff_PFRLIS_id_av[0];
		inf >> buff_INDFRLIS_id_av[0];
		inf >> buff_INPRRLIS_id_av[0];
		inf >> buff_INIS_id_av[1];				
		inf >> buff_ACIS_id_av[1];	
		inf >> buff_PFRLIS_id_av[1];	
		inf >> buff_INDFRLIS_id_av[1];
		inf >> buff_INPRRLIS_id_av[1];
		inf >> buff_max_id_INIS[0];
		inf >> buff_max_id_ACIS[0];
		inf >> buff_max_id_PFRLIS[0];
		inf >> buff_max_id_INDFRLIS[0];
		inf >> buff_max_id_INPRRLIS[0];
		inf >> buff_max_id_INIS[1];
		inf >> buff_max_id_ACIS[1];
		inf >> buff_max_id_PFRLIS[1];
		inf >> buff_max_id_INDFRLIS[1];
		inf >> buff_max_id_INPRRLIS[1];
		inf >> buff_INIS_ini_amount;
		inf >> buff_ACIS_ini_amount;
		inf >> buff_PFRLIS_ini_amount;	
		inf >> buff_INDFRLIS_ini_amount;
		inf >> buff_INPRRLIS_ini_amount;

		//-----------------------------------------------------------------------------
		//se leen los contadores de iteraciones de la upci.
		inf >> kernel_iteration_counter;
		inf >> thread_iteration_counter;

		//-----------------------------------------------------------------------------
		//se lee la semilla para la generación de números pseudo aleatorios para la gupci i1.
		inf >> seed;

		//-----------------------------------------------------------------------------
		//se Setea el id.
		this->BUFF_UPCI_I_DS.at(i1).UPCI_ID						= upci_id;
							
		//-----------------------------------------------------------------------------
		//se Setean las banderas.
		this->BUFF_UPCI_I_DS.at(i1).STORAGE_FLAG					= st_flag;
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//se Setean otros buffers.	
		this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS_ID_AV[0]			= buff_INIS_id_av[0];
		this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS_ID_AV[0]			= buff_ACIS_id_av[0];
		this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS_ID_AV[0]			= buff_PFRLIS_id_av[0];
		this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS_ID_AV[0]		= buff_INDFRLIS_id_av[0];
		this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS_ID_AV[0]		= buff_INPRRLIS_id_av[0];
		this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS_ID_AV[1]			= buff_INIS_id_av[1];				
		this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS_ID_AV[1]			= buff_ACIS_id_av[1];				
		this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS_ID_AV[1]			= buff_PFRLIS_id_av[1];	
		this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS_ID_AV[1]		= buff_INDFRLIS_id_av[1];		
		this->BUFF_UPCI_I_DS.at(i1).BUFF_INPRRLIS_ID_AV[1]		= buff_INPRRLIS_id_av[1];		
		this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS_MAX_ID[0]		= buff_max_id_INIS[0];
		this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS_MAX_ID[0]		= buff_max_id_ACIS[0];
		this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS_MAX_ID[0]		= buff_max_id_PFRLIS[0];
		this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS_MAX_ID[0]		= buff_max_id_INDFRLIS[0];
		this->BUFF_UPCI_I_DS.at(i1).BUFF_INPRRLIS_MAX_ID[0]		= buff_max_id_INPRRLIS[0];
		this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS_MAX_ID[1]		= buff_max_id_INIS[1];
		this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS_MAX_ID[1]		= buff_max_id_ACIS[1];
		this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS_MAX_ID[1]		= buff_max_id_PFRLIS[1];
		this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS_MAX_ID[1]		= buff_max_id_INDFRLIS[1];
		this->BUFF_UPCI_I_DS.at(i1).BUFF_INPRRLIS_MAX_ID[1]		= buff_max_id_INPRRLIS[1];
		this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS_INI_AMOUNT		= buff_INIS_ini_amount;
		this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS_INI_AMOUNT		= buff_ACIS_ini_amount;
		this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS_INI_AMOUNT		= buff_PFRLIS_ini_amount;
		this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS_INI_AMOUNT		= buff_INDFRLIS_ini_amount;
		this->BUFF_UPCI_I_DS.at(i1).BUFF_INPRRLIS_INI_AMOUNT		= buff_INPRRLIS_ini_amount;

		//-----------------------------------------------------------------------------
		//seteo de la cantidad de iteraciones de la upci.
		this->BUFF_UPCI_I_DS.at(i1).KERNEL_ITERATION_COUNTER		= kernel_iteration_counter;
		this->BUFF_UPCI_I_DS.at(i1).THREAD_ITERATION_COUNTER		= thread_iteration_counter;

		//-----------------------------------------------------------------------------
		//seteo de la semilla para la generación de números pseudo aleatorios para la gupci i1
		this->BUFF_UPCI_I_DS.at(i1).SEED							= seed;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle lectura estructuras INIS.
		for (in i2 = 0; i2 < inis_amount_allowed_p; i2++)
		{
			//-------------------------------------------------------------------------
			//se lee el registro de la estrutura de entrada.
			inf >> in_rg;			
			
			//-------------------------------------------------------------------------
			//se lee el registro de evaluación de la estrutura de entrada.
			inf >> ev_rg;

			//-------------------------------------------------------------------------
			//se lee el sub-registro de nivel de actividad de la estructura.
			inf >> al_srg;
			
			//-------------------------------------------------------------------------
			//si el sub-registro de nivel de actividad está definido, entonces.
			if (al_srg != -1)
			{
				//---------------------------------------------------------------------
				//seteo de sub-registros.
				cs_srg = OFF;
				al_srg = 0;
			}

			//-------------------------------------------------------------------------
			//si el sub-registro de nivel de actividad no está definido, entonces.
			else
			{
				//---------------------------------------------------------------------
				//seteo de sub-registros.
				cs_srg = -1;
				al_srg = -1;
			}
			
			//-------------------------------------------------------------------------
			//se lee la cantidad de relaciones de la estructura.
			inf >> rl_amount;
			
			//-------------------------------------------------------------------------
			//se limpia el buffer de relaciones.
			rl.clear();
			
			//-------------------------------------------------------------------------
			//lectura de relaciones.
			for (in i3 = 0; i3 < rl_amount; i3++)
			{
				//---------------------------------------------------------------------
				//se lee el id, el tipo y la dirección de la upci de la relación.
				inf >> rl_type;
				inf >> rl_id;
				inf >> rl_upci_id;	
				
				//---------------------------------------------------------------------
				//se cargan al buffer de relaciones.
				rl.push_back(deque<in>(0));
				rl.back().push_back(rl_type);
				rl.back().push_back(rl_id);
				rl.back().push_back(rl_upci_id);
			}
			
			//-------------------------------------------------------------------------
			//seteo de la estructura.
			this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS[i2].Set(in_rg, ev_rg, cs_srg, al_srg, rl);
		}
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle lectura estructuras ACIS.
		for (in i2 = 0; i2 < lacis_amount_allowed_p; i2++)
		{
			//-------------------------------------------------------------------------
			//se lee el registro de la estrutura de acción.
			inf >> ac_rg;
			
			//-------------------------------------------------------------------------
			//se lee el sub-registro de nivel de actividad de la estructura.
			inf >> al_srg;
			
			//-------------------------------------------------------------------------
			//si el sub-registro de nivel de actividad está definido, entonces.
			if (al_srg != -1)
			{
				//---------------------------------------------------------------------
				//seteo de sub-registros.
				cs_srg = OFF;
				al_srg = 0;
			}

			//-------------------------------------------------------------------------
			//si el sub-registro de nivel de actividad no está definido, entonces.
			else
			{
				//---------------------------------------------------------------------
				//seteo de sub-registros.
				cs_srg = -1;
				al_srg = -1;
			}

			//-------------------------------------------------------------------------
			//se lee la cantidad de relaciones de la estructura.
			inf >> rl_amount;
			
			//-------------------------------------------------------------------------
			//se limpia el buffer de relaciones.
			rl.clear();

			//-------------------------------------------------------------------------
			//lectura relaciones.
			for (in i3 = 0; i3 < rl_amount; i3++)
			{
				//---------------------------------------------------------------------
				//se lee el id, el tipo y la dirección de la upci de la relación.
				inf >> rl_type;
				inf >> rl_id;
				inf >> rl_upci_id;

				//---------------------------------------------------------------------
				//se cargan al buffer de relaciones.
				rl.push_back(deque<in>(0));
				rl.back().push_back(rl_type);
				rl.back().push_back(rl_id);
				rl.back().push_back(rl_upci_id);
			}

			//-------------------------------------------------------------------------
			//seteo de la estructura.
			this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS[i2].Set(ac_rg, cs_srg, al_srg, rl);
		}
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle lectura estructuras PFRLIS.
		for (in i2 = 0; i2 < rlis_amount_allowed_p; i2++)
		{
			//-------------------------------------------------------------------------
			//se leen los registros de la estructura de relación.
			inf >> str1_type_rg;
			inf >> str2_type_rg;
			inf >> str1_id_rg;
			inf >> str2_id_rg;
			inf >> upci_id_str1_rg;
			inf >> upci_id_str2_rg;
			
			//-------------------------------------------------------------------------
			//se leen los sub-registros de la estructura.
			inf >> rs_srg;

			//-------------------------------------------------------------------------
			//si el sub-registro de fortaleza de relación está definida, entonces.
			if (rs_srg != -1)
			{
				//---------------------------------------------------------------------
				//seteo de sub-registros.
				cs_srg = OFF;
				al_srg = 0;
			}

			//-------------------------------------------------------------------------
			//si el sub-registro de fortaleza de relación no está definida, entonces.
			else
			{
				//---------------------------------------------------------------------
				//seteo de sub-registros.
				cs_srg = -1;
				al_srg = -1;
			}
			
			//-------------------------------------------------------------------------
			//seteo de la estructura.
			this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS[i2].Set(str1_type_rg, str2_type_rg, str1_id_rg, str2_id_rg, upci_id_str1_rg, upci_id_str2_rg, rs_srg, al_srg);
		}
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle lectura estructuras INDFRLIS.
		for (in i2 = 0; i2 < rlis_amount_allowed_p; i2++)
		{
			//-------------------------------------------------------------------------
			//se lee el registro de diferencia.
			inf >> in_dif_rg;

			//-------------------------------------------------------------------------
			//se lee el registro de diferencia de evaluación.
			inf >> ev_dif_rg;

			//-------------------------------------------------------------------------
			//se leen los registros de la estructura de relación.
			inf >> str1_id_rg;
			inf >> str2_id_rg;
			inf >> upci_id_str1_rg;
			inf >> upci_id_str2_rg;
			
			//-------------------------------------------------------------------------
			//se leen los sub-registros de la estructura.
			inf >> rs_srg;

			//-------------------------------------------------------------------------
			//si el sub-registro de fortaleza de relación está definida, entonces.
			if (rs_srg != -1)
			{
				//---------------------------------------------------------------------
				//seteo de sub-registros.
				cs_srg = OFF;
				al_srg = 0;
			}

			//-------------------------------------------------------------------------
			//si el sub-registro de fortaleza de relación no está definida, entonces.
			else
			{
				//---------------------------------------------------------------------
				//seteo de sub-registros.
				cs_srg = -1;
				al_srg = -1;
			}

			//-------------------------------------------------------------------------
			//se lee la cantidad de relaciones de la estructura.
			inf >> rl_amount;

			//-------------------------------------------------------------------------
			//se limpia el buffer de relaciones.
			rl.clear();

			//-------------------------------------------------------------------------
			//lectura de relaciones.
			for (in i3 = 0; i3 < rl_amount; i3++)
			{
				//---------------------------------------------------------------------
				//se lee el id, el tipo y la dirección de la upci de la relación.
				inf >> rl_type;
				inf >> rl_id;
				inf >> rl_upci_id;

				//---------------------------------------------------------------------
				//se cargan al buffer de relaciones.
				rl.push_back(deque<in>(0));
				rl.back().push_back(rl_type);
				rl.back().push_back(rl_id);
				rl.back().push_back(rl_upci_id);
			}

			//-------------------------------------------------------------------------
			//seteo de la estructura.
			this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS[i2].Set(in_dif_rg, ev_dif_rg, str1_id_rg, str2_id_rg, upci_id_str1_rg, upci_id_str2_rg, cs_srg, rs_srg, al_srg, rl);
		}
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle lectura estructuras INPRRLIS.
		for (in i2 = 0; i2 < rlis_amount_allowed_p; i2++)
		{
			//-------------------------------------------------------------------------
			//se lee el registro de proporción.
			inf >> in_pro_rg;

			//-------------------------------------------------------------------------
			//se leen los registros de la estructura de relación.
			inf >> str1_id_rg;
			inf >> str2_id_rg;
			inf >> upci_id_str1_rg;
			inf >> upci_id_str2_rg;

			//-------------------------------------------------------------------------
			//seteo del sub-registro de estado de congruencia.
			if (str1_id_rg != -1)	cs_srg = OFF;
			else					cs_srg = -1;
			
			//-------------------------------------------------------------------------
			//seteo de la estructura.
			this->BUFF_UPCI_I_DS.at(i1).BUFF_INPRRLIS[i2].Set(in_pro_rg, str1_id_rg, str2_id_rg, upci_id_str1_rg, upci_id_str2_rg, cs_srg);
		}
	}
	
	//---------------------------------------------------------------------------------
	//cierre del archivo.
	inf.close();

	//---------------------------------------------------------------------------------
	//successful execution.
	return SUCCESS;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para guardar gupci.
in GUPCI_SDS::Save(st _fileNameS)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación del objeto ouf.
	ofstream ouf(_fileNameS + ".gu", ofstream::binary);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//declaración de variable auxiliar para cantidad de relaciones.										
	in	rl_amount	= NULL;														

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//se guardan los datos.	
	
	//---------------------------------------------------------------------------------
	//guardar parámetros de gupci.	
	ouf << this->GUPCI_ID			<< endl;
	ouf << this->GUPCI_NAT			<< endl;
	ouf << this->UPCI_AMOUNT		<< endl;
	ouf << this->SET_SIGNAL_FLAG	<< endl;
	
	//---------------------------------------------------------------------------------  
	//guardar parámetros upci.	
	ouf << this->BUFF_UPCI_I_DS.at(0).INIS_AMOUNT_ALLOWED				<< endl;
	ouf << this->BUFF_UPCI_I_DS.at(0).ACIS_AMOUNT_ALLOWED				<< endl;
	ouf << this->BUFF_UPCI_I_DS.at(0).RLIS_AMOUNT_ALLOWED				<< endl;
	ouf << this->BUFF_UPCI_I_DS.at(0).DEFAULT_ACTIVITY_LEVEL				<< endl;
	ouf << this->BUFF_UPCI_I_DS.at(0).MAX_ACTIVITY_LEVEL_ALLOWED			<< endl;
	ouf << this->BUFF_UPCI_I_DS.at(0).MIN_ACTIVITY_LEVEL_ALLOWED			<< endl;
	ouf << this->BUFF_UPCI_I_DS.at(0).KERNEL_RAW_INPUT_THRESHOLD			<< endl;
	ouf << this->BUFF_UPCI_I_DS.at(0).DIF_RAW_INPUT_THRESHOLD			<< endl;
	ouf << this->BUFF_UPCI_I_DS.at(0).STR_CONGRUENCE_SR_THRESHOLD		<< endl;
	ouf << this->BUFF_UPCI_I_DS.at(0).PFRLIS_STRENGTH_THRESHOLD			<< endl;
	ouf << this->BUFF_UPCI_I_DS.at(0).INDFRLIS_STRENGTH_THRESHOLD		<< endl;
	ouf << this->BUFF_UPCI_I_DS.at(0).EVALUATION_THRESHOLD				<< endl;
	ouf << this->BUFF_UPCI_I_DS.at(0).TRANSITION_EVALUATION_THRESHOLD	<< endl;
	ouf << this->BUFF_UPCI_I_DS.at(0).TIMEOUT_CLEAN_IS					<< endl;
	ouf << this->BUFF_UPCI_I_DS.at(0).TIMEOUT_UPDATE_AL_IS				<< endl;

	//---------------------------------------------------------------------------------  
	//guardar banderas para funcionalidades.
	ouf << this->SUSPENDED_ACTIONS_MAXIMIZATION_FLAG	<< endl;
	ouf << this->STRUCTURES_RECOGNITION_FLAG			<< endl;
	ouf << this->STRUCTURES_PROJECTIONS_FLAG			<< endl;

	//---------------------------------------------------------------------------------
	//guardar buffer de gupci para banderas de almacenamiento
	ouf << this->BUFF_UPCI_ID_STORAGE_FLAG_ACT << endl;

	//---------------------------------------------------------------------------------
	//se guarda la cantidad de acciones soportadas.
	ouf << this->BUFF_SUPPORTED_ACTIONS_AMOUNT << endl;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para guardar buffer para el conjunto de acciones soportadas.
	for (in i1 = 0; i1 < this->BUFF_SUPPORTED_ACTIONS_AMOUNT; i1++)
	{
		//-----------------------------------------------------------------------------
		//se guarda el Set de acciones soportadas.
		ouf << this->BUFF_SET_OF_SUPPORTED_ACTIONS.at(i1) << endl;
	}

	//---------------------------------------------------------------------------------
	//se guarda el contador de iteraciones de la gupci.
	ouf << this->GUPCI_ITERATION_COUNTER << endl;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para salvar cada upci.
	for (in i1 = 0; i1 < this->UPCI_AMOUNT; i1++)
	{		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//se guarda el id.
		ouf << this->BUFF_UPCI_I_DS.at(i1).UPCI_ID		<< endl;

		//-----------------------------------------------------------------------------
		//se guarda la bandera de almacenamiento.
		ouf << this->BUFF_UPCI_I_DS.at(i1).STORAGE_FLAG	<< endl;
		
		//-----------------------------------------------------------------------------
		//se guardan los buffers.				
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS_ID_AV[0]		<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS_ID_AV[0]		<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS_ID_AV[0]		<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS_ID_AV[0]	<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INPRRLIS_ID_AV[0]	<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS_ID_AV[1]		<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS_ID_AV[1]		<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS_ID_AV[1]		<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS_ID_AV[1]	<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INPRRLIS_ID_AV[1]	<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS_MAX_ID[0]		<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS_MAX_ID[0]		<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS_MAX_ID[0]		<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS_MAX_ID[0]	<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INPRRLIS_MAX_ID[0]	<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS_MAX_ID[1]		<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS_MAX_ID[1]		<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS_MAX_ID[1]		<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS_MAX_ID[1]	<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INPRRLIS_MAX_ID[1]	<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS_INI_AMOUNT	<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS_INI_AMOUNT	<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS_INI_AMOUNT	<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS_INI_AMOUNT	<< endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INPRRLIS_INI_AMOUNT	<< endl;

		//-----------------------------------------------------------------------------
		//se guarda el contador de iteraciones de la upci i1.
		ouf << this->BUFF_UPCI_I_DS.at(i1).KERNEL_ITERATION_COUNTER << endl;
		ouf << this->BUFF_UPCI_I_DS.at(i1).THREAD_ITERATION_COUNTER << endl;

		//-----------------------------------------------------------------------------
		//se guarda la semilla de la gupci i1.
		ouf << this->BUFF_UPCI_I_DS.at(i1).SEED << endl;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle guardar estructuras INIS de la upci i1.
		for (in i2 = 0; i2 < this->BUFF_UPCI_I_DS.at(i1).INIS_AMOUNT_ALLOWED; i2++)
		{
			//-------------------------------------------------------------------------
			//se guarda el registro de la estrutura de entrada.
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS[i2].IN_RG << endl;
			
			//-------------------------------------------------------------------------
			//se guarda el registro de la estrutura de entrada.
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS[i2].EV_RG << endl;

			//-------------------------------------------------------------------------
			//se guarda el nivel de actividad de la estrutura de entrada.
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS[i2].AL_SRG << endl;
			
			//-------------------------------------------------------------------------
			//obtención de la cantidad de relaciones de la estructura.
			rl_amount	= this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS[i2].GetRelationAmount();
			
			//-------------------------------------------------------------------------
			//se guardan las cantidades de relaciones de la estructura.
			ouf << rl_amount << endl;

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//guardar relaciones.
			for (in i3 = 0; i3 < rl_amount; i3++)
			{				
				//---------------------------------------------------------------------
				//se guardar el id y el tipo de relación.
				ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS[i2].RL.at(i3).at(0) << endl;
				ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS[i2].RL.at(i3).at(1) << endl;
				ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INIS[i2].RL.at(i3).at(2) << endl;
			}
		}
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle guardar estructuras ACIS de la upci i1.
		for (in i2 = 0; i2 < this->BUFF_UPCI_I_DS.at(i1).ACIS_AMOUNT_ALLOWED; i2++)
		{
			//-------------------------------------------------------------------------
			//se guarda el registro de la estrutura de acción.
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS[i2].AC_RG << endl;
			
			//-------------------------------------------------------------------------
			//se guarda el nivel de actividad de la estrutura de acción.
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS[i2].AL_SRG << endl;
			
			//-------------------------------------------------------------------------
			//obtención de la cantidad de relaciones de la estructura.
			rl_amount = this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS[i2].GetRelationAmount();

			//-------------------------------------------------------------------------
			//se guardan las cantidades de relaciones de la estructura.
			ouf << rl_amount << endl;

			//-------------------------------------------------------------------------
			//guardar relaciones.
			for (in i3 = 0; i3 < rl_amount; i3++)
			{
				//---------------------------------------------------------------------
				//se guardar el id y el tipo de relación.
				ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS[i2].RL.at(i3).at(0) << endl;
				ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS[i2].RL.at(i3).at(1) << endl;
				ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_ACIS[i2].RL.at(i3).at(2) << endl;
			}
		}
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle guardar estructuras PFRLIS de la upci i1.
		for (in i2 = 0; i2 < this->BUFF_UPCI_I_DS.at(i1).RLIS_AMOUNT_ALLOWED; i2++)
		{
			//-------------------------------------------------------------------------
			//se guardan los registros de la estructura de relación.
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS[i2].STR1_TYPE_RG		<< endl;
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS[i2].STR2_TYPE_RG		<< endl;
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS[i2].STR1_ID_RG		<< endl;
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS[i2].STR2_ID_RG		<< endl;
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS[i2].UPCI_ID_STR1_RG	<< endl;
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS[i2].UPCI_ID_STR2_RG	<< endl;
						
			//-------------------------------------------------------------------------
			//se guardan los sub-registros de la estructura.
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_PFRLIS[i2].RS_SRG << endl;
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle guardar estructuras INDFRLIS de la upci i1.
		for (in i2 = 0; i2 < this->BUFF_UPCI_I_DS.at(i1).RLIS_AMOUNT_ALLOWED; i2++)
		{
			//-------------------------------------------------------------------------
			//se guarda el registro de la estrutura de diferenciación de entrada.
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS[i2].IN_DIF_RG << endl;

			//-------------------------------------------------------------------------
			//se guarda el registro de diferenciación de evaluación.
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS[i2].EV_DIF_RG << endl;

			//-------------------------------------------------------------------------
			//se guardan los registros de la estructura de relación.
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS[i2].STR1_ID_RG		<< endl;
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS[i2].STR2_ID_RG		<< endl;
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS[i2].UPCI_ID_STR1_RG	<< endl;
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS[i2].UPCI_ID_STR2_RG	<< endl;

			//-------------------------------------------------------------------------
			//se guardan los sub-registros de la estructura.
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS[i2].RS_SRG << endl;

			//-------------------------------------------------------------------------
			//obtención de la cantidad de relaciones de la estructura.
			rl_amount	= this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS[i2].GetRelationAmount();

			//-------------------------------------------------------------------------
			//se guardan las cantidades de relaciones de la estructura.
			ouf << rl_amount << endl;

			//-------------------------------------------------------------------------
			//guardar relaciones.
			for (in i3 = 0; i3 < rl_amount; i3++)
			{
				//---------------------------------------------------------------------
				//se guardar el id y el tipo de relación.
				ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS[i2].RL.at(i3).at(0) << endl;
				ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS[i2].RL.at(i3).at(1) << endl;
				ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INDFRLIS[i2].RL.at(i3).at(2) << endl;
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle guardar estructuras INPRRLIS de la upci i1.
		for (in i2 = 0; i2 < this->BUFF_UPCI_I_DS.at(i1).RLIS_AMOUNT_ALLOWED; i2++)
		{
			//-------------------------------------------------------------------------
			//se guarda el registro de la estrutura de proporción de entrada.
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INPRRLIS[i2].IN_PRO_RG << endl;
			
			//-------------------------------------------------------------------------
			//se guardan los registros de la estructura de relación.
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INPRRLIS[i2].STR1_ID_RG		<< endl;
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INPRRLIS[i2].STR2_ID_RG		<< endl;
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INPRRLIS[i2].UPCI_ID_STR1_RG	<< endl;
			ouf << this->BUFF_UPCI_I_DS.at(i1).BUFF_INPRRLIS[i2].UPCI_ID_STR2_RG	<< endl;
		}
	}	
	
	//---------------------------------------------------------------------------------
	//cierre del archivo.
	ouf.close();

	//---------------------------------------------------------------------------------
	//successful execution.
	return SUCCESS;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para guardar señales de entrada, evaluación y salida de la gupci.
vo GUPCI_SDS::SaveSignalData(string _fileNameS)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.lock();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//obtención de la cantidad de tiempos de toma de registros de las señales.
	in data_amount = (in)this->INPUT_SIGNAL.size();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si no hay datos de guardar, entonces salir.
	if (data_amount == 0)
	{
		//-----------------------------------------------------------------------------
		//impresión.
		cout << "# no hay seniales que guardar." << endl;

		//-----------------------------------------------------------------------------
		//salida.
		return;
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//nombre s ficheros.
	string inputSignalFile;
	string evaluationSignalFile;
	string outputSignalFile;		

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo de los nombres de los ficheros.
	inputSignalFile			= _fileNameS + " (input signal).txt";
	evaluationSignalFile	= _fileNameS + " (evaluation signal).txt";
	outputSignalFile		= _fileNameS + " (output signal).txt";

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación del objetos de escritura.
	ofstream isf(inputSignalFile);
	ofstream esf(evaluationSignalFile);
	ofstream osf(outputSignalFile);		

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para salvar las señales de la gupci.
	for (in i1 = 0; i1 < data_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//se salvan los registros.
		isf << this->INPUT_SIGNAL[i1] << endl;
		esf << this->EVALUATION_SIGNAL[i1] << endl;
		osf << this->OUTPUT_SIGNAL[i1] << endl;
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//cierre de los ficheros.
	isf.close();
	esf.close();
	osf.close();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//desbloqueo para actualización de buffers.
	this->RED_LIGHT_MUTEX.unlock();

	//---------------------------------------------------------------------------------
	//impresión.
	cout << "# se ha guardado exitosamente las señales." << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método para imprimir gupci.
vo GUPCI_SDS::PrintGUPCI_I_DS(in _upci_id, in _buffers_selection, in _str_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//impresión de línea divisora.
	cout <<"--------------------------------------------------------------------" <<endl;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de buffers.
	if		(_buffers_selection == DEF_BUFF_BA)						this->PrintBuffBanderas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_NU)						this->PrintBuffNucleo(_upci_id);
	else if (_buffers_selection == DEF_BUFF_DIR_UPC)				this->PrintBuffDirUpc(_upci_id);
	else if (_buffers_selection == DEF_BUFF_INIS)					this->PrintBuffEstructurasINIS(_upci_id, _str_id);
	else if (_buffers_selection == DEF_BUFF_ACIS)					this->PrintBuffEstructurasACIS(_upci_id, _str_id);
	else if (_buffers_selection == DEF_BUFF_PFRLIS)					this->PrintBuffEstructurasPFRLIS(_upci_id, _str_id);
	else if (_buffers_selection == DEF_BUFF_INDFRLIS)				this->PrintBuffEstructurasINDFRLIS(_upci_id, _str_id);
	else if (_buffers_selection == DEF_BUFF_INPRRLIS)				this->PrintBuffEstructurasINPRRLIS(_upci_id, _str_id);
	else if (_buffers_selection == DEF_BUFF_INIS_CAN)				this->PrintBuffINISCandidatas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_ACIS_CAN)				this->PrintBuffACISCandidatas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_INDFRLIS_CAN)			this->PrintBuffINDFRLISCandidatas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_INPRRLIS_CAN)			this->PrintBuffINPRRLISCandidatas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_ID_UPCI_INIS_CAN)		this->PrintBuffIdUpcINISCandidatas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_ID_UPCI_ACIS_CAN)		this->PrintBuffIdUpcACISCandidatas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_ID_UPCI_INDFRLIS_CAN)	this->PrintBuffIdUpcINDFRLISCandidatas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_ID_UPCI_INPRRLIS_CAN)	this->PrintBuffIdUpcINPRRLISCandidatas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_STR_DIS)				this->PrintBuffIdEstDisponibles(_upci_id);
	else if (_buffers_selection == DEF_BUFF_STR_CRE)				this->PrintBuffIdYTipoEstCreadas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_STR_RE)					this->PrintBuffEstReconocidas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_CANT_UPCI_STR_SUS)		this->PrintBuffCantUpciEstSuspension(_upci_id);
	else if (_buffers_selection == DEF_BUFF_CANT_EST)				this->PrintBuffCantEstExistentes(_upci_id);
	else if (_buffers_selection == DEF_BUFF_CANT_EXP)				this->PrintBuffCantExp(_upci_id);
	else if (_buffers_selection == DEF_BUFF_MAX_ID_EST)				this->PrintBuffMaxIdEst(_upci_id);	

	//---------------------------------------------------------------------------------
	//impresión de línea divisora.
	cout << "--------------------------------------------------------------------" << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método Get para obtener la cantidad de upci conectados.
in GUPCI_SDS::GetUPCI_AMOUNT()
{
	//---------------------------------------------------------------------------------
	//retorno de la cantidad de upci conectados.
	return in(this->BUFF_UPCI_I_DS.size());
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para obtener el estado de la bandera 'KERNEL_INTEGRATION_FLAG'.
in GUPCI_SDS::GetKERNEL_INTEGRATION_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera KERNEL_INTEGRATION_FLAG.
	return this->BUFF_UPCI_I_DS[this->BUFF_UPCI_ID_STORAGE_FLAG_ACT].GetKERNEL_INTEGRATION_FLAG();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para obtener el estado de la bandera 'KERNEL_CONTROL_INTEGRATION_FINISHED_FLAG'. 
in GUPCI_SDS::GetKERNEL_CONTROL_INTEGRATION_FINISHED_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'KERNEL_CONTROL_INTEGRATION_FINISHED_FLAG'.
	return this->BUFF_UPCI_I_DS[this->BUFF_UPCI_ID_STORAGE_FLAG_ACT].GetKERNEL_CONTROL_INTEGRATION_FINISHED_FLAG();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para obtener el estado de la bandera 'THREAD_INTEGRATION_FLAG'.
in GUPCI_SDS::GetTHREAD_INTEGRATION_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera THREAD_INTEGRATION_FLAG.
	return this->BUFF_UPCI_I_DS[this->BUFF_UPCI_ID_STORAGE_FLAG_ACT].GetTHREAD_INTEGRATION_FLAG();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para obtener el estado de la bandera 'THREAD_INTEGRATION_FINISHED_FLAG'. 
in GUPCI_SDS::GetTHREAD_INTEGRATION_FINISHED_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'THREAD_INTEGRATION_FINISHED_FLAG'.
	return this->BUFF_UPCI_I_DS[this->BUFF_UPCI_ID_STORAGE_FLAG_ACT].GetTHREAD_INTEGRATION_FINISHED_FLAG();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método Get para obtener bandera 'SET_SIGNAL_FLAG'.
in GUPCI_SDS::GetSET_SIGNAL_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera SET_SIGNAL_FLAG.
	return this->SET_SIGNAL_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para obtener el estado de al bandera 'PAUSE_ACTIVE_THREADS_FLAG'.
in GUPCI_SDS::GetPAUSE_ACTIVE_THREADS_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera PAUSE_ACTIVE_THREADS_FLAG.
	return this->BUFF_UPCI_I_DS[this->BUFF_UPCI_ID_STORAGE_FLAG_ACT].GetPAUSE_ACTIVE_THREADS_FLAG();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para obtener el contador de iteraciones de la gupci.
in GUPCI_SDS::GetGUPCI_ITERATION_COUNTER()
{
	//---------------------------------------------------------------------------------
	//retorno del contador de iteraciones.
	return this->GUPCI_ITERATION_COUNTER;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para obtener el contador de iteraciones del kernel.
in GUPCI_SDS::GetKERNEL_ITERATION_COUNTER()
{
	//---------------------------------------------------------------------------------
	//retorno del contador de iteraciones del kernel.
	return this->BUFF_UPCI_I_DS[this->BUFF_UPCI_ID_STORAGE_FLAG_ACT].KERNEL_ITERATION_COUNTER;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para obtener el contador de iteraciones del Hilo.
in GUPCI_SDS::GetTHREAD_ITERATION_COUNTER()
{
	//---------------------------------------------------------------------------------
	//retorno del contador de iteraciones del Hilo.
	return this->BUFF_UPCI_I_DS[this->BUFF_UPCI_ID_STORAGE_FLAG_ACT].THREAD_ITERATION_COUNTER;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para obtener el contador de diferenciaciones globales de estructuras.
in GUPCI_SDS::GetGLOBAL_DIFFERENTIATION_COUNTER()
{
	//---------------------------------------------------------------------------------
	//retorno del contador de diferenciaciones gloables.
	return this->BUFF_UPCI_I_DS[this->BUFF_UPCI_ID_STORAGE_FLAG_ACT].GLOBAL_DIFFERENTIATION_COUNTER;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para setear el estado de la bandera 'SUSPENDED_ACTIONS_MAXIMIZATION_FLAG'. 
vo GUPCI_SDS::SetSUSPENDED_ACTIONS_MAXIMIZATION_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'SUSPENDED_ACTIONS_MAXIMIZATION_FLAG'.
	this->SUSPENDED_ACTIONS_MAXIMIZATION_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para setear el estado de la bandera 'STRUCTURES_RECOGNITION_FLAG'. 
vo GUPCI_SDS::SetSTRUCTURES_RECOGNITION_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'STRUCTURES_RECOGNITION_FLAG'.
	this->STRUCTURES_RECOGNITION_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para setear el estado de la bandera 'STRUCTURES_PROJECTIONS_FLAG'. 
vo GUPCI_SDS::SetSTRUCTURES_PROJECTIONS_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'STRUCTURES_PROJECTIONS_FLAG'.
	this->STRUCTURES_PROJECTIONS_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para setear el estado de al bandera 'CLOSE_ACTIVE_THREADS_FLAG'.
vo GUPCI_SDS::SetCLOSE_ACTIVE_THREADS_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'CLOSE_ACTIVE_THREADS_FLAG'.
	this->CLOSE_ACTIVE_THREADS_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método para setear el estado de al bandera 'PAUSE_ACTIVE_THREADS_FLAG'.
vo GUPCI_SDS::SetPAUSE_ACTIVE_THREADS_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'PAUSE_ACTIVE_THREADS_FLAG'.
	this->PAUSE_ACTIVE_THREADS_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#6: método Set para setear bandera 'SET_SIGNAL_FLAG'.
vo GUPCI_SDS::SetSET_SIGNAL_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo de la bandera 'SET_SIGNAL_FLAG'.
	this->SET_SIGNAL_FLAG	= _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método de asignación de señales de entrada de la gupci.
vo GUPCI_SDS::SetInputData(dou _input, dou _input_evaluation)
{
	//-----------------------------------------------------------------------------
	//asignación de señal de entrada de la gupci.
	this->INPUT_SIGNAL.push_back(_input);

	//-----------------------------------------------------------------------------
	//asignación de señal de evaluación de entrada de la gupci.
	this->EVALUATION_SIGNAL.push_back(_input_evaluation);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método de asignación de señales de salida de la gupci.
vo GUPCI_SDS::SetOutputData(st _action)
{
	//---------------------------------------------------------------------------------
	//asignación de señal de salida de la gupci.
	this->OUTPUT_SIGNAL.push_back(_action);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------- 
//#1: método para imprimir banderas.
vo GUPCI_SDS::PrintBuffBanderas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//carga de banderas.
	cout << "STORAGE_FLAG                                : " << this->BUFF_UPCI_I_DS.at(_upci_id).STORAGE_FLAG<< endl;
	cout << "KERNEL_INTEGRATION_FLAG                     : " << this->BUFF_UPCI_I_DS.at(_upci_id).KERNEL_INTEGRATION_FLAG<< endl;
	cout << "KERNEL_CONTROL_INTEGRATION_FLAG             : " << this->BUFF_UPCI_I_DS.at(_upci_id).KERNEL_CONTROL_INTEGRATION_FLAG<< endl;
	cout << "KERNEL_CONTROL_INTEGRATION_FINISHED_FLAG    : " << this->BUFF_UPCI_I_DS.at(_upci_id).KERNEL_CONTROL_INTEGRATION_FINISHED_FLAG << endl;
	cout << "THREAD_INTEGRATION_FLAG                     : " << this->BUFF_UPCI_I_DS.at(_upci_id).THREAD_INTEGRATION_FLAG<< endl;
	cout << "THREAD_INTEGRATION_LATENCY_FLAG             : " << this->BUFF_UPCI_I_DS.at(_upci_id).THREAD_INTEGRATION_LATENCY_FLAG<< endl;
	cout << "THREAD_INTEGRATION_FINISHED_FLAG            : " << this->BUFF_UPCI_I_DS.at(_upci_id).THREAD_INTEGRATION_FINISHED_FLAG<< endl;
	cout << "SUSPENDED_STRUCTURES_FLAG                    : " << this->BUFF_UPCI_I_DS.at(_upci_id).SUSPENDED_STRUCTURES_FLAG<< endl;				
	cout << "NEW_INPUT_FLAG                              : " << this->BUFF_UPCI_I_DS.at(_upci_id).NEW_INPUT_FLAG<< endl;
	cout << "CLOSE_ACTIVE_THREADS_FLAG                   : " << this->BUFF_UPCI_I_DS.at(_upci_id).CLOSE_ACTIVE_THREADS_FLAG << endl;
	cout << "PAUSE_ACTIVE_THREADS_FLAG                   : " << this->BUFF_UPCI_I_DS.at(_upci_id).PAUSE_ACTIVE_THREADS_FLAG << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para imprimir buffers del núcleo.
vo GUPCI_SDS::PrintBuffNucleo(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//carga de buffers del núcleo.
	cout << "UPCI_ID OF STR_MAX_AL : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_STR_MAX_AL->UPCI_ID<< endl;
	cout << "STR_ID OF STR MAX_AL  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_STR_MAX_AL->STR_ID << endl;
	cout << "MAX_ACTIVITY_LEVEL    : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_MAX_ACTIVITY_LEVEL<< endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------  
//#3: método para imprimir buffer de las direcciones de las upci conectadas.
vo GUPCI_SDS::PrintBuffDirUpc(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam1	= 0;

	//---------------------------------------------------------------------------------
	//variable auxiliar para la cantidad.
	tam1 = in(((deque<UPCI_I_DS>*)(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_UPCI_I_DS))->size());
	
	//---------------------------------------------------------------------------------
	//bucle para cargar direcciones.
	for (in i1 = 0; i1 < tam1; i1++)
	{
		//-----------------------------------------------------------------------------
		//carga de buffers de las direcciones.
		cout << "id("<<i1<<"): " << &(((deque<UPCI_I_DS>*)(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_UPCI_I_DS))->at(i1))<< endl;
	}	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para imprimir buffers de estructuras INIS.
vo GUPCI_SDS::PrintBuffEstructurasINIS(in _upci_id, in _str_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam1	= 0;
	
	//---------------------------------------------------------------------------------
	//carga de registro IN_RG.
	cout << "IN_RG  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS[_str_id].IN_RG << endl;

	//---------------------------------------------------------------------------------
	//carga de registro EV_RG.
	cout << "EV_RG  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS[_str_id].EV_RG << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de sub-registros.
	cout << "CS_SRG : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS[_str_id].CS_SRG << endl;
	cout << "AL_SRG : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS[_str_id].AL_SRG << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//obtención del tamaño del vector de relaciones de la estructura.
	tam1 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS[_str_id].RL.size());

	//---------------------------------------------------------------------------------
	//bucle para cargar relaciones RL.
	for (in i2 = 0; i2 < tam1; i2++)
	{
		//-----------------------------------------------------------------------------
		//cargar de relaciones.
		cout << "rl(" << i2 << ") tipo      : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS[_str_id].RL[i2].at(0) << endl;
		cout << "rl(" << i2 << ") id        : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS[_str_id].RL[i2].at(1) << endl;		
		cout << "rl(" << i2 << ") upci id   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS[_str_id].RL[i2].at(2) << endl;
		cout << endl;
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método para imprimir buffers de estructuras ACIS.
vo GUPCI_SDS::PrintBuffEstructurasACIS(in _upci_id, in _str_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam1	= 0;

	//---------------------------------------------------------------------------------
	//carga de registro AC_RG.
	cout << "AC_RG  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS[_str_id].AC_RG << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de sub-registros.
	cout << "CS_SRG : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS[_str_id].CS_SRG << endl;
	cout << "AL_SRG : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS[_str_id].AL_SRG << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//obtención del tamaño del vector de relaciones de la estructura.
	tam1 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS[_str_id].RL.size());

	//---------------------------------------------------------------------------------
	//bucle para cargar relaciones RL.
	for (in i2 = 0; i2 < tam1; i2++)
	{
		//-----------------------------------------------------------------------------
		//cargar de relaciones.
		cout << "rl(" << i2 << ") tipo      : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS[_str_id].RL[i2].at(0) << endl;
		cout << "rl(" << i2 << ") id        : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS[_str_id].RL[i2].at(1) << endl;
		cout << "rl(" << i2 << ") upci id   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS[_str_id].RL[i2].at(2) << endl;
		cout << endl;
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#6: método para imprimir buffers de estructuras PFRLIS.
vo GUPCI_SDS::PrintBuffEstructurasPFRLIS(in _upci_id, in _str_id)
{
	//---------------------------------------------------------------------------------
	//carga de registros.
	cout << "STR1_TYPE_RG       : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS[_str_id].STR1_TYPE_RG << endl;
	cout << "STR2_TYPE_RG       : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS[_str_id].STR2_TYPE_RG << endl;
	cout << "STR1_ID_RG         : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS[_str_id].STR1_ID_RG << endl;
	cout << "STR2_ID_RG         : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS[_str_id].STR2_ID_RG << endl;
	cout << "UPCI_ID_STR1_RG    : " << (in)(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS[_str_id].UPCI_ID_STR1_RG) << endl;
	cout << "UPCI_ID_STR2_RG    : " << (in)(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS[_str_id].UPCI_ID_STR2_RG) << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de sub-registros.
	cout << "RS_SRG             : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS[_str_id].RS_SRG << endl;
	cout << "AL_SRG             : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS[_str_id].AL_SRG << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#7: método para imprimir buffers de estructuras INDFRLIS.
vo GUPCI_SDS::PrintBuffEstructurasINDFRLIS(in _upci_id, in _str_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam1	= 0;

	//---------------------------------------------------------------------------------
	//carga de registro IN_DIF_RG.
	cout << "IN_DIF_RG          : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS[_str_id].IN_DIF_RG << endl;

	//---------------------------------------------------------------------------------
	//carga de registro EV_DIF_RG.
	cout << "EV_DIF_RG          : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS[_str_id].EV_DIF_RG << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de registros
	cout << "STR1_ID_RG         : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS[_str_id].STR1_ID_RG << endl;
	cout << "STR2_ID_RG         : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS[_str_id].STR2_ID_RG << endl;
	cout << "UPCI_ID_STR1_RG    : " << (in)(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS[_str_id].UPCI_ID_STR1_RG) << endl;
	cout << "UPCI_ID_STR2_RG    : " << (in)(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS[_str_id].UPCI_ID_STR2_RG) << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de sub-registros.
	cout << "CS_SRG             : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS[_str_id].CS_SRG << endl;
	cout << "RS_SRG             : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS[_str_id].RS_SRG << endl;
	cout << "AL_SRG             : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS[_str_id].AL_SRG << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//obtención del tamaño del vector de relaciones de la estructura.
	tam1 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS[_str_id].RL.size());

	//---------------------------------------------------------------------------------
	//bucle para cargar relaciones RL.
	for (in i2 = 0; i2 < tam1; i2++)
	{
		//-----------------------------------------------------------------------------
		//cargar de relaciones.
		cout << "rl(" << i2 << ") tipo      : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS[_str_id].RL[i2].at(0) << endl;
		cout << "rl(" << i2 << ") id        : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS[_str_id].RL[i2].at(1) << endl;
		cout << "rl(" << i2 << ") upci id   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS[_str_id].RL[i2].at(2) << endl;
		cout << endl;
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#8: método para imprimir buffers de estructuras INPRRLIS.
vo GUPCI_SDS::PrintBuffEstructurasINPRRLIS(in _upci_id, in _str_id)
{
	//---------------------------------------------------------------------------------
	//carga de registro IN_PRO_RG.
	cout << "IN_PRO_RG          : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS[_str_id].IN_PRO_RG << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de registros
	cout << "STR1_ID_RG         : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS[_str_id].STR1_ID_RG << endl;
	cout << "STR2_ID_RG         : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS[_str_id].STR2_ID_RG << endl;
	cout << "UPCI_ID_STR1_RG    : " << (in)(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS[_str_id].UPCI_ID_STR1_RG) << endl;
	cout << "UPCI_ID_STR2_RG    : " << (in)(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS[_str_id].UPCI_ID_STR2_RG) << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de sub-registros.
	cout << "CS_SRG             : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS[_str_id].CS_SRG << endl;
	cout << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#9: método para imprimir estructuras candidatas INIS.
vo GUPCI_SDS::PrintBuffINISCandidatas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam0					= 0;
	in tam1					= 0;
	in tam2					= 0;

	//-----------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_INIS_ID_CAN.
	tam0 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_ID_CAN->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir datos de los candidatos en los tiempos.
	for (in i1 = 0; i1 < tam0; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del tamaño del vector BUFF_INIS_ID_CAN en tiempo [i1].
		tam1 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_ID_CAN->at(i1).size());

		//-----------------------------------------------------------------------------
		//bucle para imprimir datos de los candidatos por cada upci.
		for (in i2 = 0; i2 < tam1; i2++)
		{
			//-------------------------------------------------------------------------
			//obtención del tamaño del vector BUFF_INIS_ID_CAN[i1][i2].
			tam2 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_ID_CAN->at(i1).at(i2).size());

			//-------------------------------------------------------------------------
			//bucle para imprimir datos de los candidatos.
			for (in i3 = 0; i3 < tam2; i3++)
			{
				//---------------------------------------------------------------------
				//carga de datos.
				cout << "tiempo("<<i1<<") upci_id("<<i2<<"): " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_ID_CAN->at(i1).at(i2).at(i3)<< endl;
			}
		}
	}	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#10: método para imprimir estructuras candidatas ACIS.
vo GUPCI_SDS::PrintBuffACISCandidatas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam0					= 0;
	in tam1					= 0;
	in tam2					= 0;

	//-----------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_ACIS_ID_CAN.
	tam0 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_ID_CAN->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir datos de los candidatos en los tiempos.
	for (in i1 = 0; i1 < tam0; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del tamaño del vector BUFF_ACIS_ID_CAN en tiempo [i1].
		tam1 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_ID_CAN->at(i1).size());

		//-----------------------------------------------------------------------------
		//bucle para imprimir datos de los candidatos por cada upci.
		for (in i2 = 0; i2 < tam1; i2++)
		{
			//-------------------------------------------------------------------------
			//obtención del tamaño del vector BUFF_ACIS_ID_CAN[i2][i2].
			tam2 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_ID_CAN->at(i1).at(i2).size());

			//-------------------------------------------------------------------------
			//bucle para imprimir datos de los candidatos.
			for (in i3 = 0; i3 < tam2; i3++)
			{
				//---------------------------------------------------------------------
				//carga de datos.
				cout << "tiempo(" << i1 << ") upci_id(" << i2 << "): " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_ID_CAN->at(i1).at(i2).at(i3) << endl;
			}
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#11: método para imprimir estructuras candidatas INDFRLIS.
vo GUPCI_SDS::PrintBuffINDFRLISCandidatas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam0					= 0;
	in tam1					= 0;
	in tam2					= 0;

	//-----------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_INDFRLIS_ID_CAN.
	tam0 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_ID_CAN->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir datos de los candidatos en los tiempos.
	for (in i1 = 0; i1 < tam0; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del tamaño del vector BUFF_INDFRLIS_ID_CAN en tiempo [i1].
		tam1 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_ID_CAN->at(i1).size());

		//-----------------------------------------------------------------------------
		//bucle para imprimir datos de los candidatos por cada upci.
		for (in i2 = 0; i2 < tam1; i2++)
		{
			//-------------------------------------------------------------------------
			//obtención del tamaño del vector BUFF_INDFRLIS_ID_CAN[i1][i2].
			tam2 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_ID_CAN->at(i1).at(i2).size());

			//-------------------------------------------------------------------------
			//bucle para imprimir datos de los candidatos.
			for (in i3 = 0; i3 < tam2; i3++)
			{
				//---------------------------------------------------------------------
				//carga de datos.
				cout << "tiempo(" << i1 << ") upci_id(" << i2 << "): " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_ID_CAN->at(i1).at(i2).at(i3) << endl;
			}
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#12: método para imprimir estructuras candidatas INPRRLIS.
vo GUPCI_SDS::PrintBuffINPRRLISCandidatas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam0					= 0;
	in tam1					= 0;
	in tam2					= 0;

	//-----------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_INPRRLIS_ID_CAN.
	tam0 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS_ID_CAN->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir datos de los candidatos en los tiempos.
	for (in i1 = 0; i1 < tam0; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del tamaño del vector BUFF_INPRRLIS_ID_CAN en tiempo [i1].
		tam1 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS_ID_CAN->at(i1).size());

		//-----------------------------------------------------------------------------
		//bucle para imprimir datos de los candidatos por cada upci.
		for (in i2 = 0; i2 < tam1; i2++)
		{
			//-------------------------------------------------------------------------
			//obtención del tamaño del vector BUFF_INPRRLIS_ID_CAN[i1][i2].
			tam2 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS_ID_CAN->at(i1).at(i2).size());

			//-------------------------------------------------------------------------
			//bucle para imprimir datos de los candidatos.
			for (in i3 = 0; i3 < tam2; i3++)
			{
				//---------------------------------------------------------------------
				//carga de datos.
				cout << "tiempo(" << i1 << ") upci_id(" << i2 << "): " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS_ID_CAN->at(i1).at(i2).at(i3) << endl;
			}
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#13: método para imprimir las id de upci con estructuras INIS candidatas.
vo GUPCI_SDS::PrintBuffIdUpcINISCandidatas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam0	= 0;
	in tam1	= 0;

	//-----------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_UPCI_ID_INIS_CAN.
	tam0 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_UPCI_ID_INIS_CAN->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir las id upci con estructuras candidatas en los dos tiempos.
	for (in i1 = 0; i1 < tam0; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del tamaño del vector BUFF_UPCI_ID_INIS_CAN.
		tam1 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_UPCI_ID_INIS_CAN->at(i1).size());

		//-----------------------------------------------------------------------------
		//bucle para imprimir las id upci con estructuras candidatas.
		for (in i2 = 0; i2 < tam1; i2++)
		{
			//-------------------------------------------------------------------------
			//carga del id.
			cout << "id: " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_UPCI_ID_INIS_CAN->at(i1).at(i2)<< endl;
		}
	}	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#14: método para imprimir las id de upci con estructuras ACIS candidatas.
vo GUPCI_SDS::PrintBuffIdUpcACISCandidatas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam0	= 0;
	in tam1	= 0;

	//-----------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_UPCI_ID_ACIS_CAN.
	tam0 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_UPCI_ID_ACIS_CAN->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir las id upci con estructuras candidatas en los dos tiempos.
	for (in i1 = 0; i1 < tam0; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del tamaño del vector BUFF_UPCI_ID_ACIS_CAN.
		tam1 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_UPCI_ID_ACIS_CAN->at(i1).size());

		//-----------------------------------------------------------------------------
		//bucle para imprimir las id upci con estructuras candidatas.
		for (in i2 = 0; i2 < tam1; i2++)
		{
			//-------------------------------------------------------------------------
			//carga del id.
			cout << "id: " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_UPCI_ID_ACIS_CAN->at(i1).at(i2)<< endl;
		}
	}	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#15: método para imprimir las id de upci con estructuras INDFRLIS candidatas.
vo GUPCI_SDS::PrintBuffIdUpcINDFRLISCandidatas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam0 = 0;
	in tam1 = 0;

	//-----------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_UPCI_ID_INDFRLIS_CAN.
	tam0 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_UPCI_ID_INDFRLIS_CAN->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir las id upci con estructuras candidatas en los dos tiempos.
	for (in i1 = 0; i1 < tam0; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del tamaño del vector BUFF_UPCI_ID_INDFRLIS_CAN.
		tam1 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_UPCI_ID_INDFRLIS_CAN->at(i1).size());

		//-----------------------------------------------------------------------------
		//bucle para imprimir las id upci con estructuras candidatas.
		for (in i2 = 0; i2 < tam1; i2++)
		{
			//-------------------------------------------------------------------------
			//carga del id.
			cout << "id: " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_UPCI_ID_INDFRLIS_CAN->at(i1).at(i2) << endl;
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#16: método para imprimir las id de upci con estructuras INPRRLIS candidatas.
vo GUPCI_SDS::PrintBuffIdUpcINPRRLISCandidatas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam0 = 0;
	in tam1 = 0;

	//-----------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_UPCI_ID_INPRRLIS_CAN.
	tam0 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_UPCI_ID_INPRRLIS_CAN->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir las id upci con estructuras candidatas en los dos tiempos.
	for (in i1 = 0; i1 < tam0; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del tamaño del vector BUFF_UPCI_ID_INPRRLIS_CAN.
		tam1 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_UPCI_ID_INPRRLIS_CAN->at(i1).size());

		//-----------------------------------------------------------------------------
		//bucle para imprimir las id upci con estructuras candidatas.
		for (in i2 = 0; i2 < tam1; i2++)
		{
			//-------------------------------------------------------------------------
			//carga del id.
			cout << "id: " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_UPCI_ID_INPRRLIS_CAN->at(i1).at(i2) << endl;
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#17: método para imprimir buffer de los id de estructuras disponibles.
vo GUPCI_SDS::PrintBuffIdEstDisponibles(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//carga de buffers para los id de las estructura disponibles.
	cout << "BUFF_INIS_ID_AV[0]   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_ID_AV[0]<< endl;					
	cout << "BUFF_INIS_ID_AV[1]   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_ID_AV[1]<< endl;	
	cout << endl;
	cout << "BUFF_ACIS_ID_AV[0]    : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_ID_AV[0]<< endl;
	cout << "BUFF_ACIS_ID_AV[1]    : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_ID_AV[1]<< endl;
	cout << endl;
	cout << "BUFF_PFRLIS_ID_AV[0]   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS_ID_AV[0]<< endl;
	cout << "BUFF_PFRLIS_ID_AV[1]   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS_ID_AV[1]<< endl;
	cout << endl;
	cout << "BUFF_INDFRLIS_ID_AV[0] : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_ID_AV[0]<< endl;
	cout << "BUFF_INDFRLIS_ID_AV[1] : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_ID_AV[1]<< endl;
	cout << endl;
	cout << "BUFF_INPRRLIS_ID_AV[0] : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS_ID_AV[0]<< endl;
	cout << "BUFF_INPRRLIS_ID_AV[1] : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS_ID_AV[1]<< endl;
	cout << endl;
}

//-------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------- 
//#18: método para imprimir buffer de los id y tipos de estructuras creadas.
vo GUPCI_SDS::PrintBuffIdYTipoEstCreadas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//carga de buffers para los id y tipos de las estructuras creadas.
	cout << "BUFF_INIS_CRE[0].UPCI_ID  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_CRE[0].UPCI_ID<< endl;
	cout << "BUFF_INIS_CRE[1].UPCI_ID  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_CRE[1].UPCI_ID<< endl;
	cout << endl;
	cout << "BUFF_ACIS_CRE[0].UPCI_ID  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_CRE[0].UPCI_ID << endl;
	cout << "BUFF_ACIS_CRE[1].UPCI_ID  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_CRE[1].UPCI_ID << endl;
	cout << endl;
	cout << "BUFF_INIS_CRE[0].STR_ID   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_CRE[0].STR_ID<< endl;
	cout << "BUFF_INIS_CRE[1].STR_ID   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_CRE[1].STR_ID<< endl;
	cout << endl;
	cout << "BUFF_ACIS_CRE[0].STR_ID   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_CRE[0].STR_ID << endl;
	cout << "BUFF_ACIS_CRE[1].STR_ID   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_CRE[1].STR_ID << endl;
	cout << endl;
	cout << "BUFF_INDFRLIS_CRE[0].STR_ID : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_CRE[0].STR_ID << endl;
	cout << "BUFF_INDFRLIS_CRE[1].STR_ID : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_CRE[1].STR_ID << endl;
	cout << endl;
	cout << "BUFF_INPRRLIS_CRE[0].STR_ID : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS_CRE[0].STR_ID << endl;
	cout << "BUFF_INPRRLIS_CRE[1].STR_ID : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS_CRE[1].STR_ID << endl;	
	cout << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------  
//#19: método para imprimir buffer de los id de estructuras reconocidas.
vo GUPCI_SDS::PrintBuffEstReconocidas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//estructuras INIS.
	cout << "INIS-UPCI_ID     : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_RE->UPCI_ID<< endl;
	cout << "INIS-STR_ID      : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_RE->STR_ID<< endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//estructuras ACIS.
	cout << "ACIS-UPCI_ID      : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_RE->UPCI_ID<< endl;
	cout << "ACIS-STR_ID       : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_RE->STR_ID<< endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//estructuras INDFRLIS.
	cout << "INDFRLIS-UPCI_ID   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_RE->UPCI_ID<< endl;
	cout << "INDFRLIS-STR_ID    : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_RE->STR_ID<< endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//estructuras INPRRLIS.
	cout << "INPRRLIS-UPCI_ID   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS_RE->UPCI_ID<< endl;
	cout << "INPRRLIS-STR_ID    : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS_RE->STR_ID<< endl;
	cout << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#20: método para imprimir buffer cantidades de upci y estructuras, 
//y ids de las estructuras en suspensión.
vo GUPCI_SDS::PrintBuffCantUpciEstSuspension(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam1					= 0;

	//---------------------------------------------------------------------------------
	//carga de la cantidad total de estructuras INIS en estado de suspensión.
	cout << "BUFF_INIS_SUS AMOUNT  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_SUS->size()<< endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de la cantidad total de estructuras INIS en estado de suspensión.
	cout << "BUFF_ACIS_SUS AMOUNT  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_SUS->size() << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de la cantidad total de estructuras INIS en estado de suspensión.
	cout << "BUFF_PFRLIS_SUS AMOUNT  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS_SUS->size() << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de la cantidad total de estructuras INIS en estado de suspensión.
	cout << "BUFF_INDFRLIS_SUS AMOUNT  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_SUS->size() << endl;
	cout << endl;
	
	//---------------------------------------------------------------------------------
	//impresión de INIS suspendidos.
	cout << "INIS: " << endl;

	//---------------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_INIS_SUS.
	tam1 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_SUS->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir id de las estructuras INIS en estado de suspensión.
	for (in i1 = 0; i1 < tam1; i1++)
	{
		//-----------------------------------------------------------------------------
		//carga de los id de las estructuras en estado de suspensión.
		cout << "id upci  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_SUS->at(i1).UPCI_ID<< endl;
		cout << "id str   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_SUS->at(i1).STR_ID<< endl;
		cout << endl;
	}

	//---------------------------------------------------------------------------------
	//impresión de ACIS suspendidos.
	cout << "ACIS: " << endl;

	//---------------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_ACIS_SUS.
	tam1 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_SUS->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir id de las estructuras ACIS en estado de suspensión.
	for (in i1 = 0; i1 < tam1; i1++)
	{
		//-----------------------------------------------------------------------------
		//carga de los id de las estructuras en estado de suspensión.
		cout << "id upci  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_SUS->at(i1).UPCI_ID << endl;
		cout << "id str   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_SUS->at(i1).STR_ID << endl;
		cout << endl;
	}

	//---------------------------------------------------------------------------------
	//impresión de PFRLIS suspendidos.
	cout << "PFRLIS: " << endl;

	//---------------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_PFRLIS_SUS.
	tam1 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS_SUS->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir id de las estructuras PFRLIS en estado de suspensión.
	for (in i1 = 0; i1 < tam1; i1++)
	{
		//-----------------------------------------------------------------------------
		//carga de los id de las estructuras en estado de suspensión.
		cout << "id upci  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS_SUS->at(i1).UPCI_ID << endl;
		cout << "id str   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS_SUS->at(i1).STR_ID << endl;
		cout << endl;
	}

	//---------------------------------------------------------------------------------
	//impresión de INDFRLIS suspendidos.
	cout << "INDFRLIS: " << endl;

	//---------------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_INDFRLIS_SUS.
	tam1 = in(this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_SUS->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir id de las estructuras INDFRLIS en estado de suspensión.
	for (in i1 = 0; i1 < tam1; i1++)
	{
		//-----------------------------------------------------------------------------
		//carga de los id de las estructuras en estado de suspensión.
		cout << "id upci  : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_SUS->at(i1).UPCI_ID << endl;
		cout << "id str   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_SUS->at(i1).STR_ID << endl;
		cout << endl;
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#21: método para imprimir buffer con la scantidades de estructuras existentes.
vo GUPCI_SDS::PrintBuffCantEstExistentes(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//buffers auxiliares para almacenar los ids.
	in	var_aux				= OFF;															//variable auxiliar de impresión.
	sst	buff_aux;																			//buffer auxiliar.
	st	buff_inis_id;																		//buffer para inis.
	st	buff_lacis_id;																		//buffer para lacis.
	st	buff_pfrlis_id;																		//buffer para pfrlis.
	st	buff_indfrlis_id;																	//buffer para indfrlis.
	st	buff_inprrlis_id;																	//buffer para inprrlis.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para obtener los ids de inis inicializados.
	for (in i1 = 0; i1 < this->BUFF_UPCI_I_DS.at(_upci_id).INIS_AMOUNT_ALLOWED; i1++)
	{
		//-----------------------------------------------------------------------------
		//si es la primera iteración, entonces.
		if (var_aux == OFF)
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS[i1].AL_SRG != -1)
			{
				//---------------------------------------------------------------------
				//limpieza y seteo del id.
				buff_aux		<< i1;
				buff_inis_id	= buff_aux.str();
				var_aux			= ON;
			}
		}

		//-----------------------------------------------------------------------------
		//si es después de la primera iteración, entonces.
		else 
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS[i1].AL_SRG != -1)
			{
				//---------------------------------------------------------------------
				//limpieza y seteo del id.
				buff_aux.str("");
				buff_aux		<< i1;
				buff_inis_id	= buff_inis_id + ", " + buff_aux.str();
			}
		}		
	}

	//---------------------------------------------------------------------------------
	//reset de variable auxiliar de impresión.
	var_aux = OFF;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para obtener los ids de lacis inicializados.
	for (in i1 = 0; i1 < this->BUFF_UPCI_I_DS.at(_upci_id).ACIS_AMOUNT_ALLOWED; i1++)
	{
		//-----------------------------------------------------------------------------
		//si es la primera iteración, entonces.
		if (var_aux == OFF)
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS[i1].AL_SRG != -1)
			{
				//---------------------------------------------------------------------
				//limpieza y seteo del id.
				buff_aux.str("");
				buff_aux		<< i1;
				buff_lacis_id	= buff_aux.str();
				var_aux			= ON;
			}
		}

		//-----------------------------------------------------------------------------
		//si es después de la primera iteración, entonces.
		else 
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS[i1].AL_SRG != -1)
			{
				//---------------------------------------------------------------------
				//limpieza y seteo del id.
				buff_aux.str("");
				buff_aux		<< i1;
				buff_lacis_id	= buff_lacis_id + ", " + buff_aux.str();
			}
		}		
	}
	
	//---------------------------------------------------------------------------------
	//reset de variable auxiliar de impresión.
	var_aux = OFF;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para obtener los ids de pfrlis inicializados.
	for (in i1 = 0; i1 < this->BUFF_UPCI_I_DS.at(_upci_id).RLIS_AMOUNT_ALLOWED; i1++)
	{
		//-----------------------------------------------------------------------------
		//si es la primera iteración, entonces.
		if (var_aux == OFF)
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS[i1].RS_SRG != -1)
			{
				//---------------------------------------------------------------------
				//limpieza y seteo del id.
				buff_aux.str("");
				buff_aux		<< i1;
				buff_pfrlis_id	= buff_aux.str();
				var_aux			= ON;
			}
		}

		//-----------------------------------------------------------------------------
		//si es después de la primera iteración, entonces.
		else 
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS[i1].RS_SRG != -1)
			{
				//---------------------------------------------------------------------
				//limpieza y seteo del id.
				buff_aux.str("");
				buff_aux		<< i1;
				buff_pfrlis_id	= buff_pfrlis_id + ", " + buff_aux.str();
			}
		}		
	}

	//---------------------------------------------------------------------------------
	//reset de variable auxiliar de impresión.
	var_aux = OFF;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para obtener los ids de indfrlis inicializados.
	for (in i1 = 0; i1 < this->BUFF_UPCI_I_DS.at(_upci_id).RLIS_AMOUNT_ALLOWED; i1++)
	{
		//-----------------------------------------------------------------------------
		//si es la primera iteración, entonces.
		if (var_aux == OFF)
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS[i1].RS_SRG != -1)
			{
				//---------------------------------------------------------------------
				//limpieza y seteo del id.
				buff_aux.str("");
				buff_aux			<< i1;
				buff_indfrlis_id	= buff_aux.str();
				var_aux				= ON;
			}
		}

		//-----------------------------------------------------------------------------
		//si es después de la primera iteración, entonces.
		else 
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS[i1].RS_SRG != -1)
			{
				//---------------------------------------------------------------------
				//limpieza y seteo del id.
				buff_aux.str("");
				buff_aux			<< i1;
				buff_indfrlis_id	= buff_indfrlis_id + ", " + buff_aux.str();
			}
		}		
	}

	//---------------------------------------------------------------------------------
	//reset de variable auxiliar de impresión.
	var_aux = OFF;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para obtener los ids de inprrlis inicializados.
	for (in i1 = 0; i1 < this->BUFF_UPCI_I_DS.at(_upci_id).RLIS_AMOUNT_ALLOWED; i1++)
	{
		//-----------------------------------------------------------------------------
		//si es la primera iteración, entonces.
		if (var_aux == OFF)
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS[i1].CS_SRG != -1)
			{
				//---------------------------------------------------------------------
				//limpieza y seteo del id.
				buff_aux.str("");
				buff_aux			<< i1;
				buff_inprrlis_id	= buff_aux.str();
				var_aux				= ON;
			}
		}

		//-----------------------------------------------------------------------------
		//si es después de la primera iteración, entonces.
		else 
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS[i1].CS_SRG != -1)
			{
				//---------------------------------------------------------------------
				//limpieza y seteo del id.
				buff_aux.str("");
				buff_aux			<< i1;
				buff_inprrlis_id	= buff_inprrlis_id + ", " + buff_aux.str();
			}
		}		
	}

	//---------------------------------------------------------------------------------
	//carga de buffers para la cantidad de estructuras existentes.
	cout << "BUFF_INIS_INI_AMOUNT     : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_INI_AMOUNT<< ", con ids: "<< buff_inis_id <<endl;
	cout << "BUFF_ACIS_INI_AMOUNT     : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_INI_AMOUNT << ", con ids: " << buff_lacis_id << endl;
	cout << "BUFF_PFRLIS_INI_AMOUNT     : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS_INI_AMOUNT << ", con ids: " << buff_pfrlis_id << endl;
	cout << "BUFF_INDFRLIS_INI_AMOUNT   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_INI_AMOUNT << ", con ids: " << buff_indfrlis_id << endl;
	cout << "BUFF_INPRRLIS_INI_AMOUNT   : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS_INI_AMOUNT << ", con ids: " << buff_inprrlis_id << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#22: método para imprimir buffer con la cantidad de expansiones.
vo GUPCI_SDS::PrintBuffCantExp(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//carga de buffers para la cantidad de expansiones.
	cout << "GLOBAL_DIFFERENTIATION_COUNTER: " << this->BUFF_UPCI_I_DS.at(_upci_id).GLOBAL_DIFFERENTIATION_COUNTER<< endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#23: métoddo para imprimir buffer con los máximos id de las estructuras.
vo GUPCI_SDS::PrintBuffMaxIdEst(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//carga de buffers para los máximos ids.
	cout << "BUFF_INIS_MAX_ID[0]      : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_MAX_ID[0]<< endl;					
	cout << "BUFF_INIS_MAX_ID[1]      : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INIS_MAX_ID[1]<< endl;		
	cout << endl;
	cout << "BUFF_ACIS_MAX_ID[0]       : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_MAX_ID[0]<< endl;					
	cout << "BUFF_ACIS_MAX_ID[1]       : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_ACIS_MAX_ID[1]<< endl;	
	cout << endl;
	cout << "BUFF_PFRLIS_MAX_ID[0]      : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS_MAX_ID[0]<< endl;					
	cout << "BUFF_PFRLIS_MAX_ID[1]      : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_PFRLIS_MAX_ID[1]<< endl;
	cout << endl;
	cout << "BUFF_INDFRLIS_MAX_ID[0]    : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_MAX_ID[0]<< endl;
	cout << "BUFF_INDFRLIS_MAX_ID[1]    : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INDFRLIS_MAX_ID[1]<< endl;
	cout << endl;
	cout << "BUFF_INPRRLIS_MAX_ID[0]    : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS_MAX_ID[0]<< endl;
	cout << "BUFF_INPRRLIS_MAX_ID[1]    : " << this->BUFF_UPCI_I_DS.at(_upci_id).BUFF_INPRRLIS_MAX_ID[1]<< endl;
	cout << endl;
}