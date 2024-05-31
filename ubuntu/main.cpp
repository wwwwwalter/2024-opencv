#include <opencv2/opencv.hpp>  
#include <iostream>  
#include <string>  

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
    // 1. ��ʼ��OpenCV  
    cv::namedWindow("Camera Feed", cv::WINDOW_AUTOSIZE);

    // 2. ����һ��VideoCapture���󣬲���0ͨ����ʾĬ�����  
    cv::VideoCapture cap(0,cv::CAP_V4L2);

    // �������Ƿ�ɹ���  
    if (!cap.isOpened()) {
        std::cerr << "Error opening video capture" << std::endl;
        return -1;
    }

    // �趨����ֱ��ʣ����磺640x480��  

    int fps = 30;
    //int width = 640;
    //int height = 480;

    int width = 1920;
    int height = 1080;
    cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    //cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('Y', 'U', 'Y', 'V'));
    cap.set(cv::CAP_PROP_FPS, fps);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    //cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('H', '2', '6', '4'));

    std::cout << "fps:" << cap.get(cv::CAP_PROP_FPS) << std::endl;
    std::cout << "width:" << cap.get(cv::CAP_PROP_FRAME_WIDTH) << std::endl;
    std::cout << "height:" << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
    std::cout << "fourcc:" << fourccToString(cap.get(cv::CAP_PROP_FOURCC)) << std::endl;
    // 3. ��ȡ����ʾ֡  
    cv::Mat frame;
    while (true) {
        // ��ȡһ֡  
        bool success = cap.read(frame);

        // ���֡�Ƿ�ɹ���ȡ  
        if (!success) {
            std::cerr << "Unable to read frame" << std::endl;
            break;
        }

        // ��ʾ֡  
        cv::imshow("Camera Feed", frame);

        // �ȴ��������������'q'�����˳�ѭ��  
        if (cv::waitKey(1) && 0xFF == 'q') {
            break;
        }
    }

    // 4. �ͷ�VideoCapture����  
    cap.release();

    // ���ٴ���  
    cv::destroyAllWindows();

    return 0;
}