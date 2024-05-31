#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
    VideoCapture capture("60.mp4");

    // 检查视频是否成功打开
    if (!capture.isOpened()) {
        printf("无法读取视频文件\n");
        return -1;
    }

    double frameCount = capture.get(CAP_PROP_FRAME_COUNT); // 获取视频帧数
    double fps = capture.get(CAP_PROP_FPS); // 获取帧率
    int delay = int(1000 / fps); // 根据帧率计算帧间间隔时间

    std::cout << "frameCount:"<< frameCount << std::endl;
    std::cout << "fps" << fps << std::endl;
    std::cout << "delay:" << delay << std::endl;

    while (true) {
        Mat frame;
        bool success = capture.read(frame); // 读取一帧数据

        // 检查是否成功读取帧
        if (!success) {
            printf("无法读取视频帧\n");
            break;
        }

        imshow("视频播放", frame);
        if (waitKey(delay) == 27) // 通过按下ESC键退出循环
            break;
    }

    capture.release(); // 释放视频对象
    destroyAllWindows(); // 关闭所有OpenCV窗口
    return 0;
}