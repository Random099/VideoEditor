#include "Parameter.h"

Parameter::Parameter() : type_(PType::none) {}

Parameter::Parameter(PType type, cv::Size size) : type_(type), size_(size) {}

Parameter::~Parameter()
{
}

PType Parameter::typeGet() const
{
	return this->type_;
}

void Parameter::sizeIncrease(int step)
{
	this->size_.width += step;
	this->size_.height += step;
}

void Parameter::sizeDecrease(int step)
{
	this->size_.width -= step;
	this->size_.height -= step;
}

cv::Size Parameter::sizeGet() const
{
	return this->size_;
}

