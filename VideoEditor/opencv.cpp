#include "opencv.hpp"
#include "VideoEditor.h"

using namespace cv;
int main(int argc, char* argv[])
{   
    VideoEditor editor;
    editor.appendVideo(Video{ 0 });
    editor.getVideo(0).addParameter(new Parameter{ PType::blur, Size(17, 17) });
    for(;;){
        imshow("Video Editor", editor.getVideo(0).getOutFrame());
        if (waitKey(1000.0 / editor.getVideo(0).getFPS()) >= 0) break;
    }

    /*
    VideoCapture cap(0);
    const double FPS = cap.get(CAP_PROP_FPS);
    VideoWriter video("outcpp.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), FPS, Size(640, 480));
    if (!cap.isOpened()) return -1;
    Mat frame, edges;
    Mat src = imread("wichu.png", IMREAD_COLOR);
    namedWindow("edges", WINDOW_NORMAL);

    int blurSize = 17;
    int param;
    for (;;)
    {
        cap >> frame;
        //cvtColor(frame, frame, COLOR_BGR2GRAY);
        param = waitKey(0);
        if (param == 97)
            blurSize -= 2;
        if (param == 98)
            blurSize += 2;
        blur(frame, frame, Size(blurSize, blurSize));
        Mat frameTemp1 = frame(Rect(0, 0, frame.cols / 2, frame.rows)).clone();
        Mat frameTemp2 = frame(Rect(frame.cols / 2, 0, frame.cols / 2, frame.rows)).clone();
        hconcat(frameTemp2, frameTemp1, frame);
        resize(src, src, frame.size(), 0.0, 0.0, INTER_LINEAR);
        addWeighted(frame, constants::ALPHA, src, 1 - constants::ALPHA, 0.0, frame);
        //Canny(frame, edges, 0, 30, 3);
        imshow("edges", frame);
        video.write(frame);
        if (waitKey(1000.0 / FPS) >= 0) break;
    }
    */
    return 0;
}