#pragma once
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
/*
Nombre Clase : 	  ACIS_VS (Estructura de informaci�n de acci�n tipo 'VS').
Fecha	     :	  14:51 pm 13-06-2017.
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
typedef		string				st;
typedef		deque<deque<in>>	dedein;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//nombre de espacio UPC.
namespace UPC
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//clase ACIS_VS.
	class ACIS_VS
	{

	//atributos y miembros p�blicos.
	public:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//registro.
		st		AC_RG;																		//registro de acci�n.

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
		ACIS_VS();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//destructor.
		~ACIS_VS();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para crear estructura.
		vo Create(st _ac_rg, dou _al_srg);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos para las relaciones.
		vo CreateRelation(in _rl_type, in _rl_id, in _upci_type, in _upci_id);				//creaci�n de una relaci�n a la estructura. 
		vo DeleteRelation(in _index);														//eliminaci�n de una relaci�n de la estructura.

		//-----------------------------------------------------------------------------
        //-----------------------------------------------------------------------------
        //m�todo para diferenciar estructura.
		dou Differentiate(st *_ac_rg);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos Gets.
		in GetRelationAmount();																//obtenci�n de la cantidad de relaciones.
		in GetRelationIndex(in _rl_type, in _rl_id, in _upci_type, in _upci_id);			//obtenci�n del �ndice de una relaci�n.
		in GetNextInputRelationS(in _rl_start_index);										//obtenci�n del �ndice de la siguiente relaci�n entrante.
		in GetNextOutputRelationS(in _rl_start_index);										//obtenci�n del �ndice de la siguiente relaci�n saliente.
		in GetPreviousInputRelationS(in _rl_start_index);									//obtenci�n del �ndice de la anterior relaci�n entrante.
		in GetPreviousOutputRelationS(in _rl_start_index);									//obtenci�n del �ndice de la anterior relaci�n saliente.		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo de seteo de la estructura.
		vo Set(st _ac_rg, in _cs_srg, dou _al_srg, dedein _rl);
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos de limpieza de la estructura.
		vo Clean();																		
	};
}

