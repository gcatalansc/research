#pragma once
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
/*
Nombre Clase : 	  ACIS_SD (Estructura de información de acción tipo 'SD').
Fecha	     :	  14:51 pm 13-06-2017.
Diseñador    :	  Gustavo Catalán Ulloa.
descripción	 :	  XXXXXXXXXXXX.
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include <deque>
#include <vector>
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
typedef		deque<deque<in>>	dedein;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//nombre de espacio UPC.
namespace UPC
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//clase ACIS_SD.
	class ACIS_SD
	{

	//atributos y miembros públicos.
	public:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//registro.
		dou		AC_RG;																		//registro de acción.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//sub-registros.				
		in		CS_SRG;																		//estado de congruencia.	
		dou		AL_SRG;																		//nivel de actividad.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//relaciones.
		dedein	RL;																			//relaciones.	

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//constructor.
		ACIS_SD();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//destructor.
		~ACIS_SD();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para crear estructura.
		vo Create(dou _ac_rg, dou _al_srg);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos para las relaciones.
		vo CreateRelation(in _rl_type, in _rl_id, in _upci_type, in _upci_id);				//creación de una relación a la estructura. 
		vo DeleteRelation(in _index);														//eliminación de una relación de la estructura.

		//-----------------------------------------------------------------------------
        //-----------------------------------------------------------------------------
        //método para diferenciar estructura.
		dou Differentiate(dou _ac_rg);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos Gets.
		in GetRelationAmount();																//obtención de la cantidad de relaciones.
		in GetRelationIndex(in _rl_type, in _rl_id, in _upci_type, in _upci_id);			//obtención del índice de una relación.
		in GetNextInputRelationS(in _rl_start_index);										//obtención del índice de la siguiente relación entrante.
		in GetNextOutputRelationS(in _rl_start_index);										//obtención del índice de la siguiente relación saliente.
		in GetPreviousInputRelationS(in _rl_start_index);									//obtención del índice de la anterior relación entrante.
		in GetPreviousOutputRelationS(in _rl_start_index);									//obtención del índice de la anterior relación saliente.		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método de seteo de la estructura.
		vo Set(dou _ac_rg, in _cs_srg, dou _al_srg, dedein _rl);
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos de limpieza de la estructura.
		vo Clean();																		
	};
}

