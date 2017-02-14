//
//  ViewController.m
//  SOQuestionsAnswers
//
//  Created by KrishnaChaitanya Amjuri on 25/11/16.
//  Copyright © 2016 Krishna Chaitanya. All rights reserved.
//

#import "ViewController.h"
#import <UserNotifications/UserNotifications.h>
#import <UserNotificationsUI/UserNotificationsUI.h>
#import "Masonry/Masonry.h"
#import "WFCollectionView.h"
#import "BLWordSuggestions.h"
#import <CoreMotion/CoreMotion.h>

@interface ViewController ()<UITextFieldDelegate, UIAccelerometerDelegate>

@property (nonatomic) UIView *yellow;

@property (nonatomic) BLWordSuggestions *blWordSuggestion;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    
    NSString *destinationDicPath = [NSString stringWithFormat:@"%@/%@", documentsDirectory,@"EnglishFromTwitterReddit.dic"];
    NSURL *dicUrl = [[NSBundle mainBundle] URLForResource:@"EnglishFromTwitterReddit" withExtension:@"dic"];
    
    NSArray *jsonFiles = @[@"bn_IN_126", @"bn_IN_2452", @"bn_IN_2535", @"en_US_48", @"en_US_81", @"en_US_113", @"en_US_9786", @"en_US_127968", @"en_US_128021", @"en_US_128285", @"en_US_128304", @"gu_IN_49", @"gu_IN_126", @"gu_IN_2707", @"gu_IN_2708", @"gu_IN_2722", @"hi_IN_126", @"hi_IN_2324", @"hi_IN_2380", @"hi_IN_2407", @"kn_IN_126", @"kn_IN_3231", @"kn_IN_3232", @"kn_IN_3303", @"ml_IN_49", @"ml_IN_126", @"ml_IN_3344", @"ml_IN_3415", @"pa_IN_126", @"pa_IN_2596", @"pa_IN_2597", @"pa_IN_2663", @"ta_IN_126", @"ta_IN_2974", @"ta_IN_2998", @"ta_IN_3047", @"te_IN_126", @"te_IN_3103", @"te_IN_3104"];
    
    NSString *jsonDirectoryPath = [documentsDirectory stringByAppendingPathComponent:@"DicJsonDir"];

    NSError *error;
    [[NSFileManager defaultManager] copyItemAtPath:dicUrl.path toPath:destinationDicPath error:&error];

    NSMutableArray *jsonPathsArray = [NSMutableArray array];

    for (int i = 0; i < jsonFiles.count; i++) {
        error = nil;
        NSURL *bundlePathURL = [[NSBundle mainBundle] URLForResource:jsonFiles[i] withExtension:@"json"];
        NSString *bundlePath = [bundlePathURL path];
        NSData *jsonData = [NSData dataWithContentsOfFile:bundlePath];
        if (jsonData != nil) {
            printf("Exists");
        }else {
            printf("");
        }
//        NSString *jsonPath = [jsonDirectoryPath stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.json",jsonFiles[i]]];
//        [[NSFileManager defaultManager] copyItemAtPath:bundlePath toPath:jsonPath error:&error];
        [jsonPathsArray addObject:bundlePath];
    }
    
    if (error == nil) {
        _blWordSuggestion = [[BLWordSuggestions alloc] initWithDicFilePath:destinationDicPath withProximityFiles:jsonPathsArray];
    }else if (error.code == 516) {
        _blWordSuggestion = [[BLWordSuggestions alloc] initWithDicFilePath:destinationDicPath withProximityFiles:jsonPathsArray];
    }
    
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    dateFormatter.dateFormat = @"yyyy-MM-dd";
    dateFormatter.timeZone = [NSTimeZone systemTimeZone];
    
    NSString *dateString = @"2014-06-09 11:30";
    dateString = [dateString substringToIndex:10];
    
    NSDate *s_date = [dateFormatter dateFromString:dateString];

    self.view.backgroundColor = [UIColor redColor];
    
    [[UNUserNotificationCenter currentNotificationCenter] requestAuthorizationWithOptions:UNAuthorizationOptionAlert completionHandler:^(BOOL granted, NSError * _Nullable error) {
        if (granted) {
            
        }
    }];
    
    NSMutableArray *arayMutable = [@[@"Jan", @"Feb", @"Mar"] mutableCopy];
    
    dispatch_queue_t queue1 = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0);
    dispatch_queue_t queue2 = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0);
    
    dispatch_async(queue1, ^{
        [arayMutable addObject:@"add"];
    });
    
    dispatch_async(queue2, ^{
        [arayMutable removeObject:@"Jan"];
    });
    
    UIView *greenView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 200, 200)];
    greenView.backgroundColor = [UIColor greenColor];
    [self.view addSubview:greenView];
    
    self.yellow = [[UIView alloc] initWithFrame:CGRectZero];
    _yellow.backgroundColor = [UIColor yellowColor];
    [greenView addSubview:_yellow];
    
    UIView *darkSpot = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 20, 20)];
    darkSpot.backgroundColor = [UIColor blackColor];
    [_yellow addSubview:darkSpot];
    
    [_yellow mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.equalTo(@100);
        make.height.equalTo(@100);
        make.top.equalTo(@0);
        make.left.equalTo(@0);
        make.right.equalTo(@0);
        make.bottom.equalTo(@0);
    }];
    
    NSMutableDictionary *buttonSelection = [@{@"P_Button" : @"Selected",
                                              @"F_Button" : @"Selected",
                                              @"W_Button" : @"Selected",
                                              @"NA_Button" : @"Selected"} mutableCopy];
    
    NSDateComponents *components = [[NSDateComponents alloc] init];
    components.weekday = 2;
