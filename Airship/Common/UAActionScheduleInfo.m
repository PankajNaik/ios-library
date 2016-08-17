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

#import "UAActionScheduleInfo.h"

NSUInteger const UAMaxTriggers = 10;

@implementation UAActionScheduleInfoBuilder

@end


@interface UAActionScheduleInfo()
@property(nonatomic, copy) NSDictionary *actions;
@property(nonatomic, copy) NSArray *triggers;
@property(nonatomic, copy) NSString *group;
@property(nonatomic, assign) NSUInteger limit;
@property(nonatomic, strong) NSDate *start;
@property(nonatomic, strong) NSDate *end;
@end

@implementation UAActionScheduleInfo

- (BOOL)isValid {
    if (!self.triggers.count || self.triggers.count > UAMaxTriggers) {
        return NO;
    }

    if (!self.actions.count) {
        return NO;
    }

    if ([self.start compare:self.end] == NSOrderedDescending) {
        return NO;
    }

    return YES;
}

- (instancetype)initWithBuilder:(UAActionScheduleInfoBuilder *)builder {
    self = [super self];
    if (self) {
        self.actions = [builder.actions copy] ?: @{};
        self.triggers = [builder.triggers copy] ?: @[];
        self.limit = builder.limit;
        self.group = builder.group;
        self.start = builder.start ?: [NSDate distantPast];
        self.end = builder.end ?: [NSDate distantFuture];
    }

    return self;
}

+ (instancetype)actionScheduleInfoWithBuilderBlock:(void (^)(UAActionScheduleInfoBuilder *))builderBlock {
    UAActionScheduleInfoBuilder *builder = [[UAActionScheduleInfoBuilder alloc] init];
    builder.limit = 1;

    if (builderBlock) {
        builderBlock(builder);
    }

    return [[UAActionScheduleInfo alloc] initWithBuilder:builder];
}

- (BOOL)isEqualToScheduleInfo:(UAActionScheduleInfo *)scheduleInfo {
    if (!scheduleInfo) {
        return NO;
    }

    if (self.limit != scheduleInfo.limit) {
        return NO;
    }

    if (![self.start isEqualToDate:scheduleInfo.start]) {
        return NO;
    }

    if (![self.end isEqualToDate:scheduleInfo.end]) {
        return NO;
    }

    if (self.actions != scheduleInfo.actions && ![self.actions isEqualToDictionary:scheduleInfo.actions]) {
        return NO;
    }

    if (self.triggers != scheduleInfo.triggers && ![self.triggers isEqualToArray:scheduleInfo.triggers]) {
        return NO;
    }

    if (self.group != scheduleInfo.group && ![self.group isEqualToString:scheduleInfo.group]) {
        return NO;
    }

    return YES;
}

#pragma mark - NSObject

- (BOOL)isEqual:(id)object {
    if (self == object) {
        return YES;
    }

    if (![object isKindOfClass:[UAActionScheduleInfo class]]) {
        return NO;
    }

    return [self isEqualToScheduleInfo:(UAActionScheduleInfo *)object];
}

- (NSUInteger)hash {
    NSUInteger result = 1;
    result = 31 * result + self.limit;
    result = 31 * result + [self.start hash];
    result = 31 * result + [self.end hash];
    result = 31 * result + [self.group hash];
    result = 31 * result + [self.triggers hash];
    result = 31 * result + [self.actions hash];
    return result;
}



@end
