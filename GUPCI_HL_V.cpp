//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
Class Name	: 	  GUPCI_HL_V (Grupo de unidades de procesos cognitivos integradora tipo 'SDS').
Date	    :	  12:58 pm 12-06-2017.
Diseñador   :	  Gustavo Catalán Ulloa.
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include "GUPCI_HL_V.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//espacio de nombres.
using namespace UPC;
using namespace std;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método constructor "1".
GUPCI_HL_V::GUPCI_HL_V()
{	

}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método constructor "2" para cargar desde interfaz.
GUPCI_HL_V::GUPCI_HL_V(in _gupci_id, in _upci_amount, UPCI_HL_V_ARG &_upci_arg)
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
	//inicialización de parámetros de GUPCI.
	this->GUPCI_ID								=	_gupci_id;									//id de la GUPCI.
	this->UPCI_HL_V_AMOUNT						=	_upci_amount;								//cantidad de UPCI_HL_V.		

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## BANDERAS ##################################### 

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//inicialización de banderas para threads activos.
	this->CLOSE_ACTIVE_THREADS_FLAG				=	OFF;										//bandera para cerrar threads activos.
	this->PAUSE_ACTIVE_THREADS_FLAG				=	OFF;										//bandera para pausar threads activos.

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################### BUFFERS #####################################	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización del id de la upc con almacenamiento activo.
	this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT	=	0;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de buffers para registros.
	this->BUFF_IN_RG							=	_upci_arg.buff_in_rg;						//puntero a buffer para registro de entrada.
	this->BUFF_EV_RG							=	_upci_arg.buff_ev_rg;						//puntero a buffer para registro de evaluación de entrada.
	this->BUFF_IN_DIF_RG						=	NULL;										//buffer para registro de diferencia de entradas.
	this->BUFF_IN_PRO_RG						=	NULL;										//buffer para registro de proporción de diferencia de entradas.
	this->BUFF_OUTPUT_PROJECTION				=	_upci_arg.buff_output_projection;			//puntero a buffer para registro de proyección de salida.

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
	//inicialización de contador de iteraciones de la GUPCI.
	this->GUPCI_ITERATION_COUNTER				=	0;	

	//#################################################################################
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//######################### INICIALIZACIÓN DE GUPCI_HL_V ##########################

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de las upci.
	this->BUFF_UPCI_HL_V.resize(this->UPCI_HL_V_AMOUNT);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de punteros para buffers de las upci.
	_upci_arg.SetPtrBuff(&this->CLOSE_ACTIVE_THREADS_FLAG,
						 &this->PAUSE_ACTIVE_THREADS_FLAG,
						 &this->GUPCI_ID,
						 &this->BUFF_UPCI_HL_V,
						 &this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT,
						 &this->BUFF_IN_DIF_RG,
						 &this->BUFF_IN_PRO_RG,
						 &this->BUFF_INIS_MD_MAX_EVAL,
						 &this->BUFF_MAX_EVALUATION,
						 &this->BUFF_INIS_MD_MAX_AL,
						 &this->BUFF_MAX_ACTIVITY_LEVEL,	
						 &this->BUFF_STR_MAX_RS,
						 &this->BUFF_MAX_RELATION_STRENGTH,						 
						 this->BUFF_INIS_MD_ACTIVATED,
						 &this->BUFF_RL_INDEX_USED_IN_RECOGNITION,
						 &this->BUFF_INIS_MD_SUS,
						 &this->BUFF_SRLIS_SUS,
						 &this->BUFF_PFRLIS_SUS,
						 &this->BUFF_INDFRLIS_MD_SUS,
						 this->BUFF_INIS_MD_CRE,
					     this->BUFF_SRLIS_CRE,
						 this->BUFF_PFRLIS_CRE,
						 this->BUFF_INDFRLIS_MD_CRE,
						 this->BUFF_INPRRLIS_MD_CRE,	
						 &this->BUFF_INIS_MD_RE,
						 &this->BUFF_INDFRLIS_MD_RE,
						 &this->BUFF_INPRRLIS_MD_RE,
						 &this->BUFF_UPCI_ID_INIS_MD_CAN,
						 &this->BUFF_UPCI_ID_INDFRLIS_MD_CAN,
						 &this->BUFF_UPCI_ID_INPRRLIS_MD_CAN,
						 &this->BUFF_INIS_MD_ID_CAN,
						 &this->BUFF_INDFRLIS_MD_ID_CAN,
						 &this->BUFF_INPRRLIS_MD_ID_CAN);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializar upci.
	for (in i1 = 0; i1 < this->UPCI_HL_V_AMOUNT; i1++)
	{
		//-----------------------------------------------------------------------------
		//seteo de la upci que almacenará las entradas inicialmente.
		if (this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT == i1) STORAGE_FLAG = 1; else STORAGE_FLAG = 0;

		//-----------------------------------------------------------------------------
		//inicialización de upci.
		this->BUFF_UPCI_HL_V.at(i1).Initialize(i1, STORAGE_FLAG, _upci_arg);
	}	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método destructor.
GUPCI_HL_V::~GUPCI_HL_V()
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
in GUPCI_HL_V::Initialize(in _upci_amount, UPCI_HL_V_ARG &_upci_arg)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de gupc.
	this->Clean();

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## PARÁMETROS ################################### 

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//cantidad de UPCI_HL_V.
	this->UPCI_HL_V_AMOUNT						=	_upci_amount;									

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
	//inicialización de buffers para registros.
	this->BUFF_IN_RG							=	_upci_arg.buff_in_rg;						//puntero a buffer para registro de entrada.
	this->BUFF_EV_RG							=	_upci_arg.buff_ev_rg;						//puntero a buffer para registro de evaluación de entrada.
	this->BUFF_IN_DIF_RG						=	NULL;										//buffer para registro de diferencia de entradas.
	this->BUFF_IN_PRO_RG						=	NULL;										//buffer para registro de proporción de diferencia de entradas.
	this->BUFF_OUTPUT_PROJECTION				=	_upci_arg.buff_output_projection;			//puntero a buffer para registro de proyección de salida.
		
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
	//######################### INICIALIZACIÓN DE GUPCI_HL_V ##########################

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de las upci.
	this->BUFF_UPCI_HL_V.resize(this->UPCI_HL_V_AMOUNT);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de punteros para buffers de las upci.
	_upci_arg.SetPtrBuff(&this->CLOSE_ACTIVE_THREADS_FLAG,
						 &this->PAUSE_ACTIVE_THREADS_FLAG,
						 &this->GUPCI_ID,
						 &this->BUFF_UPCI_HL_V,
						 &this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT,
						 &this->BUFF_IN_DIF_RG,
						 &this->BUFF_IN_PRO_RG,
						 &this->BUFF_INIS_MD_MAX_EVAL,
						 &this->BUFF_MAX_EVALUATION,
						 &this->BUFF_INIS_MD_MAX_AL,
						 &this->BUFF_MAX_ACTIVITY_LEVEL,	
						 &this->BUFF_STR_MAX_RS,
						 &this->BUFF_MAX_RELATION_STRENGTH,						 
						 this->BUFF_INIS_MD_ACTIVATED,
						 &this->BUFF_RL_INDEX_USED_IN_RECOGNITION,
						 &this->BUFF_INIS_MD_SUS,
						 &this->BUFF_SRLIS_SUS,
						 &this->BUFF_PFRLIS_SUS,
						 &this->BUFF_INDFRLIS_MD_SUS,
						 this->BUFF_INIS_MD_CRE,
					     this->BUFF_SRLIS_CRE,
						 this->BUFF_PFRLIS_CRE,
						 this->BUFF_INDFRLIS_MD_CRE,
						 this->BUFF_INPRRLIS_MD_CRE,	
						 &this->BUFF_INIS_MD_RE,
						 &this->BUFF_INDFRLIS_MD_RE,
						 &this->BUFF_INPRRLIS_MD_RE,
						 &this->BUFF_UPCI_ID_INIS_MD_CAN,
						 &this->BUFF_UPCI_ID_INDFRLIS_MD_CAN,
						 &this->BUFF_UPCI_ID_INPRRLIS_MD_CAN,
						 &this->BUFF_INIS_MD_ID_CAN,
						 &this->BUFF_INDFRLIS_MD_ID_CAN,
						 &this->BUFF_INPRRLIS_MD_ID_CAN);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializar upci.
	for (in i1 = 0; i1 < this->UPCI_HL_V_AMOUNT; i1++)
	{	
		//-----------------------------------------------------------------------------
		//inicialización de upci.
		this->BUFF_UPCI_HL_V.at(i1).Initialize(_upci_arg);
	}

	//---------------------------------------------------------------------------------
	//successful execution.
	return SUCCESS;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método de inicialización para cargar desde interfaz.
