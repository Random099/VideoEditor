#include "Video.h"

Video::Video(int device)
{
	this->capSrc_.open(device);
	if (!this->capSrc_.isOpened()) 
		throw VideoInitException();
	FPS_ = this->capSrc_.get(cv::CAP_PROP_FPS);
	std::cout << device << '\t' << FPS_ << '\n';
	this->parameterCreate(std::shared_ptr<Parameter>(new Parameter{ }));
}

Video::Video(const std::string& srcName)
{
	this->capSrc_.open(srcName);
	if (!this->capSrc_.isOpened())
		throw VideoInitException();
	this->FPS_ = capSrc_.get(cv::CAP_PROP_FPS);
	std::cout << srcName << '\t' << FPS_ << '\n';
	this->parameterCreate(std::shared_ptr<Parameter>(new Parameter{ }));
}

Video::~Video()
{
	this->capSrc_.release();
}

inline void Video::frameRead()
{
	this->capSrc_ >> this->originalFrame_;		
}

std::shared_ptr<cv::Mat> Video::originalFrameGet()
{
	return std::make_shared<cv::Mat>(this->originalFrame_);
}

std::shared_ptr<cv::Mat> Video::outFrameGet()
{
	this->frameRead();
	this->filterApply();
	return std::make_shared<cv::Mat>(this->outFrame_);
}

double Video::fpsGet() const
{
	return FPS_;
}

void Video::filterApply() 
{
	for(auto const& [type, param] : this->parameters_) {
		switch (type) {
			case PType::none:
				this->originalFrame_.copyTo(this->outFrame_);
				break;
			case PType::blur:
				cv::blur(this->originalFrame_, this->outFrame_, param->sizeGet());
				break;
			default:
				break;
		}
	}
}

void Video::parameterCreate(std::shared_ptr<Parameter> param)
{
	std::map<PType, std::shared_ptr<Parameter>>::size_type none = this->parameters_.erase(PType::none);
	this->parameters_.try_emplace(param->typeGet(), param);
}