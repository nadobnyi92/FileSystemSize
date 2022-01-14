#include <vector>
#include <thread>

class Task
{
public:
    enum class State
    {
        READY,
        ACTIVE, //???
        WAIT_CHILD,
        DONE
    };

    State state() const;
    int result() const;

    void process();
    void processChild();
    void finishedChild( Task* task );

private:
    State m_state;
    size_t m_result;

    std::shred_ptr<Task> m_parent;
    std::vector< std::shared_ptr<Task> > m_children;
    std::vector<int> m_completeChildren;
}
