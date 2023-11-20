#pragma once

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <memory>
#include <utility>
#include <map>
#include "Video.h"

class VideoEditor
{
public:
	VideoEditor();
	~VideoEditor();
	void addWindow(const std::string&, int source);
	void addWindow(const std::string&, const std::string& source);
	std::shared_ptr<std::thread> getWindow(const std::string&);
	void displayVideo(const std::string&, int source);
	void displayVideo(const std::string&, const std::string& source);
	void removeWindow(const std::string&);
private:
	std::map<std::string, std::shared_ptr<std::thread>> windows_;
	//std::vector<Video> videos_;
};
