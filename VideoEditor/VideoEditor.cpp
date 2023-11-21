#include "VideoEditor.h"

VideoEditor::VideoEditor()
{
	//this->controlPanelCreate(ControlPanel::defaultName);
}

VideoEditor::~VideoEditor()
{
	//cv::destroyWindow("Video Editor");
}

std::shared_ptr<WindowVideo> VideoEditor::getWindow(const std::string& name)
{
	return this->videoWindows_.find(name)->second;
}

void VideoEditor::videoWindowCreate(const std::string& name, int source)
{
	this->videoWindows_.try_emplace(name, new WindowVideo(name, source));
}

void VideoEditor::videoWindowCreate(const std::string& name, const std::string& source)
{
	this->videoWindows_.try_emplace(name, new WindowVideo(name, source));
}

void VideoEditor::videoWindowDestroy(const std::string& name)
{
	//this->windows_[name]->join();
	std::map<std::string, std::shared_ptr<WindowVideo>>::size_type erased = this->videoWindows_.erase(name);
	//std::cout << erased << '\n';
	//this->windows_.erase(name);
}

void VideoEditor::controlPanelCreate(const std::string& name)
{
	this->controlPanels_.try_emplace(name, new ControlPanel{ name });
}

void VideoEditor::controlPanelDestroy(const std::string& cpName)
{
	//this->controlPanels_.at(cpName)->join();
	std::map<std::string, std::shared_ptr<ControlPanel>>::size_type erased = this->controlPanels_.erase(cpName);
}

std::shared_ptr<WindowVideo> VideoEditor::operator[](const std::string& name)
{
	return this->videoWindows_.at(name);
}
