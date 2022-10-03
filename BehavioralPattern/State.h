/***
 * State:状态模式
 * 在一个对象的内部状态变化时改变其行为,使其看上去就像改变了自身所属的类一样
*/
#include <iostream>
#include <typeinfo>

class Context;

//State基类
class State {
protected:
    Context *context_;

public:
    virtual ~State() {
    }

    void set_context(Context *context) {
        this->context_ = context;
    }

    virtual void Handle1() = 0;

    virtual void Handle2() = 0;
};

//Context定义了客户感兴趣的接口。它还维护对 State 子类实例的引用，该实例表示 Context 的当前状态。
class Context {
    //和state相互引用
private:
    State *state_;

public:
    Context(State *state) : state_(nullptr) {
        this->TransitionTo(state);
    }

    ~Context() {
        delete state_;
    }

    //Context对象允许在运行时改变State对象
    void TransitionTo(State *state) {
        std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
        if (this->state_ != nullptr)
            delete this->state_;
        this->state_ = state;
        this->state_->set_context(this);
    }

    //Context将部分的行为委托给当前的State对象
    void Request1() {
        this->state_->Handle1();
    }

    void Request2() {
        this->state_->Handle2();
    }
};

//ConcreteState子类实现了与Context的一个状态相关的行为
class ConcreteStateA : public State {
public:
    void Handle1() override;

    void Handle2() override {
        std::cout << "ConcreteStateA handles request2.\n";
    }
};

class ConcreteStateB : public State {
public:
    void Handle1() override {
        std::cout << "ConcreteStateB handles request1.\n";
    }

    void Handle2() override {
        std::cout << "ConcreteStateB handles request2.\n";
        std::cout << "ConcreteStateB wants to change the state of the context.\n";
        this->context_->TransitionTo(new ConcreteStateA);
    }
};

void ConcreteStateA::Handle1() {
    {
        std::cout << "ConcreteStateA handles request1.\n";
        std::cout << "ConcreteStateA wants to change the state of the context.\n";

        this->context_->TransitionTo(new ConcreteStateB);
    }
}

void ClientCode() {
    Context *context = new Context(new ConcreteStateA);
    context->Request1();
    context->Request2();
    delete context;
}

int main() {
    ClientCode();
    return 0;
}