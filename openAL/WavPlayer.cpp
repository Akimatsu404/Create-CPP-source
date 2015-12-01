
/*

	Created by Akimatsu_404
	FileName : WavPlayer.cpp

*/

#include "WavPlayer.h"

#define BIT_16 16
#define BIT_8 8

namespace AKIMATSU_LIB {
	namespace WAV {

		WAV_Player::WAV_Player()
		{

			m_device = alcOpenDevice(NULL);
			m_context = alcCreateContext(m_device, NULL);
			alcMakeContextCurrent(m_context);


		}

		WAV_Player::~WAV_Player() {

			for (auto itr = m_sourceMap.begin(); itr != m_sourceMap.end(); ++itr) {
				m_sourceMap.erase(itr);
			}

			delete m_context;
			m_context = NULL;

			delete m_device;
			m_device = NULL;

		}

		void WAV_Player::Load(const std::string v_filename, const std::string v_wavName)
		{
			//ファイルをロード
			FILE *fp = NULL;
			fopen_s(&fp, v_filename.c_str(), "rb");
			assert(fp != NULL);

			WAV_FILE_FORMAT t_wavFormat;

			fread(
				&t_wavFormat,
				sizeof(WAV_FILE_FORMAT),
				1,
				fp
				);

			unsigned char* t_data = (unsigned char*)malloc(t_wavFormat.data_size);//new unsigned char[t_wavFormat.data_size];

			fread(
				t_data,
				t_wavFormat.data_size,
				1,
				fp
				);

			//セッティング

			ALenum t_channelBit;

			if (t_wavFormat.channel == MONORAL) {
				if (t_wavFormat.bit == BIT_16) {
					t_channelBit = AL_FORMAT_MONO16;
				}
				else if (t_wavFormat.bit == BIT_8) {
					t_channelBit = AL_FORMAT_MONO8;
				}
			}
			else if (t_wavFormat.channel == STEREO) {
				if (t_wavFormat.bit == BIT_16) {
					t_channelBit = AL_FORMAT_STEREO16;
				}
				else if (t_wavFormat.bit == BIT_8) {
					t_channelBit = AL_FORMAT_STEREO8;
				}
			}
			ALuint t_bid;
			alGenBuffers(1, &t_bid);

			alBufferData(t_bid, t_channelBit, t_data, t_wavFormat.data_size, t_wavFormat.rate);

			ALuint t_source;
			alGenSources(1, &t_source);

			alSourcei(t_source, AL_BUFFER, t_bid);

			m_sourceMap.insert(std::map<std::string, ALuint>::value_type(v_wavName, t_source));


			fclose(fp);

			//delete t_data;
			//t_data = NULL;
			free(t_data);

		}

		void WAV_Player::Release() {

		}

		void WAV_Player::Set_WAV(const std::string v_wavName)
		{
			m_playSource = m_sourceMap[v_wavName];

		}

		void WAV_Player::Play(const ALfloat v_volume) {

			
			//static float gain = 1.0f;
			alSourcef(
				m_playSource, // ALuint source
				AL_GAIN,// ALenum param
				v_volume);  // ALfloat value


			alSourcePlay(m_playSource);


		}

		void WAV_Player::Stop() {
			alSourcei(//リピートも止める。
				m_playSource,     // ALuint source
				AL_LOOPING, // ALenum param
				AL_FALSE);   // ALint value

			alSourcePause(m_playSource);

		}

		void WAV_Player::Repeat() {
			alSourcei(
				m_playSource,     // ALuint source
				AL_LOOPING, // ALenum param
				AL_TRUE);   // ALint value

		}

		void WAV_Player::Rewind() {
			alSourceRewind(m_playSource);

		}

		void WAV_Player::ChangeVolume(ALfloat v_volume) {
			alSourcef(
				m_playSource, // ALuint source
				AL_GAIN,// ALenum param
				v_volume);  // ALfloat value

		}

		void WAV_Player::ChangePitch(ALfloat v_pitch) {
			alSourcef(
				m_playSource,     // ALuint source
				AL_PITCH,   // ALenum param
				v_pitch);     // ALfloat value

		}


		void WAV_Player::IsLive_WAV() {

			ALint t_value;

			alGetSourcei(
				m_playSource,         // ALuint source
				AL_SOURCE_STATE,// ALenum param
				&t_value);        // ALint *value

			if (t_value == IS_LIVE_CHECKER::BEFOR) {
				printf("before PLAY\n");
			}
			else if (t_value == IS_LIVE_CHECKER::NOW) {
				printf("now PLAY\n");
			}
			else if (t_value == IS_LIVE_CHECKER::STOP) {
				printf("stop PLAY\n");
			}
			else if (t_value == IS_LIVE_CHECKER::END) {
				printf("end PLAY\n");
			}

		}

	}
}