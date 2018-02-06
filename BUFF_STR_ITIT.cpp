//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
Nombre Clase : 	  BUFF_STR_ITIT (Buffer de estructura con id y tipo de upci, tipo de 
				  estructura y id de estructura).
Fecha	     :	  17:29 pm 17-11-2015.
Dise�ador    :	  Gustavo Catal�n Ulloa.
descripci�n	 :	  XXXXXXXXXXXX.
*/

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include "BUFF_STR_ITIT.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//espacio de nombres.
using namespace UPC;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: constructor 1.
BUFF_STR_ITIT::BUFF_STR_ITIT()
{
	//---------------------------------------------------------------------------------
	//inicializaci�n de par�metros estructurales.		
	this->STR_ID	= -1;																	//id estructura.
	this->STR_TYPE	= -1;																	//tipo de estructura.
	this->UPCI_TYPE	= -1;																	//tipo de upci.
	this->UPCI_ID	= -1;																	//id upci.
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: constructor 2.
BUFF_STR_ITIT::BUFF_STR_ITIT(in _str_type, in _str_id, in _upci_type, in _upci_id)
{
	//---------------------------------------------------------------------------------
	//seteo de par�metros estructurales.	
	this->STR_TYPE	= _str_type;															//tipo de estructura.
	this->STR_ID	= _str_id;																//id estructura.		
	this->UPCI_TYPE	= _upci_id;																//id de upci.
	this->UPCI_ID	= _upci_id;																//id upci.
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: destructor.
BUFF_STR_ITIT::~BUFF_STR_ITIT()
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
//#1: m�todo para setear la estructura.
vo	BUFF_STR_ITIT::Set(in _str_type, in _str_id, in _upci_type, in _upci_id)
{
	//---------------------------------------------------------------------------------
	//seteo de par�metros estructurales.	
	this->STR_TYPE	= _str_type;															//tipo de estructura.
	this->STR_ID	= _str_id;																//id estructura.		
	this->UPCI_TYPE	= _upci_id;																//id de upci.
	this->UPCI_ID	= _upci_id;																//id upci.
}	

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: m�todo para Clean la estructura.
vo BUFF_STR_ITIT::Clean()
{
	//---------------------------------------------------------------------------------
	//limpieza par�metros estructurales.	
	this->STR_TYPE	= -1;																	//tipo de estructura.
	this->STR_ID	= -1;																	//id estructura.	
	this->UPCI_TYPE	= -1;																	//tipo de upci.	
	this->UPCI_ID	= -1;																	//id upci.	
	
}
