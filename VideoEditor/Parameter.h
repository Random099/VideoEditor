#pragma once
//opencv
#include <opencv2/core.hpp>
//std
#include <string>
#include <map>



namespace Param {
	enum class Type {
		none = 0,
		blur = 1
	};
	const std::map<std::string, Type> map = {
		{"none", Type::none},
		{"blur", Type::blur}
	};
}

class Parameter
{
public:
	Parameter();
	Parameter(Param::Type, cv::Size);
	~Parameter();
	Param::Type typeGet() const;
	cv::Size sizeGet() const;
	void sizeIncrease(int);
	void sizeDecrease(int);
private:
	Param::Type type_;
	cv::Size size_;
};

