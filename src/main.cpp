#include <framework/win/seadGameFrameworkWinGL.h>

#include <RootTask.h>

const u32 cWidth = 1280;
const u32 cHeight = 720;

int main()
{
    //* Init sead
    {
        sead::Framework::InitializeArg arg;
        arg.heap_size = 100 * 1024 * 1024; // 100 MiB

        sead::GameFrameworkWinGL::initialize(arg);
    }

    sead::Heap* heap = sead::HeapMgr::instance()->getRootHeap(0);

    //* Init app framework
    sead::GameFrameworkWinGL* fw;
    {
        sead::GameFrameworkWinGL::CreateArg arg;
        arg.window_name = "sead";
        arg.width = cWidth;
        arg.height = cHeight;

        fw = new(heap) sead::GameFrameworkWinGL(arg);

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

//? Needed for subsystem entry point (Release builds don't have a console by default)
#if defined(SEAD_PLATFORM_WINDOWS)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    return main();
}
#endif // SEAD_PLATFORM_WINDOWS
