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
    cv::waitKey(0);//���޵ȴ���һֱ���������¼���

    //���û���µ�֡����һ֡��һֱ��ʾ�ڴ�����

    //cv::waitKey(3000);
    //while (1) {
    //    std::this_thread::sleep_for(std::chrono::seconds(1));
    //    std::cout << "sleep" << std::endl;
    //}

    return 0;
}