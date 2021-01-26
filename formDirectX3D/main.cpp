#include "iostream"
#include "windows.h"
#include "windowsx.h"
#include "DX9Form.h"
#include "d3d9.h"
#include "d3dx9.h"

using namespace formDirectX3D;

[STAThread]

void Main(array<String^>^ args)

{

    Application::EnableVisualStyles();

    Application::SetCompatibleTextRenderingDefault(false);

    formDirectX3D::DX9Form form;

    Application::Run(% form);

}