#pragma once
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
Class Name	: 	  GUPCI_SDS (Limted Group Units Cognitive Processes, type 'DS'). 
Date	    :	  12:58 pm 12-06-2017.
Author		:	  Gustavo Catalán Ulloa.
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//libraries.
#include "UPCI_I_DS.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//espacio de nombres.
using namespace UPC;
using namespace std;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//types.
typedef 	void						vo;
typedef		bool						bo;
typedef		int							in;
typedef		double						dou;
typedef		stringstream				sst;
typedef		vector<double>				vedou;
typedef		vector<string>				vest;
typedef		deque<int>					dein;
typedef		deque<string>				dest;
typedef		deque<deque<int>>			dedein;
typedef		deque<deque<deque<int>>>	dededein;
typedef		deque<BUFF_STR_II>			deBUFF_STR_II;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//nombre de espacio UPC.
namespace UPC
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------  
	//clase: Grupo de unidad de procesos Cognitivos tipo 'DS'.
	class GUPCI_SDS
	{
		//elementos privados.
	private:
	
		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################ PARÁMETROS ################################# 

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//parámetros de gupci.
		in						GUPCI_ID;													//id de la gupci.
		in						GUPCI_NAT;													//naturaleza de la unidad ('a','b','c'...'z').
		in						UPCI_AMOUNT;												//cantidad de upci.	

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################ BANDERAS ################################### 											

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//banderas para funcionalidades.
		in						SUSPENDED_ACTIONS_MAXIMIZATION_FLAG;						//bandera para utilizar reactivación acción suspendida con máxima asociación positiva.
		in						STRUCTURES_RECOGNITION_FLAG;								//bandrea para utilizar reconocimiento de estructuras.
		in						STRUCTURES_PROJECTIONS_FLAG;								//bandera para utilizar proyección de estructuras.	

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//banderas para threads activos.
		in						CLOSE_ACTIVE_THREADS_FLAG;									//bandera para cerrar threads activos.
		in						PAUSE_ACTIVE_THREADS_FLAG;									//bandera para pausar threads activos.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bandera de almacenamiento de señales.
		in						SET_SIGNAL_FLAG;

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################# BUFFERS ################################### 

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para las upci.									
		deque<UPCI_I_DS>		BUFF_UPCI_I_DS;		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffer para cargar argumentos de las upci.
		UPCI_SDS_ARG			BUFF_UPCI_ARG;	

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffer del id de la upci con bandera de almacenamiento en estado activo.
		in						BUFF_UPCI_ID_STORAGE_FLAG_ACT;
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para almacenar registros.
		dou						BUFF_IN_RG;													//buffer para registro de entrada.
		dou						BUFF_EV_RG;													//buffer para registro de evaluación de entrada.
		st						BUFF_AC_RG;													//buffer para registro de acción.
		dou						BUFF_IN_DIF_RG;												//buffer para registro de diferencia de entradas.
		dou						BUFF_IN_PRO_RG;												//buffer para registro de proporción de diferencia de entradas.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para acciones.
		dest					BUFF_SET_OF_SUPPORTED_ACTIONS;								//buffer para el conjunto de acciones soportadas.
		in						BUFF_SUPPORTED_ACTIONS_AMOUNT;								//buffer para la cantidad de acciones soportadas.		
		
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//buffers para estructura con evaluación máxima.
		BUFF_STR_II				BUFF_STR_MAX_EVAL;											//buffer para la estructura INIS con máxima evaluación.
		dou						BUFF_MAX_EVALUATION;										//buffer para la máxima evaluación.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------   
		//buffers para estructura con nivel de actividad máximo.
		BUFF_STR_IIT			BUFF_STR_MAX_AL;											//buffer para la estructura con nivel de actividad máximo.
		dou						BUFF_MAX_ACTIVITY_LEVEL;									//buffer para el máximo nivel de actividad.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------   
		//buffers para estructura con fortaleza de la relación máximo.
		BUFF_STR_IIT			BUFF_STR_MAX_RS;											//buffer para la estructura con fortaleza de la relación máximo.
		dou						BUFF_MAX_RELATION_STRENGTH;									//buffer para el máximo fortaleza de la relación.	

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para las estructuras activadas.
		BUFF_STR_IIT			BUFF_STR_ACTIVATED[2];										//buffer para las estructuras activadas.
		BUFF_STR_II				BUFF_INIS_ACTIVATED[2];									//buffer para las estructuras INIS activadas.
		BUFF_STR_II				BUFF_ACIS_ACTIVATED[2];									//buffer para las estructuras ACIS activadas.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//buffer para las estructuras de acción ejecutadas.
		BUFF_STR_II				BUFF_EXECUTE_ACIS[2];			

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para las estructuras creadas.
		BUFF_STR_II				BUFF_INIS_CRE[2];											//buffer para estructuras INIS creadas.
		BUFF_STR_II				BUFF_ACIS_CRE[2];											//buffer para estructuras ACIS creadas.
		BUFF_STR_II				BUFF_PFRLIS_CRE[2];											//buffer para estructuras PFRLIS creadas.
		BUFF_STR_II				BUFF_INDFRLIS_CRE[2];										//buffer para estructuras INDFRLIS creadas.
		BUFF_STR_II				BUFF_INPRRLIS_CRE[2];										//buffer para estructuras INPRRLIS creadas.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para las estructuras en estado de suspensión.		
		deBUFF_STR_II			BUFF_INIS_SUS;											//buffer para las estructuras INIS suspendidas.
		deBUFF_STR_II			BUFF_ACIS_SUS;											//buffer para las estructuras ACIS suspendidas.
		deBUFF_STR_II			BUFF_PFRLIS_SUS;											//buffer para las estructuras PFRLIS suspendidas.
		deBUFF_STR_II			BUFF_INDFRLIS_SUS;											//buffer para las estructuras INDFRLIS suspendidas.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para los id de las upci candidatas. 
		//[a][b]: a: tiempo, b: upci.
		dedein					BUFF_UPCI_ID_INIS_CAN;									//buffer de id de las upci candidatas para INIS.
		dedein					BUFF_UPCI_ID_ACIS_CAN;									//buffer de id de las upci candidatas para ACIS.
		dedein					BUFF_UPCI_ID_INDFRLIS_CAN;									//buffer de id de las upci candidatas para INDFRLIS.
		dedein					BUFF_UPCI_ID_INPRRLIS_CAN;									//buffer de id de las upci candidatas para INPRRLIS.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffer de estructuras candidatas. 
		//[a][b][c]: a: tiempo, b: upci, c: buffer de estructura.
		dededein				BUFF_INIS_ID_CAN;											//buffer de ids de estructuras tipo INIS candidatas.
		dededein				BUFF_ACIS_ID_CAN;											//buffer de ids de estructuras tipo ACIS candidatas.
		dededein				BUFF_INDFRLIS_ID_CAN;										//buffer de ids de estructuras tipo INDFRLIS candidatas.
		dededein				BUFF_INPRRLIS_ID_CAN;										//buffer de ids de estructuras tipo INPRRLIS candidatas.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//buffer para índice de la relación utilizada en flujo por reconocimiento.
		in						BUFF_RL_INDEX_USED_IN_RECOGNITION;	

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//buffer de las estructuras reconocidas.
		BUFF_STR_II				BUFF_INIS_RE;												//buffer para estructura reconocida INIS.
		BUFF_STR_II				BUFF_ACIS_RE;												//buffer para estructura reconocida ACIS.
		BUFF_STR_II				BUFF_INDFRLIS_RE;											//buffer para estructura reconocida INDFRLIS.
		BUFF_STR_II				BUFF_INPRRLIS_RE;											//buffer para estructura reconocida INPRRLIS.												

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//############################### CONTADORES ##################################

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//contador de iteraciones de la gupci.
		in						GUPCI_ITERATION_COUNTER;		

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//########################## VARIABLES AUXILIARES ############################# 

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//semilla para generación números pseudo aleatorios.
		in						SEED;

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################ THREADS #################################### 

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//thread de entrada de la gupci.
		thread					THREAD_GUPCI_INPUT;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//mutex para escritura.
		std::mutex				RED_LIGHT_MUTEX;

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################ SEÑALES ####################################

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para señales.
		vedou					INPUT_SIGNAL;												//señal de entrada de la gupci.
		vedou					EVALUATION_SIGNAL;											//señal de evaluación de la gupci.
		vest					OUTPUT_SIGNAL;												//señal de salida de la gupci.			

		//métodos públicos.
	public:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos constructor.
		GUPCI_SDS();
		GUPCI_SDS(in _gupci_id, in _gupci_nat, in _upci_amount, in _set_signal_flag, in _seed, dest &_buff_set_of_supported_actions, UPCI_SDS_ARG &_upci_i_ds_arg);		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos destructor.
		~GUPCI_SDS();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos de inicialización.
		in			Initialize(in _upci_amount, UPCI_SDS_ARG &_upci_i_ds_arg);
		in			Initialize(in _gupci_id, in _gupci_nat, in _upci_amount, in _set_signal_flag, in _seed, dest &_buff_set_of_supported_actions, UPCI_SDS_ARG &_upci_i_ds_arg);
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para Clean rupci.
		in			Clean();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método entrada y salida de datos visible por el usuario.
		vo			input(dou _input, dou _input_evaluation, st *_output_action);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método de entrada de comandos del usuario.
		vo			UserCommand(st _user_command);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos para abrir, guardar, leer y imprimir gupci.
		in			Open(st _fileNameS);
		in			Save(st _fileNameS);
		vo			SaveSignalData(string _fileNameS);
		vo			PrintGUPCI_I_DS(in _upci_id, in _buffers_selection, in _str_id);
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos Get para obtener cantidad de upci.
		in			GetUPCI_AMOUNT();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos Gets para estado de la banderas de la upci activa.
		in			GetKERNEL_INTEGRATION_FLAG();
		in			GetKERNEL_CONTROL_INTEGRATION_FINISHED_FLAG();
		in			GetTHREAD_INTEGRATION_FLAG();
		in			GetTHREAD_INTEGRATION_FINISHED_FLAG();			
		in			GetSET_SIGNAL_FLAG();
		in			GetPAUSE_ACTIVE_THREADS_FLAG();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos Get para obtener contadores de la gupci y de la upci activa.
		in			GetGUPCI_ITERATION_COUNTER();
		in			GetKERNEL_ITERATION_COUNTER();
		in			GetTHREAD_ITERATION_COUNTER();
		in			GetGLOBAL_DIFFERENTIATION_COUNTER();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método Set de banderas.		
		vo			SetSUSPENDED_ACTIONS_MAXIMIZATION_FLAG(in _status);
		vo			SetSTRUCTURES_RECOGNITION_FLAG(in _status);
		vo			SetSTRUCTURES_PROJECTIONS_FLAG(in _status);
		vo			SetCLOSE_ACTIVE_THREADS_FLAG(in _status);
		vo			SetPAUSE_ACTIVE_THREADS_FLAG(in _status);
		vo			SetSET_SIGNAL_FLAG(in _status);

		//métodos privados.
	private:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método entrada y salida de datos no visible por el usuario.
		vo			ThreadInput(dou _input, dou _input_evaluation, st *_output_action);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para setear señales de la gupci.
		inline vo	SetInputData(dou _input, dou _input_evaluation);
		inline vo	SetOutputData(st _action);		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos de imprimir BUFF_DATA.		
		inline vo	PrintBuffBanderas(in _upci_id);											//impresión buffer de banderas.
		inline vo   PrintBuffNucleo(in _upci_id);											//impresión buffer del núcleo.
		inline vo   PrintBuffDirUpc(in _upci_id);											//impresión de las direcciones de las upci conectadas.
		inline vo   PrintBuffEstructurasINIS(in _upci_id, in _str_id);					//impresión buffer de estructuras INIS.
		inline vo   PrintBuffEstructurasACIS(in _upci_id, in _str_id);					//impresión buffer de estructuras ACIS.
		inline vo   PrintBuffEstructurasPFRLIS(in _upci_id, in _str_id);					//impresión buffer de estructuras PFRLIS.
		inline vo   PrintBuffEstructurasINDFRLIS(in _upci_id, in _str_id);					//impresión buffer de estructuras INDFRLIS.
		inline vo   PrintBuffEstructurasINPRRLIS(in _upci_id, in _str_id);					//impresión buffer de estructuras INPRRLIS.
		inline vo   PrintBuffINISCandidatas(in _upci_id);									//impresión buffer de estructuras candidatas de INIS.
		inline vo   PrintBuffACISCandidatas(in _upci_id);									//impresión buffer de estructuras candidatas de ACIS.
		inline vo   PrintBuffINDFRLISCandidatas(in _upci_id);								//impresión buffer de estructuras candidatas de INDFRLIS.
		inline vo   PrintBuffINPRRLISCandidatas(in _upci_id);								//impresión buffer de estructuras candidatas de INPRRLIS.
		inline vo   PrintBuffIdUpcINISCandidatas(in _upci_id);							//impresión buffer de las id de upci con estructuras INIS candidatas.
		inline vo   PrintBuffIdUpcACISCandidatas(in _upci_id);							//impresión buffer de las id de upci con estructuras ACIS candidatas.
		inline vo   PrintBuffIdUpcINDFRLISCandidatas(in _upci_id);							//impresión buffer de las id de upci con estructuras INDFRLIS candidatas.
		inline vo   PrintBuffIdUpcINPRRLISCandidatas(in _upci_id);							//impresión buffer de las id de upci con estructuras INPRRLIS candidatas.
		inline vo   PrintBuffIdEstDisponibles(in _upci_id);									//impresión buffer de id de estructuras disponibles.
		inline vo   PrintBuffIdYTipoEstCreadas(in _upci_id);								//impresión buffer de id de estructuras creadas.
		inline vo   PrintBuffEstReconocidas(in _upci_id);									//impresión buffer de id de estructuras reconocidas.
		inline vo   PrintBuffCantUpciEstSuspension(in _upci_id);							//impresión buffer de cantidades de upci y estructuras en estado de suspensión.
		inline vo   PrintBuffCantEstExistentes(in _upci_id);								//impresión buffer con la cantidades de estructuras existentes.
		inline vo   PrintBuffCantExp(in _upci_id);											//impresión de buffer de cantidad de expansiones.
		inline vo   PrintBuffMaxIdEst(in _upci_id);											//impresión buffer con los máximos id de las estructuras.		
	};
}