//
//  KSocialObject.h
//  KSocial
//
//  Created by kinfen on 13-7-7.
//  Copyright (c) 2013年 KStudio. All rights reserved.
//

#ifndef __KSocial__KSocialObject__
#define __KSocial__KSocialObject__

#include <iostream>
#include <KSocial/IKSocialDelegate.h>
#include <KSocial/IKSocialObjectAction.h>
#include <KSocial/gamekit.h>


namespace kgk
{
    typedef void(^K_PERMISSION_CALLBACK_BLOCK)(const char* error);
    
    class EXPORT KSocialObject : public IKSocialObjectAction
    {
        KSocialObject();
    public:
        static EXPORT SHARED_PTR<KSocialObject> sharedInstance();
        EXPORT virtual void loginWithFacebook();
        EXPORT virtual void logoutWithFacebook();
        EXPORT virtual bool isFacebookLogin();
        EXPORT virtual void resume();
        EXPORT virtual void close();
        
        EXPORT virtual void requestMe();
        EXPORT virtual void inviteFriends(const char* mesage, const char* title, std::vector<std::string>* toFriendsID, std::vector<std::string>* suggestFriendsID, K_FB_DIALOG_REQUEST_BLOCK block);
        EXPORT virtual void like(const char* targetPath, K_FB_LIKE_CALLBACK_BLOCK block);
        EXPORT virtual void readLikes(K_FB_READLIKES_CALLBACK_BLOCK block);
        EXPORT virtual void readLikeWithID(const char * ID, K_FB_LIKE_CALLBACK_BLOCK block);
        EXPORT virtual void likeUpdate(const char* targetPath, const char* ID,K_FB_LIKE_CALLBACK_BLOCK block);
        EXPORT virtual void unlike(const char* ID, K_FB_LIKE_REMOVE_CALLBACK_BLOCK block);
        
        EXPORT virtual void headImagePathWithFacebookID(const char* ID, int width, int height, K_FB_HEAD_REQUEST_BLOCK block);
        K_SYNTHESIZE(IKSocialDelegate*, m_delegate, Delegate);
        
    private:
        void openSession();
        void checkPermission(const char* permission, kFBPermissionType type,K_PERMISSION_CALLBACK_BLOCK block);
    };
}

#endif /* defined(__KSocial__KSocialObject__) */
