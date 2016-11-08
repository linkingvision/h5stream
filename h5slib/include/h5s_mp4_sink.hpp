#ifndef __H5S_MP4_SINK__
#define __H5S_MP4_SINK__

#include <string.h>
#include <vector>
#include <iostream>
#include <vector>

#include "h5s_sink.hpp"
#include "h264_parser.h"

extern "C" {
#include <libavformat/avformat.h>
};

//#define H5S_RAW_FILE 1

using namespace media;
class  H5S_LIBRARY_API H5SMP4Callback
{
public:
	virtual bool  onH5SMP4Data(unsigned char* buffer, int size) = 0;
};

class H5S_LIBRARY_API H5SMP4Sink : public H5SCallback
{
public:
	H5SMP4Sink(H5SMP4Callback &pCallback);
	~H5SMP4Sink();
public:
	static int WritePacket(void *opaque, unsigned char *buf, int buf_size);
	bool AddVideoTrack(const H264SPS* pSPS, const H264PPS* pPPS, H264NALU &nal_sps, 
		H264NALU &nal_pps);
public:
	virtual bool  onH5SData(unsigned char* buffer, int size, unsigned long long secs, 
			unsigned long long msecs, H5SCodecType codec, H5SStreamType stream, 
			H5SFrameType frm);
	bool  onH5SMP4Data(unsigned char* buffer, int size);
private:
	H5SMP4Callback &m_pCallback;
	AVFormatContext *m_pFormatContext;
	unsigned int m_vId;
	unsigned int m_avioBufferLen;
	unsigned long long int m_fileDuration;
	long long int m_lastMsecs;
#ifdef H5S_RAW_FILE
	FILE *m_fptr;
#endif
};



#endif 

