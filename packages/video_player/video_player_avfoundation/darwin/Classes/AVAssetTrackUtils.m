// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#import <AVFoundation/AVFoundation.h>

int FVPGetOrientationForTrack(AVAssetTrack *track) {
  CGAffineTransform t = track.preferredTransform;
  // Each case of control flows corresponds to a specific
  // `UIImageOrientation`, with 8 cases in total.
  if (t.a == 1 && t.b == 0 && t.c == 0 && t.d == 1) {
    return kCGImagePropertyOrientationUp;
  } else if (t.a == -1 && t.b == 0 && t.c == 0 && t.d == -1) {
    return kCGImagePropertyOrientationDown;
  } else if (t.a == 0 && t.b == -1 && t.c == 1 && t.d == 0) {
    return kCGImagePropertyOrientationLeft;
  } else if (t.a == 0 && t.b == 1 && t.c == -1 && t.d == 0) {
    return kCGImagePropertyOrientationRight;
  } else if (t.a == -1 && t.b == 0 && t.c == 0 && t.d == 1) {
    return kCGImagePropertyOrientationUpMirrored;
  } else if (t.a == 1 && t.b == 0 && t.c == 0 && t.d == -1) {
    return kCGImagePropertyOrientationDownMirrored;
  } else if (t.a == 0 && t.b == -1 && t.c == -1 && t.d == 0) {
    return kCGImagePropertyOrientationLeftMirrored;
  } else if (t.a == 0 && t.b == 1 && t.c == 1 && t.d == 0) {
    return kCGImagePropertyOrientationRightMirrored;
  }
  return kCGImagePropertyOrientationUp;
}
