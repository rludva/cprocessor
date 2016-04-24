#ifndef __CPROCESSOR_H__
#define __CPROCESSOR_H__

//
#define MAX_OF_COMMAND_INPUT_CHARS 1024

//
struct cprocessor_command
{
	char *nazev;
	char *kategorie;
	int (*function)();
};

//
int cprocessor_open();
int cprocessor_close();

//
struct cprocessor_command *cprocessor_command_new(char *nazev, char *kategorie, int (*function)());
void cprocessor_command_delete(void *command_ptr);

//
int cprocessor_run();

//
int cprocessor_command_register(struct cprocessor_command *command_ptr);

//
int cprocessor_command_exit_function();
int cprocessor_command_show_commands_function();

#endif
