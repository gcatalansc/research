#pragma once
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
/*
Nombre Clase : 	  UPCI_ARG_MDS (Estructura de argumentos para la clase UPCI_MDS).
Fecha	     :	  11:58 pm 08-02-2017.
Dise�ador    :	  Gustavo Catal�n Ulloa.
descripci�n	 :	  XXXXXXXXXXXX.
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
	//clase UPCI_ARG_MDS.
	class UPCI_ARG_MDS
	{

		//miembros p�blicos.
	public:		

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------
		//argumentos: par�metros estructurales.	
		in					inis_md_amount_allowed;											//cantidad de estructuras de entrada permitidas.
		in					acis_vs_amount_allowed;											//cantidad de estructuras de acci�n permitidas.
		in					rlis_amount_allowed;											//cantidad de estructuras de relaci�n permitidas.

		//-----------------------------------------------------------------------------
        //-----------------------------------------------------------------------------
        //argumentos: dimensiones del registro de entrada.
        in                  x_length;				                                        //largo en "x".
        in                  y_length;					                                    //largo en "y".
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//argumentos: par�metros de actividad.
		dou					default_activity_level;											//nivel de actividad por defecto.
		dou					max_activity_level_allowed;										//nivel de actividad m�ximo permitido.
		dou					min_activity_level_allowed;										//nivel de actividad m�nimo permitido.
		
		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//argumentos: umbrales.
		dou					kernel_raw_input_threshold;										//umbral de entrada cruda para control del n�cleo.
		dou					dif_raw_input_threshold;										//umbral de entrada cruda para focalizaci�n de la atenci�n (%).
		dou					str_congruence_sr_threshold;									//umbral de congruencia de registros unidimensionales (%).	
		dou					pfrlis_strength_threshold;										//umbral de fortaleza de relaci�n PFRLIS para eliminar relaci�n por N.A.
		dou					indfrlis_md_strength_threshold;									//umbral de fortaleza de relaci�n INDFRLIS_MD para eliminar relaci�n por N.A.
		dou					evaluation_threshold;											//umbral para evaluaciones.	
		dou					transition_evaluation_threshold;								//umbral para transiciones de evaluaciones.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//argumentos: tiempos para threads de limpieza y actualizaci�n.
		in					timeout_clean_is;												//tiempo de espera de limpieza de IS.
		in					timeout_update_al_is;											//tiempo de espera para actualizar niveles de actividad en IS (ms). (ms)

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//punteros a banderas para funcionalidades.
		in					*suspended_actions_maximization_flag;							//puntero a bandera para utilizar reactivaci�n acci�n suspendida con m�xima asociaci�n positiva.
		in					*structures_recognition_flag;									//puntero a bandrea para utilizar reconocimiento de estructuras.
		in					*structures_projections_flag;									//puntero a bandera para utilizar proyecci�n de estructuras.

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
		vo					*buff_upci_mds;		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------  
		//puntero a buffer para el id de la upci que puede almacenar estructuras.
		in					*buff_upci_id_storage_flag_act;
				
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para almacenar registros.
		dou					*buff_in_rg;													//puntero a buffer para registro de entrada.
		dou					*buff_ev_rg;													//puntero a buffer para registro de evaluaci�n de entrada.
		st					*buff_ac_rg;													//puntero a buffer para registro de acci�n.
		dou					*buff_in_dif_rg;												//puntero a buffer para registro de diferencia de entradas.
		dou					*buff_in_pro_rg;												//puntero a buffer para registro de proporci�n de diferencia de entradas.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//punteros a buffers para estructura con evaluaci�n m�xima.
		BUFF_STR_II			*buff_str_max_eval;												//puntero a buffer para la estructura INIS_MD con m�xima evaluaci�n
		dou					*buff_max_evaluation;											//puntero a buffer para la m�xima evaluaci�n.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//punteros a buffers para estructura con nivel de actividad m�ximo.
		BUFF_STR_IIT		*buff_str_max_al;												//puntero a buffer para la estructura con nivel de actividad m�ximo.
		dou					*buff_max_activity_level;										//puntero a buffer para el m�ximo nivel de actividad.

		//----------------------------------------------------------------------------- 
		//-----------------------------------------------------------------------------  
		//punteros a buffers para estructura con fortaleza de la relaci�n m�ximo.
		BUFF_STR_IIT		*buff_str_max_rs;												//puntero a buffer para la estructura con fortaleza de la relaci�n m�ximo.
		dou					*buff_max_relation_strength;									//puntero a buffer para el m�ximo fortaleza de la relaci�n.	

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//punteros a buffers para las estructuras activadas.
		BUFF_STR_IIT		*buff_str_activated;											//puntero a buffer para las estructuras activadas.
		BUFF_STR_II			*buff_inis_md_activated;										//puntero a buffer para las estructuras INIS_MD activadas.
		BUFF_STR_II			*buff_acis_vs_activated;										//puntero a buffer para las estructuras ACIS_VS activadas.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//puntero a buffer para las estructuras de acci�n ejecutadas.
		BUFF_STR_II			*buff_execute_acis_vs;
		
		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//puntero a buffer para �ndice de la relaci�n utilizada en flujo por reconocimiento.
		in					*buff_rl_index_used_in_recognition;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para estructuras en estado de suspensi�n.		
		deBUFF_STR_II		*buff_inis_md_sus;												//puntero a buffer para las estructuras INIS_MD suspendidas.
		deBUFF_STR_II		*buff_acis_vs_sus;												//puntero a buffer para las estructuras ACIS_VS suspendidas.
		deBUFF_STR_II		*buff_pfrlis_sus;												//puntero a buffer para las estructuras PFRLIS suspendidas.
		deBUFF_STR_II		*buff_indfrlis_md_sus;											//puntero a buffer para las estructuras INDFRLIS_MD suspendidas.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffers para las estructuras creadas.
		BUFF_STR_II			*buff_inis_md_cre;												//puntero a buffer para estructuras INIS_MD creadas.
		BUFF_STR_II			*buff_acis_vs_cre;												//puntero a buffer para estructuras ACIS_VS creadas.
		BUFF_STR_II			*buff_pfrlis_cre;												//puntero a buffer para estructuras PFRLIS creadas.
		BUFF_STR_II			*buff_indfrlis_md_cre;											//puntero a buffer para estructuras INDFRLIS_MD creadas.
		BUFF_STR_II			*buff_inprrlis_md_cre;											//puntero a buffer para estructuras INPRRLIS_MD creadas.

		//-----------------------------------------------------------------------------
		//----------------------------------------------------------------------------- 
		//punteros a buffers para las estructuras reconocidas.
		BUFF_STR_II			*buff_inis_md_re;												//puntero a buffer para estructura reconocida INIS_MD.
		BUFF_STR_II			*buff_acis_vs_re;												//puntero a buffer para estructura reconocida ACIS_VS.
		BUFF_STR_II			*buff_indfrlis_md_re;											//puntero a buffer para estructura reconocida INDFRLIS_MD.
		BUFF_STR_II			*buff_inprrlis_md_re;											//puntero a buffer para estructura reconocida INPRRLIS_MD.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//argumento: punteros a buffers para los id de las upci candidatas.
		dedein				*buff_upci_id_inis_md_can;										//puntero a buffer de id de las upci candidatas para INIS_MD.
		dedein				*buff_upci_id_acis_vs_can;										//puntero a buffer de id de las upci candidatas para ACIS_VS.
		dedein				*buff_upci_id_indfrlis_md_can;									//puntero a buffer de id de las upci candidatas para INDFRLIS_MD.
		dedein				*buff_upci_id_inprrlis_md_can;									//puntero a buffer de id de las upci candidatas para INPRRLIS_MD.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//punteros a buffer de estructuras candidatas externas
		dededein			*buff_inis_md_id_can;											//puntero a buffer de ids de estructuras tipo INIS_MD candidatas.
		dededein			*buff_acis_vs_id_can;											//puntero a buffer de ids de estructuras tipo ACIS_VS candidatas.
		dededein			*buff_indfrlis_md_id_can;										//puntero a buffer de ids de estructuras tipo INDFRLIS_MD candidatas.
		dededein			*buff_inprrlis_md_id_can;										//puntero a buffer de ids de estructuras tipo INPRRLIS_MD candidatas.
		
		//m�todos p�blicos.
	public:

		//-----------------------------------------------------------------------------
		//m�todos constructor.
		UPCI_ARG_MDS();
		UPCI_ARG_MDS(in		_inis_md_amount_allowed,
				     in		_acis_vs_amount_allowed,
					 in		_rlis_amount_allowed,
					 in     _x_length,
                     in     _y_length,
					 dou	_default_activity_level,
					 dou	_max_activity_level_allowed,
					 dou	_min_activity_level_allowed,	
					 dou	_kernel_raw_input_threshold,
					 dou	_dif_raw_input_threshold,
					 dou	_str_congruence_sr_threshold,
					 dou	_pfrlis_strength_threshold,
					 dou	_indfrlis_md_strength_threshold,
					 dou	_evaluation_threshold,
					 dou	_transition_evaluation_threshold,
					 in		_timeout_clean_is,
					 in		_timeout_update_al_is);

		//-----------------------------------------------------------------------------
		//destructor.
		~UPCI_ARG_MDS();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo de inicializaci�n.
		vo Initialize(in	_inis_md_amount_allowed,
					  in	_acis_vs_amount_allowed,
					  in	_rlis_amount_allowed,
					  in    _x_length,
					  in    _y_length,
	  				  dou	_default_activity_level,
		 			  dou	_max_activity_level_allowed,
					  dou	_min_activity_level_allowed,	
					  dou	_kernel_raw_input_threshold,
					  dou	_dif_raw_input_threshold,
					  dou	_str_congruence_sr_threshold,
					  dou	_pfrlis_strength_threshold,
					  dou	_indfrlis_md_strength_threshold,
					  dou	_evaluation_threshold,
					  dou	_transition_evaluation_threshold,
					  in	_timeout_clean_is,
					  in	_timeout_update_al_is);
		
		//-----------------------------------------------------------------------------
		//m�todo para Setear punteros a buffers de gupci.
		vo	SetPtrBuff(in					*_suspended_actions_maximization_flag,
					   in					*_structures_recognition_flag,
					   in					*_structures_projections_flag,
					   in					*_close_active_threads_flag,
					   in					*_pause_active_threads_flag,
					   in					*_gupci_id,
					   vo					*_buff_upci_mds,
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
					   BUFF_STR_II			*_buff_inis_md_activated,
					   BUFF_STR_II			*_buff_acis_vs_activated,
					   BUFF_STR_II			*_buff_execute_acis_vs,
					   in					*_buff_rl_index_used_in_recognition,
					   deBUFF_STR_II		*_buff_inis_md_sus,
					   deBUFF_STR_II		*_buff_acis_vs_sus,
					   deBUFF_STR_II		*_buff_pfrlis_sus,
					   deBUFF_STR_II		*_buff_indfrlis_md_sus,
					   BUFF_STR_II			*_buff_inis_md_cre,
					   BUFF_STR_II			*_buff_acis_vs_cre,
					   BUFF_STR_II			*_buff_pfrlis_cre,
					   BUFF_STR_II			*_buff_indfrlis_md_cre,
					   BUFF_STR_II			*_buff_inprrlis_md_cre,	
					   BUFF_STR_II			*_buff_inis_md_re,
					   BUFF_STR_II			*_buff_acis_vs_re,
					   BUFF_STR_II			*_buff_indfrlis_md_re,
					   BUFF_STR_II			*_buff_inprrlis_md_re,
					   dedein				*_buff_upci_id_inis_md_can,
					   dedein				*_buff_upci_id_acis_vs_can,
					   dedein				*_buff_upci_id_indfrlis_md_can,
					   dedein				*_buff_upci_id_inprrlis_md_can,
					   dededein				*_buff_inis_md_can,
					   dededein				*_buff_acis_vs_can,
					   dededein				*_buff_indfrlis_md_can,
					   dededein				*_buff_inprrlis_md_can);

		//-----------------------------------------------------------------------------
		//m�todo para limpiar UPCI_ARG_MDS.
		vo  Clean();
	};
}

