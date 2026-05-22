#if defined(SEAD_PLATFORM_GLFW)
#include <framework/glfw/seadGameFrameworkGlfwGL.h>
#elif defined(SEAD_PLATFORM_WINDOWS)
#include <framework/win/seadGameFrameworkWinGL.h>
#endif // SEAD_PLATFORM

#include <heap/seadExpHeap.h>

#include <RootTask.h>

const u32 cWidth = 1280;
const u32 cHeight = 720;

#if defined(SEAD_PLATFORM_GLFW)
using AppFramework = sead::GameFrameworkGlfwGL;
#elif defined(SEAD_PLATFORM_WINDOWS)
using AppFramework = sead::GameFrameworkWinGL;
#endif // SEAD_PLATFORM

int main()
{
    //* Init sead
    {
        sead::Framework::InitializeArg arg;
        arg.heap_size = 100 * 1024 * 1024; // 100 MiB

        AppFramework::initialize(arg);
    }

    sead::Heap* heap = sead::HeapMgr::instance()->getRootHeap(0);

    //* Create heap for other threads
    {
        sead::ExpHeap* h = sead::ExpHeap::create(50 * 1024 * 1024, "NonSeadThreadHeap", heap, sead::Heap::HeapDirection::eForward, true);
        sead::HeapMgr::instance()->setAllocFromNotSeadThreadHeap(h);
    }

    //* Init app framework
    AppFramework* fw;
    {
        AppFramework::CreateArg arg;
        arg.window_name = "sead";
        arg.width = cWidth;
        arg.height = cHeight;
        arg.clear_color = sead::Color4f(0.0f, 0.0f, 0.3f, 1.0f);

        fw = new(heap) AppFramework(arg);

        fw->initializeGraphicsSystem(heap, sead::Vector2f(cWidth, cHeight));
    }

    //* Run app framework
    {
        sead::TaskBase::CreateArg taskArg(&sead::TTaskFactory<RootTask>);
        sead::Framework::RunArg runArg;

        fw->run(heap, taskArg, runArg);
    }

    delete fw;
}
