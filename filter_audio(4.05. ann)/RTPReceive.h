#pragma once
#include "stdafx.h"
#include "Structs.h"
//#include "Utils.h"
#define INPUT_SAMPLERATE     44100
#define INPUT_FORMAT         AV_SAMPLE_FMT_S16
#define INPUT_CHANNEL_LAYOUT AV_CH_LAYOUT_STEREO

/** The output bit rate in kbit/s */
#define OUTPUT_BIT_RATE 8000
/** The number of output channels */
#define OUTPUT_CHANNELS 1
/** The audio sample output format */
#define OUTPUT_SAMPLE_FORMAT AV_SAMPLE_FMT_S16

#define VOLUME_VAL 0.90
class CRTPReceive
{
public:
	CRTPReceive(vector<string> SDPs) { FirstInit(); init(SDPs); }
	int init(vector<string> SDPs);
	int FirstInit();

	int process_all();
	int write_output_file_header(AVFormatContext *output_format_context);
	int write_output_file_trailer(AVFormatContext *output_format_context);
	int init_input_frame(AVFrame **frame);
	void init_packet(AVPacket *packet);
	int sdp_open(AVFormatContext **pctx, const char *data, AVDictionary **options);
	int init_filter_graph(int ForClient);
	int open_input_file(string sdp_string, AVFormatContext **input_format_context, AVCodecContext **input_codec_context);
	int open_output_file(const char *filename, int i);
	int decode_audio_frame(AVFrame *frame, AVFormatContext *input_format_context,
		AVCodecContext *input_codec_context, int *data_present, int *finished);
	int encode_audio_frame(AVFrame *frame, AVFormatContext *output_format_context,
		AVCodecContext *output_codec_context, int *data_present);

private:
	vector<AVFormatContext *> out_ifcx;
	vector<AVCodecContext *> out_iccx;

	vector<AVFormatContext *> ifcx;
	vector<AVCodecContext *> iccx;

	vector<SSource> afcx;//src(i)
	//AVFilterGraph *graph = NULL;
	//AVFilterContext *sink = NULL;
	vector<AVFilterGraph *> graphVec;
	vector<AVFilterContext *> sinkVec;

	const int tracks = 3;

	

	
};
typedef std::shared_ptr<CRTPReceive> SHP_CRTPReceive;