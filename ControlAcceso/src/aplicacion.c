
#include "aplicacion.h"






void Inicializar ( void )
{
	InicPLL ();
	inic_GPIO ();
	InitGPIOs_Exp3 ();
	inic_systick ();
	rtc_initialize ();


	// la inicializacion del wav, del dac y del timer debe estar en ese orden!
	inic_dac ();
	inic_wav();
	inic_timer0 ();
	/////******

	Inic_LCD();
	Inic_UART1();
}

void aplicacion (void)
{
	__RW uint8_t estado=NORMAL;

	while (1)
	{

		//CONDICION_CAMBIO_DE ESTADOS

		if (estado==NORMAL)
		{
			estado_normal ();
		}

		if (estado==SETEO)
		{
			estado_seteo ();
		}
    	//ejemplo_uart1 ();
	}

}




void estado_normal (void)
{
	__RW static uint8_t estado = DETECCION;
	__RW static uint32_t codigo_personal = 0;
	__RW static uint8_t codigo_tarjeta [13];
	__RW uint8_t resultado_codigo_personal =BUSY;
	if (estado==DETECCION)
	{
		Display_lcd("INGRESE TARJETA ",0,0);
		if (get_RFID(codigo_tarjeta)) //si se encontro una tarjeta
		{
		reproducir_wav(WAV_BIENVENIDO);
	    reproducir_wav(WAV_INGRESE_CODIGO);
		estado= VALIDACION_CODIGO;
		}
	}



	if (estado==VALIDACION_CODIGO)
	{
		Display_lcd(" INGRESE CODIGO ",0,0);
		resultado_codigo_personal= get_codigo_personal (&codigo_personal);
		if (resultado_codigo_personal==READY) //fue ingresado por el usuario
		{
			//ENVIAR_DATOS_PC;


				if (CODIGO_CORRECTO) //para simular pregunto si se apreto la tecla 0 en la exp 3
				{
					reproducir_wav (WAV_CLAVE_CORRECTA);
					reproducir_wav (WAV_HASTA_LUEGO);
					bzero(codigo_tarjeta,13);
					codigo_personal=0;
					estado =DETECCION;

				}
				else if (CODIGO_INCORRECTO)
				{
					reproducir_wav (WAV_CLAVE_INCORRECTA);
					bzero(codigo_tarjeta,13);
					codigo_personal=0;
					estado =DETECCION;
				}



		}
		else if (get_pin(KEY0, ACTIVO_BAJO)/*resultado_codigo_personal== TIEMPO_VENCIDO*/)
		{
			bzero(codigo_tarjeta,13);
			codigo_personal=0;
			estado =DETECCION;
		}


	}
}

void estado_seteo (void)
{
	__RW static uint8_t estado =DETECCION;
	__RW static uint32_t codigo_personal = 0;
	__RW static uint8_t codigo_tarjeta [13];
	__RW uint8_t resultado_codigo_personal =BUSY;


	if (estado==DETECCION )
	{
		if (get_RFID (codigo_tarjeta))
		{
			reproducir_wav(WAV_BIENVENIDO);
			reproducir_wav(WAV_INGRESE_CODIGO);
			estado= INGRESO_CODIGO;

		}
	}
	if (estado==INGRESO_CODIGO )
	{
		resultado_codigo_personal= get_codigo_personal (&codigo_personal);

		if (resultado_codigo_personal==READY) //fue ingresado por el usuario
		{
			//ENVIAR_DATOS_SETEO_A_PC;
			reproducir_wav (WAV_HASTA_LUEGO);
			bzero(codigo_tarjeta,13);
			codigo_personal=0;
			estado =DETECCION;
		}
		else if (resultado_codigo_personal== TIEMPO_VENCIDO)
		{
			bzero(codigo_tarjeta,13);
			codigo_personal=0;
			estado =DETECCION;
		}

	}

}




void ejemplo_uart1 () {
	static uint8_t aux[13];
	Display_lcd("INGRESE TARJETA",0,0);
	if (get_RFID(aux)) {
		//WComando8(LCD_CLEAR);
		if (!(strcmp((char *)aux, "540022C7AE1F"))) {
			set_pin(RGBR, 0);
		}
		else if (!(strcmp((char *)aux, "540021EABB24"))) {
			set_pin(RGBR, 1);
		}
		Display_lcd((char *) aux,1,1);
	}
}
