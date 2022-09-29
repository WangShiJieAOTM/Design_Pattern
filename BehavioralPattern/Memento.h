/***
 * Memento:备忘录模式
 * 允许在不暴露对象实现细节的情况下保存和恢复对象之前的状态
*/

//Memento 接口提供了一种检索备忘录元数据的方法，例如创建日期或名称。但是，它不会暴露 Originator 的状态。
class Memento {
public:
    virtual ~Memento() {}

    virtual std::string GetName() const = 0;

    virtual std::string date() const = 0;

    virtual std::string state() const = 0;
};

//Concrete Memento 包含用于存储 Originator 状态的基础设施。
class ConcreteMemento : public Memento {
private:
    std::string state_;
    std::string date_;

public:
    ConcreteMemento(std::string state) : state_(state) {
        this->state_ = state;
        std::time_t now = std::time(0);
        this->date_ = std::ctime(&now);
    }

    //恢复
    std::string state() const override {
        return this->state_;
    }

    std::string GetName() const override {
        return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
    }

    std::string date() const override {
        return this->date_;
    }
};

//发起者持有一些可能随时间改变的重要状态。它还定义了一种将状态保存在备忘录中的方法和另一种从中恢复状态的方法。
class Originator {
private:
    std::string state_;

    std::string GenerateRandomString(int length = 10) {
        const char alphanum[] =
                "012345678989"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        int stringLength = sizeof(alphanum) - 1;

        std::string random_string;
        for (int i = 0; i < length; i++) {
            random_string += alphanum[std::rand() % stringLength];
        }
        return random_string;
    }

public:
    Originator(std::string state) : state_(state) {
        std::cout << "Originator: My initial state is: " << this->state_ << "\n";
    }

    //发起者的业务逻辑可能会影响其内部状态。因此，客户端应该在通过 save() 方法启动业务逻辑的方法之前备份状态。
    void DoSomething() {
        std::cout << "Originator: I'm doing something important.\n";
        this->state_ = this->GenerateRandomString(30);
        std::cout << "Originator: and my state has changed to: " << this->state_ << "\n";
    }

    //将当前状态保存在备忘录中。
    Memento *Save() {
        return new ConcreteMemento(this->state_);
    }

    void Restore(Memento *memento) {
        this->state_ = memento->state();
        std::cout << "Originator: My state has changed to: " << this->state_ << "\n";
    }
};

//看守者不依赖于 Concrete Memento 类。因此，它无法访问存储在备忘录中的发起者的状态。它通过基础 Memento 接口与所有纪念品一起工作。
class Caretaker {
private:
    std::vector<Memento *> mementos_;
    Originator *originator_;

public:
    Caretaker(Originator *originator) : originator_(originator) {
    }

    ~Caretaker() {
        for (auto m : mementos_) delete m;
    }

    void Backup() {
        std::cout << "\nCaretaker: Saving Originator's state...\n";
        this->mementos_.push_back(this->originator_->Save());
    }

    void Undo() {
        if (!this->mementos_.size()) {
            return;
        }
        Memento *memento = this->mementos_.back();
        this->mementos_.pop_back();
        std::cout << "Caretaker: Restoring state to: " << memento->GetName() << "\n";
        try {
            this->originator_->Restore(memento);
        } catch (...) {
            this->Undo();
        }
    }

    void ShowHistory() const {
        std::cout << "Caretaker: Here's the list of mementos:\n";
        for (Memento *memento : this->mementos_) {
            std::cout << memento->GetName() << "\n";
        }
    }
};

void ClientCode() {
    Originator *originator = new Originator("Super-duper-super-puper-super.");
    Caretaker *caretaker = new Caretaker(originator);
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    std::cout << "\n";
    caretaker->ShowHistory();
    std::cout << "\nClient: Now, let's rollback!\n\n";
    caretaker->Undo();
    std::cout << "\nClient: Once more!\n\n";
    caretaker->Undo();

    delete originator;
    delete caretaker;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    ClientCode();
    return 0;
}