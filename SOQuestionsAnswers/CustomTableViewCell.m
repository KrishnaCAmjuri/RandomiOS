//
//  CustomTableViewCell.m
//  SOQuestionsAnswers
//
//  Created by KrishnaChaitanya Amjuri on 07/01/17.
//  Copyright © 2017 Krishna Chaitanya. All rights reserved.
//

#import "CustomTableViewCell.h"

@implementation CustomTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code

}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];
    // Configure the view for the selected state
}

- (void)passButtonSelected {
    [self.cellDelegate passButtonSelected:YES forIndexPath:self.indexPath];
}

- (void)passButtonSelected:(BOOL)selected forIndexPath:(NSIndexPath *)indexPath {
    
    NSMutableDictionary *statusDic = [[self.buttonStatusModelArray objectAtIndex:indexPath.row] mutableCopy];
    [statusDic setObject:(selected ? @"Selected" : @"NonSelected") forKey:@"P_Button"];
    
    [self.buttonStatusModelArray replaceObjectAtIndex:indexPath.row withObject:statusDic];
}


@end
