#include <opencv2/opencv.hpp>  
#include <iostream>  
#include <string>  

std::string fourccToString(int fourcc) {
    char arr[5];
    arr[0] = (fourcc >> 24) & 0xFF;
    arr[1] = (fourcc >> 16) & 0xFF;
    arr[2] = (fourcc >> 8) & 0xFF;
    arr[3] = fourcc & 0xFF;
    arr[4] = '\0'; // Null terminator for C string  

    printf("%d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);
    return std::string(arr);
}

int main(int argc, char** argv) {
    // 1. 初始化OpenCV  
    cv::namedWindow("Camera Feed", cv::WINDOW_AUTOSIZE);

    // 2. 创建一个VideoCapture对象，参数0通常表示默认相机  
    cv::VideoCapture cap(0);

    // 检查相机是否成功打开  
    if (!cap.isOpened()) {
        std::cerr << "Error opening video capture" << std::endl;
        return -1;
    }

    // 设定相机分辨率（例如：640x480）  

    int fps = 30;
    //int width = 640;
    //int height = 480;

    int width = 1920;
    int height = 1080;
    //cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    //cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('H', '2', '6', '4'));
    //cap.set(cv::CAP_PROP_FPS, fps);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    //cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('H', '2', '6', '4'));

    std::cout << "fps:" << cap.get(cv::CAP_PROP_FPS) << std::endl;
    std::cout << "width:" << cap.get(cv::CAP_PROP_FRAME_WIDTH) << std::endl;
    std::cout << "height:" << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
    std::cout << "fourcc:" << fourccToString(cap.get(cv::CAP_PROP_FOURCC)) << std::endl;
    // 3. 读取并显示帧  
    cv::Mat frame;
    while (true) {
        // 读取一帧  
        bool success = cap.read(frame);

        // 检查帧是否成功读取  
        if (!success) {
            std::cerr << "Unable to read frame" << std::endl;
            break;
        }

        // 显示帧  
        cv::imshow("Camera Feed", frame);

        // 等待按键，如果按下'q'键则退出循环  
        if (cv::waitKey(1) && 0xFF == 'q') {
            break;
        }
    }

    // 4. 释放VideoCapture对象  
    cap.release();

    // 销毁窗口  
    cv::destroyAllWindows();

    return 0;
}