//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
/*
Nombre Clase : 	  INDFRLIS_SD (Estructura de informaci�n de relaci�n de flujo diferencial de entradas tipo 'SD').
Fecha	     :	  15:44 pm 15-04-2015.
Dise�ador    :	  Gustavo Catal�n Ulloa.
descripci�n	 :	  XXXXXXXXXXXX.
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include "INDFRLIS_SD.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//espacio de nombres.
using namespace UPC;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: constructor.
INDFRLIS_SD::INDFRLIS_SD()
{
	//---------------------------------------------------------------------------------
	//inicializaci�n de registros.
	this->IN_DIF_RG			= -1;															//diferencia entre registros de entrada.
	this->EV_DIF_RG			= -1;															//diferencia entre registros de evaluaci�n.
	this->STR1_ID_RG		= -1;															//id estructura n�1.
	this->STR2_ID_RG		= -1;															//id estructura n�2.
	this->UPCI_ID_STR1_RG	= -1;															//id upci de estructura n�1.
	this->UPCI_ID_STR2_RG	= -1;															//id upci de estructura n�2.

	//---------------------------------------------------------------------------------
	//inicializaci�n de sub-registros.
	this->CS_SRG			= -1;															//estado de congruencia.
	this->RS_SRG			= -1;															//fortaleza de la relaci�n.
	this->AL_SRG			= -1;															//nivel de actividad.	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: destructor.
INDFRLIS_SD::~INDFRLIS_SD()
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
//#1: m�todo para crear estructura.
vo INDFRLIS_SD::Create(dou &_in_dif_rg, dou _ev_dif_rg, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2, dou _rs_srg, dou _al_srg)
{
	//---------------------------------------------------------------------------------
	//inicializaci�n de registros.
	this->IN_DIF_RG			= _in_dif_rg;													//diferencia entre registros de entrada;
	this->EV_DIF_RG			= _ev_dif_rg;													//diferencia entre registros de evaluaci�n.
	this->STR1_ID_RG		= _str1_id;														//id estructura n�1.
	this->STR2_ID_RG		= _str2_id;														//id estructura n�2.
	this->UPCI_ID_STR1_RG	= _upci_id_str1;												//id upci de estructura n�1.
	this->UPCI_ID_STR2_RG	= _upci_id_str2;												//id upci de estructura n�2.

	//---------------------------------------------------------------------------------
	//inicializaci�n de sub-registros.
	this->CS_SRG			= OFF;															//estado de congruencia.
	this->RS_SRG			= _rs_srg;														//fortaleza de la relaci�n.
	this->AL_SRG			= _al_srg;														//nivel de actividad.
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: m�todo para crear una relaci�n a la estructura.
vo INDFRLIS_SD::CreateRelation(in _rl_type, in _rl_id, in _upci_type, in _upci_id)
{
	//--------------------------------------------------------------------------------
	//seteo de uana relaci�n a la estructura.
	this->RL.push_back(deque<in>(0));
	this->RL.back().push_back(_rl_type);
	this->RL.back().push_back(_rl_id);
	this->RL.back().push_back(_upci_type);
	this->RL.back().push_back(_upci_id);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: m�todo para eliminar una relaci�n a la estructura.
vo INDFRLIS_SD::DeleteRelation(in _index)
{
	//---------------------------------------------------------------------------------
	//eliminaci�n de la relaci�n en _index.
	this->RL.erase(RL.begin() + _index);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: m�todo para diferenciar estructura.
dou INDFRLIS_SD::Differentiate(dou _in_dif_rg)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//nivel de congruencia de las estructuras.
	dou congruence = 0;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si "_in_dif_rg" es mayor, entonces.
	if (abs(_in_dif_rg) > abs(this->IN_DIF_RG))
	{
		//-----------------------------------------------------------------------------
		//diferenciaci�n de estructuras para obtener congruencia porcentual acumulada.
		congruence += 100.0 - ((abs(_in_dif_rg - this->IN_DIF_RG) / abs(_in_dif_rg)) * 100.0);
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//si "_in_dif_rg" es menor o igual, entonces.
	else
	{
		//-----------------------------------------------------------------------------
		//diferenciaci�n de estructuras para obtener congruencia porcentual acumulada.
		congruence += 100.0 - ((abs(_in_dif_rg - this->IN_DIF_RG) / abs(this->IN_DIF_RG)) * 100.0);
	}

	//---------------------------------------------------------------------------------
	//retorno del nivel de congruencia.
	return congruence;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: m�todo para obtener la cantidad de relaciones.
in INDFRLIS_SD::GetRelationAmount()
{
	//---------------------------------------------------------------------------------
	//obtenci�n de la cantidad de relaciones.
	return in(this->RL.size());
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: m�todo para obtener �ndice de una relaci�n.
in INDFRLIS_SD::GetRelationIndex(in _rl_type, in _rl_id, in _upci_type, in _upci_id)
{
	//---------------------------------------------------------------------------------
	//cantidad de relaciones.
	in rl_amount = this->GetRelationAmount();

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para hallar la relaci�n.
	for (in i1 = 0; i1 < rl_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si se halla la relaci�n, entonces retornar el �ndice de la relaci�n.
		if (_rl_type == abs(this->RL.at(i1).at(0)) && _rl_id == this->RL.at(i1).at(1) && _upci_type == this->RL.at(i1).at(2) && _upci_id == this->RL.at(i1).at(3))	return i1;
	}

	//---------------------------------------------------------------------------------
	//retorno si no se ha hallado la relaci�n.
	return -1;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: m�todo especial para obtener �ndice de la siguiente relaci�n saliente.
in INDFRLIS_SD::GetNextOutputRelationS(in _rl_start_index)
{
	//---------------------------------------------------------------------------------
	//obtenci�n de la cantidad de relaciones.
	in rl_amount = this->GetRelationAmount();

	//---------------------------------------------------------------------------------
	//bucle para obtener el �ndice de la siguiente relaci�n PFRLIS saliente.
	for (in i1 = _rl_start_index + 1; i1 < rl_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//si la relaci�n es saliente, entonces.
		if (this->RL.at(i1).at(0) == PFRLIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//retorno del �ndice de la relaci�n saliente.
			return  i1;
		}
	}

	//---------------------------------------------------------------------------------
	//retorno si no se ha hallado la relaci�n.
	return -1;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: m�todo para obtener �ndice de la anterior relaci�n PFRLIS entrante.
in INDFRLIS_SD::GetPreviousInputRelationS(in _rl_start_index)
{
	//---------------------------------------------------------------------------------
	//bucle para obtener el �ndice de la anterior relaci�n PFRLIS entrante.
	for (in i1 = _rl_start_index - 1; i1 >= 0; i1--)
	{
		//-----------------------------------------------------------------------------
		//si la relaci�n es entrante, entonces.
		if (this->RL.at(i1).at(0) == -PFRLIS_TYPE)
		{
			//-------------------------------------------------------------------------
			//retorno del �ndice de la relaci�n entrante.
			return  i1;
		}
	}

	//---------------------------------------------------------------------------------
	//retorno si no se ha hallado la relaci�n.
	return -1;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: m�todo para setear la estructura.
vo INDFRLIS_SD::Set(dou _in_dif_rg, dou _ev_dif_rg, in _str1_id, in _str2_id, in _upci_id_str1, in _upci_id_str2, in _cs_srg, dou _rs_srg, dou	_al_srg, dedein	&_rl)
{
	//---------------------------------------------------------------------------------
	//seteo de registros.
	this->IN_DIF_RG			= _in_dif_rg;													//diferencia entre registros de entrada;
	this->EV_DIF_RG			= _ev_dif_rg;													//diferencia entre registros de evaluaci�n.
	this->STR1_ID_RG		= _str1_id;														//id estructura n�1.
	this->STR2_ID_RG		= _str2_id;														//id estructura n�2.
	this->UPCI_ID_STR1_RG	= _upci_id_str1;												//id upci de estructura n�1.
	this->UPCI_ID_STR2_RG	= _upci_id_str2;												//id upci de estructura n�2.

	//---------------------------------------------------------------------------------
	//seteo de sub-registros.
	this->CS_SRG			= _cs_srg;														//estado de congruencia.
	this->RS_SRG			= _rs_srg;														//fortaleza de la relaci�n.
	this->AL_SRG			= _al_srg;														//nivel de actividad.

	//---------------------------------------------------------------------------------
	//seteo de relaciones.
	this->RL				= _rl;	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: m�todo para Clean la estructura.
vo INDFRLIS_SD::Clean()
{
	//---------------------------------------------------------------------------------
	//reset de registros.
	this->IN_DIF_RG			= -1;															//diferencia entre registros de entrada.
	this->EV_DIF_RG			= -1;															//diferencia entre registros de evaluaci�n.
	this->STR1_ID_RG		= -1;															//id estructura n�1.
	this->STR2_ID_RG		= -1;															//id estructura n�2.
	this->UPCI_ID_STR1_RG	= -1;															//id upci de estructura n�1.
	this->UPCI_ID_STR2_RG	= -1;															//id upci de estructura n�2.

	//---------------------------------------------------------------------------------
	//inicializaci�n de sub-registros.
	this->CS_SRG			= -1;															//estado de congruencia.
	this->RS_SRG			= -1;															//fortaleza de la relaci�n.
	this->AL_SRG			= -1;															//nivel de actividad.

	//---------------------------------------------------------------------------------
	//reset de relaciones.
	this->RL.clear();
}
