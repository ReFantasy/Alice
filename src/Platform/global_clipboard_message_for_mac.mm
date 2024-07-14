#include "global_clipboard_message_for_mac.h"
#include <AppKit/AppKit.h>
#include <iostream>
#import <Cocoa/Cocoa.h>

QClipboard* _qclipboad;


@interface Worker : NSObject
@end
@implementation Worker
-(instancetype)init
{
    if (self=[super init]) 
    {
        /*
        [NSEvent addGlobalMonitorForEventsMatchingMask:NSFlagsChangedMask //NSKeyDownMask  NSMouseMovedMask NSFlagsChangedMask
                                                       handler:^(NSEvent *event){
            NSUInteger flags = [event modifierFlags] & NSDeviceIndependentModifierFlagsMask;
            if(flags == (NSCommandKeyMask|NSAlternateKeyMask))
            {
                _qclipboad->dataChanged();
            }
          }
        ];*/

       [NSEvent addGlobalMonitorForEventsMatchingMask:NSLeftMouseDownMask handler:^(NSEvent *event){
            NSUInteger flags = [event modifierFlags] & NSDeviceIndependentModifierFlagsMask;
        }];

        [NSEvent addGlobalMonitorForEventsMatchingMask:NSLeftMouseUpMask handler:^(NSEvent *event){
            CGEventRef commandCEventDown = CGEventCreateKeyboardEvent(NULL, (CGKeyCode)8, true); 
            CGEventSetFlags(commandCEventDown, kCGEventFlagMaskCommand);
            CGEventPost(kCGSessionEventTap, commandCEventDown);
            CFRelease(commandCEventDown);
            CGEventRef commandCEventUp = CGEventCreateKeyboardEvent(NULL, (CGKeyCode)8, false); 
            CGEventSetFlags(commandCEventUp, kCGEventFlagMaskCommand);
            CGEventPost(kCGSessionEventTap, commandCEventUp);
            CFRelease(commandCEventUp);
            _qclipboad->dataChanged();
        }];
   
    }
    return self;
}

@end

void SetQtClipboard(QClipboard* qclipboad)
{
    static Worker * worker=[[Worker alloc] init];
    _qclipboad = qclipboad;
}







