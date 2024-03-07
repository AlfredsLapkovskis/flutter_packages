// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#import "FVPVideoPlayerPlugin.h"

#import <AVFoundation/AVFoundation.h>

#import "FVPDisplayLink.h"
#import "messages.g.h"

// Protocol for AVFoundation object instance factory. Used for injecting framework objects in tests.
@protocol FVPAVFactory
@required
- (AVPlayer *)playerWithPlayerItem:(AVPlayerItem *)playerItem;
- (AVPlayerItemVideoOutput *)videoOutputWithPixelBufferAttributes:
    (NSDictionary<NSString *, id> *)attributes;
@end

// Protocol for an AVPlayer instance factory. Used for injecting display links in tests.
@protocol FVPDisplayLinkFactory
- (FVPDisplayLink *)displayLinkWithRegistrar:(id<FlutterPluginRegistrar>)registrar
                                    callback:(void (^)(void))callback;
@end

#pragma mark -

// TODO(stuartmorgan): Move this whole class to its own files.
@interface FVPVideoPlayer : NSObject <FlutterStreamHandler, FlutterTexture>
@property(readonly, nonatomic) AVPlayer *player;
@property(readonly, nonatomic) int64_t position;

- (void)onTextureUnregistered:(NSObject<FlutterTexture> *)texture;
@end

#pragma mark -

@interface FVPVideoPlayerPlugin () <FVPAVFoundationVideoPlayerApi>

@property(readonly, strong, nonatomic)
    NSMutableDictionary<NSNumber *, FVPVideoPlayer *> *playersByTextureId;

- (instancetype)initWithAVFactory:(id<FVPAVFactory>)avFactory
               displayLinkFactory:(id<FVPDisplayLinkFactory>)displayLinkFactory
                        registrar:(NSObject<FlutterPluginRegistrar> *)registrar;

@end
