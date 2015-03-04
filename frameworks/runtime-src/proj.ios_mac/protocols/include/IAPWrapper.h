//
//  IAPWrapper.h
//  PluginProtocol
//
//  Created by cocos2dx on 14-9-9.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface IAPWrapper : NSObject

+ (void)getPayOrderId:(NSMutableDictionary*)orderInfo target:(id)target action:(SEL)action;

+ (NSMutableDictionary*) getOrderInfo:(NSMutableDictionary*)productInfo userID:(NSString*)user;

typedef enum{
    PAYRESULT_SUCCESS = 0,
    PAYRESULT_FAIL,
    PAYRESULT_CANCEL,
    PAYRESULT_NETWORK_ERROR,
    PAYRESULT_PRODUCTIONINFOR_INCOMPLETE,
    PAYRESULT_INIT_SUCCESS,
    PAYRESULT_INIT_FAIL,
    PAYRESULT_NOW_PAYING,
    PAYRESULT_RECHARGE_SUCCESS
} PAY_RESULT;

+ (void)onPayResult:(id)pPlugin retCode:(int)ret retMsg:(NSString*)msg;
+ (void)onPayResult:(id)pPlugin retCode:(int)ret products:(NSMutableDictionary*)products;

@end
