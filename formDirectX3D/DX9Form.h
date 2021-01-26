#pragma once

#using "System.dll"
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include <windowsx.h>
#include <Directxmath.h>


#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;
using namespace Microsoft::DirectX;
using namespace Microsoft::DirectX::Direct3D;

namespace formDirectX3D {

	public ref class DX9Form : public System::Windows::Forms::Form
	{
	public:
		DX9Form(void)
		{
			this->SetStyle(ControlStyles::AllPaintingInWmPaint | ControlStyles::Opaque, true);
			InitializeComponent();
			initializeGraphics();

		}







	protected:

		~DX9Form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel1;
	protected:
	private: System::ComponentModel::IContainer^ components;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(45, 51);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(578, 373);
			this->panel1->TabIndex = 0;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &DX9Form::panel1_Paint);
			// 
			// DX9Form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(675, 497);
			this->Controls->Add(this->panel1);
			this->Name = L"DX9Form";
			this->Text = L"DX9Form";
			this->ResumeLayout(false);

		}
#pragma endregion
	
	private: Device^ device;
	private: VertexBuffer^ vertexBuffer;
	private: array<CustomVertex::PositionColored>^ verts;
	private: float angle = 0.0f;
		
	private: void initializeGraphics() {
		PresentParameters^ pp = gcnew PresentParameters;
		pp->Windowed = true;
		pp->SwapEffect = SwapEffect::Discard;
		this->device = gcnew Device(0, DeviceType::Hardware, this->panel1, CreateFlags::HardwareVertexProcessing, pp);
		vertexBuffer = gcnew VertexBuffer(CustomVertex::PositionColored::typeid,3, device, Usage::Dynamic | Usage::WriteOnly,CustomVertex::PositionColored::Format,Pool::Default);
		//vertexBuffer->Created += gcnew EventHandler(this,&onVertexBufferCreate);
		onVertexBufferCreate(vertexBuffer,nullptr);
		vertexBuffer->SetData(verts, 0, LockFlags::None);
	}

	void onVertexBufferCreate(Object^ sender, EventArgs^ e) {
		VertexBuffer^ buffer = (VertexBuffer^ )sender;
		verts = gcnew array<CustomVertex::PositionColored>(3);
		verts[0].Position = Vector3(0, 1, 1);
		verts[0].Color = Color::Green.ToArgb();

		verts[1].Position = Vector3(-1, -1, 1);
		verts[1].Color = Color::Blue.ToArgb();

		verts[2].Position = Vector3(1, -1, 1);
		verts[2].Color = Color::Red.ToArgb();
		
		buffer->SetData(verts, 0, LockFlags::None);
	}

	private: void setUpCamera() {
		this->device->Transform->Projection = Matrix::PerspectiveFovLH((float)Math::PI / 4,panel1->Width/panel1->Height,1.0f,100.0f);
		device->Transform->View = Matrix::LookAtLH(Vector3(0,0,5), Vector3(), Vector3(0,1,0));
		
		device->Transform->World = Matrix::RotationY(angle);
		angle = angle + 0.05f;
		device->RenderState->Lighting = false;
		device->RenderState->CullMode = Cull::None;
	}

	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		if (this->device == nullptr) return;
		this->device->Clear(ClearFlags::Target, Color::CornflowerBlue, 1, 0);
		setUpCamera();
		device->BeginScene();
		device->VertexFormat = CustomVertex::PositionColored::Format;
		device->SetStreamSource(0, vertexBuffer, 0);
		device->DrawPrimitives(PrimitiveType::TriangleList, 0, 1);
		device->EndScene();
		device->Present();
		panel1->Invalidate();
	
	}
};
}
