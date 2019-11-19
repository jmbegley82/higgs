#import <Foundation/Foundation.h>

int main () {
  @autoreleasepool {
	  NSMutableDictionary *dict = [[NSMutableDictionary alloc]initWithCapacity:10];
	  //[dict setObject:[NSNumber numberWithInt:42] forKey:@"number"];
	  dict[@"number"] = [NSNumber numberWithInt:42];
	  int myNumber = [[dict objectForKey:@"number"] intValue];
	  NSLog(@"myNumber = %d",myNumber);

  }
  return 0;
}
