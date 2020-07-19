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

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#define _CRT_SECURE_NO_WARNINGS

#include "MyForm.h"
#include "CreatePlaylistForm.h"
#include "PlayerMusic.h"
#include <Windows.h>
#include <commdlg.h>
#include <cwchar>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <thread>

using namespace MusicPlayer;
using playermusic::PlayerMusic;
using std::vector;

OPENFILENAME ofile;
static bool playlistOpen = false;			// if playlist is open then playlistOpen will be equal to true
static bool endOfPlaylist = false;			// if playlist is finished then endOfPlaylist will be equal to true
static vector <PlayerMusic::Track*> list;	// The vector of pointers to the tracks in the original playlist sequence (for random play)
static BYTE combination = 0;				// default mode
UINT_PTR timerRend = 0;
UINT_PTR timerEvent = 0;


int main() {
	PlayerMusic::Init();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	MyForm form;
	Application::Run(% form);

	PlayerMusic::Delete(PlayerMusic::playlist);
	return 0;
}

void MyForm::AlignCenter(System::Windows::Forms::Label^ label) {
	int x = int(MyForm::FormWidth / 2.0 - label->Size.Width / 2.0);
	label->Location = System::Drawing::Point(x, label->Location.Y);
}

System::Void MyForm::buttonPlay_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!playlistOpen) {
		MessageBoxW(NULL, L"Playlist wasn't open.\nOpen it before play the tracks.", NULL, MB_OK);
		return;
	}
	if (PlayerMusic::playlist->GetCount() == 0) {
		MessageBoxW(NULL, L"Can't play the track, playlist is empty.", NULL, MB_OK);
		return;
	}

	bool condA = !PlayerMusic::StreamIsActive();
	bool condB = PlayerMusic::playlist->current->next == nullptr;
	bool condC = (PlayerMusic::playlist->GetMode() & PlayerMusic::LIST_REPEAT) != PlayerMusic::LIST_REPEAT;

	if (condA && condB && condC) {
		int answer = MessageBoxW(NULL, L"Playlist ended, do you want to listen again ?", L"End of playlist", MB_YESNO);

		if (answer == IDYES) {
			PlayerMusic::playlist->current = PlayerMusic::playlist->first;
		}
		else {
			PlayerMusic::Delete(PlayerMusic::playlist);
			exit(0);
		}
	}
	switch (PlayerMusic::IsPlaying()) {
		case true:		PlayerMusic::playlist->current->track->Pause();		break;
		case false:		PlayerMusic::playlist->current->track->Continue();	break;
	}
}

System::Void MyForm::buttonPrev_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!playlistOpen) {
		MessageBoxW(NULL, L"Playlist wasn't open.\nOpen it before play the track.", L"Error: Playlist does not exist", MB_OK);
		return;
	}
	if (PlayerMusic::playlist->GetCount() == 0) {
		MessageBoxW(NULL, L"Can't play the previous track, playlist is empty.", NULL, MB_OK);
		return;
	}
	PlayerMusic::playlist->Prev();
	PlayerMusic::playlist->current->track->Play();
}

System::Void MyForm::buttonNext_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!playlistOpen) {
		MessageBoxW(NULL, L"Playlist wasn't open.\nOpen it before play the track.", L"Error: Playlist does not exist", MB_OK);
		return;
	}
	if (PlayerMusic::playlist->GetCount() == 0) {
		MessageBoxW(NULL, L"Can't play the next track, playlist is empty.", NULL, MB_OK);
		return;
	}
	PlayerMusic::playlist->Next();
	PlayerMusic::playlist->current->track->Play();
}

static void MusicPlayer::Rendering() {
	switch (PlayerMusic::GetCurrTime() != nullptr) {
		case true:		MyForm::labelCurrTime->Text = gcnew System::String(PlayerMusic::GetCurrTime());		break;
		case false:		MyForm::labelCurrTime->Text = L" 0 : 0";											break;
	}
	switch (PlayerMusic::IsPlaying()) {
		case true:		MyForm::buttonPlay->Text = L"Pause";	break;
		case false:		MyForm::buttonPlay->Text = L"Play";		break;
	}
	MyForm::labelTrackLength->Text	= gcnew System::String( PlayerMusic::playlist->current->track->GetDurationStr() );
	MyForm::labelTrackName->Text	= gcnew System::String(PlayerMusic::playlist->current->track->GetName());

	MyForm::AlignCenter(MyForm::labelTrackName);
}

