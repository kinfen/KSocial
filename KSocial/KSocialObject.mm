//
//  KSocialObject.cpp
//  KSocial
//
//  Created by kinfen on 13-7-7.
//  Copyright (c) 2013年 KStudio. All rights reserved.
//

#include "KSocialObject.h"
#import "ios/KNSSocialManager.h"
#import <FacebookSDK/FacebookSDK.h>
#include "KSocialUser.h"
#include "KNSFileFetcher.h"
using namespace kgk;

#define NSSTRING_TO_UTF8_STRING(STR) (STR == nil ? "" : STR.UTF8String)
#define UTF8STRING_TO_NSSTRING(STR) (STR == NULL ? nil : [NSString stringWithUTF8String:STR])
SHARED_PTR<KSocialObject> KSocialObject::sharedInstance()
{
    static SHARED_PTR<KSocialObject> g_instance;
    if (g_instance.get() == NULL)
    {
        g_instance = SHARED_PTR<KSocialObject>(new KSocialObject());
    }
    return g_instance;
}

KSocialObject::KSocialObject() : m_delegate(NULL)
{
    
}
void KSocialObject::loginWithFacebook()
{
    KNSSocialManager* socialManager = [KNSSocialManager sharedInstance];
    if (!socialManager.session.isOpen)
    {
        socialManager.session = [[FBSession alloc] init];
        [FBSession setActiveSession:socialManager.session];
        if (socialManager.session.state == FBSessionStateCreatedTokenLoaded || socialManager.session.state == FBSessionStateCreated)
        {
            //has or never login before
            openSession();
        }
    }
}
void KSocialObject::logoutWithFacebook()
{
    [((KNSSocialManager*)[KNSSocialManager sharedInstance]).session closeAndClearTokenInformation];
}
bool KSocialObject::isFacebookLogin()
{
    return ((KNSSocialManager*)[KNSSocialManager sharedInstance]).session.isOpen;
}
void KSocialObject::resume()
{
    
    KNSSocialManager* socialManager = [KNSSocialManager sharedInstance];
    if (!socialManager.session.isOpen)
    {
        if (socialManager.session)
        {
            NSLog(@"%@", socialManager.session);
            if (socialManager.session.state != FBSessionStateCreatedOpening)
            {
                [FBAppCall handleDidBecomeActiveWithSession:socialManager.session];
            }
        }
        else
        {
            socialManager.session = [[FBSession alloc] init];
            [FBSession setActiveSession:socialManager.session];
            if (socialManager.session.state == FBSessionStateCreatedTokenLoaded)
            {
                openSession();
            }
            
        }
    }
}
void KSocialObject::close()
{
    [[[KNSSocialManager sharedInstance] session] close];
}

