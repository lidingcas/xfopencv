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

#ifndef _XF_HOG_DESCRIPTOR_CONFIG_H_
#define _XF_HOG_DESCRIPTOR_CONFIG_H_

#include "hls_stream.h"
#include "xf_headers.h"
#include "common/xf_common.h"
#include "common/xf_utility.h"
#include "imgproc/xf_hog_descriptor.hpp"
#include "xf_config_params.h"

#define 	XF_HEIGHT 		1080
#define 	XF_WIDTH  		1920

/* set the various hog parameters */
#define		XF_WIN_STRIDE		8
#define 	XF_BLOCK_HEIGHT	    16
#define 	XF_BLOCK_WIDTH   	16
#define 	XF_CELL_HEIGHT		8
#define 	XF_CELL_WIDTH		8
#define 	XF_NO_OF_BINS   	9

#define 	OUT_T1		ap_uint16_t

#endif  // end of _AU_HOG_CONFIG_H_
