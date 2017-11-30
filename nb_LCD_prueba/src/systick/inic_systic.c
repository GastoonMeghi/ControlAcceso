#include <aplicacion.h>


//////////.......PROTOTIPOS EN: systick.h/////////


//-----------------------------------------------------------------------------
// Configuración del SysTick para 10ms
//-----------------------------------------------------------------------------
void inic_systick(void)
{
	STRELOAD = (uint16_t) (STCALIB/1) -1;
	STCURR=0;
	CLKSOURCE = 1;
	ENABLE =1;
	TICKINT = 1;
}
