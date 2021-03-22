#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    //读取原始图像
    string im_path = "../data/apple.jpeg";
    Mat in_image = imread(im_path, IMREAD_UNCHANGED);

    if (in_image.empty()) {
        //检查是否读取图像
        cout << "Error! Input image cannot be read...\n";
        return -1;
    }

    //创建两个具有图像名称的窗口
    namedWindow("Input", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);

    //在之前创建的窗口中显示图片
    imshow("Input", in_image);

    Mat out_image;
    cvtColor(in_image, out_image, COLOR_BGR2GRAY);
    imshow("Output", out_image);
    imwrite("../data/output.jpeg", out_image);

    cout << "Press any key to exit...\n";
    waitKey(0); // Wait for key press
    return 0;
}

