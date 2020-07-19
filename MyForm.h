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

#include "PlayerMusic.h"
#include <string> 
#include <sstream>


namespace MusicPlayer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace playermusic;

	static void Rendering();
	static void EventsHendling();
	static void SetRenderAndEvnets();
	static UINT_PTR timerRend;
	static UINT_PTR timerEvent;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	private: static const int FormWidth = 950;
	private: System::Windows::Forms::CheckBox^ checkBoxRepeatTrack;
	private: System::Windows::Forms::CheckBox^ checkBoxRepeatPlaylist;
	private: System::Windows::Forms::CheckBox^ checkBoxRandomList;
	private: static const int FormHeight = 670;

	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	public: static System::Windows::Forms::Button^ buttonPlay;
	public: static System::Windows::Forms::Label^ labelTrackName;
	public: static System::Windows::Forms::Label^ labelTrackLength;
	public: static System::Windows::Forms::Label^ labelCurrTime;

	private: System::Windows::Forms::Button^ buttonNext;
	private: System::Windows::Forms::Button^ buttonOpenPlaylist;
	private: System::Windows::Forms::Button^ buttonAddTrack;
	private: System::Windows::Forms::Button^ buttonCreatePlaylist;
	private: System::Windows::Forms::Button^ buttonPrev;
	private: System::Windows::Forms::Label^ label5;

		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->buttonPlay = (gcnew System::Windows::Forms::Button());
			this->buttonNext = (gcnew System::Windows::Forms::Button());
			this->labelTrackName = (gcnew System::Windows::Forms::Label());
			this->buttonAddTrack = (gcnew System::Windows::Forms::Button());
			this->buttonPrev = (gcnew System::Windows::Forms::Button());
			this->buttonOpenPlaylist = (gcnew System::Windows::Forms::Button());
			this->buttonCreatePlaylist = (gcnew System::Windows::Forms::Button());
			this->labelTrackLength = (gcnew System::Windows::Forms::Label());
			this->labelCurrTime = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->checkBoxRepeatTrack = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxRepeatPlaylist = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxRandomList = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();

			this->buttonPlay->BackColor = System::Drawing::SystemColors::ControlDark;
			this->buttonPlay->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonPlay.BackgroundImage")));
			this->buttonPlay->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->buttonPlay->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonPlay->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->buttonPlay->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonPlay->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->buttonPlay->ImageKey = L"(none)";
			this->buttonPlay->Location = System::Drawing::Point(413, 95);
			this->buttonPlay->Name = L"buttonPlay";
			this->buttonPlay->Size = System::Drawing::Size(125, 125);
			this->buttonPlay->TabIndex = 0;
			this->buttonPlay->Text = L"Play";
			this->buttonPlay->UseVisualStyleBackColor = false;
			this->buttonPlay->Click += gcnew System::EventHandler(this, &MyForm::buttonPlay_Click);

			this->buttonNext->BackColor = System::Drawing::SystemColors::ControlDark;
			this->buttonNext->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonNext.BackgroundImage")));
			this->buttonNext->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->buttonNext->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonNext->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->buttonNext->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonNext->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->buttonNext->ImageKey = L"(none)";
			this->buttonNext->Location = System::Drawing::Point(638, 160);
			this->buttonNext->Name = L"buttonNext";
			this->buttonNext->Size = System::Drawing::Size(150, 60);
			this->buttonNext->TabIndex = 2;
			this->buttonNext->Text = L"next";
			this->buttonNext->UseVisualStyleBackColor = false;
			this->buttonNext->Click += gcnew System::EventHandler(this, &MyForm::buttonNext_Click);

			this->labelTrackName->AutoSize = true;
			this->labelTrackName->BackColor = System::Drawing::Color::Transparent;
			this->labelTrackName->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelTrackName->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->labelTrackName->Location = System::Drawing::Point(365, 350);
			this->labelTrackName->Name = L"labelTrackName";
			this->labelTrackName->Size = System::Drawing::Size(220, 46);
			this->labelTrackName->TabIndex = 4;
			this->labelTrackName->Text = L"__________";

			this->buttonAddTrack->BackColor = System::Drawing::SystemColors::ControlDark;
			this->buttonAddTrack->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonAddTrack.BackgroundImage")));
			this->buttonAddTrack->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->buttonAddTrack->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonAddTrack->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->buttonAddTrack->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonAddTrack->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->buttonAddTrack->ImageKey = L"(none)";
			this->buttonAddTrack->Location = System::Drawing::Point(645, 450);
			this->buttonAddTrack->Name = L"buttonAddTrack";
			this->buttonAddTrack->Size = System::Drawing::Size(175, 75);
			this->buttonAddTrack->TabIndex = 5;
			this->buttonAddTrack->Text = L"Add track";
			this->buttonAddTrack->UseVisualStyleBackColor = false;
			this->buttonAddTrack->Click += gcnew System::EventHandler(this, &MyForm::buttonAddTrack_Click);

			this->buttonPrev->BackColor = System::Drawing::SystemColors::ControlDark;
			this->buttonPrev->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonPrev.BackgroundImage")));
			this->buttonPrev->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->buttonPrev->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonPrev->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->buttonPrev->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonPrev->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->buttonPrev->ImageKey = L"(none)";
			this->buttonPrev->Location = System::Drawing::Point(162, 160);
			this->buttonPrev->Name = L"buttonPrev";
			this->buttonPrev->Size = System::Drawing::Size(150, 60);
			this->buttonPrev->TabIndex = 8;
			this->buttonPrev->Text = L"prev";
			this->buttonPrev->UseVisualStyleBackColor = false;
			this->buttonPrev->Click += gcnew System::EventHandler(this, &MyForm::buttonPrev_Click);

			this->buttonOpenPlaylist->BackColor = System::Drawing::SystemColors::ControlDark;
			this->buttonOpenPlaylist->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonOpenPlaylist.BackgroundImage")));
			this->buttonOpenPlaylist->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->buttonOpenPlaylist->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonOpenPlaylist->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->buttonOpenPlaylist->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonOpenPlaylist->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->buttonOpenPlaylist->ImageKey = L"(none)";
			this->buttonOpenPlaylist->Location = System::Drawing::Point(388, 450);
			this->buttonOpenPlaylist->Name = L"buttonOpenPlaylist";
			this->buttonOpenPlaylist->Size = System::Drawing::Size(175, 75);
			this->buttonOpenPlaylist->TabIndex = 9;
			this->buttonOpenPlaylist->Text = L"Open playlist";
			this->buttonOpenPlaylist->UseVisualStyleBackColor = false;
			this->buttonOpenPlaylist->Click += gcnew System::EventHandler(this, &MyForm::buttonOpenPlaylist_Click);

			this->buttonCreatePlaylist->BackColor = System::Drawing::SystemColors::ControlDark;
			this->buttonCreatePlaylist->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonCreatePlaylist.BackgroundImage")));
			this->buttonCreatePlaylist->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->buttonCreatePlaylist->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonCreatePlaylist->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->buttonCreatePlaylist->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonCreatePlaylist->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->buttonCreatePlaylist->ImageKey = L"(none)";
			this->buttonCreatePlaylist->Location = System::Drawing::Point(130, 450);
			this->buttonCreatePlaylist->Name = L"buttonCreatePlaylist";
			this->buttonCreatePlaylist->Size = System::Drawing::Size(175, 75);
			this->buttonCreatePlaylist->TabIndex = 10;
			this->buttonCreatePlaylist->Text = L"Create playlist";
			this->buttonCreatePlaylist->UseVisualStyleBackColor = false;
			this->buttonCreatePlaylist->Click += gcnew System::EventHandler(this, &MyForm::buttonCreatePlaylist_Click);

			this->labelTrackLength->AutoSize = true;
			this->labelTrackLength->BackColor = System::Drawing::Color::Transparent;
			this->labelTrackLength->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelTrackLength->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->labelTrackLength->Location = System::Drawing::Point(549, 280);
			this->labelTrackLength->Name = L"labelTrackLength";
			this->labelTrackLength->Size = System::Drawing::Size(111, 46);
			this->labelTrackLength->TabIndex = 11;
			this->labelTrackLength->Text = L" 0 : 0 ";

			this->labelCurrTime->AutoSize = true;
			this->labelCurrTime->BackColor = System::Drawing::Color::Transparent;
			this->labelCurrTime->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelCurrTime->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->labelCurrTime->Location = System::Drawing::Point(288, 280);
			this->labelCurrTime->Name = L"labelCurrTime";
			this->labelCurrTime->Size = System::Drawing::Size(111, 46);
			this->labelCurrTime->TabIndex = 12;
			this->labelCurrTime->Text = L" 0 : 0 ";

			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label5->Location = System::Drawing::Point(458, 280);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(31, 46);
			this->label5->TabIndex = 13;
			this->label5->Text = L"/";

			this->checkBoxRepeatTrack->AutoSize = true;
			this->checkBoxRepeatTrack->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxRepeatTrack->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->checkBoxRepeatTrack->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->checkBoxRepeatTrack->Location = System::Drawing::Point(765, 245);
			this->checkBoxRepeatTrack->Name = L"checkBoxRepeatTrack";
			this->checkBoxRepeatTrack->Size = System::Drawing::Size(163, 31);
			this->checkBoxRepeatTrack->TabIndex = 14;
			this->checkBoxRepeatTrack->Text = L"Repeat Track";
			this->checkBoxRepeatTrack->UseVisualStyleBackColor = false;
			this->checkBoxRepeatTrack->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxRepeatTrack_CheckedChanged);
			this->checkBoxRepeatPlaylist->AutoSize = true;
			this->checkBoxRepeatPlaylist->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxRepeatPlaylist->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->checkBoxRepeatPlaylist->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->checkBoxRepeatPlaylist->Location = System::Drawing::Point(765, 320);
			this->checkBoxRepeatPlaylist->Name = L"checkBoxRepeatPlaylist";
			this->checkBoxRepeatPlaylist->Size = System::Drawing::Size(179, 31);
			this->checkBoxRepeatPlaylist->TabIndex = 15;
			this->checkBoxRepeatPlaylist->Text = L"Repeat Playlist";
			this->checkBoxRepeatPlaylist->UseVisualStyleBackColor = true;
			this->checkBoxRepeatPlaylist->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxRepeatPlaylist_CheckedChanged);

			this->checkBoxRandomList->AutoSize = true;
			this->checkBoxRandomList->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxRandomList->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->checkBoxRandomList->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->checkBoxRandomList->Location = System::Drawing::Point(765, 395);
			this->checkBoxRandomList->Name = L"checkBoxRandomList";
			this->checkBoxRandomList->Size = System::Drawing::Size(158, 31);
			this->checkBoxRandomList->TabIndex = 16;
			this->checkBoxRandomList->Text = L"Random List";
			this->checkBoxRandomList->UseVisualStyleBackColor = true;
			this->checkBoxRandomList->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxRandomList_CheckedChanged);

			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::Color::Indigo;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(950, 670);

			this->Controls->Add(this->checkBoxRepeatTrack);
			this->Controls->Add(this->checkBoxRepeatPlaylist);
			this->Controls->Add(this->checkBoxRandomList);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->labelCurrTime);
			this->Controls->Add(this->labelTrackLength);
			this->Controls->Add(this->buttonCreatePlaylist);
			this->Controls->Add(this->buttonOpenPlaylist);
			this->Controls->Add(this->buttonPrev);
			this->Controls->Add(this->buttonAddTrack);
			this->Controls->Add(this->labelTrackName);
			this->Controls->Add(this->buttonNext);
			this->Controls->Add(this->buttonPlay);

			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Opacity = 0.95;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Ind Music Player ";
			this->TransparencyKey = System::Drawing::Color::DimGray;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		System::Void buttonCreatePlaylist_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonPlay_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonOpenPlaylist_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonAddTrack_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonPrev_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonNext_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void checkBoxRepeatTrack_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void checkBoxRepeatPlaylist_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void checkBoxRandomList_CheckedChanged(System::Object^ sender, System::EventArgs^ e);

	public:
		/* This method set the name of track (mp3 file) in Label.
		 * Returns nothing (void).
		 */
		static void AlignCenter(System::Windows::Forms::Label^ label);
	};
}
