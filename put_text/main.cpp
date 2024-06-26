#include <iostream>
#include <chrono>  
#include <time.h>
#include "CvxFont.h"
using namespace cvx;
using namespace std;

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


int main(int argc, char* argv[])
{

    cvx::CvxFont font("Noto.ttf");

    //cv::Mat img(800, 800, CV_8UC3, cv::Scalar(0, 0, 0)); // create a black background
    //cv::Mat img = cv::imread("stack.jpg");
    //cv::String msg6 = "这段代码首先初始化FreeType库，然后加载宋体字体文件，并设置字体大小。接着，它遍历文本字符串，使用FreeType库将每个字符渲染到位图上。之后，代码读取一个背景图像，并将渲染好的文字位图叠加到背景图像的指定位置。最后，显示图像，并在程序结束时释放资源。";
    








    cv::VideoCapture cap(0, cv::CAP_DSHOW);//windows


    if (!cap.isOpened()) {
        std::cerr << "Error opening video capture" << std::endl;
        return -1;
    }


    int fps = 30;
    //int width = 640;
    //int height = 480;

    int width = 1920;
    int height = 1080;
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

    cv::String msg = "这段代码首先初始化FreeType库，然后加载宋体字体文件，并设置字体大小。";

    while (true) {

        bool success = cap.read(frame);
        if (!success) {
            std::cerr << "Unable to read frame" << std::endl;
            break;
        }
        frame_count++;



        auto start_in = std::chrono::high_resolution_clock::now();
        putText(frame, msg, cv::Point(100, 100), font, 30, cv::Scalar(255, 255, 255));
        auto end_in = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_in - start_in); 
        std::cout << ms.count() << "ms\n";


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







void func() {
    auto start = std::chrono::high_resolution_clock::now();
    // ... 执行一些操作 ...  

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // 输出毫秒数  
    std::cout << ms.count() << "ms\n";
}

