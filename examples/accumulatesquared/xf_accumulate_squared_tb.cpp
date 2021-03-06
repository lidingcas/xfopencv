/***************************************************************************
Copyright (c) 2016, Xilinx, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation 
and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors 
may be used to endorse or promote products derived from this software 
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

***************************************************************************/

#include "xf_accumulate_squared_config.h"


int main(int argc, char** argv)
{
	if (argc != 3)
	{
		fprintf(stderr,"Invalid Number of Arguments!\nUsage:\n");
		fprintf(stderr,"<Executable Name> <input image path1> <input image path2> \n");
		return -1;
	}


	cv::Mat in_img, in_img1, out_img;
	cv::Mat in_gray, in_gray1, diff;

	in_img  = cv::imread(argv[1], 1);  // read image
	in_img1 = cv::imread(argv[2], 1);  // read image

	if (in_img.data == NULL)
	{
		fprintf(stderr,"Cannot open image %s\n",argv[1]);
		return 0;
	}
	if (in_img1.data == NULL)
	{
		fprintf(stderr,"Cannot open image %s\n",argv[2]);
		return 0;
	}

	cvtColor(in_img, in_gray, CV_BGR2GRAY);
	cvtColor(in_img1, in_gray1, CV_BGR2GRAY);

	cv::Mat inout_gray(in_img.rows, in_img.cols, CV_16U, 1);
	cv::Mat   out_gray(in_img.rows, in_img.cols, CV_16U, 1);
	cv::Mat inout_gray1(in_img.rows, in_img.cols, CV_32FC1, 1);

	cv::Mat ocv_ref(in_img.rows, in_img.cols, CV_16U, 1);
	cv::Mat ocv_ref_in1(in_img.rows, in_img.cols, CV_32FC1, 1);
	cv::Mat ocv_ref_in2(in_img.rows, in_img.cols, CV_32FC1, 1);

	in_gray.convertTo(ocv_ref_in1, CV_32FC1);
	in_gray1.convertTo(ocv_ref_in2, CV_32FC1);
	// OpenCV function
	cv::accumulateSquare(ocv_ref_in1, ocv_ref_in2, cv::noArray());

	ocv_ref_in2.convertTo(ocv_ref, CV_16U);

	// write OpenCV reference output
	imwrite("out_ocv.jpg", ocv_ref);

	in_gray1.convertTo(inout_gray, CV_8U);



#if NO
	xF::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> imgInput1(in_gray.rows,in_gray.cols);
	xF::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> imgInput2(inout_gray.rows,inout_gray.cols);

	xF::Mat<XF_16UC1, HEIGHT, WIDTH, XF_NPPC1> imgOutput(in_gray1.rows,in_gray1.cols);

	imgInput1.copyTo(in_gray.data);
	imgInput2.copyTo(inout_gray.data);
	#if __SDSCC__
	TIME_STAMP_INIT
	#endif
	xFaccumulateSquare<XF_8UC1,XF_16UC1, HEIGHT, WIDTH, XF_NPPC1> (imgInput1,imgInput2,imgOutput);
	#if __SDSCC__
	TIME_STAMP
	#endif

	out_gray.data = (unsigned char *)imgOutput.copyFrom();

#endif
#if RO
	xF::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC8> imgInput1(in_gray.rows,in_gray.cols);
	xF::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC8> imgInput2(inout_gray.rows,inout_gray.cols);

	xF::Mat<XF_16UC1, HEIGHT, WIDTH, XF_NPPC8> imgOutput(in_gray1.rows,in_gray1.cols);

	imgInput1.copyTo(in_gray.data);
	imgInput2.copyTo(inout_gray.data);
	#if __SDSCC__
	TIME_STAMP_INIT
	#endif
	xFaccumulateSquare <XF_8UC1,XF_16UC1, HEIGHT, WIDTH, XF_NPPC8> (imgInput1,imgInput2,imgOutput);
	#if __SDSCC__
	TIME_STAMP
	#endif

	out_gray.data = (unsigned char *)imgOutput.copyFrom();

#endif

	// Write the output
	imwrite("out_hls.jpg", out_gray);

	out_gray.convertTo(inout_gray1, CV_32FC1);
	// Compute absolute difference image
	absdiff(ocv_ref_in2, inout_gray1, diff);
	// Save the difference image 
	imwrite("diff.jpg", diff); 

	// Find minimum and maximum differences.
	double minval = 256, maxval = 0;
	int cnt = 0;
	for (int i=0; i < in_img.rows; i++)
	{
		for(int j = 0; j<in_img.cols; j++)
		{
			float v = diff.at<float>(i,j);
			if (v > 0.0f) cnt++;
			if (minval > v ) minval = v;
			if (maxval < v)  maxval = v;
		}
	}
	float err_per = 100.0 * (float)cnt/(in_img.rows*in_img.cols);

	fprintf(stderr,"Minimum error in intensity = %f\n"
			"Maximum error in intensity = %f\n"
			"Percentage of pixels above error threshold = %f\n",
			minval,maxval,err_per);
	if(err_per > 0.0f) return (int)-1;

	return 0;
}
