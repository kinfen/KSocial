//
//  KSocialManager.h
//  Skewer It
//
//  Created by kinfen on 13-7-6.
//
//

#ifndef __Skewer_It__KSocialManager__
#define __Skewer_It__KSocialManager__

#include <iostream>
#include <KSocial/gamekit.h>
//#include "EziSocialDelegate.h" 
namespace kgk
{
    class EXPORT KSocialManager
    {
    public:
        EXPORT static SHARED_PTR<KSocialManager> sharedInstance();
        EXPORT bool handleURL(const char* url, const char* sourceApplication);
        EXPORT void handleApplicationDidBecomeActive();
        EXPORT void handleApplicationLaunched();
        EXPORT void handleapplicationWillTerminate();
        
        EXPORT void fbSessionCallback(int responseCode);
    };
}

//-(BOOL) handleURL:(NSURL *)url;
//-(void) handleApplicationDidBecomeActive;
//-(void) handleApplicationLaunched;
#endif /* defined(__Skewer_It__KSocialManager__) */