static void MusicPlayer::EventsHendling() {
	bool condA = !PlayerMusic::StreamIsActive();
	bool condB = PlayerMusic::playlist->current->next != nullptr;
	bool condC = (PlayerMusic::playlist->GetMode() & PlayerMusic::LIST_REPEAT) == PlayerMusic::LIST_REPEAT;
	bool condD = (PlayerMusic::playlist->GetMode() & PlayerMusic::REPEAT_TRACK) == PlayerMusic::REPEAT_TRACK;
	bool condE = (PlayerMusic::playlist->GetMode() & PlayerMusic::RANDOM_LIST) == PlayerMusic::RANDOM_LIST;

	if (condA && condD) {
		PlayerMusic::playlist->current->track->Play();
	}
	else if (condA && (condB || condC)) {
		PlayerMusic::playlist->Next();
		PlayerMusic::playlist->current->track->Play();
	}
}

static void MusicPlayer::SetRenderAndEvnets() {
	if (PlayerMusic::playlist->GetCount() != 0) {
		KillTimer(0, timerEvent);
		KillTimer(0, timerRend);
		PlayerMusic::playlist->current = PlayerMusic::playlist->first;
		PlayerMusic::playlist->current->track->Play();
		timerEvent = SetTimer(0, 0, 150, (TIMERPROC)EventsHendling);
		timerRend = SetTimer(0, 0, 150, (TIMERPROC)Rendering);
	}
}

void CreateForm() {
	CreatePlaylistForm^ createForm = gcnew CreatePlaylistForm();
	Application::Run(createForm);
}

System::Void MyForm::buttonCreatePlaylist_Click(System::Object^ sender, System::EventArgs^ e) {
	std::thread func_thread(CreateForm);
	if (func_thread.joinable())
		func_thread.join();
}

System::Void MyForm::buttonOpenPlaylist_Click(System::Object^ sender, System::EventArgs^ e) {
	if (playlistOpen) {
		MessageBoxW(NULL, L"Playlist is already open.", NULL, MB_OK);
		return;
	}
	wchar_t File[MAX_PATH_LENGTH];
	memset(File, 0, MAX_PATH_LENGTH);
	wchar_t FileTitle[MAX_PLAYLIST_NAME];
	memset(FileTitle, 0, MAX_PLAYLIST_NAME);
	wchar_t Filter[30] =
		L"Playlist file *.pll\0*.pll\0";

	ofile.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	ofile.lpstrTitle = L"Open the playlist";
	ofile.lStructSize = sizeof(OPENFILENAME);
	ofile.hwndOwner = NULL;
	ofile.lpstrFilter = Filter;
	ofile.nFilterIndex = 1;
	ofile.lpstrFile = File;
	ofile.nMaxFile = sizeof(File);
	ofile.lpstrFileTitle = FileTitle;
	ofile.nMaxFileTitle = sizeof(FileTitle);
	ofile.lpstrInitialDir = L"C:\\";

	bool open = GetOpenFileName(&ofile);

	if (open) {
		playlistOpen = true;
		std::ifstream fin;

		fin.open(ofile.lpstrFile, std::ios_base::in);
		if (!fin.is_open()) {
			MessageBoxW(NULL, L"Failed to open playlist.", NULL, MB_OK);
			return;
		}
		
		char name[MAX_PLAYLIST_NAME]{};
		fin.getline(name, MAX_PLAYLIST_NAME, '\0');
		wchar_t wname[MAX_PLAYLIST_NAME]{};

		char path[MAX_PATH_LENGTH]{};
		fin.getline(path, MAX_PATH_LENGTH, '\0');
		wchar_t wpath[MAX_PATH_LENGTH]{};

		PlayerMusic::playlist = PlayerMusic::Playlist::Create(name, path);

		fin.getline(path, MAX_PATH_LENGTH, '\0');
		while (fin.fail() == false) {
			PlayerMusic::playlist->AddTrack(PlayerMusic::Track::Create(path));
			fin.getline(path, MAX_PATH_LENGTH, '\0');
		}
		fin.close();

		SetRenderAndEvnets();
	}
}

