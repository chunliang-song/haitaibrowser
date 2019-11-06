// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "remoting/protocol/channel_dispatcher_base.h"

#include <utility>

#include "base/bind.h"
#include "remoting/base/compound_buffer.h"
#include "remoting/protocol/message_channel_factory.h"
#include "remoting/protocol/message_pipe.h"

namespace remoting {
namespace protocol {

ChannelDispatcherBase::ChannelDispatcherBase(const char* channel_name)
    : channel_name_(channel_name) {}

ChannelDispatcherBase::~ChannelDispatcherBase() {
  if (channel_factory_)
    channel_factory_->CancelChannelCreation(channel_name_);
}

void ChannelDispatcherBase::Init(MessageChannelFactory* channel_factory,
                                 EventHandler* event_handler) {
  channel_factory_ = channel_factory;
  event_handler_ = event_handler;

  channel_factory_->CreateChannel(channel_name_, base::Bind(
      &ChannelDispatcherBase::OnChannelReady, base::Unretained(this)));
}

void ChannelDispatcherBase::OnChannelReady(
    std::unique_ptr<MessagePipe> message_pipe) {
  channel_factory_ = nullptr;
  message_pipe_ = std::move(message_pipe);
  message_pipe_->StartReceiving(base::Bind(
      &ChannelDispatcherBase::OnIncomingMessage, base::Unretained(this)));

  event_handler_->OnChannelInitialized(this);
}

}  // namespace protocol
}  // namespace remoting