//
//  SPAppDelegate.h
//  SDK-MessageAPI Sample
//
//  Created by Michael Knecht on 31.05.13.
//  Copyright (c) 2013 C2Call GmbH. All rights reserved.
//

#import <SocialCommunication/SocialCommunication.h>
#import <UIKit/UIKit.h>

/** UIApplication Delegate
 
 The UIApplication delegate super class needs to be replaced with the C2CallAppDelegate class in order to handle the C2Call API initialization properly.

 The C2CallAppDelegate class also handles background modes and remote notifications.
 */
@interface SPAppDelegate : C2CallAppDelegate

@property (strong, nonatomic) UIWindow *window;

@end