System::Void MyForm::buttonAddTrack_Click(System::Object^ sender, System::EventArgs^ e) {
	if (playlistOpen) {
		wchar_t File[MAX_PATH_LENGTH];
		memset(File, 0, MAX_PATH_LENGTH);
		wchar_t FileTitle[MAX_PLAYLIST_NAME];
		memset(FileTitle, 0, MAX_PLAYLIST_NAME);
		wchar_t Filter[30] =
			L"Mp3 Files\0*.mp3\0";

		ofile.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
		ofile.lpstrTitle = L"Select files";
		ofile.lStructSize = sizeof(OPENFILENAME);
		ofile.hwndOwner = NULL;
		ofile.lpstrFilter = Filter;
		ofile.nFilterIndex = 1;
		ofile.lpstrFile = File;
		ofile.nMaxFile = sizeof(File);
		ofile.lpstrFileTitle = FileTitle;
		ofile.nMaxFileTitle = sizeof(FileTitle);
		ofile.lpstrInitialDir = L"C:\\";

		bool select = GetOpenFileName(&ofile);

		if (select) {
			char path[MAX_PATH_LENGTH]{};
			wcstombs(path, ofile.lpstrFile, wcslen(ofile.lpstrFile) + 1);
			PlayerMusic::playlist->AddTrack(PlayerMusic::Track::Create(path));

			std::ofstream fout;
			fout.open(PlayerMusic::playlist->GetPath(), std::ios_base::app);
			fout << PlayerMusic::playlist->current->track->GetPath() << '\0';
			fout.close();

			SetRenderAndEvnets();
		}
	}
	else
		MessageBoxW(NULL, L"Playlist wasn't open.\nOpen it before adding new tracks.", L"Error: Playlist does not exist", MB_OK);
}

System::Void MyForm::checkBoxRepeatTrack_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (!playlistOpen) {
		if (this->checkBoxRepeatTrack->Checked) {
			this->checkBoxRepeatTrack->Checked = false;
			MessageBoxW(NULL, L"Playlist wasn't open.\nOpen it before change mode.", NULL, MB_OK);
		}
		return;
	}
	static bool b = false;
	b = !b;
	if (b)	combination = combination |  PlayerMusic::PlayMode::REPEAT_TRACK;
	else	combination = combination & ~PlayerMusic::PlayMode::REPEAT_TRACK;

	PlayerMusic::playlist->ChangeMode(combination);
}

System::Void MyForm::checkBoxRepeatPlaylist_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (!playlistOpen) {
		if (this->checkBoxRepeatPlaylist->Checked) {
			this->checkBoxRepeatPlaylist->Checked = false;
			MessageBoxW(NULL, L"Playlist wasn't open.\nOpen it before change mode.", NULL, MB_OK);
		}
		return;
	}
	static bool b = false;
	b = !b;
	if (b)	combination = combination |  PlayerMusic::PlayMode::LIST_REPEAT;
	else	combination = combination & ~PlayerMusic::PlayMode::LIST_REPEAT;

	PlayerMusic::playlist->ChangeMode(combination);
}

System::Void MyForm::checkBoxRandomList_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (!playlistOpen) {
		if (this->checkBoxRandomList->Checked) {
			this->checkBoxRandomList->Checked = false;
			MessageBoxW(NULL, L"Playlist wasn't open.\nOpen it before change mode.", NULL, MB_OK);
		}
		return;
	}

	static bool b = false;
	b = !b;
	if (b)	combination = combination | PlayerMusic::PlayMode::RANDOM_LIST;
	else	combination = combination & ~PlayerMusic::PlayMode::RANDOM_LIST;

	PlayerMusic::playlist->ChangeMode(combination);

	if (b) {
		list.clear();
		list.shrink_to_fit();

		for(PlayerMusic::List *ptr = PlayerMusic::playlist->first; ptr != nullptr; ptr = ptr->next)
			list.push_back(ptr->track);
		PlayerMusic::playlist->RandomList();
	}
	else {
		int i = 0;
		for (PlayerMusic::List* ptr = PlayerMusic::playlist->first; ptr != nullptr; ptr = ptr->next)
			ptr->track = list[i++];
	}
	PlayerMusic::playlist->current->track->Play();
}