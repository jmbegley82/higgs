#import <Foundation/Foundation.h>
#import "Car.h"

int main () {
  @autoreleasepool {
    Car *toyota = [[Car alloc] init];

    [toyota setModel:@"Toyota Corolla"];
    NSLog(@"Created a %@", [toyota model]);

    toyota.model = @"Toyota Camry";
    NSLog(@"Changed the car to a %@", toyota.model);

    [toyota drive];
  }
  return 0;
}
