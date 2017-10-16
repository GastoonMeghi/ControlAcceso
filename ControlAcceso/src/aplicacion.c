
#include "aplicacion.h"

extern __RW uint32_t buffer_rfid;

extern __RW uint16_t timer_codigo_personal;

extern __RW datos_pc_t datos_pc;

extern __RW colaborador_t colaborador;

extern __RW uint8_t flag_ingreso_codigo;

extern __RW uint8_t buff_key;




__RW uint8_t codigo_personal_listo;


void Inicializar ( void )
{
	InicPLL ();
	inic_GPIO ();
	InitGPIOs_Exp3 ();
	inic_systick ();
	rtc_initialize ();
	inic_datos ();
	inic_timer1();

	// la inicializacion del wav, del dac y del timer debe estar en ese orden!
	inic_dac ();
	inic_wav();
	inic_timer0 ();
	/////******

	Inic_UART1();
//	Inic_LCD();
}

void aplicacion (void)
{
	__RW uint8_t estado=NORMAL;

	while (1)
	{


		if (estado==NORMAL)
		{
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

	if (estado==DETECCION && HAY_TARJETA)
	{
		reproducir_wav(WAV_BIENVENIDO);
	    reproducir_wav(WAV_INGRESE_CODIGO);
		//PEDIR_CODIGO_PERSONAL_PC; //flag para pedir los datos de la pc

		flag_ingreso_codigo=1;	//habilito a que se pueda ingresar el codigo
		ACTIVAR_TEMPORIZADOR_DE_INGRESO; //activa un timer que fija el tiempo maximo para ingresar y aceptar el codigo
		colaborador.codigo_personal =0;
		codigo_personal_listo =0;

		estado= VALIDACION_CODIGO;
		//IGNORAR_LECTOR; //evita que se remplace el valor de tarjeta leido
	}



	if (estado==VALIDACION_CODIGO)
	{
		if (codigo_personal_listo) //fue ingresado por el usuario
		{
			flag_ingreso_codigo=0;

			if (CODIGO_PC_RECIBIDO)
			{
				if (CODIGO_CORRECTO)
				{
					//SEÑAL_BIENVENIDA_DESPEDIDA;
					//ENVIAR_DATOS_PC;
					//RESETEAR_DATOS; //resetea DETECCION_TARJETA,CODIGO_INGRESADO,CODIGO_CORRECTO
					flag_ingreso_codigo=0; //el codigo ya fue ingresado
					DESACTIVAR_TEMPORIZADOR_DE_INGRESO;
					estado =DETECCION;
					//ESCUCHAR_LECTOR //vuelve a habilitar el lector de rfid
				}
				else
				{
					//SEÑAL_CLAVE_INCORRECTA;
					colaborador.codigo_personal=0; //borro el codigo anterior
					ACTIVAR_TEMPORIZADOR_DE_INGRESO;
					flag_ingreso_codigo=1;
				}

				codigo_personal_listo =0;
			}
		}

		if (TEMPORIZADOR_DE_INGRESO_VENCIDO)
		{
			//RESETEAR_DATOS;
			colaborador.codigo_tarjeta=0;
			colaborador.codigo_personal=0;
			DESACTIVAR_TEMPORIZADOR_DE_INGRESO;
			estado=DETECCION;
		}


	}
}

void estado_seteo (void)
{
	__RW static uint8_t estado =DETECCION;

	if (estado==DETECCION &&HAY_TARJETA)
	{
		//IGNORAR_LECTOR
		//SEÑAL_INGRESO_CODIGO; //señal que indica al colaborador que debe ingresar el codigo
		//PEDIR_CODIGO_PERSONAL_PC; //flag para pedir los datos de la pc

		flag_ingreso_codigo=1;	//habilito a que se pueda ingresar el codigo
		ACTIVAR_TEMPORIZADOR_DE_INGRESO; //activa un timer que fija el tiempo maximo para ingresar y aceptar el codigo
		colaborador.codigo_personal =0;
		codigo_personal_listo =0;
		estado=INGRESO_CODIGO;
	}
	if (estado==INGRESO_CODIGO && codigo_personal_listo)
	{
		datos_pc.codigo_tarjeta=colaborador.codigo_tarjeta;
		datos_pc.codigo_personal=colaborador.codigo_personal;
		//ENVIAR_DATOS_PC
		estado= DETECCION;

	}

}


void inic_datos (void)
{
	datos_pc.codigo_personal=0;
	colaborador.codigo_personal=0;
	colaborador.codigo_tarjeta=0;
}


void ejemplo_uart1 () {
	static uint8_t aux[13];
	//Display_lcd("INGRESE TARJETA",0,0);
	//Display_lcd("               ",1,0);
	if (get_RFID(aux)) {
		//WComando8(LCD_CLEAR);
		if (!(strcmp((char *)aux, "540022C7AE1F"))) {
			set_pin(RGBR, 0);
		}
		else if (!(strcmp((char *)aux, "540021EABB24"))) {
			set_pin(RGBR, 1);
		}
		//Display_lcd((char *) aux,1,1);
	}
}
