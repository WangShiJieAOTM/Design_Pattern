/***
 * Mediator:中介者模式
 * 限制对象之间的直接交互,迫使他们通过一个中介者对象进行合作
*/
#include <iostream>
#include <string>

//Mediator 接口声明了一个组件用来通知中介各种事件的方法。 Mediator 可以对这些事件做出反应并将执行传递给其他组件。
class BaseComponent;

class Mediator {
public:
    virtual void Notify(BaseComponent *sender, std::string event) const = 0;
};

//基本组件提供了将中介实例存储在组件对象中的基本功能。
class BaseComponent {
protected:
    Mediator *mediator_;

public:
    BaseComponent(Mediator *mediator = nullptr) : mediator_(mediator) {
    }

    void set_mediator(Mediator *mediator) {
        this->mediator_ = mediator;
    }
};

//具体组件实现各种功能。它们不依赖于其他组件。它们也不依赖于任何具体的中介类。
class Component1 : public BaseComponent {
public:
    void DoA() {
        std::cout << "Component 1 does A.\n";
        this->mediator_->Notify(this, "A");
    }

    void DoB() {
        std::cout << "Component 1 does B.\n";
        this->mediator_->Notify(this, "B");
    }
};

class Component2 : public BaseComponent {
public:
    void DoC() {
        std::cout << "Component 2 does C.\n";
        this->mediator_->Notify(this, "C");
    }

    void DoD() {
        std::cout << "Component 2 does D.\n";
        this->mediator_->Notify(this, "D");
    }
};

//具体中介者通过协调多个组件来实现合作行为。
class ConcreteMediator : public Mediator {
private:
    Component1 *component1_;
    Component2 *component2_;

public:
    ConcreteMediator(Component1 *c1, Component2 *c2) : component1_(c1), component2_(c2) {
        this->component1_->set_mediator(this);
        this->component2_->set_mediator(this);
    }

    void Notify(BaseComponent *sender, std::string event) const override {
        if (event == "A") {
            std::cout << "Mediator reacts on A and triggers following operations:\n";
            this->component2_->DoC();
        }
        if (event == "D") {
            std::cout << "Mediator reacts on D and triggers following operations:\n";
            this->component1_->DoB();
            this->component2_->DoC();
        }
    }
};

void ClientCode() {
    Component1 *c1 = new Component1;
    Component2 *c2 = new Component2;
    ConcreteMediator *mediator = new ConcreteMediator(c1, c2);
    std::cout << "Client triggers operation A.\n";
    c1->DoA();
    std::cout << "\n";
    std::cout << "Client triggers operation D.\n";
    c2->DoD();

    delete c1;
    delete c2;
    delete mediator;
}

int main() {
    ClientCode();
    return 0;
}