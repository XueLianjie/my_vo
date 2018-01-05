#ifndef RGBDMAP_H
#define RGBDMAP_H

#include<iostream>
#include<pcl/common/transforms.h>
#include<pcl/point_types.h>
#include<pcl/filters/voxel_grid.h>
using namespace std;

class Rgbdmap
{
public:
    typedef pcl::PointXYZRGB PointT;
    typedef pcl::PointCloud<PointT> PointCloud;
    
    Rgbdmap();
    void createPointCloud();


protected:
    PointCloud::Ptr generatePointCloud(KeyFrame* kf, cv::Mat& color, cv::Mat& depth);

    PointCloud::Ptr point_cloud_;
    PointCloud::Ptr global_map_;
    pcl::VoxelGrid<PointT> voxel;
    double resolution = 0.04;

};

#endif 
