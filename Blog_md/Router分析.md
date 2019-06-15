```
void
Router::wakeup()
{
    DPRINTF(RubyNetwork, "Router %d woke up\n", m_id);//类似printf函数输出信息

// 92     std::vector<InputUnit *> m_input_unit;
// 93     std::vector<OutputUnit *> m_output_unit;

    // check for incoming flits  //定义InputUnit类，并开始调用它的wakeup函数
    for (int inport = 0; inport < m_input_unit.size(); inport++) {
        m_input_unit[inport]->wakeup();
    }   
    // 定义OutputUnit类，并开始调用它的wakeup函数
    // check for incoming credits
    // Note: the credit update is happening before SA
    // buffer turnaround time =
    //     credit traversal (1-cycle) + SA (1-cycle) + Link Traversal (1-cycle)
    // if we want the credit update to take place after SA, this loop should
    // be moved after the SA request
    for (int outport = 0; outport < m_output_unit.size(); outport++) {
        m_output_unit[outport]->wakeup();
    }   

    // Switch Allocation
    m_sw_alloc->wakeup();

    // Switch Traversal
    m_switch->wakeup();
}

```
router初始化后，wakeup函数中依次初始化的是

①InputUnit.cc->wakeup
②OutputUnit.cc->wakeup
③SwitchAllocator.cc->wakeup
④CrossbarSwitch.cc->wakeup

```
//
// DPRINTF is a debugging trace facility that allows one to
// selectively enable tracing statements.  To use DPRINTF, there must
// be a function or functor called name() that returns a const
// std::string & in the current scope.
//
// If you desire that the automatic printing not occur, use DPRINTFR
// (R for raw)
//

#if TRACING_ON

#define DTRACE(x) (Debug::x)

#define DDUMP(x, data, count) do {                                        \
    using namespace Debug;                                                \
    if (DTRACE(x))                                                        \
        Trace::getDebugLogger()->dump(curTick(), name(), data, count);    \
} while (0)

#define DPRINTF(x, ...) do {                                              \
    using namespace Debug;                                                \
    if (DTRACE(x)) {                                                      \
        Trace::getDebugLogger()->dprintf(curTick(), name(),               \
            __VA_ARGS__);                                                 \
    }                                                                     \
} while (0)

#define DPRINTFS(x, s, ...) do {                                          \
    using namespace Debug;                                                \
    if (DTRACE(x)) {                                                      \
        Trace::getDebugLogger()->dprintf(curTick(), s->name(),            \
            __VA_ARGS__);                                                 \
    }                                                                     \
} while (0)

#define DPRINTFR(x, ...) do {                                             \
    using namespace Debug;                                                \
    if (DTRACE(x)) {                                                      \
        Trace::getDebugLogger()->dprintf((Tick)-1, std::string(),         \
            __VA_ARGS__);                                                 \
    }                                                                     \
} while (0)

#define DDUMPN(data, count) do {                                          \
    Trace::getDebugLogger()->dump(curTick(), name(), data, count);        \
} while (0)

#define DPRINTFN(...) do {                                                \
    Trace::getDebugLogger()->dprintf(curTick(), name(), __VA_ARGS__);     \
} while (0)

#define DPRINTFNR(...) do {                                               \
    Trace::getDebugLogger()->dprintf((Tick)-1, string(), __VA_ARGS__);    \
} while (0)

#else // !TRACING_ON

#define DTRACE(x) (false)
#define DDUMP(x, data, count) do {} while (0)
#define DPRINTF(x, ...) do {} while (0)
#define DPRINTFS(x, ...) do {} while (0)
#define DPRINTFR(...) do {} while (0)
#define DDUMPN(data, count) do {} while (0)
#define DPRINTFN(...) do {} while (0)
#define DPRINTFNR(...) do {} while (0)

#endif  // TRACING_ON


```
