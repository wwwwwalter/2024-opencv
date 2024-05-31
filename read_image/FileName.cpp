#include <opencv2/opencv.hpp>  
#include <iostream>  

int main() {
    // ��ȡͼ��  
    cv::Mat image = cv::imread("stack.jpg", cv::IMREAD_COLOR); // �滻 "path_to_your_image.jpg" Ϊ���ͼƬ·��  

    // ���ͼ���Ƿ�ɹ�����  
    if (image.empty()) {
        std::cerr << "�޷�����ͼ��" << std::endl;
        return -1;
    }

    // ����һ����������ʾͼ��  
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);

    // �ڴ�������ʾͼ��  
    cv::imshow("Display Image", image);

    // �ȴ��û�������Ȼ��رմ���  
    cv::waitKey(0);

    return 0;
}