void KSocialObject::openSession()
{
    KNSSocialManager* socialManager = [KNSSocialManager sharedInstance];
    if  (socialManager.session == nil) return;
    
    [socialManager.session openWithCompletionHandler:^(FBSession *session,
                                                       FBSessionState status,
                                                       NSError *error)
     {
         // we recurse here, in order to update buttons and labels
         const char* errMsg = error == nil ? NULL : error.localizedDescription.UTF8String;
         if (this->getDelegate())
         {
             this->getDelegate()->facebookSessionCallback((kFBSessionState)status, errMsg);
         }
     }];

}
void KSocialObject::inviteFriends(const char* mesage, const char* title, std::vector<std::string>* toFriendsID, std::vector<std::string>* suggestFriendsID, K_FB_DIALOG_REQUEST_BLOCK block)
{
    
    NSMutableDictionary* params =   [NSMutableDictionary dictionary];
    
    if (toFriendsID)
    {
        NSMutableArray* array = [NSMutableArray array];
        for (int i = 0; i < toFriendsID->size(); i++)
        {
            [array addObject:[NSString stringWithUTF8String:toFriendsID->at(i).c_str()]];
        }
        [params setObject:[array componentsJoinedByString:@","] forKey:@"to"];
    }
    
    if (suggestFriendsID)
    {
        NSMutableArray* array = [NSMutableArray array];
        for (int i = 0; i < suggestFriendsID->size(); i++)
        {
            [array addObject:[NSString stringWithUTF8String:suggestFriendsID->at(i).c_str()]];
        }
        [params setObject:[array componentsJoinedByString:@","] forKey:@"suggestions"];
    }
    [FBWebDialogs presentRequestsDialogModallyWithSession:[[KNSSocialManager sharedInstance] session]
                                                  message:UTF8STRING_TO_NSSTRING(mesage)
                                                    title:UTF8STRING_TO_NSSTRING(title)
                                               parameters:params
                                                  handler:^(FBWebDialogResult result, NSURL *resultURL, NSError *error)
                                                    {
                                                        block((kFBWebDialogResult)result, resultURL.absoluteString.UTF8String, error.description.UTF8String);
                                                    }];
}
void KSocialObject::like(const char* targetPath, K_FB_LIKE_CALLBACK_BLOCK block)
{
    checkPermission("publish_actions", FBPermissionTypePublish, ^(const char *error)
    {
        if(error)
        {
            block(NULL, error);
        }
        else
        {
            NSMutableDictionary<FBGraphObject> *action = [FBGraphObject graphObject];
            action[@"object"] = UTF8STRING_TO_NSSTRING(targetPath);
            [FBRequestConnection startForPostWithGraphPath:@"me/og.likes"
                                               graphObject:action
                                         completionHandler:^(FBRequestConnection *connection,
                                                             id result,
                                                             NSError *error)
             {
                 if (error)
                 {
                     block(NULL, error.description.UTF8String);
                 }
                 else
                 {
                     block([result[@"id"] UTF8String], NULL);
                 }
             }];
        }
    });
    
}
void KSocialObject::readLikes(K_FB_READLIKES_CALLBACK_BLOCK block)
{
    checkPermission("publish_actions", FBPermissionTypePublish, ^(const char *error)
    {
        if(error)
        {
            vector<const char*> vec;
            block(vec, error);
        }
        else
        {

            [FBRequestConnection startWithGraphPath:@"me/og.likes"
                                  completionHandler:^(FBRequestConnection *connection,
                                                      id result,
                                                      NSError *error)
            {
                vector<const char*> vec;
                if (error)
                {
                    block(vec, error.description.UTF8String);
                }
                else
                {
                    NSArray* idList = [result valueForKeyPath:@"data.id"];
                    for(NSString* ID in idList)
                    {
                        vec.push_back(ID.UTF8String);
                    }
                }
                block(vec, NULL);
            }];
        }
    });
}
void KSocialObject::readLikeWithID(const char *ID, K_FB_LIKE_CALLBACK_BLOCK block)
{
    checkPermission("publish_actions", FBPermissionTypePublish, ^(const char *error)
    {
        if(error)
        {
            block(NULL, error);
        }
        else
        {
            [FBRequestConnection startWithGraphPath:[NSString stringWithFormat:@"me/og.likes/%s", ID]
                                  completionHandler:^(FBRequestConnection *connection,
                                                      id result,
                                                      NSError *error)
             {
                 if (error)
                 {
                     block(NULL, error.description.UTF8String);
                 }
                 else
                 {
                     NSArray* list = [result valueForKeyPath:@"data.id"];
                     if (list.count > 0)
                     {
                         block([list[0] UTF8String], NULL);
                     }
                     else
                     {
                         block(NULL, NULL);
                     }
                     
                 }
             }];
        }
    });
}
void KSocialObject::unlike(const char* ID, K_FB_LIKE_REMOVE_CALLBACK_BLOCK block)
{
    checkPermission("publish_actions", FBPermissionTypePublish, ^(const char *error)
    {
        if(error)
        {
            block(NULL, error);
        }
        else
        {
            [FBRequestConnection startWithGraphPath:UTF8STRING_TO_NSSTRING(ID)
                                         parameters:nil
                                         HTTPMethod:@"DELETE"
                                  completionHandler:^(FBRequestConnection *connection,
                                                      id result,
                                                      NSError *error)
             {
                 if (error)
                 {
                     block(NULL, error.description.UTF8String);
                 }
                 else
                 {
                     block([result[@"FACEBOOK_NON_JSON_RESULT"] boolValue], NULL);
                 }
             }];
        }
    });
    
    
}
void KSocialObject::likeUpdate(const char* targetPath, const char* ID,K_FB_LIKE_CALLBACK_BLOCK block)
{
    checkPermission("publish_actions", FBPermissionTypePublish, ^(const char *error)
    {
        if(error)
        {
            block(NULL, error);
        }
        else
        {
            NSMutableDictionary<FBGraphObject> *action = [FBGraphObject graphObject];
            action[@"object"] = UTF8STRING_TO_NSSTRING(targetPath);
            
            [FBRequestConnection startForPostWithGraphPath:UTF8STRING_TO_NSSTRING(ID)
                                               graphObject:action
                                         completionHandler:^(FBRequestConnection *connection,
                                                             id result,
                                                             NSError *error)
             {
                 if (error)
                 {
                     block(NULL, error.description.UTF8String);
                 }
                 else
                 {
                     block([result[@"id"] UTF8String], NULL);
                 }
             }];
        }
    });
    
    
}
void KSocialObject::requestMe()
{
    if (FBSession.activeSession.isOpen)
    {
        [[FBRequest requestForMe] startWithCompletionHandler:
         ^(FBRequestConnection *connection,
           NSDictionary<FBGraphUser> *user,
           NSError *error)
         {
             if (!error)
             {
                 if(this->getDelegate())
                 {
                     SHARED_PTR<IKSocialUser> socialUser = SHARED_PTR<IKSocialUser>(new KSocialUser());
                     socialUser->setID(NSSTRING_TO_UTF8_STRING(user.id));
                     socialUser->setName(NSSTRING_TO_UTF8_STRING(user.name));
                     socialUser->setUsername(NSSTRING_TO_UTF8_STRING(user.username));
                     socialUser->setMiddleName(NSSTRING_TO_UTF8_STRING(user.middle_name));
                     socialUser->setLink(NSSTRING_TO_UTF8_STRING(user.link));
                     socialUser->setLastName(NSSTRING_TO_UTF8_STRING(user.last_name));
                     socialUser->setFirstname(NSSTRING_TO_UTF8_STRING(user.first_name));
                     socialUser->setBirthday(NSSTRING_TO_UTF8_STRING(user.birthday));
                    
                     
                     this->getDelegate()->facebookDidRequestMe(socialUser, nil);
                     
                     
                     
                 }
             }
             else
             {
                 if(this->getDelegate())
                 {
                     this->getDelegate()->facebookDidRequestMe(SHARED_PTR<KSocialUser>(NULL), error.localizedDescription.UTF8String);
                 }
             }
         }];
    }
}
void KSocialObject::headImagePathWithFacebookID(const char* ID, int width, int height, K_FB_HEAD_REQUEST_BLOCK block)
{
    char path[512];
    sprintf(path, "http://graph.facebook.com/%s/picture?width=%d&height=%d", ID, width, height);
    
    KNSFileFetcher* fileFetcher = [[KNSFileFetcher alloc] init];
    [fileFetcher fetchImageWithUrl:[NSString stringWithUTF8String:path] subFolderInCache:@"Library/Caches/fb_head" andCompletionBlock:block];
}
void KSocialObject::checkPermission(const char* permission, kFBPermissionType type, K_PERMISSION_CALLBACK_BLOCK block)
{
    NSString* nsPermission = UTF8STRING_TO_NSSTRING(permission);
    if (![FBSession.activeSession.permissions containsObject:nsPermission])
    {
        if (type == FBPermissionTypeRead)
        {
            [FBSession.activeSession requestNewReadPermissions:@[nsPermission] completionHandler:^(FBSession *session, NSError *error)
            {
                if (error)
                {
                    block(error.description.UTF8String);
                }
                else
                {
                    block(NULL);
                }
            }];
        }
        else if (type == FBPermissionTypePublish)
        {
            [FBSession.activeSession requestNewPublishPermissions:@[nsPermission] defaultAudience:(FBSessionDefaultAudience)FBSessionDefaultAudienceEveryone  completionHandler:^(FBSession *session, NSError *error)
             {
                 if (error)
                 {
                     block(error.description.UTF8String);
                 }
                 else
                 {
                     block(NULL);
                 }
             }];
        }
    }
    else
    {
        block(NULL);
    }
}