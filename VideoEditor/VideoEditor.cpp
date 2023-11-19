#include "VideoEditor.h"

VideoEditor::VideoEditor()
{
	//cv::namedWindow("Video Editor", cv::WINDOW_AUTOSIZE);
}

VideoEditor::~VideoEditor()
{
	//cv::destroyWindow("Video Editor");
}

void VideoEditor::addVideo(const std::string name, std::shared_ptr<Video> video)
{
	cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
	this->windows_.try_emplace(name, video);
}

std::shared_ptr<Video> VideoEditor::getVideo(const std::string name)
{
	return this->windows_.find(name)->second;
}