#pragma once
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
Nombre Clase : 	  BUFF_STR_ITI (Buffer de estructura con id y tipo de upci, id de
				  estructura).
Fecha	     :	  19:26 pm 24-04-2017.
Dise�ador    :	  Gustavo Catal�n Ulloa.
descripci�n	 :	  XXXXXXXXXXXX.
*/

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//tipos.
typedef 	void		vo;
typedef		int			in;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//nombre de espacio UPC.
namespace UPC
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//clase BUFF_STR_ITI.
	class BUFF_STR_ITI
	{

		//miembros p�blicos.
	public:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//par�metros estructurales.
		in	STR_ID;																			//id estructura.		
		in	UPCI_TYPE;																		//tipo de de upci.
		in	UPCI_ID;																		//id upci.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos constructor.
		BUFF_STR_ITI();
		BUFF_STR_ITI(in _str_id, in _upci_type, in _upci_id);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//destructor.
		~BUFF_STR_ITI();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//seteo de la estructura.
		vo	Set(in _str_id, in _upci_type, in _upci_id);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//limpieza  de la estructura.
		vo Clean();
	};
}