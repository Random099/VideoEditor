#include "Video.h"

Video::Video(int device) //todo: frame read multithreading
{
	this->capSrc_.open(device);
	if (!this->capSrc_.isOpened()) 
		throw VideoInitException();
	this->FPS_ = this->capSrc_.get(cv::CAP_PROP_FPS);
	this->frameCount_ = this->capSrc_.get(cv::CAP_PROP_FRAME_COUNT);
	std::cout << device << '\t' << FPS_ << '\n';
	int x = this->frameCount_;
	std::cout << device << " frame count: " <<  x << '\n';
	this->parameterCreate(std::shared_ptr<Parameter>(new Parameter{ }));
	this->framesRead_ = std::unique_ptr<ConcurrentQueue<cv::Mat>>(new ConcurrentQueue<cv::Mat>);
	this->frameReader_ = std::thread([this] { this->frameRead(); });
}

Video::Video(const std::string& srcName)
{
	this->capSrc_.open(srcName);
	if (!this->capSrc_.isOpened())
		throw VideoInitException();
	this->FPS_ = capSrc_.get(cv::CAP_PROP_FPS);
	this->frameCount_ = this->capSrc_.get(cv::CAP_PROP_FRAME_COUNT);
	std::cout << srcName << '\t' << FPS_ << '\n';
	int x = this->frameCount_;
	std::cout << srcName << " frame count:" << x << '\n';
	this->parameterCreate(std::shared_ptr<Parameter>(new Parameter{ }));
	this->framesRead_ = std::unique_ptr<ConcurrentQueue<cv::Mat>>(new ConcurrentQueue<cv::Mat>);
	this->frameReader_ = std::thread([this] { this->frameRead(); });
}

Video::~Video()
{
	this->capSrc_.release();
}

void Video::frameRead()
{
	cv::Mat frameIn;
	while(--(this->frameCount_)) {
		this->capSrc_ >> frameIn;
		this->framesRead_->push(frameIn);
	}
}

std::shared_ptr<cv::Mat> Video::outFrameGet() 
{
	//this->frameRead();
	this->filterApply();
	return std::make_shared<cv::Mat>(this->frameOut_);
}

double Video::fpsGet() const
{
	return FPS_;
}

void Video::filterApply() 
{
	cv::Mat frameIn;
	this->framesRead_->wait_and_pop(frameIn);
	for(auto const& [type, param] : this->parameters_) {
		switch (type) {
			case PType::none:
				frameIn.copyTo(this->frameOut_);
				break;
			case PType::blur:
				cv::blur(frameIn, this->frameOut_, param->sizeGet());
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