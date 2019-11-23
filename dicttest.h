#ifndef DICTTEST_H
#define DICTTEST_H

#import <Foundation/Foundation.h>

struct pointlessStruct {
	int bullHonkey;
	double modifier;
	bool fleebJuice;
};

bool PStoNSD(struct pointlessStruct* ps, NSMutableDictionary* nsd) {
	if(ps == NULL || nsd == NULL) return false;
	// TODO:  make this actually work!
	nsd[@"bullHonkey"] = [NSNumber numberWithInt:ps->bullHonkey];
	nsd[@"modifier"] = [NSNumber numberWithDouble:ps->modifier];
	nsd[@"fleebJuice"] = [NSNumber numberWithBool:ps->fleebJuice];
	return true;
}

bool NSDtoPS(NSDictionary* nsd, struct pointlessStruct* ps) {
	if(ps == NULL || nsd == NULL) return false;
	ps->bullHonkey = [nsd[@"bullHonkey"] intValue];
	ps->modifier = [nsd[@"modifier"] doubleValue];
	ps->fleebJuice = [nsd[@"fleebJuice"] boolValue];
	return true;
}

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
