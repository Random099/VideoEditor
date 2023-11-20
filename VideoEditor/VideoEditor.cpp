#include "VideoEditor.h"

VideoEditor::VideoEditor()
{
	//cv::namedWindow("Video Editor", cv::WINDOW_AUTOSIZE);
}

VideoEditor::~VideoEditor()
{
	//cv::destroyWindow("Video Editor");
}

void VideoEditor::addWindow(const std::string& name, int source)
{

	this->windows_.try_emplace(name, new std::thread([this, name, source] { displayVideo(name, source); }));
}

void VideoEditor::addWindow(const std::string& name, const std::string& source)
{

	this->windows_.try_emplace(name, new std::thread([this, name, source] { displayVideo(name, source); }));
}

std::shared_ptr<std::thread> VideoEditor::getWindow(const std::string& name)
{
	return this->windows_.find(name)->second;
}

void VideoEditor::displayVideo(const std::string& name, int source)
{
	cv::namedWindow(name, cv::WINDOW_NORMAL);
	std::shared_ptr<Video> vPtr(new Video{ source });
	for (;;) {
		cv::imshow(name, vPtr->getOutFrame());
		if (cv::waitKey(1000.0 / vPtr->getFPS()) == 27) break;
	}
}

void VideoEditor::displayVideo(const std::string& name, const std::string& source)
{
	cv::namedWindow(name, cv::WINDOW_NORMAL);
	std::shared_ptr<Video> vPtr(new Video{ source });
	for (;;) {
		cv::imshow(name, vPtr->getOutFrame());
		if (cv::waitKey(1000.0 / vPtr->getFPS()) == 27) break;
	}
}

void VideoEditor::removeWindow(const std::string& name)
{
	this->windows_.find(name)->second->join();
	this->windows_.erase(name);
}