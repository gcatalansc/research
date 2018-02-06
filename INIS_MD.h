#pragma once
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------ 
/*
Nombre Clase : 	  INIS_MD (Estructura de informaci�n de entrada tipo 'MD').
Fecha	     :	  11:50 pm 08-02-2017.
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
	//clase INIS_MD.
	class INIS_MD
	{
	//atributos y miembros p�blicos.
	public:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//registros.
		dou		**IN_RG;																	//registro de entrada.
		dou		EV_RG;																		//registro de evaluaci�n.

		//-----------------------------------------------------------------------------
        //-----------------------------------------------------------------------------
        //dimensiones del registro de entrada.
        in      X_LENGTH;																	//largo en "x".
        in      Y_LENGTH;																	//largo en "y".

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//sub-registros.			
		in		RS_SRG;																		//estado de realidad.
		in		CS_SRG;																		//estado de congruencia.
		dou		AL_SRG;																		//nivel de actividad.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//relaciones.
		dedein	RL;																			//relaciones.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//constructor.
		INIS_MD();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//destructor.
		~INIS_MD();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para inicializar estructura.
		vo Initialize(in _x_length, in _y_length);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para crear estructura.
		vo Create(dou **_input, dou _input_evaluation, in _rs_srg, dou _al_srg);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para las relaciones.
		vo CreateRelation(in _rl_type, in _rl_id, in _upci_type, in _upci_id);				//creaci�n de una relaci�n a la estructura. 
		vo DeleteRelation(in _index);														//eliminaci�n de una relaci�n de la estructura.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para diferenciar estructura.
		dou Differentiate(dou **_in_rg);
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos Gets.
		in GetRelationAmount();																//obtenci�n de la cantidad de relaciones.
		in GetRelationIndex(in _rl_type, in _rl_id, in _upci_type, in _upci_id);			//obtenci�n del �ndice de una relaci�n.
		in GetNextDifferentialInputRelation(in _rl_start_index);							//obtenci�n del �ndice de la siguiente relaci�n diferencial entrante.
		in GetNextOutputRelationS(in _rl_start_index);										//obtenci�n del �ndice de la siguiente relaci�n saliente.
		in GetPreviousInputRelationS(in _rl_start_index);									//obtenci�n del �ndice de la anterior relaci�n entrante.
		in GetPreviousDifferentialInputRelation(in _rl_start_index);						//obtenci�n del �ndice de la anterior relaci�n diferencial entrante.
		in GetLastInputDifferentialRelationIndex();											//obtenci�n del �ndice de la �ltima relaci�n diferencial de entradas.		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo de seteo de la estructura.
		vo Set(dou **_input, dou _input_evaluation, in _rs_srg, in _cs_srg, dou _al_srg, dedein &_rl);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo de limpieza de la estructura.
		vo Clean();																	
	};
}
