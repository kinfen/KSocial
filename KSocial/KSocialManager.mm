//
//  KSocialManager.cpp
//  Skewer It
//
//  Created by kinfen on 13-7-6.
//
//

#include "KSocialManager.h"
#include "KSocialObject.h"
#import "KNSSocialManager.h"
#include <vector>
using namespace kgk;
SHARED_PTR<KSocialManager> KSocialManager::sharedInstance()
{
//    std::vector<<#class _Tp#>>
    static SHARED_PTR<KSocialManager> g_instance;
    if (g_instance.get() == NULL)
    {
        g_instance = SHARED_PTR<KSocialManager>(new KSocialManager());
    }
    return g_instance;
}

bool KSocialManager::handleURL(const char *url, const char *sourceApplication)
{
    
    NSURL* targetURL = [NSURL URLWithString:[NSString stringWithUTF8String:url]];
    NSString* application = [NSString stringWithUTF8String:sourceApplication];
    return [FBAppCall handleOpenURL:targetURL sourceApplication:application withSession:[[KNSSocialManager sharedInstance] session]];
}

void KSocialManager::handleApplicationLaunched()
{
//    printf("testtetsafaf;kja;dfkjad;lkfja;dlfkjadfk\n");
//    [[EziSocialManager sharedManager] handleApplicationLaunched];

}
void KSocialManager::handleApplicationDidBecomeActive()
{
    [FBAppCall handleDidBecomeActiveWithSession: [[KNSSocialManager sharedInstance] session]];
}
void KSocialManager::handleapplicationWillTerminate()
{
    KSocialObject::sharedInstance()->close();
}

void KSocialManager::fbSessionCallback(int responseCode)
{
    switch (responseCode)
    {
//        case EziSocialWrapperNS::RESPONSE_CODE::FB_LOGIN_SUCCESSFUL:
//            EziSocialObject::sharedObject()->openFacebookPage("skeweritapp", false);
//            break;
//        case EziSocialWrapperNS::RESPONSE_CODE::FB_LOGIN_FAILED:
//            CCAssert(false, "login fail");
//            break;
//            
//        case EziSocialWrapperNS::RESPONSE_CODE::FB_LOGIN_FIRST_NEEDS_READ_PERMISSION:
//            CCLOG("needs read permsssion");
//            break;
//            
//        case EziSocialWrapperNS::RESPONSE_CODE::FB_LOGIN_APP_NOT_ALLOWERD_TO_USE_FB:
//            CCLOG("not allow to login fb");
//            break;
//            
//        case EziSocialWrapperNS::RESPONSE_CODE::FB_LOGIN_PERMISSION_DENIED:
//            CCLOG("fb login permission denied");
//            break;
            
            
        default:
            break;
    }
}
