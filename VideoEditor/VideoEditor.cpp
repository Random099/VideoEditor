#include "VideoEditor.h"

void test(int pos, void* data)
{
	*(int*)data = pos;
	std::cout << *(int*)data << '\n';
}

VideoEditor::VideoEditor()
{
	testData = 0;
	//this->controlPanelCreate(ControlPanel::defaultName);
}

VideoEditor::~VideoEditor()
{
	//cv::destroyWindow("Video Editor");
}

std::shared_ptr<std::thread> VideoEditor::getWindow(const std::string& name)
{
	return this->windows_.find(name)->second;
}

void VideoEditor::windowCreate(const std::string& name, int source)
{

	this->windows_.try_emplace(name, new std::thread([this, name, source]{ videoDisplay(name, source); }));
	this->windows_.at(name)->detach();
}

void VideoEditor::windowCreate(const std::string& name, const std::string& source)
{

	this->windows_.try_emplace(name, new std::thread([this, name, source]{ videoDisplay(name, source); }));
	this->windows_.at(name)->detach();
}

void VideoEditor::windowDestroy(const std::string& name)
{
	//this->windows_[name]->join();
	std::map<std::string, std::shared_ptr<std::thread>>::size_type erased = this->windows_.erase(name);
	//std::cout << erased << '\n';
	//this->windows_.erase(name);
}

void VideoEditor::videoDisplay(const std::string& name, int source)
{
	cv::namedWindow(name, cv::WINDOW_NORMAL);
	std::shared_ptr<Video> vPtr(new Video{ source });
	std::shared_ptr<cv::Mat> outputFrame;
	for (;;) {
		outputFrame = vPtr->outFrameGet();
		if (!outputFrame->empty()) {
			cv::imshow(name, *outputFrame);
		}
		else {
			break;
		}
		if (cv::waitKey(1000.0 / vPtr->fpsGet()) == 27) break;
	}
	cv::destroyWindow(name);
}

void VideoEditor::videoDisplay(const std::string& name, const std::string& source)
{
	cv::namedWindow(name, cv::WINDOW_NORMAL);
	std::shared_ptr<Video> vPtr(new Video{ source });
	std::shared_ptr<cv::Mat> outputFrame;
	for (;;) {
		outputFrame = vPtr->outFrameGet();
		if (!outputFrame->empty()) {
			cv::imshow(name, *outputFrame);
		}
		else {
			std::cout << name << " display finished.\n";
			break;
		}
		if (cv::waitKey( (1000.0 / vPtr->fpsGet()) / 2) == 27) break;
	}
	cv::destroyWindow(name);
}

void VideoEditor::controlPanelCreate(const std::string& cpName) {
	this->controlPanels_.try_emplace(
		cpName,
		new std::thread([this, cpName] { controlPanelRun(cpName); })
	);
	this->controlPanels_.at(cpName)->detach();
}

void VideoEditor::controlPanelDestroy(const std::string& cpName)
{
	//this->controlPanels_.at(cpName)->join();
	std::map<std::string, std::shared_ptr<std::thread>>::size_type erased = this->controlPanels_.erase(cpName);
}

void VideoEditor::controlPanelRun(const std::string& cpName) {
	cv::namedWindow(cpName, cv::WINDOW_NORMAL);
	ControlPanel controlPanel{ cpName };
	for (;;) {
		//cv::imshow(cpName, ControlPanel::imgBackground);
		if (cv::waitKey(0) == 98) {
			controlPanel.trackbarCreate("blur", test, &this->testData, controlPanel.posGet(), controlPanel.maxGet());
		}
		else {
			break;
		}
	}
	cv::destroyWindow(cpName);
}

std::shared_ptr<std::thread> VideoEditor::operator[](const std::string& name)
{
	return this->windows_.at(name);
}

/*

Control Panel

*/

ControlPanel::ControlPanel(const std::string& cpName)
{
	this->name_ = cpName;
	//cv::putText(background, "ControlPanel", cv::Point(0, 0), cv::FONT_ITALIC, 1, cv::Scalar(0, 0, 0), 2);
}

inline std::string ControlPanel::nameGet() const
{
	return this->name_;
}

int* ControlPanel::posGet() {
	return &this->pos;
}

int ControlPanel::maxGet() {
	return this->max;
}

void ControlPanel::trackbarCreate(const std::string& name, void(*func)(int, void*), void* data, int* pos, int max)
{
	cv::createTrackbar(name, this->name_, nullptr, max, func, data);
	cv::setTrackbarPos(name, this->name_, *pos);
	this->trackbars_.push_back(name);
}

void ControlPanel::targetChange(const std::string& name, int* target)
{
	cv::setTrackbarPos(name, this->name_, *target);
}