#pragma once
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------ 
/*
Nombre Clase : 	  INIS_MD (Estructura de información de entrada tipo 'MD').
Fecha	     :	  11:50 pm 08-02-2017.
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
	//clase INIS_MD.
	class INIS_MD
	{
	//atributos y miembros públicos.
	public:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//registros.
		dou		**IN_RG;																	//registro de entrada.
		dou		EV_RG;																		//registro de evaluación.

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
		//método para inicializar estructura.
		vo Initialize(in _x_length, in _y_length);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para crear estructura.
		vo Create(dou **_input, dou _input_evaluation, in _rs_srg, dou _al_srg);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos para las relaciones.
		vo CreateRelation(in _rl_type, in _rl_id, in _upci_type, in _upci_id);				//creación de una relación a la estructura. 
		vo DeleteRelation(in _index);														//eliminación de una relación de la estructura.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para diferenciar estructura.
		dou Differentiate(dou **_in_rg);
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos Gets.
		in GetRelationAmount();																//obtención de la cantidad de relaciones.
		in GetRelationIndex(in _rl_type, in _rl_id, in _upci_type, in _upci_id);			//obtención del índice de una relación.
		in GetNextDifferentialInputRelation(in _rl_start_index);							//obtención del índice de la siguiente relación diferencial entrante.
		in GetNextOutputRelationS(in _rl_start_index);										//obtención del índice de la siguiente relación saliente.
		in GetPreviousInputRelationS(in _rl_start_index);									//obtención del índice de la anterior relación entrante.
		in GetPreviousDifferentialInputRelation(in _rl_start_index);						//obtención del índice de la anterior relación diferencial entrante.
		in GetLastInputDifferentialRelationIndex();											//obtención del índice de la última relación diferencial de entradas.		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método de seteo de la estructura.
		vo Set(dou **_input, dou _input_evaluation, in _rs_srg, in _cs_srg, dou _al_srg, dedein &_rl);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método de limpieza de la estructura.
		vo Clean();																	
	};
}
