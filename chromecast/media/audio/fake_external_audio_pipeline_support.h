// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_MEDIA_AUDIO_FAKE_EXTERNAL_AUDIO_PIPELINE_SUPPORT_H
#define CHROMECAST_MEDIA_AUDIO_FAKE_EXTERNAL_AUDIO_PIPELINE_SUPPORT_H

namespace chromecast {
namespace media {
namespace testing {

// Interface class for fake external pipeline library to interact with the
// library from unit tests.
class FakeExternalAudioPipelineSupport {
 public:
  virtual void SetSupported() = 0;
  virtual void Reset() = 0;
  // Get last received values.
  virtual float GetVolume() const = 0;
  virtual bool IsMuted() const = 0;
  // Request for change values.
  virtual void OnVolumeChangeRequest(float level) = 0;
  virtual void OnMuteChangeRequest(bool muted) = 0;

  virtual ~FakeExternalAudioPipelineSupport() {}
};

FakeExternalAudioPipelineSupport* GetFakeExternalAudioPipelineSupport();

}  // namespace testing
}  // namespace media
}  // namespace chromecast

#endif  // CHROMECAST_MEDIA_AUDIO_FAKE_EXTERNAL_AUDIO_PIPELINE_SUPPORT_H
