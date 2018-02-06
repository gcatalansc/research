//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
Nombre Clase : 	  UPCI_HL_V_ARG (Estructura de argumentos para la clase UPCI_HL_V).
Fecha	     :	  11:58 pm 08-02-2017.
Diseñador    :	  Gustavo Catalán Ulloa.
descripción	 :	  XXXXXXXXXXXX.
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include "UPCI_HL_V_ARG.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: constructor 1.
UPCI_HL_V_ARG::UPCI_HL_V_ARG()
{

}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: constructor 2.
UPCI_HL_V_ARG::UPCI_HL_V_ARG(dou	*_buff_in_rg,
						     dou	*_buff_ev_rg,	
					         dou	*_buff_output_projection,
						     in		_inis_md_amount_allowed,
						     in		_rlis_amount_allowed,
						     dou	_default_activity_level,
						     dou	_max_activity_level_allowed,
						     dou	_min_activity_level_allowed,
						     dou	_dif_raw_input_threshold,
						     dou	_str_congruence_threshold,
						     dou	_pfrlis_strength_threshold,
						     dou	_indfrlis_strength_threshold,
						     dou	_evaluation_threshold,
						     dou	_transition_evaluation_threshold,
						     in		_timeout_clean_is,
						     in		_timeout_update_al_is)
{
	//---------------------------------------------------------------------------------
	//inicialización de argumebntos: punteros a buffers para registros.
	this->buff_in_rg						= _buff_in_rg;									//puntero a buffer para registro de entrada.
	this->buff_ev_rg						= _buff_ev_rg;									//puntero a buffer para registro de evaluación de entrada.
	this->buff_output_projection			= _buff_output_projection;						//puntero a buffer para registro de proyección de salida.

		//---------------------------------------------------------------------------------
	//inicialización de argumentos: parámetros estructurales.
	this->inis_md_amount_allowed			= _inis_md_amount_allowed;							//cantidad de estructuras inis_md permitidas.
	this->rlis_amount_allowed				= _rlis_amount_allowed;							//cantidad de estructuras rlis permitidas.
	
	//---------------------------------------------------------------------------------
	//inicialización de argumentos: parámetros de actividad.
	this->default_activity_level			= _default_activity_level;						//nivel de actividad por defecto.
	this->max_activity_level_allowed		= _max_activity_level_allowed;					//nivel de actividad máximo permitido.
	this->min_activity_level_allowed		= _min_activity_level_allowed;					//nivel de actividad mínimo permitido.

	//---------------------------------------------------------------------------------
	//inicialización de argumentos: umbrales.
	this->dif_raw_input_threshold			= _dif_raw_input_threshold;						//umbral de entrada cruda para focalización de la atención (%).
	this->str_congruence_threshold			= _str_congruence_threshold;					//umbral de congruencia para estructuras candidatas (%).	
	this->pfrlis_strength_threshold			= _pfrlis_strength_threshold;					//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
	this->indfrlis_strength_threshold		= _indfrlis_strength_threshold;					//umbral de fortaleza de relación INDFRLIS para eliminar relación por N.A.
	this->transition_evaluation_threshold	= _transition_evaluation_threshold;				//umbral para transición de evaluaciones.	

	//---------------------------------------------------------------------------------
	//inicialización de argumentos: tiempos para threads de limpieza y actualización.
	this->timeout_clean_is					= _timeout_clean_is;							//tiempo de espera de limpieza de IS.
	this->timeout_update_al_is				= _timeout_update_al_is;						//tiempo de espera para actualizar niveles de actividad en IS (ms). (ms)
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: destructor.
UPCI_HL_V_ARG::~UPCI_HL_V_ARG()
{
	//---------------------------------------------------------------------------------
	//limpieza de buffer.
	this->Clean();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método de inicialización.
vo  UPCI_HL_V_ARG::Initialize(dou	*_buff_in_rg,
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
							  in	_timeout_update_al_is)
{
	//---------------------------------------------------------------------------------
	//limpieza de buffer.
	this->Clean();

	//---------------------------------------------------------------------------------
	//inicialización de argumebntos: punteros a buffers para registros.
	this->buff_in_rg						= _buff_in_rg;									//puntero a buffer para registro de entrada.
	this->buff_ev_rg						= _buff_ev_rg;									//puntero a buffer para registro de evaluación de entrada.
	this->buff_output_projection			= _buff_output_projection;						//puntero a buffer para registro de proyección de salida.

	//---------------------------------------------------------------------------------
	//inicialización de argumentos: parámetros estructurales.
	this->inis_md_amount_allowed			= _inis_md_amount_allowed;						//cantidad de estructuras inis_md permitidas.
	this->rlis_amount_allowed				= _rlis_amount_allowed;							//cantidad de estructuras rlis permitidas.
	
	//---------------------------------------------------------------------------------
	//inicialización de argumentos: parámetros de actividad.
	this->default_activity_level			= _default_activity_level;						//nivel de actividad por defecto.
	this->max_activity_level_allowed		= _max_activity_level_allowed;					//nivel de actividad máximo permitido.
	this->min_activity_level_allowed		= _min_activity_level_allowed;					//nivel de actividad mínimo permitido.

	//---------------------------------------------------------------------------------
	//inicialización de argumentos: umbrales.
	this->dif_raw_input_threshold			= _dif_raw_input_threshold;						//umbral de entrada cruda para focalización de la atención (%).
	this->str_congruence_threshold			= _str_congruence_threshold;					//umbral de congruencia para estructuras candidatas (%).	
	this->pfrlis_strength_threshold			= _pfrlis_strength_threshold;					//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
	this->indfrlis_strength_threshold		= _indfrlis_strength_threshold;					//umbral de fortaleza de relación INDFRLIS para eliminar relación por N.A.
	this->transition_evaluation_threshold	= _transition_evaluation_threshold;				//umbral para transición de evaluaciones.	

	//---------------------------------------------------------------------------------
	//inicialización de argumentos: tiempos para threads de limpieza y actualización.
	this->timeout_clean_is					= _timeout_clean_is;							//tiempo de espera de limpieza de IS.
	this->timeout_update_al_is				= _timeout_update_al_is;						//tiempo de espera para actualizar niveles de actividad en IS (ms). (ms)
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: //método para setear punteros a buffers de gupci.
vo	UPCI_HL_V_ARG::SetPtrBuff(in				*_close_active_threads_flag,
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
						      deBUFF_STR_II		*_buff_inis_md_sus,
							  deBUFF_STR_II		*_buff_srlis_sus,
						      deBUFF_STR_II		*_buff_pfrlis_sus,
						      deBUFF_STR_II		*_buff_indfrlis_sus,
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
						      dededein			*_buff_inprrlis_can)
 {
	//--------------------------------------------------------------------------------- 
	//seteo de punteros a banderas para threads activos.
	this->close_active_threads_flag				= _close_active_threads_flag;										
	this->pause_active_threads_flag				= _pause_active_threads_flag;										

	//--------------------------------------------------------------------------------- 
	//seteo de puntero a id de la gupci.
	this->gupci_id								= _gupci_id;

	//---------------------------------------------------------------------------------
	//seteo de puntero para las upci.
	this->buff_upci								= _buff_upci;

	//---------------------------------------------------------------------------------  
	//seteo de puntero a buffer para el id de la upci que puede almacenar estructuras.
	this->buff_upci_id_storage_flag_act			= _buff_upci_id_storage_flag_act;

	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para registros.
	this->buff_in_dif_rg						= _buff_in_dif_rg;
	this->buff_in_pro_rg						= _buff_in_pro_rg;

	//--------------------------------------------------------------------------------- 
	//seteo de punteros a buffers para estructura INIS_MD con evaluación máxima.
	this->buff_inis_md_max_eval					= _buff_inis_md_max_eval;
	this->buff_max_evaluation					= _buff_max_evaluation;											

	//--------------------------------------------------------------------------------- 
	//seteo de punteros a buffers para estructura INIS_MD con nivel de actividad máximo.
	this->buff_inis_md_max_al					= _buff_inis_md_max_al;
	this->buff_max_activity_level				= _buff_max_activity_level;		

	//--------------------------------------------------------------------------------- 
	//seteo de punteros a buffers para estructura con fortaleza de la relación máximo.
	this->buff_str_max_rs						= _buff_str_max_rs;
	this->buff_max_relation_strength			= _buff_max_relation_strength;	

	//---------------------------------------------------------------------------------
	//seteo de puntero a buffer para las estructuras INIS_MD activadas.
	this->buff_inis_md_activated				= _buff_inis_md_activated;

	//---------------------------------------------------------------------------------
	//puntero a buffer para índice de la relación utilizada en flujo por reconocimiento.
	this->buff_rl_index_used_in_recognition		= _buff_rl_index_used_in_recognition;

	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para estructuras en estado de suspensión.
	this->buff_inis_md_sus						= _buff_inis_md_sus;
	this->buff_srlis_sus						= _buff_srlis_sus;
	this->buff_pfrlis_sus						= _buff_pfrlis_sus;
	this->buff_indfrlis_sus						= _buff_indfrlis_sus;

	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para las estructuras creadas.
	this->buff_inis_md_cre						= _buff_inis_md_cre;
	this->buff_srlis_cre						= _buff_srlis_cre;	
	this->buff_pfrlis_cre						= _buff_pfrlis_cre;	
	this->buff_indfrlis_cre						= _buff_indfrlis_cre;										
	this->buff_inprrlis_cre						= _buff_inprrlis_cre;

	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para las estructuras reconocidas.
	this->buff_inis_md_re						= _buff_inis_md_re;
	this->buff_indfrlis_re						= _buff_indfrlis_re;
	this->buff_inprrlis_re						= _buff_inprrlis_re;

	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers de id de las upci candidatas.
	this->buff_upci_id_inis_md_can				= _buff_upci_id_inis_md_can;
	this->buff_upci_id_indfrlis_can				= _buff_upci_id_indfrlis_can;
	this->buff_upci_id_inprrlis_can				= _buff_upci_id_inprrlis_can;

	//---------------------------------------------------------------------------------
	//seteo de punteros buffers de estructuras candidatas.
	this->buff_inis_md_id_can					= _buff_inis_md_can;
	this->buff_indfrlis_id_can					= _buff_indfrlis_can;
	this->buff_inprrlis_id_can					= _buff_inprrlis_can;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para Clean UPCI_HL_V_ARG.
vo  UPCI_HL_V_ARG::Clean()
{
	//---------------------------------------------------------------------------------
	//limpieza de argumentos: parámetros estructurales.
	this->inis_md_amount_allowed				= NULL;								
	this->rlis_amount_allowed					= NULL;									
	
	//---------------------------------------------------------------------------------
	//limpieza de argumentos: parámetros de actividad.
	this->default_activity_level				= NULL;								
	this->max_activity_level_allowed			= NULL;									
	this->min_activity_level_allowed			= NULL;									

	//---------------------------------------------------------------------------------
	//limpieza de argumentos: umbrales.						
	this->dif_raw_input_threshold				= NULL;								
	this->str_congruence_threshold				= NULL;								
	this->pfrlis_strength_threshold				= NULL;							
	this->indfrlis_strength_threshold			= NULL;
	this->evaluation_threshold					= NULL;
	this->transition_evaluation_threshold		= NULL;							

	//---------------------------------------------------------------------------------
	//limpieza de argumentos: tiempos para threads de limpieza y actualización.
	this->timeout_clean_is						= NULL;									
	this->timeout_update_al_is					= NULL;		

	//--------------------------------------------------------------------------------- 
	//seteo de punteros a banderas para threads activos.
	this->close_active_threads_flag				= NULL;										
	this->pause_active_threads_flag				= NULL;

	//--------------------------------------------------------------------------------- 
	//limpieza de puntero a id de la gupci.
	this->gupci_id								= NULL;

	//---------------------------------------------------------------------------------
	//limpieza de puntero para las upci.
	this->buff_upci								= NULL;

	//---------------------------------------------------------------------------------  
	//limpieza de puntero a buffer para el id de la upci que puede almacenar estructuras.
	this->buff_upci_id_storage_flag_act			= NULL;

	//---------------------------------------------------------------------------------
	//limpieza de punteros a buffers para registros.
	this->buff_in_rg							= NULL;
	this->buff_ev_rg							= NULL;
	this->buff_in_dif_rg						= NULL;
	this->buff_in_pro_rg						= NULL;
	this->buff_output_projection				= NULL;				

	//--------------------------------------------------------------------------------- 
	//limpieza de punteros a buffers para estructura INIS_MD con evaluación máxima.
	this->buff_inis_md_max_eval					= NULL;
	this->buff_max_evaluation					= NULL;											

	//--------------------------------------------------------------------------------- 
	//limpieza de punteros a buffers para estructura con nivel de actividad máximo.
	this->buff_inis_md_max_al					= NULL;
	this->buff_max_activity_level				= NULL;		

	//--------------------------------------------------------------------------------- 
	//limpieza de punteros a buffers para estructura con fortaleza de la relación máximo.
	this->buff_str_max_rs						= NULL;
	this->buff_max_relation_strength			= NULL;	

	//---------------------------------------------------------------------------------
	//limpieza de puntero a buffer para las estructuras INIS_MD activadas.
	this->buff_inis_md_activated				= NULL;

	//---------------------------------------------------------------------------------
	//limpieza de puntero a buffer para las estructuras proyectadas de salida.
	this->buff_output_projection				= NULL;

	//---------------------------------------------------------------------------------
	//limpieza de puntero a buffer para índice de la relación utilizada en flujo por reconocimiento.
	this->buff_rl_index_used_in_recognition		= NULL;

	//---------------------------------------------------------------------------------
	//limpieza de punteros a buffers para las estructuras en estado de suspensión.
	this->buff_inis_md_sus						= NULL;	
	this->buff_srlis_sus						= NULL;
	this->buff_pfrlis_sus						= NULL;
	this->buff_indfrlis_sus						= NULL;

	//---------------------------------------------------------------------------------
	//limpieza de punteros a buffers para las estructuras creadas.
	this->buff_inis_md_cre						= NULL;
	this->buff_srlis_cre						= NULL;	
	this->buff_pfrlis_cre						= NULL;	
	this->buff_indfrlis_cre						= NULL;											
	this->buff_inprrlis_cre						= NULL;	

	//---------------------------------------------------------------------------------
	//limpieza de punteros a buffers para las estructuras reconocidas.
	this->buff_inis_md_re						= NULL;
	this->buff_indfrlis_re						= NULL;
	this->buff_inprrlis_re						= NULL;

	//---------------------------------------------------------------------------------
	//limpieza de punteros a buffers de id de las upci candidatas.
	this->buff_upci_id_inis_md_can				= NULL;
	this->buff_upci_id_indfrlis_can				= NULL;
	this->buff_upci_id_inprrlis_can				= NULL;

	//---------------------------------------------------------------------------------
	//limpieza de punteros buffers de estructuras candidatas.
	this->buff_inis_md_id_can					= NULL;
	this->buff_indfrlis_id_can					= NULL;
	this->buff_inprrlis_id_can					= NULL;				
}
