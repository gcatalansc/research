//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
Nombre Clase : 	  GUPC_PROGRAM (Programa de implementación para GUPC).
Fecha	     :	  12:13 pm 16-03-2016.
Diseñador    :	  Gustavo Catalán Ulloa.
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//librerias.
#include "GUPC_PROGRAM.h"
#include "PROGRAM_PAR.h"
#include "GUPCI_TEST.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//espacio de nombres.
using namespace UPC;
using namespace std;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método constructor.
GUPC_PROGRAM::GUPC_PROGRAM()
{
	//#################################################################################
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//################################## PROGRAMA #####################################

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de banderas del programa.
	this->GUPCI_LOADED_FLAG						= OFF;											//bandera de GUPCI cargada.
	this->WAITING_NEXT_ITERATION_FLAG			= ON;											//bandera para saltar iteración del programa.
	this->PROGRAM_RUNNING_FLAG					= OFF;											//bandera de rupci corriendo.
	this->SET_SYSTEM_FLAG						= OFF;											//bandera de seteo de una condición incial al sistema.
	this->MANUAL_RESET_SYSTEM_FLAG				= ON;											//bandera de reseteo del sistema manual.
	this->EXIT_FLAG								= OFF;											//bandera de salida del programa.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de variables para el buffer seleccionado.
	this->SELECT_BUFF							= NULL;											//buffers seleccionado.
	this->GUPCI_ID								= NULL;											//id de la GUPCI.
	this->UPCI_ID								= NULL;											//id de la upci.
	this->STR_ID								= NULL;											//id de la estructura.
		
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de variables para el bucle del programa.
	this->ITERATION_TYPE						= NULL;											//tipo de iteración.
	this->ITERATIONS_COUNTER					= 0;											//contador de iteraciones.	
	this->ITERATIONS_COUNTER_FOR_EXPLORER_NODE	= 50;											//contador de iteraciones para nodo explorador.
	this->TIMEOUT_PROGRAM_LOOP					= timeout_program_loop;							//tiempo de espera del bucle del programa.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//comandos.
	this->ESC_KEY								= VK_ESCAPE;									//tecla 'ESC'.

	//#################################################################################
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//################################### NODOS #######################################

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de entrada, evaluación y proyección de la GUPCI.
	this->GUPCI_INPUT							= new dou*[3];
	this->GUPCI_EVALUATION						= 0;
	this->GUPCI_PROJECTION						= new dou*[3];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializar entrada y proyección de la GUPCI restante.
	for (in i1 = 0; i1 < 3; i1++)
	{
		//-----------------------------------------------------------------------------
		//inicialización de entrada y proyección de la GUPCI restante.
		this->GUPCI_INPUT[i1]		= new dou[3];
		this->GUPCI_PROJECTION[i1]	= new dou[3];
	}	

	//#################################################################################
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//################################## GRÁFICOS #####################################

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de parámetros del render.
	this->HIGH_WINDOW							= 800;											//alto de la ventana.
	this->WIDTH_WINDOW							= 1800;											//ancho de la ventana.
	this->WINDOW_TITLE							= "Render";										//título de la ventana.
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización del RENDERER.
	/*this->ENVIRONMENT_TEST.iniENVIRONMENT(this->HIGH_WINDOW,
										  this->WIDTH_WINDOW, 
										  this->WINDOW_TITLE, 
										  this->TEST_GUPCI_TYPES_AMOUNT,
										  this->TEST_GUPCI_AMOUNT);*/
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método destructor.
GUPC_PROGRAM::~GUPC_PROGRAM()
{

}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para correr programa.
vo GUPC_PROGRAM::RunPro()
{
	//---------------------------------------------------------------------------------
	//impresión del inicio del programa de prueba de la rgupci.
	cout << "--------------------------------------------------------------------" << endl;
	cout << "----------- Bienvenido al programa de prueba GUPCI y QL ------------" << endl;
	cout << "--------------------------------------------------------------------" << endl;
	cout << endl;
	cout << "# para mostrar comandos ingrese : 'scommand'." << endl;

	//---------------------------------------------------------------------------------
	//lanzamiento de threads.	
	this->THREAD_COM = thread(&UPC::GUPC_PROGRAM::ThreadUserComunication, this);
	this->THREAD_PRO = thread(&UPC::GUPC_PROGRAM::ThreadPrograma, this);

	//---------------------------------------------------------------------------------
	//término de los thredas.
	this->THREAD_COM.join();
	this->THREAD_PRO.join();	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método thread para la comunicación con el usuario.
vo GUPC_PROGRAM::ThreadUserComunication()
{
	//---------------------------------------------------------------------------------
	//seteo de tiempos de espera del bucle.
	chrono::milliseconds timeout_loop_slow(TIMEOUT_LOOP_SLOW);
	chrono::milliseconds timeout_loop_fast(TIMEOUT_LOOP_FAST);
	chrono::milliseconds timeout_loop_very_fast(TIMEOUT_LOOP_VERY_FAST);

	//---------------------------------------------------------------------------------
	//bucle para consulta de recepción de datos de parte del cliente. 
	while (this->EXIT_FLAG == OFF)
	{
		//-----------------------------------------------------------------------------
		//reset de buffer de comandos.
		this->BUFF_RAW_USER_COMMAND.clear();
		
		//-----------------------------------------------------------------------------
		//espera por ingreso de comandos por parte del usuario. 
		cout << endl;
		getline(std::cin, this->BUFF_RAW_USER_COMMAND);
		
		//-----------------------------------------------------------------------------
		//obtención de los comandos.
		this->GetUserCommand(this->BUFF_RAW_USER_COMMAND, this->BUFF_USER_COMMAND);
		
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//comando "scommand".
		if (this->BUFF_USER_COMMAND[0] == "scommand")
		{
			//-------------------------------------------------------------------------
			//impresión de los comandos.
			cout << "--------------------------------------------------------------------" << endl;
			cout << "scommand        : mostrar comandos." << endl;
			cout << "lg              : cargar las GUPCI." << endl;
			cout << "open            : abrir GUPCI (open _gupci_id _name) , (_gupci_id: id de la GUPCI, _name: nombre del fichero)." << endl;			
			cout << "save            : salvar GUPCI (save _name), (_name: nombre del fichero)." << endl;
			cout << "sitime          : setear tiempo de iteracion [ms] (sitime 500), (500: tiempo en milisegundos)." << endl;
			cout << "print           : imprimir buffer (print 3 0 0 12), (3: buffer 3, 0: id GUPCI, 0: id UPCI, 12: id de la IS)." << endl;
			cout << "display         : mostrar graficos." << endl;
			cout << "nexti           : siguiente interacion." << endl;
			cout << "run             : correr programa." << endl;
			cout << "[ESCAPE]        : detener programa." << endl;
			cout << "exit            : salir del programa." << endl;
			cout << "--------------------------------------------------------------------" << endl;
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//comando "lg".
		if (this->BUFF_USER_COMMAND[0] == "lg")
		{		
			//-------------------------------------------------------------------------
			//parámetros de inicialización de GUCPI, cantidad de upci por grupo.	
			this->UPCI_AMOUNT						= upci_amount_test;						

			//-------------------------------------------------------------------------
			//parámetros de inicialización de UPCI.
			this->INIS_AMOUNT_ALLOWED				= inis_amount_allowed_test;					//cantidad de estructuras INIS permitidas.
			this->ACIS_AMOUNT_ALLOWED				= acis_amount_allowed_test;					//cantidad de estructuras ACIS permitidas.
			this->RLIS_AMOUNT_ALLOWED				= rlis_amount_allowed_test;					//cantidad de estructuras rlis permitidas.
			this->DEFAULT_ACTIVITY_LEVEL			= default_activity_level_test;				//nivel de actividad por defecto.
			this->MAX_ACTIVITY_LEVEL_ALLOWED		= max_activity_level_allowed_test;			//nivel de actividad máximo permitido.
			this->MIN_ACTIVITY_LEVEL_ALLOWED		= min_activity_level_allowed_test;			//nivel de actividad mínimo permitido.
			this->KERNEL_RAW_INPUT_THRESHOLD		= kernel_raw_input_threshold_test;			//umbral de entrada cruda para control del núcleo.
			this->DIF_RAW_INPUT_THRESHOLD			= dif_raw_input_threshold_test;				//umbral de entrada cruda para focalización de la atención (%).
			this->STR_CONGRUENCE_THRESHOLD			= str_congruence_threshold_test;			//umbral de congruencia para estructuras candidatas (%).	
			this->PFRLIS_STRENGTH_THRESHOLD			= pfrlis_strength_threshold_test;			//umbral de fortaleza de relación PFRLIS para eliminar relación por N.A.
			this->INDFRLIS_STRENGTH_THRESHOLD		= indfrlis_strength_threshold_test;			//umbral de fortaleza de relación INDFRLIS para eliminar relación por N.A.
			this->EVALUATION_THRESHOLD				= evaluation_threshold_test;				//umbral para evaluaciones.	
			this->TRANSITION_EVALUATION_THRESHOLD	= transition_evaluation_threshold_test;		//umbral para transición de evaluaciones.	
			this->TIMEOUT_CLEAN_IS					= timeout_clean_is_test;					//tiempo de espera de limpieza de IS.
			this->TIMEOUT_UPDATE_AL_IS				= timeout_update_al_is_test;				//tiempo de espera para actualizar niveles de actividad en IS (ms).	

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//carga de la GUPCI.
			this->LoadGUPCI();
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//comando "open".
		else if (this->BUFF_USER_COMMAND[0] == "open")
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//abrir GUPCI desde fichero.
			this->OpenGUPCI(this->BUFF_USER_COMMAND[1]);
		}		

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//comando "save".
		else if (this->BUFF_USER_COMMAND[0] == "save")
		{
			//-------------------------------------------------------------------------
			//si la GUPCI está cargada, entonces.
			if (this->GUPCI_LOADED_FLAG == ON)
			{
				//---------------------------------------------------------------------
				//---------------------------------------------------------------------
				//si existen tipos de agentes GUPCI, entonces.
				this->SaveGUPCI(this->BUFF_USER_COMMAND[1]);
			}
			
			//-------------------------------------------------------------------------
			//si no está cargada, entonces imprimir error.
			else
			{
				//---------------------------------------------------------------------
				//impresión de error.
				cout << "# error, no hay GUPCI cargadas." << endl;
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//comando "sitime".
		else if (this->BUFF_USER_COMMAND[0] == "sitime")
		{
			//-------------------------------------------------------------------------
			//actualización del tiempo de espera de la iteración del programa.
			this->TIMEOUT_PROGRAM_LOOP = atoi(this->BUFF_USER_COMMAND[1].c_str());

			//-------------------------------------------------------------------------
			//impresión.
			cout << "# se ha seteado el tiempo de iteracion a " << this->TIMEOUT_PROGRAM_LOOP << "[ms]." << endl;
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//comando "Print".
		else if (this->BUFF_USER_COMMAND[0] == "Print")
		{
			//-------------------------------------------------------------------------
			//si la GUPCI está cargada, entonces.
			if (this->GUPCI_LOADED_FLAG == ON)
			{
				//---------------------------------------------------------------------
				//si se ingresado el id de una estructura, entonces setear.
				if (this->BUFF_USER_COMMAND.size() == 6) this->STR_ID = atoi(this->BUFF_USER_COMMAND[5].c_str());

				//---------------------------------------------------------------------
				//carga del id del tipo de GUPCI.
				this->GUPCI_TYPE_ID = atoi(this->BUFF_USER_COMMAND[1].c_str());
				
				//---------------------------------------------------------------------
				//carga del id de la GUPCI.
				this->GUPCI_ID		= atoi(this->BUFF_USER_COMMAND[2].c_str());

				//---------------------------------------------------------------------
				//carga del id de la upci.
				this->UPCI_ID		= atoi(this->BUFF_USER_COMMAND[3].c_str());

				//---------------------------------------------------------------------
				//carga del buffers a enviar.
				this->SELECT_BUFF	= atoi(this->BUFF_USER_COMMAND[4].c_str());
								
				//---------------------------------------------------------------------
				//impresión del buffer seleccionado.
				this->BUFF_GUPCI.PrintGUPCI(this->UPCI_ID, this->SELECT_BUFF, this->STR_ID);
			}

			//-------------------------------------------------------------------------
			//si no está cargada, entonces imprimir error.
			else
			{
				//---------------------------------------------------------------------
				//impresión de error.
				cout << "# error, la GUPCI no esta cargada."<<endl;
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//comando "display".
		else if (this->BUFF_USER_COMMAND[0] == "display")
		{
			//-------------------------------------------------------------------------
			//visualización de gráficos.
			this->ENVIRONMENT_TEST.ShowRender();

			//-------------------------------------------------------------------------
			//impresión.
			cout << "# mostrando graficos." << endl;
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//comando "nexti".
		else if (this->BUFF_USER_COMMAND[0] == "nexti")
		{
			//-------------------------------------------------------------------------
			//si la GUPCI está cargada, entonces.
			if (this->GUPCI_LOADED_FLAG == ON)
			{
				//---------------------------------------------------------------------
				//si está corriendo el programa, entonces.
				if (this->PROGRAM_RUNNING_FLAG == ON)
				{
					//-----------------------------------------------------------------
					//si está en espera de otra iteración, entonces.
					if (this->WAITING_NEXT_ITERATION_FLAG = ON)
					{
						//-------------------------------------------------------------
						//actualización del estado del programa.
						this->ITERATION_TYPE				= NEXT_ITERATION;
						this->WAITING_NEXT_ITERATION_FLAG	= OFF;
					}
				}
				else
				{
					//-----------------------------------------------------------------
					//actualización del estado del programa.
					this->ITERATION_TYPE				= NEXT_ITERATION;
					this->WAITING_NEXT_ITERATION_FLAG	= ON;
					this->PROGRAM_RUNNING_FLAG			= ON;
				}

				//---------------------------------------------------------------------
				//impresión.
				cout << endl;
				cout << "################# Siguiente iteracion del programa #################" << endl;
			}

			//-------------------------------------------------------------------------
			//si no está cargada, entonces imprimir error.
			else
			{
				//---------------------------------------------------------------------
				//impresión de error.
				cout << "# error, la GUPCI no esta cargada." << endl;
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//comando "run".
		else if (this->BUFF_USER_COMMAND[0] == "run")
		{			
			//-------------------------------------------------------------------------
			//si la GUPCI está cargada, entonces.
			if (this->GUPCI_LOADED_FLAG == ON)
			{
				//---------------------------------------------------------------------
				//si está corriendo el programa, entonces.
				if (this->PROGRAM_RUNNING_FLAG == ON)
				{
					//-----------------------------------------------------------------
					//si está en espera de otra iteración, entonces.
					if (this->WAITING_NEXT_ITERATION_FLAG == ON)
					{
						//-------------------------------------------------------------
						//actualización del estado del programa en GUPCI.
						this->BUFF_GUPCI.SetPAUSE_ACTIVE_THREADS_FLAG(OFF);

						//-------------------------------------------------------------
						//actualización del estado del programa.
						this->ITERATION_TYPE				= RUN_PROGRAM;
						this->WAITING_NEXT_ITERATION_FLAG	= OFF;
					}
				}
				else
				{
					//-----------------------------------------------------------------
					//actualización del estado del programa en GUPCI.
					this->BUFF_GUPCI.SetPAUSE_ACTIVE_THREADS_FLAG(OFF);

					//-----------------------------------------------------------------
					//actualización del estado del programa.
					this->ITERATION_TYPE				= RUN_PROGRAM;
					this->WAITING_NEXT_ITERATION_FLAG	= OFF;
					this->PROGRAM_RUNNING_FLAG			= ON;					
				}

				//---------------------------------------------------------------------
				//impresión.
				cout << endl;
				cout << "####################### Programa corriendo #########################" << endl;

				//---------------------------------------------------------------------
				//llamada de función previa.
				GetAsyncKeyState(this->ESC_KEY);

				//---------------------------------------------------------------------
				//bucle de espera por el comando 'ESC'.
				while (true)
				{
					//-----------------------------------------------------------------
					//si se presiona la tecla 'ESC', entonces detener programa.  
					if (GetAsyncKeyState(this->ESC_KEY))
					{
						//-------------------------------------------------------------
						//si la GUPCI está cargada y está corriendo, entonces.
						if (this->GUPCI_LOADED_FLAG == ON || this->PROGRAM_RUNNING_FLAG == ON)
						{
							//---------------------------------------------------------
							//actualización del estado del programa.
							this->WAITING_NEXT_ITERATION_FLAG	= OFF;
							this->PROGRAM_RUNNING_FLAG			= OFF;

							//---------------------------------------------------------
							//actualización del estado del programa en GUPCI.
							this->BUFF_GUPCI.SetPAUSE_ACTIVE_THREADS_FLAG(ON);

							//---------------------------------------------------------
							//impresión.
							cout << endl;
							cout << "################### El programa se ha detenido #####################" << endl;
							cout << "# iteracion: " << this->ITERATIONS_COUNTER << endl;

							//---------------------------------------------------------
							//salida del bucle.
							break;
						}
					}
					
					//-----------------------------------------------------------------
					//pause.
					this_thread::sleep_for(timeout_loop_very_fast);
				}
			}

			//-------------------------------------------------------------------------
			//si no está cargada, entonces imprimir error.
			else
			{
				//---------------------------------------------------------------------
				//impresión de error.
				cout << "# error, la GUPCI no esta cargada." << endl;
			}
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//comando "exit".
		else if (this->BUFF_USER_COMMAND[0] == "exit")
		{
			//-------------------------------------------------------------------------
			//se terminan los threads del render si estos existen.
			this->ENVIRONMENT_TEST.SetExit_flag(ON);

			//-------------------------------------------------------------------------
			//pause.
			this_thread::sleep_for(timeout_loop_slow);
			
			//-------------------------------------------------------------------------
			//se terminan los threads del programa y del usuario.
			this->EXIT_FLAG = ON;	
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//comando no reconocido.
		else 
		{
			//-------------------------------------------------------------------------
			//impresión.
			cout << "# comando no reconocido." << endl;
		}

		//-----------------------------------------------------------------------------
		//pause.
		this_thread::sleep_for(timeout_loop_slow);

	} 
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método thread para la ejecución del programa.
vo GUPC_PROGRAM::ThreadPrograma()
{	
	//---------------------------------------------------------------------------------
	//seteo del tiempo de espera del loop del programa.
	chrono::milliseconds timeout_program_loop(this->TIMEOUT_PROGRAM_LOOP);
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para consulta de recepción de datos de parte del cliente. 
	while (this->EXIT_FLAG == OFF)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//ejecución del programa.
		if (this->PROGRAM_RUNNING_FLAG == ON && this->GUPCI_LOADED_FLAG == ON)
		{			
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//si la bandera de detención esta en ON, entonces imprimir.
			if (this->WAITING_NEXT_ITERATION_FLAG == ON)
			{
				//---------------------------------------------------------------------
				//seteo del tiempo de espera del loop del programa.
				chrono::milliseconds timeout_program_loop_aux(0);
				timeout_program_loop = timeout_program_loop_aux;

				//---------------------------------------------------------------------
				//impresiones.
				this->PrintingInformation();
			}

			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//cambiar solamente cambiar tiempo de espera si la bandera está en OFF.
			else
			{
				//---------------------------------------------------------------------
				//seteo del tiempo de espera del loop del programa.
				chrono::milliseconds timeout_program_loop_aux(this->TIMEOUT_PROGRAM_LOOP);
				timeout_program_loop = timeout_program_loop_aux;
			}

			//-------------------------------------------------------------------------
			//integración de datos en GUPCI.
			//this->BUFF_GUPCI.Input();

			//-------------------------------------------------------------------------
			//pause del programa si la bandera de espera está activa.
			this->PauseIteration();
			
			//-------------------------------------------------------------------------
			//incremento del comtador de iteraciones.
			++this->ITERATIONS_COUNTER;
		}	

		//-----------------------------------------------------------------------------
		//pause.
		this_thread::sleep_for(timeout_program_loop);
	} 	
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#4: método para imprimir información resumen de la ejecución del programa.
vo GUPC_PROGRAM::PrintingInformation()
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//impresiones.
	cout << "--------------------------------------------------------------------" << endl;
	cout << "--------------------------------------------------------------------" << endl;
	cout << "-> iteracion            n:                    " << this->ITERATIONS_COUNTER << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#5: método para pause en iteración del programa.
vo GUPC_PROGRAM::PauseIteration() 
{
	//---------------------------------------------------------------------------------
	//seteo del tiempo de espera del bucle.
	chrono::milliseconds timeout_loop_slow(TIMEOUT_LOOP_FAST);
	
	//---------------------------------------------------------------------------------
	//bucle para esperar un comando del usuario.
	while (this->WAITING_NEXT_ITERATION_FLAG == ON) 
	{
		//-----------------------------------------------------------------------------
		//salida del bucle.
		if (this->EXIT_FLAG == ON) return;
		
		//-----------------------------------------------------------------------------
		//espera.
		this_thread::sleep_for(timeout_loop_slow);
	}

	//---------------------------------------------------------------------------------
	//si la iteración es el tipo NEXT_ITERATION, entonces.
	if (this->ITERATION_TYPE == NEXT_ITERATION)
	{
		//-----------------------------------------------------------------------------
		//seteo de bandera WAITING_NEXT_ITERATION_FLAG.
		this->WAITING_NEXT_ITERATION_FLAG = ON;
	}
	else
	{
		//-----------------------------------------------------------------------------
		//seteo de bandera WAITING_NEXT_ITERATION_FLAG.
		this->WAITING_NEXT_ITERATION_FLAG = OFF;
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: método para cargar GUPCI.
vo GUPC_PROGRAM::LoadGUPCI()
{		
	//---------------------------------------------------------------------------------
	//carga de argumentos para inicialización de GUPCI.
	this->BUFF_UPCI_ARG.Initialize(this->GUPCI_INPUT,
								   this->GUPCI_EVALUATION,
								   this->GUPCI_PROJECTION,
								   this->INIS_AMOUNT_ALLOWED,
								   this->ACIS_AMOUNT_ALLOWED,
								   this->RLIS_AMOUNT_ALLOWED,
								   this->DEFAULT_ACTIVITY_LEVEL,
								   this->MAX_ACTIVITY_LEVEL_ALLOWED,
								   this->MIN_ACTIVITY_LEVEL_ALLOWED,
								   this->KERNEL_RAW_INPUT_THRESHOLD,
								   this->DIF_RAW_INPUT_THRESHOLD,
								   this->STR_CONGRUENCE_THRESHOLD,
								   this->PFRLIS_STRENGTH_THRESHOLD,
								   this->INDFRLIS_STRENGTH_THRESHOLD,
								   this->EVALUATION_THRESHOLD,
								   this->TRANSITION_EVALUATION_THRESHOLD,
								   this->TIMEOUT_CLEAN_IS,
								   this->TIMEOUT_UPDATE_AL_IS);

	//---------------------------------------------------------------------------------
	//inicialización de GUPCI.
	this->BUFF_GUPCI.Initialize(0, this->UPCI_AMOUNT, this->BUFF_UPCI_ARG);
	
	//---------------------------------------------------------------------------------
	//actualización del estado del programa.
	this->GUPCI_LOADED_FLAG = ON;
	
	//---------------------------------------------------------------------------------
	//impresión.
	cout << "# carga exitosa de la GUPCI." << endl;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#2: método para abrir GUPCI.
vo GUPC_PROGRAM::OpenGUPCI(string _fileNameS)
{
	//---------------------------------------------------------------------------------
	//se abre un fichero para cargar una GUPCI.
	if (this->BUFF_GUPCI.Open(_fileNameS, this->GUPCI_INPUT, this->GUPCI_EVALUATION, this->GUPCI_PROJECTION) == SUCCESS)
	{
		//-----------------------------------------------------------------------------
		//impresión.
		cout << "# carga exitosa de la GUPCI: " << ", desde el fichero: " << _fileNameS + ".gu" << endl;
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#3: método para salvar GUPCI.
vo GUPC_PROGRAM::SaveGUPCI(string _fileNameS)
{
	//---------------------------------------------------------------------------------
	//se salva la GUPCI en un fichero.
	if (this->BUFF_GUPCI.Save(_fileNameS) == SUCCESS)
	{
		//-----------------------------------------------------------------------------
		//impresión.
		cout << "# se ha guardado exitosamente la GUPCI: " << ", en el fichero: " << _fileNameS + "_"  + ".gu" << endl;
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//método para obtener los comandos del usuario particionado.
vo GUPC_PROGRAM::GetUserCommand(st _buffer_raw_user_command, vest &_buffer_user_command)
{
	//---------------------------------------------------------------------------------
	//varibles auxiliares.
	int length_buffer_raw_user_command	= in(_buffer_raw_user_command.length());			//largo de _buffer_raw_user_command.
	int start_pos_command				= -1;												//posición inicial del comando.

	//---------------------------------------------------------------------------------
	//limpieza del buffer de comandos del usuario.
	_buffer_user_command.clear();

	//---------------------------------------------------------------------------------
	//bucle para obtener comandos particionados.
	for (int i1 = 0; i1 < length_buffer_raw_user_command; i1++)
	{
		//-----------------------------------------------------------------------------
		//si es distinto a un espacio y si la posición inicial no está definida, 
		//entonces setear posición de inicio.
		if (_buffer_raw_user_command.at(i1) != ' ' && start_pos_command == -1)	start_pos_command = i1;
	
		//-----------------------------------------------------------------------------
		//si es igual a un espacio y si la posición inicial está definida, 
		//entonces setear comando.
		if (_buffer_raw_user_command.at(i1) == ' ' && start_pos_command != -1 || i1 == length_buffer_raw_user_command - 1)
		{
			//-------------------------------------------------------------------------
			//si se ha llegado al fin de la cadena, entonces.
			if (i1 == length_buffer_raw_user_command - 1) ++i1;

			//-------------------------------------------------------------------------
			//seteo del comando en buffer.
			_buffer_user_command.push_back(_buffer_raw_user_command.substr(start_pos_command, i1 - start_pos_command));

			//-------------------------------------------------------------------------
			//reset de la posición inicial.
			start_pos_command = -1;
		}		
	}
}