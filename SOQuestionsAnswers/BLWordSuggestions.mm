//
//  BLWordSuggestions.m
//  Bobble
//
//  Created by KrishnaChaitanya Amjuri on 13/02/17.
//  Copyright © 2017 Touchtalent. All rights reserved.
//

#import "BLWordSuggestions.h"
#import "Word_Suggestion_CPP/libDict/suggest/core/suggest_options.h"
#import "Word_Suggestion_CPP/libDict/suggest/core/dictionary/dictionary.h"
#import "Word_Suggestion_CPP/libDict/suggest/core/layout/proximity_info.h"
#import "Word_Suggestion_CPP/libDict/suggest/policyimpl/typing/typing_suggest_policy.h"
#import "Word_Suggestion_CPP/libDict/suggest/core/session/prev_words_info.h"
#import "Word_Suggestion_CPP/libDict/suggest/core/suggest_options.h"
#import "Word_Suggestion_CPP/libDict/suggest/core/session/prev_words_info.h"
#import "Word_Suggestion_CPP/libDict/suggest/core/suggest_options.h"
#import "SuggestionProvider.h"
#import "FileUtils.h"

#define MAX_WORD_LENGTH 48
#define SUGGESTION_COUNT 3

@interface BLWordSuggestions ()
{
    SuggestionProvider *suggestor;
    latinime::SuggestOptions *suggestOptions;
}
@end

@implementation BLWordSuggestions

- (instancetype)initWithDicFilePath:(NSString *)dicFilePathString withProximityFiles:(NSArray *)proxmFiles {
    
    self = [super init];
    
    if (self) {
        std::string dicPath = [dicFilePathString cStringUsingEncoding:NSUTF8StringEncoding];
       
        std::vector<std::string> proxmPathVector;
        
        for (int i = 0; i < proxmFiles.count; i++) {
            NSString *proxmFile = proxmFiles[i];
            std::string proxmPath = [proxmFile cStringUsingEncoding:NSUTF8StringEncoding];
            proxmPathVector.push_back(proxmPath);
        }
        
        int suggestOptionsFlags[] = {0, /* IS_GESTURE */
            0, /* USE_FULL_EDIT_DISTANCE */
            0, /* BLOCK_OFFENSIVE_WORDS */
            0  /* SPACE_AWARE_GESTURE_ENABLED */};
                
        suggestOptions = new latinime::SuggestOptions(suggestOptionsFlags, 4);
        suggestor = new SuggestionProvider(dicPath, proxmPathVector);
    }
    
    return self;
}

- (NSArray *)getSuggestionsForWord:(NSString *)word withPreviousWord:(NSString *)prevWord {
    
    prevWord = @"";
    
    const char *wordStr = [word cStringUsingEncoding:NSUTF8StringEncoding];
    const char *prevWordStr = [prevWord cStringUsingEncoding:NSUTF8StringEncoding];
    
    int prevWordCodePoints[prevWord.length];
    int inputCodePoints[word.length];
    
    for (int i = 0; i < word.length; i++) {
        inputCodePoints[i] = -1;
    }
    
    bool isBeginningOfSentence = NO;//(prevWord.length == 0);
    std::vector<std::string> suggestionsVector;
    
    for (int i = 0; i < prevWord.length; i++) {
        prevWordCodePoints[i] = prevWordStr[i];
    }
    
    for (int i = 0; i < word.length; i++) {
        inputCodePoints[i] = wordStr[i];
    }

    int prevWordlngth = (int)prevWord.length;
    int wordlngth = (int)word.length;
    
    latinime::PrevWordsInfo *prevWordsInfo = new latinime::PrevWordsInfo(prevWordCodePoints, prevWordlngth, isBeginningOfSentence);

    suggestionsVector = suggestor->getSuggestions(3, inputCodePoints, wordlngth, prevWordsInfo, suggestOptions);
    
    NSMutableArray *suggestionsArray = [NSMutableArray array];
    for (int i = 0; i < suggestionsVector.size(); i++) {
        const char* suggstStr = suggestionsVector[i].c_str();
        NSString *suggestion = [NSString stringWithUTF8String:suggstStr];
        if (suggestion != nil) {
            [suggestionsArray addObject:suggestion];
        }
    }
    
    return suggestionsArray;
}

@end
