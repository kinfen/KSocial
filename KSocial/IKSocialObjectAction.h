//
//  IKSocialObjectAction.h
//  KSocial
//
//  Created by kinfen on 13-7-7.
//  Copyright (c) 2013年 KStudio. All rights reserved.
//

#ifndef __KSocial__IKSocialObjectAction__
#define __KSocial__IKSocialObjectAction__

#include <iostream>
#include <KSocial/gamekit.h>
#include <vector>

using namespace std;

namespace kgk
{
    
    typedef   void(^K_FB_HEAD_REQUEST_BLOCK)(const char* imagePath, const char* error);
    typedef   void(^K_FB_DIALOG_REQUEST_BLOCK)(kFBWebDialogResult result, const char *resultURL, const char* error);
    
    typedef   void(^K_FB_LIKE_CALLBACK_BLOCK)(const char* ID, const char* error);
    typedef   void(^K_FB_READLIKES_CALLBACK_BLOCK)(vector<const char*> ID_List, const char* error);
    typedef   void(^K_FB_LIKE_REMOVE_CALLBACK_BLOCK)(bool result, const char* error);
    
    
    class IKSocialObjectAction
    {
    public:
        virtual void loginWithFacebook(){};
        virtual void logoutWithFacebook(){};
        virtual bool isFacebookLogin(){return false;};
        virtual void resume(){};
        virtual void close(){};
        virtual void requestMe(){};
        virtual void inviteFriends(const char* mesage, const char* title, std::vector<std::string>* toFriendsID, std::vector<std::string>* suggestFriendsID, K_FB_DIALOG_REQUEST_BLOCK block){};
        
        virtual void like(const char* targetPath, K_FB_LIKE_CALLBACK_BLOCK block){};
        virtual void readLikes(K_FB_READLIKES_CALLBACK_BLOCK block){};
        virtual void readLikeWithID(const char * ID, K_FB_LIKE_CALLBACK_BLOCK block){};
        virtual void likeUpdate(const char* targetPath, const char* ID,  K_FB_LIKE_CALLBACK_BLOCK block){};
        virtual void unlike(const char* ID, K_FB_LIKE_REMOVE_CALLBACK_BLOCK block){};
        
        virtual void headImagePathWithFacebookID(const char* ID, int width, int height, K_FB_HEAD_REQUEST_BLOCK block){};
    };
}
#endif /* defined(__KSocial__IKSocialObjectAction__) */

//https://profile-a.xx.fbcdn.net/hprofile-ash4/c178.0.604.604/s320x320/252231_1002029915278_1941483569_n.jpg
//https://fbcdn-profile-a.akamaihd.net/hprofile-ak-frc1/c24.0.155.155/1002444_10201410651290552_1097622634_n.jpg
//https://profile-b.xx.fbcdn.net/hprofile-frc1/c108.28.345.345/s320x320/944199_10201410665370904_498138862_n.jpg
//https://fbcdn-profile-a.akamaihd.net/hprofile-ak-prn1/c35.35.442.442/s320x320/1012811_10201410721452306_1290279825_n.jpg