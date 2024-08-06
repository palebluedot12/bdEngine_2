#include "SquaresDream.h"

int wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	SquaresDream app;
	if (app.Initialize(hInstance, nCmdShow) == FALSE)
		return FALSE;

	MSG msg{};

	app.Loop(msg);

	app.Uninitialize();

	return (int)msg.wParam;
}
