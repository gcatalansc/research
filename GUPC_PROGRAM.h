#pragma once
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
Nombre Clase : 	  GUPC_PROGRAM (Programa de implementaci�n para GUPCI).
Fecha	     :	  12:13 pm 16-03-2016.
Dise�ador    :	  Gustavo Catal�n Ulloa.
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include <Windows.h>
#include <SFML\Graphics.hpp>
#include "ENVIRONMENT.h"
#include "SYSTEMS.h"
#include "GUPCI_SDS.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//espacio de nombres.
using namespace UPC;
using namespace std;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//tipos.
typedef 	void									vo;
typedef		int										in;
typedef		double									dou;
typedef		string									st;
typedef		vector<string>							vest;
typedef		deque<string>							dest;
typedef		deque<deque<GUPCI_SDS>>					dedeGUPCI_SDS;
typedef		deque<UPCI_SDS_ARG>						deUPCI_SDS_ARG;
typedef		deque<deque<deque<double>>>				dedededou;
typedef		vector<vector<vector<double>>>			vevevedou;
typedef		vector<vector<vector<vector<double>>>>	vevevevedou;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//nombre de espacio UPC.
namespace UPC
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//clase: Programa para de testeo de GUPC.
	class GUPC_PROGRAM
	{
		//elementos privados.
	private:

		//#############################################################################
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//################################ PROGRAMA ###################################

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//banderas del programa. 
		in					GUPCI_LOADED_FLAG;												//bandera de GUPCI cargada.
		in					WAITING_NEXT_ITERATION_FLAG;									//bandera para saltar iteraci�n del programa.
		in					PROGRAM_RUNNING_FLAG;											//bandera de programa corriendo.		
		in					SET_SYSTEM_FLAG;												//bandera de seteo de sistema.
		in					MANUAL_RESET_SYSTEM_FLAG;										//bandera de reSeteo del sistema manual.
		in					EXIT_FLAG;														//bandera de salida del programa.
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//threads del programa.
		thread				THREAD_COM;
		thread				THREAD_PRO;		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//variables para el buffer seleccionado.	
		in					SELECT_BUFF;													//buffers seleccionado.
		in					GUPCI_TYPE_ID;													//id del tipo de GUPCI.
		in					GUPCI_ID;														//id de la GUPCI.
		in					UPCI_ID;														//id de la upci.
		in					STR_ID;															//id de la estructura.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//variables para el bucle del programa.
		in					ITERATION_TYPE;													//tipo de iteraci�n.
		in					ITERATIONS_COUNTER;												//contador de iteraciones.	
		in					ITERATIONS_COUNTER_FOR_EXPLORER_NODE;							//contador de iteraciones para nodo explorador.	
		in					TIMEOUT_PROGRAM_LOOP;											//tiempo de espera del bucle del programa.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//variables para comandos.
		st					BUFF_RAW_USER_COMMAND;											//buffer para comando raw.
		vest				BUFF_USER_COMMAND;												//buffer para comandos separados.
		in					ESC_KEY;														//tecla 'ESC'.

		//#############################################################################
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//################################### NODOS ###################################

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//entrada, evaluaci�n y proyecci�n de la GUPCI.
		dou					**GUPCI_INPUT;
		dou					GUPCI_EVALUATION;
		dou					**GUPCI_PROJECTION;
										

		//#############################################################################
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//################################# GUPCI #####################################

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//buffers GUPCI.	
		GUPCI_SDS			BUFF_GUPCI;														//buffer de GUPCI tipo DS.
		UPCI_SDS_ARG		BUFF_UPCI_ARG;													//buffer para la inicializaci�n de las GUPCI.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//par�metros de inicializaci�n de GUCPI, cantidad de upci por grupo.
		in					UPCI_AMOUNT;														

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//par�metros de inicializaci�n de UPCI.
		in					INIS_AMOUNT_ALLOWED;											//cantidad de estructuras INIS permitidas.
		in					ACIS_AMOUNT_ALLOWED;											//cantidad de estructuras ACIS permitidas.
		in					RLIS_AMOUNT_ALLOWED;											//cantidad de estructuras rlis permitidas.
		dou					DEFAULT_ACTIVITY_LEVEL;											//nivel de actividad por defecto.
		dou					MAX_ACTIVITY_LEVEL_ALLOWED;										//nivel de actividad m�ximo permitido.
		dou					MIN_ACTIVITY_LEVEL_ALLOWED;										//nivel de actividad m�nimo permitido.
		dou					KERNEL_RAW_INPUT_THRESHOLD;										//umbral de entrada cruda para control del n�cleo.
		dou					DIF_RAW_INPUT_THRESHOLD;										//umbral de entrada cruda para focalizaci�n de la atenci�n (%).
		dou					STR_CONGRUENCE_THRESHOLD;										//umbral de congruencia para estructuras candidatas (%).	
		dou					PFRLIS_STRENGTH_THRESHOLD;										//umbral de fortaleza de relaci�n PFRLIS para eliminar relaci�n por N.A.
		dou					INDFRLIS_STRENGTH_THRESHOLD;									//umbral de fortaleza de relaci�n INDFRLIS para eliminar relaci�n por N.A.
		dou					EVALUATION_THRESHOLD;											//umbral para evaluaciones.	
		dou					TRANSITION_EVALUATION_THRESHOLD;								//umbral para transici�n de evaluaciones.	
		in					TIMEOUT_CLEAN_IS;												//tiempo de espera de limpieza de IS.
		in					TIMEOUT_UPDATE_AL_IS;											//tiempo de espera para actualizar niveles de actividad en IS (ms).

		//#############################################################################
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//################################ GR�FICOS ###################################

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//declaraci�n de clases para gr�ficos.
		ENVIRONMENT			ENVIRONMENT_TEST;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//argumentos: par�metros del render.
		in					HIGH_WINDOW;													//alto de la ventana.
		in					WIDTH_WINDOW;													//ancho de la ventana.
		string				WINDOW_TITLE;													//t�tulo de la ventana.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//variables auxiliares.
		std::mutex			RED_LIGHT_MUTEX;												//mutex para escritura.

		//m�todos p�blicos.
	public:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo constructor.
		GUPC_PROGRAM();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todosdestructor.
		~GUPC_PROGRAM();													

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todos del programa.
		vo RunPro();																		//correr programa.
		vo ThreadUserComunication();														//thread para la comunicaci�n con el cliente.
		vo ThreadPrograma();																//thread para la ejecuci�n del programa.		
		vo PrintingInformation();															//impresi�n de informaci�n.
		vo PauseIteration();																//pause en iteraci�n.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para abrir, cargar y salvar GUPC.	
		vo LoadGUPCI();
		vo OpenGUPCI(string _fileNameS);
		vo SaveGUPCI(string _fileNameS);		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//m�todo para obtener los comandos del usuario particionado.
		vo GetUserCommand(st _buffer_raw_user_command, vest &_buffer_user_command);		
	};
}

