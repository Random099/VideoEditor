#include "Parameter.h"

Parameter::Parameter() : type_(PType::none) {}

Parameter::Parameter(PType type, cv::Size size) : type_(type), size_(size) {}

Parameter::~Parameter()
{
}

PType Parameter::getType() const
{
	return this->type_;
}

void Parameter::increaseSize(int step)
{
	this->size_.width += step;
	this->size_.height += step;
}

void Parameter::decreaseSize(int step)
{
	this->size_.width -= step;
	this->size_.height -= step;
}

cv::Size Parameter::getSize() const
{
	return this->size_;
}