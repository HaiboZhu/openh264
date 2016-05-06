/*!
 * \copy
 *     Copyright (c)  2013, Cisco Systems
 *     All rights reserved.
 *
 *     Redistribution and use in source and binary forms, with or without
 *     modification, are permitted provided that the following conditions
 *     are met:
 *
 *        * Redistributions of source code must retain the above copyright
 *          notice, this list of conditions and the following disclaimer.
 *
 *        * Redistributions in binary form must reproduce the above copyright
 *          notice, this list of conditions and the following disclaimer in
 *          the documentation and/or other materials provided with the
 *          distribution.
 *
 *     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *     "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *     LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *     FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *     COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *     INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *     BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *     CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *     LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *     ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *     POSSIBILITY OF SUCH DAMAGE.
 *
 */

extern int EncMain(int argc, char **argv);

#import "ViewController.h"


@interface ViewController ()

@end

@implementation ViewController
@synthesize statusText=statusText_;

- (void)viewDidLoad
{
    [super viewDidLoad];
    statusText_.text = @"Status: Ready for Go";
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (IBAction) buttonPressed:(id)sender
{
    NSBundle * bundle = [NSBundle mainBundle];
    NSString * encCfg0 = [bundle pathForResource:@"welsenc_ios0" ofType:@"cfg"];
    NSString * encCfg1 = [bundle pathForResource:@"welsenc_ios1" ofType:@"cfg"];
    NSString * dlayerCfg0 = [bundle pathForResource:@"layer20" ofType:@"cfg"];
    NSString * dlayerCfg1 = [bundle pathForResource:@"layer21" ofType:@"cfg"];
    NSString * yuvFile0 = [bundle pathForResource:@"iphone5A1429_sitting_1280x720" ofType:@"yuv"];
    NSString * yuvFile1 = [bundle pathForResource:@"iphone5A1429_sitting_1280x720_2" ofType:@"yuv"];
    NSString * bsfile0 = [NSString stringWithFormat:@"%@/%@", [self getPathForWrite], @"test0.264"];
    NSString * bsfile1 = [NSString stringWithFormat:@"%@/%@", [self getPathForWrite], @"test1.264"];
    NSLog(@"WELS_INFO: enc config file: %@, yuv file %@", encCfg0, yuvFile0);
    NSLog(@"WELS_INFO: enc config file: %@, yuv file %@", encCfg1, yuvFile1);
    const char * argv[] = {
        [encCfg0 UTF8String],
        [encCfg1 UTF8String],
        [yuvFile0 UTF8String],
        [yuvFile1 UTF8String],
        [bsfile0 UTF8String],
        [bsfile1 UTF8String],
        [dlayerCfg0 UTF8String],
        [dlayerCfg1 UTF8String]
    };
    //SLog(@"WELS_INFO: enc config file: %@", encCfg0);
    EncMain(sizeof(argv)/sizeof(argv[0]), (char**)&argv[0]);
    statusText_.text = @"Status: Test Over";
}

- (NSString*) getPathForWrite {
    NSArray * pathes =  NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString * documentDirectory = [pathes objectAtIndex:0];
    return documentDirectory;
}


@end
