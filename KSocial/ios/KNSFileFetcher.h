//
//  KNSFileFetcher.h
//  KSocial
//
//  Created by kinfen on 13-7-8.
//  Copyright (c) 2013年 KStudio. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface KNSFileFetcher : NSObject
- (void) fetchImageWithUrl:(NSString *)url subFolderInCache:(NSString*)folder andCompletionBlock:( void(^)(const char* imagePath, const char* error))block;
@end
