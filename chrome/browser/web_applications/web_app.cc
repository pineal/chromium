// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/web_applications/web_app.h"

namespace web_app {

WebApp::WebApp(const AppId& app_id) : app_id_(app_id) {}

WebApp::~WebApp() = default;

void WebApp::SetName(const std::string& name) {
  name_ = name;
}

void WebApp::SetDescription(const std::string& description) {
  description_ = description;
}

void WebApp::SetLaunchUrl(const std::string& launch_url) {
  launch_url_ = launch_url;
}

}  // namespace web_app
