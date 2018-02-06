#pragma once
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
/*
Nombre Clase : 	  INDFRLIS_SD (Estructura de información de relación de flujo diferencial de entradas tipo 'SD').
Fecha	     :	  15:44 pm 15-04-2015.
Diseñador    :	  Gustavo Catalán Ulloa.
descripción	 :	  XXXXXXXXXXXX.
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include <deque>
#include "DEFINITIONS.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//espacio de nombres.
using namespace std;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//tipos.
typedef 	void				vo;
typedef		int					in;
typedef		double				dou;
typedef		deque<deque<int>>	dedein;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//nombre de espacio UPC.
namespace UPC
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//clase INDFRLIS_SD.
	class INDFRLIS_SD
	{

	//atributos y miembros públicos.
	public:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//registros.
		dou		IN_DIF_RG;																	//diferencia entre registros de entrada.
		dou		EV_DIF_RG;																	//diferencia entre registros de evaluación.
		in		STR1_ID_RG;																	//id estructura n°1.
		in		STR2_ID_RG;																	//id estructura n°2.		
		in		UPCI_ID_STR1_RG;															//id upci de estructura n°1.
		in		UPCI_ID_STR2_RG;															//id upci de estructura n°2.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//sub-registros.
		in		CS_SRG;																		//estado de congruencia.
		dou		RS_SRG;																		//fortaleza de la relación.
		dou		AL_SRG;																		//nivel de actividad.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//relaciones.
		dedein	RL;																			//relaciones.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//constructor.
		INDFRLIS_SD();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//destructor.
		~INDFRLIS_SD();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para crear estructura.
		vo Create(dou &_in_dif_rg, dou _ev_dif, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2, dou _rs_srg, dou _al_srg);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos para las relaciones.
		vo CreateRelation(in _rl_type, in _rl_id, in _upci_type, in _upci_id);				//creación de una relación a la estructura. 
		vo DeleteRelation(in _index);														//eliminación de una relación de la estructura.

		//-----------------------------------------------------------------------------
        //-----------------------------------------------------------------------------
        //método para diferenciar estructura.
		dou Differentiate(dou _in_dif_rg);
 
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos Gets.
		in GetRelationAmount();																//obtención de la cantidad de relaciones.
		in GetRelationIndex(in _rl_type, in _rl_id, in _upci_type, in _upci_id);			//obtención del índice de una relación.
		in GetNextOutputRelationS(in _rl_start_index);										//obtención del índice de la siguiente relación PFRLIS saliente.
		in GetPreviousInputRelationS(in _rl_start_index);									//obtención del índice de la anterior relación PFRLIS entrante.		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método de seteo de la estructura.
		vo Set(dou _in_dif_rg, dou _ev_dif_rg, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2, in _cs_srg, dou _rs_srg, dou _al_srg, dedein &_rl);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para limpieza de la estructura.
		vo Clean();																	
		
	};
}

