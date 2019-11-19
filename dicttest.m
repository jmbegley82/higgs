#import <Foundation/Foundation.h>

struct pointlessStruct {
	int bullHonkey;
	double modifier;
	bool fleebJuice;
};

int main () {
  @autoreleasepool {
	  NSMutableDictionary *dict = [[NSMutableDictionary alloc]initWithCapacity:10];
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
	  NSLog(@"ps_check->modifier = %f", ps_check.modifier);
  }
  return 0;
}
