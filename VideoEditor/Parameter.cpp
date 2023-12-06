#include "Parameter.h"

Parameter::Parameter() : type_(Param::Type::none) {}

Parameter::Parameter(Param::Type type, cv::Size size) : type_{ type }, size_{ size } {}

Parameter::~Parameter()
{
}

Param::Type Parameter::typeGet() const
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

