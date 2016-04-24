//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//
#include "../../cicanura/core/include/collection.h"
#include "../../cicanura/core/include/strings.h"

//
#include "../include/cprocessor.h"

//
struct collection *co_collection;

// Signály pro C Processor..
int cprocessor_signal_exit;

//
#define COMMAND_EXIT_NAZEV "exit"
#define COMMAND_EXIT_KATEGORIE "cprocessor"
struct cprocessor_command *cprocessor_command_exit;

//
#define COMMAND_SHOW_COMMANDS_NAZEV "show_commands"
#define COMMAND_SHOW_COMMANDS_KATEGORIE "cprocessor"
struct cprocessor_command *cprocessor_command_show_commands;

///
int cprocessor_open()
{
	//
	co_collection = collection_new();

	//
	cprocessor_signal_exit = 0;

	// Přidání příkazu pro exit..
	cprocessor_command_exit = cprocessor_command_new(COMMAND_EXIT_NAZEV, COMMAND_EXIT_KATEGORIE, &cprocessor_command_exit_function);
	cprocessor_command_show_commands = cprocessor_command_new(COMMAND_SHOW_COMMANDS_NAZEV, COMMAND_SHOW_COMMANDS_KATEGORIE, &cprocessor_command_show_commands_function);

	//
	collection_add(co_collection, cprocessor_command_exit);
	collection_add(co_collection, cprocessor_command_show_commands);

	//
	return 0;
}

///
struct cprocessor_command *cprocessor_command_new(char *nazev, char *kategorie, int (*function)())
{
	//
	struct cprocessor_command *command_ptr;

	//
	command_ptr = (struct cprocessor_command *) malloc(sizeof(struct cprocessor_command));

	//
	if(command_ptr)
	{
		command_ptr -> nazev = strings_new(nazev);
		command_ptr -> kategorie = strings_new(kategorie);
		command_ptr -> function = function;
	}

	//
	return command_ptr;
}

///
void cprocessor_command_delete(void *command_ptr)
{
	//
	struct cprocessor_command *ptr = (struct cprocessor_command *) command_ptr;

	//
	if(ptr)
	{
		//
		free(ptr -> nazev);
		free(ptr -> kategorie);

		//
		free(ptr);
	}
}

///
int cprocessor_close()
{
	//
	if(co_collection)
	{
		// Smazání samotných objektů v kolekci (co_collection)..
		collection_object_delete(co_collection, &cprocessor_command_delete);

		//
		collection_delete(co_collection);

		//
		co_collection = NULL;
	}

	//
	return 0;
}

///
int cprocessor_command_register(struct cprocessor_command *command_ptr)
{
	//
	collection_add(co_collection, command_ptr);

	//
	return 0;
}

///
int cprocessor_command_exit_function()
{
	//
	cprocessor_signal_exit = 1;

	//
	return 0;
}

///
int cprocessor_command_show_commands_function()
{
	///
	int function(void *object_ptr)
	{
		//
		struct cprocessor_command *command_ptr = (struct cprocessor_command *) object_ptr;

		//
		if(command_ptr)
		{
			printf("%s\n", command_ptr -> nazev);
		}
	}

	//
	collection_foreach(co_collection, &function);
}

///
int cprocessor_run()
{
	//
	char *input;

	//
	input = malloc(sizeof(char) * MAX_OF_COMMAND_INPUT_CHARS);

	///
	int function(void *object_ptr)
	{
		//
		struct cprocessor_command *command_ptr = (struct cprocessor_command *) object_ptr;

		//
		if(command_ptr)
		{
			if(strcmp(command_ptr -> nazev, input) == 0)
			{
				command_ptr -> function();
			}
		}
	}

	//
	while(!cprocessor_signal_exit)
	{
		//
		printf("cprocessor> ");
		scanf("%s", input);

		//
		collection_foreach(co_collection, &function);
	}

	//
	free(input);
}
