#include "VideoEditor.h"

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <thread>

namespace constants {
	constexpr double ALPHA = 0.9;
}