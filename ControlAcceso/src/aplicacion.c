
#include "aplicacion.h"
#define  TAM_TARJETA sizeof(codigo_tarjeta)
#define  NUMERO_PIN 6

char ESTADO_RX_UART0;
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
	InitUART0();
}

void aplicacion (void)
{
	__RW uint8_t estado=NORMAL;

	while (1)
	{

		if(ESTADO_RX_UART0=='Z')//EL USUARIO PIDIO UNA NUEVA TARJETA
		{
			ESTADO_RX_UART0='0';
			estado=SETEO;
		}


		//CONDICION_CAMBIO_DE ESTADOS

		if (estado==NORMAL)
		{
			 MensajesRX();
			estado_normal ();
		}

		if (estado==SETEO)
		{
			estado_seteo ();
			MensajesRX();
		}

	}

}




void estado_normal (void)
{
	__RW static uint8_t estado = DETECCION;
	__RW static uint32_t codigo_personal = 0;
	__RW static uint8_t codigo_tarjeta [13];
	__RW uint8_t resultado_codigo_personal =BUSY;
	char DATOS_TARJETA_PIN[TAM_TARJETA+NUMERO_PIN+3];// TRAMA DE DATOS A ENVIAR EJEMPLO:"T000000000000-000000"
	static uint8_t flag_LCD = 1;



	if (estado==DETECCION)
	{
		if (flag_LCD) {
			Display_lcd("INGRESE TARJETA ",0,0);
			flag_LCD = 0;
			MODO_NUEVO_EMPLEADO_OFF;
		}
		if (get_RFID(codigo_tarjeta)) //si se encontro una tarjeta
		{
			reproducir_wav(WAV_BIENVENIDO);
	    	reproducir_wav(WAV_INGRESE_CODIGO);
			estado= VALIDACION_CODIGO;
			flag_LCD = 1;
		}
	}



	if (estado==VALIDACION_CODIGO)
	{
		if (flag_LCD) {
			Display_lcd("ID: ",0,0);
			Display_lcd((char *)codigo_tarjeta,0,4);
			flag_LCD = 0;
		}
		resultado_codigo_personal= get_codigo_personal (&codigo_personal);

		resultado_codigo_personal=READY;// descomentar esto cuando este la expansion 3
		if (resultado_codigo_personal==READY) //fue ingresado por el usuario
		{
			//ENVIAR_DATOS_PC;
			codigo_personal=123456; // descomentar esto cuando este la tarjeta
			sprintf(DATOS_TARJETA_PIN,"K%s-%d\r",codigo_tarjeta,codigo_personal);
			EnviarString_0 (DATOS_TARJETA_PIN);
			MensajesRX();
				if (ESTADO_RX_UART0=='B') //para simular pregunto si se apreto la tecla 0 en la exp 3
				{
					Display_lcd("CORRECTO",1,0);
					reproducir_wav (WAV_CLAVE_CORRECTA);
					reproducir_wav (WAV_HASTA_LUEGO);
					bzero(codigo_tarjeta,13);
					codigo_personal=0;
					estado =DETECCION;
					flag_LCD = 1;
					ESTADO_RX_UART0='0';
					resultado_codigo_personal=BUSY;
					return;

				}
			if (ESTADO_RX_UART0=='M')
				{
					Display_lcd("INCORRECTO",1,0);
					reproducir_wav (WAV_CLAVE_INCORRECTA);
					bzero(codigo_tarjeta,13);
					codigo_personal=0;
					estado =DETECCION;
					flag_LCD = 1;
					ESTADO_RX_UART0='0';
					resultado_codigo_personal=BUSY;
					return;

				}



		}
	 if (resultado_codigo_personal== TIEMPO_VENCIDO)
		{
			bzero(codigo_tarjeta,13);
			codigo_personal=0;
			estado =DETECCION;
			flag_LCD = 1;
			return;
		}
	 else
	 {
		 ESTADO_RX_UART0='0';
	 }

	}
}

void estado_seteo (void)
{

	__RW static uint8_t nueva_tarjeta =0;
	__RW static uint8_t estado =DETECCION;
	__RW static uint32_t codigo_personal = 0;
	__RW static char codigo_tarjeta [13];
	__RW uint8_t resultado_codigo_personal =BUSY;
	char DATOS_TARJETA_PIN[TAM_TARJETA+NUMERO_PIN+3];// TRAMA DE DATOS A ENVIAR EJEMPLO:"T000000000000-000000"
MODO_NUEVO_EMPLEADO_ON;
//PARA PROBAR
codigo_personal=123456;// CODIGO DE PRUEBA PORUQUE NO TENGO LA EXPANSION 3
if(nueva_tarjeta==0)
{

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
		//resultado_codigo_personal= get_codigo_personal (&codigo_personal);
		resultado_codigo_personal=READY;

		if (resultado_codigo_personal==READY) //fue ingresado por el usuario
		{
			//ENVIAR_DATOS_SETEO_A_PC;
			sprintf(DATOS_TARJETA_PIN,"T%s-%d\r",codigo_tarjeta,codigo_personal);
			EnviarString_0 (DATOS_TARJETA_PIN);
			ESTADO_RX_UART0='0';
			MODO_NUEVO_EMPLEADO_OFF;

			//reproducir_wav (WAV_HASTA_LUEGO);
			bzero(codigo_tarjeta,13);
			codigo_personal=0;
			estado =DETECCION;
			return;
		}
		if (resultado_codigo_personal== TIEMPO_VENCIDO)
		{
			bzero(codigo_tarjeta,13);
			codigo_personal=0;
			estado =DETECCION;
			return;
		}

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
