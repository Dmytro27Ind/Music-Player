/*
Copyright © 2020 Dmytro Kagirov, dmytro27kagirov@gmail.com

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http ://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissionsand
limitations under the License.
*/

#pragma once

#include <Windows.h>

namespace MusicPlayer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class CreatePlaylistForm : public System::Windows::Forms::Form
	{
	public:
		CreatePlaylistForm(void)
		{
			InitializeComponent();
		}

	protected:
		~CreatePlaylistForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ buttonSave;
	private: System::Windows::Forms::TextBox^ textBoxName;
	private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ buttonAddTrack;
	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(CreatePlaylistForm::typeid));
			this->buttonSave = (gcnew System::Windows::Forms::Button());
			this->textBoxName = (gcnew System::Windows::Forms::TextBox());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->buttonAddTrack = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// buttonSave
			// 
			this->buttonSave->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->buttonSave->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonSave.BackgroundImage")));
			this->buttonSave->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->buttonSave->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->buttonSave->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonSave->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->buttonSave->Location = System::Drawing::Point(265, 241);
			this->buttonSave->Name = L"buttonSave";
			this->buttonSave->Size = System::Drawing::Size(125, 60);
			this->buttonSave->TabIndex = 0;
			this->buttonSave->Text = L"Save";
			this->buttonSave->UseVisualStyleBackColor = false;
			this->buttonSave->Click += gcnew System::EventHandler(this, &CreatePlaylistForm::buttonSave_Click);
			// 
			// textBoxName
			// 
			this->textBoxName->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->textBoxName->Font = (gcnew System::Drawing::Font(L"Times New Roman", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBoxName->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->textBoxName->Location = System::Drawing::Point(40, 60);
			this->textBoxName->Name = L"textBoxName";
			this->textBoxName->Size = System::Drawing::Size(370, 45);
			this->textBoxName->TabIndex = 1;
			// 
			// listView1
			// 
			this->listView1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->listView1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"listView1.BackgroundImage")));
			this->listView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->listView1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->listView1->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->listView1->HideSelection = false;
			this->listView1->Location = System::Drawing::Point(40, 120);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(370, 100);
			this->listView1->TabIndex = 2;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::List;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label1->Location = System::Drawing::Point(40, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(169, 33);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Write a name:";
			// 
			// buttonAddTrack
			// 
			this->buttonAddTrack->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->buttonAddTrack->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonAddTrack.BackgroundImage")));
			this->buttonAddTrack->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->buttonAddTrack->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonAddTrack->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->buttonAddTrack->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonAddTrack->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->buttonAddTrack->Location = System::Drawing::Point(60, 241);
			this->buttonAddTrack->Name = L"buttonAddTrack";
			this->buttonAddTrack->Size = System::Drawing::Size(125, 60);
			this->buttonAddTrack->TabIndex = 4;
			this->buttonAddTrack->Text = L"Add Track";
			this->buttonAddTrack->UseVisualStyleBackColor = false;
			this->buttonAddTrack->Click += gcnew System::EventHandler(this, &CreatePlaylistForm::buttonAddTrack_Click);
			// 
			// CreatePlaylistForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(450, 325);
			this->Controls->Add(this->buttonAddTrack);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->textBoxName);
			this->Controls->Add(this->buttonSave);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"CreatePlaylistForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Create Playlist";
			this->TransparencyKey = System::Drawing::Color::DimGray;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void buttonSave_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void buttonAddTrack_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
