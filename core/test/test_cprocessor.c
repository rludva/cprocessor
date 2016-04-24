//
#include <stdlib.h>

//
#include "../../cicanura/core/include/ctest.h"
#include "../../cicanura/core/include/strings.h"

//
#include "../include/cprocessor.h"

///
int test_cprocessor_pass()
{
	ctest_assert_pass("Nultý pass-assert pro detekci spuštěného testu.");
}

/// The open/close pass test..
int test_cprocessor_01()
{
	// Otevření datových struktur procesoru..
	int open_result = cprocessor_open();

	//
	{
		char *assert_message = "Otevření příkazového procesoru proběhlo v pořádku..";
		int assert_result = open_result;
		ctest_assert_zero(assert_result, assert_message);
	}

	// Zavření datových struktur procesoru..
	int close_result = cprocessor_close();

	//
	{
		char *assert_message = "Zavření příkazového procesoru proběhlo v pořádku..";
		int assert_result = close_result;
		ctest_assert_zero(assert_result, assert_message);
	}

	//
	ctest_assert_pass("The C Processor open/close pass test..");
}

///
int test_cprocessor_command_delete()
{
	/// Prázdná funkce (empty function)..
	int command_function()
	{
		return 0;
	}

	//
	struct cprocessor_command *command_ptr;

	//
	command_ptr = (struct cprocessor_command *) malloc(sizeof(struct cprocessor_command));

	//
	command_ptr -> nazev = strings_new("Nějaký název");
	command_ptr -> kategorie = strings_new("(bez kategorie)");
	command_ptr -> function = &command_function;

	//
	cprocessor_command_delete(command_ptr);

	// Pokus o opětovné mazání by měl být irelevantní..
	command_ptr = NULL;
	cprocessor_command_delete(command_ptr);

	//
	{
		char *assert_message = "Kontrola smazaného objektu cprocessor_command..";
		void *assert_result = (void *) command_ptr;
		ctest_assert_null(assert_result, assert_message);
	}
}

///
int test_cprocessor_command_new()
{
	///
	int my_function()
	{
		return 0;
	}

	//
	struct cprocessor_command *command_ptr = NULL;

	//
	char *command_nazev = "(název)";
	char *command_kategorie = "(kategorie)";
	int (*function)() = &my_function;

	//
	command_ptr = cprocessor_command_new(command_nazev, command_kategorie, function);
	
	//
	{
		char *assert_message = "Kontrola objektu cprocessor_command na správnost pro název..";
		int assert_result = (strcmp(command_ptr -> nazev, command_nazev) == 0) ? TRUE : FALSE;
		ctest_assert_true(assert_result, assert_message);
	}

	//
	{
		char *assert_message = "Kontrola objektu cprocessor_command na správnost pro položku kategorie..";
		int assert_result = (strcmp(command_ptr -> kategorie, command_kategorie) == 0) ? TRUE : FALSE;
		ctest_assert_true(assert_result, assert_message);
	}

	//
	{
		char *assert_message = "Kontrola objektu cprocessor_command na správnost ukazelete na funkci..";
		int assert_result = (command_ptr -> function == function) ? TRUE : FALSE;
		ctest_assert_true(assert_result, assert_message);
	}

	//
	cprocessor_command_delete(command_ptr);
	
	//
	return 0;
}

///
void ctest_test_cprocessor_register()
{
	ctest_test_functions_add("Přidán nultý test pro cprocessor", "cprocessor", &test_cprocessor_pass);
	ctest_test_functions_add("The open/close pass test..", "cprocessor", &test_cprocessor_01);
	ctest_test_functions_add("Odzkoušení funkce pro smazání objektu cprocessor_command", "cprocessor", &test_cprocessor_command_delete);
	ctest_test_functions_add("Odzkoušení funkce pro vytvoření objektu cprocessor_command", "cprocessor", &test_cprocessor_command_new);
}
