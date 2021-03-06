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

#include "xf_integral_image_config.h"

// Declaration of top function

int main(int argc, char** argv)
{
	cv::Mat in_img, in_img1, out_img, ocv_ref, ocv_ref1;
	cv::Mat in_gray, in_gray1, diff;

	if(argc != 2)
	{
		fprintf(stderr, "Usage: <executable> <input image>\n");
		return -1;
	}	

	// Read input image
	in_img = cv::imread(argv[1], 1);
	if (in_img.data == NULL)
	{
		//cout << "Can't open image !!" << endl;
		return -1;
	}

	cvtColor(in_img,in_gray,CV_BGR2GRAY);
	imwrite("input.jpg", in_gray);

	// create memory for output images
	ocv_ref.create(in_gray.rows,in_gray.cols,CV_32S);
	ocv_ref1.create(in_gray.rows,in_gray.cols,CV_32S);

	cv::integral(in_gray, ocv_ref, -1);

	for(int i = 0; i < in_gray.rows; i++)
	{
		for(int j=0; j<in_gray.cols; j++)
		{
			ocv_ref1.at<unsigned int>(i,j) =  ocv_ref.at<unsigned int>(i+1, j+1);
		}
	}

	imwrite("out_ocv.png",ocv_ref1);


	// create memory for output image
	out_img.create(in_gray.rows,in_gray.cols,CV_32S); 

	// image height and width
	uint16_t height = in_gray.rows;
	uint16_t width = in_gray.cols;

	xF::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> imgInput(in_gray.rows,in_gray.cols);
	xF::Mat<XF_32UC1, HEIGHT, WIDTH, XF_NPPC1> imgOutput(in_gray.rows,in_gray.cols);

	imgInput.copyTo(in_gray.data);

	#if __SDSCC__
	TIME_STAMP_INIT
	#endif
	xFIntegralImage<XF_8UC1,XF_32UC1,HEIGHT, WIDTH,XF_NPPC1>(imgInput, imgOutput);
	#if __SDSCC__
	TIME_STAMP
	#endif


	out_img.data = (unsigned char*) imgOutput.copyFrom();

	imwrite("out_hls.jpg", out_img);
	// Compute absolute difference image
	absdiff(ocv_ref1, out_img, diff);
	// Save the difference image 
	imwrite("diff.png", diff); 

	// Find minimum and maximum differences.
	double minval = 256, maxval = 0;
	int cnt = 0;
	for (int i = 0; i < in_img.rows; i++)
	{
		for(int j = 0; j < in_img.cols; j++)
		{
			uchar v = diff.at<uchar>(i,j);
			if (v>1)
				cnt++;
			if (minval > v )
				minval = v;
			if (maxval < v)
				maxval = v;
		}
	}

	float err_per = 100.0*(float)cnt/(in_img.rows * in_img.cols);
	fprintf(stderr,"Minimum error in intensity = %f\n"
			"Maximum error in intensity = %f\n"
			"Percentage of pixels above error threshold = %f\n",
			minval, maxval, err_per);
	if(err_per > 0.0f)
		return 1;
	return 0;
}
