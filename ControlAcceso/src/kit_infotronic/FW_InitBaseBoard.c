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
}
