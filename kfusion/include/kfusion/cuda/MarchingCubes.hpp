#pragma once
#ifndef MARCHING_CUBES_H_H
#define MARCHING_CUBES_H_H
#include <kfusion/cuda/device_memory.hpp>
#include <kfusion/types.hpp>

namespace kfusion
{
	namespace cuda
	{
		class TsdfVolume;
		class KF_EXPORTS MarchingCubes
		{
		public:
			MarchingCubes(void);
			~MarchingCubes(void);
		public:
			enum
			{ 
				POINTS_PER_TRIANGLE = 3,
				DEFAULT_TRIANGLES_BUFFER_SIZE = 2 * 1000 * 1000 * POINTS_PER_TRIANGLE      
			};
			typedef cv::Ptr<MarchingCubes> MarchingCubes_Ptr; //÷«ƒ‹÷∏’Î
			typedef kfusion::Point Point;
		public:
			DeviceArray<Point> run(const TsdfVolume& tsdf, DeviceArray<Point>& triangles_buffer);
		private:
			DeviceArray<int> edgeTable_;
			DeviceArray<int> numVertsTable_;
			DeviceArray<int> triTable_;
			DeviceArray2D<int> occupied_voxels_buffer_;
		};
	}
}


#endif