//
//  IKSocialDelegate.h
//  KSocial
//
//  Created by kinfen on 13-7-7.
//  Copyright (c) 2013年 KStudio. All rights reserved.
//

#ifndef __KSocial__IKSocialDelegate__
#define __KSocial__IKSocialDelegate__

#include <iostream>
#include <KSocial/gamekit.h>
//#include <KSocial/KSocialUser.h>
NAMESPACE_KGK_BEGIN
class IKSocialUser;
class IKSocialDelegate
{
public:
    virtual void facebookSessionCallback(kFBSessionState state, const char* error){};
    virtual void facebookDidRequestMe(SHARED_PTR<IKSocialUser> user, const char* error){};
};

NAMESPACE_END

#endif /* defined(__KSocial__IKSocialDelegate__) */
