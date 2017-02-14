//
//  WFCollectionView.m
//  SOQuestionsAnswers
//
//  Created by KrishnaChaitanya Amjuri on 13/02/17.
//  Copyright © 2017 Krishna Chaitanya. All rights reserved.
//

#import "WFCollectionView.h"

@interface WFCollectionView ()

@property(nonatomic) NSArray *collectionArray;

@end

@implementation WFCollectionView

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

- (instancetype)initWithFrame:(CGRect)frame collectionViewLayout:(UICollectionViewLayout *)layout {
    
    self = [super initWithFrame:frame collectionViewLayout:layout];
    
    if (self) {
        self.delegate = self;
        self.dataSource = self;
        self.collectionArray = @[[UIColor redColor], [UIColor blueColor], [UIColor greenColor], [UIColor yellowColor], [UIColor orangeColor], [UIColor blackColor], [UIColor brownColor], [UIColor magentaColor]];
        [self registerClass:[UICollectionViewCell class] forCellWithReuseIdentifier:@"reuse"];
    }
    
    return self;
}

#pragma mark - DataSource

- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView {
    
    return 1;
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
   
    return self.collectionArray.count;
}

- (__kindof UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    
    UICollectionViewCell *collectionCell = [self dequeueReusableCellWithReuseIdentifier:@"reuse" forIndexPath:indexPath];
    collectionCell.backgroundColor = [self.collectionArray objectAtIndex:indexPath.row];
    return collectionCell;
}

#pragma mark - delegate

@end
