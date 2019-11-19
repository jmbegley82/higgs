#import "Car.h"

@implementation Car {
  double _odometer;
}

@synthesize model = _model;

- (void)drive {
  NSLog(@"Driving a %@. Vrooom!", self.model);
}

@end
