//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/*
Nombre Clase : 	  ENVIRONMENT (Clase para renderizar red upci).
Fecha	     :	  18:24 pm 21-01-2015.
Diseñador    :	  Gustavo Catalán Ulloa.
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
	//inicialización de parámetros.
	this->x							= _ancho;												//resolución en X.
	this->y							= _alto;												//resolución en Y.
	this->test_node_group_amount	= _test_node_group_amount;								//cantidad de grupos de nodos.
	this->test_node_amount			= _test_node_amount;									//cantidad de nodos por grupo.									

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//condiciones de ejecución.
	this->update_render_flag		=	OFF;												//bandera para actualizar render.
	this->exit_flag					=	OFF;												//bandera para salir.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de buffer de colores.
	this->color						= new sf::Color[this->test_node_group_amount];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de colores para buffer de colores auxiliar.	
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
	//inicialización del contador de colores.
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
		//si se ha llegado al límite del buffer de colores auxiliare, entonces.
		if (this->color_counter == 8) this->color_counter = 0;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//selección del color al grupo de nodos.
		this->color[i1] = this->color_aux[this->color_counter];
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de instancias de renderizado textos.
	this->titulovS					= _tituloVentana;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de instancias de marco padre.
	this->backgroundP				= new sf::RectangleShape(sf::Vector2f(flo(this->x), flo(this->y)));
	this->backgroundP->setOrigin(sf::Vector2f(0, 0));
	this->backgroundP->setFillColor(sf::Color(100, 100, 100));

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de nodos base para renderizado de figuras.
	this->base_nodes				= new sf::CircleShape[2];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de grupos de nodos de prueba para renderizado de figuras.
	this->test_nodes				= new sf::CircleShape*[this->test_node_group_amount];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para creación de instancias de renderizado de figuras para nodos de prueba.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//creación de nodos de prueba para renderizado de figuras.
		this->test_nodes[i1] = new sf::CircleShape[this->test_node_amount];
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación y configuración de fuente de texto.
	this->text_font.loadFromFile("fonts/arial.ttf");

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de figuras de textos de renderizado de números sobre nodos de prueba.
	this->nodes_number			= new sf::Text*[this->test_node_group_amount];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para creación de instancias de figuras de textos.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//creación de nodos de prueba para renderizado de figuras de números.
		this->nodes_number[i1] = new sf::Text[this->test_node_amount];
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicialización de instancias de figuras de textos.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para inicialización de instancias de figuras de textos.
		for (in i2 = 0; i2 < this->test_node_amount; i2++)
		{
			//-------------------------------------------------------------------------
			//creación y configuración de números.
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
		//inicialización de nodo.
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
			//inicialización del radio del nodo.
			this->test_nodes[i1][i2].setRadius(10);
		}		
	}

	//-----------------------------------------------------------------------------
	//inicialización de colores de los nodos base.
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
			//inicialización del color del nodo.
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
	//liberación de memoria.
	delete backgroundP;																	//background padre de renderización.
	delete [] base_nodes;																//nodos base.
	delete [] test_nodes;																//nodos de prueba.
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//método para seteo de inicialización.
vo ENVIRONMENT::iniENVIRONMENT(in		_alto,
							   in		_ancho,
							   string	_tituloVentana,	     
							   in		_test_node_group_amount,
							   in		_test_node_amount)
{
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de parámetros.
	this->x							= _ancho;												//resolución en X.
	this->y							= _alto;												//resolución en Y.
	this->test_node_group_amount	= _test_node_group_amount;								//cantidad de grupos de nodos.
	this->test_node_amount			= _test_node_amount;									//cantidad de nodos por grupo.									

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//condiciones de ejecución.
	this->update_render_flag		=	OFF;												//bandera para actualizar render.
	this->exit_flag					=	OFF;												//bandera para salir.

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de buffer de colores.
	this->color						= new sf::Color[this->test_node_group_amount];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//inicialización de colores para buffer de colores auxiliar.	
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
	//inicialización del contador de colores.
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
		//si se ha llegado al límite del buffer de colores auxiliare, entonces.
		if (this->color_counter == 8) this->color_counter = 0;

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//selección del color al grupo de nodos.
		this->color[i1] = this->color_aux[this->color_counter];
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de instancias de renderizado textos.
	this->titulovS					= _tituloVentana;

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de instancias de marco padre.
	this->backgroundP				= new sf::RectangleShape(sf::Vector2f(flo(this->x), flo(this->y)));
	this->backgroundP->setOrigin(sf::Vector2f(0, 0));
	this->backgroundP->setFillColor(sf::Color(100, 100, 100));

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de nodos base para renderizado de figuras.
	this->base_nodes				= new sf::CircleShape[2];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de grupos de nodos de prueba para renderizado de figuras.
	this->test_nodes				= new sf::CircleShape*[this->test_node_group_amount];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para creación de instancias de renderizado de figuras para nodos de prueba.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//creación de nodos de prueba para renderizado de figuras.
		this->test_nodes[i1] = new sf::CircleShape[this->test_node_amount];
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación y configuración de fuente de texto.
	this->text_font.loadFromFile("fonts/arial.ttf");

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//creación de figuras de textos de renderizado de números sobre nodos de prueba.
	this->nodes_number			= new sf::Text*[this->test_node_group_amount];

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para creación de instancias de figuras de textos.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//creación de nodos de prueba para renderizado de figuras de números.
		this->nodes_number[i1] = new sf::Text[this->test_node_amount];
	}

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//bucle para inicialización de instancias de figuras de textos.
	for (in i1 = 0; i1 < this->test_node_group_amount; i1++)
	{
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//bucle para inicialización de instancias de figuras de textos.
		for (in i2 = 0; i2 < this->test_node_amount; i2++)
		{
			//-------------------------------------------------------------------------
			//creación y configuración de números.
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
		//inicialización de nodo.
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
			//inicialización del radio del nodo.
			this->test_nodes[i1][i2].setRadius(10);
		}		
	}

	//-----------------------------------------------------------------------------
	//inicialización de colores de los nodos base.
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
			//inicialización del color del nodo.
			this->test_nodes[i1][i2].setFillColor(this->color[i1]);
		}
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//método de entrada de datos de las posiciones de los nodos.
void ENVIRONMENT::NodePositionInput(dou _new_positions_base_nodes[2][2], dou ***_new_positions_test_nodes)
{
	//---------------------------------------------------------------------------------
	//seteo de posiciones de nodos base.
	this->base_nodes[0].setPosition(sf::Vector2f(flo(_new_positions_base_nodes[0][0]), flo(this->y - _new_positions_base_nodes[0][1])));
	this->base_nodes[1].setPosition(sf::Vector2f(flo(_new_positions_base_nodes[1][0]), flo(this->y - _new_positions_base_nodes[1][1])));

	//---------------------------------------------------------------------------------
	//paralelización del bucle for.
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
			//seteo de posiciones de los textos de números de los nodos.
			this->nodes_number[i1][i2].setPosition(flo(_new_positions_test_nodes[i1][i2][0] + 4), flo(this->y - _new_positions_test_nodes[i1][i2][1] - 3));
		}
	}
	
	//---------------------------------------------------------------------------------
	//seteo del estado de la bandera 'update_render_flag'.
	this->SetUpdate_render_flag(ON);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//método para mostrar render.
