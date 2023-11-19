#pragma once

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <memory>
#include "Video.h"

class VideoEditor
{
public:
	VideoEditor();
	~VideoEditor();
	void appendVideo(Video);
	Video& getVideo(int);
private:
	std::vector<Video> videos;
};
