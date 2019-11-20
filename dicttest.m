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
	  NSMutableDictionary* maynardsDict = [[NSMutableDictionary alloc] autorelease];
	  maynardsDict[@"dict"] = dict;
	  NSMutableDictionary* unfamiliarDict = [maynardsDict objectForKey:@"dict"];
	  struct pointlessStruct ps_check2;
	  NSValue* nv_check2 = [unfamiliarDict objectForKey:@"object"];
	  [nv_check2 getValue:&ps_check2];
	  NSLog(@"ps_check2.modifier = %f", ps_check2.modifier);
  }
  return 0;
}
