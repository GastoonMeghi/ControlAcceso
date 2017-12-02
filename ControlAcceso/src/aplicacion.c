
#include "aplicacion.h"
#define  TAM_TARJETA sizeof(codigo_tarjeta)
#define  NUMERO_PIN 6
#define ARMAR_TRAMA_DE_DATOS_INGRESO sprintf(DATOS_TARJETA_PIN,"K%s-%d\r",codigo_tarjeta,codigo_personal)
#define ARMAR_TRAMA_DE_DATOS_NUEVA_TARJETA sprintf(DATOS_TARJETA_PIN,"T%s-%d\r",codigo_tarjeta,codigo_personal)
char ESTADO_RX_UART0;
uint8_t ESTADO_TARJETA_NUEVA_INGRESADA;
uint8_t soft_timer;
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
	ESTADO_TARJETA_NUEVA_INGRESADA=0;
	while (1)
	{
		MensajesRX();
		if(ESTADO_RX_UART0=='Z')//EL USUARIO PIDIO UNA NUEVA TARJETA
		{
			ESTADO_RX_UART0='0';
			estado=SETEO;
		}


		if(ESTADO_TARJETA_NUEVA_INGRESADA==1)//EL USUARIO PIDIO UNA NUEVA TARJETA
			{
			ESTADO_TARJETA_NUEVA_INGRESADA=0;
				estado=NORMAL;
				MODO_NUEVO_EMPLEADO_OFF;
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
		}

	}

}




void estado_normal (void)
{
	__RW static uint8_t estado = DETECCION;
	__RW static uint8_t flag_ingreso =1;
	__RW static uint32_t codigo_personal = 0;
	__RW static uint8_t codigo_tarjeta [13];
	static __RW uint8_t resultado_codigo_personal =BUSY;
	char DATOS_TARJETA_PIN[TAM_TARJETA+NUMERO_PIN+3];// TRAMA DE DATOS A ENVIAR EJEMPLO:"T000000000000-000000"
	static char OLD_TRAMA_DATOS[TAM_TARJETA+NUMERO_PIN+3];
	static uint8_t flag_LCD = 1;
	static uint8_t flag_LCD3 = 1;

	static uint8_t enviar=0;
	MODO_NUEVO_EMPLEADO_OFF;


	if (estado==DETECCION)
	{
		if (flag_LCD) {
			Display_lcd("INGRESE TARJETA ",0,0);
			Display_lcd("                ",1,0);
			flag_LCD = 0;
			MODO_NUEVO_EMPLEADO_OFF;
		}
		if (get_RFID(codigo_tarjeta)) //si se encontro una tarjeta
		{
			reproducir_wav(WAV_BIENVENIDO);
	    	reproducir_wav(WAV_INGRESE_CODIGO);
			estado= VALIDACION_CODIGO;
			Display_lcd("ID: ",0,0);
			Display_lcd((char *)codigo_tarjeta,0,4);
			Display_lcd("INGRESE CODIGO    ",1,0);

			flag_LCD = 1;
		}
	}



	if (estado==VALIDACION_CODIGO)
	{
		if(flag_ingreso)
		resultado_codigo_personal= get_codigo_personal (&codigo_personal);

		//resultado_codigo_personal=READY;// comentar esto cuando este la expansion 3
		if (resultado_codigo_personal==READY) //fue ingresado por el usuario
		{
			//ENVIAR_DATOS_PC;
			//codigo_personal=123456; // comentar esto cuando este la tarjeta

			ARMAR_TRAMA_DE_DATOS_INGRESO ;//armo la trama de datos con sprintf
			if(enviar==0 && (strcmp(OLD_TRAMA_DATOS,DATOS_TARJETA_PIN))!=0)
			{
				EnviarString_0 (DATOS_TARJETA_PIN);// mando la trama por la uart0
				strcpy(OLD_TRAMA_DATOS,DATOS_TARJETA_PIN);
				enviar=1;
				flag_ingreso=0;
			}

			MensajesRX();
				if (ESTADO_RX_UART0=='B') //USUARIO INGRESADO Y VALIDADO
				{
					Display_lcd("CORRECTO        ",0,0);
					Display_lcd("                  ",1,0);
					reproducir_wav (WAV_CLAVE_CORRECTA);
					reproducir_wav (WAV_HASTA_LUEGO);
					bzero(codigo_tarjeta,13);
					codigo_personal=0;
					estado =DETECCION;
					flag_LCD = 1;
					ESTADO_RX_UART0='0';
					resultado_codigo_personal=BUSY;
					enviar=0;
					flag_ingreso=1;
					return;

				}
			if (ESTADO_RX_UART0=='M')
				{
				Display_lcd("INCORRECTO      ",0,0);
				Display_lcd("                  ",1,0);
				reproducir_wav (WAV_CLAVE_INCORRECTA);
					bzero(codigo_tarjeta,13);
					codigo_personal=0;
					estado =DETECCION;
					flag_LCD = 1;
					ESTADO_RX_UART0='0';
					resultado_codigo_personal=BUSY;
					flag_ingreso=1;
					enviar=0;
					return;

				}





		}
	 if (resultado_codigo_personal== TIEMPO_VENCIDO)
		{
			bzero(codigo_tarjeta,13);

			codigo_personal=0;
			if (flag_LCD3)
			{
				Display_lcd("TIEMPO VENCIDO     ",0,0);
				Display_lcd("                   ",1,0);
				flag_LCD3=0;
				soft_timer=100;
			}

			if(!soft_timer)
			{
				estado =DETECCION;
				flag_LCD3=1;
				flag_LCD=1;
				flag_ingreso=1;
				enviar=0;
			}


			return;
		}

	}
}

