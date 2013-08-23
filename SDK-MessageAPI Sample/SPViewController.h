//
//  SPViewController.h
//  SDK-MessageAPI Sample
//
//  Created by Michael Knecht on 31.05.13.
//  Copyright (c) 2013 C2Call GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

/** Simple ViewController to demonstrate the messaging API
 
 This ViewController is intended to demonstrate the C2Call low-level message API.
 It uses only simple controls like UIButton, UILable and UITextField to implement a simple text message and a simple picture message functionnality
 The ViewController imports <SocialCommunication/UIViewController+SCCustomViewController.h> which extends this ViewController by simple methods to capture photos, videos or other rich media items.
 
    Example:
    [self captureImageFromCameraWithQuality:UIImagePickerControllerQualityTypeMedium andCompleteAction:^(NSString *key) {
        [[C2CallPhone currentPhone] submitRichMessage:key message:self.messageText.text toTarget:self.email.text];
    }];

 
 The core messaging functions used here are:
 
    [[C2CallPhone currentPhone] submitMessage:self.messageText.text toNumber:self.email.text];
    [[C2CallPhone currentPhone] submitMessage:self.messageText.text toUser:self.email.text];
    [[C2CallPhone currentPhone] submitRichMessage:key message:self.messageText.text toTarget:self.email.text];

  
 */
@interface SPViewController : UIViewController

/**---------------------------------------------------------------------------------------
 * @name Message Handling
 *  ---------------------------------------------------------------------------------------
 */

/** This method handles incoming messages through AppDelegate Class
 
 A message can be a text message or a rich message key, which is an URL like reference to a rich media item, like an image or a video.
 A helper method will help you to differentiate between the different message types:
 
    SCRichMediaType mt = [[C2CallPhone currentPhone] mediaTypeForKey:message];

 @param message The actual text message or rich message key
 @param remoteParty The senders name
 */
-(void) messageReceived:(NSString *) message remoteParty:(NSString *) remoteParty;

/**---------------------------------------------------------------------------------------
 * @name Actions
 *  ---------------------------------------------------------------------------------------
 */

/** Submit an Image captured from Camera Device
 
 This Method will open the camera controle to capture a photo.
 The captured photo will be stored and automatically submitted to the receiver
 
 @param sender The sender control which triggers the action.
 */

-(IBAction)submitImage:(id)sender;

/** Submit a Text Message
 
 This will submit the text message, entered into the message UITextField
 
 @param sender The sender control which triggers the action.
 */

-(IBAction)submitMessage:(id)sender;

/**---------------------------------------------------------------------------------------
 * @name Static Methods
 *  ---------------------------------------------------------------------------------------
 */

/** Access the instance of SPViewController
 
 @return Returns the instance of SPViewController
 */

+(SPViewController *) instance;

/**---------------------------------------------------------------------------------------
 * @name Properties
 *  ---------------------------------------------------------------------------------------
 */
/**
 */
@property (nonatomic, weak) IBOutlet        UITextField     *email, *messageText;
@property (nonatomic, weak) IBOutlet        UILabel         *receivedMessage;
@property (nonatomic, weak) IBOutlet        UIButton        *imageButton;

@end
