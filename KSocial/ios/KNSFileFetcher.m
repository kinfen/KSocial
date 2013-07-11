//
//  KNSFileFetcher.m
//  KSocial
//
//  Created by kinfen on 13-7-8.
//  Copyright (c) 2013年 KStudio. All rights reserved.
//

#import "KNSFileFetcher.h"

@implementation KNSFileFetcher
- (void) fetchImageWithUrl:(NSString *)url subFolderInCache:(NSString*)folder andCompletionBlock:( void(^)(const char* imagePath, const char* error))block
{
    NSURLRequest *request = [NSURLRequest requestWithURL:[NSURL URLWithString:url]];
    
    NSHTTPURLResponse *response  =nil;
    NSError *error = nil;
    NSData *imageData = [NSURLConnection sendSynchronousRequest:request returningResponse:&response error:&error];
    
    if (error || response.statusCode != 200 || !imageData || imageData.length == 0)
    {
        block(NULL, error == nil ? "fetch file error" : error.localizedDescription.UTF8String);
    }
    else
    {
        
        NSString* urlPath = [response.URL.URLByDeletingLastPathComponent.absoluteString stringByReplacingOccurrencesOfString:@"/" withString:@"_"];
        urlPath = [urlPath stringByReplacingOccurrencesOfString:@":" withString:@"_"];
        urlPath = [urlPath stringByReplacingOccurrencesOfString:@"." withString:@"_"];
        NSString* filePath = [NSString stringWithFormat:@"~/%@",(folder == nil ? @"" : folder)];
        filePath = [filePath stringByExpandingTildeInPath];
        
        
        NSFileManager* fileManager = [NSFileManager defaultManager];
        if (![fileManager fileExistsAtPath:filePath])
        {
            NSError* error = nil;
            if (![fileManager createDirectoryAtPath:filePath withIntermediateDirectories:YES attributes:nil error:&error])
            {
                block(nil, error.userInfo.description.UTF8String);
                return;
            }
            
        }
        filePath = [filePath stringByAppendingPathComponent:response.URL.lastPathComponent];
        if (![fileManager fileExistsAtPath:filePath])
        {
            if ([fileManager createFileAtPath:filePath contents:imageData attributes:nil])
            {
                block(filePath.UTF8String, nil);
            }
            else
            {
                block(nil, "can not create file");
            }
        }
        else
        {
            block(filePath.UTF8String, nil);
        }

        
    }
}
@end
