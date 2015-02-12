#include <QtWidgets/QApplication>
#include "main_form.h"
#include <Windows.h>

int main(int argc, char *argv[])
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
	printf("Debugging Window:\n");

	QApplication a(argc, argv);
	main_form mainForm;
	mainForm.show();
	return a.exec();
}
