//
//  KFBGraphUser.h
//  KSocial
//
//  Created by kinfen on 13-7-8.
//  Copyright (c) 2013年 KStudio. All rights reserved.
//

#ifndef __KSocial__KSocialUser__
#define __KSocial__KSocialUser__

#include <iostream>
#include <KSocial/gamekit.h>

NAMESPACE_KGK_BEGIN


class IKSocialUser
{
public:
    K_VIRTUAL_PROPERTY_ASSIGN(std::string, ID);
    K_VIRTUAL_PROPERTY_ASSIGN(std::string, Name);
    K_VIRTUAL_PROPERTY_ASSIGN(std::string, Firstname);
    K_VIRTUAL_PROPERTY_ASSIGN(std::string, MiddleName);
    K_VIRTUAL_PROPERTY_ASSIGN(std::string, LastName);
    K_VIRTUAL_PROPERTY_ASSIGN(std::string, Link);
    K_VIRTUAL_PROPERTY_ASSIGN(std::string, Username);
    K_VIRTUAL_PROPERTY_ASSIGN(std::string, Birthday);
    //    K_VIRTUAL_PROPERTY_ASSIGN(std::string, Location);
    
};

class KSocialUser : public IKSocialUser
{
public:
    KSocialUser(){};
    K_SYNTHESIZE(std::string, m_id, ID);
    K_SYNTHESIZE(std::string, m_name, Name);
    K_SYNTHESIZE(std::string, m_firstName, Firstname);
    K_SYNTHESIZE(std::string, m_middleName, MiddleName);
    K_SYNTHESIZE(std::string, m_lastName, LastName);
    K_SYNTHESIZE(std::string, m_link, Link);
    K_SYNTHESIZE(std::string, m_username, Username);
    K_SYNTHESIZE(std::string, m_birthday, Birthday);
//    K_SYNTHESIZE(std::string, m_location, Location);
    
};

//@property (retain, nonatomic) NSString *id;
//
///*!
// @property
// @abstract Typed access to the user's name.
// */
//@property (retain, nonatomic) NSString *name;
//
///*!
// @property
// @abstract Typed access to the user's first name.
// */
//@property (retain, nonatomic) NSString *first_name;
//
///*!
// @property
// @abstract Typed access to the user's middle name.
// */
//@property (retain, nonatomic) NSString *middle_name;
//
///*!
// @property
// @abstract Typed access to the user's last name.
// */
//@property (retain, nonatomic) NSString *last_name;
//
///*!
// @property
// @abstract Typed access to the user's profile URL.
// */
//@property (retain, nonatomic) NSString *link;
//
///*!
// @property
// @abstract Typed access to the user's username.
// */
//@property (retain, nonatomic) NSString *username;
//
///*!
// @property
// @abstract Typed access to the user's birthday.
// */
//@property (retain, nonatomic) NSString *birthday;
//
///*!
// @property
// @abstract Typed access to the user's current city.
// */
//@property (retain, nonatomic) id<FBGraphPlace> location;
NAMESPACE_END

#endif /* defined(__KSocial__KFBGraphUser__) */
