/***
 * Chain of responsibility pattern:责任链模式
 * 将请求沿着处理者链进行发送,收到请求后每个处理者均可对请求进行处理,或将其传递给链上的下个处理者
*/

//Handler 接口声明了一个用于构建处理程序链的方法。它还声明了一个执行请求的方法。
class Handler {
public:
    virtual Handler *SetNext(Handler *handler) = 0;

    virtual std::string Handle(std::string request) = 0;
};

//默认链接行为可以在基处理程序类中实现。
class AbstractHandler : public Handler {
private:
    Handler *next_handler_;

public:
    AbstractHandler() : next_handler_(nullptr) {
    }

    Handler *SetNext(Handler *handler) override {
        this->next_handler_ = handler;
        // Returning a handler from here will let us link handlers in a convenient
        // way like this:
        // $monkey->setNext($squirrel)->setNext($dog);
        return handler;
    }

    std::string Handle(std::string request) override {
        if (this->next_handler_) {
            return this->next_handler_->Handle(request);
        }

        return {};
    }
};

//所有具体处理程序要么处理请求，要么将其传递给链中的下一个处理程序。
class MonkeyHandler : public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if (request == "Banana") {
            return "Monkey: I'll eat the " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);//是我处理不了的,交给下一个处理者
        }
    }
};

class SquirrelHandler : public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if (request == "Nut") {
            return "Squirrel: I'll eat the " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);//是我处理不了的,交给下一个处理者
        }
    }
};

class DogHandler : public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if (request == "MeatBall") {
            return "Dog: I'll eat the " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);//是我处理不了的,交给下一个处理者
        }
    }
};

//客户端代码通常适合使用单个处理程序。在大多数情况下，它甚至不知道处理程序是链的一部分。
void ClientCode(Handler &handler) {
    std::vector <std::string> food = {"Nut", "Banana", "Cup of coffee"};
    for (const std::string &f: food) {
        std::cout << "Client: Who wants a " << f << "?\n";
        const std::string result = handler.Handle(f);
        if (!result.empty()) {
            std::cout << "  " << result;
        } else {
            std::cout << "  " << f << " was left untouched.\n";
        }
    }
}

//客户端代码的另一部分构建实际的链。
int main() {
    MonkeyHandler *monkey = new MonkeyHandler;
    SquirrelHandler *squirrel = new SquirrelHandler;
    DogHandler *dog = new DogHandler;
    monkey->SetNext(squirrel)->SetNext(dog);

    //客户端应该能够向任何处理程序发送请求，而不仅仅是链中的第一个处理程序。
    std::cout << "Chain: Monkey > Squirrel > Dog\n\n";
    ClientCode(*monkey);
    std::cout << "\n";
    std::cout << "Subchain: Squirrel > Dog\n\n";
    ClientCode(*squirrel);

    delete monkey;
    delete squirrel;
    delete dog;

    return 0;
}
