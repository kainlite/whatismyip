/*
 *  Copyright (c) 2016, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <proxygen/httpserver/Mocks.h>
#include "../src/EchoHandler.h"
#include "../src/EchoStats.h"

using namespace EchoService;
using namespace proxygen;
using namespace testing;

class MockEchoStats : public EchoStats {
 public:
  MOCK_METHOD0(recordRequest, void());
  MOCK_METHOD0(getRequestCount, uint64_t());
  MOCK_METHOD0(setClientIP, void());
  MOCK_METHOD0(getClientIP, std::string());
};

class EchoHandlerFixture : public testing::Test {
 public:
  void SetUp() override {
    handler = new EchoHandler(&stats);
    responseHandler = folly::make_unique<MockResponseHandler>(handler);
    handler->setResponseHandler(responseHandler.get());
  }

  void TearDown() override {
    Mock::VerifyAndClear(&stats);
    Mock::VerifyAndClear(responseHandler.get());
  }

 protected:
  EchoHandler* handler{nullptr};
  StrictMock<MockEchoStats> stats;
  std::unique_ptr<MockResponseHandler> responseHandler;
};

TEST_F(EchoHandlerFixture, SetBodyWithClientIp) {
  // EXPECT_CALL(stats, recordRequest()).WillOnce(Return());
  EXPECT_CALL(stats, getRequestCount()).WillOnce(Return(5));
  
  // EXPECT_CALL(stats, setClientIP()).WillOnce(Return());
  EXPECT_CALL(stats, getClientIP()).WillOnce(Return("::1"));

  HTTPMessage response;
  folly::fbstring body;

  EXPECT_CALL(*responseHandler, sendHeaders(_)).WillOnce(
      DoAll(SaveArg<0>(&response), Return()));

  EXPECT_CALL(*responseHandler, sendBody(_)).WillRepeatedly(
      DoAll(
          Invoke([&] (std::shared_ptr<folly::IOBuf> b) {
            body += b->moveToFbString();
          }),
          Return()));

  EXPECT_CALL(*responseHandler, sendEOM()).WillOnce(Return());

  // Since we know we dont touch request, its ok to pass `nullptr` here.
  // handler->onRequest(nullptr);
  handler->onBody(folly::IOBuf::copyBuffer("::1"));
  handler->onEOM();
  handler->requestComplete();

  EXPECT_EQ("5", response.getHeaders().getSingleOrEmpty("Request-Number"));
  EXPECT_EQ("::1", body);
  EXPECT_EQ(200, response.getStatusCode());
}
