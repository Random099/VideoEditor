#include "opencv.hpp"

using namespace cv;

int main(int argc, char* argv[])
{   
    VideoEditor editor;
    
    editor.windowCreate("First", 0);
    editor.controlPanelCreate(ControlPanel::defaultName);
    editor.windowCreate("Second", "doanel.mp4");
    for (;;);
    editor.windowDestroy("First");
    editor.windowDestroy("Second");
    editor.controlPanelDestroy(ControlPanel::defaultName);

    /*
    char c;
    for(;;){
        std::cin >> c;
        if (c == 'c') {
            editor.controlPanelCreate(ControlPanel::defaultName);
        }
        if (c == 'w') {
			editor.windowCreate("First", 0);
		}
        if (c == 'y') {
            editor.controlPanelDestroy(ControlPanel::defaultName);
        }
        if (c == 'x') {
            editor.windowDestroy("First");
        }
    }
    */
    //editor.windowDestroy("First");
    //editor.controlPanelDestroy(ControlPanel::defaultName);
    //editor.getVideo("First")->addParameter(std::shared_ptr<Parameter>(new Parameter{PType::blur, Size(17, 17)}));
    
    /*
    for(;;){
        imshow("First", editor.getVideo("First")->getOutFrame());
        imshow("Second", editor.getVideo("Second")->getOutFrame());
        //waitKey(0);
        if (waitKey(1000.0 / editor.getVideo("First")->getFPS()) >= 0) break;
    }
    */
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