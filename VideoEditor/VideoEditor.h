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
	void addVideo(const std::string, std::shared_ptr<Video>);
	std::shared_ptr<Video> getVideo(const std::string);
private:
	std::map<std::string, std::shared_ptr<Video>> windows_;
	//std::vector<Video> videos_;
};
