//
//  BLWordSuggestions.h
//  Bobble
//
//  Created by KrishnaChaitanya Amjuri on 13/02/17.
//  Copyright © 2017 Touchtalent. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BLWordSuggestions : NSObject

- (instancetype)initWithDicFilePath:(NSString *)dicFilePathString withProximityFiles:(NSArray *)proxmFiles;

- (NSArray *)getSuggestionsForWord:(NSString *)word withPreviousWord:(NSString *)prevWord;

@end
