//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
Nombre Clase : 	  BUFF_DS_STR_IITE (Buffer de estructuras para construcci�n de Hilo potencial tipo 'DS').
Fecha	     :	  22:17 pm 13-06-2017.
Dise�ador    :	  Gustavo Catal�n Ulloa.
descripci�n	 :	  XXXXXXXXXXXX.
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include "BUFF_DS_STR_IITE.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//espacio de nombres.
using namespace UPC;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: constructor 1.
BUFF_DS_STR_IITE::BUFF_DS_STR_IITE()
{
	//---------------------------------------------------------------------------------
	//inicializaci�n de par�metros estructurales.
	this->UPCI_ID					= -1;													//id de upci.	
	this->STR_ID					= -1;													//id estructura.
	this->STR_TYPE					= -1;													//tipo de estructura.

	//---------------------------------------------------------------------------------
	//inicializaci�n de par�metros de evaluaci�n.
	this->MAX_EV					= -1;													//evaluaci�n m�xima del Hilo potencial.
	this->INPUT_EVALUATION			= -1;													//evaluaci�n de entrada para obtener transiciones del Hilo potencial.
	this->POSITIVE_STATES_AMOUNT	= -1;													//cantidad de estados positivos (transiciones y entradas) del Hilo potencial.
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: constructor 2.
BUFF_DS_STR_IITE::BUFF_DS_STR_IITE(in _upci_id, in _str_id, in _str_type, dou _maximum__evaluation, dou _input_evaluation, in _positive_states_amount)
{
	//---------------------------------------------------------------------------------
	//seteo de par�metros estructurales.
	this->UPCI_ID					= _upci_id;												//id de upci.	
	this->STR_ID					= _str_id;												//id estructura.
	this->STR_TYPE					= _str_type;											//tipo de estructura.

	//---------------------------------------------------------------------------------
	//seteo de par�metros de evaluaci�n.
	this->MAX_EV					= _maximum__evaluation;									//evaluaci�n m�xima del Hilo potencial.
	this->INPUT_EVALUATION			= _input_evaluation;									//evaluaci�n de entrada para obtener transiciones del Hilo potencial.
	this->POSITIVE_STATES_AMOUNT	= _positive_states_amount;								//cantidad de estados positivos (transiciones y entradas) del Hilo potencial.
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: destructor.
BUFF_DS_STR_IITE::~BUFF_DS_STR_IITE()
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
vo	BUFF_DS_STR_IITE::Set(in _upci_id, in _str_id, in _str_type, dou _maximum__evaluation, dou _input_evaluation, in _positive_states_amount)
{
	//---------------------------------------------------------------------------------
	//seteo de par�metros estructurales.
	this->UPCI_ID					= _upci_id;												//id de upci.	
	this->STR_ID					= _str_id;												//id estructura.
	this->STR_TYPE					= _str_type;											//tipo de estructura.

	//---------------------------------------------------------------------------------
	//par�metros de evaluaci�n.
	this->MAX_EV					= _maximum__evaluation;									//evaluaci�n m�xima del Hilo potencial.
	this->INPUT_EVALUATION			= _input_evaluation;									//evaluaci�n de entrada para obtener transiciones del Hilo potencial.
	this->POSITIVE_STATES_AMOUNT	= _positive_states_amount;								//cantidad de estados positivos (transiciones y entradas) del Hilo potencial.
}	

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: m�todo para Clean la estructura.
vo BUFF_DS_STR_IITE::Clean()
{
	//---------------------------------------------------------------------------------
	//seteo de par�metros estructurales.
	this->UPCI_ID					= -1;													//id de upci.	
	this->STR_ID					= -1;													//id estructura.
	this->STR_TYPE					= -1;													//tipo de estructura.

	//---------------------------------------------------------------------------------
	//limpieza par�metros de evaluaci�n.
	this->MAX_EV					= -1;													//evaluaci�n m�xima del Hilo potencial.
	this->INPUT_EVALUATION			= -1;													//evaluaci�n de entrada para obtener transiciones del Hilo potencial.
	this->POSITIVE_STATES_AMOUNT	= -1;													//cantidad de estados positivos (transiciones y entradas) del Hilo potencial.
}
