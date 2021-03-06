//=====================================================================
// Copyright 2016 (c), Advanced Micro Devices, Inc. All rights reserved.
//=====================================================================
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef _CMDLINE_H_
#define _CMDLINE_H_

#include <windows.h>
#include <string>
#include <tchar.h>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include "Compressonator.h"
#include "GPU_Decode\GPU_Decode.h"

#include "MIPS.h"

class CCmdLineParamaters
{
public:
    // Set defaults
    CCmdLineParamaters()
    {
        SetDefault();
    };

    void SetDefault()
    {
        SourceFile              = "";
        DestFile                = "";
        DecompressFile          = "";
        use_WIC                 = false;
        use_OCV                 = false;
        use_WIC_out             = false;
        use_OCV_out             = false;
        use_noMipMaps           = false;
        dwWidth                 = 0;
        dwHeight                = 0;
        nMinSize                = 0;
        MipsLevel               = 1;
        silent                  = false;
        noswizzle               = false;
        doswizzle               = false;
        doDecompress            = false;
        BlockWidth              = 4;
        BlockHeight             = 4;
        BlockDepth              = 1;
        conversion_fDuration    = 0;
        memset(&CompressOptions, 0, sizeof(CompressOptions));
        CompressOptions.dwSize              = sizeof(CompressOptions);
        CompressOptions.nCompressionSpeed   = (CMP_Speed)CMP_Speed_Normal;
        CompressOptions.dwnumThreads        = 8;
        CompressOptions.fquality            = AMD_CODEC_QUALITY_DEFAULT;     // This default value is also ref by code in SDK Compress.cpp 
        CompressOptions.dwmodeMask          = 0xCF;     // If you reset this default: seach for comments with dwmodeMask and change the values also
        DestFormat                          = CMP_FORMAT_Unknown;
        SourceFormat                        = CMP_FORMAT_Unknown;
    }

public:
    
    std::string                 SourceFile;             //
    std::string                 DestFile;               //
    std::string                 DiffFile;                // Diff image file name
    std::string                 DecompressFile;         //
    CMP_FORMAT               SourceFormat;           //
    CMP_FORMAT               DestFormat;             //
    CMP_CompressOptions      CompressOptions;        //
    DWORD                       dwWidth;                //
    DWORD                       dwHeight;               //
    double                      conversion_fDuration;   // Total Performance time
    int                         MipsLevel;              //
    int                         nMinSize;               //
    bool                        doDecompress;           //
    bool                        noswizzle;              //
    bool                        doswizzle;              //
    bool                        silent;                 //
    bool                        analysis;               // run alaysis
    bool                        showperformance;        //
    bool                        noprogressinfo;         //
    bool                        use_noMipMaps;          //  use of image loads based on Open CV Components in place of raw image plugins for write to file
    bool                        use_WIC;                //  use of image loads based on Windows Imagaing Components in place of raw image plugins for read from file
    bool                        use_OCV;                //  use of image loads based on Open CV Components in place of raw image plugins  for read from file
    bool                        use_WIC_out;            //  use of image loads based on Windows Imagaing Components in place of raw image plugins  for write to file
    bool                        use_OCV_out;            //  use of image loads based on Open CV Components in place of raw image plugins for write to file
    int                         BlockWidth;             // Width (xdim) in pixels of the Compression Block that is to be processed default for ASTC is 4 
    int                         BlockHeight;            // Height (ydim)in pixels of the Compression Block that is to be processed default for ASTC is 4
    int                         BlockDepth;             // Depth  (zdim)in pixels of the Compression Block that is to be processed default for ASTC is 1
    bool                        useGPU;                 // Reserved Feature: Enable GPU Compression, default is false which uses CPU
};


extern void PrintInfo(const char* Format, ... );
extern void PrintUsage();
extern bool ParseParams(int argc, CMP_CHAR* argv[]);
extern int  ProcessCMDLine(CMP_Feedback_Proc pFeedbackProc, MipSet *userMips);
extern      CCmdLineParamaters g_CmdPrams;
extern int  GetNumberOfCores(wchar_t *envp[ ]);
extern bool SouceAndDestCompatible(CCmdLineParamaters g_CmdPrams);
extern void SwizzleMipMap(MipSet *pMipSet);
extern bool KeepSwizzle(CMP_FORMAT destformat);

extern int  DecompressCMDLine(CMP_Feedback_Proc pFeedbackProc, MipSet *userMips);

#endif