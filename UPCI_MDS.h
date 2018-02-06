#pragma once
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
	Nombre Clase : 	  UPCI_I_DS (Unidad de procesos Cognitivos Integradora Limitada tipo 'DS'). 
	Date	     :	  12:58 pm 12-06-2017.
	Dise�ador    :	  Gustavo Catal�n Ulloa.
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
#include <math.h>
#include <time.h>
#include "DEFINITIONS.h"
#include "UPCI_SDS_ARG.h"
#include "BUFF_STR_II.h"
#include "BUFF_STR_IIT.h"
#include "BUFF_STR_IIE.h"
#include "INIS.h"
#include "ACIS.h"
#include "PFRLIS.h"
#include "INDFRLIS.h"
#include "INPRRLIS.h"

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
typedef		vector<int>						vein;
typedef		deque<string>					dest;
typedef		deque<deque<int>>				dedein;
typedef		deque<deque<deque<int>>>		dededein;
typedef		deque<BUFF_STR_II>				deBUFF_STR_II;
typedef		deque<BUFF_STR_IIE>				deBUFF_STR_IIE;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//nombre de espacio UPC.
namespace UPC
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//clase: Unidad de procesos Cognitivos Integradora B�sica tipo 'DS'.
	class UPCI_I_DS
	{
		//elementos p�blicos.
	public:

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################ PAR�METROS ################################# 
		
		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//par�metros estructurales.
		in						*GUPCI_ID;													//puntero a id de la gupci.
		in						UPCI_ID;													//id de la upci.
		in						UPCI_NAT;													//naturaleza de la unidad ('a','b','c'...'z').	
		in						INIS_AMOUNT_ALLOWED;										//cantidad de estructuras INIS permitidas.
		in						ACIS_AMOUNT_ALLOWED;										//cantidad de estructuras ACIS permitidas.
		in						RLIS_AMOUNT_ALLOWED;										//cantidad de estructuras de relaciones permitidas por tipo.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//par�metros de actividad.
		dou						DEFAULT_ACTIVITY_LEVEL;										//nivel de actividad por defecto.
		dou						MAX_ACTIVITY_LEVEL_ALLOWED;									//nivel de actividad m�ximo permitido.
		dou						MIN_ACTIVITY_LEVEL_ALLOWED;									//nivel de actividad m�nimo permitido.	

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------    
		//umbrales.
		dou						KERNEL_RAW_INPUT_THRESHOLD;									//umbral de entrada cruda para control del n�cleo.
		dou						DIF_RAW_INPUT_THRESHOLD;									//umbral de entrada cruda para focalizaci�n de la atenci�n (%).
		dou						STR_CONGRUENCE_SR_THRESHOLD;								//umbral de congruencia de registros unidimensionales (%).	
		dou						PFRLIS_STRENGTH_THRESHOLD;									//umbral de fortaleza de relaci�n PFRLIS para eliminar relaci�n por N.A.
		dou						INDFRLIS_STRENGTH_THRESHOLD;								//umbral de fortaleza de relaci�n INDFRLIS para eliminar relaci�n por N.A.
		dou						EVALUATION_THRESHOLD;										//umbral para evaluaciones.	
		dou						TRANSITION_EVALUATION_THRESHOLD;							//umbral para transiciones de evaluaciones.	

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
		//punteros a banderas para funcionalidades.
		in						*SUSPENDED_ACTIONS_MAXIMIZATION_FLAG;						//puntero a bandera para utilizar reactivaci�n acci�n suspendida con m�xima asociaci�n positiva.
		in						*STRUCTURES_RECOGNITION_FLAG;								//puntero a bandrea para utilizar reconocimiento de estructuras.
		in						*STRUCTURES_PROJECTIONS_FLAG;								//puntero a bandera para utilizar proyecci�n de estructuras.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//bandera del kernel.
		in						KERNEL_INTEGRATION_FLAG;									//bandera del estado de integraci�n del kernel (ON: integrando, OFF: libre).
		in						KERNEL_CONTROL_INTEGRATION_FLAG;							//bandera del estado de integraci�n del control del kernel (ON: integrando, OFF: no controlando).
		in						KERNEL_CONTROL_INTEGRATION_FINISHED_FLAG;					//bandera de aviso del t�rmino de la integraci�n del control del kernel.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//banderas del integrador de Hilos.
		in						THREAD_INTEGRATION_FLAG;									//bandera del estado de integraci�n del Hilo (ON: integrando, OFF: libre).
		in						THREAD_INTEGRATION_LATENCY_FLAG;							//bandera del estado de latencia de la integraci�n del Hilo.
		in						THREAD_INTEGRATION_FINISHED_FLAG;							//bandera de aviso del t�rmino de la integraci�n del Hilo.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//bandera de la existencia de estructuras en estado de suspensi�n.
		in						SUSPENDED_STRUCTURES_FLAG;									

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//banderas para estructuras creadas.
		in						NEW_INPUT_FLAG;												//bandera de alerta de una nueva entrada.
		in						NEW_INPUT_DIFFERENCE_RELATION_FLAG;							//bandera de alerta de la creaci�n de una nueva relaci�n de diferencia de entradas.

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
		//tiempos para threads de limpieza y actualizaci�n.
		in						TIMEOUT_CLEAN_IS;											//tiempo de espera de limpieza de IS (ms).	
		in						TIMEOUT_UPDATE_AL_IS;										//tiempo de espera para actualizar niveles de actividad en IS (ms).

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################# BUFFERS ################################### 

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//puntero a buffers del grupo de upci.
		deque<UPCI_I_DS>			*BUFF_UPCI_I_DS;	

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------  
		//puntero a buffer para el id de la upci que puede almacenar estructuras.
		in						*BUFF_UPCI_ID_STORAGE_FLAG_ACT;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para las estructuras de informaci�n.
		INIS					*BUFF_INIS;												//buffer para estructuras de entrada.
		ACIS					*BUFF_ACIS;												//buffer para estructuras de acci�n.
		PFRLIS					*BUFF_PFRLIS;												//buffer para estructuras de relaci�n de flujo puro.
		INDFRLIS				*BUFF_INDFRLIS;												//buffer para estructuras de relaci�n de flujo diferencial de entradas.	
		INPRRLIS				*BUFF_INPRRLIS;												//buffer para estructuras de relaci�n de flujo diferencial de entradas.	
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para almacenar registros.
		dou						*BUFF_IN_RG;												//puntero a buffer para registro de entrada.
		dou						*BUFF_EV_RG;												//puntero a buffer para registro de evaluaci�n de entrada.
		st						*BUFF_AC_RG;												//puntero a buffer para registro de acci�n.
		dou						*BUFF_IN_DIF_RG;											//puntero a buffer para registro de diferencia de entradas.
		dou						*BUFF_IN_PRO_RG;											//puntero a buffer para registro de proporci�n de diferencia de entradas.
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para acciones.
		dest					*BUFF_SET_OF_SUPPORTED_ACTIONS;								//puntero a buffer para el conjunto de acciones soportadas.	
		in						*BUFF_SUPPORTED_ACTIONS_AMOUNT;								//puntero a buffer para la cantidad de acciones soportadas.		

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//punteros a buffers para estructura con evaluaci�n m�xima.
		BUFF_STR_II				*BUFF_STR_MAX_EVAL;											//puntero a buffer para la estructura INIS con m�xima evaluaci�n.
		dou						*BUFF_MAX_EVALUATION;										//puntero a buffer para la m�xima evaluaci�n.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//punteros a buffers para estructura con nivel de actividad m�ximo.
		BUFF_STR_IIT			*BUFF_STR_MAX_AL;											//puntero a buffer para la estructura con nivel de actividad m�ximo.
		dou						*BUFF_MAX_ACTIVITY_LEVEL;									//puntero a buffer para el m�ximo nivel de actividad.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//punteros a buffers para estructura con fortaleza de la relaci�n m�ximo.
		BUFF_STR_IIT			*BUFF_STR_MAX_RS;											//puntero a buffer para la estructura con fortaleza de la relaci�n m�ximo.
		dou						*BUFF_MAX_RELATION_STRENGTH;								//puntero a buffer para el m�ximo fortaleza de la relaci�n.		

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//puntero a buffer para las estructuras de acci�n ejecutadas.
		BUFF_STR_II				*BUFF_EXECUTE_ACIS;			

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para los id de las estructuras disponibles.
		in						BUFF_INIS_ID_AV[2];										//buffer para id de INIS disponible.
		in						BUFF_ACIS_ID_AV[2];										//buffer para id de ACIS disponible.
		in						BUFF_PFRLIS_ID_AV[2];										//buffer para id de PFRLIS disponible.	
		in						BUFF_INDFRLIS_ID_AV[2];										//buffer para id de INDFRLIS disponible.
		in						BUFF_INPRRLIS_ID_AV[2];										//buffer para id de INPRRLIS disponible.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para las estructuras creadas.
		BUFF_STR_II				*BUFF_INIS_CRE;											//puntero a buffer para estructuras INIS creadas.
		BUFF_STR_II				*BUFF_ACIS_CRE;											//puntero a buffer para estructuras ACIS creadas.
		BUFF_STR_II				*BUFF_PFRLIS_CRE;											//puntero a buffer para estructuras PFRLIS creadas.
		BUFF_STR_II				*BUFF_INDFRLIS_CRE;											//puntero a buffer para estructuras INDFRLIS creadas.
		BUFF_STR_II				*BUFF_INPRRLIS_CRE;											//puntero a buffer para estructuras INPRRLIS creadas.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//punteros a buffers para las estructuras activadas.
		BUFF_STR_IIT			*BUFF_STR_ACTIVATED;										//puntero a buffer para las estructuras activadas.
		BUFF_STR_II				*BUFF_INIS_ACTIVATED;										//puntero a buffer para las estructuras INIS activadas.
		BUFF_STR_II				*BUFF_ACIS_ACTIVATED;										//puntero a buffer para las estructuras ACIS activadas.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para las estructuras en estado de suspensi�n.		
		deBUFF_STR_II			*BUFF_INIS_SUS;											//puntero a buffer para las estructuras INIS suspendidas.
		deBUFF_STR_II			*BUFF_ACIS_SUS;											//puntero a buffer para las estructuras ACIS suspendidas.
		deBUFF_STR_II			*BUFF_PFRLIS_SUS;											//puntero a buffer para las estructuras PFRLIS suspendidas.
		deBUFF_STR_II			*BUFF_INDFRLIS_SUS;											//puntero a buffer para las estructuras INDFRLIS suspendidas.	

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para los id de las upci candidatas. 
		//[a][b]: a: tiempo, b: upci.
		dedein					*BUFF_UPCI_ID_INIS_CAN;									//puntero a buffer de id de las upci candidatas para INIS.
		dedein					*BUFF_UPCI_ID_ACIS_CAN;									//puntero a buffer de id de las upci candidatas para ACIS.
		dedein					*BUFF_UPCI_ID_INDFRLIS_CAN;									//puntero a buffer de id de las upci candidatas para INDFRLIS.
		dedein					*BUFF_UPCI_ID_INPRRLIS_CAN;									//puntero a buffer de id de las upci candidatas para INPRRLIS.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffer de estructuras candidatas. 
		//[a][b][c]: a: tiempo, b: upci, c: buffer de estructura.
		dededein				*BUFF_INIS_ID_CAN;										//puntero a buffer de ids de estructuras tipo INIS candidatas.
		dededein				*BUFF_ACIS_ID_CAN;										//puntero a buffer de ids de estructuras tipo ACIS candidatas.
		dededein				*BUFF_INDFRLIS_ID_CAN;										//puntero a buffer de ids de estructuras tipo INDFRLIS candidatas.
		dededein				*BUFF_INPRRLIS_ID_CAN;										//puntero a buffer de ids de estructuras tipo INPRRLIS candidatas.	

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//puntero a buffer para �ndice de la relaci�n utilizada en flujo por reconocimiento.
		in						*BUFF_RL_INDEX_USED_IN_RECOGNITION;

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//punteros a buffers para las estructuras reconocidas.
		BUFF_STR_II				*BUFF_INIS_RE;											//puntero a buffer para estructura reconocida INIS.
		BUFF_STR_II				*BUFF_ACIS_RE;											//puntero a buffer para estructura reconocida ACIS.
		BUFF_STR_II				*BUFF_INDFRLIS_RE;											//puntero a buffer para estructura reconocida INDFRLIS.
		BUFF_STR_II				*BUFF_INPRRLIS_RE;											//puntero a buffer para estructura reconocida INPRRLIS.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para los m�ximos ids.
		in						BUFF_INIS_MAX_ID[2];										//buffer para m�ximos ids en estructuras INIS.
		in						BUFF_ACIS_MAX_ID[2];										//buffer para m�ximos ids en estructuras ACIS.
		in						BUFF_PFRLIS_MAX_ID[2];										//buffer para m�ximos ids en estructuras PFRLIS.
		in						BUFF_INDFRLIS_MAX_ID[2];									//buffer para m�ximos ids en estructuras INDFRLIS.
		in						BUFF_INPRRLIS_MAX_ID[2];									//buffer para m�ximos ids en estructuras INPRRLIS.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para la cantidad de estructuras inicializadas.
		in						BUFF_INIS_INI_AMOUNT;										//buffer para la cantidad de INIS inicializadas.
		in						BUFF_ACIS_INI_AMOUNT;										//buffer para la cantidad de ACIS inicializadas.
		in						BUFF_PFRLIS_INI_AMOUNT;										//buffer para la cantidad de PFRLIS inicializadas.
		in						BUFF_INDFRLIS_INI_AMOUNT;									//buffer para la cantidad de INDFRLIS inicializadas.
		in						BUFF_INPRRLIS_INI_AMOUNT;									//buffer para la cantidad de INPRRLIS inicializadas.
		in						BUFF_TOTAL_STR_INI_AMOUNT;									//buffer para la cantidad total de IS inicializadas.									

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//buffers auxiliares.
		BUFF_STR_II				BUFF_STR_SUS_AUX;											//buffer auxiliar para estructuras en suspensi�n.
		dest					BUFF_ACTION_REGISTERS_TO_DISCRIMINATE;						//buffer para registros de acciones a discriminar.

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
		//########################## VARIABLES AUXILIARES ############################# 

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//semilla para generaci�n n�meros pseudo aleatorios.
		in						SEED;

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################ THREADS #################################### 

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//threads para procesamiento.												
		thread					TH_THREAD_INTEGRATION;										//thread para integraci�n de entradas de la upci.
		thread					TH_KERNEL_ACTION_CONTROL;									//thread para acci�n de control por parte del kernel.
		thread					TH_CLEAN_STR_BUFFERS;										//thread para limpieza de buffers de IS.
		thread					TH_UPDATE_AL_STR_BUFFERS;									//thread para actualizar niveles de actividad de buffers de IS.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//mutex para escritura.
		std::mutex				RED_LIGHT_MUTEX;					

	//m�todos p�blicos.
	public:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos constructor.
		UPCI_I_DS();
		UPCI_I_DS(in _id, in _nat, in _storage_flag, in _seed, UPCI_SDS_ARG &_upci_i_ds_arg);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos destructor.
		~UPCI_I_DS();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos de inicializaci�n.
		in			Initialize(in _nat, UPCI_SDS_ARG &_upci_i_ds_arg);
		in			Initialize(in _id, in _nat, in _storage_flag, in _seed, UPCI_SDS_ARG &_upci_i_ds_arg);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para Clean upci.
		inline in	Clean();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos kernel.
		vo			KernelInput(dou _input, dou _input_evaluation, st *_output_action);
		vo			KernelActionControl(dou _input, st *_output_action);

		//-----------------------------------------------------------------------------  
		//-----------------------------------------------------------------------------
		//m�todo de entrada para la integraci�n de Hilos.	
		vo			ThreadIntegrationInput(dou _input_evaluation, st *_output_action);
		
		//----------------------------------------------------------------------------- 
		//----------------------------------------------------------------------------- 
		//m�todos para la integraci�n de Hilos mediante evaluaciones.
		inline vo	InputEvaluationIntegration(st *_output_action);
		inline vo	InputTransitionEvaluationIntegration(st *_output_action);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para integrar transiciones de evaluaci�n de entradas.		
		inline vo	PositiveTransitionIntegration(st *_output_action);
		inline vo	NegativeTransitionIntegration(st *_output_action);
		inline vo	NeutralNegativeTransitionIntegration(st *_output_action);		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para integrar registro de acci�n creado.
		inline vo	ActionRegisterIntegration(st _action_register, st *_output_action);

		//-----------------------------------------------------------------------------  
		//-----------------------------------------------------------------------------   
		//m�todos para la integraci�n de Hilos reconocidos.	
		inline vo	RecognizedThreadIntegrationINIS(st *_output_action);
		inline vo	RecognizedThreadIntegrationACIS(st *_output_action);

		//-----------------------------------------------------------------------------  
		//-----------------------------------------------------------------------------   
		//m�todos para obtener acciones potenciales.
		inline vo	GetPotentialActionsINIS(in _inis_id, in _rl_index_to_use, BUFF_STR_IIE *_potential_action);
		inline vo	GetPotentialActionsACIS(in _lacis_id, in _rl_index_to_use, BUFF_STR_IIE *_potential_action);
		inline vo	GetPotentialActionsPFRLIS(in _pfrlis_id, BUFF_STR_IIE *_potential_action);
		inline vo	GetPotentialActionsINDFRLIS(in _indfrlis_id, BUFF_STR_IIE *_potential_action);

		//-----------------------------------------------------------------------------  
		//-----------------------------------------------------------------------------
		//m�todo para obtener id de la acci�n ganadora.
		inline in	GetWinningPotentialActionIndex(dou _input_evaluation, deBUFF_STR_IIE &_potential_thread);
		
		//-----------------------------------------------------------------------------  
		//-----------------------------------------------------------------------------
		//m�todos para obtener el Hilo reconocido por expansi�n de flujo directo.
		//inline vo	GetPotentialThreadsINIS(in _inis_id, in _rl_index_to_use, deBUFF_STR_IITE *_potential_thread);
		//inline vo	GetPotentialThreadsACIS(in _lacis_id, in _rl_index_to_use, deBUFF_STR_IITE *_potential_thread);
		//inline vo	GetPotentialThreadsPFRLIS(in _pfrlis, deBUFF_STR_IITE *_potential_thread);
		//inline vo	GetPotentialThreadsINDFRLIS(in _indfrlis_id, deBUFF_STR_IITE *_potential_thread);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para integrar Hilo ganador.
		//inline vo	winningThreadIntegration(deBUFF_STR_IITE *_winning_thread, dou _input_evaluation, st *_output_action);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para estructuras de acci�n.		
		inline vo	GetCausalAction(in _inis_id, in & _causal_lacis_id, in &_upci_id_causal_lacis);				
		inline vo	GetWinningSuspendedAction(in & _winning_sus_lacis_id, in &_upci_id_winning_sus_lacis);
		inline dou	GetActionEvaluation(in _lacis_id);
		inline st	CreateActionRegister();
		inline in	CheckDiscrimination(st _action_register);
		inline vo	ExecuteActionRegister(in _lacis_id, st *_output_action);

		//----------------------------------------------------------------------------- 
		//----------------------------------------------------------------------------- 
		//m�todos para crear estructuras.
		inline vo	CreateINIS(dou _input, dou _input_evaluation);
		inline vo	CreateACIS(st _ac_rg);
		inline vo	CreatePFRLIS(in _str1_type, in _str2_type, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2);
		inline vo	CreateINDFRLIS(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2);
		inline vo	CreateINPRRLIS(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2);
 
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para Delete estructuras.
		inline vo	DeleteINIS(in _inis_id);																	
		inline vo	DeleteACIS(in _lacis_id);																	
		inline vo	DeletePFRLIS(in _pfrlis_id);	
		inline vo	DeleteINDFRLIS(in _indfrlis_id);
		inline vo	DeleteINPRRLIS(in _inprrlis_id);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para Delete estructuras con excepci�n a una estructura.
		inline vo	DeletePFRLIS(in _pfrlis_id, in _str_type, in _str_id, in _upci_id_str);
		inline vo	DeleteINDFRLIS(in _indfrlis_id, in _str_id, in _upci_id_str);
		inline vo	DeleteINPRRLIS(in _indfrlis_id, in _str_id, in _upci_id_str);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo thread para limpiar buffers de IS.
		inline vo	CleanISBuffers();														

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para limpiar buffers de IS.
		inline vo	CleanPFRLIS();
		inline vo	CleanINDFRLIS();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para relacionar estructuras.
		inline vo	RelateINIS_CR(in _inis_id);
		inline vo	RelateINIS_F(in _inis_id);
		inline vo	RelateACIS(in _lacis_id);
		inline vo	RelateINDFRLIS(in _indfrlis_id);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para chekear la no repetici�n de relaciones contiguas.
		inline in	CheckPreviousPFRLIS(in _str1_type, in _str2_type, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2);
		inline in	CheckPreviousINDFRLIS(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2);
		inline in	CheckPreviousINPRRLIS(in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2);

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//m�todo para reactivar estructuras de informaci�n.
		inline vo	ReactiveINIS(in _inis_id);
		inline vo	ReactiveACIS(in _lacis_id);
		inline vo	ReactivePFRLIS(in _pfrlis_id);
		inline vo	ReactiveINDFRLIS(in _indfrlis_id);		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------   
		//m�todos de diferenciaci�n global de estructuras.
		inline vo	GlobalDifferentiationINIS();
		inline vo	GlobalDifferentiationACIS();
		inline vo	GlobalDifferentiationINDFRLIS();
		inline vo	GlobalDifferentiationINPRRLIS();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos de diferenciaci�n local para estructuras.
		inline vo	LocalDifferentiationINIS();
		inline vo	LocalDifferentiationACIS();
		inline vo	LocalDifferentiationINDFRLIS();
		inline vo	LocalDifferentiationINPRRLIS();

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//m�todos para conocer si exite flujo continuo de congruencias en estructuras candidatas.
		inline in	ContinuousFlowOfCongruencesINIS(in _inis_id);															
		inline in	ContinuousFlowOfCongruencesACIS(in _lacis_id);
		inline in	ContinuousFlowOfCongruencesINDFRLIS(in _indfrlis_id);
		inline in	ContinuousFlowOfCongruencesINPRRLIS(in _inprrlis_id);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para limpiar buffers de candidatos.	
		inline vo	CleanBuffersOfPreviousCandidatesINIS();																	
		inline vo	CleanBuffersOfPreviousCandidatesACIS();	
		inline vo	CleanBuffersOfPreviousCandidatesINDFRLIS();
		inline vo	CleanBuffersOfPreviousCandidatesINPRRLIS();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para limpiar niveles de actividad de IS.
		inline vo	CleanActivityLevelIS();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo thread para actualizar niveles de actividad de IS.
		inline vo	UpdateActivityLevelIS();
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos thread para actualizar buffer tras crear estructuras de informaci�n.
		inline vo	UpdateBuffersAfterCreatingINIS(in _inis_id, dou _input_evaluation, dou _al_srg);
		inline vo	UpdateBuffersAfterCreatingACIS(in _lacis_id, dou _al_srg);
		inline vo	UpdateBuffersAfterCreatingPFRLIS(in _pfrlis_id);
		inline vo	UpdateBuffersAfterCreatingINDFRLIS(in _indfrlis_id);
		inline vo	UpdateBuffersAfterCreatingINPRRLIS(in _inprrlis_id);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos thread para actualizar buffer tras eliminar estructuras de informaci�n.
		inline vo	UpdateBuffersToDeleteINIS(in _inis_id);
		inline vo	UpdateBuffersToDeleteACIS(in _lacis_id);
		inline vo	UpdateBuffersToDeletePFRLIS(in _pfrlis_id);
		inline vo	UpdateBuffersToDeleteINDFRLIS(in _indfrlis_id);
		inline vo	UpdateBuffersToDeleteINPRRLIS(in _inprrlis_id);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para actualizar estados de congruencia de estructuras, de estado 
		//no congruente a estado congruente.
		inline vo	UpdateToCongruentBUFF_INIS();															
		inline vo	UpdateToCongruentBUFF_ACIS();	
		inline vo	UpdateToCongruentBUFF_INDFRLIS();
		inline vo	UpdateToCongruentBUFF_INPRRLIS();
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para actualizar estados de congruencia de estructuras de estado 
		//congruente a estado no congruente.
		inline vo   UpdateToNotCongruentBUFF_INIS();															
		inline vo   UpdateToNotCongruentBUFF_ACIS();	
		inline vo   UpdateToNotCongruentBUFF_INDFRLIS();
		inline vo   UpdateToNotCongruentBUFF_INPRRLIS();
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para calcular el nivel de actividad.
		inline dou	ActivityLevelFunction(dou _seed);
		inline dou	ActivityLevelFunction(in _seed);
		
		//----------------------------------------------------------------------------- 
		//----------------------------------------------------------------------------- 
		//m�todos para obtener estados de las banderas.
		inline in	GetSTORAGE_FLAG();				
		in			GetSUSPENDED_ACTIONS_MAXIMIZATION_FLAG();
		in			GetSTRUCTURES_RECOGNITION_FLAG();
		in			GetSTRUCTURES_PROJECTIONS_FLAG();
		in			GetKERNEL_INTEGRATION_FLAG();																		
		inline in	GetKERNEL_CONTROL_INTEGRATION_FLAG();
		inline in	GetKERNEL_CONTROL_INTEGRATION_FINISHED_FLAG();
		in			GetTHREAD_INTEGRATION_FLAG();																		
		inline in	GetTHREAD_INTEGRATION_LATENCY_FLAG();																	
		inline in	GetTHREAD_INTEGRATION_FINISHED_FLAG();																	
		inline in	CheckSUSPENDED_STRUCTURES();																		
		inline in	GetNEW_INPUT_FLAG();		
		inline in	GetNEW_INPUT_DIFFERENCE_RELATION_FLAG();
		inline in	GetCLOSE_ACTIVE_THREADS_FLAG();
		inline in	GetPAUSE_ACTIVE_THREADS_FLAG();
		inline in	GetPRINT_FLAG();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para obtener cantidad de upci en el grupo.
		inline in	GetAmountUpcGro();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para obtener tipo de evaluaci�n de transiciones de entradas.		
		inline in	GetInputTransitionEvaluationTypeIn(dou _input_evaluation, dou _input_evaluation_difference);	
		inline st	GetInputTransitionEvaluationTypeSt(dou _input_evaluation, dou _input_evaluation_difference);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para obtener acci�n inversa de una acci�n.
		inline st	GetInverseAction(st _action_register);

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//m�todos para obtener el estado de las estructura activadas, para su uso.
		inline in	GetCurrentStrActiveStatus();
		inline in	GetPastStrActiveStatus();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para obtener el m�ximo nivel de actividad.
		inline dou	GetMaxActivityLevel();		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para obtener el contador de la upci.
		inline in	GetKERNEL_ITERATION_COUNTER();
		inline in	GetTHREAD_ITERATION_COUNTER();
		inline in	GetGLOBAL_DIFFERENTIATION_COUNTER();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos Sets de banderas.
		inline vo	SetSTORAGE_FLAG(in _status);	
		vo			SetSUSPENDED_ACTIONS_MAXIMIZATION_FLAG(in _status);
		vo			SetSTRUCTURES_RECOGNITION_FLAG(in _status);
		vo			SetSTRUCTURES_PROJECTIONS_FLAG(in _status);
		inline vo	SetKERNEL_INTEGRATION_FLAG(in _status);														
		inline vo	SetKERNEL_CONTROL_INTEGRATION_FLAG(in _status);		
		inline vo	SetKERNEL_CONTROL_INTEGRATION_FINISHED_FLAG(in _status);
		inline vo	SetTHREAD_INTEGRATION_FLAG(in _status);																
		inline vo	SetTHREAD_INTEGRATION_LATENCY_FLAG(in _status);															
		inline vo	SetTHREAD_INTEGRATION_FINISHED_FLAG(in _status);														
		inline vo	SetSUSPENDED_STRUCTURES_FLAG(in _status);																
		inline vo	SetNEW_INPUT_FLAG(in _status);				
		inline vo	SetNEW_INPUT_DIFFERENCE_RELATION_FLAG(in _status);
		inline vo	SetCLOSE_ACTIVE_THREADS_FLAG(in _status);
		vo			SetPAUSE_ACTIVE_THREADS_FLAG(in _status);
		vo			SetPRINT_FLAG(in _status);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para setear buffers de estructuras.
		inline vo	SetBUFF_STR_MAX_EVAL(in _inis_id, dou _max_evaluation);
		inline vo	SetBUFF_STR_MAX_AL(in _str_id, in _str_type, dou _max_activity_level);
		inline vo	SetBUFF_STR_MAX_RS(in _str_id, in _str_type, in _max_activity_counter);
		inline vo	SetBUFF_INIS_CRE(in _inis_id);
		inline vo	SetBUFF_ACIS_CRE(in _lacis_id);
		inline vo	SetBUFF_PFRLIS_CRE(in _pfrlis_id);
		inline vo	SetBUFF_INDFRLIS_CRE(in _indfrlis_id);
		inline vo	SetBUFF_INPRRLIS_CRE(in _inprrlis_id);
		inline vo	SetBUFF_STR_ACTIVATED(in _str_id, in _str_type);
		inline vo	SetBUFF_INIS_ACTIVATED(in _inis_id);
		inline vo	SetBUFF_ACIS_ACTIVATED(in _lacis_id);		
		inline vo	SetBUFF_STR_SUS(in _str_id, in _str_type);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//------------------------- m�todos auxiliares --------------------------------

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo debug y Print.
		inline vo	Print(st _message);
		inline vo	Print(st _message, dou _data);
		inline vo	Print(st _message, st _data);
	};
}