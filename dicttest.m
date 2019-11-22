#import <Foundation/Foundation.h>
#import "dicttest.h"
#import "Plist.h"

/*
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
*/

int main () {
  @autoreleasepool {
	  NSMutableDictionary *dict = [[[NSMutableDictionary alloc]initWithCapacity:10] autorelease];
	  //[dict setObject:[NSNumber numberWithInt:42] forKey:@"number"];
	  dict[@"number"] = [NSNumber numberWithInt:42];
	  struct pointlessStruct* ps = malloc(sizeof(struct pointlessStruct));
	  ps->bullHonkey = 2;
	  ps->modifier = 46.2;
	  ps->fleebJuice = true;
	  dict[@"object"] = [NSValue valueWithBytes:ps objCType:@encode(struct pointlessStruct)];
	  int myNumber = [[dict objectForKey:@"number"] intValue];
	  struct pointlessStruct ps_check; //= [[dict objectForKey:@"object"] pointerValue];
	  NSValue* nv_check = [dict objectForKey:@"object"];
	  [nv_check getValue:&ps_check];
	  NSLog(@"myNumber = %d",myNumber);
	  NSLog(@"ps_check.modifier = %f", ps_check.modifier);
	  for(NSNumber* thisNumber in dict) {
		  NSLog(@"%@", thisNumber);
	  }
	  NSMutableDictionary* maynardsDict = [[NSMutableDictionary alloc] autorelease];
	  maynardsDict[@"dict"] = dict;
	  NSMutableDictionary* unfamiliarDict = [maynardsDict objectForKey:@"dict"];
	  struct pointlessStruct ps_check2;
	  NSValue* nv_check2 = [unfamiliarDict objectForKey:@"object"];
	  [nv_check2 getValue:&ps_check2];
	  NSLog(@"ps_check2.modifier = %f", ps_check2.modifier);

	  NSLog(@"object type string is %@", [NSString stringWithUTF8String:[dict[@"object"] objCType]]);
	  NSLog(@"number type string is %@", [NSString stringWithUTF8String:[dict[@"number"] objCType]]);
	  //NSLog(@"dict type string is %@", [NSString stringWithUTF8String:[maynardsDict[@"dict"] objCType]]);
//	  NSString* ns_check2 = [NSString stringWithUTF8String:nv_check2.objCType];
//	  NSLog(@"number type string is %@", ns_check2);
/*
	  if([[dict valueForKey:@"object"] isKindOfClass:[NSValue class]]) {
		  NSLog(@"object is an NSValue, as expected.");
	  } else {
		  NSLog(@"object is not an NSValue, which is awkward.");
	  }

	  if([dict[@"object"] isKindOfClass:[NSValue class]])
		  NSLog(@"object is an NSValue, as expected, %@", [maynardsDict[@"dict"] class]);
*/
	  NSLog(@"Type stuff:");
	  NSLog(@"number = %@", [dict[@"number"] class]);
	  NSLog(@"object = %@", [dict[@"object"] class]);
	  NSLog(@"dict = %@", [maynardsDict[@"dict"] class]);

	  ListAllIds(dict);
	  ListAllIds(maynardsDict);
	  ListAllIds(unfamiliarDict);
	  NSString* plist = [Plist objToPlistAsString:maynardsDict];
	  NSLog(@"Plist test:\n%@", plist);
	  NSLog(@"Plist test 2:\n");
	  NSDictionary* additionalDict = [Plist plistToObjectFromString:plist];
	  ListAllIds(additionalDict);
  }
  return 0;
}
