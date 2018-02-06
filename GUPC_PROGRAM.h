#pragma once
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
Nombre Clase : 	  GUPC_PROGRAM (Programa de implementación para GUPCI).
Fecha	     :	  12:13 pm 16-03-2016.
Diseñador    :	  Gustavo Catalán Ulloa.
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
		in					WAITING_NEXT_ITERATION_FLAG;									//bandera para saltar iteración del programa.
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
		in					ITERATION_TYPE;													//tipo de iteración.
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
		//entrada, evaluación y proyección de la GUPCI.
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
		UPCI_SDS_ARG		BUFF_UPCI_ARG;													//buffer para la inicialización de las GUPCI.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//parámetros de inicialización de GUCPI, cantidad de upci por grupo.
		in					UPCI_AMOUNT;														

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//parámetros de inicialización de UPCI.
		in					INIS_AMOUNT_ALLOWED;											//cantidad de estructuras INIS permitidas.
		in					ACIS_AMOUNT_ALLOWED;											//cantidad de estructuras ACIS permitidas.
		in					RLIS_AMOUNT_ALLOWED;											//cantidad de estructuras rlis permitidas.
		dou					DEFAULT_ACTIVITY_LEVEL;											//nivel de actividad por defecto.
		dou					MAX_ACTIVITY_LEVEL_ALLOWED;										//nivel de actividad máximo permitido.
		dou					MIN_ACTIVITY_LEVEL_ALLOWED;										//nivel de actividad mínimo permitido.
		dou					KERNEL_RAW_INPUT_THRESHOLD;										//umbral de entrada cruda para control del núcleo.
		dou					DIF_RAW_INPUT_THRESHOLD;										//umbral de entrada cruda para focalización de la atención (%).
		dou					STR_CONGRUENCE_THRESHOLD;										//umbral de congruencia para estructuras candidatas (%).	
		dou					PFRLIS_STRENGTH_THRESHOLD;										//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
		dou					INDFRLIS_STRENGTH_THRESHOLD;									//umbral de fortaleza de relación INDFRLIS para eliminar relación por N.A.
		dou					EVALUATION_THRESHOLD;											//umbral para evaluaciones.	
		dou					TRANSITION_EVALUATION_THRESHOLD;								//umbral para transición de evaluaciones.	
		in					TIMEOUT_CLEAN_IS;												//tiempo de espera de limpieza de IS.
		in					TIMEOUT_UPDATE_AL_IS;											//tiempo de espera para actualizar niveles de actividad en IS (ms).

		//#############################################################################
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//################################ GRÁFICOS ###################################

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//declaración de clases para gráficos.
		ENVIRONMENT			ENVIRONMENT_TEST;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//argumentos: parámetros del render.
		in					HIGH_WINDOW;													//alto de la ventana.
		in					WIDTH_WINDOW;													//ancho de la ventana.
		string				WINDOW_TITLE;													//título de la ventana.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//variables auxiliares.
		std::mutex			RED_LIGHT_MUTEX;												//mutex para escritura.

		//métodos públicos.
	public:

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método constructor.
		GUPC_PROGRAM();

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodosdestructor.
		~GUPC_PROGRAM();													

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//métodos del programa.
		vo RunPro();																		//correr programa.
		vo ThreadUserComunication();														//thread para la comunicación con el cliente.
		vo ThreadPrograma();																//thread para la ejecución del programa.		
		vo PrintingInformation();															//impresión de información.
		vo PauseIteration();																//pause en iteración.

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para abrir, cargar y salvar GUPC.	
		vo LoadGUPCI();
		vo OpenGUPCI(string _fileNameS);
		vo SaveGUPCI(string _fileNameS);		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//método para obtener los comandos del usuario particionado.
		vo GetUserCommand(st _buffer_raw_user_command, vest &_buffer_user_command);		
	};
}

