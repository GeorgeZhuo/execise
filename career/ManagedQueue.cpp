#include <vector>
#include <algorithm>

struct node {
    
    int u_id;
    Task task;
}

struct user {
    
    int u_id;
    double ratio;
    int task_size;
    int dequeue_size;
};

class ManagedQueue {
public:
    ManagedQueue();
     ~ManagedQueue();

    void Dequeue(Task task, int u_id);
    Task Enqueue();
    void  decise_dequeue();
    bool cmp(const user a, const user b);
private:
    vector<node> Queue;
    vector<user> User;
};

bool ManagedQueue::cmp(const user a, const user b) {

    int x = a.task_size * a.ratio - a.dequeue_size;
    int y = b.task_size * b.ratio - b.dequeue_size;

    return x > y;
}

void  ManagedQueue::decise_dequeue() {
    
    sort(User.begin(), User.end(), cmp);
    
}
Task ManagedQueue::Dequeue() {
    
    decise_dequeue();
    node temp = Queue[0];
    
    vector<node> iterator:: it;
    it = Queue.find(temp);
    Queue.erase(it);
    
    return temp;
}