void estado_seteo (void)
{

	__RW static uint8_t nueva_tarjeta =0;
	__RW static uint8_t flag_LCD=1;
	__RW static uint8_t flag_LCD2=1;
	__RW static uint8_t estado =DETECCION;
	__RW static uint32_t codigo_personal = 0;
	__RW static char codigo_tarjeta [13];
	__RW uint8_t resultado_codigo_personal =BUSY;
	char DATOS_TARJETA_PIN[TAM_TARJETA+NUMERO_PIN+3];// TRAMA DE DATOS A ENVIAR EJEMPLO:"T000000000000-000000"
MODO_NUEVO_EMPLEADO_ON;
if(nueva_tarjeta==0)
{

	if (estado==DETECCION )
	{
		if (flag_LCD)
		{
		Display_lcd("INGRESE TARJETA ",0,0);
		Display_lcd("                ",1,0);
		flag_LCD=0;
		}
		if (get_RFID (codigo_tarjeta))
		{
			reproducir_wav(WAV_BIENVENIDO);
			reproducir_wav(WAV_INGRESE_CODIGO);
			estado= INGRESO_CODIGO;
			flag_LCD=1;
		}
	}
	if (estado==INGRESO_CODIGO )
	{
		if (flag_LCD)
		{
		Display_lcd("INGRESE CODIGO     ",0,0);
		flag_LCD=0;
		}
		resultado_codigo_personal= get_codigo_personal (&codigo_personal);

		if (resultado_codigo_personal==READY) //fue ingresado por el usuario
		{
			ARMAR_TRAMA_DE_DATOS_NUEVA_TARJETA;
			EnviarString_0 (DATOS_TARJETA_PIN);

			ESTADO_RX_UART0='0';
			MODO_NUEVO_EMPLEADO_OFF;

			reproducir_wav (WAV_HASTA_LUEGO);
			bzero(codigo_tarjeta,13);
			codigo_personal=0;
			estado =DETECCION;
			ESTADO_TARJETA_NUEVA_INGRESADA=1;
			Display_lcd("GRACIAS POR          ",0,0);
			Display_lcd("REGISTRARSE          ",1,0);
			flag_LCD=1;
			return;
		}
		if (resultado_codigo_personal== TIEMPO_VENCIDO)
		{

			if (flag_LCD2)
			{
				Display_lcd("TIEMPO VENCIDO     ",0,0);
				flag_LCD2=0;
				soft_timer=100;
			}

			bzero(codigo_tarjeta,13);
			codigo_personal=0;

			if(!soft_timer)
			{
			estado =DETECCION;
			flag_LCD2=1;
			flag_LCD=1;
			}
			return;
		}

	}

}
}
