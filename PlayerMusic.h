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
#ifndef MP3PLAYER_H
#define MP3PLAYER_H

#include <iostream>
#include <string>
#include "bass.h"

#define MAX_PATH_LENGTH 260
#define MAX_TRACK_NAME 100
#define MAX_PLAYLIST_NAME 40

using std::cout;
using std::string;

void PrintDeviceInfo();

namespace playermusic {

	class PlayerMusic
	{
	private:
		static HSTREAM stream;
		static bool active;
		static int currTime;			// current track time in the seconds
		static char* strCurrTime;		// current track time in format "mmm : ss"
		static bool playing;			// if the track is playing - var playing equal to true, else false 
		static UINT_PTR timer;			//Current Timer

	public:
		struct Playlist;
		static Playlist *playlist;
		
		enum PlayMode {
			LIST_REPEAT = 1,		// After the last track will be the first.
			RANDOM_LIST = 2,		// All tracks in the playlist go in random sequence.
			REPEAT_TRACK = 8,		// Repeat the one track.
		};

		struct Track {
		private:
			
			char* name;				// track name
			char* path;				// path to mp3 file
			int duration;			// duration of track in seconds
			char* strDuration;		// duratin in format "mmm : ss"

			/* Constructor of class Track.
			 * param path the path to mp3 file.
			 */
			Track(const char* path);

			/* This method set a tack duration.
			 * Returns nothing (void).
			 */
			void SetDuration();

			/* This method set the name of track (mp3 file).
			 * Returns nothing(void).
			 */
			void SetName();

		public:
			/* Function creates a new track based on it's title and duration.
			 * param path the path to the track.
			 * return reference to the track or nullptr.
			 */
			static Track* Create(const char* path);

			// This mmethod frees track from the memory.
			void Delete();

			/* This method plays the track (mp3 file).
			 * Returns nothing (void).
			 */
			void Play();

			/* This method pauses the track (mp3 file).
			 * Returns nothing (void).
			 */
			void Pause();

			/* This method continue the track (mp3 file).
			 * Returns nothing (void).
			 */
			void Continue();

			// This method return the duration of track in format "mmm : ss".
			const char* GetDurationStr();

			// This method return the duration of track in seconds.
			int GetDuration();

			// This method return the name of track (mp3 file).
			const char* GetName();

			//This method return the path to track.
			char* GetPath();
		};

		struct List {
			Track* track;			// reference to track
			List* next;				// reference to the next list with track in the playlist
			List* prev;				// reference to the previous list with track in the playlist

			/* Constructor of class List.
			 * param track the pointer to new track.
			 * param prev the pointer to previous list with track.
			 */
			List(Track* track = nullptr, List* prev = nullptr);
		};

		struct Playlist {
		private:
			char* name;				// playlist name
			char* path;				// path to playlist
			int count;				// numbers of track in playlist
			int duration;			// lenght of playlist in seconds.
			BYTE mode;				// playing mode (combination of PlayMode enumeration constants)

			//Constructor of class Playlist
			Playlist(char* name, char* path);

		public:
			List* first;			// first track int the playlist
			List* current;			// curent track

			/* This method creates new playlist with name.
			 * param name the name of the new playlist.
			 * This method return reference to the created playlist or nullptr.
			 */
			static Playlist* Create(char* name, char* path);

			/* This method removes the playlist from the memory and all track.
			 * returns nothing (void).
			 */
			void Delete();

			/* This method play the previous track in the playlist.
			 * returns nothing (void).
			 */
			void Prev();

			/* This method play the next track int the playlist.
			 * returns nothing (void).
			 */
			void Next();

			/* This method add the new track to the playlist.
			 * param track the track, which will be added.
			 * returns nothing (void).
			 */
			void AddTrack(Track* track);

			/* This method to change the play mode playlist.
			 * param mode the new play mode or their combination.
			 * returns nothing (void).
			 */
			void ChangeMode(BYTE mode);

			/* This method mixes the tracks in new (random) sequence.
			 * returns nothing (void).
			 */
			void RandomList();

			//This method return the reference to the playlist name.
			char* GetName();

			//This method return the duration of playlist.
			int GetDuration();

			//This method return the count of track in playlist.
			int GetCount();

			//This method return the mode of playlist.
			int GetMode();

			//This method return the path to playlist file.
			char* GetPath();
		};

		/* Initialization of the Music Player.
		 * Method return noting (void).
		 */
		static void Init();

		/* This method delete the BASS and BASS_Stream of PlayerMusic class.
		 * Also this method delete Playlist with track from the memory.
		 * param playlist the reference to playlist
		 */
		static void Delete(Playlist* playlist);

		// This method sets the time in seconds in the variable "currTime".
		static void SetCurrTime();

		// This method return the current time of track in format "mmm : ss".
		static const char* GetCurrTime();

		//This method return true if track is playing, else return false.
		static bool IsPlaying();

		//This method return true if track was finished, else return false.
		//static bool IsEnd();

		//This method return true if stream was created, else return false.
		static bool StreamIsActive();
	};
}

#endif
