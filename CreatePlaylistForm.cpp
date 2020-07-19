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

#include "CreatePlaylistForm.h"
#include "PlayerMusic.h"
#include "MyForm.h"
#include <fstream>
#include <commdlg.h>
#include <Windows.h>
#include <vector>

using namespace MusicPlayer;
using namespace playermusic;
using std::vector;

extern OPENFILENAME ofile;

struct TrackPaths {
	char* path;
	TrackPaths* prev;
	TrackPaths* next;

	TrackPaths();

	void AddPath(char* path);

	void Delete();
};

static TrackPaths* list = new TrackPaths();

TrackPaths::TrackPaths() {
	path = nullptr;
	prev = nullptr;
	next = nullptr;
}

void TrackPaths::AddPath(char* path) {
	if (list->path != nullptr) {
		list->next = new TrackPaths();
		list->next->prev = list;
		list = list->next;
	}
	list->path = new char[strlen(path) + 1];
	strcpy(list->path, path);
}

void TrackPaths::Delete() {
	TrackPaths* ptr = this;

	if (ptr->next != nullptr) 
		ptr->next->Delete();

	delete[] ptr->path;
	delete this;
}

System::Void CreatePlaylistForm::buttonSave_Click(System::Object^ sender, System::EventArgs^ e) {
	wchar_t File[MAX_PATH_LENGTH];
	memset(File, 0, MAX_PATH_LENGTH);
	wchar_t FileTitle[MAX_PLAYLIST_NAME];
	memset(FileTitle, 0, MAX_PLAYLIST_NAME);
	wchar_t Filter[30] = L"Playlist file *.pll\0*.pll\0";

	for (int i = 0; i < this->textBoxName->Text->Length; i++)
		File[i] = textBoxName->Text[i];

	ofile.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	ofile.lpstrTitle = L"Create and save playlist";
	ofile.lStructSize = sizeof(OPENFILENAME);
	ofile.hwndOwner = NULL;
	ofile.lpstrFilter = Filter;
	ofile.nFilterIndex = 1;
	ofile.lpstrFile = File;
	ofile.nMaxFile = sizeof(File);
	ofile.lpstrFileTitle = FileTitle;
	ofile.nMaxFileTitle = sizeof(FileTitle);
	ofile.lpstrInitialDir = L"C:\\";

	bool save = GetSaveFileName(&ofile);

	if (save) {
		const wchar_t* ptr = wcsstr(ofile.lpstrFile, L".pll");
		if (ptr == nullptr)
			wcsncat(ofile.lpstrFile, L".pll", MAX_PATH_LENGTH);

		std::ofstream fout;

		fout.open(ofile.lpstrFile, std::ios_base::trunc | std::ios_base::out);
		if (!fout.is_open()) {
			MessageBoxW(NULL, L"Failed to create playlist.", NULL, MB_OK);
			return;
		}

		char name[MAX_PLAYLIST_NAME]{};
		wcstombs(name, ofile.lpstrFileTitle, wcslen(ofile.lpstrFile) + 1);
		char path[MAX_PATH_LENGTH]{};
		wcstombs(path, ofile.lpstrFile, wcslen(ofile.lpstrFile) + 1);

		fout << name << '\0';
		fout << path << '\0';

		for (; list->prev != nullptr; list = list->prev)
			continue;
		
		for (TrackPaths* ptr = list; ptr != nullptr; ptr = ptr->next)
			if(ptr->path != nullptr)
				fout << ptr->path << '\0';

		fout.close();
		list->Delete();
		this->~CreatePlaylistForm();
	}
}

System::Void CreatePlaylistForm::buttonAddTrack_Click(System::Object^ sender, System::EventArgs^ e) {
	wchar_t File[MAX_PATH_LENGTH];
	memset(File, 0, MAX_PATH_LENGTH);
	wchar_t FileTitle[MAX_PLAYLIST_NAME];
	memset(FileTitle, 0, MAX_PLAYLIST_NAME);
	wchar_t Filter[30] =
		L"Mp3 Files *.mp3\0*.mp3\0";

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
		list->AddPath(path);

		System::String ^str = gcnew System::String(ofile.lpstrFileTitle);
		listView1->Items->Add(str);
	}
}