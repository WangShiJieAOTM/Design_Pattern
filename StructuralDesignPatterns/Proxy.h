/***
 * Proxy:代理模式
 * 提供对象的替代品或其占位符.代理控制这对于原对象的访问,并允许在将请求提交给对象前后进行一些处理
*/
#include <iostream>

//Subject 接口声明了 RealSubject 和 Proxy 的通用操作。
//只要客户端使用此接口与 RealSubject 一起工作，您就可以向它传递Proxy而不是RealSubject。
class Subject {
public:
    virtual void Request() const = 0;
};

//RealSubject 包含一些核心业务逻辑。
//通常，RealSubjects 能够做一些有用的工作，这些工作也可能非常缓慢或敏感 -
//例如修正输入数据。代理可以解决这些问题，而无需对 RealSubject 的代码进行任何更改。
class RealSubject : public Subject {
public:
    void Request() const override {
        std::cout << "RealSubject: Handling request.\n";
    }
};

//Proxy 有一个与 RealSubject 相同的接口。
class Proxy : public Subject {
private:
    RealSubject *real_subject_;

    bool CheckAccess() const {
        // Some real checks should go here.
        std::cout << "Proxy: Checking access prior to firing a real request.\n";
        return true;
    }

    void LogAccess() const {
        std::cout << "Proxy: Logging the time of request.\n";
    }
    //Proxy 维护对 RealSubject 类的对象的引用。它可以是延迟加载的，也可以由客户端传递给代理。
public:
    Proxy(RealSubject *real_subject) : real_subject_(new RealSubject(*real_subject)) {
    }

    ~Proxy() {
        delete real_subject_;
    }

    //代理模式最常见的应用是延迟加载、缓存、控制访问、日志记录等。
    //代理可以执行其中一项操作，然后根据结果将执行传递给链接的 RealSubject 对象中的相同方法.
    void Request() const override {
        if (this->CheckAccess()) {
            this->real_subject_->Request();
            this->LogAccess();
        }
    }
};

//客户端代码应该通过 Subject 接口与所有对象（主体和代理）一起工作，以支持真实的主体和代理。
//然而，在现实生活中，客户大多直接与他们的真实主题合作。在这种情况下，为了更容易地实现该模式，您可以从真实主题的类中扩展您的代理。
void ClientCode(const Subject &subject) {
    // ...
    subject.Request();
    // ...
}

int main() {
    std::cout << "Client: Executing the client code with a real subject:\n";
    RealSubject *real_subject = new RealSubject;
    ClientCode(*real_subject);
    std::cout << "\n";
    std::cout << "Client: Executing the same client code with a proxy:\n";
    Proxy *proxy = new Proxy(real_subject);
    ClientCode(*proxy);

    delete real_subject;
    delete proxy;
    return 0;
}

/***
 * 代理模式最常见的应用是延迟加载、缓存、控制访问、日志记录等。
 * 代理可以执行其中一项操作，然后根据结果将执行传递给链接的 RealSubject 对象中的相同方法.
*/