
class _CrtDumpMemoryLeaks
{
public:
    ~_CrtDumpMemoryLeaks()
    {
        _CrtDumpMemoryLeaks();
    }

    static void DumpMemoryLeaks()
    {
        _CrtDumpMemoryLeaks();
    }

};