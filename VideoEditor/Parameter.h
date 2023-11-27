#pragma once
//opencv
#include <opencv2/core.hpp>
//std
#include <string>

enum class PType {
	none = 0,
	blur = 1
};

class Parameter
{
public:
	Parameter();
	Parameter(PType, cv::Size);
	~Parameter();
	PType typeGet() const;
	cv::Size sizeGet() const;
	void sizeIncrease(int);
	void sizeDecrease(int);
private:
	PType type_;
	cv::Size size_;
};

