#ifndef PLIST_H
#define PLIST_H

// from http://hayageek.com/plist-tutorial/

#import <Foundation/Foundation.h>
 
@interface Plist : NSObject
 
//Convert Object(Dictionary,Array) to Plist(NSData)
+(NSData *) objToPlistAsData:(id)obj;
 
//Convert Object(Dictionary,Array) to Plist(NSString)
+(NSString *) objToPlistAsString:(id)obj;
 
//Convert Plist(NSData) to Object(Array,Dictionary)
+(id) plistToObjectFromData:(NSData *)data;
 
//Convert Plist(NSString) to Object(Array,Dictionary)
+(id) plistToObjectFromString:(NSString*)str;
 
@end

#endif //PLIST_H
