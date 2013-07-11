//
//  gamekit.h
//  KSocialKit
//
//  Created by kinfen on 13-7-6.
//  Copyright (c) 2013年 kinfen. All rights reserved.
//

#ifndef KSocialKit_gamekit_h
#define KSocialKit_gamekit_h
#include <boost/shared_ptr.hpp>

class vector;

#ifndef SHARED_PTR
#define SHARED_PTR boost::shared_ptr
#endif

#define EXPORT //_LIBCPP_VISIBLE

#ifndef NAMESPACE_KGK_BEGIN
#define NAMESPACE_KGK_BEGIN namespace kgk{
#define NAMESPACE_END }
#define USING_NAMESPACE_KGK using namespace kgk
#endif

#ifndef K_PROPERTY

#define K_PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void);

#define K_PROPERTY_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void);


#define K_PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void);\
public: virtual void set##funName(varType var);

#define K_PROPERTY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void);\
public: virtual void set##funName(const varType& var);

#define K_SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }

#define K_SYNTHESIZE_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const { return varName; }

#define K_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

#define K_SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const { return varName; }\
public: virtual void set##funName(const varType& var){ varName = var; }

#define K_SAFE_DELETE(p)            do { if(p) { delete (p); (p) = 0; } } while(0)
#define K_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = 0; } } while(0)
#define K_SAFE_FREE(p)                do { if(p) { free(p); (p) = 0; } } while(0)
#define K_BREAK_IF(cond)            if(cond) break

#define K_PROPERTY_DEFINED_ASSIGN(TYPE, PROPERTYNAME) \
void set##PROPERTYNAME(TYPE value);\
TYPE get##PROPERTYNAME() const

#define K_VIRTUAL_PROPERTY_ASSIGN(TYPE, PROPERTYNAME)\
virtual void set##PROPERTYNAME(TYPE value){};\
virtual TYPE get##PROPERTYNAME() const{ return 0;}

#define K_VIRTUAL_PROPERTY_DEFINED_ASSIGN(TYPE, PROPERTYNAME)\
virtual void set##PROPERTYNAME(TYPE value);\
virtual TYPE get##PROPERTYNAME() const

#define K_VIRTUAL_PROPERTY_READONLY(TYPE, PROPERTYNAME)\
virtual TYPE get##PROPERTYNAME() const{ return 0;}

#define K_VIRTUAL_PROPERTY_DEFINED_READONLY(TYPE, PROPERTYNAME)\
virtual TYPE get##PROPERTYNAME() const

#endif



#define FB_SESSIONSTATETERMINALBIT (1 << 8)

#define FB_SESSIONSTATEOPENBIT (1 << 9)

NAMESPACE_KGK_BEGIN

/*
    use kFBPermissionType for ask permission
 */
typedef enum
{
    FBPermissionTypeRead,
    FBPermissionTypePublish
    
}kFBPermissionType;

/*!
 @typedef FBSessionState enum
 
 @abstract Passed to handler block each time a session state changes
 
 @discussion
 */
typedef enum {
    /*! One of two initial states indicating that no valid cached token was found */
    FBSessionStateCreated                   = 0,
    /*! One of two initial session states indicating that a cached token was loaded;
     when a session is in this state, a call to open* will result in an open session,
     without UX or app-switching*/
    FBSessionStateCreatedTokenLoaded        = 1,
    /*! One of three pre-open session states indicating that an attempt to open the session
     is underway*/
    FBSessionStateCreatedOpening            = 2,
    
    /*! Open session state indicating user has logged in or a cached token is available */
    FBSessionStateOpen                      = 1 | FB_SESSIONSTATEOPENBIT,
    /*! Open session state indicating token has been extended */
    FBSessionStateOpenTokenExtended         = 2 | FB_SESSIONSTATEOPENBIT,
    
    /*! Closed session state indicating that a login attempt failed */
    FBSessionStateClosedLoginFailed         = 1 | FB_SESSIONSTATETERMINALBIT, // NSError obj w/more info
    /*! Closed session state indicating that the session was closed, but the users token
     remains cached on the device for later use */
    FBSessionStateClosed                    = 2 | FB_SESSIONSTATETERMINALBIT, // "
} kFBSessionState;

/*! helper macro to test for states that imply an open session */
#define FB_ISSESSIONOPENWITHSTATE(state) (0 != (state & FB_SESSIONSTATEOPENBIT))

