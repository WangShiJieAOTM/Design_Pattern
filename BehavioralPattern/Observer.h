/***
 * Observer:观察者模式
 * 定义一种订阅机制，可在对象事件发生时通知多个“观察者”对象
 * 参考 ROS的消息发布订阅机制
*/
#include <iostream>
#include <list>
#include <string>

//Observer基类
class IObserver {
public:
    virtual ~IObserver() {};

    virtual void Update(const std::string &message_from_subject) = 0;
};

//Subject基类
class ISubject {
public:
    virtual ~ISubject() {};

    virtual void Attach(IObserver *observer) = 0;

    virtual void Detach(IObserver *observer) = 0;

    virtual void Notify() = 0;
};

//Subject有一些状态,当状态改变时,通知Observer
class Subject : public ISubject {
public:
    virtual ~Subject() {
        std::cout << "Goodbye, I was the Subject.\n";
    }

    void Attach(IObserver *observer) override {
        list_observer_.push_back(observer);//加入观察者
    }

    void Detach(IObserver *observer) override {
        list_observer_.remove(observer);//删除观察者
    }

    //通知所有Observer更新状态
    void Notify() override {
        std::list<IObserver *>::iterator iterator = list_observer_.begin();
        HowManyObserver();
        while (iterator != list_observer_.end()) {
            (*iterator)->Update(message_);
            ++iterator;
        }
    }

    void CreateMessage(std::string message = "Empty") {
        this->message_ = message;
        Notify();
    }

    void HowManyObserver() {
        std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
    }

    //一般subject有自己的一些业务逻辑在完成后通知给Observer
    void SomeBusinessLogic() {
        this->message_ = "change message message";
        Notify();
        std::cout << "I'm about to do some thing important\n";
    }

private:
    std::list<IObserver *> list_observer_;//观察者列表
    std::string message_;
};

//Concrete Observer
class Observer : public IObserver {
public:
    Observer(Subject &subject) : subject_(subject) {
        this->subject_.Attach(this);
        std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
        this->number_ = Observer::static_number_;
    }

    virtual ~Observer() {
        std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
    }

    void Update(const std::string &message_from_subject) override {
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }

    void RemoveMeFromTheList() {
        subject_.Detach(this);
        std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
    }

    void PrintInfo() {
        std::cout << "Observer \"" << this->number_ << "\": a new message is available --> "
                  << this->message_from_subject_ << "\n";
    }

private:
    std::string message_from_subject_;
    Subject &subject_;
    static int static_number_;
    int number_;
};

int Observer::static_number_ = 0;

void ClientCode() {
    //创建一个subject
    Subject *subject = new Subject;
    //创建三个观察subject的Observer
    Observer *observer1 = new Observer(*subject);
    Observer *observer2 = new Observer(*subject);
    Observer *observer3 = new Observer(*subject);
    Observer *observer4;
    Observer *observer5;

    subject->CreateMessage("Hello World! :D");//subject写入消息并通知
    observer3->RemoveMeFromTheList();

    subject->CreateMessage("The weather is hot today! :p");
    observer4 = new Observer(*subject);

    observer2->RemoveMeFromTheList();
    observer5 = new Observer(*subject);

    subject->CreateMessage("My new car is great! ;)");
    observer5->RemoveMeFromTheList();

    observer4->RemoveMeFromTheList();
    observer1->RemoveMeFromTheList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
}

int main() {
    ClientCode();
    return 0;
}