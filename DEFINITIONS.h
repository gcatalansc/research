#pragma once
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//definiciones.

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//constantes de tipos de integración del Hilo.
#define		WITHOUT_DIF_AL_INTEGRATION			1												//integración sin diferenciación de estructuras ni retensión del nivel de actividad.
#define		WITHOUT_DIF_INTEGRATION				2												//integración sin diferenciación de estructuras.
#define		FULL_INTEGRATION					3												//integración completa.

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//constantes de tipos IS.
#define		INIS_SD_TYPE						1												//estructura de entrada tipo SD.
#define		INIS_VD_TYPE						2												//estructura de entrada tipo VD.
#define		INIS_MD_TYPE						3												//estructura de entrada tipo MD.
#define		ACIS_TYPE							4												//estructura de acción.
#define		SRLIS_TYPE							5												//estructura de relación simple.
#define		PFRLIS_TYPE							6												//estructura de relación de flujo puro.
#define		INDFRLIS_SD_TYPE					7												//estructura de relación de flujo diferencial de entradas tipo SD.
#define		INDFRLIS_VD_TYPE					8												//estructura de relación de flujo diferencial de entradas tipo VD.
#define		INDFRLIS_MD_TYPE					9												//estructura de relación de flujo diferencial de entradas tipo MD.
#define		ACDFRLIS_TYPE						10												//estructura de relación de flujo diferencial de acciones.
#define		INPRRLIS_SD_TYPE					11												//estructura de relación proporcional de estructuras "INDFRLIS" tipo SD.
#define		INPRRLIS_VD_TYPE					12												//estructura de relación proporcional de estructuras "INDFRLIS" tipo VD.
#define		INPRRLIS_MD_TYPE					13												//estructura de relación proporcional de estructuras "INDFRLIS" tipo MD.
#define		ACPRRLIS_TYPE						14												//estructura de relación proporcional de estructuras "ACDFRLIS".	

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//constante para estados de realidad.
#define		RS_EFFECTIVE						1												//estado de realidad efectivo.
#define		RS_PROJECTED						2												//estado de realidad proyectado.

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//constantes para tipos de evaluaciones de transiciones de entradas.
#define		POSITIVE_TRANSITION					1												//transición positiva.
#define		NEGATIVE_TRANSITION					2												//transición negativa.
#define		NEUTRAL_POSITIVE_TRANSITION			3												//transición neutral postiva.

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//constantes para comparativa de Hilos ganadores.
#define		FIRST_THREAD_HAS_WON				1												//el primer Hilo ganador ha ganado.
#define		SECOND_THREAD_HAS_WON				2												//el segundo Hilo ganador ha ganado.

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//constantes de estados de banderas.
#define		ON									1												//estado activo.
#define		OFF									0												//estado inactivo.

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//constantes de estados de ejecución de métodos.
#define		SUCCESS								1												//estado exitoso.
#define		FAILURE								0												//estado fallo.

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//constantes para tiempos de espera.
#define		TIMEOUT_LOOP_SLOW					200												//tiempo de espera de bucles de consulta (ms).
#define		TIMEOUT_LOOP_FAST					100												//tiempo de espera de bucles de consulta (ms).
#define		TIMEOUT_LOOP_VERY_FAST				10												//tiempo de espera de bucles de consulta (ms).

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//definiciones para el loop del programa.
#define		NEXT_ITERATION						1												//siguiente iteración.
#define		RUN_PROGRAM							2												//correr programa.
#define		STOP_PROGRAM						3												//detener programa.

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//definiciones para impresión de buffers.
#define		DEF_BUFF_BA							1												//buffers de banderas.
#define		DEF_BUFF_NU							2												//buffers de núcleo.
#define		DEF_BUFF_INIS_SD					3												//buffers de estructuras INIS_SD.
#define		DEF_BUFF_INIS_VD					4												//buffers de estructuras INIS_VD.
#define		DEF_BUFF_INIS_MD					5												//buffers de estructuras INIS_MD.
#define		DEF_BUFF_ACIS						6												//buffers de estructuras ACIS.
#define		DEF_BUFF_PFRLIS						7												//buffers de estructuras PFRLIS.
#define		DEF_BUFF_INDFRLIS_SD				8												//buffers de estructuras INDFRLIS_SD.
#define		DEF_BUFF_INDFRLIS_VD				9												//buffers de estructuras INDFRLIS_VD.
#define		DEF_BUFF_INDFRLIS_MD				10												//buffers de estructuras INDFRLIS_MD.
#define		DEF_BUFF_ACDFRLIS					11												//buffers de estructuras ACDFRLIS.
#define		DEF_BUFF_INPRRLIS_SD				12												//buffers de estructuras INPRRLIS_SD.
#define		DEF_BUFF_INPRRLIS_VD				13												//buffers de estructuras INPRRLIS_VD.
#define		DEF_BUFF_INPRRLIS_MD				14												//buffers de estructuras INPRRLIS_MD.
#define		DEF_BUFF_ACPRRLIS					15												//buffers de estructuras ACPRRLIS.
#define		DEF_BUFF_INIS_SD_CAN				16												//buffers de INIS_SD candidatas.
#define		DEF_BUFF_INIS_VD_CAN				17												//buffers de INIS_VD candidatas.
#define		DEF_BUFF_INIS_MD_CAN				18												//buffers de INIS_MD candidatas.
#define		DEF_BUFF_ACIS_CAN					19												//buffers de ACIS candidatas.
#define		DEF_BUFF_INDFRLIS_SD_CAN			20												//buffers de INDFRLIS_SD candidatas.
#define		DEF_BUFF_INDFRLIS_VD_CAN			21												//buffers de INDFRLIS_VD candidatas.
#define		DEF_BUFF_INDFRLIS_MD_CAN			22												//buffers de INDFRLIS_MD candidatas.
#define		DEF_BUFF_ACDFRLIS_CAN				23												//buffers de ACDFRLIS candidatas.
#define		DEF_BUFF_INPRRLIS_SD_CAN			24												//buffers de INPRRLIS_SD candidatas.
#define		DEF_BUFF_INPRRLIS_VD_CAN			25												//buffers de INPRRLIS_VD candidatas.
#define		DEF_BUFF_INPRRLIS_MD_CAN			26												//buffers de INPRRLIS_MD candidatas.
#define		DEF_BUFF_ACPRRLIS_CAN				27												//buffers de ACPRRLIS candidatas.
#define		DEF_BUFF_EiX_CAN_AUX				28												//buffer auxiliares para estructuras candidatas.
#define		DEF_BUFF_ID_UPCI_INIS_SD_CAN		29												//buffers de id de las upci con estructuras INIS_SD candidatas.
#define		DEF_BUFF_ID_UPCI_INIS_VD_CAN		30												//buffers de id de las upci con estructuras INIS_VD candidatas.
#define		DEF_BUFF_ID_UPCI_INIS_MD_CAN		31												//buffers de id de las upci con estructuras INIS_MD candidatas.
#define		DEF_BUFF_ID_UPCI_ACIS_CAN			32												//buffers de id de las upci con estructuras ACIS candidatas.
#define		DEF_BUFF_ID_UPCI_INDFRLIS_SD_CAN	33												//buffers de id de las upci con estructuras INDFRLIS_SD candidatas.
#define		DEF_BUFF_ID_UPCI_INDFRLIS_VD_CAN	34												//buffers de id de las upci con estructuras INDFRLIS_VD candidatas.
#define		DEF_BUFF_ID_UPCI_INDFRLIS_MD_CAN	35												//buffers de id de las upci con estructuras INDFRLIS_MD candidatas.
#define		DEF_BUFF_ID_UPCI_ACDFRLIS_CAN		36												//buffers de id de las upci con estructuras ACDFRLIS candidatas.
#define		DEF_BUFF_ID_UPCI_INPRRLIS_SD_CAN	37												//buffers de id de las upci con estructuras INPRRLIS_SD candidatas.
#define		DEF_BUFF_ID_UPCI_INPRRLIS_VD_CAN	38												//buffers de id de las upci con estructuras INPRRLIS_VD candidatas.
#define		DEF_BUFF_ID_UPCI_INPRRLIS_MD_CAN	39												//buffers de id de las upci con estructuras INPRRLIS_MD candidatas.
#define		DEF_BUFF_ID_UPCI_ACPRRLIS_CAN		40												//buffers de id de las upci con estructuras ACPRRLIS candidatas.
#define		DEF_BUFF_STR_DIS					41												//buffers de estructuras disponibles.
#define		DEF_BUFF_STR_CRE					42												//buffers de estructuras creadas.
#define		DEF_BUFF_STR_RE						43												//buffers de estructuras reconocidas.
#define		DEF_BUFF_CANT_UPCI_STR_SUS			44												//buffers de ids de estructuras supendidas y de cantidad de upci y estructuras suspendidas.
#define		DEF_BUFF_CANT_EST					45												//buffer de cantidad de estructuras existentes.
#define		DEF_BUFF_CANT_EXP					46												//buffer de cantidad de expansiones.
#define		DEF_BUFF_MAX_ID_EST					47												//buffers de máximos id de estructuras.