/*! helper macro to test for states that are terminal */
#define FB_ISSESSIONSTATETERMINAL(state) (0 != (state & FB_SESSIONSTATETERMINALBIT))

/*!
 @typedef FBSessionLoginBehavior enum
 
 @abstract
 Passed to open to indicate whether Facebook Login should allow for fallback to be attempted.
 
 @discussion
 Facebook Login authorizes the application to act on behalf of the user, using the user's
 Facebook account. Usually a Facebook Login will rely on an account maintained outside of
 the application, by the native Facebook application, the browser, or perhaps the device
 itself. This avoids the need for a user to enter their username and password directly, and
 provides the most secure and lowest friction way for a user to authorize the application to
 interact with Facebook. If a Facebook Login is not possible, a fallback Facebook Login may be
 attempted, where the user is prompted to enter their credentials in a web-view hosted directly
 by the application.
 
 The `FBSessionLoginBehavior` enum specifies whether to allow fallback, disallow fallback, or
 force fallback login behavior. Most applications will use the default, which attempts a normal
 Facebook Login, and only falls back if needed. In rare cases, it may be preferable to disallow
 fallback Facebook Login completely, or to force a fallback login.
 */
typedef enum {
    /*! Attempt Facebook Login, ask user for credentials if necessary */
    FBSessionLoginBehaviorWithFallbackToWebView      = 0,
    /*! Attempt Facebook Login, no direct request for credentials will be made */
    FBSessionLoginBehaviorWithNoFallbackToWebView    = 1,
    /*! Only attempt WebView Login; ask user for credentials */
    FBSessionLoginBehaviorForcingWebView             = 2,
    /*! Attempt Facebook Login, prefering system account and falling back to fast app switch if necessary */
    FBSessionLoginBehaviorUseSystemAccountIfPresent  = 3,
} kFBSessionLoginBehavior;

/*!
 @typedef FBSessionDefaultAudience enum
 
 @abstract
 Passed to open to indicate which default audience to use for sessions that post data to Facebook.
 
 @discussion
 Certain operations such as publishing a status or publishing a photo require an audience. When the user
 grants an application permission to perform a publish operation, a default audience is selected as the
 publication ceiling for the application. This enumerated value allows the application to select which
 audience to ask the user to grant publish permission for.
 */
typedef enum {
    /*! No audience needed; this value is useful for cases where data will only be read from Facebook */
    FBSessionDefaultAudienceNone                = 0,
    /*! Indicates that only the user is able to see posts made by the application */
    FBSessionDefaultAudienceOnlyMe              = 10,
    /*! Indicates that the user's friends are able to see posts made by the application */
    FBSessionDefaultAudienceFriends             = 20,
    /*! Indicates that all Facebook users are able to see posts made by the application */
    FBSessionDefaultAudienceEveryone            = 30,
} kFBSessionDefaultAudience;

/*!
 @typedef FBSessionLoginType enum
 
 @abstract
 Used as the type of the loginType property in order to specify what underlying technology was used to
 login the user.
 
 @discussion
 The FBSession object is an abstraction over five distinct mechanisms. This enum allows an application
 to test for the mechanism used by a particular instance of FBSession. Usually the mechanism used for a
 given login does not matter, however for certain capabilities, the type of login can impact the behavior
 of other Facebook functionality.
 */
typedef enum {
    /*! A login type has not yet been established */
    FBSessionLoginTypeNone                      = 0,
    /*! A system integrated account was used to log the user into the application */
    FBSessionLoginTypeSystemAccount             = 1,
    /*! The Facebook native application was used to log the user into the application */
    FBSessionLoginTypeFacebookApplication       = 2,
    /*! Safari was used to log the user into the application */
    FBSessionLoginTypeFacebookViaSafari         = 3,
    /*! A web view was used to log the user into the application */
    FBSessionLoginTypeWebView                   = 4,
    /*! A test user was used to create an open session */
    FBSessionLoginTypeTestUser                  = 5,
} kFBSessionLoginType;

typedef enum {
    /*! Indicates that the dialog action completed successfully. Note, that cancel operations represent completed dialog operations.
     The url argument may be used to distinguish between success and user-cancelled cases */
    FBWebDialogResultDialogCompleted,
    /*! Indicates that the dialog operation was not completed. This occurs in cases such as the closure of the web-view using the X in the upper left corner. */
    FBWebDialogResultDialogNotCompleted
} kFBWebDialogResult;

NAMESPACE_END


#endif
