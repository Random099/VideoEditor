#include "Video.h"

Video::Video(int device)
{
	this->capSrc_.open(device);
	if (!this->capSrc_.isOpened()) 
		throw VideoInitException();
	FPS_ = this->capSrc_.get(cv::CAP_PROP_FPS);
	this->addParameter(std::shared_ptr<Parameter>(new Parameter{ }));
}

Video::Video(const std::string& srcName)
{
	this->capSrc_.open(srcName);
	if (!this->capSrc_.isOpened())
		throw VideoInitException();
	this->FPS_ = capSrc_.get(cv::CAP_PROP_FPS);
	this->addParameter(std::shared_ptr<Parameter>(new Parameter{ }));
}

Video::~Video()
{
	this->capSrc_.~VideoCapture();
}

inline void Video::readFrame()
{
	this->capSrc_ >> this->originalFrame_;
}

cv::Mat Video::getFrame()
{
	return this->originalFrame_;
}

cv::Mat Video::getOutFrame()
{
	this->readFrame();
	this->applyFilter();
	return this->outFrame_;
}

int Video::getFPS() const
{
	return FPS_;
}

void Video::applyFilter() {
	for(auto const& [type, param] : this->parameters_) {
		switch (type) {
			case PType::none:
				this->originalFrame_.copyTo(this->outFrame_);
				break;
			case PType::blur:
				cv::blur(this->originalFrame_, this->outFrame_, param->getSize());
				break;
			default:
				break;
		}
	}
}

void Video::addParameter(std::shared_ptr<Parameter> param)
{
	std::map<PType, std::shared_ptr<Parameter>>::size_type none = this->parameters_.erase(PType::none);
	this->parameters_.try_emplace(param->getType(), param);
}