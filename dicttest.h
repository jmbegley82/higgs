#ifndef DICTTEST_H
#define DICTTEST_H

#import <Foundation/Foundation.h>

struct pointlessStruct {
	int bullHonkey;
	double modifier;
	bool fleebJuice;
};

void ListAllIds(NSDictionary* dict) {
	NSLog(@"Info for Dictionary:");
	for (id nv in dict) {
		NSLog(@"type info:  %@ -> %@", nv, [dict[nv] class]);
		if([dict[nv] isKindOfClass:[NSValue class]])
			NSLog(@"NSValue extra info -> %@", [NSString stringWithUTF8String:[dict[nv] objCType]]);
		else if([dict[nv] isKindOfClass:[NSDictionary class]])
			ListAllIds(dict[nv]);
	}
}

#endif //DICTTEST_H
