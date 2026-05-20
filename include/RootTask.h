#pragma once

#include <framework/seadTask.h>

class RootTask : public sead::Task
{
public:
    explicit RootTask(const sead::TaskConstructArg& arg);

    void calc() override;
};
