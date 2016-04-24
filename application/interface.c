//
#include <stdio.h>

//
#include "../core/include/cprocessor.h"

//
struct cprocessor_command *command_version;

///
int command_version_function()
{
	//
	printf("Verze __VERSION__\n");

	//
	return 0;
}

///
int init()
{
	//
	cprocessor_open();

	//
	command_version = cprocessor_command_new("version", "interface", &command_version_function);

	//
	cprocessor_command_register(command_version);
	
	//
	puts("Simple C Processor interface..");

	//
	return 0;
}

///
int main()
{
	//
	init();

	//
	cprocessor_run();

	//
	cprocessor_close();

	//
	return 0;
}
