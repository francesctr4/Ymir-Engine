#include <stdlib.h>
#include "Application.h"
#include "Globals.h"
#include "ModuleInput.h"

#include "External/SDL/include/SDL.h"
#pragma comment( lib, "Source/External/SDL/libx86/SDL2.lib" )
#pragma comment( lib, "Source/External/SDL/libx86/SDL2main.lib" )

#include "External/Optick/include/optick.h"
#ifdef _DEBUG
#pragma comment( lib, "Source/External/Optick/lib/debugLib/OptickCore.lib" )
#else
#pragma comment (lib, "Source/External/Optick/lib/releaseLib/OptickCore.lib") 
#endif // _DEBUG

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

int main(int argc, char ** argv)
{
	LOG("Starting engine '%s'....", TITLE);

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	Application* App = NULL;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			LOG("-------------- Application Creation --------------");
			App = new Application();
			state = MAIN_START;
			break;

		case MAIN_START:

			LOG("-------------- Application Init --------------");
			if (App->Init() == false)
			{
				LOG("Application Init exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("-------------- Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			OPTICK_FRAME("Main Loop");

			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with ERROR");
				state = MAIN_EXIT;
			}
			else if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;

			// Easy solution to close the program

			if (App->input->quit == true || App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_UP) {

				return MAIN_FINISH;

			}

			break;

		}

		case MAIN_FINISH:

			LOG("-------------- Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG("Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
	}

	delete App;
	LOG("Exiting engine '%s'...\n", TITLE);
	return main_return;
}