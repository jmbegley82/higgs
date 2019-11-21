#import <Foundation/Foundation.h>

struct pointlessStruct {
	int bullHonkey;
	double modifier;
	bool fleebJuice;
};

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

	  for (NSNumber *nv in dict) {
		  NSLog(@"type info:  %@ -> %@", nv, [nv class]);
		  if([nv isKindOfClass:[NSValue class]])
			  NSLog(@"NSValue extra info -> %@", [NSString stringWithUTF8String:[nv objCType]]);
	  }
	  //NSLog(@"number = %@", [dict[@"number"] class]);

/*
// BAD LOGIC
	  if([[dict valueForKey:@"number"] isKindOfClass:[NSValue class]]) {

		  NSLog(@"number is an NSValue, which is weird.");
	  } else {
		  NSLog(@"number is not an NSValue, which is expected.");
	  }
*/
  }
  return 0;
}
