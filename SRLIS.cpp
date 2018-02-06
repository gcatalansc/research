//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
/*
Nombre Clase : 	  SRLIS (Estructura de Información de Relación de Simple).
Fecha	     :	  17:32 pm 15-11-2017.
Diseñador    :	  Gustavo Catalán Ulloa.
descripción	 :	  XXXXXXXXXXXX.
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include "SRLIS.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//espacio de nombres.
using namespace UPC;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: constructor.
SRLIS::SRLIS()
{
	//---------------------------------------------------------------------------------
	//inicialización de registros.
	this->STR1_TYPE_RG		= -1;															//tipo de estructura n°1.
	this->STR2_TYPE_RG		= -1;															//tipo de estructura n°2.
	this->STR1_ID_RG		= -1;															//id estructura n°1.
	this->STR2_ID_RG		= -1;															//id estructura n°2.
	this->UPCI_ID_STR1_RG	= -1;															//id upci de estructura n°1.
	this->UPCI_ID_STR2_RG	= -1;															//id upci de estructura n°2.

	//---------------------------------------------------------------------------------
	//inicialización de sub-registros.
	this->RS_SRG			= -1;															//fortaleza de la relación.
	this->AL_SRG			= -1;															//nivel de actividad.
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: destructor.
SRLIS::~SRLIS()
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
//#1: método para crear estructura.
vo SRLIS::Create(in _str1_type, in _str2_type, in _str1_id, in _str2_id, in _upci_type_str1, in _upci_type_str2, in _upci_id_str1, in _upci_id_str2, dou	_rs_srg, dou _al_srg)
{
	//---------------------------------------------------------------------------------
	//inicialización de registros.
	this->STR1_TYPE_RG		= _str1_type;													//tipo de estructura n°1.
	this->STR2_TYPE_RG		= _str2_type;													//tipo de estructura n°2.
	this->STR1_ID_RG		= _str1_id;														//id estructura n°1.
	this->STR2_ID_RG		= _str2_id;														//id estructura n°2.
	this->UPCI_TYPE_STR1_RG	= _upci_type_str1;												//tipo de upci de estructura n°1.
	this->UPCI_TYPE_STR2_RG	= _upci_type_str2;												//tipo de upci de estructura n°2.
	this->UPCI_ID_STR1_RG	= _upci_id_str1;												//id upci de estructura n°1.
	this->UPCI_ID_STR2_RG	= _upci_id_str2;												//id upci de estructura n°2.

	//---------------------------------------------------------------------------------
	//inicialización de sub-registros.
	this->RS_SRG			= _rs_srg;														//fortaleza de la relación.
	this->AL_SRG			= _al_srg;														//nivel de actividad.
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para setear la estructura.
vo SRLIS::Set(in _str1_type, in _str2_type, in _str1_id, in _str2_id, in _upci_type_str1, in _upci_type_str2, in _upci_id_str1, in _upci_id_str2, dou _rs_srg, dou _al_srg)
{
	//---------------------------------------------------------------------------------
	//seteo de registros.
	this->STR1_TYPE_RG		= _str1_type;													//tipo de estructura n°1.
	this->STR2_TYPE_RG		= _str2_type;													//tipo de estructura n°2.
	this->STR1_ID_RG		= _str1_id;														//id estructura n°1.
	this->STR2_ID_RG		= _str2_id;														//id estructura n°2.
	this->UPCI_TYPE_STR1_RG	= _upci_type_str1;												//tipo de upci de estructura n°1.
	this->UPCI_TYPE_STR2_RG	= _upci_type_str2;												//tipo de upci de estructura n°2.
	this->UPCI_ID_STR1_RG	= _upci_id_str1;												//id upci de estructura n°1.
	this->UPCI_ID_STR2_RG	= _upci_id_str2;												//id upci de estructura n°2.

	//---------------------------------------------------------------------------------
	//seteo de sub-registros.
	this->RS_SRG			= _rs_srg;														//fortaleza de la relación.
	this->AL_SRG			= _al_srg;														//nivel de actividad.
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para Clean la estructura.
vo SRLIS::Clean()
{
	//---------------------------------------------------------------------------------
	//reset de registros.
	this->STR1_TYPE_RG		= -1;															//tipo de estructura n°1.
	this->STR2_TYPE_RG		= -1;															//tipo de estructura n°2.
	this->STR1_ID_RG		= -1;															//id estructura n°1.
	this->STR2_ID_RG		= -1;															//id estructura n°2.
	this->UPCI_TYPE_STR1_RG = -1;															//tipo de upci de estructura n°1.
	this->UPCI_TYPE_STR2_RG = -1;															//tipo de upci de estructura n°2.
	this->UPCI_ID_STR1_RG	= -1;															//id upci de estructura n°1.
	this->UPCI_ID_STR2_RG	= -1;															//id upci de estructura n°2.

	//---------------------------------------------------------------------------------
	//reset de sub-registros.
	this->RS_SRG			= -1;															//fortaleza de la relación.
	this->AL_SRG			= -1;															//nivel de actividad.
}
