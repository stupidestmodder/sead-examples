#include <RootTask.h>

RootTask::RootTask(const sead::TaskConstructArg& arg)
    : sead::Task(arg, "RootTask")
{
}

void RootTask::calc()
{
    SEAD_PRINT("RootTask::calc()\n");
}
