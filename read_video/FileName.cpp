#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
    VideoCapture capture("60.mp4");

    // �����Ƶ�Ƿ�ɹ���
    if (!capture.isOpened()) {
        printf("�޷���ȡ��Ƶ�ļ�\n");
        return -1;
    }

    double frameCount = capture.get(CAP_PROP_FRAME_COUNT); // ��ȡ��Ƶ֡��
    double fps = capture.get(CAP_PROP_FPS); // ��ȡ֡��
    int delay = int(1000 / fps); // ����֡�ʼ���֡����ʱ��

    std::cout << "frameCount:"<< frameCount << std::endl;
    std::cout << "fps" << fps << std::endl;
    std::cout << "delay:" << delay << std::endl;

    while (true) {
        Mat frame;
        bool success = capture.read(frame); // ��ȡһ֡����

        // ����Ƿ�ɹ���ȡ֡
        if (!success) {
            printf("�޷���ȡ��Ƶ֡\n");
            break;
        }

        imshow("��Ƶ����", frame);
        if (waitKey(delay) == 27) // ͨ������ESC���˳�ѭ��
            break;
    }

    capture.release(); // �ͷ���Ƶ����
    destroyAllWindows(); // �ر�����OpenCV����
    return 0;
}