/**
 * @file acct.cpp
 * @author slguan (slguan@taosdata.com)
 * @brief MNODE module acct tests
 * @version 1.0
 * @date 2021-12-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "base.h"

class DndTestAcct : public ::testing::Test {
 protected:
  static void SetUpTestSuite() { test.Init("/tmp/mnode_test_acct", 9012); }
  static void TearDownTestSuite() { test.Cleanup(); }

  static Testbase test;

 public:
  void SetUp() override {}
  void TearDown() override {}
};

Testbase DndTestAcct::test;

TEST_F(DndTestAcct, 01_CreateAcct) {
  int32_t contLen = sizeof(SCreateAcctReq);

  SCreateAcctReq* pReq = (SCreateAcctReq*)rpcMallocCont(contLen);

  SRpcMsg* pMsg = test.SendMsg(TDMT_MND_CREATE_ACCT, pReq, contLen);
  ASSERT_NE(pMsg, nullptr);
  ASSERT_EQ(pMsg->code, TSDB_CODE_MND_MSG_NOT_PROCESSED);
}

TEST_F(DndTestAcct, 02_AlterAcct) {
  int32_t contLen = sizeof(SCreateAcctReq);

  SAlterAcctReq* pReq = (SAlterAcctReq*)rpcMallocCont(contLen);

  SRpcMsg* pMsg = test.SendMsg(TDMT_MND_ALTER_ACCT, pReq, contLen);
  ASSERT_NE(pMsg, nullptr);
  ASSERT_EQ(pMsg->code, TSDB_CODE_MND_MSG_NOT_PROCESSED);
}

TEST_F(DndTestAcct, 03_DropAcct) {
  int32_t contLen = sizeof(SDropAcctReq);

  SDropAcctReq* pReq = (SDropAcctReq*)rpcMallocCont(contLen);

  SRpcMsg* pMsg = test.SendMsg(TDMT_MND_DROP_ACCT, pReq, contLen);
  ASSERT_NE(pMsg, nullptr);
  ASSERT_EQ(pMsg->code, TSDB_CODE_MND_MSG_NOT_PROCESSED);
}

TEST_F(DndTestAcct, 04_ShowAcct) {
  int32_t contLen = sizeof(SShowMsg);

  SShowMsg* pReq = (SShowMsg*)rpcMallocCont(contLen);
  pReq->type = TSDB_MGMT_TABLE_ACCT;

  SRpcMsg* pMsg = test.SendMsg(TDMT_MND_SHOW, pReq, contLen);
  ASSERT_NE(pMsg, nullptr);
  ASSERT_EQ(pMsg->code, TSDB_CODE_MND_INVALID_MSG_TYPE);
}