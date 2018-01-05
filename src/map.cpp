/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2016  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "myslam/map.h"

namespace myslam
{
/*
Map::Map():global_map_(nullptr), resolution_(0.04)
{
    
}*/

void Map::insertKeyFrame ( Frame::Ptr frame )
{
    cout<<"Key frame size = "<<keyframes_.size()<<endl;
    if ( keyframes_.find(frame->id_) == keyframes_.end() )
    {
        keyframes_.insert( make_pair(frame->id_, frame) );
    }
    else
    {
        keyframes_[ frame->id_ ] = frame;
    }
}

void Map::insertMapPoint ( MapPoint::Ptr map_point )
{
    if ( map_points_.find(map_point->id_) == map_points_.end() )
    {
        map_points_.insert( make_pair(map_point->id_, map_point) );
    }
    else 
    {
        map_points_[map_point->id_] = map_point;
    }
}

void Map::updateGlobalMap( Frame::Ptr frame )
{
    //global_map_ = boost::make_shared< pcl::PointCloud<pcl::PointXYZRGB> >( );
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr tmp(new pcl::PointCloud<pcl::PointXYZRGB> );
    //pcl::transformPointCloud( *(frame->point_cloud_), *tmp, frame->T_c_w_.inverse().matrix() );
    tmp->is_dense = false;
    *global_map_ += *tmp;
    voxel_.setLeafSize( resolution_, resolution_, resolution_);
    voxel_.setInputCloud( global_map_ );
    voxel_.filter( *tmp );
    global_map_->swap( *tmp );
   // viewer_.showCloud( global_map_ );
    
}

}
