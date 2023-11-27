#include "WindowVideo.h"


WindowVideo::WindowVideo(const std::string& name, const std::string& source) : isSourceCam_(false), video_(source), name_(name)
{
	this->videoFrameCount_ = this->video_.frameCountGet();
	this->frameReader_ = std::thread([this] { this->readFrames(); });
	this->frameReader_.detach();
}

WindowVideo::WindowVideo(const std::string& name, const int source) : isSourceCam_(true), video_(source), name_(name)
{
	this->videoFrameCount_ = this->video_.frameCountGet();
	this->frameReader_ = std::thread([this] { this->readFrames(); });
	this->frameReader_.detach();
}

void WindowVideo::readFrames() 
{
	if (!this->isSourceCam_) 
	{
		while (1)
		{
			this->framesRead_.push(this->video_.outFrameGet());
			if (!this->video_.frameEmptyFlag())
				this->framesRead_.push(this->video_.outFrameGet());
			else
				break;
		}
	}
	else 
	{
		while (1) 
			this->framesRead_.push(this->video_.outFrameGet());
	}
}

void WindowVideo::run()
{
	if (this->currentFrameId_ < this->videoFrameCount_)
	{
		this->framesRead_.wait_and_pop(this->frame_);
		++this->currentFrameId_;
	}
	else if(this->isSourceCam_)
		this->framesRead_.wait_and_pop(this->frame_);
	else
		this->video_.frameLastGet().copyTo(this->frame_);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->frame_.cols, this->frame_.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->frame_.data);
	
	ImGui::Begin(this->name_.c_str());
	ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(texture)), ImVec2(this->frame_.cols, this->frame_.rows));
	ImGui::End();
}