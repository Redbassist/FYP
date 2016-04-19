#pragma once

#include "stdafx.h"
#include <string> 
#include <sapi.h> 
#include <atlbase.h> 
#include <sphelper.h> 
#include <atlcom.h> 
#include <queue> 

class VoiceReceiver {
private:

	CComPtr <ISpVoice>		cpVoice;
	CComPtr <ISpStream>		cpStream;
	CSpStreamFormat			cAudioFmt;
	HRESULT hr;

	//Create a SAPI Voice
	ISpVoice * voice;

	queue<std::string> voiceQueue;

public:
	static VoiceReceiver* GetInstance();

	VoiceReceiver();

	void Reset();

	void ReleaseVoice();

	void CloseStream();

	void WriteTextToFile(std::string text);

	void AddVoiceToQueue(std::string text);

	void ProcessVoiceQueue();
};