//    UNCalendarNotificationTrigger *cc = [UNCalendarNotificationTrigger triggerWithDateMatchingComponents: repeats:];
    
    [self addAViewWithTextField];
}

- (void)addAViewWithTextField {
    
    UIView *myView = [[UIView alloc] initWithFrame:self.view.bounds];
    myView.backgroundColor = [UIColor whiteColor];
    [self.view addSubview:myView];
    
    UITextField *textField = [[UITextField alloc] initWithFrame:CGRectMake(40, 60, self.view.bounds.size.width-80, 60)];
    textField.backgroundColor = [[UIColor whiteColor] colorWithAlphaComponent:0.75];
    textField.layer.borderColor = [[UIColor blueColor] CGColor];
    textField.layer.borderWidth = 1.0f;
    textField.delegate = self;
    textField.autocorrectionType = UITextAutocorrectionTypeNo;
    textField.textColor = [UIColor blueColor];
    [myView addSubview:textField];
}

- (void)textFieldDidEndEditing:(UITextField *)textField {

    NSString *word = textField.text;
    if (word != NULL) {
        NSArray *suggestArray = [_blWordSuggestion getSuggestionsForWord:word withPreviousWord:@""];
        NSLog(@"suggestArray: %@", suggestArray);
    }
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return YES;
}

- (void)viewDidLayoutSubviews {
    [super viewDidLayoutSubviews];
    
    NSLog(@"%@", NSStringFromCGRect(self.yellow.frame));
}

- (void)didReceiveMemoryWarning {
    
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)buttonTapped:(id)sender {
    
    NSCalendar *currentCalendar = [NSCalendar currentCalendar];

    NSString *fromDateString = @"16-01-2017";
    
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"dd-MM-yyyy"];
    
    NSDate *fromDate = [dateFormatter dateFromString:fromDateString];
    
    NSDateComponents *components = [currentCalendar components:NSCalendarUnitWeekday fromDate:fromDate];
    components.weekday = 4;// sunday = 1 saturday = 7
    components.hour = 23;
    components.minute = 30;
    components.timeZone = [NSTimeZone systemTimeZone];
    
    UNCalendarNotificationTrigger *trigger = [UNCalendarNotificationTrigger triggerWithDateMatchingComponents:components repeats:YES];
    NSLog(@"next Trigger Date: %@", trigger.nextTriggerDate);
    
    UNMutableNotificationContent *content = [[UNMutableNotificationContent alloc] init];
    content.title = @"This is Notification";
    content.body = @"I am his body";
    
    UNNotificationRequest *request = [UNNotificationRequest requestWithIdentifier:@"KrishnaChaitanya" content:content trigger:trigger];
    
    [[UNUserNotificationCenter currentNotificationCenter] addNotificationRequest:request withCompletionHandler:^(NSError * _Nullable error) {
        NSLog(@"error = %@", error);
    }];
}

@end
