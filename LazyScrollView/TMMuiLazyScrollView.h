//
//  TMMuiLazyScrollView.h
//  LazyScrollView
//
//  Copyright (c) 2015-2017 Alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TMMuiLazyScrollViewCellProtocol.h"
#import "TMMuiRectModel.h"

@class TMMuiLazyScrollView;


/**
 A UIView category required by LazyScrollView.
 */
@interface UIView (TMMuiLazyScrollView)

// A uniq string that identify a view, require to
// be same as muiID of the model.
@property (nonatomic, copy, nullable) NSString *muiID;
// A string used to identify a view that is reusable.
@property (nonatomic, copy, nullable) NSString *reuseIdentifier;

- (nonnull instancetype)initWithFrame:(CGRect)frame
                      reuseIdentifier:(nullable NSString *)reuseIdentifier;

@end

//****************************************************************

/**
 This protocol represents the data model object.
 */
@protocol TMMuiLazyScrollViewDataSource <NSObject>

@required

// 0 by default.
- (NSUInteger)numberOfItemInScrollView:(nonnull TMMuiLazyScrollView *)scrollView;
// Return the view model by spcial index.
- (nonnull TMMuiRectModel *)scrollView:(nonnull TMMuiLazyScrollView *)scrollView
                      rectModelAtIndex:(NSUInteger)index;
// You should render the item view here.
// You should ALWAYS try to reuse views by setting each view's reuseIdentifier.
- (nonnull UIView *)scrollView:(nonnull TMMuiLazyScrollView *)scrollView
                   itemByMuiID:(nonnull NSString *)muiID;

@end
//****************************************************************


@interface TMMuiLazyScrollView : UIScrollView

// 注意，修改 delegate 属性后需要将 scrollViewDidScroll: 事件转发回给 TangramView

@property (nonatomic, weak, nullable) id<TMMuiLazyScrollViewDataSource> dataSource;

@property (nonatomic, weak, nullable) id<UIScrollViewDelegate> forwardingDelegate;

// Default value is NO.
@property (nonatomic, assign) BOOL autoAddSubview;

// Items which has been added to LazyScrollView.
@property (nonatomic, strong, readonly, nonnull) NSSet *visibleItems;
// Items which is in the visible screen area.
// It is a sub set of "visibleItems".
@property (nonatomic, strong, readonly, nonnull) NSSet *inScreenVisibleItems;
// Tangram can be footerView for TableView, this outerScrollView is your tableview.
@property (nonatomic, weak, nullable) UIScrollView *outerScrollView;


// reloads everything from scratch and redisplays visible views.
- (void)reloadData;
// call this func to get the view update without reload the scrollView.
- (void)invalidateView:(NSUInteger) _index;
// Remove all subviews and reuseable views.
- (void)removeAllLayouts;
// trigger datasource update a view in a certain index
- (void)replaceViewAt:(NSString*) _muiID;

// Get reuseable view by reuseIdentifier. If cannot find reuseable
// view by reuseIdentifier, here will return nil.
- (nullable UIView *)dequeueReusableItemWithIdentifier:(nonnull NSString *)identifier;
// Get reuseable view by reuseIdentifier and muiID.
// MuiID has higher priority.
- (nullable UIView *)dequeueReusableItemWithIdentifier:(nonnull NSString *)identifier
                                                 muiID:(nullable NSString *)muiID;

// After call this method, the times of mui_didEnterWithTimes will start from 0
- (void)resetViewEnterTimes;

@end

//****************************************************************

@interface TMMuiLazyScrollViewObserver: NSObject
@property (nonatomic, weak, nullable) TMMuiLazyScrollView *lazyScrollView;
@end
