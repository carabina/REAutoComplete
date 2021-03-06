//
//  UITextField+REAutoComplete.h
//  Pods
//
//  Created by Rinat Enikeev on 25/07/16.
//
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class REAutoComplete;

@protocol REAutoCompleteItem <NSObject>
- (NSString *)autoCompleteText;
@end

@protocol REAutoCompleteDataSource <NSObject>
- (void)autoComplete:(REAutoComplete*)autoComplete suggestionsFor:(NSString*)query whenReady:(void (^)(NSArray<id<REAutoCompleteItem>>* suggestions))callback;
@end

@protocol REAutoCompleteAlgorithm <NSObject>
- (void)suggestionsFor:(NSString*)query whenReady:(void (^)(NSArray<id<REAutoCompleteItem>>* suggestions))callback;
@optional
- (instancetype)initWithSuggestions:(NSArray<id<REAutoCompleteItem>>*)suggestions;
@end

@protocol REAutoCompleteDelegate <UITextFieldDelegate>

- (void)autoComplete:(REAutoComplete*)autoComplete didSelectObject:(id<REAutoCompleteItem>)object;

@optional

- (void)autoCompleteWillAppear:(REAutoComplete*)autoComplete;
- (void)autoCompleteWillDissapear:(REAutoComplete*)autoComplete;

// cell
- (void)autoComplete:(REAutoComplete*)autoComplete configureCell:(UITableViewCell *)cell withObject:(id<REAutoCompleteItem>)object;
- (CGFloat)autoComplete:(REAutoComplete*)autocomplete heightForRowAtIndexPath:(NSIndexPath *)indexPath;

@end

NS_CLASS_AVAILABLE_IOS(8_0) @interface REAutoComplete : NSObject<UITextFieldDelegate>

// all UITextField delegate calls will be forwarded to this delegate 
@property (strong, nonatomic) id<REAutoCompleteDelegate> delegate;

// use either dataSource or algorithm
@property (strong, nonatomic) id<REAutoCompleteDataSource> dataSource;
@property (strong, nonatomic) id<REAutoCompleteAlgorithm> algorithm;

@property (weak, nonatomic, readonly) UITextField* textField;
@property (assign, nonatomic) NSUInteger minimumCharacters;

// Appearance
@property (assign, nonatomic) BOOL keyboardAccessory;
@property (assign, nonatomic) BOOL showAlways;

@property (assign, nonatomic) BOOL tableViewAutoHeight;
@property (strong, nonatomic, readonly) UITableView *tableView;
@property (assign, nonatomic) CGFloat tableViewHeight;
@property (assign, nonatomic) CGRect tableViewFrame;
@property (assign, nonatomic) CGFloat tableViewTopMargin;
@property (assign, nonatomic) CGFloat tableViewBottomMargin;

@property (strong, nonatomic) NSString* cellReuseIdentifier;
@property (assign, nonatomic) BOOL tableViewCellApplyBoldEffect;
@property (strong, nonatomic) UIColor* tableViewCellTextColor;

@end

@interface UITextField(REAutoComplete)

@property (strong, nonatomic, nonnull, readonly) REAutoComplete* autoComplete;

@end

NS_ASSUME_NONNULL_END
