#include "Video.h"

Video::Video(int device) //todo: frame read multithreading
{
	this->capSrc_.open(device);
	if (!this->capSrc_.isOpened()) 
		throw VideoInitException();
	this->FPS_ = this->capSrc_.get(cv::CAP_PROP_FPS);
	this->frameCount_ = this->capSrc_.get(cv::CAP_PROP_FRAME_COUNT);
	this->parameterCreate(std::shared_ptr<Parameter>(new Parameter{ }));
}

Video::Video(const std::string& srcName)
{
	this->capSrc_.open(srcName);
	if (!this->capSrc_.isOpened())
		throw VideoInitException();
	this->FPS_ = capSrc_.get(cv::CAP_PROP_FPS);
	this->frameCount_ = this->capSrc_.get(cv::CAP_PROP_FRAME_COUNT);
	this->parameterCreate(std::shared_ptr<Parameter>(new Parameter{ }));
}

Video::~Video()
{
	this->capSrc_.release();
}

bool Video::frameRead()
{
	this->capSrc_ >> this->frameIn_;
	if (this->frameIn_.empty()) {
		this->frameEmptyFlag_ = true;
		this->frameOut_.copyTo(this->frameLast_);
		return false;
	}
	return true;
}

cv::Mat Video::outFrameGet() 
{
	//this->frameRead();
	this->filterApply();
	return this->frameOut_;
}

double Video::fpsGet() const
{
	return FPS_;
}

void Video::filterApply() 
{
	if (this->frameRead()) {
		for (auto const& [type, param] : this->parameters_) {
			switch (type) {
			case PType::none:
				this->frameIn_.copyTo(this->frameOut_);
				break;
			case PType::blur:
				cv::blur(this->frameIn_, this->frameOut_, param->sizeGet());
				break;
			default:
				break;
			}
			cv::cvtColor(this->frameOut_, this->frameOut_, cv::COLOR_BGR2RGBA);
		}
	}
}

void Video::parameterCreate(std::shared_ptr<Parameter> param)
{
	std::map<PType, std::shared_ptr<Parameter>>::size_type none = this->parameters_.erase(PType::none);
	this->parameters_.try_emplace(param->typeGet(), param);
}

int Video::frameCountGet() const
{
	return this->frameCount_;
}

bool Video::frameEmptyFlag()
{
	return this->frameEmptyFlag_;
}

cv::Mat Video::frameLastGet()
{
	return this->frameLast_;
}