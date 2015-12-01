/*

		Created by Akimatsu_404
		FileName : WavPlayer.h

*/

#ifndef __WAV_PLAYER_H_
#define __WAV_PLAYER_H_

#include <vector>
#include <map>
#include <assert.h>

#include "AL\alc.h"
#include "AL\al.h"

#pragma comment(lib,"OpenAL32.lib")

namespace AKIMATSU_LIB {
		enum CHANNEL_TYPE {
					MONORAL = 1,
					STEREO = 2
				};

		enum IS_LIVE_CHECKER {
			BEFOR = 0x1011,
			NOW = 0x1012,
			STOP = 0x1013,
			END = 0x1014
		};

	namespace WAV {

		struct WAV_FILE_FORMAT {

			char riff[4];              // = "RIFF"
			unsigned int total_size;    // �S�̃T�C�Y
			char fmt[8];               // "WAVEfmt "
			unsigned int fmt_size;      // fmt �`�����N�T�C�Y
			unsigned short  format;       // �t�H�[�}�b�g�̎��
			unsigned short  channel;      // �`�����l��
			unsigned int   rate;         // �T���v�����O���[�g
			unsigned int   avgbyte;      // rate * block
			unsigned short  block;        // channels * bit / 8
			unsigned short  bit;          // �r�b�g��
			char data[4];               // = "data"
			unsigned int data_size;      // �f�[�^�T�C�Y

		};

		class WAV_Player {

			//	WAV_FILE_FORMAT m_wavFile;
			std::map<std::string, ALuint> m_sourceMap;

			ALCdevice* m_device;
			ALCcontext* m_context;
			ALuint m_playSource;

			
		public:

			WAV_Player();
			~WAV_Player();

			void Load(const std::string v_filename, const std::string v_wavName);
			void Release();

			void Set_WAV(const std::string v_wavName);

			void Play(const ALfloat v_volume);
			void Stop();
			void Repeat();//�J��Ԃ�
			void Rewind();//�����߂�
			
			void ChangeVolume(ALfloat v_volume);//���ʕύX �����l1.0f
			void ChangePitch(ALfloat v_pitch);//�s�b�`�ύX 1�œ��{ �Q�{�̏㉺�ŃI�N�^�[�u���ς��

			void IsLive_WAV();

			//	void Get_WAV();

		};
	}
}

#endif