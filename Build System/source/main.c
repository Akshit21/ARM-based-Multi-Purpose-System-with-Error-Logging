#include<stdint.h>
#ifdef FRDM
	#include "projectFRDM_1.h"
#else 
	#include "project_1.h"
#endif

int main()
{
	project_1_report();
	return 1;
}
