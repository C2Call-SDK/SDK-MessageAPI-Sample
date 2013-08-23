//
//  SPViewController.m
//  SDK-MessageAPI Sample
//
//  Created by Michael Knecht on 31.05.13.
//  Copyright (c) 2013 C2Call GmbH. All rights reserved.
//

#import <SocialCommunication/SocialCommunication.h>
#import <SocialCommunication/UIViewController+SCCustomViewController.h>

#import "SPViewController.h"


static SPViewController *__instance = nil;

@interface SPViewController () {
    C2BlockAction *openImageAction;
}

@end

@implementation SPViewController
@synthesize email, receivedMessage, messageText, imageButton;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    __instance = self;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(IBAction)submitMessage:(id)sender
{
    if ([self.messageText.text length] == 0) {
        self.receivedMessage.text = @"Please enter Message Text!";
        return;
    }

    if ([self.email.text length] == 0) {
        self.receivedMessage.text = @"Please enter receivers email address!";
        return;
    }

    if ([self.email.text rangeOfString:@"@"].location == NSNotFound) {
        // Seams to be a phone number
        [[C2CallPhone currentPhone] submitMessage:self.messageText.text toNumber:self.email.text];
    } else {
        [[C2CallPhone currentPhone] submitMessage:self.messageText.text toUser:self.email.text];
    }
    
}

-(IBAction)submitImage:(id)sender
{
    [self captureImageFromCameraWithQuality:UIImagePickerControllerQualityTypeMedium andCompleteAction:^(NSString *key) {
        [[C2CallPhone currentPhone] submitRichMessage:key message:self.messageText.text toTarget:self.email.text];
    }];
}

-(void) messageReceived:(NSString *) message remoteParty:(NSString *) remoteParty
{
    SCRichMediaType mt = [[C2CallPhone currentPhone] mediaTypeForKey:message];
    if (mt == SCMEDIATYPE_TEXT) {
        self.receivedMessage.text = [NSString stringWithFormat:@"%@:\n%@", remoteParty, message];
    }

    if (mt == SCMEDIATYPE_IMAGE) {
        self.receivedMessage.text = [NSString stringWithFormat:@"%@:\n%@", remoteParty, @"Got Image!"];
        if (![[C2CallPhone currentPhone] hasObjectForKey:message])  {
            SCWaitIndicatorController *wait = [SCWaitIndicatorController controllerWithTitle:@"Image Download" andWaitMessage:nil];
            [wait show:self.view];
            [[C2CallPhone currentPhone] retrieveObjectForKey:message completion:^(BOOL finished) {
                [wait hide];
                
                // Do this on Main-Thread
                dispatch_async(dispatch_get_main_queue(), ^{
                    UIImage *thumb = [[C2CallPhone currentPhone] thumbnailForKey:message];
                    if (thumb) {
                        openImageAction = [[C2BlockAction alloc] initWithAction:^(id sender) {
                            [self showPhoto:message];
                        }];
                        [self.imageButton addTarget:openImageAction action:@selector(fireAction:) forControlEvents:UIControlEventTouchUpInside];
                        [self.imageButton setImage:thumb forState:UIControlStateNormal];
                    }
                });
            }];
        }
    }
}

+(SPViewController *) instance
{
    return __instance;
}

@end
