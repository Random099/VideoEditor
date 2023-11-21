#include "Window.h"


WindowVideo::WindowVideo(const std::string& name, const std::string& source)
{
	this->thread_ = std::thread([this, name, source]{ this->run(name, source); });
	this->thread_.detach();
}

WindowVideo::WindowVideo(const std::string& name, int source)
{
	this->thread_ = std::thread([this, name, source] { this->run(name, source); });
	this->thread_.detach();
}

void WindowVideo::run(const std::string& name, const std::string& source)
{
	cv::namedWindow(name, cv::WINDOW_NORMAL);
	std::shared_ptr<Video> vPtr(new Video{ source });
	std::shared_ptr<cv::Mat> outputFrame;
	for (;;)
	{
		outputFrame = vPtr->outFrameGet();
		if (!outputFrame->empty())
			cv::imshow(name, *outputFrame);
		else
		{
			std::cout << name << " display finished.\n";
			break;
		}
		if (cv::waitKey(1000.0 / vPtr->fpsGet()) == 27) break;
	}
	cv::destroyWindow(name);
}

void WindowVideo::run(const std::string& name, int source)
{
	cv::namedWindow(name, cv::WINDOW_NORMAL);
	std::shared_ptr<Video> vPtr(new Video{ source });
	std::shared_ptr<cv::Mat> outputFrame;
	for (;;)
	{
		outputFrame = vPtr->outFrameGet();
		if (!outputFrame->empty())
			cv::imshow(name, *outputFrame);
		else
		{
			std::cout << name << " display finished.\n";
			break;
		}
		if (cv::waitKey(1000.0 / vPtr->fpsGet()) == 27) break;
	}
	cv::destroyWindow(name);
}