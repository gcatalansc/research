#pragma once
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
//tipos.
typedef 	void				vo;
typedef		int					in;
typedef		double				dou;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//nombre de espacio UPC.
namespace UPC
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//clase BUFF_DS_STR_IITE.
	class BUFF_DS_STR_IITE
	{

		//miembros p�blicos.
	public:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//par�metros estructurales.
		in	UPCI_ID;																		//id de upci.
		in	STR_ID;																			//id estructura.
		in	STR_TYPE;																		//tipo de estructura.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//par�metros de evaluaci�n.
		dou	MAX_EV;																			//evaluaci�n m�xima del Hilo potencial.
		dou	INPUT_EVALUATION;																//evaluaci�n de entrada para obtener transiciones del Hilo potencial.		
		in	POSITIVE_STATES_AMOUNT;															//cantidad de estados positivos (transiciones y entradas) del Hilo potencial.	

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos constructor.
		BUFF_DS_STR_IITE();
		BUFF_DS_STR_IITE(in _upci_id, in _str_id, in _str_type, dou _maximum__evaluation, dou _input_evaluation, in _positive_states_amount);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//destructor.
		~BUFF_DS_STR_IITE();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//seteo de la estructura.
		vo	Set(in _upci_id, in _str_id, in _str_type, dou _maximum__evaluation, dou _input_evaluation, in _positive_states_amount);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//limpieza  de la estructura.
		vo Clean();
	};
}