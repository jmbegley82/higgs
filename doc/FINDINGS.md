Safe things to store into/retrieve from a plist:

Cocoa class			CoreFoundation type
NSArray				CFArray
NSDictionary			CFDictionary
NSString			CFString
NSData				CFData
NSDate				CFDate
NSNumber (int and float)	CFNumber (int and float)
NSNumber (bool)			CFBoolean (bool)

So it may be a good idea to store data using these objects instead of trying
to cram arbitrary c-structs into containers.  If structs need to be used, they
should be converted to NSArray or NSDictionary for storage and back to structs
for passing back to straight C.

