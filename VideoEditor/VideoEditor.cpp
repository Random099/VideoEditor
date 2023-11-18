#include "VideoEditor.h"

VideoEditor::VideoEditor()
{
	cv::namedWindow("Video Editor", cv::WINDOW_AUTOSIZE);
}

VideoEditor::~VideoEditor()
{
	cv::destroyWindow("Video Editor");
}

void VideoEditor::appendVideo(Video* video)
{
	this->videos.push_back(video);
}

Video* VideoEditor::getVideo(int videoIdx) const
{
	return this->videos[videoIdx];
}