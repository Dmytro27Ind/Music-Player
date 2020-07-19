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

#define _CRT_SECURE_NO_WARNINGS

#include "PlayerMusic.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <ctime>

using namespace playermusic;
using std::cerr;
using std::vector;

typedef PlayerMusic::Track Track;
typedef PlayerMusic::Playlist Playlist;

HSTREAM PlayerMusic::stream{};
bool PlayerMusic::active = false;
Playlist* PlayerMusic::playlist = nullptr;
int PlayerMusic::currTime = 0;
char* PlayerMusic::strCurrTime = nullptr;
bool PlayerMusic::playing = false;
UINT_PTR PlayerMusic::timer = NULL;


void PlayerMusic::Init() {
	if (!BASS_Init(-1, 44100, 0, 0, nullptr)) {
		cerr << "Error: Audio device wasn't initializated. Code: 1\n";
		exit(1);
	}
}

void PlayerMusic::Delete(Playlist* playlist) {
	active = false;
	if(playlist != nullptr)
		playlist->Delete();
	BASS_StreamFree(stream);
	BASS_Free();
}

void PlayerMusic::SetCurrTime() {
	if (currTime == playlist->current->track->GetDuration()) {
		currTime = 0;
		playing = false;
		active = false;
		delete[] strCurrTime;
		strCurrTime = nullptr;
	}
	else if (playing && active) {
		currTime++;

		delete[] strCurrTime;
		int min{}, sec{};
		min = currTime / 60;
		sec = currTime - min * 60;
		strCurrTime = new char[9];			// mmm : ss\0
		if (min < 10)
			sprintf(strCurrTime, " %d : %d", min, sec);
		else
			sprintf(strCurrTime, "%d : %d", min, sec);
	}
}

const char* PlayerMusic::GetCurrTime() {
	return strCurrTime;
}

bool PlayerMusic::IsPlaying() {
	return (playing == true) ? true : false;
}

bool PlayerMusic::StreamIsActive() {
	return (active == true) ? true : false;
}

Track::Track(const char* path) {
	this->name = new char[MAX_TRACK_NAME];
	this->path = new char[MAX_PATH_LENGTH];

	strncpy(this->path, path, MAX_PATH_LENGTH);
	SetName();
	SetDuration();
}

Track* Track::Create(const char* path) {
	Track* track = new Track(path);
	return track;
}

void Track::Delete() {
	delete[] name;
	delete[] path;
	delete[] strDuration;
	delete this;
}

void Track::Play() {
	BASS_StreamFree(stream);
	stream = BASS_StreamCreateFile(false, (void*)path, 0, 0, 0);
	BASS_ChannelPlay(stream, false);

	currTime = 0;
	KillTimer(0, timer);
	timer = SetTimer(0, 0, 1000, (TIMERPROC)PlayerMusic::SetCurrTime);

	playing = true;
	active = true;
}

void Track::Pause() {
	BASS_ChannelPause(stream);
	playing = false;
}

void Track::Continue() {
	BASS_ChannelPlay(stream, false);
	playing = true;
}

void Track::SetDuration() {
	QWORD length;

	HSTREAM s = BASS_StreamCreateFile(false, (void*)path, 0, 0, 0);
	length = BASS_ChannelGetLength(s, BASS_POS_BYTE);			// the length in bytes
	length = (QWORD)BASS_ChannelBytes2Seconds(s, length);		// the length in seconds
	BASS_StreamFree(s);

	duration = int(length);

	int min{}, sec{};
	min = int(duration / 60);
	sec = duration - min * 60;

	strDuration = new char[9];			// mmm : ss\0
	if (min < 10)
		sprintf(strDuration, " %d : %d", min, sec);
	else
		sprintf(strDuration, "%d : %d", min, sec);
}

const char* Track::GetDurationStr() {
	return strDuration;
}

int Track::GetDuration() {
	return duration;
}

