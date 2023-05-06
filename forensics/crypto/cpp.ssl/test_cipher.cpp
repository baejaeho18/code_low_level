#include "cipher.h"

#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
class CipherTest: public testing::Test
{
protected:
  virtual void SetUp()
  {
  }

  virtual void TearDown()
  {
  }
};

TEST_F(CipherTest, AESCBC256)
{
  OpenSSL::Cipher aes("aes-256-cbc");

  EXPECT_EQ(aes.ok(), true);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////