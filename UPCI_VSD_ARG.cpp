//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
Nombre Clase : 	  UPCI_ARG_VSD (Estructura de argumentos para la clase UPCI_VSD).
Fecha	     :	  11:58 pm 08-02-2017.
Diseñador    :	  Gustavo Catalán Ulloa.
descripción	 :	  XXXXXXXXXXXX.
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include "UPCI_ARG_VSD.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: constructor 1.
UPCI_ARG_VSD::UPCI_ARG_VSD()
{

}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: constructor 2.
UPCI_ARG_VSD::UPCI_ARG_VSD(in	_inis_vs_amount_allowed,
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
						   in	_timeout_update_al_is)
{
	//---------------------------------------------------------------------------------
	//inicialización de argumentos: parámetros estructurales.
	this->inis_vs_amount_allowed			= _inis_vs_amount_allowed;								//cantidad de estructuras inis_vs permitidas.
	this->acis_sd_amount_allowed			= _acis_sd_amount_allowed;								//cantidad de estructuras acis_sd permitidas.
	this->rlis_amount_allowed				= _rlis_amount_allowed;									//cantidad de estructuras rlis permitidas.
	
	//---------------------------------------------------------------------------------
	//inicialización de argumentos: parámetros de actividad.
	this->default_activity_level			= _default_activity_level;								//nivel de actividad por defecto.
	this->max_activity_level_allowed		= _max_activity_level_allowed;							//nivel de actividad máximo permitido.
	this->min_activity_level_allowed		= _min_activity_level_allowed;							//nivel de actividad mínimo permitido.

	//---------------------------------------------------------------------------------
	//inicialización de argumentos: umbrales.
	this->kernel_raw_input_threshold		= _kernel_raw_input_threshold;							//umbral de entrada cruda para control del núcleo.
	this->dif_raw_input_threshold			= _dif_raw_input_threshold;								//umbral de entrada cruda para focalización de la atención (%).
	this->str_congruence_sr_threshold		= _str_congruence_sr_threshold;							//umbral de congruencia de registros unidimensionales (%).	
	this->pfrlis_strength_threshold			= _pfrlis_strength_threshold;							//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
	this->indfrlis_vs_strength_threshold	= _indfrlis_vs_strength_threshold;						//umbral de fortaleza de relación INDFRLIS_VS para eliminar relación por N.A.
	this->transition_evaluation_threshold	= _transition_evaluation_threshold;						//umbral para transición de evaluaciones.	

	//---------------------------------------------------------------------------------
	//inicialización de argumentos: tiempos para threads de limpieza y actualización.
	this->timeout_clean_is					= _timeout_clean_is;									//tiempo de espera de limpieza de IS.
	this->timeout_update_al_is				= _timeout_update_al_is;								//tiempo de espera para actualizar niveles de actividad en IS (ms). (ms)
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: destructor.
UPCI_ARG_VSD::~UPCI_ARG_VSD()
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
vo  UPCI_ARG_VSD::Initialize(in		_inis_vs_amount_allowed,
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
							 in		_timeout_update_al_is)
{
	//---------------------------------------------------------------------------------
	//inicialización de argumentos: parámetros estructurales.
	this->inis_vs_amount_allowed			= _inis_vs_amount_allowed;								//cantidad de estructuras inis_vs permitidas.
	this->acis_sd_amount_allowed			= _acis_sd_amount_allowed;								//cantidad de estructuras acis_sd permitidas.
	this->rlis_amount_allowed				= _rlis_amount_allowed;									//cantidad de estructuras rlis permitidas.
	
	//---------------------------------------------------------------------------------
	//inicialización de argumentos: parámetros de actividad.
	this->default_activity_level			= _default_activity_level;								//nivel de actividad por defecto.
	this->max_activity_level_allowed		= _max_activity_level_allowed;							//nivel de actividad máximo permitido.
	this->min_activity_level_allowed		= _min_activity_level_allowed;							//nivel de actividad mínimo permitido.

	//---------------------------------------------------------------------------------
	//inicialización de argumentos: umbrales.
	this->kernel_raw_input_threshold		= _kernel_raw_input_threshold;							//umbral de entrada cruda para control del núcleo.
	this->dif_raw_input_threshold			= _dif_raw_input_threshold;								//umbral de entrada cruda para focalización de la atención (%).
	this->str_congruence_sr_threshold		= _str_congruence_sr_threshold;							//umbral de congruencia de registros unidimensionales (%).	
	this->pfrlis_strength_threshold			= _pfrlis_strength_threshold;							//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
	this->indfrlis_vs_strength_threshold	= _indfrlis_vs_strength_threshold;						//umbral de fortaleza de relación INDFRLIS_VS para eliminar relación por N.A.
	this->transition_evaluation_threshold	= _transition_evaluation_threshold;						//umbral para transición de evaluaciones.	

	//---------------------------------------------------------------------------------
	//inicialización de argumentos: tiempos para threads de limpieza y actualización.
	this->timeout_clean_is					= _timeout_clean_is;									//tiempo de espera de limpieza de IS.
	this->timeout_update_al_is				= _timeout_update_al_is;								//tiempo de espera para actualizar niveles de actividad en IS (ms). (ms)
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: //método para setear punteros a buffers de gupci.
vo	UPCI_ARG_VSD::SetPtrBuff(in					*_suspended_actions_maximization_flag,
							 in					*_structures_recognition_flag,
							 in					*_structures_projections_flag, 
							 in					*_close_active_threads_flag,
							 in					*_pause_active_threads_flag,
							 in					*_gupci_id,
						     vo					*_buff_upci_vsd,
						     in					*_buff_upci_id_storage_flag_act,
						     dou				*_buff_in_rg,
							 dou				*_buff_ev_rg,
							 st					*_buff_ac_rg,
							 dou				*_buff_in_dif_rg,
							 dou				*_buff_in_pro_rg,
						     BUFF_STR_II		*_buff_str_max_eval,
						     dou				*_buff_max_evaluation,
						     BUFF_STR_IIT		*_buff_str_max_al,
						     dou				*_buff_max_activity_level,	
						     BUFF_STR_IIT		*_buff_str_max_rs,
						     dou				*_buff_max_relation_strength,	
						     BUFF_STR_IIT		*_buff_str_activated,
							 BUFF_STR_II		*_buff_inis_vs_activated,
							 BUFF_STR_II		*_buff_acis_sd_activated,
							 BUFF_STR_II		*_buff_execute_acis_sd,
							 in					*_buff_rl_index_used_in_recognition,
						     deBUFF_STR_II		*_buff_inis_vs_sus,
							 deBUFF_STR_II		*_buff_acis_sd_sus,
						     deBUFF_STR_II		*_buff_pfrlis_sus,
						     deBUFF_STR_II		*_buff_indfrlis_vs_sus,
						     BUFF_STR_II		*_buff_inis_vs_cre,
							 BUFF_STR_II		*_buff_acis_sd_cre,
							 BUFF_STR_II		*_buff_pfrlis_cre,
							 BUFF_STR_II		*_buff_indfrlis_vs_cre,
							 BUFF_STR_II		*_buff_inprrlis_vs_cre,
							 BUFF_STR_II		*_buff_inis_vs_re,
						     BUFF_STR_II		*_buff_acis_sd_re,
						     BUFF_STR_II		*_buff_indfrlis_vs_re,
						     BUFF_STR_II		*_buff_inprrlis_vs_re,
						     dedein				*_buff_upci_id_inis_vs_can,
						     dedein				*_buff_upci_id_acis_sd_can,
						     dedein				*_buff_upci_id_indfrlis_vs_can,
						     dedein				*_buff_upci_id_inprrlis_vs_can,
						     dededein			*_buff_inis_vs_can,
						     dededein			*_buff_acis_sd_can,
						     dededein			*_buff_indfrlis_vs_can,
						     dededein			*_buff_inprrlis_vs_can)
 {
	//--------------------------------------------------------------------------------- 
	//seteo de punteros a banderas para funcionalidades.
	this->suspended_actions_maximization_flag	= _suspended_actions_maximization_flag;
	this->structures_recognition_flag			= _structures_recognition_flag;
	this->structures_projections_flag			= _structures_projections_flag;

	//--------------------------------------------------------------------------------- 
	//seteo de punteros a banderas para threads activos.
	this->close_active_threads_flag				= _close_active_threads_flag;										
	this->pause_active_threads_flag				= _pause_active_threads_flag;										

	//--------------------------------------------------------------------------------- 
	//seteo de puntero a id de la gupci.
	this->gupci_id								= _gupci_id;

	//---------------------------------------------------------------------------------
	//seteo de puntero para las upci.
	this->buff_upci_vsd							= _buff_upci_vsd;

	//---------------------------------------------------------------------------------  
	//seteo de puntero a buffer para el id de la upci que puede almacenar estructuras.
	this->buff_upci_id_storage_flag_act			= _buff_upci_id_storage_flag_act;

	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para almacenar registros.
	this->buff_in_rg							= _buff_in_rg;
	this->buff_ev_rg							= _buff_ev_rg;
	this->buff_ac_rg							= _buff_ac_rg;
	this->buff_in_dif_rg						= _buff_in_dif_rg;
	this->buff_in_pro_rg						= _buff_in_pro_rg;

	//--------------------------------------------------------------------------------- 
	//seteo de punteros a buffers para estructura con evaluación máxima.
	this->buff_str_max_eval						= _buff_str_max_eval;
	this->buff_max_evaluation					= _buff_max_evaluation;											

	//--------------------------------------------------------------------------------- 
	//seteo de punteros a buffers para estructura con nivel de actividad máximo.
	this->buff_str_max_al						= _buff_str_max_al;
	this->buff_max_activity_level				= _buff_max_activity_level;		

	//--------------------------------------------------------------------------------- 
	//seteo de punteros a buffers para estructura con fortaleza de la relación máximo.
	this->buff_str_max_rs						= _buff_str_max_rs;
	this->buff_max_relation_strength			= _buff_max_relation_strength;	

	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para las estructuras activadas.
	this->buff_str_activated					= _buff_str_activated;
	this->buff_inis_vs_activated				= _buff_inis_vs_activated;
	this->buff_acis_sd_activated				= _buff_acis_sd_activated;

	//---------------------------------------------------------------------------------
	//puntero a buffer para las estructuras de acción ejecutadas.
	this->buff_execute_acis_sd					= _buff_execute_acis_sd;

	//---------------------------------------------------------------------------------
	//puntero a buffer para índice de la relación utilizada en flujo por reconocimiento.
	this->buff_rl_index_used_in_recognition		= _buff_rl_index_used_in_recognition;

	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para estructuras en estado de suspensión.
	this->buff_inis_vs_sus						= _buff_inis_vs_sus;
	this->buff_acis_sd_sus						= _buff_acis_sd_sus;
	this->buff_pfrlis_sus						= _buff_pfrlis_sus;
	this->buff_indfrlis_vs_sus						= _buff_indfrlis_vs_sus;

	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para las estructuras creadas.
	this->buff_inis_vs_cre						= _buff_inis_vs_cre;
	this->buff_acis_sd_cre						= _buff_acis_sd_cre;	
	this->buff_pfrlis_cre						= _buff_pfrlis_cre;	
	this->buff_indfrlis_vs_cre					= _buff_indfrlis_vs_cre;										
	this->buff_inprrlis_vs_cre					= _buff_inprrlis_vs_cre;

	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers para las estructuras reconocidas.
	this->buff_inis_vs_re						= _buff_inis_vs_re;
	this->buff_acis_sd_re						= _buff_acis_sd_re;
	this->buff_indfrlis_vs_re					= _buff_indfrlis_vs_re;
	this->buff_inprrlis_vs_re					= _buff_inprrlis_vs_re;

	//---------------------------------------------------------------------------------
	//seteo de punteros a buffers de id de las upci candidatas.
	this->buff_upci_id_inis_vs_can				= _buff_upci_id_inis_vs_can;
	this->buff_upci_id_acis_sd_can				= _buff_upci_id_acis_sd_can;
	this->buff_upci_id_indfrlis_vs_can			= _buff_upci_id_indfrlis_vs_can;
	this->buff_upci_id_inprrlis_vs_can			= _buff_upci_id_inprrlis_vs_can;

	//---------------------------------------------------------------------------------
	//seteo de punteros buffers de estructuras candidatas.
	this->buff_inis_vs_id_can					= _buff_inis_vs_can;
	this->buff_acis_sd_id_can					= _buff_acis_sd_can;
	this->buff_indfrlis_vs_id_can				= _buff_indfrlis_vs_can;
	this->buff_inprrlis_vs_id_can				= _buff_inprrlis_vs_can;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para Clean UPCI_ARG_VSD.
vo  UPCI_ARG_VSD::Clean()
{
	//---------------------------------------------------------------------------------
	//limpieza de argumentos: parámetros estructurales.
	this->inis_vs_amount_allowed				= NULL;								
	this->acis_sd_amount_allowed				= NULL;								
	this->rlis_amount_allowed					= NULL;									
	
	//---------------------------------------------------------------------------------
	//limpieza de argumentos: parámetros de actividad.
	this->default_activity_level				= NULL;								
	this->max_activity_level_allowed			= NULL;									
	this->min_activity_level_allowed			= NULL;									

	//---------------------------------------------------------------------------------
	//limpieza de argumentos: umbrales.
	this->kernel_raw_input_threshold			= NULL;							
	this->dif_raw_input_threshold				= NULL;								
	this->str_congruence_sr_threshold			= NULL;								
	this->pfrlis_strength_threshold				= NULL;							
	this->indfrlis_vs_strength_threshold		= NULL;
	this->evaluation_threshold					= NULL;
	this->transition_evaluation_threshold		= NULL;							

	//---------------------------------------------------------------------------------
	//limpieza de argumentos: tiempos para threads de limpieza y actualización.
	this->timeout_clean_is						= NULL;									
	this->timeout_update_al_is					= NULL;		

	//--------------------------------------------------------------------------------- 
	//limpieza de punteros a banderas para funcionalidades.
	this->suspended_actions_maximization_flag	= NULL;
	this->structures_recognition_flag			= NULL;
	this->structures_projections_flag			= NULL;

	//--------------------------------------------------------------------------------- 
	//seteo de punteros a banderas para threads activos.
	this->close_active_threads_flag				= NULL;										
	this->pause_active_threads_flag				= NULL;

	//--------------------------------------------------------------------------------- 
	//limpieza de puntero a id de la gupci.
	this->gupci_id								= NULL;

	//---------------------------------------------------------------------------------
	//limpieza de puntero para las upci.
	this->buff_upci_vsd							= NULL;

	//---------------------------------------------------------------------------------  
	//limpieza de puntero a buffer para el id de la upci que puede almacenar estructuras.
	this->buff_upci_id_storage_flag_act			= NULL;

	//---------------------------------------------------------------------------------
	//limpieza de punteros a buffers para almacenar registros.
	this->buff_in_rg							= NULL;
	this->buff_ev_rg							= NULL;
	this->buff_ac_rg							= NULL;
	this->buff_in_dif_rg						= NULL;
	this->buff_in_pro_rg						= NULL;

	//--------------------------------------------------------------------------------- 
	//limpieza de punteros a buffers para estructura con evaluación máxima.
	this->buff_str_max_eval						= NULL;
	this->buff_max_evaluation					= NULL;											

	//--------------------------------------------------------------------------------- 
	//limpieza de punteros a buffers para estructura con nivel de actividad máximo.
	this->buff_str_max_al						= NULL;
	this->buff_max_activity_level				= NULL;		

	//--------------------------------------------------------------------------------- 
	//limpieza de punteros a buffers para estructura con fortaleza de la relación máximo.
	this->buff_str_max_rs						= NULL;
	this->buff_max_relation_strength			= NULL;	

	//---------------------------------------------------------------------------------
	//limpieza de punteros a buffers para las estructuras activadas.
	this->buff_str_activated					= NULL;
	this->buff_inis_vs_activated				= NULL;
	this->buff_acis_sd_activated				= NULL;
	//---------------------------------------------------------------------------------
	//limpieza de puntero a buffer para las estructuras de acción ejecutadas.
	this->buff_execute_acis_sd					= NULL;

	//---------------------------------------------------------------------------------
	//limpieza de puntero a buffer para índice de la relación utilizada en flujo por reconocimiento.
	this->buff_rl_index_used_in_recognition		= NULL;

	//---------------------------------------------------------------------------------
	//limpieza de punteros a buffers para las estructuras en estado de suspensión.
	this->buff_inis_vs_sus						= NULL;	
	this->buff_acis_sd_sus						= NULL;
	this->buff_pfrlis_sus						= NULL;
	this->buff_indfrlis_vs_sus						= NULL;

	//---------------------------------------------------------------------------------
	//limpieza de punteros a buffers para las estructuras creadas.
	this->buff_inis_vs_cre						= NULL;
	this->buff_acis_sd_cre						= NULL;	
	this->buff_pfrlis_cre						= NULL;	
	this->buff_indfrlis_vs_cre					= NULL;											
	this->buff_inprrlis_vs_cre					= NULL;	

	//---------------------------------------------------------------------------------
	//limpieza de punteros a buffers para las estructuras reconocidas.
	this->buff_inis_vs_re						= NULL;
	this->buff_acis_sd_re						= NULL;
	this->buff_indfrlis_vs_re					= NULL;
	this->buff_inprrlis_vs_re					= NULL;

	//---------------------------------------------------------------------------------
	//limpieza de punteros a buffers de id de las upci candidatas.
	this->buff_upci_id_inis_vs_can				= NULL;
	this->buff_upci_id_acis_sd_can				= NULL;
	this->buff_upci_id_indfrlis_vs_can			= NULL;
	this->buff_upci_id_inprrlis_vs_can			= NULL;

	//---------------------------------------------------------------------------------
	//limpieza de punteros buffers de estructuras candidatas.
	this->buff_inis_vs_id_can					= NULL;
	this->buff_acis_sd_id_can					= NULL;
	this->buff_indfrlis_vs_id_can				= NULL;
	this->buff_inprrlis_vs_id_can				= NULL;							
}
