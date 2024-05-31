#include <opencv2/opencv.hpp>  
#include <iostream>  

int main() {
    // 读取图像  
    cv::Mat image = cv::imread("stack.jpg", cv::IMREAD_COLOR); // 替换 "path_to_your_image.jpg" 为你的图片路径  

    // 检查图像是否成功加载  
    if (image.empty()) {
        std::cerr << "无法加载图像" << std::endl;
        return -1;
    }

    // 创建一个窗口来显示图像  
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);

    // 在窗口中显示图像  
    cv::imshow("Display Image", image);

    // 等待用户按键，然后关闭窗口  
    cv::waitKey(0);

    return 0;
}