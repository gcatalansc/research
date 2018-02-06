#pragma once
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
Class Name	: 	  GUPCI_HL_V (Grupo de unidades de procesos cognitivos integradora de alto 
				  nivel (HL) para visi�n (V)). 
Date	    :	  11:06 pm 17-11-2017.
Author		:	  Gustavo Catal�n Ulloa.
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------	 ## VER SI CREAR CLASE ABSTRACTA PARA LA GUPCI.
//-------------------------------------------------------------------------------------  ## INSERTAR �NDICE EN ESTRUCTURAS DE ENTRADAS: "INIS_MD0", "INDFRLIS_MD0", ETC. CORREGIR BUFFERS PARA REGISTROS : "BUFF_IN_RG_MD0", "BUFF_EV_RG_MD0", "BUFF_IN_DIF_RG_MD0".
//libraries.
#include "UPCI_HL_V.h"

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
typedef		deque<int>					dein;
typedef		deque<deque<int>>			dedein;
typedef		deque<deque<deque<int>>>	dededein;
typedef		deque<BUFF_STR_ITI>			deBUFF_STR_II;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//nombre de espacio UPC.
namespace UPC
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------  
	//clase GUPCI_HL_V.
	class GUPCI_HL_V
	{
		//elementos privados.
	private:
	
		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################ PAR�METROS ################################# 

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//par�metros de gupci.
		in						GUPCI_ID;													//id de la GUPCI.
		in						UPCI_HL_V_AMOUNT;											//cantidad de UPCI_HL_V.	

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################ BANDERAS ################################### 											

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//banderas para threads activos.
		in						CLOSE_ACTIVE_THREADS_FLAG;									//bandera para cerrar threads activos.
		in						PAUSE_ACTIVE_THREADS_FLAG;									//bandera para pausar threads activos.

		//#############################################################################
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//################################# BUFFERS ################################### 

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para las upci.									
		deque<UPCI_HL_V>		BUFF_UPCI_HL_V;		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffer para cargar argumentos de las upci.
		UPCI_HL_V_ARG			BUFF_UPCI_HL_V_ARG;	

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffer del id de la upci con bandera de almacenamiento en estado activo.
		in						BUFF_UPCI_HL_V_ID_STORAGE_FLAG_ACT;
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para registros.
		dou						*BUFF_IN_RG;												//puntero a buffer para registro de entrada.
		dou						*BUFF_EV_RG;												//puntero a buffer para registro de evaluaci�n de entrada.
		dou						BUFF_IN_DIF_RG;												//buffer para registro de diferencia de entradas.
		dou						BUFF_IN_PRO_RG;												//buffer para registro de proporci�n de diferencia de entradas.
		dou						*BUFF_OUTPUT_PROJECTION;									//puntero a buffer para registro de proyecci�n de salida.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//buffers para estructura INIS_MD con evaluaci�n m�xima.
		BUFF_STR_ITI			BUFF_INIS_MD_MAX_EVAL;										//buffer para la estructura INIS_MD con m�xima evaluaci�n.
		dou						BUFF_MAX_EVALUATION;										//buffer para la m�xima evaluaci�n.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------   
		//buffers para estructura INIS_MD con nivel de actividad m�ximo.
		BUFF_STR_ITI			BUFF_INIS_MD_MAX_AL;										//buffer para la estructura INIS_MD con nivel de actividad m�ximo.
		dou						BUFF_MAX_ACTIVITY_LEVEL;									//buffer para el m�ximo nivel de actividad.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------   
		//buffers para estructura con fortaleza de la relaci�n m�ximo.
		BUFF_STR_ITIT			BUFF_STR_MAX_RS;											//buffer para la estructura con fortaleza de la relaci�n m�ximo.
		dou						BUFF_MAX_RELATION_STRENGTH;									//buffer para el m�ximo fortaleza de la relaci�n.	

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffer para las estructuras INIS_MD activadas.
		BUFF_STR_ITI			BUFF_INIS_MD_ACTIVATED[2];										

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para las estructuras creadas.
		BUFF_STR_ITI			BUFF_INIS_MD_CRE[2];										//buffer para estructuras INIS_MD creadas.
		BUFF_STR_ITI			BUFF_SRLIS_CRE[2];											//buffer para estructuras SRLIS creadas.
		BUFF_STR_ITI			BUFF_PFRLIS_CRE[2];											//buffer para estructuras PFRLIS creadas.
		BUFF_STR_ITI			BUFF_INDFRLIS_MD_CRE[2];									//buffer para estructuras INDFRLIS_MD creadas.
		BUFF_STR_ITI			BUFF_INPRRLIS_MD_CRE[2];									//buffer para estructuras INPRRLIS_MD creadas.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para las estructuras en estado de suspensi�n.		
		deBUFF_STR_II			BUFF_INIS_MD_SUS;											//buffer para las estructuras INIS_MD suspendidas.
		deBUFF_STR_II			BUFF_SRLIS_SUS;												//buffer para las estructuras SRLIS suspendidas.
		deBUFF_STR_II			BUFF_PFRLIS_SUS;											//buffer para las estructuras PFRLIS suspendidas.
		deBUFF_STR_II			BUFF_INDFRLIS_MD_SUS;										//buffer para las estructuras INDFRLIS_MD suspendidas.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers para los id de las upci candidatas. 
		//[a][b]: a: tiempo, b: upci.
		dedein					BUFF_UPCI_ID_INIS_MD_CAN;									//buffer de id de las upci candidatas para INIS_MD.
		dedein					BUFF_UPCI_ID_INDFRLIS_MD_CAN;								//buffer de id de las upci candidatas para INDFRLIS_MD.
		dedein					BUFF_UPCI_ID_INPRRLIS_MD_CAN;								//buffer de id de las upci candidatas para INPRRLIS_MD.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffer de estructuras candidatas. 
		//[a][b][c]: a: tiempo, b: upci, c: buffer de estructura.
		dededein				BUFF_INIS_MD_ID_CAN;										//buffer de ids de estructuras tipo INIS_MD candidatas.
		dededein				BUFF_INDFRLIS_MD_ID_CAN;									//buffer de ids de estructuras tipo INDFRLIS_MD candidatas.
		dededein				BUFF_INPRRLIS_MD_ID_CAN;									//buffer de ids de estructuras tipo INPRRLIS_MD candidatas.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//buffer para �ndice de la relaci�n utilizada en flujo por reconocimiento.
		in						BUFF_RL_INDEX_USED_IN_RECOGNITION;	

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//buffer de las estructuras reconocidas.
		BUFF_STR_ITI			BUFF_INIS_MD_RE;											//buffer para estructura reconocida INIS_MD.
		BUFF_STR_ITI			BUFF_INDFRLIS_MD_RE;										//buffer para estructura reconocida INDFRLIS_MD.
		BUFF_STR_ITI			BUFF_INPRRLIS_MD_RE;										//buffer para estructura reconocida INPRRLIS_MD.												

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
		//################################ THREADS #################################### 

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//thread de entrada de la gupci.
		thread					THREAD_GUPCI_INPUT;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//mutex para escritura.
		std::mutex				RED_LIGHT_MUTEX;

	//m�todos p�blicos.
	public:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos constructor.
		GUPCI_HL_V();
		GUPCI_HL_V(in _gupci_id, in _upci_amount, UPCI_HL_V_ARG &_upci_arg);		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos destructor.
		~GUPCI_HL_V();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos de inicializaci�n.
		in			Initialize(in _upci_amount, UPCI_HL_V_ARG &_upci_arg);
		in			Initialize(in _gupci_id, in _upci_amount, UPCI_HL_V_ARG &_upci_arg);
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para Clean rupci.
		in			Clean();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para correr GUPCI.
		vo			Run();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo de entrada de comandos del usuario.
		vo			UserCommand(st _user_command);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para abrir, guardar, leer y imprimir gupci.
		in			Open(st _fileNameS, dou	*_buff_in_rg, dou *_buff_ev_rg, dou	*_buff_output_projection);
		in			Save(st _fileNameS);
		vo			PrintGUPCI(in _upci_id, in _buffers_selection, in _str_id);
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos Get para obtener cantidad de upci.
		in			GetUPCI_AMOUNT();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos Gets para estado de la banderas de la upci activa.
		in			GetKERNEL_INTEGRATION_FLAG();
		in			GetTHREAD_INTEGRATION_FLAG();
		in			GetTHREAD_INTEGRATION_FINIS_MDHED_FLAG();	
		in			GetCLOSE_ACTIVE_THREADS_FLAG();
		in			GetPAUSE_ACTIVE_THREADS_FLAG();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos Get para obtener contadores de la gupci y de la upci activa.
		in			GetGUPCI_ITERATION_COUNTER();
		in			GetKERNEL_ITERATION_COUNTER();
		in			GetTHREAD_ITERATION_COUNTER();
		in			GetGLOBAL_DIFFERENTIATION_COUNTER();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo Set de banderas.		
		vo			SetCLOSE_ACTIVE_THREADS_FLAG(in _status);
		vo			SetPAUSE_ACTIVE_THREADS_FLAG(in _status);

	//m�todos privados.
	private:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//thread donde corre la GUPCI.
		vo			ThreadRun();
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos de imprimir BUFF_DATA.		
		inline vo	PrintBuffBanderas(in _upci_id);											//impresi�n buffer de banderas.
		inline vo   PrintBuffNucleo(in _upci_id);											//impresi�n buffer del n�cleo.
		inline vo   PrintBuffEstructurasINIS_MD(in _upci_id, in _str_id);					//impresi�n buffer de estructuras INIS_MD.
		inline vo   PrintBuffEstructurasSRLIS(in _upci_id, in _str_id);						//impresi�n buffer de estructuras SRLIS.
		inline vo   PrintBuffEstructurasPFRLIS(in _upci_id, in _str_id);					//impresi�n buffer de estructuras PFRLIS.
		inline vo   PrintBuffEstructurasINDFRLIS_MD(in _upci_id, in _str_id);				//impresi�n buffer de estructuras INDFRLIS_MD.
		inline vo   PrintBuffEstructurasINPRRLIS_MD(in _upci_id, in _str_id);				//impresi�n buffer de estructuras INPRRLIS_MD.
		inline vo   PrintBuffINIS_MDCandidatas(in _upci_id);								//impresi�n buffer de estructuras candidatas de INIS_MD.
		inline vo   PrintBuffINDFRLIS_MDCandidatas(in _upci_id);							//impresi�n buffer de estructuras candidatas de INDFRLIS_MD.
		inline vo   PrintBuffINPRRLIS_MDCandidatas(in _upci_id);							//impresi�n buffer de estructuras candidatas de INPRRLIS_MD.
		inline vo   PrintBuffIdUpcINIS_MDCandidatas(in _upci_id);							//impresi�n buffer de las id de upci con estructuras INIS_MD candidatas.
		inline vo   PrintBuffIdUpcINDFRLIS_MDCandidatas(in _upci_id);						//impresi�n buffer de las id de upci con estructuras INDFRLIS_MD candidatas.
		inline vo   PrintBuffIdUpcINPRRLIS_MDCandidatas(in _upci_id);						//impresi�n buffer de las id de upci con estructuras INPRRLIS_MD candidatas.
		inline vo   PrintBuffIdEstDisponibles(in _upci_id);									//impresi�n buffer de id de estructuras disponibles.
		inline vo   PrintBuffIdYTipoEstCreadas(in _upci_id);								//impresi�n buffer de id de estructuras creadas.
		inline vo   PrintBuffEstReconocidas(in _upci_id);									//impresi�n buffer de id de estructuras reconocidas.
		inline vo   PrintBuffCantUpciEstSuspension(in _upci_id);							//impresi�n buffer de cantidades de upci y estructuras en estado de suspensi�n.
		inline vo   PrintBuffCantEstExistentes(in _upci_id);								//impresi�n buffer con la cantidades de estructuras existentes.
		inline vo   PrintBuffCantExp(in _upci_id);											//impresi�n de buffer de cantidad de expansiones.
		inline vo   PrintBuffMaxIdEst(in _upci_id);											//impresi�n buffer con los m�ximos id de las estructuras.		
	};
}