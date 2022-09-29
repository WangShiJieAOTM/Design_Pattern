/***
 * Command Pattern:命令模式
 * 将请求转换为一个包含与请求相关的所有信息的独立对象.该转换让你能根据不同请求将方法参数化,延迟请求执行或将其放入队列,以及支持可撤销的操作
*/

//Command 接口声明了一个执行命令的方法。
class Command {
public:
    virtual ~Command() {
    }

    virtual void Execute() const = 0;
};

//有些命令可以自己实现简单的操作。
class SimpleCommand : public Command {
private:
    std::string pay_load_;

public:
    explicit SimpleCommand(std::string pay_load) : pay_load_(pay_load) {
    }

    void Execute() const override {
        std::cout << "SimpleCommand: See, I can do simple things like printing (" << this->pay_load_ << ")\n";
    }
};

//Receiver 类包含一些重要的业务逻辑。他们知道如何执行与执行请求相关的各种操作。事实上，任何类都可以作为接收者
class Receiver {
public:
    void DoSomething(const std::string &a) {
        std::cout << "Receiver: Working on (" << a << ".)\n";
    }

    void DoSomethingElse(const std::string &b) {
        std::cout << "Receiver: Also working on (" << b << ".)\n";
    }
};

//但是，某些命令可以将更复杂的操作委托给其他对象，称为“Receiver”。
class ComplexCommand : public Command {
private:
    Receiver *receiver_;
    std::string a_;
    std::string b_;
    //复杂命令可以通过构造函数接受一个或多个接收器对象以及任何上下文数据。
public:
    ComplexCommand(Receiver *receiver, std::string a, std::string b) : receiver_(receiver), a_(a), b_(b) {
    }

    void Execute() const override {
        std::cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";
        this->receiver_->DoSomething(this->a_);
        this->receiver_->DoSomethingElse(this->b_);
    }
};

//Invoker 与一个或多个命令相关联。它向命令发送请求。
class Invoker {
private:
    Command *on_start_;
    Command *on_finish_;
public:
    ~Invoker() {
        delete on_start_;
        delete on_finish_;
    }

    void SetOnStart(Command *command) {
        this->on_start_ = command;
    }

    void SetOnFinish(Command *command) {
        this->on_finish_ = command;
    }

    //Invoker 不依赖于具体的命令或接收器类。调用者通过执行命令间接将请求传递给接收者。
    void DoSomethingImportant() {
        std::cout << "Invoker: Does anybody want something done before I begin?\n";
        if (this->on_start_) {
            this->on_start_->Execute();
        }
        std::cout << "Invoker: ...doing something really important...\n";
        std::cout << "Invoker: Does anybody want something done after I finish?\n";
        if (this->on_finish_) {
            this->on_finish_->Execute();
        }
    }
};

//客户端代码可以使用任何命令参数化调用程序。
int main() {
    Invoker *invoker = new Invoker;
    invoker->SetOnStart(new SimpleCommand("Say Hi!"));
    Receiver *receiver = new Receiver;
    invoker->SetOnFinish(new ComplexCommand(receiver, "Send email", "Save report"));
    invoker->DoSomethingImportant();

    delete invoker;
    delete receiver;

    return 0;
}