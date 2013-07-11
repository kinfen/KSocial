//
//  KNSSocialManager.m
//  KSocial
//
//  Created by kinfen on 13-7-7.
//  Copyright (c) 2013年 KStudio. All rights reserved.
//

#import "KNSSocialManager.h"

@implementation KNSSocialManager
+(id)sharedInstance
{
    static KNSSocialManager* g_instance = nil;
    if(g_instance == nil)
    {
        g_instance = [[KNSSocialManager alloc] init];
    }
    return g_instance;
}
-(void)dealloc
{
    self.session = nil;
}
@end
