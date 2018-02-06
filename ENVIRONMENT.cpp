//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
Nombre Clase : 	  ENVIRONMENT (Clase para renderizar red upci).
Fecha	     :	  18:24 pm 21-01-2015.
Dise�ador    :	  Gustavo Catal�n Ulloa.
*/
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//librerias.
#include "ENVIRONMENT.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: constructor 1.
ENVIRONMENT::ENVIRONMENT()
{

}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//#1: constructor 2.
ENVIRONMENT::ENVIRONMENT(in		_alto,
						 in		_ancho,
						 string	_tituloVentana,	
						 in		_test_node_group_amount,
						 in		_test_node_amount)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicializaci�n de par�metros.
	this->x							= _ancho;												//resoluci�n en X.
	this->y							= _alto;												//resoluci�n en Y.
	this->test_node_group_amount	= _test_node_group_amount;								//cantidad de grupos de nodos.
	this->test_node_amount			= _test_node_amount;									//cantidad de nodos por grupo.									

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//condiciones de ejecuci�n.
	this->update_render_flag		=	OFF;												//bandera para actualizar render.
	this->exit_flag					=	OFF;												//bandera para salir.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicializaci�n de buffer de colores.
	this->color						= new sf::Color[this->test_node_group_amount];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicializaci�n de colores para buffer de colores auxiliar.	
	this->color_aux[0]				= sf::Color::Blue;
	this->color_aux[1]				= sf::Color::Red;
	this->color_aux[2]				= sf::Color::Magenta;
	this->color_aux[3]				= sf::Color::Yellow;
	this->color_aux[4]				= sf::Color::Cyan;
	this->color_aux[5]				= sf::Color::Magenta;
	this->color_aux[6]				= sf::Color::White;
	this->color_aux[7]				= sf::Color::Green;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicializaci�n del contador de colores.
	this->color_counter				= 0;												

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializar buffer de colores por grupos de nodos.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//incremento del contador de colores.
		++color_counter;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si se ha llegado al l�mite del buffer de colores auxiliare, entonces.
		if (this->color_counter == 8) this->color_counter = 0;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//selecci�n del color al grupo de nodos.
		this->color[i1] = this->color_aux[this->color_counter];
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creaci�n de instancias de renderizado textos.
	this->titulovS					= _tituloVentana;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creaci�n de instancias de marco padre.
	this->backgroundP				= new sf::RectangleShape(sf::Vector2f(flo(this->x), flo(this->y)));
	this->backgroundP->setOrigin(sf::Vector2f(0, 0));
	this->backgroundP->setFillColor(sf::Color(100, 100, 100));

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creaci�n de nodos base para renderizado de figuras.
	this->base_nodes				= new sf::CircleShape[2];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creaci�n de grupos de nodos de prueba para renderizado de figuras.
	this->test_nodes				= new sf::CircleShape*[this->test_node_group_amount];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para creaci�n de instancias de renderizado de figuras para nodos de prueba.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//creaci�n de nodos de prueba para renderizado de figuras.
		this->test_nodes[i1] = new sf::CircleShape[this->test_node_amount];
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creaci�n y configuraci�n de fuente de texto.
	this->text_font.loadFromFile("fonts/arial.ttf");

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creaci�n de figuras de textos de renderizado de n�meros sobre nodos de prueba.
	this->nodes_number			= new sf::Text*[this->test_node_group_amount];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para creaci�n de instancias de figuras de textos.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//creaci�n de nodos de prueba para renderizado de figuras de n�meros.
		this->nodes_number[i1] = new sf::Text[this->test_node_amount];
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializaci�n de instancias de figuras de textos.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para inicializaci�n de instancias de figuras de textos.
		for (in i2 = 0; i2 < this->test_node_amount; i2++)
		{
			//-------------------------------------------------------------------------
			//creaci�n y configuraci�n de n�meros.
			this->nodes_number[i1][i2].setFont(this->text_font);
			this->nodes_number[i1][i2].setString(to_string(i2));
			this->nodes_number[i1][i2].setCharacterSize(20);			
			this->nodes_number[i1][i2].setFillColor(sf::Color::Black);
		}
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//tiempo de espera de bucles (milisegundos).
	this->twait						= 100;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializar radio de los nodos base.
	for (in i1 = 0; i1 < 2; i1++)
	{
		//-----------------------------------------------------------------------------
		//inicializaci�n de nodo.
		this->base_nodes[i1].setRadius(10);
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializar radio de los nodos de prueba por grupos.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para inicializar radio de los nodos de prueba.
		for (in i2 = 0; i2 < this->test_node_amount; i2++)
		{
			//-------------------------------------------------------------------------
			//inicializaci�n del radio del nodo.
			this->test_nodes[i1][i2].setRadius(10);
		}		
	}

	//-----------------------------------------------------------------------------
	//inicializaci�n de colores de los nodos base.
	this->base_nodes[0].setFillColor(sf::Color::Black);
	this->base_nodes[1].setFillColor(sf::Color::Green);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializar color de los nodos de prueba por grupos.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para inicializar color de los nodos de prueba.
		for (in i2 = 0; i2 < this->test_node_amount; i2++)
		{
			//-------------------------------------------------------------------------
			//inicializaci�n del color del nodo.
			this->test_nodes[i1][i2].setFillColor(this->color[i1]);
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//destructor.
ENVIRONMENT::~ENVIRONMENT(void)
{
	//---------------------------------------------------------------------------------
	//liberaci�n de memoria.
	delete backgroundP;																	//background padre de renderizaci�n.
	delete [] base_nodes;																//nodos base.
	delete [] test_nodes;																//nodos de prueba.
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//m�todo para seteo de inicializaci�n.
vo ENVIRONMENT::iniENVIRONMENT(in		_alto,
							   in		_ancho,
							   string	_tituloVentana,	     
							   in		_test_node_group_amount,
							   in		_test_node_amount)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicializaci�n de par�metros.
	this->x							= _ancho;												//resoluci�n en X.
	this->y							= _alto;												//resoluci�n en Y.
	this->test_node_group_amount	= _test_node_group_amount;								//cantidad de grupos de nodos.
	this->test_node_amount			= _test_node_amount;									//cantidad de nodos por grupo.									

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//condiciones de ejecuci�n.
	this->update_render_flag		=	OFF;												//bandera para actualizar render.
	this->exit_flag					=	OFF;												//bandera para salir.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicializaci�n de buffer de colores.
	this->color						= new sf::Color[this->test_node_group_amount];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicializaci�n de colores para buffer de colores auxiliar.	
	this->color_aux[0]				= sf::Color::Blue;
	this->color_aux[1]				= sf::Color::Red;
	this->color_aux[2]				= sf::Color::Magenta;
	this->color_aux[3]				= sf::Color::Yellow;
	this->color_aux[4]				= sf::Color::Cyan;
	this->color_aux[5]				= sf::Color::Magenta;
	this->color_aux[6]				= sf::Color::White;
	this->color_aux[7]				= sf::Color::Green;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicializaci�n del contador de colores.
	this->color_counter				= 0;												

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializar buffer de colores por grupos de nodos.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//incremento del contador de colores.
		++color_counter;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//si se ha llegado al l�mite del buffer de colores auxiliare, entonces.
		if (this->color_counter == 8) this->color_counter = 0;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//selecci�n del color al grupo de nodos.
		this->color[i1] = this->color_aux[this->color_counter];
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creaci�n de instancias de renderizado textos.
	this->titulovS					= _tituloVentana;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creaci�n de instancias de marco padre.
	this->backgroundP				= new sf::RectangleShape(sf::Vector2f(flo(this->x), flo(this->y)));
	this->backgroundP->setOrigin(sf::Vector2f(0, 0));
	this->backgroundP->setFillColor(sf::Color(100, 100, 100));

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creaci�n de nodos base para renderizado de figuras.
	this->base_nodes				= new sf::CircleShape[2];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creaci�n de grupos de nodos de prueba para renderizado de figuras.
	this->test_nodes				= new sf::CircleShape*[this->test_node_group_amount];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para creaci�n de instancias de renderizado de figuras para nodos de prueba.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//creaci�n de nodos de prueba para renderizado de figuras.
		this->test_nodes[i1] = new sf::CircleShape[this->test_node_amount];
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creaci�n y configuraci�n de fuente de texto.
	this->text_font.loadFromFile("fonts/arial.ttf");

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creaci�n de figuras de textos de renderizado de n�meros sobre nodos de prueba.
	this->nodes_number			= new sf::Text*[this->test_node_group_amount];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para creaci�n de instancias de figuras de textos.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//creaci�n de nodos de prueba para renderizado de figuras de n�meros.
		this->nodes_number[i1] = new sf::Text[this->test_node_amount];
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializaci�n de instancias de figuras de textos.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para inicializaci�n de instancias de figuras de textos.
		for (in i2 = 0; i2 < this->test_node_amount; i2++)
		{
			//-------------------------------------------------------------------------
			//creaci�n y configuraci�n de n�meros.
			this->nodes_number[i1][i2].setFont(this->text_font);
			this->nodes_number[i1][i2].setString(to_string(i2));
			this->nodes_number[i1][i2].setCharacterSize(20);			
			this->nodes_number[i1][i2].setFillColor(sf::Color::Black);
		}
	}
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//tiempo de espera de bucles (milisegundos).
	this->twait						= 100;
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializar radio de los nodos base.
	for (in i1 = 0; i1 < 2; i1++)
	{
		//-----------------------------------------------------------------------------
		//inicializaci�n de nodo.
		this->base_nodes[i1].setRadius(10);
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializar radio de los nodos de prueba por grupos.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para inicializar radio de los nodos de prueba.
		for (in i2 = 0; i2 < this->test_node_amount; i2++)
		{
			//-------------------------------------------------------------------------
			//inicializaci�n del radio del nodo.
			this->test_nodes[i1][i2].setRadius(10);
		}		
	}

	//-----------------------------------------------------------------------------
	//inicializaci�n de colores de los nodos base.
	this->base_nodes[0].setFillColor(sf::Color::Black);
	this->base_nodes[1].setFillColor(sf::Color::Green);

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicializar color de los nodos de prueba por grupos.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para inicializar color de los nodos de prueba.
		for (in i2 = 0; i2 < this->test_node_amount; i2++)
		{
			//-------------------------------------------------------------------------
			//inicializaci�n del color del nodo.
			this->test_nodes[i1][i2].setFillColor(this->color[i1]);
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//m�todo de entrada de datos de las posiciones de los nodos.
void ENVIRONMENT::NodePositionInput(dou _new_positions_base_nodes[2][2], dou ***_new_positions_test_nodes)
{
	//---------------------------------------------------------------------------------
	//seteo de posiciones de nodos base.
	this->base_nodes[0].setPosition(sf::Vector2f(flo(_new_positions_base_nodes[0][0]), flo(this->y - _new_positions_base_nodes[0][1])));
	this->base_nodes[1].setPosition(sf::Vector2f(flo(_new_positions_base_nodes[1][0]), flo(this->y - _new_positions_base_nodes[1][1])));

	//---------------------------------------------------------------------------------
	//paralelizaci�n del bucle for.
	#pragma omp parallel for

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para setear posiciones de los nodos de prueba por grupos.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para setear posiciones de los nodos de prueba.
		for (in i2 = 0; i2 < this->test_node_amount; i2++)
		{
			//-------------------------------------------------------------------------
			//seteo de posiciones del nodo.
			this->test_nodes[i1][i2].setPosition(sf::Vector2f(flo(_new_positions_test_nodes[i1][i2][0]), flo(this->y - _new_positions_test_nodes[i1][i2][1])));

			//-------------------------------------------------------------------------
			//seteo de posiciones de los textos de n�meros de los nodos.
			this->nodes_number[i1][i2].setPosition(flo(_new_positions_test_nodes[i1][i2][0] + 4), flo(this->y - _new_positions_test_nodes[i1][i2][1] - 3));
		}
	}
	
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'update_render_flag'.
	this->SetUpdate_render_flag(ON);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//m�todo para mostrar render.
void ENVIRONMENT::ShowRender(void)
{
	//---------------------------------------------------------------------------------
	//thread.
	this->threadtEventos = std::thread(&ENVIRONMENT::ThreadEventos, this);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//m�todo thread para controlar eventos.
void ENVIRONMENT::ThreadEventos(void)
{
	//---------------------------------------------------------------------------------
	//creaci�n de instancias de ventana de render.
	this->rV = new sf::RenderWindow(sf::VideoMode(x, y), titulovS, sf::Style::Close);

	//---------------------------------------------------------------------------------
	//desactivar contexto.
	this->rV->setActive(false);
	
	//---------------------------------------------------------------------------------
	//thread.
	this->threadUpdateRender = std::thread(&ENVIRONMENT::ThreadUpdateRenderNodes, this);
	
	//---------------------------------------------------------------------------------
	//bucle de eventos.
	while (this->rV->isOpen() && this->GetExit_flag() == OFF)
	{
		//-----------------------------------------------------------------------------
		//creaci�n de objeto evento para analizar eventos.
		sf::Event event;
		
		//-----------------------------------------------------------------------------
		//revisi�n de eventos de la ventana.
		while (this->rV->pollEvent(event) && this->GetExit_flag() == OFF)
		{
			//-------------------------------------------------------------------------
			//evento cerrar ventana.
			if (event.type == sf::Event::Closed)
			{
				//---------------------------------------------------------------------
				//cierre de ventana.
				this->rV->close();			
			}

			//-------------------------------------------------------------------------
			//retardo.
			Sleep(twait);
		}

		//-----------------------------------------------------------------------------
		//retardo.
		Sleep(twait);
	}

	//---------------------------------------------------------------------------------
	//cierre del hilo threadUpdateRenderSignals.
	this->threadUpdateRender.join();

	//---------------------------------------------------------------------------------
	//activar contexto.
	this->rV->setActive(true);

	//---------------------------------------------------------------------------------
	//cierre de ventana.
	if (this->rV->isOpen()) this->rV->close();
	
	//---------------------------------------------------------------------------------
	//eliminaci�n en memoria de rV.
	delete[] this->rV;
	
	//---------------------------------------------------------------------------------
	//cierre del hilo.
	this->threadtEventos.detach();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//m�todo thread para actualizar renderizaci�n de nodos.
void ENVIRONMENT::ThreadUpdateRenderNodes(void)
{
	//---------------------------------------------------------------------------------
	//activar contexto.
	this->rV->setActive(true);

	//---------------------------------------------------------------------------------
	//limpieza de la ventana.
	this->rV->clear(sf::Color(255, 255, 255));

	//---------------------------------------------------------------------------------
	//renderizar background padre.
	this->rV->draw(*backgroundP);			

	//---------------------------------------------------------------------------------
	//mostrar.
	this->rV->display();
	
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle mientras la ventana siga abierta.
	while (this->rV->isOpen() && this->GetExit_flag() == OFF)
	{
		//-----------------------------------------------------------------------------
		//bucle para capturar estado de la bandera 'update_render_flag' y de la badera de cierre.
		while (this->rV->isOpen() && this->GetUpdate_render_flag() == OFF && this->GetExit_flag() == OFF)	Sleep(twait);

		//-----------------------------------------------------------------------------
		//seteo del estado de la bandera 'update_render_flag'.
		this->SetUpdate_render_flag(OFF);

		//-----------------------------------------------------------------------------
		//limpieza de la ventana.
		this->rV->clear(sf::Color(255, 255, 255));

		//-----------------------------------------------------------------------------
		//renderizar background padre.
		this->rV->draw(*backgroundP);

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para renderizar nodos de prueba por grupos.
		for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
		{
			//-------------------------------------------------------------------------
			//-------------------------------------------------------------------------
			//bucle para renderizar nodos de prueba.
			for (in i2 = 0; i2 < this->test_node_amount; i2++)
			{
				//---------------------------------------------------------------------
				//renderizar nodo.
				this->rV->draw(this->test_nodes[i1][i2]);

				//---------------------------------------------------------------------
				//renderizar de texto de n�meros de los nodos.
				this->rV->draw(this->nodes_number[i1][i2]);
			}
		}
		
		//-----------------------------------------------------------------------------
		//renderizaci�n de nodos base.
		this->rV->draw(this->base_nodes[0]);
		this->rV->draw(this->base_nodes[1]);

		//-----------------------------------------------------------------------------
		//mostrar.
		this->rV->display();
	}	

	//---------------------------------------------------------------------------------
	//desactivar contexto.
	this->rV->setActive(false);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//m�todo Get para obtener la bandera 'update_render_flag'.
in ENVIRONMENT::GetUpdate_render_flag(void)
{
	//---------------------------------------------------------------------------------
	//retorno del estado de la bandera.
	return this->update_render_flag;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//m�todo Get para obtener la bandera 'exit_flag'.
in ENVIRONMENT::GetExit_flag(void)
{
	//---------------------------------------------------------------------------------
	//retorno del estado de la bandera.
	return this->exit_flag;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//m�todo set para setear la bandera 'update_render_flag'.
void ENVIRONMENT::SetUpdate_render_flag(in _status)
{
	//---------------------------------------------------------------------------------
	//retorno del estado de la bandera.
	this->update_render_flag = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//m�todo set para setear la bandera 'exit_flag'.
void ENVIRONMENT::SetExit_flag(in _status)
{
	//---------------------------------------------------------------------------------
	//retorno del estado de la bandera.
	this->exit_flag = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//m�todo para hacer casting de dou a string.
string ENVIRONMENT::CastNumsGridFaS(dou _numeroF)
{
	//---------------------------------------------------------------------------------
	//variables auxiliar.
	string numeroS;

	//---------------------------------------------------------------------------------
	//conversi�n.
	numeroS = to_string(in(_numeroF)) + "." + to_string(abs(in(_numeroF*100) - in(_numeroF)*100));

	//---------------------------------------------------------------------------------
	//retorno.
	return numeroS;
}




