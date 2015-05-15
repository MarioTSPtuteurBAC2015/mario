#include <sdl/sdl.h>

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

typedef struct
{
	char key[SDLK_LAST];
	int mousex,mousey;
	int mousexrel,mouseyrel;
	char mousebuttons[8];
	char quit;
} Input;

void UpdateEvents(Input* in);
void InitEvents(Input* in);

#ifdef __cplusplus
}
#endif // __cplusplus
