#pragma once
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
/*
Nombre Clase : 	  UPCI_ARG_VSD (Estructura de argumentos para la clase UPCI_VSD).
Fecha	     :	  11:58 pm 08-02-2017.
Diseñador    :	  Gustavo Catalán Ulloa.
descripción	 :	  XXXXXXXXXXXX.
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include <deque>
#include "BUFF_STR_II.h"
#include "BUFF_STR_IIT.h"

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
typedef		deque<in>						dein;
typedef		deque<string>					dest;
typedef		deque<deque<in>>				dedein;
typedef		deque<deque<deque<in>>>			dededein;	
typedef		deque<BUFF_STR_II>				deBUFF_STR_II;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//nombre de espacio UPC.
namespace UPC
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//clase UPCI_ARG_VSD.
	class UPCI_ARG_VSD
	{

		//miembros públicos.
	public:		

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//argumentos: parámetros estructurales.	
		in					inis_vs_amount_allowed;											//cantidad de estructuras de entrada permitidas.
		in					acis_sd_amount_allowed;											//cantidad de estructuras de acción permitidas.
		in					rlis_amount_allowed;											//cantidad de estructuras de relación permitidas.
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//argumentos: parámetros de actividad.
		dou					default_activity_level;											//nivel de actividad por defecto.
		dou					max_activity_level_allowed;										//nivel de actividad máximo permitido.
		dou					min_activity_level_allowed;										//nivel de actividad mínimo permitido.
		
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//argumentos: umbrales.
		dou					kernel_raw_input_threshold;										//umbral de entrada cruda para control del núcleo.
		dou					dif_raw_input_threshold;										//umbral de entrada cruda para focalización de la atención (%).
		dou					str_congruence_sr_threshold;									//umbral de congruencia de registros unidimensionales (%).	
		dou					pfrlis_strength_threshold;										//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
		dou					indfrlis_vs_strength_threshold;									//umbral de fortaleza de relación INDFRLIS_VS para eliminar relación por N.A.
		dou					evaluation_threshold;											//umbral para evaluaciones.	
		dou					transition_evaluation_threshold;								//umbral para transiciones de evaluaciones.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//argumentos: tiempos para threads de limpieza y actualización.
		in					timeout_clean_is;												//tiempo de espera de limpieza de IS.
		in					timeout_update_al_is;											//tiempo de espera para actualizar niveles de actividad en IS (ms). (ms)

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//punteros a banderas para funcionalidades.
		in					*suspended_actions_maximization_flag;							//puntero a bandera para utilizar reactivación acción suspendida con máxima asociación positiva.
		in					*structures_recognition_flag;									//puntero a bandrea para utilizar reconocimiento de estructuras.
		in					*structures_projections_flag;									//puntero a bandera para utilizar proyección de estructuras.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//punteros a banderas para threads activos.
		in					*close_active_threads_flag;										//puntero a bandera para cerrar threads activos.
		in					*pause_active_threads_flag;										//puntero a bandera para pausar threads activos.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//puntero a id de la gupci.
		in					*gupci_id;				

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//puntero a buffer para las upci.
		vo					*buff_upci_vsd;		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------  
		//puntero a buffer para el id de la upci que puede almacenar estructuras.
		in					*buff_upci_id_storage_flag_act;
				
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para almacenar registros.
		dou					*buff_in_rg;													//puntero a buffer para registro de entrada.
		dou					*buff_ev_rg;													//puntero a buffer para registro de evaluación de entrada.
		st					*buff_ac_rg;													//puntero a buffer para registro de acción.
		dou					*buff_in_dif_rg;												//puntero a buffer para registro de diferencia de entradas.
		dou					*buff_in_pro_rg;												//puntero a buffer para registro de proporción de diferencia de entradas.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//punteros a buffers para estructura con evaluación máxima.
		BUFF_STR_II			*buff_str_max_eval;												//puntero a buffer para la estructura INIS_VS con máxima evaluación
		dou					*buff_max_evaluation;											//puntero a buffer para la máxima evaluación.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//punteros a buffers para estructura con nivel de actividad máximo.
		BUFF_STR_IIT		*buff_str_max_al;												//puntero a buffer para la estructura con nivel de actividad máximo.
		dou					*buff_max_activity_level;										//puntero a buffer para el máximo nivel de actividad.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//punteros a buffers para estructura con fortaleza de la relación máximo.
		BUFF_STR_IIT		*buff_str_max_rs;												//puntero a buffer para la estructura con fortaleza de la relación máximo.
		dou					*buff_max_relation_strength;									//puntero a buffer para el máximo fortaleza de la relación.	

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//punteros a buffers para las estructuras activadas.
		BUFF_STR_IIT		*buff_str_activated;											//puntero a buffer para las estructuras activadas.
		BUFF_STR_II			*buff_inis_vs_activated;										//puntero a buffer para las estructuras INIS_VS activadas.
		BUFF_STR_II			*buff_acis_sd_activated;										//puntero a buffer para las estructuras ACIS_SD activadas.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//puntero a buffer para las estructuras de acción ejecutadas.
		BUFF_STR_II			*buff_execute_acis_sd;
		
		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//puntero a buffer para índice de la relación utilizada en flujo por reconocimiento.
		in					*buff_rl_index_used_in_recognition;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para estructuras en estado de suspensión.		
		deBUFF_STR_II		*buff_inis_vs_sus;												//puntero a buffer para las estructuras INIS_VS suspendidas.
		deBUFF_STR_II		*buff_acis_sd_sus;												//puntero a buffer para las estructuras ACIS_SD suspendidas.
		deBUFF_STR_II		*buff_pfrlis_sus;												//puntero a buffer para las estructuras PFRLIS suspendidas.
		deBUFF_STR_II		*buff_indfrlis_vs_sus;											//puntero a buffer para las estructuras INDFRLIS_VS suspendidas.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para las estructuras creadas.
		BUFF_STR_II			*buff_inis_vs_cre;												//puntero a buffer para estructuras INIS_VS creadas.
		BUFF_STR_II			*buff_acis_sd_cre;												//puntero a buffer para estructuras ACIS_SD creadas.
		BUFF_STR_II			*buff_pfrlis_cre;												//puntero a buffer para estructuras PFRLIS creadas.
		BUFF_STR_II			*buff_indfrlis_vs_cre;											//puntero a buffer para estructuras INDFRLIS_VS creadas.
		BUFF_STR_II			*buff_inprrlis_vs_cre;											//puntero a buffer para estructuras INPRRLIS_VS creadas.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//punteros a buffers para las estructuras reconocidas.
		BUFF_STR_II			*buff_inis_vs_re;												//puntero a buffer para estructura reconocida INIS_VS.
		BUFF_STR_II			*buff_acis_sd_re;												//puntero a buffer para estructura reconocida ACIS_SD.
		BUFF_STR_II			*buff_indfrlis_vs_re;											//puntero a buffer para estructura reconocida INDFRLIS_VS.
		BUFF_STR_II			*buff_inprrlis_vs_re;											//puntero a buffer para estructura reconocida INPRRLIS_VS.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//argumento: punteros a buffers para los id de las upci candidatas.
		dedein				*buff_upci_id_inis_vs_can;										//puntero a buffer de id de las upci candidatas para INIS_VS.
		dedein				*buff_upci_id_acis_sd_can;										//puntero a buffer de id de las upci candidatas para ACIS_SD.
		dedein				*buff_upci_id_indfrlis_vs_can;									//puntero a buffer de id de las upci candidatas para INDFRLIS_VS.
		dedein				*buff_upci_id_inprrlis_vs_can;									//puntero a buffer de id de las upci candidatas para INPRRLIS_VS.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffer de estructuras candidatas externas
		dededein			*buff_inis_vs_id_can;											//puntero a buffer de ids de estructuras tipo INIS_VS candidatas.
		dededein			*buff_acis_sd_id_can;											//puntero a buffer de ids de estructuras tipo ACIS_SD candidatas.
		dededein			*buff_indfrlis_vs_id_can;										//puntero a buffer de ids de estructuras tipo INDFRLIS_VS candidatas.
		dededein			*buff_inprrlis_vs_id_can;										//puntero a buffer de ids de estructuras tipo INPRRLIS_VS candidatas.
		
		//métodos públicos.
	public:

		//-----------------------------------------------------------------------------
		//métodos constructor.
		UPCI_ARG_VSD();
		UPCI_ARG_VSD(in		_inis_vs_amount_allowed,
				     in		_acis_sd_amount_allowed,
					 in		_rlis_amount_allowed,
					 dou	_default_activity_level,
					 dou	_max_activity_level_allowed,
					 dou	_min_activity_level_allowed,	
					 dou	_kernel_raw_input_threshold,
					 dou	_dif_raw_input_threshold,
					 dou	_str_congruence_sr_threshold,
					 dou	_pfrlis_strength_threshold,
					 dou	_indfrlis_vs_strength_threshold,
					 dou	_evaluation_threshold,
					 dou	_transition_evaluation_threshold,
					 in		_timeout_clean_is,
					 in		_timeout_update_al_is);

		//-----------------------------------------------------------------------------
		//destructor.
		~UPCI_ARG_VSD();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método de inicialización.
		vo Initialize(in	_inis_vs_amount_allowed,
					  in	_acis_sd_amount_allowed,
					  in	_rlis_amount_allowed,
	  				  dou	_default_activity_level,
		 			  dou	_max_activity_level_allowed,
					  dou	_min_activity_level_allowed,	
					  dou	_kernel_raw_input_threshold,
					  dou	_dif_raw_input_threshold,
					  dou	_str_congruence_sr_threshold,
					  dou	_pfrlis_strength_threshold,
					  dou	_indfrlis_vs_strength_threshold,
					  dou	_evaluation_threshold,
					  dou	_transition_evaluation_threshold,
					  in	_timeout_clean_is,
					  in	_timeout_update_al_is);
		
		//-----------------------------------------------------------------------------
		//método para Setear punteros a buffers de gupci.
		vo	SetPtrBuff(in					*_suspended_actions_maximization_flag,
					   in					*_structures_recognition_flag,
					   in					*_structures_projections_flag,
					   in					*_close_active_threads_flag,
					   in					*_pause_active_threads_flag,
					   in					*_gupci_id,
					   vo					*_buff_upci_vsd,
					   in					*_buff_upci_id_storage_flag_act,
					   dou					*_buff_in_rg,
					   dou					*_buff_ev_rg,
					   st					*_buff_ac_rg,
					   dou					*_buff_in_dif_rg,
					   dou					*_buff_in_pro_rg,					   
					   BUFF_STR_II			*_buff_str_max_eval,
					   dou					*_buff_max_evaluation,
					   BUFF_STR_IIT			*_buff_str_max_al,
					   dou					*_buff_max_activity_level,	
					   BUFF_STR_IIT			*_buff_str_max_rs,
					   dou					*_buff_max_relation_strength,	
					   BUFF_STR_IIT			*_buff_str_activated,
					   BUFF_STR_II			*_buff_inis_vs_activated,
					   BUFF_STR_II			*_buff_acis_sd_activated,
					   BUFF_STR_II			*_buff_execute_acis_sd,
					   in					*_buff_rl_index_used_in_recognition,
					   deBUFF_STR_II		*_buff_inis_vs_sus,
					   deBUFF_STR_II		*_buff_acis_sd_sus,
					   deBUFF_STR_II		*_buff_pfrlis_sus,
					   deBUFF_STR_II		*_buff_indfrlis_vs_sus,
					   BUFF_STR_II			*_buff_inis_vs_cre,
					   BUFF_STR_II			*_buff_acis_sd_cre,
					   BUFF_STR_II			*_buff_pfrlis_cre,
					   BUFF_STR_II			*_buff_indfrlis_vs_cre,
					   BUFF_STR_II			*_buff_inprrlis_vs_cre,	
					   BUFF_STR_II			*_buff_inis_vs_re,
					   BUFF_STR_II			*_buff_acis_sd_re,
					   BUFF_STR_II			*_buff_indfrlis_vs_re,
					   BUFF_STR_II			*_buff_inprrlis_vs_re,
					   dedein				*_buff_upci_id_inis_vs_can,
					   dedein				*_buff_upci_id_acis_sd_can,
					   dedein				*_buff_upci_id_indfrlis_vs_can,
					   dedein				*_buff_upci_id_inprrlis_vs_can,
					   dededein				*_buff_inis_vs_can,
					   dededein				*_buff_acis_sd_can,
					   dededein				*_buff_indfrlis_vs_can,
					   dededein				*_buff_inprrlis_vs_can);

		//-----------------------------------------------------------------------------
		//método para limpiar UPCI_ARG_VSD.
		vo  Clean();
	};
}

