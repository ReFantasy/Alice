#include "global_clipboard_message_for_mac.h"
#include <iostream>
#import <Cocoa/Cocoa.h>

QClipboard* _qclipboad;


@interface Worker : NSObject
@end
@implementation Worker
-(instancetype)init
{
    if (self=[super init]) {
        [NSEvent addGlobalMonitorForEventsMatchingMask:NSFlagsChangedMask //NSKeyDownMask  NSMouseMovedMask NSFlagsChangedMask
                                                       handler:^(NSEvent *event){

            NSUInteger flags = [event modifierFlags] & NSDeviceIndependentModifierFlagsMask;
            if(flags == (NSCommandKeyMask|NSAlternateKeyMask)){
                _qclipboad->dataChanged();
            }
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








