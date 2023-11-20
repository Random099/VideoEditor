#pragma once
#include <opencv2/core.hpp>
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
	PType getType() const;
	cv::Size getSize() const;
	void increaseSize(int);
	void decreaseSize(int);
private:
	PType type_;
	cv::Size size_;
};
