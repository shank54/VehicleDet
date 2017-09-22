#include "com_example_mypc_vehicledet_OpencvClass.h"

JNIEXPORT void JNICALL Java_com_example_mypc_vehicledet_OpencvClass_vehicleDetection
  (JNIEnv *, jclass, jlong addrRgba){
    Mat& frame = *(Mat*)addrRgba;

    detect(frame);


}
void detect(Mat& frame){
    String car_cascade_name = "/storage/emulated/0/data/cars.xml";


    CascadeClassifier  car_cascade;

    if( !car_cascade.load( car_cascade_name ) ){ printf("--(!)Error loading\n"); return; };

    std::vector<Rect> car;

    Mat frame_gray;

    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect cars
    car_cascade.detectMultiScale( frame_gray, car, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );


    for( size_t i = 0; i < car.size(); i++ )
    {
        Point center( car[i].x + car[i].width*0.5, car[i].y + car[i].height*0.5 );
        ellipse( frame, center, Size( car[i].width*0.5, car[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 0 ), 4, 8, 0 );
    }


}