void ENVIRONMENT::ShowRender(void)
{
	//---------------------------------------------------------------------------------
	//thread.
	this->threadtEventos = std::thread(&ENVIRONMENT::ThreadEventos, this);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//método thread para controlar eventos.
void ENVIRONMENT::ThreadEventos(void)
{
	//---------------------------------------------------------------------------------
	//creación de instancias de ventana de render.
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
		//creación de objeto evento para analizar eventos.
		sf::Event event;
		
		//-----------------------------------------------------------------------------
		//revisión de eventos de la ventana.
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
	//eliminación en memoria de rV.
	delete[] this->rV;
	
	//---------------------------------------------------------------------------------
	//cierre del hilo.
	this->threadtEventos.detach();
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//método thread para actualizar renderización de nodos.
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
				//renderizar de texto de números de los nodos.
				this->rV->draw(this->nodes_number[i1][i2]);
			}
		}
		
		//-----------------------------------------------------------------------------
		//renderización de nodos base.
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
//método Get para obtener la bandera 'update_render_flag'.
in ENVIRONMENT::GetUpdate_render_flag(void)
{
	//---------------------------------------------------------------------------------
	//retorno del estado de la bandera.
	return this->update_render_flag;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//método Get para obtener la bandera 'exit_flag'.
in ENVIRONMENT::GetExit_flag(void)
{
	//---------------------------------------------------------------------------------
	//retorno del estado de la bandera.
	return this->exit_flag;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//método set para setear la bandera 'update_render_flag'.
void ENVIRONMENT::SetUpdate_render_flag(in _status)
{
	//---------------------------------------------------------------------------------
	//retorno del estado de la bandera.
	this->update_render_flag = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//método set para setear la bandera 'exit_flag'.
void ENVIRONMENT::SetExit_flag(in _status)
{
	//---------------------------------------------------------------------------------
	//retorno del estado de la bandera.
	this->exit_flag = _status;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//método para hacer casting de dou a string.
string ENVIRONMENT::CastNumsGridFaS(dou _numeroF)
{
	//---------------------------------------------------------------------------------
	//variables auxiliar.
	string numeroS;

	//---------------------------------------------------------------------------------
	//conversión.
	numeroS = to_string(in(_numeroF)) + "." + to_string(abs(in(_numeroF*100) - in(_numeroF)*100));

	//---------------------------------------------------------------------------------
	//retorno.
	return numeroS;
}




