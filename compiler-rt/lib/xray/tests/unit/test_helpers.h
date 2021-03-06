//===-- test_helpers.h ----------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file is a part of XRay, a function call tracing system.
//
//===----------------------------------------------------------------------===//
#ifndef COMPILER_RT_LIB_XRAY_TESTS_TEST_HELPERS_H_
#define COMPILER_RT_LIB_XRAY_TESTS_TEST_HELPERS_H_

#include "xray_buffer_queue.h"
#include "llvm/XRay/XRayRecord.h"
#include "llvm/XRay/Trace.h"
#include "gmock/gmock.h"

// TODO: Move these to llvm/include/Testing/XRay/...
namespace llvm {
namespace xray {

std::string RecordTypeAsString(RecordTypes T);
void PrintTo(RecordTypes T, std::ostream *OS);
void PrintTo(const XRayRecord &R, std::ostream *OS);
void PrintTo(const Trace &T, std::ostream *OS);

namespace testing {

MATCHER_P(FuncId, F, "") {
  *result_listener << "where the function id is " << F;
  return arg.FuncId == F;
}

MATCHER_P(RecordType, T, "") {
  *result_listener << "where the record type is " << RecordTypeAsString(T);
  return arg.Type == T;
}

MATCHER_P(HasArg, A, "") {
  *result_listener << "where args contains " << A;
  return !arg.CallArgs.empty() &&
         std::any_of(arg.CallArgs.begin(), arg.CallArgs.end(),
                     [this](decltype(A) V) { return V == A; });
}

} // namespace testing
} // namespace xray
} // namespace llvm

namespace __xray {

std::string serialize(BufferQueue &Buffers, int32_t Version);

} // namespace __xray

#endif // COMPILER_RT_LIB_XRAY_TESTS_TEST_HELPERS_H_