in GUPCI_HL_V::Initialize(in _gupci_id, in _upci_amount, UPCI_HL_V_ARG &_upci_arg)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de gupc.
	this->Clean();

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
	//inicialización de parámetros de GUPCI.
	this->GUPCI_ID								=	_gupci_id;									//id de la GUPCI.
	this->UPCI_HL_V_AMOUNT						=	_upci_amount;								//cantidad de UPCI_HL_V.	

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################## BANDERAS ##################################### 

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//inicialización de banderas para threads activos.
	this->CLOSE_ACTIVE_THREADS_FLAG				=	OFF;										//bandera para cerrar threads activos.
	this->PAUSE_ACTIVE_THREADS_FLAG				=	OFF;										//bandera para pausar threads activos.

	//#################################################################################
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//################################### BUFFERS #####################################	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//incialización del id de la upc con almacenamiento activo.
	this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT	=	0;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de buffers para registros.
	this->BUFF_IN_RG							=	_upci_arg.buff_in_rg;						//puntero a buffer para registro de entrada.
	this->BUFF_EV_RG							=	_upci_arg.buff_ev_rg;						//puntero a buffer para registro de evaluación de entrada.
	this->BUFF_IN_DIF_RG						=	NULL;										//buffer para registro de diferencia de entradas.
	this->BUFF_IN_PRO_RG						=	NULL;										//buffer para registro de proporción de diferencia de entradas.
	this->BUFF_OUTPUT_PROJECTION				=	_upci_arg.buff_output_projection;			//puntero a buffer para registro de proyección de salida.

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
	//inicialización de contador de iteraciones de la GUPCI.
	this->GUPCI_ITERATION_COUNTER				=	0;	

	//#################################################################################
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//######################### INICIALIZACIÓN DE GUPCI_HL_V ##########################

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de las upci.
	this->BUFF_UPCI_HL_V.resize(this->UPCI_HL_V_AMOUNT);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de punteros para buffers de las upci.
	_upci_arg.SetPtrBuff(&this->CLOSE_ACTIVE_THREADS_FLAG,
						 &this->PAUSE_ACTIVE_THREADS_FLAG,
						 &this->GUPCI_ID,
						 &this->BUFF_UPCI_HL_V,
						 &this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT,
						 &this->BUFF_IN_DIF_RG,
						 &this->BUFF_IN_PRO_RG,
						 &this->BUFF_INIS_MD_MAX_EVAL,
						 &this->BUFF_MAX_EVALUATION,
						 &this->BUFF_INIS_MD_MAX_AL,
						 &this->BUFF_MAX_ACTIVITY_LEVEL,	
						 &this->BUFF_STR_MAX_RS,
						 &this->BUFF_MAX_RELATION_STRENGTH,						 
						 this->BUFF_INIS_MD_ACTIVATED,
						 &this->BUFF_RL_INDEX_USED_IN_RECOGNITION,
						 &this->BUFF_INIS_MD_SUS,
						 &this->BUFF_SRLIS_SUS,
						 &this->BUFF_PFRLIS_SUS,
						 &this->BUFF_INDFRLIS_MD_SUS,
						 this->BUFF_INIS_MD_CRE,
					     this->BUFF_SRLIS_CRE,
						 this->BUFF_PFRLIS_CRE,
						 this->BUFF_INDFRLIS_MD_CRE,
						 this->BUFF_INPRRLIS_MD_CRE,	
						 &this->BUFF_INIS_MD_RE,
						 &this->BUFF_INDFRLIS_MD_RE,
						 &this->BUFF_INPRRLIS_MD_RE,
						 &this->BUFF_UPCI_ID_INIS_MD_CAN,
						 &this->BUFF_UPCI_ID_INDFRLIS_MD_CAN,
						 &this->BUFF_UPCI_ID_INPRRLIS_MD_CAN,
						 &this->BUFF_INIS_MD_ID_CAN,
						 &this->BUFF_INDFRLIS_MD_ID_CAN,
						 &this->BUFF_INPRRLIS_MD_ID_CAN);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializar upci.
	for (in i1 = 0; i1 < this->UPCI_HL_V_AMOUNT; i1++)
	{
		//-----------------------------------------------------------------------------
		//seteo de la upci que almacenará las entradas inicialmente.
		if (this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT	 == i1) STORAGE_FLAG = 1; else STORAGE_FLAG = 0;

		//-----------------------------------------------------------------------------
		//inicialización de upci.
		this->BUFF_UPCI_HL_V.at(i1).Initialize(i1, STORAGE_FLAG, _upci_arg);
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
//#1: método para Clean totalmente la GUPCI.
in GUPCI_HL_V::Clean()
{	
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//término de thread de entrada de la GUPCI_HL_V.
	if (this->THREAD_GUPCI_INPUT.joinable()	== ON)	this->THREAD_GUPCI_INPUT.join();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de parámetros de GUPCI.
	this->GUPCI_ID									=	-1;									//id de la GUPCI.
	this->UPCI_HL_V_AMOUNT							=	-1;									//cantidad de UPCI_HL_V.			

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//limpieza de banderas para threads activos.
	this->CLOSE_ACTIVE_THREADS_FLAG					=	-1;									//bandera para cerrar threads activos.
	this->PAUSE_ACTIVE_THREADS_FLAG					=	-1;									//bandera para pausar threads activos.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de UPCI_HL_V.
	this->BUFF_UPCI_HL_V.clear();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza del buffer de argumentos de las upci.
	this->BUFF_UPCI_HL_V_ARG.Clean();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza del buffer de GUPCI para banderas de almacenamiento.
	this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT		=	-1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de buffers para registros.
	this->BUFF_IN_RG								=	NULL;								//puntero a buffer para registro de entrada.
	this->BUFF_EV_RG								=	NULL;								//puntero a buffer para registro de evaluación de entrada.
	this->BUFF_IN_DIF_RG							=	NULL;								//puntero a buffer para registro de diferencia de entradas.
	this->BUFF_IN_PRO_RG							=	NULL;								//puntero a buffer para registro de proporción de diferencia de entradas.
	this->BUFF_OUTPUT_PROJECTION					=	NULL;								//puntero a buffer para registro de proyección de salida.

	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//limpieza de buffers para estructura con evaluación máxima.
	this->BUFF_INIS_MD_MAX_EVAL.Clean();													//buffer para la estructura INIS_MD con máxima evaluación.
	this->BUFF_MAX_EVALUATION						=	NULL;								//buffer para la máxima evaluación.
	
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//limpieza de buffers para estructura con nivel de actividad máximo.
	this->BUFF_INIS_MD_MAX_AL.Clean();														//buffer para la estructura con nivel de actividad máximo.
	this->BUFF_MAX_ACTIVITY_LEVEL					=	-1;									//buffer para el máximo nivel de actividad.
	
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------  
	//limpieza de buffers para estructura con fortaleza de la relación máximo.
	this->BUFF_STR_MAX_RS.Clean();															//buffer para la estructura con fortaleza de la relación máximo.
	this->BUFF_MAX_RELATION_STRENGTH				=	-1;									//buffer para el máximo fortaleza de la relación.	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de buffer para las estructuras INIS_MD activadas.
	this->BUFF_INIS_MD_ACTIVATED[0].Clean();												//buffer para estructura INIS_MD activada presente.
	this->BUFF_INIS_MD_ACTIVATED[1].Clean();												//buffer para estructura INIS_MD activada pasada.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de los buffers para los ids de las estructuras creadas.
	this->BUFF_INIS_MD_CRE[0].Clean();														//buffer para id de INIS_MD creada actual.
	this->BUFF_INIS_MD_CRE[1].Clean();														//buffer para id de INIS_MD creada anterior.
	this->BUFF_SRLIS_CRE[0].Clean();														//buffer para id de SRLIS creada actual.
	this->BUFF_SRLIS_CRE[1].Clean();														//buffer para id de SRLIS creada anterior.
	this->BUFF_PFRLIS_CRE[0].Clean();														//buffer para id de PFRLIS creada actual.
	this->BUFF_PFRLIS_CRE[1].Clean();														//buffer para id de PFRLIS creada anterior.
	this->BUFF_INDFRLIS_MD_CRE[0].Clean();														//buffer para id de INDFRLIS_MD creada actual.
	this->BUFF_INDFRLIS_MD_CRE[1].Clean();														//buffer para id de INDFRLIS_MD creada anterior.
	this->BUFF_INPRRLIS_MD_CRE[0].Clean();														//buffer para id de INPRRLIS_MD creada actual.
	this->BUFF_INPRRLIS_MD_CRE[1].Clean();														//buffer para id de INPRRLIS_MD creada anterior.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de buffers para las estructuras en estado de suspensión.		
	this->BUFF_INIS_MD_SUS.clear();															//buffer para las estructuras INIS_MD suspendidas.
	this->BUFF_SRLIS_SUS.clear();															//buffer para las estructuras SRLIS suspendidas.
	this->BUFF_PFRLIS_SUS.clear();															//buffer para las estructuras PFRLIS suspendidas.
	this->BUFF_INDFRLIS_MD_SUS.clear();														//buffer para las estructuras INDFRLIS_MD suspendidas.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de buffers para los id de las upci candidatas. [a][b]: a: tiempo, b: upci.
	this->BUFF_UPCI_ID_INIS_MD_CAN.clear();											//buffer a id de las upci candidatas para INIS_MD.
	this->BUFF_UPCI_ID_INDFRLIS_MD_CAN.clear();											//buffer a id de las upci candidatas para INDFRLIS_MD.
	this->BUFF_UPCI_ID_INPRRLIS_MD_CAN.clear();											//buffer a id de las upci candidatas para INPRRLIS_MD.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza de buffers de GUPCI a estructuras candidatas. 
	//[a][b][c]: a: tiempo, b: upci, c: buffer de estructura.
	this->BUFF_INIS_MD_ID_CAN.clear();														//buffer de ids de estructuras tipo INIS_MD candidatas.
	this->BUFF_INDFRLIS_MD_ID_CAN.clear();														//buffer de ids de estructuras tipo INDFRLIS_MD candidatas.
	this->BUFF_INPRRLIS_MD_ID_CAN.clear();														//buffer de ids de estructuras tipo INPRRLIS_MD candidatas.

	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//limpieza de buffer para índice de relación utilizada en reconocimiento.
	this->BUFF_RL_INDEX_USED_IN_RECOGNITION			=	-1;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpíeza de buffers para las estructuras reconocidas.
	this->BUFF_INIS_MD_RE.Clean();															//buffer para estructura reconocida INIS_MD.
	this->BUFF_INDFRLIS_MD_RE.Clean();															//buffer para estructura reconocida INDFRLIS_MD.
	this->BUFF_INPRRLIS_MD_RE.Clean();															//buffer para estructura reconocida INPRRLIS_MD.	
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//variables auxiliares.
	this->GUPCI_ITERATION_COUNTER					=	-1;									//contador de iteraciones de la GUPCI.
	
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
//#1: método para correr GUPCI_HL_V.
vo GUPCI_HL_V::Run()
{
	//---------------------------------------------------------------------------------
	//thread para correr la GUPCI_HL_V.
	this->THREAD_GUPCI_INPUT = thread(&UPC::GUPCI_HL_V::ThreadRun, this);
}

//------------------------------------------------------------------------------------- 
//------------------------------------------------------------------------------------- 
//#2: thread donde corre la GUPCI_HL_V.
vo GUPCI_HL_V::ThreadRun()
{	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//seteo del tiempo de espera.
	chrono::milliseconds timeout(TIMEOUT_LOOP_SLOW);
	
	//--------------------------------------------------------------------------------- 
	//---------------------------------------------------------------------------------
	//bucle para la GUPCI_HL_V.
	while (this->GetCLOSE_ACTIVE_THREADS_FLAG() == OFF)
	{
		//-----------------------------------------------------------------------------
		//si la GUPCI esta en pausa, entonces esperar.
		while (this->GetPAUSE_ACTIVE_THREADS_FLAG() == ON && this->GetCLOSE_ACTIVE_THREADS_FLAG() == OFF)	this_thread::sleep_for(timeout);

		//---------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------
		//si el kernel está disponible para operar, entonces.
		if (this->GetKERNEL_INTEGRATION_FLAG() == OFF)
		{
			//-----------------------------------------------------------------------------
			//entrada a la upci por kernel.
			this->BUFF_UPCI_HL_V[this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT].KernelInput();

			//-----------------------------------------------------------------------------
			//incremento del contador de iteraciones.
			++this->GUPCI_ITERATION_COUNTER;
		}
	}		 
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método de entrada de comandos del usuario.
vo GUPCI_HL_V::UserCommand(st _user_command)
{

}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para abrir GUPCI_HL_V.
in GUPCI_HL_V::Open(st _fileNameS, dou *_buff_in_rg, dou *_buff_ev_rg, dou *_buff_output_projection)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación del objeto inf. 
	ifstream inf(_fileNameS + ".gu", ifstream::binary);
	
	//#################################################################################
	//---------------------------------------------------------------------------------
	//########################## VARIABLES DE INICIALIZACIÓN ##########################

	//---------------------------------------------------------------------------------
	//argumentos: parámetros de GUPCI.
	in		gupci_id_p							= NULL;										//id de GUPCI.	
	in		upci_amount_p						= NULL;										//cantidad de upci por grupo.	

	//---------------------------------------------------------------------------------
	//argumentos: parámetros de las upci.
	in		inis_md_amount_allowed_p			= NULL;										//cantidad de estructuras INIS_MD permitidas.
	in		rlis_amount_allowed_p				= NULL;										//cantidad de estructuras rlis permitidas.
	in		default_activity_level_p			= NULL;										//nivel de actividad por defecto.
	in		max_activity_level_allowed_p		= NULL;										//nivel de actividad máximo permitido.
	in		min_activity_level_allowed_p		= NULL;										//nivel de actividad mínimo permitido.
	dou		dif_raw_input_threshold_p			= NULL;										//umbral de entrada cruda para focalización de la atención (%).
	dou		str_congruence_threshold_p			= NULL;										//umbral de congruencia para estructuras candidatas (%).	
	dou		pfrlis_strength_threshold_p			= NULL;										//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
	dou		indfrlis_strength_threshold_p		= NULL;										//umbral de fortaleza de relación INDFRLIS_MD para eliminar relación por N.A.
	dou		evaluation_threshold_p				= NULL;										//umbral para evaluaciones.	
	dou		transition_evaluation_threshold_p	= NULL;										//umbral para transición de evaluaciones.	
	in		timeout_clean_is_p					= NULL;										//tiempo de espera de limpieza de IS.
	in		timeout_update_al_is_p				= NULL;										//tiempo de espera para actualizar niveles de actividad en IS (ms).
	
	//---------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------- 
	//variables internas.

	//---------------------------------------------------------------------------------
	//declaración de buffer del id de la upci con bandera de almacenamiento en estado activo.
	in		buff_upci_hl_v_id_storage_flag_act	= NULL;		

	//---------------------------------------------------------------------------------
	//declaración de buffer para el contador de iteraciones de la GUPCI.
	in		gupci_iteration_counter				= NULL;

	//---------------------------------------------------------------------------------
	//declaración ids de la upci.
	in		upci_hl_v_id						= NULL;																						

	//---------------------------------------------------------------------------------
	//declaración de bandera del estado del almacenamiento de la unidad (true: salvar, false: no-salvar).
	in		st_flag								= NULL;			

	//---------------------------------------------------------------------------------
	//declaración de otros buffers upci.	
	in		buff_INIS_MD_id_av[2];															//buffer para id de INIS_MD disponible.
	in		buff_SRLIS_id_av[2];															//buffer para id de SRLIS disponible.
	in		buff_PFRLIS_id_av[2];															//buffer para id de PFRLIS disponible.
	in		buff_INDFRLIS_MD_id_av[2];															//buffer para id de INDFRLIS_MD disponible.
	in		buff_INPRRLIS_MD_id_av[2];															//buffer para id de INPRRLIS_MD disponible.
	in		buff_max_id_INIS_MD[2];															//buffer para máximos ids en estructuras INIS_MD.
	in		buff_max_id_SRLIS[2];															//buffer para máximos ids en estructuras SRLIS.
	in		buff_max_id_PFRLIS[2];															//buffer para máximos ids en estructuras PFRLIS.
	in		buff_max_id_INDFRLIS_MD[2];														//buffer para máximos ids en estructuras INDFRLIS_MD.
	in		buff_max_id_INPRRLIS_MD[2];														//buffer para máximos ids en estructuras INPRRLIS_MD.
	in		buff_INIS_MD_ini_amount				= NULL;										//buffer para la cantidad de INIS_MD existentes.
	in		buff_SRLIS_ini_amount				= NULL;										//buffer para la cantidad de SRLIS existentes.
	in		buff_PFRLIS_ini_amount				= NULL;										//buffer para la cantidad de PFRLIS existentes.
	in		buff_INDFRLIS_MD_ini_amount			= NULL;										//buffer para la cantidad de INDFRLIS_MD existentes.
	in		buff_INPRRLIS_MD_ini_amount			= NULL;										//buffer para la cantidad de INPRRLIS_MD existentes.

	//---------------------------------------------------------------------------------
	//declaración de buffer para los contadores de iteraciones de la upci.
	in		kernel_iteration_counter			= NULL;										//contador de iteraciones del kernel de la upci.
	in		thread_iteration_counter			= NULL;										//contador de iteraciones del Hilo de la upci.

	//---------------------------------------------------------------------------------
	//declaración de registros para las estructuras.
	dou		in_rg								= NULL;										//registro de entrada.
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
	in		upci_type_str1_rg					= NULL;										//tipo de upci de estructura n°1.
	in		upci_type_str2_rg					= NULL;										//tipo de upci de estructura n°2.
	in		upci_id_str1_rg						= NULL;										//id upci de estructura n°1.
	in		upci_id_str2_rg						= NULL;										//id upci de estructura n°2.

	//---------------------------------------------------------------------------------
	//declaración de sub-registros para las estructuras.
	in		rs_srg								= NULL;										//estado de realidad o fortaleza de relación.
	in		cs_srg								= NULL;										//estado de congruencia.
	dou		rs_srg								= NULL;										//fortaleza de la relación.
	dou		al_srg								= NULL;										//nivel de actividad.

	//---------------------------------------------------------------------------------
	//declaración de variables auxiliares para las relaciones.
	dedein	rl;
	in		rl_type								= NULL;
	in		rl_id								= NULL;	
	in		rl_upci_type						= NULL;
	in		rl_upci_id							= NULL;

	//---------------------------------------------------------------------------------
	//declaración de variables auxiliares cantidad de relaciones.
	in		rl_amount							= NULL;								

	//#################################################################################
	//---------------------------------------------------------------------------------
	//################################## LECTURA ######################################
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//lectura parámetros de GUPCI.	
	inf >> gupci_id_p;
	inf >> upci_amount_p;
	
	//---------------------------------------------------------------------------------  
	//---------------------------------------------------------------------------------  
	//lectura de parámetros de las upci.
	inf >> inis_md_amount_allowed_p;
	inf >> rlis_amount_allowed_p;
	inf >> default_activity_level_p;
	inf >> max_activity_level_allowed_p;
	inf >> min_activity_level_allowed_p;
	inf >> dif_raw_input_threshold_p;
	inf >> str_congruence_threshold_p;
	inf >> pfrlis_strength_threshold_p;
	inf >> indfrlis_strength_threshold_p;
	inf >> evaluation_threshold_p;
	inf >> transition_evaluation_threshold_p;
	inf >> timeout_clean_is_p; 
	inf >> timeout_update_al_is_p;	

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------  
	//lectura de buffers de GUPCI para banderas de almacenamiento.
	inf >> buff_upci_hl_v_id_storage_flag_act;

	//---------------------------------------------------------------------------------
	//se lee el contador de iteraciones de la GUPCI.
	inf >> gupci_iteration_counter;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//limpieza del grupo de unidad de proceso cognitivo.
	this->Clean();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de argumentos de inicialización del objeto upci.
	this->BUFF_UPCI_HL_V_ARG.Initialize(_buff_in_rg,
										_buff_ev_rg,
										_buff_output_projection,
										inis_md_amount_allowed_p,
										rlis_amount_allowed_p,
										default_activity_level_p,
										max_activity_level_allowed_p,
										min_activity_level_allowed_p,
										dif_raw_input_threshold_p,
										str_congruence_threshold_p,
										pfrlis_strength_threshold_p,
										indfrlis_strength_threshold_p,
										evaluation_threshold_p,
										transition_evaluation_threshold_p,
										timeout_clean_is_p,
										timeout_update_al_is_p);
	
	//---------------------------------------------------------------------------------
	//inicialización de la GUPCI.
	this->Initialize(upci_amount_p, BUFF_UPCI_HL_V_ARG);

	//---------------------------------------------------------------------------------
	//seteo del id de la GUPCI.
	this->GUPCI_ID	= gupci_id_p;
	
	//---------------------------------------------------------------------------------
	//seteo de buffer del id de la upci con bandera de almacenamiento en estado activo.
	this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT	= buff_upci_hl_v_id_storage_flag_act;	
	
	//---------------------------------------------------------------------------------
	//seteo de la cantidad de iteraciones de la GUPCI.
	this->GUPCI_ITERATION_COUNTER				= gupci_iteration_counter;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para leer cada upci.
	for (in i1 = 0; i1 < this->UPCI_HL_V_AMOUNT; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//limpieza de ids de la upci.
		upci_hl_v_id				= NULL;																						

		//-----------------------------------------------------------------------------
		//limpieza de bandera del estado del almacenamiento de la unidad (true: salvar, false: no-salvar).
		st_flag						= NULL;			

		//-----------------------------------------------------------------------------
		//limpieza de otros buffers upci.	
		buff_INIS_MD_id_av[0]		= NULL;													//buffer para id de INIS_MD disponible en [0].
		buff_SRLIS_id_av[0]			= NULL;													//buffer para id de SRLIS disponible en [0].
		buff_PFRLIS_id_av[0]		= NULL;													//buffer para id de PFRLIS disponible en [0].
		buff_INDFRLIS_MD_id_av[0]		= NULL;													//buffer para id de INDFRLIS_MD disponible en [0].
		buff_INPRRLIS_MD_id_av[0]		= NULL;													//buffer para id de INPRRLIS_MD disponible en [0].
		buff_max_id_INIS_MD[0]		= NULL;													//buffer para máximos ids en estructuras INIS_MD en [0].
		buff_max_id_SRLIS[0]		= NULL;													//buffer para máximos ids en estructuras SRLIS en [0].
		buff_max_id_PFRLIS[0]		= NULL;													//buffer para máximos ids en estructuras PFRLIS en [0].
		buff_max_id_INDFRLIS_MD[0]		= NULL;													//buffer para máximos ids en estructuras INDFRLIS_MD en [0].
		buff_max_id_INPRRLIS_MD[0]		= NULL;													//buffer para máximos ids en estructuras INPRRLIS_MD en [0].
		buff_INIS_MD_id_av[1]		= NULL;													//buffer para id de INIS_MD disponible en [1].
		buff_SRLIS_id_av[1]			= NULL;													//buffer para id de SRLIS disponible en [1].
		buff_PFRLIS_id_av[1]		= NULL;													//buffer para id de PFRLIS disponible en [1].
		buff_INDFRLIS_MD_id_av[1]		= NULL;													//buffer para id de INDFRLIS_MD disponible en [1].
		buff_INPRRLIS_MD_id_av[1]		= NULL;													//buffer para id de INPRRLIS_MD disponible en [1].
		buff_max_id_INIS_MD[1]		= NULL;													//buffer para máximos ids en estructuras INIS_MD en [1].
		buff_max_id_SRLIS[1]		= NULL;													//buffer para máximos ids en estructuras SRLIS en [1].
		buff_max_id_PFRLIS[1]		= NULL;													//buffer para máximos ids en estructuras PFRLIS en [1].
		buff_max_id_INDFRLIS_MD[1]		= NULL;													//buffer para máximos ids en estructuras INDFRLIS_MD en [1].
		buff_max_id_INPRRLIS_MD[1]		= NULL;													//buffer para máximos ids en estructuras INPRRLIS_MD en [1].
		buff_INIS_MD_ini_amount		= NULL;													//buffer para la cantidad de INIS_MD existentes.
		buff_SRLIS_ini_amount		= NULL;													//buffer para la cantidad de SRLIS existentes.
		buff_PFRLIS_ini_amount		= NULL;													//buffer para la cantidad de PFRLIS existentes.
		buff_INDFRLIS_MD_ini_amount	= NULL;													//buffer para la cantidad de INDFRLIS_MD existentes.
		buff_INPRRLIS_MD_ini_amount	= NULL;													//buffer para la cantidad de INPRRLIS_MD existentes.

		//-----------------------------------------------------------------------------
		//limpieza de buffer para los contadores de iteraciones de la upci.
		kernel_iteration_counter	= NULL;													//contador de iteraciones del kernel de la upci.
		thread_iteration_counter	= NULL;													//contador de iteraciones del Hilo de la upci.

		//-----------------------------------------------------------------------------
		//limpieza de registros para las estructuras.
		in_rg						= NULL;													//registro de entrada.
		ev_rg						= NULL;													//registro de evaluación.
		in_dif_rg					= NULL;													//diferencia de registros de entrada.
		ev_dif_rg					= NULL;													//diferencia de registros de evaluación.
		in_pro_rg					= NULL;													//proporción de registros de entrada.
		rl_type_rg					= NULL;													//tipo de relación.
		str_type_rg					= NULL;													//tipo de estructura.
		str1_type_rg				= NULL;													//tipo de estructura n°1.
		str2_type_rg				= NULL;													//tipo de estructura n°2.
		str_id_rg					= NULL;													//id estructura.
		str1_id_rg					= NULL;													//id estructura n°1.
		str2_id_rg					= NULL;													//id estructura n°2.
		upci_type_str1_rg			= NULL;													//tipo de upci de estructura n°1.
		upci_type_str2_rg			= NULL;													//tipo de upci de estructura n°2.
		upci_id_str1_rg				= NULL;													//id upci de estructura n°1.
		upci_id_str2_rg				= NULL;													//id upci de estructura n°2.

		//-----------------------------------------------------------------------------
		//limpieza de sub-registros para las estructuras.
		rs_srg						= NULL;													//estado de realidad o fortaleza de relación.
		cs_srg						= NULL;													//estado de congruencia.
		rs_srg						= NULL;													//fortaleza de la relación.
		al_srg						= NULL;													//nivel de actividad.

		//-----------------------------------------------------------------------------
		//limpieza de variables auxiliares para las relaciones.
		rl_type						= NULL;
		rl_id						= NULL;	
		rl_upci_type				= NULL;
		rl_upci_id					= NULL;

		//-----------------------------------------------------------------------------
		//limpieza de variables auxiliares cantidad de relaciones.
		rl_amount					= NULL;	

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//lectura del id. 
		inf >> upci_hl_v_id;
		
		//-----------------------------------------------------------------------------
		//lectura de los estados de las banderas.
		inf >> st_flag;
		
		//-----------------------------------------------------------------------------
		//lectura de algunos buffers.				
		inf >> buff_INIS_MD_id_av[0];
		inf >> buff_SRLIS_id_av[0];
		inf >> buff_PFRLIS_id_av[0];
		inf >> buff_INDFRLIS_MD_id_av[0];
		inf >> buff_INPRRLIS_MD_id_av[0];
		inf >> buff_INIS_MD_id_av[1];	
		inf >> buff_SRLIS_id_av[1];
		inf >> buff_PFRLIS_id_av[1];	
		inf >> buff_INDFRLIS_MD_id_av[1];
		inf >> buff_INPRRLIS_MD_id_av[1];
		inf >> buff_max_id_INIS_MD[0];
		inf >> buff_max_id_SRLIS[0];
		inf >> buff_max_id_PFRLIS[0];
		inf >> buff_max_id_INDFRLIS_MD[0];
		inf >> buff_max_id_INPRRLIS_MD[0];
		inf >> buff_max_id_INIS_MD[1];
		inf >> buff_max_id_SRLIS[1];
		inf >> buff_max_id_PFRLIS[1];
		inf >> buff_max_id_INDFRLIS_MD[1];
		inf >> buff_max_id_INPRRLIS_MD[1];
		inf >> buff_INIS_MD_ini_amount;
		inf >> buff_SRLIS_ini_amount;
		inf >> buff_PFRLIS_ini_amount;	
		inf >> buff_INDFRLIS_MD_ini_amount;
		inf >> buff_INPRRLIS_MD_ini_amount;

		//-----------------------------------------------------------------------------
		//se leen los contadores de iteraciones de la upci.
		inf >> kernel_iteration_counter;
		inf >> thread_iteration_counter;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//se Setea el id.
		this->BUFF_UPCI_HL_V.at(i1).UPCI_ID						= upci_hl_v_id;
							
		//-----------------------------------------------------------------------------
		//se Setean las banderas.
		this->BUFF_UPCI_HL_V.at(i1).STORAGE_FLAG				= st_flag;
		
		//-----------------------------------------------------------------------------		
		//se setean otros buffers.	
		this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD_ID_AV[0]		= buff_INIS_MD_id_av[0];
		this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS_ID_AV[0]			= buff_SRLIS_id_av[0];
		this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS_ID_AV[0]		= buff_PFRLIS_id_av[0];
		this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD_ID_AV[0]		= buff_INDFRLIS_MD_id_av[0];
		this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD_ID_AV[0]		= buff_INPRRLIS_MD_id_av[0];
		this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD_ID_AV[1]		= buff_INIS_MD_id_av[1];		
		this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS_ID_AV[1]			= buff_SRLIS_id_av[1];	
		this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS_ID_AV[1]		= buff_PFRLIS_id_av[1];	
		this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD_ID_AV[1]		= buff_INDFRLIS_MD_id_av[1];		
		this->BUFF_UPCI_HL_V.at(i1).BUFF_INPRRLIS_MD_ID_AV[1]		= buff_INPRRLIS_MD_id_av[1];		
		this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD_MAX_ID[0]		= buff_max_id_INIS_MD[0];
		this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS_MAX_ID[0]		= buff_max_id_SRLIS[0];
		this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS_MAX_ID[0]		= buff_max_id_PFRLIS[0];
		this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD_MAX_ID[0]		= buff_max_id_INDFRLIS_MD[0];
		this->BUFF_UPCI_HL_V.at(i1).BUFF_INPRRLIS_MD_MAX_ID[0]		= buff_max_id_INPRRLIS_MD[0];
		this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD_MAX_ID[1]		= buff_max_id_INIS_MD[1];
		this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS_MAX_ID[1]		= buff_max_id_SRLIS[1];
		this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS_MAX_ID[1]		= buff_max_id_PFRLIS[1];
		this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD_MAX_ID[1]		= buff_max_id_INDFRLIS_MD[1];
		this->BUFF_UPCI_HL_V.at(i1).BUFF_INPRRLIS_MD_MAX_ID[1]		= buff_max_id_INPRRLIS_MD[1];
		this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD_INI_AMOUNT		= buff_INIS_MD_ini_amount;
		this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS_INI_AMOUNT		= buff_SRLIS_ini_amount;
		this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS_INI_AMOUNT		= buff_PFRLIS_ini_amount;
		this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD_INI_AMOUNT	= buff_INDFRLIS_MD_ini_amount;
		this->BUFF_UPCI_HL_V.at(i1).BUFF_INPRRLIS_MD_INI_AMOUNT	= buff_INPRRLIS_MD_ini_amount;

		//-----------------------------------------------------------------------------
		//seteo de la cantidad de iteraciones de la upci.
		this->BUFF_UPCI_HL_V.at(i1).KERNEL_ITERATION_COUNTER	= kernel_iteration_counter;
		this->BUFF_UPCI_HL_V.at(i1).THREAD_ITERATION_COUNTER	= thread_iteration_counter;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle lectura estructuras INIS_MD.
		for (in i2 = 0; i2 < inis_md_amount_allowed_p; i2++)
		{
			//-------------------------------------------------------------------------
			//se lee el registro de la estrutura de entrada.
			inf >> in_rg;			
			
			//-------------------------------------------------------------------------
			//se lee el registro de evaluación de la estrutura de entrada.
			inf >> ev_rg;

			//-------------------------------------------------------------------------
			//se lee el sub-registro de estado de realidad de la estructura.
			inf >> rs_srg;

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
				rs_srg = -1;
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
				inf >> rl_upci_type;
				inf >> rl_upci_id;	
				
				//---------------------------------------------------------------------
				//se cargan al buffer de relaciones.
				rl.push_back(deque<in>(0));
				rl.back().push_back(rl_type);
				rl.back().push_back(rl_id);
				rl.back().push_back(rl_upci_type);
				rl.back().push_back(rl_upci_id);
			}
			
			//-------------------------------------------------------------------------
			//seteo de la estructura.
			this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD[i2].Set(in_rg, ev_rg, rs_srg, cs_srg, al_srg, rl);
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle lectura estructuras SRLIS.
		for (in i2 = 0; i2 < rlis_amount_allowed_p; i2++)
		{
			//-------------------------------------------------------------------------
			//se leen los registros de la estructura de relación.
			inf >> str1_type_rg;
			inf >> str2_type_rg;
			inf >> str1_id_rg;
			inf >> str2_id_rg;
			inf >> upci_type_str1_rg;
			inf >> upci_type_str2_rg;
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
			this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS[i2].Set(str1_type_rg, 
														   str2_type_rg, 
														   str1_id_rg, 
														   str2_id_rg, 
														   upci_type_str1_rg, 
														   upci_type_str2_rg, 														   
														   upci_id_str1_rg, 
														   upci_id_str2_rg, 
														   rs_srg, 
														   al_srg);
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
			inf >> upci_type_str1_rg;
			inf >> upci_type_str2_rg;
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
			this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS[i2].Set(str1_type_rg, 
															str2_type_rg, 
															str1_id_rg, 
															str2_id_rg, 
															upci_type_str1_rg, 
														    upci_type_str2_rg, 
															upci_id_str1_rg, 
															upci_id_str2_rg, 
															rs_srg, 
															al_srg);
		}
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle lectura estructuras INDFRLIS_MD.
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
				inf >> rl_upci_type;
				inf >> rl_upci_id;

				//---------------------------------------------------------------------
				//se cargan al buffer de relaciones.
				rl.push_back(deque<in>(0));
				rl.back().push_back(rl_type);
				rl.back().push_back(rl_id);
				rl.back().push_back(rl_upci_type);
				rl.back().push_back(rl_upci_id);
			}

			//-------------------------------------------------------------------------
			//seteo de la estructura.
			this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD[i2].Set(in_dif_rg, ev_dif_rg, str1_id_rg, str2_id_rg, upci_id_str1_rg, upci_id_str2_rg, cs_srg, rs_srg, al_srg, rl);
		}
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle lectura estructuras INPRRLIS_MD.
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
			this->BUFF_UPCI_HL_V.at(i1).BUFF_INPRRLIS_MD[i2].Set(in_pro_rg, str1_id_rg, str2_id_rg, upci_id_str1_rg, upci_id_str2_rg, cs_srg);
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
//#2: método para guardar GUPCI.
in GUPCI_HL_V::Save(st _fileNameS)
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
	//guardar parámetros de GUPCI.	
	ouf << this->GUPCI_ID			<< endl;
	ouf << this->UPCI_HL_V_AMOUNT	<< endl;
	
	//---------------------------------------------------------------------------------  
	//guardar parámetros upci.	
	ouf << this->BUFF_UPCI_HL_V.at(0).INIS_MD_AMOUNT_ALLOWED			<< endl;
	ouf << this->BUFF_UPCI_HL_V.at(0).RLIS_AMOUNT_ALLOWED				<< endl;
	ouf << this->BUFF_UPCI_HL_V.at(0).DEFAULT_ACTIVITY_LEVEL			<< endl;
	ouf << this->BUFF_UPCI_HL_V.at(0).MAX_ACTIVITY_LEVEL_ALLOWED		<< endl;
	ouf << this->BUFF_UPCI_HL_V.at(0).MIN_ACTIVITY_LEVEL_ALLOWED		<< endl;
	ouf << this->BUFF_UPCI_HL_V.at(0).DIF_RAW_INPUT_THRESHOLD			<< endl;
	ouf << this->BUFF_UPCI_HL_V.at(0).STR_CONGRUENCE_THRESHOLD			<< endl;
	ouf << this->BUFF_UPCI_HL_V.at(0).PFRLIS_STRENGTH_THRESHOLD			<< endl;
	ouf << this->BUFF_UPCI_HL_V.at(0).INDFRLIS_MD_STRENGTH_THRESHOLD		<< endl;
	ouf << this->BUFF_UPCI_HL_V.at(0).EVALUATION_THRESHOLD				<< endl;
	ouf << this->BUFF_UPCI_HL_V.at(0).TRANSITION_EVALUATION_THRESHOLD	<< endl;
	ouf << this->BUFF_UPCI_HL_V.at(0).TIMEOUT_CLEAN_IS					<< endl;
	ouf << this->BUFF_UPCI_HL_V.at(0).TIMEOUT_UPDATE_AL_IS				<< endl;

	//---------------------------------------------------------------------------------
	//guardar buffer de GUPCI para banderas de almacenamiento
	ouf << this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT	<< endl;
	
	//---------------------------------------------------------------------------------
	//se guarda el contador de iteraciones de la GUPCI.
	ouf << this->GUPCI_ITERATION_COUNTER		<< endl;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para salvar cada upci.
	for (in i1 = 0; i1 < this->UPCI_HL_V_AMOUNT; i1++)
	{		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//se guarda el id.
		ouf << this->BUFF_UPCI_HL_V.at(i1).UPCI_HL_V_ID		<< endl;

		//-----------------------------------------------------------------------------
		//se guarda la bandera de almacenamiento.
		ouf << this->BUFF_UPCI_HL_V.at(i1).STORAGE_FLAG	<< endl;
		
		//-----------------------------------------------------------------------------
		//se guardan los buffers.				
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD_ID_AV[0]	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS_ID_AV[0]		<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS_ID_AV[0]		<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD_ID_AV[0]	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INPRRLIS_MD_ID_AV[0]	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD_ID_AV[1]	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS_ID_AV[1]		<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS_ID_AV[1]		<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD_ID_AV[1]	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INPRRLIS_MD_ID_AV[1]	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD_MAX_ID[0]	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS_MAX_ID[0]		<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS_MAX_ID[0]	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD_MAX_ID[0]	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INPRRLIS_MD_MAX_ID[0]	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD_MAX_ID[1]	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS_MAX_ID[1]		<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS_MAX_ID[1]	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD_MAX_ID[1]	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INPRRLIS_MD_MAX_ID[1]	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD_INI_AMOUNT	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS_INI_AMOUNT	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS_INI_AMOUNT	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD_INI_AMOUNT	<< endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INPRRLIS_MD_INI_AMOUNT	<< endl;

		//-----------------------------------------------------------------------------
		//se guarda el contador de iteraciones de la upci i1.
		ouf << this->BUFF_UPCI_HL_V.at(i1).KERNEL_ITERATION_COUNTER << endl;
		ouf << this->BUFF_UPCI_HL_V.at(i1).THREAD_ITERATION_COUNTER << endl;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle guardar estructuras INIS_MD de la upci i1.
		for (in i2 = 0; i2 < this->BUFF_UPCI_HL_V.at(i1).INIS_MD_AMOUNT_ALLOWED; i2++)
		{
			//-------------------------------------------------------------------------
			//se guarda el registro de la estrutura de entrada.
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD[i2].IN_RG << endl;
			
			//-------------------------------------------------------------------------
			//se guarda el registro de evaluación de la estrutura de entrada.
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD[i2].EV_RG << endl;

			//-------------------------------------------------------------------------
			//se guarda el estado de realidad de la estructura de entrada.
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD[i2].RS_SRG << endl;

			//-------------------------------------------------------------------------
			//se guarda el nivel de actividad de la estrutura de entrada.
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD[i2].AL_SRG << endl;
			
			//-------------------------------------------------------------------------
			//obtención de la cantidad de relaciones de la estructura.
			rl_amount	= this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD[i2].GetRelationAmount();
			
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
				ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD[i2].RL.at(i3).at(0) << endl;
				ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD[i2].RL.at(i3).at(1) << endl;
				ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD[i2].RL.at(i3).at(2) << endl;
				ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INIS_MD[i2].RL.at(i3).at(3) << endl;
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle guardar estructuras SRLIS de la upci i1.
		for (in i2 = 0; i2 < this->BUFF_UPCI_HL_V.at(i1).RLIS_AMOUNT_ALLOWED; i2++)
		{
			//-------------------------------------------------------------------------
			//se guardan los registros de la estructura de relación.
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS[i2].STR1_TYPE_RG		<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS[i2].STR2_TYPE_RG		<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS[i2].STR1_ID_RG		<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS[i2].STR2_ID_RG		<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS[i2].UPCI_TYPE_STR1_RG	<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS[i2].UPCI_TYPE_STR2_RG	<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS[i2].UPCI_ID_STR1_RG	<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS[i2].UPCI_ID_STR2_RG	<< endl;

			//-------------------------------------------------------------------------
			//se guardan los sub-registros de la estructura.
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_SRLIS[i2].RS_SRG << endl;
		}
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle guardar estructuras PFRLIS de la upci i1.
		for (in i2 = 0; i2 < this->BUFF_UPCI_HL_V.at(i1).RLIS_AMOUNT_ALLOWED; i2++)
		{
			//-------------------------------------------------------------------------
			//se guardan los registros de la estructura de relación.
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS[i2].STR1_TYPE_RG			<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS[i2].STR2_TYPE_RG			<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS[i2].STR1_ID_RG			<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS[i2].STR2_ID_RG			<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS[i2].UPCI_TYPE_STR1_RG	<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS[i2].UPCI_TYPE_STR2_RG	<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS[i2].UPCI_ID_STR1_RG		<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS[i2].UPCI_ID_STR2_RG		<< endl;
						
			//-------------------------------------------------------------------------
			//se guardan los sub-registros de la estructura.
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_PFRLIS[i2].RS_SRG << endl;
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle guardar estructuras INDFRLIS_MD de la upci i1.
		for (in i2 = 0; i2 < this->BUFF_UPCI_HL_V.at(i1).RLIS_AMOUNT_ALLOWED; i2++)
		{
			//-------------------------------------------------------------------------
			//se guarda el registro de la estrutura de diferenciación de entrada.
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD[i2].IN_DIF_RG << endl;

			//-------------------------------------------------------------------------
			//se guarda el registro de diferenciación de evaluación.
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD[i2].EV_DIF_RG << endl;

			//-------------------------------------------------------------------------
			//se guardan los registros de la estructura de relación.
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD[i2].STR1_ID_RG			<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD[i2].STR2_ID_RG			<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD[i2].UPCI_ID_STR1_RG	<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD[i2].UPCI_ID_STR2_RG	<< endl;

			//-------------------------------------------------------------------------
			//se guardan los sub-registros de la estructura.
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD[i2].RS_SRG << endl;

			//-------------------------------------------------------------------------
			//obtención de la cantidad de relaciones de la estructura.
			rl_amount	= this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD[i2].GetRelationAmount();

			//-------------------------------------------------------------------------
			//se guardan las cantidades de relaciones de la estructura.
			ouf << rl_amount << endl;

			//-------------------------------------------------------------------------
			//guardar relaciones.
			for (in i3 = 0; i3 < rl_amount; i3++)
			{
				//---------------------------------------------------------------------
				//se guardar el id y el tipo de relación.
				ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD[i2].RL.at(i3).at(0) << endl;
				ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD[i2].RL.at(i3).at(1) << endl;
				ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD[i2].RL.at(i3).at(2) << endl;
				ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INDFRLIS_MD[i2].RL.at(i3).at(3) << endl;
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle guardar estructuras INPRRLIS_MD de la upci i1.
		for (in i2 = 0; i2 < this->BUFF_UPCI_HL_V.at(i1).RLIS_AMOUNT_ALLOWED; i2++)
		{
			//-------------------------------------------------------------------------
			//se guarda el registro de la estrutura de proporción de entrada.
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INPRRLIS_MD[i2].IN_PRO_RG << endl;
			
			//-------------------------------------------------------------------------
			//se guardan los registros de la estructura de relación.
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INPRRLIS_MD[i2].STR1_ID_RG			<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INPRRLIS_MD[i2].STR2_ID_RG			<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INPRRLIS_MD[i2].UPCI_ID_STR1_RG	<< endl;
			ouf << this->BUFF_UPCI_HL_V.at(i1).BUFF_INPRRLIS_MD[i2].UPCI_ID_STR2_RG	<< endl;
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
//#3: método para imprimir GUPCI.
vo GUPCI_HL_V::PrintGUPCI(in _upci_id, in _buffers_selection, in _str_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//impresión de línea divisora.
	cout <<"--------------------------------------------------------------------" <<endl;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//carga de buffers.
	if		(_buffers_selection == DEF_BUFF_BA)							this->PrintBuffBanderas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_NU)							this->PrintBuffNucleo(_upci_id);
	else if (_buffers_selection == DEF_BUFF_DIR_UPC)					this->PrintBuffDirUpc(_upci_id);
	else if (_buffers_selection == DEF_BUFF_INIS_MD)					this->PrintBuffEstructurasINIS_MD(_upci_id, _str_id);
	else if (_buffers_selection == DEF_BUFF_PFRLIS)						this->PrintBuffEstructurasPFRLIS(_upci_id, _str_id);
	else if (_buffers_selection == DEF_BUFF_INDFRLIS_MD)					this->PrintBuffEstructurasINDFRLIS_MD(_upci_id, _str_id);
	else if (_buffers_selection == DEF_BUFF_INPRRLIS_MD)					this->PrintBuffEstructurasINPRRLIS_MD(_upci_id, _str_id);
	else if (_buffers_selection == DEF_BUFF_INIS_MD_CAN)				this->PrintBuffINIS_MDCandidatas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_INDFRLIS_MD_CAN)				this->PrintBuffINDFRLIS_MDCandidatas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_INPRRLIS_MD_CAN)				this->PrintBuffINPRRLIS_MDCandidatas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_ID_UPCI_HL_V_INIS_MD_CAN)	this->PrintBuffIdUpcINIS_MDCandidatas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_ID_UPCI_HL_V_INDFRLIS_MD_CAN)	this->PrintBuffIdUpcINDFRLIS_MDCandidatas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_ID_UPCI_HL_V_INPRRLIS_MD_CAN)	this->PrintBuffIdUpcINPRRLIS_MDCandidatas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_STR_DIS)					this->PrintBuffIdEstDisponibles(_upci_id);
	else if (_buffers_selection == DEF_BUFF_STR_CRE)					this->PrintBuffIdYTipoEstCreadas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_STR_RE)						this->PrintBuffEstReconocidas(_upci_id);
	else if (_buffers_selection == DEF_BUFF_CANT_UPCI_STR_SUS)			this->PrintBuffCantUpciEstSuspension(_upci_id);
	else if (_buffers_selection == DEF_BUFF_CANT_EST)					this->PrintBuffCantEstExistentes(_upci_id);
	else if (_buffers_selection == DEF_BUFF_CANT_EXP)					this->PrintBuffCantExp(_upci_id);
	else if (_buffers_selection == DEF_BUFF_MAX_ID_EST)					this->PrintBuffMaxIdEst(_upci_id);	

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
in GUPCI_HL_V::GetUPCI_AMOUNT()
{
	//---------------------------------------------------------------------------------
	//retorno de la cantidad de upci conectados.
	return in(this->BUFF_UPCI_HL_V.size());
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para obtener el estado de la bandera 'KERNEL_INTEGRATION_FLAG'.
in GUPCI_HL_V::GetKERNEL_INTEGRATION_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera KERNEL_INTEGRATION_FLAG.
	return this->BUFF_UPCI_HL_V[this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT].GetKERNEL_INTEGRATION_FLAG();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para obtener el estado de la bandera 'THREAD_INTEGRATION_FLAG'.
in GUPCI_HL_V::GetTHREAD_INTEGRATION_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera THREAD_INTEGRATION_FLAG.
	return this->BUFF_UPCI_HL_V[this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT].GetTHREAD_INTEGRATION_FLAG();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para obtener el estado de la bandera 'THREAD_INTEGRATION_FINISHED_FLAG'. 
in GUPCI_HL_V::GetTHREAD_INTEGRATION_FINIS_MDHED_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'THREAD_INTEGRATION_FINISHED_FLAG'.
	return this->BUFF_UPCI_HL_V[this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT].GetTHREAD_INTEGRATION_FINISHED_FLAG();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para obtener el estado de la bandera 'CLOSE_ACTIVE_THREADS_FLAG'.
in GUPCI_HL_V::GetCLOSE_ACTIVE_THREADS_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'CLOSE_ACTIVE_THREADS_FLAG'.
	return this->CLOSE_ACTIVE_THREADS_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método para obtener el estado de la bandera 'PAUSE_ACTIVE_THREADS_FLAG'.
in GUPCI_HL_V::GetPAUSE_ACTIVE_THREADS_FLAG()
{
	//---------------------------------------------------------------------------------
	//retorno de la bandera 'PAUSE_ACTIVE_THREADS_FLAG'.
	return this->PAUSE_ACTIVE_THREADS_FLAG;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para obtener el contador de iteraciones de la GUPCI.
in GUPCI_HL_V::GetGUPCI_ITERATION_COUNTER()
{
	//---------------------------------------------------------------------------------
	//retorno del contador de iteraciones.
	return this->GUPCI_ITERATION_COUNTER;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para obtener el contador de iteraciones del kernel.
in GUPCI_HL_V::GetKERNEL_ITERATION_COUNTER()
{
	//---------------------------------------------------------------------------------
	//retorno del contador de iteraciones del kernel.
	return this->BUFF_UPCI_HL_V[this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT].KERNEL_ITERATION_COUNTER;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para obtener el contador de iteraciones del Hilo.
in GUPCI_HL_V::GetTHREAD_ITERATION_COUNTER()
{
	//---------------------------------------------------------------------------------
	//retorno del contador de iteraciones del Hilo.
	return this->BUFF_UPCI_HL_V[this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT].THREAD_ITERATION_COUNTER;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para obtener el contador de diferenciaciones globales de estructuras.
in GUPCI_HL_V::GetGLOBAL_DIFFERENTIATION_COUNTER()
{
	//---------------------------------------------------------------------------------
	//retorno del contador de diferenciaciones gloables.
	return this->BUFF_UPCI_HL_V[this->BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT].GLOBAL_DIFFERENTIATION_COUNTER;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para setear el estado de la bandera 'CLOSE_ACTIVE_THREADS_FLAG'.
vo GUPCI_HL_V::SetCLOSE_ACTIVE_THREADS_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'CLOSE_ACTIVE_THREADS_FLAG'.
	this->CLOSE_ACTIVE_THREADS_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para setear el estado de la bandera 'PAUSE_ACTIVE_THREADS_FLAG'.
vo GUPCI_HL_V::SetPAUSE_ACTIVE_THREADS_FLAG(in _status)
{
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'PAUSE_ACTIVE_THREADS_FLAG'.
	this->PAUSE_ACTIVE_THREADS_FLAG = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------- 
//#1: método para imprimir banderas.
vo GUPCI_HL_V::PrintBuffBanderas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//carga de banderas.
	cout << "STORAGE_FLAG                                : " << this->BUFF_UPCI_HL_V.at(_upci_id).STORAGE_FLAG<< endl;
	cout << "KERNEL_INTEGRATION_FLAG                     : " << this->BUFF_UPCI_HL_V.at(_upci_id).KERNEL_INTEGRATION_FLAG<< endl;
	cout << "THREAD_INTEGRATION_FLAG                     : " << this->BUFF_UPCI_HL_V.at(_upci_id).THREAD_INTEGRATION_FLAG<< endl;
	cout << "THREAD_INTEGRATION_LATENCY_FLAG             : " << this->BUFF_UPCI_HL_V.at(_upci_id).THREAD_INTEGRATION_LATENCY_FLAG<< endl;
	cout << "THREAD_INTEGRATION_FINISHED_FLAG            : " << this->BUFF_UPCI_HL_V.at(_upci_id).THREAD_INTEGRATION_FINISHED_FLAG << endl;
	cout << "NEW_INPUT_FLAG                              : " << this->BUFF_UPCI_HL_V.at(_upci_id).NEW_INPUT_FLAG<< endl;
	cout << "CLOSE_ACTIVE_THREADS_FLAG                   : " << this->BUFF_UPCI_HL_V.at(_upci_id).CLOSE_ACTIVE_THREADS_FLAG << endl;
	cout << "PAUSE_ACTIVE_THREADS_FLAG                   : " << this->BUFF_UPCI_HL_V.at(_upci_id).PAUSE_ACTIVE_THREADS_FLAG << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para imprimir buffers del núcleo.
vo GUPCI_HL_V::PrintBuffNucleo(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//carga de buffers del núcleo.
	cout << "UPCI_HL_V_ID OF STR_MAX_AL : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_MAX_AL->UPCI_ID<< endl;
	cout << "STR_ID OF STR MAX_AL       : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_MAX_AL->STR_ID << endl;
	cout << "MAX_ACTIVITY_LEVEL         : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_MAX_ACTIVITY_LEVEL<< endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para imprimir buffers de estructuras INIS_MD.
vo GUPCI_HL_V::PrintBuffEstructurasINIS_MD(in _upci_id, in _str_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam1	= 0;
	
	//---------------------------------------------------------------------------------
	//carga de registro IN_RG.
	cout << "IN_RG  : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD[_str_id].IN_RG << endl;

	//---------------------------------------------------------------------------------
	//carga de registro EV_RG.
	cout << "EV_RG  : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD[_str_id].EV_RG << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de sub-registros.
	cout << "CS_SRG : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD[_str_id].CS_SRG << endl;
	cout << "AL_SRG : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD[_str_id].AL_SRG << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//obtención del tamaño del vector de relaciones de la estructura.
	tam1 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD[_str_id].RL.size());

	//---------------------------------------------------------------------------------
	//bucle para cargar relaciones RL.
	for (in i2 = 0; i2 < tam1; i2++)
	{
		//-----------------------------------------------------------------------------
		//cargar de relaciones.
		cout << "rl(" << i2 << ") tipo      : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD[_str_id].RL[i2].at(0) << endl;
		cout << "rl(" << i2 << ") id        : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD[_str_id].RL[i2].at(1) << endl;		
		cout << "rl(" << i2 << ") upci id   : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD[_str_id].RL[i2].at(2) << endl;
		cout << endl;
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para imprimir buffers de estructuras SRLIS.
vo GUPCI_HL_V::PrintBuffEstructurasSRLIS(in _upci_id, in _str_id)
{
	//---------------------------------------------------------------------------------
	//carga de registros.
	cout << "STR1_TYPE_RG       : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS[_str_id].STR1_TYPE_RG << endl;
	cout << "STR2_TYPE_RG       : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS[_str_id].STR2_TYPE_RG << endl;
	cout << "STR1_ID_RG         : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS[_str_id].STR1_ID_RG << endl;
	cout << "STR2_ID_RG         : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS[_str_id].STR2_ID_RG << endl;
	cout << "UPCI_ID_STR1_RG    : " << (in)(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS[_str_id].UPCI_ID_STR1_RG) << endl;
	cout << "UPCI_ID_STR2_RG    : " << (in)(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS[_str_id].UPCI_ID_STR2_RG) << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de sub-registros.
	cout << "RS_SRG             : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS[_str_id].RS_SRG << endl;
	cout << "AL_SRG             : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS[_str_id].AL_SRG << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método para imprimir buffers de estructuras PFRLIS.
vo GUPCI_HL_V::PrintBuffEstructurasPFRLIS(in _upci_id, in _str_id)
{
	//---------------------------------------------------------------------------------
	//carga de registros.
	cout << "STR1_TYPE_RG       : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS[_str_id].STR1_TYPE_RG << endl;
	cout << "STR2_TYPE_RG       : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS[_str_id].STR2_TYPE_RG << endl;
	cout << "STR1_ID_RG         : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS[_str_id].STR1_ID_RG << endl;
	cout << "STR2_ID_RG         : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS[_str_id].STR2_ID_RG << endl;
	cout << "UPCI_ID_STR1_RG    : " << (in)(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS[_str_id].UPCI_ID_STR1_RG) << endl;
	cout << "UPCI_ID_STR2_RG    : " << (in)(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS[_str_id].UPCI_ID_STR2_RG) << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de sub-registros.
	cout << "RS_SRG             : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS[_str_id].RS_SRG << endl;
	cout << "AL_SRG             : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS[_str_id].AL_SRG << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#6: método para imprimir buffers de estructuras INDFRLIS_MD.
vo GUPCI_HL_V::PrintBuffEstructurasINDFRLIS_MD(in _upci_id, in _str_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam1	= 0;

	//---------------------------------------------------------------------------------
	//carga de registro IN_DIF_RG.
	cout << "IN_DIF_RG          : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD[_str_id].IN_DIF_RG << endl;

	//---------------------------------------------------------------------------------
	//carga de registro EV_DIF_RG.
	cout << "EV_DIF_RG          : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD[_str_id].EV_DIF_RG << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de registros
	cout << "STR1_ID_RG         : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD[_str_id].STR1_ID_RG << endl;
	cout << "STR2_ID_RG         : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD[_str_id].STR2_ID_RG << endl;
	cout << "UPCI_ID_STR1_RG    : " << (in)(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD[_str_id].UPCI_ID_STR1_RG) << endl;
	cout << "UPCI_ID_STR2_RG    : " << (in)(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD[_str_id].UPCI_ID_STR2_RG) << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de sub-registros.
	cout << "CS_SRG             : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD[_str_id].CS_SRG << endl;
	cout << "RS_SRG             : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD[_str_id].RS_SRG << endl;
	cout << "AL_SRG             : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD[_str_id].AL_SRG << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//obtención del tamaño del vector de relaciones de la estructura.
	tam1 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD[_str_id].RL.size());

	//---------------------------------------------------------------------------------
	//bucle para cargar relaciones RL.
	for (in i2 = 0; i2 < tam1; i2++)
	{
		//-----------------------------------------------------------------------------
		//cargar de relaciones.
		cout << "rl(" << i2 << ") tipo      : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD[_str_id].RL[i2].at(0) << endl;
		cout << "rl(" << i2 << ") id        : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD[_str_id].RL[i2].at(1) << endl;
		cout << "rl(" << i2 << ") upci id   : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD[_str_id].RL[i2].at(2) << endl;
		cout << endl;
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#7: método para imprimir buffers de estructuras INPRRLIS_MD.
vo GUPCI_HL_V::PrintBuffEstructurasINPRRLIS_MD(in _upci_id, in _str_id)
{
	//---------------------------------------------------------------------------------
	//carga de registro IN_PRO_RG.
	cout << "IN_PRO_RG          : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD[_str_id].IN_PRO_RG << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de registros
	cout << "STR1_ID_RG         : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD[_str_id].STR1_ID_RG << endl;
	cout << "STR2_ID_RG         : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD[_str_id].STR2_ID_RG << endl;
	cout << "UPCI_ID_STR1_RG    : " << (in)(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD[_str_id].UPCI_ID_STR1_RG) << endl;
	cout << "UPCI_ID_STR2_RG    : " << (in)(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD[_str_id].UPCI_ID_STR2_RG) << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de sub-registros.
	cout << "CS_SRG             : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD[_str_id].CS_SRG << endl;
	cout << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#8: método para imprimir estructuras candidatas INIS_MD.
vo GUPCI_HL_V::PrintBuffINIS_MDCandidatas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam0					= 0;
	in tam1					= 0;
	in tam2					= 0;

	//-----------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_INIS_MD_ID_CAN.
	tam0 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_ID_CAN->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir datos de los candidatos en los tiempos.
	for (in i1 = 0; i1 < tam0; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del tamaño del vector BUFF_INIS_MD_ID_CAN en tiempo [i1].
		tam1 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_ID_CAN->at(i1).size());

		//-----------------------------------------------------------------------------
		//bucle para imprimir datos de los candidatos por cada upci.
		for (in i2 = 0; i2 < tam1; i2++)
		{
			//-------------------------------------------------------------------------
			//obtención del tamaño del vector BUFF_INIS_MD_ID_CAN[i1][i2].
			tam2 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_ID_CAN->at(i1).at(i2).size());

			//-------------------------------------------------------------------------
			//bucle para imprimir datos de los candidatos.
			for (in i3 = 0; i3 < tam2; i3++)
			{
				//---------------------------------------------------------------------
				//carga de datos.
				cout << "tiempo("<<i1<<") upci_id("<<i2<<"): " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_ID_CAN->at(i1).at(i2).at(i3)<< endl;
			}
		}
	}	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#9: método para imprimir estructuras candidatas INDFRLIS_MD.
vo GUPCI_HL_V::PrintBuffINDFRLIS_MDCandidatas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam0					= 0;
	in tam1					= 0;
	in tam2					= 0;

	//-----------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_INDFRLIS_MD_ID_CAN.
	tam0 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_ID_CAN->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir datos de los candidatos en los tiempos.
	for (in i1 = 0; i1 < tam0; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del tamaño del vector BUFF_INDFRLIS_MD_ID_CAN en tiempo [i1].
		tam1 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_ID_CAN->at(i1).size());

		//-----------------------------------------------------------------------------
		//bucle para imprimir datos de los candidatos por cada upci.
		for (in i2 = 0; i2 < tam1; i2++)
		{
			//-------------------------------------------------------------------------
			//obtención del tamaño del vector BUFF_INDFRLIS_MD_ID_CAN[i1][i2].
			tam2 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_ID_CAN->at(i1).at(i2).size());

			//-------------------------------------------------------------------------
			//bucle para imprimir datos de los candidatos.
			for (in i3 = 0; i3 < tam2; i3++)
			{
				//---------------------------------------------------------------------
				//carga de datos.
				cout << "tiempo(" << i1 << ") upci_id(" << i2 << "): " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_ID_CAN->at(i1).at(i2).at(i3) << endl;
			}
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#10: método para imprimir estructuras candidatas INPRRLIS_MD.
vo GUPCI_HL_V::PrintBuffINPRRLIS_MDCandidatas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam0					= 0;
	in tam1					= 0;
	in tam2					= 0;

	//-----------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_INPRRLIS_MD_ID_CAN.
	tam0 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD_ID_CAN->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir datos de los candidatos en los tiempos.
	for (in i1 = 0; i1 < tam0; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del tamaño del vector BUFF_INPRRLIS_MD_ID_CAN en tiempo [i1].
		tam1 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD_ID_CAN->at(i1).size());

		//-----------------------------------------------------------------------------
		//bucle para imprimir datos de los candidatos por cada upci.
		for (in i2 = 0; i2 < tam1; i2++)
		{
			//-------------------------------------------------------------------------
			//obtención del tamaño del vector BUFF_INPRRLIS_MD_ID_CAN[i1][i2].
			tam2 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD_ID_CAN->at(i1).at(i2).size());

			//-------------------------------------------------------------------------
			//bucle para imprimir datos de los candidatos.
			for (in i3 = 0; i3 < tam2; i3++)
			{
				//---------------------------------------------------------------------
				//carga de datos.
				cout << "tiempo(" << i1 << ") upci_id(" << i2 << "): " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD_ID_CAN->at(i1).at(i2).at(i3) << endl;
			}
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#11: método para imprimir las id de upci con estructuras INIS_MD candidatas.
vo GUPCI_HL_V::PrintBuffIdUpcINIS_MDCandidatas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam0	= 0;
	in tam1	= 0;

	//-----------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_UPCI_ID_INIS_MD_CAN.
	tam0 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_UPCI_ID_INIS_MD_CAN->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir las id upci con estructuras candidatas en los dos tiempos.
	for (in i1 = 0; i1 < tam0; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del tamaño del vector BUFF_UPCI_ID_INIS_MD_CAN.
		tam1 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_UPCI_ID_INIS_MD_CAN->at(i1).size());

		//-----------------------------------------------------------------------------
		//bucle para imprimir las id upci con estructuras candidatas.
		for (in i2 = 0; i2 < tam1; i2++)
		{
			//-------------------------------------------------------------------------
			//carga del id.
			cout << "id: " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_UPCI_ID_INIS_MD_CAN->at(i1).at(i2) << endl;
		}
	}	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#12: método para imprimir las id de upci con estructuras INDFRLIS_MD candidatas.
vo GUPCI_HL_V::PrintBuffIdUpcINDFRLIS_MDCandidatas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam0 = 0;
	in tam1 = 0;

	//-----------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_UPCI_ID_INDFRLIS_MD_CAN.
	tam0 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_UPCI_ID_INDFRLIS_MD_CAN->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir las id upci con estructuras candidatas en los dos tiempos.
	for (in i1 = 0; i1 < tam0; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del tamaño del vector BUFF_UPCI_ID_INDFRLIS_MD_CAN.
		tam1 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_UPCI_ID_INDFRLIS_MD_CAN->at(i1).size());

		//-----------------------------------------------------------------------------
		//bucle para imprimir las id upci con estructuras candidatas.
		for (in i2 = 0; i2 < tam1; i2++)
		{
			//-------------------------------------------------------------------------
			//carga del id.
			cout << "id: " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_UPCI_ID_INDFRLIS_MD_CAN->at(i1).at(i2) << endl;
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#13: método para imprimir las id de upci con estructuras INPRRLIS_MD candidatas.
vo GUPCI_HL_V::PrintBuffIdUpcINPRRLIS_MDCandidatas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam0 = 0;
	in tam1 = 0;

	//-----------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_UPCI_ID_INPRRLIS_MD_CAN.
	tam0 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_UPCI_ID_INPRRLIS_MD_CAN->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir las id upci con estructuras candidatas en los dos tiempos.
	for (in i1 = 0; i1 < tam0; i1++)
	{
		//-----------------------------------------------------------------------------
		//obtención del tamaño del vector BUFF_UPCI_ID_INPRRLIS_MD_CAN.
		tam1 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_UPCI_ID_INPRRLIS_MD_CAN->at(i1).size());

		//-----------------------------------------------------------------------------
		//bucle para imprimir las id upci con estructuras candidatas.
		for (in i2 = 0; i2 < tam1; i2++)
		{
			//-------------------------------------------------------------------------
			//carga del id.
			cout << "id: " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_UPCI_ID_INPRRLIS_MD_CAN->at(i1).at(i2) << endl;
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#14: método para imprimir buffer de los id de estructuras disponibles.
vo GUPCI_HL_V::PrintBuffIdEstDisponibles(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//carga de buffers para los id de las estructura disponibles.
	cout << "BUFF_INIS_MD_ID_AV[0]      : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_ID_AV[0]<< endl;					
	cout << "BUFF_INIS_MD_ID_AV[1]      : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_ID_AV[1]<< endl;	
	cout << endl;
	cout << "BUFF_SRLIS_ID_AV[0]        : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS_ID_AV[0] << endl;
	cout << "BUFF_SRLIS_ID_AV[1]        : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS_ID_AV[1] << endl;
	cout << endl;
	cout << "BUFF_PFRLIS_ID_AV[0]       : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS_ID_AV[0]<< endl;
	cout << "BUFF_PFRLIS_ID_AV[1]       : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS_ID_AV[1]<< endl;
	cout << endl;
	cout << "BUFF_INDFRLIS_MD_ID_AV[0]  : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_ID_AV[0]<< endl;
	cout << "BUFF_INDFRLIS_MD_ID_AV[1]  : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_ID_AV[1]<< endl;
	cout << endl;
	cout << "BUFF_INPRRLIS_MD_ID_AV[0]  : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD_ID_AV[0]<< endl;
	cout << "BUFF_INPRRLIS_MD_ID_AV[1]  : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD_ID_AV[1]<< endl;
	cout << endl;
}

//-------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------- 
//#15: método para imprimir buffer de los id y tipos de estructuras creadas.
vo GUPCI_HL_V::PrintBuffIdYTipoEstCreadas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//carga de buffers para los id y tipos de las estructuras creadas.
	cout << "BUFF_INIS_MD_CRE[0].STR_ID       : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_CRE[0].STR_ID << endl;
	cout << "BUFF_INIS_MD_CRE[1].STR_ID       : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_CRE[1].STR_ID << endl;
	cout << endl;
	cout << "BUFF_SRLIS_CRE[0].STR_ID         : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS_CRE[0].STR_ID << endl;
	cout << "BUFF_SRLIS_CRE[1].STR_ID         : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS_CRE[1].STR_ID << endl;
	cout << endl;
	cout << "BUFF_PFRLIS_CRE[0].STR_ID        : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS_CRE[0].STR_ID<< endl;
	cout << "BUFF_PFRLIS_CRE[1].STR_ID        : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS_CRE[1].STR_ID<< endl;
	cout << endl;
	cout << "BUFF_INDFRLIS_MD_CRE[0].STR_ID   : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_CRE[0].STR_ID << endl;
	cout << "BUFF_INDFRLIS_MD_CRE[1].STR_ID   : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_CRE[1].STR_ID << endl;
	cout << endl;
	cout << "BUFF_INPRRLIS_MD_CRE[0].STR_ID   : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD_CRE[0].STR_ID << endl;
	cout << "BUFF_INPRRLIS_MD_CRE[1].STR_ID   : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD_CRE[1].STR_ID << endl;	
	cout << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------  
//#16: método para imprimir buffer de los id de estructuras reconocidas.
vo GUPCI_HL_V::PrintBuffEstReconocidas(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//estructuras INIS_MD.
	cout << "INIS_MD-UPCI_HL_V_ID      : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_RE->UPCI_ID<< endl;
	cout << "INIS_MD-STR_ID            : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_RE->STR_ID<< endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//estructuras INDFRLIS_MD.
	cout << "INDFRLIS_MD-UPCI_HL_V_ID  : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_RE->UPCI_ID<< endl;
	cout << "INDFRLIS_MD-STR_ID        : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_RE->STR_ID<< endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//estructuras INPRRLIS_MD.
	cout << "INPRRLIS_MD-UPCI_HL_V_ID  : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD_RE->UPCI_ID<< endl;
	cout << "INPRRLIS_MD-STR_ID        : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD_RE->STR_ID<< endl;
	cout << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#17: método para imprimir buffer cantidades de upci y estructuras, 
//y ids de las estructuras en suspensión.
vo GUPCI_HL_V::PrintBuffCantUpciEstSuspension(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//inicialización de variables auxiliares.
	in tam1					= 0;

	//---------------------------------------------------------------------------------
	//carga de la cantidad total de estructuras INIS_MD en estado de suspensión.
	cout << "BUFF_INIS_MD_SUS AMOUNT      : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_SUS->size()<< endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de la cantidad total de estructuras SRLIS en estado de suspensión.
	cout << "BUFF_SRLIS_SUS AMOUNT        : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS_SUS->size() << endl;
	cout << endl;
	
	//---------------------------------------------------------------------------------
	//carga de la cantidad total de estructuras PFRLIS en estado de suspensión.
	cout << "BUFF_PFRLIS_SUS AMOUNT       : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS_SUS->size() << endl;
	cout << endl;

	//---------------------------------------------------------------------------------
	//carga de la cantidad total de estructuras INDFRLIS_MD en estado de suspensión.
	cout << "BUFF_INDFRLIS_MD_SUS AMOUNT  : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_SUS->size() << endl;
	cout << endl;
	
	//---------------------------------------------------------------------------------
	//impresión de INIS_MD suspendidos.
	cout << "INIS_MD: " << endl;

	//---------------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_INIS_MD_SUS.
	tam1 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_SUS->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir id de las estructuras INIS_MD en estado de suspensión.
	for (in i1 = 0; i1 < tam1; i1++)
	{
		//-----------------------------------------------------------------------------
		//carga de los id de las estructuras en estado de suspensión.
		cout << "id upci  : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_SUS->at(i1).UPCI_ID<< endl;
		cout << "id str   : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_SUS->at(i1).STR_ID<< endl;
		cout << endl;
	}

	//---------------------------------------------------------------------------------
	//impresión de SRLIS suspendidos.
	cout << "SRLIS: " << endl;

	//---------------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_SRLIS_SUS.
	tam1 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS_SUS->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir id de las estructuras SRLIS en estado de suspensión.
	for (in i1 = 0; i1 < tam1; i1++)
	{
		//-----------------------------------------------------------------------------
		//carga de los id de las estructuras en estado de suspensión.
		cout << "id upci  : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS_SUS->at(i1).UPCI_ID << endl;
		cout << "id str   : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS_SUS->at(i1).STR_ID << endl;
		cout << endl;
	}

	//---------------------------------------------------------------------------------
	//impresión de PFRLIS suspendidos.
	cout << "PFRLIS: " << endl;

	//---------------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_PFRLIS_SUS.
	tam1 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS_SUS->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir id de las estructuras PFRLIS en estado de suspensión.
	for (in i1 = 0; i1 < tam1; i1++)
	{
		//-----------------------------------------------------------------------------
		//carga de los id de las estructuras en estado de suspensión.
		cout << "id upci  : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS_SUS->at(i1).UPCI_ID << endl;
		cout << "id str   : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS_SUS->at(i1).STR_ID << endl;
		cout << endl;
	}

	//---------------------------------------------------------------------------------
	//impresión de INDFRLIS_MD suspendidos.
	cout << "INDFRLIS_MD: " << endl;

	//---------------------------------------------------------------------------------
	//obtención del tamaño del vector BUFF_INDFRLIS_MD_SUS.
	tam1 = in(this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_SUS->size());

	//---------------------------------------------------------------------------------
	//bucle para imprimir id de las estructuras INDFRLIS_MD en estado de suspensión.
	for (in i1 = 0; i1 < tam1; i1++)
	{
		//-----------------------------------------------------------------------------
		//carga de los id de las estructuras en estado de suspensión.
		cout << "id upci  : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_SUS->at(i1).UPCI_ID << endl;
		cout << "id str   : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_SUS->at(i1).STR_ID << endl;
		cout << endl;
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#18: método para imprimir buffer con la scantidades de estructuras existentes.
vo GUPCI_HL_V::PrintBuffCantEstExistentes(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//buffers auxiliares para almacenar los ids.
	in	var_aux				= OFF;															//variable auxiliar de impresión.
	sst	buff_aux;																			//buffer auxiliar.
	st	buff_inis_md_id;																	//buffer para inis_md.
	st	buff_srlis_id;																		//buffer para srlis.
	st	buff_pfrlis_id;																		//buffer para pfrlis.
	st	buff_indfrlis_id;																	//buffer para indfrlis.
	st	buff_inprrlis_id;																	//buffer para inprrlis.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para obtener los ids de inis_md inicializados.
	for (in i1 = 0; i1 < this->BUFF_UPCI_HL_V.at(_upci_id).INIS_MD_AMOUNT_ALLOWED; i1++)
	{
		//-----------------------------------------------------------------------------
		//si es la primera iteración, entonces.
		if (var_aux == OFF)
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD[i1].AL_SRG != -1)
			{
				//---------------------------------------------------------------------
				//limpieza y seteo del id.
				buff_aux		<< i1;
				buff_inis_md_id	= buff_aux.str();
				var_aux			= ON;
			}
		}

		//-----------------------------------------------------------------------------
		//si es después de la primera iteración, entonces.
		else 
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD[i1].AL_SRG != -1)
			{
				//---------------------------------------------------------------------
				//limpieza y seteo del id.
				buff_aux.str("");
				buff_aux		<< i1;
				buff_inis_md_id	= buff_inis_md_id + ", " + buff_aux.str();
			}
		}		
	}
	
	//---------------------------------------------------------------------------------
	//reset de variable auxiliar de impresión.
	var_aux = OFF;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para obtener los ids de srlis inicializados.
	for (in i1 = 0; i1 < this->BUFF_UPCI_HL_V.at(_upci_id).RLIS_AMOUNT_ALLOWED; i1++)
	{
		//-----------------------------------------------------------------------------
		//si es la primera iteración, entonces.
		if (var_aux == OFF)
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS[i1].RS_SRG != -1)
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
			if (this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS[i1].RS_SRG != -1)
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
	//bucle para obtener los ids de pfrlis inicializados.
	for (in i1 = 0; i1 < this->BUFF_UPCI_HL_V.at(_upci_id).RLIS_AMOUNT_ALLOWED; i1++)
	{
		//-----------------------------------------------------------------------------
		//si es la primera iteración, entonces.
		if (var_aux == OFF)
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS[i1].RS_SRG != -1)
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
			if (this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS[i1].RS_SRG != -1)
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
	for (in i1 = 0; i1 < this->BUFF_UPCI_HL_V.at(_upci_id).RLIS_AMOUNT_ALLOWED; i1++)
	{
		//-----------------------------------------------------------------------------
		//si es la primera iteración, entonces.
		if (var_aux == OFF)
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD[i1].RS_SRG != -1)
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
			if (this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD[i1].RS_SRG != -1)
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
	for (in i1 = 0; i1 < this->BUFF_UPCI_HL_V.at(_upci_id).RLIS_AMOUNT_ALLOWED; i1++)
	{
		//-----------------------------------------------------------------------------
		//si es la primera iteración, entonces.
		if (var_aux == OFF)
		{
			//-------------------------------------------------------------------------
			//si al estructura está inicializada.
			if (this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD[i1].CS_SRG != -1)
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
			if (this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD[i1].CS_SRG != -1)
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
	cout << "BUFF_INIS_MD_INI_AMOUNT       : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_INI_AMOUNT<< ", con ids: "<< buff_inis_md_id <<endl;
	cout << "BUFF_SRLIS_INI_AMOUNT         : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS_INI_AMOUNT << ", con ids: " << buff_srlis_id << endl;
	cout << "BUFF_PFRLIS_INI_AMOUNT        : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS_INI_AMOUNT << ", con ids: " << buff_pfrlis_id << endl;
	cout << "BUFF_INDFRLIS_MD_INI_AMOUNT   : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_INI_AMOUNT << ", con ids: " << buff_indfrlis_id << endl;
	cout << "BUFF_INPRRLIS_MD_INI_AMOUNT   : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD_INI_AMOUNT << ", con ids: " << buff_inprrlis_id << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#19: método para imprimir buffer con la cantidad de expansiones.
vo GUPCI_HL_V::PrintBuffCantExp(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//carga de buffers para la cantidad de expansiones.
	cout << "GLOBAL_DIFFERENTIATION_COUNTER: " << this->BUFF_UPCI_HL_V.at(_upci_id).GLOBAL_DIFFERENTIATION_COUNTER<< endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#20: métoddo para imprimir buffer con los máximos id de las estructuras.
vo GUPCI_HL_V::PrintBuffMaxIdEst(in _upci_id)
{
	//---------------------------------------------------------------------------------
	//carga de buffers para los máximos ids.
	cout << "BUFF_INIS_MD_MAX_ID[0]         : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_MAX_ID[0]<< endl;					
	cout << "BUFF_INIS_MD_MAX_ID[1]         : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INIS_MD_MAX_ID[1]<< endl;		
	cout << endl;
	cout << "BUFF_SRLIS_MAX_ID[0]           : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS_MAX_ID[0] << endl;
	cout << "BUFF_SRLIS_MAX_ID[1]           : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_SRLIS_MAX_ID[1] << endl;
	cout << endl;
	cout << "BUFF_PFRLIS_MAX_ID[0]          : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS_MAX_ID[0]<< endl;					
	cout << "BUFF_PFRLIS_MAX_ID[1]          : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_PFRLIS_MAX_ID[1]<< endl;
	cout << endl;
	cout << "BUFF_INDFRLIS_MD_MAX_ID[0]     : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_MAX_ID[0]<< endl;
	cout << "BUFF_INDFRLIS_MD_MAX_ID[1]     : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INDFRLIS_MD_MAX_ID[1]<< endl;
	cout << endl;
	cout << "BUFF_INPRRLIS_MD_MAX_ID[0]     : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD_MAX_ID[0]<< endl;
	cout << "BUFF_INPRRLIS_MD_MAX_ID[1]     : " << this->BUFF_UPCI_HL_V.at(_upci_id).BUFF_INPRRLIS_MD_MAX_ID[1]<< endl;
	cout << endl;
}