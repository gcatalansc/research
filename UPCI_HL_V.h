#pragma once
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
	Nombre Clase : 	  UPCI_HL_V (Unidad de procesos cognitivos integradora de alto 
					  nivel (HL) para visión (V) 
	Date	     :	  12:58 pm 12-06-2017.
	Diseñador    :	  Gustavo Catalán Ulloa.
*/
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//librerias.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <mutex>
#include <deque>
#include <vector>
#include <cmath>
#include <time.h>
#include "DEFINITIONS.h"
#include "UPCI_HL_V_ARG.h"
#include "BUFF_STR_ITI.h"
#include "BUFF_STR_ITIT.h"
#include "BUFF_STR_ITIE.h"
#include "INIS_MD.h"
#include "SRLIS.h"
#include "PFRLIS.h"
#include "INDFRLIS_MD.h"
#include "INPRRLIS_MD.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//espacio de nombres.
using namespace UPC;
using namespace std;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//tipos.
typedef 	void							vo;
typedef		int								in;
typedef		double							dou;
typedef		string							st;
typedef		const int						coin;
typedef		vector<int>						vein;
typedef		deque<deque<int>>				dedein;
typedef		deque<deque<deque<int>>>		dededein;
typedef		deque<BUFF_STR_ITI>				deBUFF_STR_II;
typedef		deque<BUFF_STR_ITIE>			deBUFF_STR_IIE;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//nombre de espacio UPC.
namespace UPC
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//clase UPCI_HL_V.
	class UPCI_HL_V
	{
		//elementos públicos.
	public:

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################ PARÁMETROS ################################# 
		
		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//parámetros estructurales.
		in						*GUPCI_ID;													//puntero a id de la gupci.
		in						UPCI_ID;													//id de la upci.
		in						INIS_MD_AMOUNT_ALLOWED;										//cantidad de estructuras INIS_MD permitidas.
		in						RLIS_AMOUNT_ALLOWED;										//cantidad de estructuras de relaciones permitidas por tipo.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//parámetros de actividad.
		dou						DEFAULT_ACTIVITY_LEVEL;										//nivel de actividad por defecto.
		dou						MAX_ACTIVITY_LEVEL_ALLOWED;									//nivel de actividad máximo permitido.
		dou						MIN_ACTIVITY_LEVEL_ALLOWED;									//nivel de actividad mínimo permitido.	

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------    
		//umbrales.
		dou						DIF_RAW_INPUT_THRESHOLD;									//umbral de entrada cruda para focalización de la atención (%).
		dou						STR_CONGRUENCE_THRESHOLD;									//umbral de congruencia para estructuras candidatas (%).	
		dou						PFRLIS_STRENGTH_THRESHOLD;									//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
		dou						INDFRLIS_MD_STRENGTH_THRESHOLD;								//umbral de fortaleza de relación INDFRLIS_MD para eliminar relación por N.A.
		dou						EVALUATION_THRESHOLD;										//umbral para evaluaciones.	
		dou						TRANSITION_EVALUATION_THRESHOLD;							//umbral para transición de evaluaciones.	

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################ BANDERAS ################################### 

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//bandera del estado del almacenamiento de la unidad (ON: salvar, OFF: no-salvar).
		in						STORAGE_FLAG;												

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//bandera del estado de integración del kernel (ON: integrando, OFF: libre).
		in						KERNEL_INTEGRATION_FLAG;									

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//banderas del integrador de Hilos.
		in						THREAD_INTEGRATION_FLAG;									//bandera del estado de integración del Hilo (ON: integrando, OFF: libre).
		in						THREAD_INTEGRATION_LATENCY_FLAG;							//bandera del estado de latencia de la integración del Hilo.
		in						THREAD_INTEGRATION_FINISHED_FLAG;							//bandera de aviso del término de la integración del Hilo.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//banderas para estructuras creadas.
		in						NEW_INPUT_FLAG;												//bandera de alerta de una nueva entrada.
		in						NEW_INPUT_DIFFERENCE_RELATION_FLAG;							//bandera de alerta de la creación de una nueva relación de diferencia de entradas.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//banderas para estructuras que superen umbral de congruencia.
		in						INIS_MD_CONGRUENCE_ACCOMPLISHED;							//bandera para estructuras INIS_MD que superen umbral de congruencia.
		in						INDFRLIS_MD_CONGRUENCE_ACCOMPLISHED;						//bandera para estructuras INDFRLIS_MD que superen umbral de congruencia.
		in						INPRRLIS_MD_CONGRUENCE_ACCOMPLISHED;						//bandera para estructuras INPRRLIS_MD que superen umbral de congruencia.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//punteros a banderas para threads activos.
		in						*CLOSE_ACTIVE_THREADS_FLAG;									//puntero a bandera para cerrar threads activos.
		in						*PAUSE_ACTIVE_THREADS_FLAG;									//puntero a bandera para pausar threads activos.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//bandera para imprimir en pantalla.
		in						PRINT_FLAG;													

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################# TIEMPOS ################################### 

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//tiempos para threads de limpieza y actualización.
		in						TIMEOUT_CLEAN_IS;											//tiempo de espera de limpieza de IS (ms).	
		in						TIMEOUT_UPDATE_AL_IS;										//tiempo de espera para actualizar niveles de actividad en IS (ms).

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################# BUFFERS ################################### 

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//puntero a buffers del grupo de upci.
		deque<UPCI_HL_V>		*BUFF_UPCI;	

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------  
		//puntero a buffer para el id de la upci que puede almacenar estructuras.
		in						*BUFF_UPCI_ID_STORAGE_FLAG_ACT;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para las estructuras de información.
		INIS_MD					*BUFF_INIS_MD;												//buffer para estructuras de entrada.
		SRLIS					*BUFF_SRLIS;												//buffer para estructuras de relación simple.
		PFRLIS					*BUFF_PFRLIS;												//buffer para estructuras de relación de flujo puro.
		INDFRLIS_MD				*BUFF_INDFRLIS_MD;											//buffer para estructuras de relación de flujo diferencial de entradas.	
		INPRRLIS_MD				*BUFF_INPRRLIS_MD;											//buffer para estructuras de relación de flujo diferencial de entradas.	

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para registros.
		dou						*BUFF_IN_RG;												//puntero a buffer para registro de entrada.
		dou						*BUFF_EV_RG;												//puntero a buffer para registro de evaluación de entrada.
		dou						*BUFF_IN_DIF_RG;											//puntero a buffer para registro de diferencia de entradas.
		dou						*BUFF_IN_PRO_RG;											//puntero a buffer para registro de proporción de diferencia de entradas.
		dou						*BUFF_OUTPUT_PROJECTION;									//puntero a buffer para registro de proyección de salida.
		
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//punteros a buffers para estructura INIS_MD con evaluación máxima.
		BUFF_STR_ITI			*BUFF_INIS_MD_MAX_EVAL;										//puntero a buffer para la estructura INIS_MD con máxima evaluación.
		dou						*BUFF_MAX_EVALUATION;										//puntero a buffer para la máxima evaluación.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//punteros a buffers para estructura INIS_MD con nivel de actividad máximo.
		BUFF_STR_ITI			*BUFF_INIS_MD_MAX_AL;										//puntero a buffer para la estructura INIS_MD con nivel de actividad máximo.
		dou						*BUFF_MAX_ACTIVITY_LEVEL;									//puntero a buffer para el máximo nivel de actividad.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//punteros a buffers para estructura con fortaleza de la relación máximo.
		BUFF_STR_ITIT			*BUFF_STR_MAX_RS;											//puntero a buffer para la estructura con fortaleza de la relación máximo.
		dou						*BUFF_MAX_RELATION_STRENGTH;								//puntero a buffer para el máximo fortaleza de la relación.		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para los id de las estructuras disponibles.
		in						BUFF_INIS_MD_ID_AV[2];										//buffer para id de INIS_MD disponible.
		in						BUFF_SRLIS_ID_AV[2];										//buffer para id de SRLIS disponible.	
		in						BUFF_PFRLIS_ID_AV[2];										//buffer para id de PFRLIS disponible.	
		in						BUFF_INDFRLIS_MD_ID_AV[2];									//buffer para id de INDFRLIS_MD disponible.
		in						BUFF_INPRRLIS_MD_ID_AV[2];									//buffer para id de INPRRLIS_MD disponible.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para las estructuras creadas.
		BUFF_STR_ITI			*BUFF_INIS_MD_CRE;											//puntero a buffer para estructuras INIS_MD creadas.
		BUFF_STR_ITI			*BUFF_SRLIS_CRE;											//puntero a buffer para estructuras SRLIS creadas.
		BUFF_STR_ITI			*BUFF_PFRLIS_CRE;											//puntero a buffer para estructuras PFRLIS creadas.
		BUFF_STR_ITI			*BUFF_INDFRLIS_MD_CRE;										//puntero a buffer para estructuras INDFRLIS_MD creadas.
		BUFF_STR_ITI			*BUFF_INPRRLIS_MD_CRE;										//puntero a buffer para estructuras INPRRLIS_MD creadas.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//punteros a buffer para las estructuras INIS_MD activadas.
		BUFF_STR_ITI			*BUFF_INIS_MD_ACTIVATED;									//puntero a buffer para las estructuras INIS_MD activadas.		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para las estructuras en estado de suspensión.		
		deBUFF_STR_II			*BUFF_INIS_MD_SUS;											//puntero a buffer para las estructuras INIS_MD suspendidas.
		deBUFF_STR_II			*BUFF_SRLIS_SUS;											//puntero a buffer para las estructuras SRLIS suspendidas.
		deBUFF_STR_II			*BUFF_PFRLIS_SUS;											//puntero a buffer para las estructuras PFRLIS suspendidas.
		deBUFF_STR_II			*BUFF_INDFRLIS_MD_SUS;										//puntero a buffer para las estructuras INDFRLIS_MD suspendidas.	

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para los id de las upci candidatas. 
		//[a][b]: a: tiempo, b: upci.
		dedein					*BUFF_UPCI_ID_INIS_MD_CAN;									//puntero a buffer de id de las upci candidatas para INIS_MD.
		dedein					*BUFF_UPCI_ID_INDFRLIS_MD_CAN;								//puntero a buffer de id de las upci candidatas para INDFRLIS_MD.
		dedein					*BUFF_UPCI_ID_INPRRLIS_MD_CAN;								//puntero a buffer de id de las upci candidatas para INPRRLIS_MD.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffer de estructuras candidatas. 
		//[a][b][c]: a: tiempo, b: upci, c: buffer de estructura.
		dededein				*BUFF_INIS_MD_ID_CAN;										//puntero a buffer de ids de estructuras tipo INIS_MD candidatas.
		dededein				*BUFF_INDFRLIS_MD_ID_CAN;									//puntero a buffer de ids de estructuras tipo INDFRLIS_MD candidatas.
		dededein				*BUFF_INPRRLIS_MD_ID_CAN;									//puntero a buffer de ids de estructuras tipo INPRRLIS_MD candidatas.	

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//puntero a buffer para índice de la relación utilizada en flujo por reconocimiento.
		in						*BUFF_RL_INDEX_USED_IN_RECOGNITION;

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//punteros a buffers para las estructuras reconocidas.
		BUFF_STR_ITI			*BUFF_INIS_MD_RE;											//puntero a buffer para estructura reconocida INIS_MD.
		BUFF_STR_ITI			*BUFF_INDFRLIS_MD_RE;										//puntero a buffer para estructura reconocida INDFRLIS_MD.
		BUFF_STR_ITI			*BUFF_INPRRLIS_MD_RE;										//puntero a buffer para estructura reconocida INPRRLIS_MD.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para los máximos ids.
		in						BUFF_INIS_MD_MAX_ID[2];										//buffer para máximos ids en estructuras INIS_MD.
		in						BUFF_SRLIS_MAX_ID[2];										//buffer para máximos ids en estructuras SRLIS.
		in						BUFF_PFRLIS_MAX_ID[2];										//buffer para máximos ids en estructuras PFRLIS.
		in						BUFF_INDFRLIS_MD_MAX_ID[2];									//buffer para máximos ids en estructuras INDFRLIS_MD.
		in						BUFF_INPRRLIS_MD_MAX_ID[2];									//buffer para máximos ids en estructuras INPRRLIS_MD.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para la cantidad de estructuras inicializadas.
		in						BUFF_INIS_MD_INI_AMOUNT;									//buffer para la cantidad de INIS_MD inicializadas.
		in						BUFF_SRLIS_INI_AMOUNT;										//buffer para la cantidad de SRLIS inicializadas.
		in						BUFF_PFRLIS_INI_AMOUNT;										//buffer para la cantidad de PFRLIS inicializadas.
		in						BUFF_INDFRLIS_MD_INI_AMOUNT;								//buffer para la cantidad de INDFRLIS_MD inicializadas.
		in						BUFF_INPRRLIS_MD_INI_AMOUNT;								//buffer para la cantidad de INPRRLIS_MD inicializadas.
		in						BUFF_TOTAL_STR_INI_AMOUNT;									//buffer para la cantidad total de IS inicializadas.									

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//buffers auxiliares.
		BUFF_STR_ITI			BUFF_STR_SUS_AUX;											//buffer auxiliar para estructuras en suspensión.

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//############################### CONTADORES ##################################

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//contadores.
		in						KERNEL_ITERATION_COUNTER;									//contador de iteraciones del kernel.
		in						THREAD_ITERATION_COUNTER;									//contador de iteraciones del Hilo.
		in						GLOBAL_DIFFERENTIATION_COUNTER;								//contador de diferenciaciones globales.

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################ THREADS #################################### 

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//threads para procesamiento.												
		thread					TH_THREAD_INTEGRATION;										//thread para integración de entradas de la upci.
		thread					TH_CLEAN_STR_BUFFERS;										//thread para limpieza de buffers de IS.
		thread					TH_UPDATE_AL_STR_BUFFERS;									//thread para actualizar niveles de actividad de buffers de IS.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//mutex para escritura.
		std::mutex				RED_LIGHT_MUTEX;					

	//métodos públicos.
	public:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos constructor.
		UPCI_HL_V();
		UPCI_HL_V(in _upci_id, in _storage_flag, UPCI_HL_V_ARG &_upci_arg);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos destructor.
		~UPCI_HL_V();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos de inicialización.
		in			Initialize(UPCI_HL_V_ARG &_upci_arg);
		in			Initialize(in _upci_id, in _storage_flag, UPCI_HL_V_ARG &_upci_arg);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para Clean upci.
		inline in	Clean();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para el kernel.
		vo			KernelInput();

		//-----------------------------------------------------------------------------  
		//-----------------------------------------------------------------------------
		//método de entrada para la integración de Hilos.	
		vo			ThreadIntegrationInput();
		
		//-----------------------------------------------------------------------------  
		//-----------------------------------------------------------------------------   
		//métodos para la integración de Hilos reconocidos.	
		inline vo	RecognizedThreadIntegrationINIS_MD();
		inline vo	RecognizedThreadIntegrationACIS();

		//-----------------------------------------------------------------------------  
		//-----------------------------------------------------------------------------   
		//métodos para obtener acciones potenciales.
		inline vo	GetPotentialActionsINIS_MD(in _inis_id, in _rl_index_to_use, BUFF_STR_ITIE *_potential_action);
		inline vo	GetPotentialActionsPFRLIS(in _pfrlis_id, BUFF_STR_ITIE *_potential_action);
		inline vo	GetPotentialActionsINDFRLIS_MD(in _indfrlis_id, BUFF_STR_ITIE *_potential_action);

		//-----------------------------------------------------------------------------  
		//-----------------------------------------------------------------------------
		//método para obtener id de la acción ganadora.
		inline in	GetWinningPotentialActionIndex(dou _input_evaluation, deBUFF_STR_IIE &_potential_thread);		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos para estructuras de entrada como salida.		
		inline vo	GetCausalEstructure(in _inis_id, in & _causal_inis_id, in &_upci_id_causal_inis);				
		inline vo	GetWinningSuspendedAction(in & _winning_sus_acis_id, in &_upci_id_winning_sus_acis);
		inline dou	GetActionEvaluation(in _acis_id);
		inline vo	OutputEstructure(in _inis_id);					

		//----------------------------------------------------------------------------- 
		//----------------------------------------------------------------------------- 
		//métodos para crear estructuras.
		inline vo	CreateINIS_MD(dou *_in_rg, dou _ev_rg, coin _rs_srg);
		inline vo	CreateSRLIS(in _str1_type, in _str2_type, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2);
		inline vo	CreatePFRLIS(in _str1_type, in _str2_type, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2);
		inline vo	CreateINDFRLIS_MD(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2);
		inline vo	CreateINPRRLIS_MD(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2);
 
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos para Delete estructuras.
		inline vo	DeleteINIS_MD(in _inis_id);		
		inline vo	DeleteSRLIS(in _srlis_id);
		inline vo	DeletePFRLIS(in _pfrlis_id);	
		inline vo	DeleteINDFRLIS_MD(in _indfrlis_id);
		inline vo	DeleteINPRRLIS_MD(in _inprrlis_id);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos para Delete estructuras con excepción a una estructura.
		inline vo	DeleteSRLIS(in _srlis_id, in _str_type, in _str_id, in _upci_id_str);
		inline vo	DeletePFRLIS(in _pfrlis_id, in _str_type, in _str_id, in _upci_id_str);
		inline vo	DeleteINDFRLIS_MD(in _indfrlis_id, in _str_id, in _upci_id_str);
		inline vo	DeleteINPRRLIS_MD(in _indfrlis_id, in _str_id, in _upci_id_str);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para limpiar buffer de proyección de salida.
		inline vo	CleanBUFF_OUTPUT_PROJECTION();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método thread para limpiar buffers de IS.
		inline vo	CleanISBuffers();														

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos para limpiar buffers de IS.
		inline vo	CleanSRLIS();
		inline vo	CleanPFRLIS();
		inline vo	CleanINDFRLIS_MD();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos para relacionar estructuras.
		inline vo	RelateINIS_MD_CR(in _inis_id);
		inline vo	RelateINIS_MD_F(in _inis_id);
		inline vo	RelateINDFRLIS_MD(in _indfrlis_id);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos para chekear la no repetición de relaciones contiguas.
		inline in	CheckPreviousSRLIS(in _str1_type, in _str2_type, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2);
		inline in	CheckPreviousPFRLIS(in _str1_type, in _str2_type, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2);
		inline in	CheckPreviousINDFRLIS_MD(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2);
		inline in	CheckPreviousINPRRLIS_MD(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2);

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//método para reactivar estructuras de información.
		inline vo	ReactiveINIS_MD(in _inis_id);
		inline vo	ReactiveSRLIS(in _srlis_id);
		inline vo	ReactivePFRLIS(in _pfrlis_id);
		inline vo	ReactiveINDFRLIS_MD(in _indfrlis_id);		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------   
		//métodos de diferenciación global de estructuras.
		inline vo	GlobalDifferentiationINIS_MD();
		inline vo	GlobalDifferentiationINDFRLIS_MD();
		inline vo	GlobalDifferentiationINPRRLIS_MD();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos de diferenciación local para estructuras.
		inline vo	LocalDifferentiationINIS_MD();
		inline vo	LocalDifferentiationINDFRLIS_MD();
		inline vo	LocalDifferentiationINPRRLIS_MD();

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//métodos para conocer si exite flujo continuo de congruencias en estructuras candidatas.
		inline in	ContinuousFlowOfCongruencesINIS_MD(in _inis_id);	
		inline in	ContinuousFlowOfCongruencesINDFRLIS_MD(in _indfrlis_id);
		inline in	ContinuousFlowOfCongruencesINPRRLIS_MD(in _inprrlis_id);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos para limpiar buffers de candidatos.	
		inline vo	CleanBuffersOfPreviousCandidatesINIS_MD();	
		inline vo	CleanBuffersOfPreviousCandidatesINDFRLIS_MD();
		inline vo	CleanBuffersOfPreviousCandidatesINPRRLIS_MD();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para limpiar niveles de actividad de IS.
		inline vo	CleanActivityLevelIS();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método thread para actualizar niveles de actividad de IS.
		inline vo	UpdateActivityLevelIS();
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos thread para actualizar buffer tras crear estructuras de información.
		inline vo	UpdateBuffersAfterCreatingINIS_MD(in _inis_id, dou _al_srg);
		inline vo	UpdateBuffersAfterCreatingSRLIS(in _srlis_id);
		inline vo	UpdateBuffersAfterCreatingPFRLIS(in _pfrlis_id);
		inline vo	UpdateBuffersAfterCreatingINDFRLIS_MD(in _indfrlis_id);
		inline vo	UpdateBuffersAfterCreatingINPRRLIS_MD(in _inprrlis_id);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos thread para actualizar buffer tras eliminar estructuras de información.
		inline vo	UpdateBuffersToDeleteINIS_MD(in _inis_id);
		inline vo	UpdateBuffersToDeleteSRLIS(in _srlis_id);
		inline vo	UpdateBuffersToDeletePFRLIS(in _pfrlis_id);
		inline vo	UpdateBuffersToDeleteINDFRLIS_MD(in _indfrlis_id);
		inline vo	UpdateBuffersToDeleteINPRRLIS_MD(in _inprrlis_id);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos para actualizar estados de congruencia de estructuras, de estado 
		//no congruente a estado congruente.
		inline vo	UpdateToCongruentBUFF_INIS_MD();		
		inline vo	UpdateToCongruentBUFF_INDFRLIS_MD();
		inline vo	UpdateToCongruentBUFF_INPRRLIS_MD();
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos para actualizar estados de congruencia de estructuras de estado 
		//congruente a estado no congruente.
		inline vo   UpdateToNotCongruentBUFF_INIS_MD();	
		inline vo   UpdateToNotCongruentBUFF_INDFRLIS_MD();
		inline vo   UpdateToNotCongruentBUFF_INPRRLIS_MD();
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para calcular el nivel de actividad.
		inline dou	ActivityLevelFunction(dou _seed);
		inline dou	ActivityLevelFunction(in _seed);
		
		//----------------------------------------------------------------------------- 
		//----------------------------------------------------------------------------- 
		//métodos para obtener estados de las banderas.
		inline in	GetSTORAGE_FLAG();				
		in			GetKERNEL_INTEGRATION_FLAG();					
		in			GetTHREAD_INTEGRATION_FLAG();																		
		inline in	GetTHREAD_INTEGRATION_LATENCY_FLAG();																	
		inline in	GetTHREAD_INTEGRATION_FINISHED_FLAG();			
		inline in	GetNEW_INPUT_FLAG();		
		inline in	GetNEW_INPUT_DIFFERENCE_RELATION_FLAG();
		inline in	GetINIS_MD_CONGRUENCE_ACCOMPLISHED();
		inline in	GetINDFRLIS_MD_CONGRUENCE_ACCOMPLISHED();
		inline in	GetINPRRLIS_MD_CONGRUENCE_ACCOMPLISHED();
		inline in	GetCLOSE_ACTIVE_THREADS_FLAG();
		inline in	GetPAUSE_ACTIVE_THREADS_FLAG();
		inline in	GetPRINT_FLAG();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para obtener cantidad de upci en el grupo.
		inline in	GetAmountUpcGro();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para obtener tipo de evaluación de transiciones de entradas.		
		inline in	GetInputTransitionEvaluationTypeIn(dou _input_evaluation, dou _input_evaluation_difference);
		inline st	GetInputTransitionEvaluationTypeSt(dou _input_evaluation, dou _input_evaluation_difference);

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//métodos para obtener el estado del nivel de actividad de las estructura activadas.
		inline in	GetCurrentActivityStatus_INIS_MD();
		inline in	GetPastActivityStatus_INIS_MD();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para obtener el máximo nivel de actividad.
		inline dou	GetMaxActivityLevel();		

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//métodos para checkear estructuras en estado de suspensión.
		inline in	CheckSUSPENDED_STRUCTURES();
		inline in	CheckSUSPENDED_INIS_MD();
		inline in	CheckSUSPENDED_INDFRLIS_MD();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos para obtener el contador de la upci.
		inline in	GetKERNEL_ITERATION_COUNTER();
		inline in	GetTHREAD_ITERATION_COUNTER();
		inline in	GetGLOBAL_DIFFERENTIATION_COUNTER();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos Sets de banderas.
		inline vo	SetSTORAGE_FLAG(in _status);	
		inline vo	SetKERNEL_INTEGRATION_FLAG(in _status);						
		inline vo	SetTHREAD_INTEGRATION_FLAG(in _status);																
		inline vo	SetTHREAD_INTEGRATION_LATENCY_FLAG(in _status);															
		inline vo	SetTHREAD_INTEGRATION_FINISHED_FLAG(in _status);															
		inline vo	SetNEW_INPUT_FLAG(in _status);				
		inline vo	SetNEW_INPUT_DIFFERENCE_RELATION_FLAG(in _status);
		inline in	SetINIS_MD_CONGRUENCE_ACCOMPLISHED(in _status);
		inline in	SetINDFRLIS_MD_CONGRUENCE_ACCOMPLISHED(in _status);
		inline in	SetINPRRLIS_MD_CONGRUENCE_ACCOMPLISHED(in _status);
		inline vo	SetCLOSE_ACTIVE_THREADS_FLAG(in _status);
		vo			SetPAUSE_ACTIVE_THREADS_FLAG(in _status);
		vo			SetPRINT_FLAG(in _status);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos para setear buffers de estructuras.
		inline vo	SetBUFF_INIS_MD_MAX_EVAL(in _inis_id, dou _max_evaluation);
		inline vo	SetBUFF_INIS_MD_MAX_AL(in _str_id, dou _max_activity_level);
		inline vo	SetBUFF_STR_MAX_RS(in _str_id, in _str_type, in _max_activity_counter);
		inline vo	SetBUFF_INIS_MD_CRE(in _inis_id);
		inline vo	SetBUFF_PFRLIS_CRE(in _pfrlis_id);
		inline vo	SetBUFF_INDFRLIS_MD_CRE(in _indfrlis_id);
		inline vo	SetBUFF_INPRRLIS_MD_CRE(in _inprrlis_id);
		inline vo	SetBUFF_INIS_MD_ACTIVATED(in _inis_id);
		inline vo	SetBUFF_STR_SUS(in _str_id, in _str_type);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//------------------------- métodos auxiliares --------------------------------

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método debug y print.
		inline vo	Print(st _message);
		inline vo	Print(st _message, dou _data);
		inline vo	Print(st _message, st _data);
	};
}