#include <opencv2/opencv.hpp>  
#include <iostream>  
#include <string>  
#include <chrono>  


std::string fourccToString(int fourcc) {
    char arr[5];
    arr[3] = (fourcc >> 24) & 0xFF;
    arr[2] = (fourcc >> 16) & 0xFF;
    arr[1] = (fourcc >> 8) & 0xFF;
    arr[0] = fourcc & 0xFF;
    arr[4] = '\0'; // Null terminator for C string  

    printf("%d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);
    return std::string(arr);
}

int main(int argc, char** argv) {

    cv::namedWindow("Camera Feed", cv::WINDOW_AUTOSIZE);


    //v::VideoCapture cap(0);//default,can't set fourcc
    //cv::VideoCapture cap(0,cv::CAP_V4L2);//linux
    cv::VideoCapture cap(0,cv::CAP_DSHOW);//windows


    if (!cap.isOpened()) {
        std::cerr << "Error opening video capture" << std::endl;
        return -1;
    }

  


    int fps = 30;
    int width = 640;
    int height = 480;

    //int width = 1920;
    //int height = 1080;
    cap.set(cv::CAP_PROP_FPS, fps);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    //cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('Y', 'U', 'Y', 'V'));


    std::cout << "fps:" << cap.get(cv::CAP_PROP_FPS) << std::endl;
    std::cout << "width:" << cap.get(cv::CAP_PROP_FRAME_WIDTH) << std::endl;
    std::cout << "height:" << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
    std::cout << "fourcc:" << fourccToString(cap.get(cv::CAP_PROP_FOURCC)) << std::endl;

    cv::Mat frame;
    int frame_count = 0;
    auto start = std::chrono::high_resolution_clock::now();

    while (true) {

        bool success = cap.read(frame);
        frame_count++;


        if (!success) {
            std::cerr << "Unable to read frame" << std::endl;
            break;
        }


        cv::imshow("Camera Feed", frame);


        if (cv::waitKey(1) && 0xFF == 'q') {
            break;
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::seconds second = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        if (second.count() >= 20) {
            printf("FPS:%d\n", frame_count / second.count());
            break;
        }

    }

    


    cap.release();
    cv::destroyAllWindows();

    return 0;
}