#include"rgbdmap.h"
Rgbd::Rgbd()
{}



void Rgbd::generatePointCloud(KeyFrame* kf, cv::Mat& color, cv::Mat& depth)
{
    for ( int v=0; v<color.rows; v++ )
        for ( int u=0; u<color.cols; u++ )
        {
            unsigned int d = depth.ptr<unsigned short> ( v )[u]; // 深度值
            if ( d==0 ) continue; // 为0表示没有测量到
            Eigen::Vector3d point; 
            point[2] = double(d)/camera_->depth_scale_; 
            point[0] = (u-camera_->cx_)*point[2]/camera_->fx_;
            point[1] = (v-camera_->cy_)*point[2]/camera_->fy_; 
            Eigen::Vector3d pointWorld = T_c_w_.inverse() * point;
            
            pcl::PointXYZRGB p ;
            p.x = pointWorld[0];
            p.y = pointWorld[1];
            p.z = pointWorld[2];
            p.b = color.data[ v*color.step+u*color.channels() ];
            p.g = color.data[ v*color.step+u*color.channels()+1 ];
            p.r = color.data[ v*color.step+u*color.channels()+2 ];
            point_cloud_->points.push_back( p );
        }    

}
