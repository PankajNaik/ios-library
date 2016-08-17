/*
 Copyright 2009-2016 Urban Airship Inc. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE URBAN AIRSHIP INC ``AS IS'' AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 EVENT SHALL URBAN AIRSHIP INC OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Possible trigger types.
 */
typedef NS_ENUM(NSInteger, UAScheduleTriggerType) {
    /**
     * Foreground trigger.
     */
    UAScheduleTriggerAppForeground,

    /**
     * Background trigger.
     */
    UAScheduleTriggerAppBackground,

    /**
     * Region enter trigger.
     */
    UAScheduleTriggerRegionEnter,

    /**
     * Region exit trigger.
     */
    UAScheduleTriggerRegionExit,

    /**
     * Custom event count trigger.
     */
    UAScheduleTriggerCustomEventCount,

    /**
     * Custom event value trigger.
     */
    UAScheduleTriggerCustomEventValue,

    /**
     * Screen trigger.
     */
    UAScheduleTriggerScreen
};


@interface UAScheduleTrigger: NSObject

/**
 * The trigger type.
 */
@property(nonatomic, readonly) UAScheduleTriggerType type;

/**
 * The trigger's goal. Once the goal is reached it will cause the schedule
 * to execute its actions.
 */
@property(nonatomic, readonly) NSNumber *goal;

/**
 * Factory method to create a foreground trigger.
 *
 * @param count Number of foregrounds before firing the trigger.
 * @return A foreground trigger.
 */
+ (instancetype)foregroundTriggerWithCount:(NSUInteger)count;


/**
 * Factory method to create a background trigger.
 *
 * @param count Number of backgrounds before firing the trigger.
 * @return A background trigger.
 */
+ (instancetype)backgroundTriggerWithCount:(NSUInteger)count;

/**
 * Factory method to create a region enter trigger.
 *
 * @param regionID Source ID of the region.
 * @param count Number of region enters before firing the trigger.
 * @return A region enter trigger.
 */
+ (instancetype)regionEnterTriggerForRegionID:(NSString *)regionID
                                        count:(NSUInteger)count;

/**
 * Factory method to create a region exit trigger.
 *
 * @param regionID Source ID of the region.
 * @param count Number of region exits before firing the trigger.
 * @return A region exit trigger.
 */
+ (instancetype)regionExitTriggerForRegionID:(NSString *)regionID
                                       count:(NSUInteger)count;

/**
 * Factory method to create a screen trigger.
 *
 * @param screenName Name of the screen.
 * @param count Number of screen enters before firing the trigger.
 * @return A screen trigger.
 */
+ (instancetype)screenTriggerForScreenName:(NSString *)screenName
                                     count:(NSUInteger)count;

/**
 * Factory method to create a custom event count trigger.
 *
 * @param predicateFormat Custom event predicate to filter out events that are applied
 * to the trigger's count.
 * @param count Number of custom event counts before firing the trigger.
 * @return A custom event count trigger.
 */
+ (instancetype)customEventTriggerWithPredicateFormat:(NSString *)predicateFormat
                                                count:(NSUInteger)count;

/**
 * Factory method to create a custom event value trigger.
 *
 * @param predicateFormat Custom event predicate to filter out events that are applied
 * to the trigger's value.
 * @param value Aggregate custom event value before firing the trigger.
 * @return A custom event value trigger.
 */
+ (instancetype)customEventTriggerWithPredicateFormat:(NSString *)predicateFormat
                                                value:(NSNumber *)value;


/**
 * Checks if the trigger is equal to another trigger.
 *
 * @param trigger The other trigger info to compare against.
 * @return `YES` if the triggers are equal, otherwise `NO`.
 */
- (BOOL)isEqualToTrigger:(nullable UAScheduleTrigger *)trigger;

@end

NS_ASSUME_NONNULL_END