void Track::SetName() {
	HSTREAM s = BASS_StreamCreateFile(false, (void*)path, 0, 0, 0);

	BASS_CHANNELINFO info;
	BASS_ChannelGetInfo(s, &info);

	const char* fname = info.filename;
	const char* ptr = strrchr(fname, '\\');
	if (ptr != nullptr)
		fname = ptr + 1;

	char ncName[MAX_TRACK_NAME];
	strncpy(ncName, fname, MAX_TRACK_NAME);
	char *p = strstr(ncName, ".mp3");
	p[0] = '\0';

	strncpy(name, ncName, MAX_TRACK_NAME);
	BASS_StreamFree(s);
}

const char* Track::GetName() {
	return name;
}

char* Track::GetPath() {
	return path;
}

PlayerMusic::List::List(Track* track, List* prev) {
	this->track = track;
	this->prev = prev;
	next = nullptr;
}

Playlist::Playlist(char* name, char* path) {
	this->name = new char[MAX_PLAYLIST_NAME];
	strncpy(this->name, name, MAX_PLAYLIST_NAME);

	this->path = new char[MAX_PATH_LENGTH];
	strncpy(this->path, path, MAX_PATH_LENGTH);

	count = 0;
	duration = 0;
	mode = 0;		// default mode

	first = nullptr;
	current = nullptr;
}

Playlist* Playlist::Create(char* name, char* path) {
	Playlist* playlist = new Playlist(name, path);
	return playlist;
}

void Playlist::Delete() {
	delete[] name;
	delete[] path;

	if (first == nullptr) {
		delete this;
		return;
	}

	if (first->next == nullptr) {
		first->track->Delete();
		delete first;
	}
	else {
		List* ptr;
		for (ptr = first->next; ptr->next != nullptr; ptr = ptr->next) {
			ptr->prev->track->Delete();
			delete ptr->prev;
		}
		ptr->prev->track->Delete();
		delete ptr->prev;
		ptr->track->Delete();
		delete ptr;
	}
	delete this;
}

void Playlist::AddTrack(Track* track) {
	count++;
	duration += track->GetDuration();

	if (current == nullptr) {
		current = new List(track);
		first = current;
		return;
	}
	while (current->next != nullptr)
		current = current->next;
	current->next = new List(track, current);
	current = current->next;
}

void Playlist::Prev() {
	if (current->prev != nullptr)
		current = current->prev;

	else if ((mode & LIST_REPEAT) == LIST_REPEAT)
		while (current->next != nullptr)
			current = current->next;

	delete[] strCurrTime;
	strCurrTime = nullptr;
	currTime = 0;
	playing = true;
	active = true;
}

void Playlist::Next() {
	if (current->next != nullptr)
		current = current->next;

	else if ((mode & LIST_REPEAT) == LIST_REPEAT)
		while (current->prev != nullptr)
			current = current->prev;

	delete[] strCurrTime;
	strCurrTime = new char[9];		// mmm : ss\0
	strncpy(strCurrTime, " 0 : 0 ", 9);
	currTime = 0;
	playing = true;
	active = true;
}

void Playlist::RandomList() {
	vector <Track*> list;
	for (List *ptr = playlist->first; ptr != nullptr; ptr = ptr->next)
		list.push_back(ptr->track);

	int count = playlist->GetCount();
	int num = count;
	srand(time(nullptr));

	for (int i = 0; i < count; i++, num--) {
		int r = rand() % num;

		List* ptr = playlist->first;
		for (int j=0; j < i; j++)
			ptr = ptr->next;
		ptr->track = list[r];

		for (int j = r; j < num-1; j++)
			list[r] = list[j + 1];
	}
}

void Playlist::ChangeMode(BYTE mode) {
	this->mode = mode;
}

char* Playlist::GetName() {
	return name;
}

int Playlist::GetDuration() {
	return duration;
}

int Playlist::GetCount() {
	return count;
}

int Playlist::GetMode() {
	return int(mode);
}

char* Playlist::GetPath() {
	return path;
}

void PrintDeviceInfo() {
	cout << "List of devices:\n\n";
	BASS_DEVICEINFO list;

	for (int i = 1; BASS_GetDeviceInfo(i, &list); i++) {

		if (list.flags & BASS_DEVICE_ENABLED)
			cout << "Device " << i << ": " << list.name << " is enable\n";
		else
			cout << "Device " << i << ": " << list.name << " is unable\n";
	}
	cout << "\nTHE END OF DEVICE LIST\n";
}
