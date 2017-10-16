#include <aplicacion.h>



void inic_GPIO (void)
{
	// Apagar LED RGB de la placa
	set_pinsel(RGBB, PINSEL_GPIO);
	set_dir(RGBB, SALIDA);
	set_pin(RGBB, 0);
	set_pinsel(RGBR, PINSEL_GPIO);
	set_dir(RGBR, SALIDA);
	set_pin(RGBR, 0);
	set_pinsel(RGBG, PINSEL_GPIO);
	set_dir(RGBG, SALIDA);
	set_pin(RGBG, 0);
	// Apagar Reles
	set_pinsel(RELE1, PINSEL_GPIO);
	set_dir(RELE1, SALIDA);
	set_pin(RELE1, 1);
	set_pinsel(RELE2, PINSEL_GPIO);
	set_dir(RELE2, SALIDA);
	set_pin(RELE2, 1);
	set_pinsel(RELE3, PINSEL_GPIO);
	set_dir(RELE3, SALIDA);
	set_pin(RELE3, 1);
	set_pinsel(RELE4, PINSEL_GPIO);
	set_dir(RELE4, SALIDA);
	set_pin(RELE4, 1);
	// Apagar buzzer
	set_pinsel(BUZZ, PINSEL_GPIO);
	set_dir(BUZZ, SALIDA);
	set_pin(BUZZ, BUZZ_OFF);
	// Apagar leds stick
	set_pinsel(LED_ROJO, PINSEL_GPIO);
	set_dir(LED_ROJO, SALIDA);
	set_pin(LED_ROJO, 1);
	set_pinsel(LED_AZUL, PINSEL_GPIO);
	set_dir(LED_AZUL, SALIDA);
	set_pin(LED_AZUL, 1);
	set_pinsel(LED_VERDE, PINSEL_GPIO);
	set_dir(LED_VERDE, SALIDA);
	set_pin(LED_VERDE, 1);
}
