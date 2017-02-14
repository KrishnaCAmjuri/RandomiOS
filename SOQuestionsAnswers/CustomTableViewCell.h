//
//  CustomTableViewCell.h
//  SOQuestionsAnswers
//
//  Created by KrishnaChaitanya Amjuri on 07/01/17.
//  Copyright © 2017 Krishna Chaitanya. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol CustomCellProtocol <NSObject>

- (void)passButtonSelected:(BOOL)selected forIndexPath:(NSIndexPath *)indexPath;

@end

@interface CustomTableViewCell : UITableViewCell

@property (nonatomic, weak) id<CustomCellProtocol> cellDelegate;

@property (nonatomic) NSIndexPath *indexPath;

@property (nonatomic) NSMutableArray *buttonStatusModelArray;

@end
