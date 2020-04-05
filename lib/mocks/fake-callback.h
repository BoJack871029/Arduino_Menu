#include "gmock/gmock.h"

namespace test
{
namespace mocks
{
namespace
{
struct IFakeCallback
{
    virtual void exec(void *) = 0;
    virtual ~IFakeCallback() {}
};

struct FakeCallback : public IFakeCallback
{
    FakeCallback() {}
    virtual ~FakeCallback() {}
    MOCK_METHOD1(exec, void(void *));
};

void fakeCallback(void *iInput)
{
    mocks::FakeCallback *aMock = (mocks::FakeCallback *)iInput;
    aMock->exec(NULL);
}

void emptyCallback(void *)
{
}
} // namespace
} // namespace mocks
} // namespace test
