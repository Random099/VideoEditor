#include "Video.h"

Video::Video(int device)
{
	capSrc.open(device);
	if (!capSrc.isOpened()) 
		throw VideoInitException();
	FPS = capSrc.get(cv::CAP_PROP_FPS);
}

Video::Video(const std::string& srcName)
{
	capSrc.open(srcName);
	FPS = capSrc.get(cv::CAP_PROP_FPS);
}

Video::~Video()
{
	capSrc.~VideoCapture();
}

void Video::readFrame()
{
	capSrc >> this->originalFrame;
}

cv::Mat Video::getFrame()
{
	return this->originalFrame;
}

cv::Mat Video::getOutFrame()
{
	this->applyFilter();
	return this->outFrame;
}

int Video::getFPS() const
{
	return FPS;
}

void Video::applyFilter() {
	this->readFrame();
	for(auto const& [type, param] : this->parameters) {
		switch (type) {
			case PType::blur:
				cv::blur(this->originalFrame, this->outFrame, param->getSize());
				break;
		}
	}
}

void Video::addParameter(Parameter* param)
{
	this->parameters.try_emplace(param->getType(), param);
}