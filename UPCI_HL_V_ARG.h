#pragma once
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
/*
Nombre Clase : 	  UPCI_HL_V_ARG (Estructura de argumentos para la clase UPCI_HL_V).
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
	//clase UPCI_HL_V_ARG.
	class UPCI_HL_V_ARG
	{

		//miembros públicos.
	public:		

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//argumentos: parámetros estructurales.	
		in					inis_md_amount_allowed;											//cantidad de estructuras de entrada permitidas.
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
		dou					dif_raw_input_threshold;										//umbral de entrada cruda para focalización de la atención (%).
		dou					str_congruence_threshold;										//umbral de congruencia para estructuras candidatas (%).	
		dou					pfrlis_strength_threshold;										//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
		dou					indfrlis_strength_threshold;									//umbral de fortaleza de relación INDFRLIS para eliminar relación por N.A.
		dou					evaluation_threshold;											//umbral para evaluaciones.	
		dou					transition_evaluation_threshold;								//umbral para transiciones de evaluaciones.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//argumentos: tiempos para threads de limpieza y actualización.
		in					timeout_clean_is;												//tiempo de espera de limpieza de IS.
		in					timeout_update_al_is;											//tiempo de espera para actualizar niveles de actividad en IS (ms). (ms)

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
		vo					*buff_upci;		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------  
		//puntero a buffer para el id de la upci que puede almacenar estructuras.
		in					*buff_upci_id_storage_flag_act;
				
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para registros.
		dou					*buff_in_rg;													//puntero a buffer para registro de entrada.
		dou					*buff_ev_rg;													//puntero a buffer para registro de evaluación de entrada.
		dou					*buff_in_dif_rg;												//puntero a buffer para registro de diferencia de entradas.
		dou					*buff_in_pro_rg;												//puntero a buffer para registro de proporción de diferencia de entradas.
		dou					*buff_output_projection;										//puntero a buffer para registro de proyección de salida.
		
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//punteros a buffers para estructura INIS_MD con evaluación máxima.
		BUFF_STR_II			*buff_inis_md_max_eval;											//puntero a buffer para la estructura INIS_MD con máxima evaluación
		dou					*buff_max_evaluation;											//puntero a buffer para la máxima evaluación.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//punteros a buffers para estructura INIS_MD con nivel de actividad máximo.
		BUFF_STR_II			*buff_inis_md_max_al;											//puntero a buffer para la estructura INIS_MD con nivel de actividad máximo.
		dou					*buff_max_activity_level;										//puntero a buffer para el máximo nivel de actividad.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//punteros a buffers para estructura con fortaleza de la relación máximo.
		BUFF_STR_IIT		*buff_str_max_rs;												//puntero a buffer para la estructura con fortaleza de la relación máximo.
		dou					*buff_max_relation_strength;									//puntero a buffer para el máximo fortaleza de la relación.	

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//puntero a buffer para las estructuras INIS_MD activadas.
		BUFF_STR_II			*buff_inis_md_activated;											

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//puntero a buffer para índice de la relación utilizada en flujo por reconocimiento.
		in					*buff_rl_index_used_in_recognition;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para estructuras en estado de suspensión.		
		deBUFF_STR_II		*buff_inis_md_sus;												//puntero a buffer para las estructuras INIS_MD suspendidas.
		deBUFF_STR_II		*buff_srlis_sus;												//puntero a buffer para las estructuras SRLIS suspendidas.
		deBUFF_STR_II		*buff_pfrlis_sus;												//puntero a buffer para las estructuras PFRLIS suspendidas.
		deBUFF_STR_II		*buff_indfrlis_sus;												//puntero a buffer para las estructuras INDFRLIS suspendidas.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para las estructuras creadas.
		BUFF_STR_II			*buff_inis_md_cre;												//puntero a buffer para estructuras INIS_MD creadas.
		BUFF_STR_II			*buff_srlis_cre;												//puntero a buffer para estructuras SRLIS creadas.
		BUFF_STR_II			*buff_pfrlis_cre;												//puntero a buffer para estructuras PFRLIS creadas.
		BUFF_STR_II			*buff_indfrlis_cre;												//puntero a buffer para estructuras INDFRLIS creadas.
		BUFF_STR_II			*buff_inprrlis_cre;												//puntero a buffer para estructuras INPRRLIS creadas.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//punteros a buffers para las estructuras reconocidas.
		BUFF_STR_II			*buff_inis_md_re;												//puntero a buffer para estructura reconocida INIS_MD.
		BUFF_STR_II			*buff_indfrlis_re;												//puntero a buffer para estructura reconocida INDFRLIS.
		BUFF_STR_II			*buff_inprrlis_re;												//puntero a buffer para estructura reconocida INPRRLIS.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//argumento: punteros a buffers para los id de las upci candidatas.
		dedein				*buff_upci_id_inis_md_can;										//puntero a buffer de id de las upci candidatas para INIS_MD.
		dedein				*buff_upci_id_indfrlis_can;										//puntero a buffer de id de las upci candidatas para INDFRLIS.
		dedein				*buff_upci_id_inprrlis_can;										//puntero a buffer de id de las upci candidatas para INPRRLIS.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffer de estructuras candidatas externas
		dededein			*buff_inis_md_id_can;											//puntero a buffer de ids de estructuras tipo INIS_MD candidatas.
		dededein			*buff_indfrlis_id_can;											//puntero a buffer de ids de estructuras tipo INDFRLIS candidatas.
		dededein			*buff_inprrlis_id_can;											//puntero a buffer de ids de estructuras tipo INPRRLIS candidatas.
		
		//métodos públicos.
	public:

		//-----------------------------------------------------------------------------
		//métodos constructor.
		UPCI_HL_V_ARG();
		UPCI_HL_V_ARG(dou	*_buff_in_rg,
					  dou	*_buff_ev_rg,	
					  dou	*_buff_output_projection,
					  in	_inis_md_amount_allowed,
					  in	_rlis_amount_allowed,
					  dou	_default_activity_level,
					  dou	_max_activity_level_allowed,
					  dou	_min_activity_level_allowed,	
					  dou	_dif_raw_input_threshold,
					  dou	_str_congruence_threshold,
					  dou	_pfrlis_strength_threshold,
					  dou	_indfrlis_strength_threshold,
					  dou	_evaluation_threshold,
					  dou	_transition_evaluation_threshold,
					  in	_timeout_clean_is,
					  in	_timeout_update_al_is);

		//-----------------------------------------------------------------------------
		//destructor.
		~UPCI_HL_V_ARG();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método de inicialización.
		vo Initialize(dou	*_buff_in_rg,
					  dou	*_buff_ev_rg,	
					  dou	*_buff_output_projection,
					  in	_inis_md_amount_allowed,
					  in	_rlis_amount_allowed,
	  				  dou	_default_activity_level,
		 			  dou	_max_activity_level_allowed,
					  dou	_min_activity_level_allowed,	
					  dou	_dif_raw_input_threshold,
					  dou	_str_congruence_threshold,
					  dou	_pfrlis_strength_threshold,
					  dou	_indfrlis_strength_threshold,
					  dou	_evaluation_threshold,
					  dou	_transition_evaluation_threshold,
					  in	_timeout_clean_is,
					  in	_timeout_update_al_is);
		
		//-----------------------------------------------------------------------------
		//método para Setear punteros a buffers de gupci.
		vo	SetPtrBuff(in				*_close_active_threads_flag,
					   in				*_pause_active_threads_flag,
					   in				*_gupci_id,
					   vo				*_buff_upci,
					   in				*_buff_upci_id_storage_flag_act,
					   dou				*_buff_in_dif_rg,
					   dou				*_buff_in_pro_rg,	
					   BUFF_STR_II		*_buff_inis_md_max_eval,
					   dou				*_buff_max_evaluation,
					   BUFF_STR_II		*_buff_inis_md_max_al,
					   dou				*_buff_max_activity_level,	
					   BUFF_STR_IIT		*_buff_str_max_rs,
					   dou				*_buff_max_relation_strength,	
					   BUFF_STR_II		*_buff_inis_md_activated,
					   in				*_buff_rl_index_used_in_recognition,
					   deBUFF_STR_II	*_buff_inis_md_sus,
					   deBUFF_STR_II	*_buff_srlis_sus,
					   deBUFF_STR_II	*_buff_pfrlis_sus,
					   deBUFF_STR_II	*_buff_indfrlis_sus,
					   BUFF_STR_II		*_buff_inis_md_cre,
					   BUFF_STR_II		*_buff_srlis_cre,
					   BUFF_STR_II		*_buff_pfrlis_cre,
					   BUFF_STR_II		*_buff_indfrlis_cre,
					   BUFF_STR_II		*_buff_inprrlis_cre,
					   BUFF_STR_II		*_buff_inis_md_re,
					   BUFF_STR_II		*_buff_indfrlis_re,
					   BUFF_STR_II		*_buff_inprrlis_re,
					   dedein			*_buff_upci_id_inis_md_can,
					   dedein			*_buff_upci_id_indfrlis_can,
					   dedein			*_buff_upci_id_inprrlis_can,
					   dededein			*_buff_inis_md_can,
					   dededein			*_buff_indfrlis_can,
					   dededein			*_buff_inprrlis_can);

		//-----------------------------------------------------------------------------
		//método para limpiar UPCI_HL_V_ARG.
		vo  Clean();
	};
}

