// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/platform/wtf/threading_primitives.h"

#include "base/bind.h"
#include "base/synchronization/waitable_event.h"
#include "base/threading/scoped_blocking_call.h"
#include "base/threading/thread.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "third_party/blink/renderer/platform/wtf/time.h"

namespace WTF {
namespace {

class MockBlockingObserver : public base::internal::BlockingObserver {
 public:
  // base::internal::BlockingObserver
  MOCK_METHOD1(BlockingStarted, void(base::BlockingType));
  MOCK_METHOD0(BlockingTypeUpgraded, void());
  MOCK_METHOD0(BlockingEnded, void());
};

class ThreadConditionTest : public testing::Test {
 public:
  ThreadConditionTest() : condition_(mutex_) {}

  void RunOtherThreadInfiniteWait() {
    base::internal::SetBlockingObserverForCurrentThread(&observer_);
    MutexLocker lock(mutex_);
    ready_.Signal();
    condition_.Wait();
  }

 protected:
  base::WaitableEvent ready_;
  testing::StrictMock<MockBlockingObserver> observer_;
  Mutex mutex_;
  ThreadCondition condition_;
};

// TODO(https://crbug.com/897550): Test often flakes on its first run, only
// passing when retried by the TestLauncher.
TEST_F(ThreadConditionTest, DISABLED_WaitReportsBlockingCall) {
  EXPECT_CALL(observer_, BlockingStarted(base::BlockingType::MAY_BLOCK));
  EXPECT_CALL(observer_, BlockingEnded());

  base::Thread other_thread("other thread");
  other_thread.StartAndWaitForTesting();
  other_thread.task_runner()->PostTask(
      FROM_HERE,
      base::BindOnce(&ThreadConditionTest::RunOtherThreadInfiniteWait,
                     base::Unretained(this)));

  ready_.Wait();
  MutexLocker lock(mutex_);
  condition_.Signal();
}

}  // namespace
}  // namespace WTF
