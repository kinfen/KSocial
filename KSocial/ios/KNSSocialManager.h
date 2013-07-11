//
//  KNSSocialManager.h
//  KSocial
//
//  Created by kinfen on 13-7-7.
//  Copyright (c) 2013年 KStudio. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FacebookSDK/FacebookSDK.h>
@interface KNSSocialManager : NSObject
+(id) sharedInstance;
@property (nonatomic, strong) FBSession*            session;
@end
