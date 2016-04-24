# CProcessor, příkazový procesor

Přehled definic:
* MAX_OF_COMMAND_INPUT_CHARS

Přehled datových struktur:
* struct cprocessor_command;

Přehled funkcí:
* int cprocessor_open();
* int cprocessor_close();

* struct cprocessor_command *cprocessor_command_new(char *nazev, char *kategorie, int (*function)());
* void cprocessor_command_delete(void *command_ptr);

* int cprocessor_run();

* int cprocessor_command_exit_function();
* int cprocessor_command_show_commands_function();

## Přehled funkcí

### Funkce pro otevření a zavření příkazového procesoru
Pro inicializace všech datových struktur a nastavení proměnných na výchozí hodnoty je třeba příkazový procesor nejdříve otevřít pomocí volání cprocessor_open a po ukončení práce s příkazovým procesorem uvolnin alokovanou paměť všech objektů pomocí cprocessor_close.

* Funkce int cprocessor_open();
* Funkce int cprocessor_close();

### Funkce pro vytvoření nového příkazu

* Funkce  struct cprocessor_command *cprocessor_command_new(char *nazev, char *kategorie, int (*function)());
* Funkce  void cprocessor_command_delete(void *command_ptr);

### Funkce pro řízení běhu

* int cprocessor_run();

### Funkce pro zpracování příkazů
* int cprocessor_command_register(struct cprocessor_command *command_ptr);

* int cprocessor_command_exit_function();
* int cprocessor_command_show_commands_function();


## Interface
Pojem Interface je používán pro modul, který rozšiřuje příkazový procesor o další funkce.
Interface je nutné k příkazovému procesoru připojit v době kompilace.

Samotný interface obsahuje naplněné struktury cprocessor_command a funkce, které vykonávají jednotlivé příkazy.
Naplněné struktury cprocessor_command se poté přidají do kolekce příkazů procesoru voláním metody cprocessor_command_register.

### Jak napsat interface s vlastními příkazy
* Nejdříve je nutné includovat soubor cprocessor.h z projektu cicanura.
* Potom je třeba vytvořit proměnou do které se uloží command, tedy instanci třídy cprocessor_command, přesněji řečeno ukazatel na tento příkaz.
* Následně je třeba vytvořit prototyp funkce, která vrací int a nemá žedné parametry. Tato funkce vykonává samotný příkaz.
* Dále se vytvoří inicializační funkce, která otevře příkazový procesor, vytvoří se nový příkaz voláním cprocessor_command_new(příkaz, kategorie, ukazatel na výkonou funkci)
* Spustí se cprocessor_run(), které vyvolá shell příkazového procesoru a v okamžiku, kdy se dokončí hlavní výkonná část programu, tak je volán cprocessor_close, který zároveň uvolní paměť, která byla alokována pro strukturu příkazu.

* Co je to interface = vlastní rozhraní pro příkazový procesor postavený za účelem zpracování příkazů aplikace jako náhrada GUI či WEB_GUI.

