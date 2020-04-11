#include <task-runner.h>

task::TaskRunner::TaskRunner(long iStartTime, void (*iTask)(void *), void *iResourceManager)
{
    _lastExecution= _startTime = iStartTime;
    _task = iTask;
    _resourceManager = iResourceManager;
}

void task::TaskRunner::run(long iCurrentTime, int iInterval)
{
    if ((iCurrentTime - _lastExecution) >= iInterval)
    {
        _task(_resourceManager);
        _lastExecution = iCurrentTime;
    }
}

long task::TaskRunner::getLastExecution()
{
    return _lastExecution;
}