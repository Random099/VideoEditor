#include "ControlPanel.h"

void test(int pos, void* data)
{
	*(int*)data = pos;
	std::cout << *(int*)data << '\n';
}

int testData = 0;

ControlPanel::ControlPanel(const std::string& name)
{
	//this->run(name);
	this->thread_ = std::thread([this, name] { this->run(name); });
	this->thread_.detach();
}

void ControlPanel::run(const std::string& name) {
	cv::namedWindow(name, cv::WINDOW_NORMAL);
	this->background_.open("wichu.mp4");
	std::vector<std::string> trackbars;
	int pos = 0;
	int max = 100;
	cv::Mat bgFrame;
	for (;;) {
		this->background_ >> bgFrame;
		cv::imshow(name, bgFrame);
		int command = cv::waitKey(1);
		if (command == 98)
		{
			cv::createTrackbar("blur", name, nullptr, max, test, &testData);
			cv::setTrackbarPos("blur", name, pos);
			trackbars.push_back("blur");
		}
		else if (command == 27) {
			break;
		}
	}
	cv::destroyWindow(name);
}