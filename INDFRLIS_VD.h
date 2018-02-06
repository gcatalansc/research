#pragma once
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
/*
Nombre Clase : 	  INDFRLIS_VD (Estructura de informaci�n de relaci�n de flujo diferencial de entradas tipo 'VD').
Fecha	     :	  15:44 pm 15-04-2015.
Dise�ador    :	  Gustavo Catal�n Ulloa.
descripci�n	 :	  XXXXXXXXXXXX.
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
	//clase INDFRLIS_VD.
	class INDFRLIS_VD
	{

	//atributos y miembros p�blicos.
	public:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//registros.
		dou		*IN_DIF_RG;																	//diferencia entre registros de entrada.
		dou		EV_DIF_RG;																	//diferencia entre registros de evaluaci�n.
		in		STR1_ID_RG;																	//id estructura n�1.
		in		STR2_ID_RG;																	//id estructura n�2.		
		in		UPCI_ID_STR1_RG;															//id upci de estructura n�1.
		in		UPCI_ID_STR2_RG;															//id upci de estructura n�2.

		//-----------------------------------------------------------------------------
        //-----------------------------------------------------------------------------
        //dimensiones del registro de entrada.
        in      X_LENGTH;																	//largo en "x".

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//sub-registros.
		in		CS_SRG;																		//estado de congruencia.
		dou		RS_SRG;																		//fortaleza de la relaci�n.
		dou		AL_SRG;																		//nivel de actividad.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//relaciones.
		dedein	RL;																			//relaciones.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//constructor.
		INDFRLIS_VD();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//destructor.
		~INDFRLIS_VD();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para inicializar estructura.
		vo Initialize(in _x_length);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para crear estructura.
		vo Create(dou *_in_dif_rg, dou _ev_dif_rg, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2, dou _rs_srg, dou _al_srg);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para las relaciones.
		vo CreateRelation(in _rl_type, in _rl_id, in _upci_type, in _upci_id);				//creaci�n de una relaci�n a la estructura. 
		vo DeleteRelation(in _index);														//eliminaci�n de una relaci�n de la estructura.

		//-----------------------------------------------------------------------------
        //-----------------------------------------------------------------------------
        //m�todo para diferenciar estructura.
		dou Differentiate(dou *_in_dif_rg);
 
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos Gets.
		in GetRelationAmount();																//obtenci�n de la cantidad de relaciones.
		in GetRelationIndex(in _rl_type, in _rl_id, in _upci_type, in _upci_id);			//obtenci�n del �ndice de una relaci�n.
		in GetNextOutputRelationS(in _rl_start_index);										//obtenci�n del �ndice de la siguiente relaci�n PFRLIS saliente.
		in GetPreviousInputRelationS(in _rl_start_index);									//obtenci�n del �ndice de la anterior relaci�n PFRLIS entrante.		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo de seteo de la estructura.
		vo Set(dou *_in_dif_rg, dou _ev_dif_rg, in _x_length, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2, in _cs_srg, dou _rs_srg, dou _al_srg, dedein &_rl);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para limpieza de la estructura.
		vo Clean();																	
		
	};
}

