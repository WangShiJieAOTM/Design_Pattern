/***
 * I:Interface Segregation Principle 接口隔离原则
 * 分离接口，以便各用户自主选择
*/

//强制提供三个接口
class IMachine {
public:
    virtual void print(std::vector<Document *> docs) = 0;

    virtual void scan(std::vector<Document *> docs) = 0;

    virtual void fax(std::vector<Document *> docs) = 0;
};

class MyMachine : public IMachine {
public:
    void print(std::vector<Document *> docs) override;

    void scan(std::vector<Document *> docs) override;

    void fax(std::vector<Document *> docs) override;
};

//但是如果PeterMachine只需要 print和scan功能呢?
class PeterMachine : public IMachine {
public:
    void print(std::vector<Document *> docs) override;

    void scan(std::vector<Document *> docs) override;

    void fax(std::vector<Document *> docs) override;
};


//这时候就需要分离接口:
class IPrinter {
public:
    virtual void print(std::vector<Document *> docs) = 0;
};

class IScanner {
public:
    virtual void scan(std::vector<Document *> docs) = 0;
};

class IFax {
public:
    virtual void fax(std::vector<Document *> docs) = 0;
};
//一些实现:

class MyPrinter : public IPrinter {
public:
    void print(std::vector<Document *> docs) override;
};

class MyScanner : public IScanner {
public:
    void scan(std::vector<Document *> docs) override;
};

class MyFax : public IFax {
public:
    void fax(std::vector<Document *> docs) override;
};

class peterPrinter : public IPrinter {
public:
    void print(std::vector<Document *> docs) override;
};

class peterScanner : public IScanner {
public:
    void scan(std::vector<Document *> docs) override;
};

class MyNewMachine {
private:
    IPrinter &printer;
    IScanner &scanner;
    IFax &fax;
public:
    MyNewMachine(IPrinter &printer, IScanner &scanner, IFax &fax) : printer(printer), scanner(scanner), fax(fax) {}

    void print(std::vector<Document *> docs) {
        printer.print(docs);
    }

    void scan(std::vector<Document *> docs) {
        scanner.scan(docs);
    }

    void fax(std::vector<Document *> docs) {
        fax.fax(docs);
    }
};

class PeterNewMachine {
private:
    IPrinter &printer;
    IScanner &scanner;
public:
    PeterNewMachine(IPrinter &printer, IScanner &scanner) : printer(printer), scanner(scanner) {}

    void print(std::vector<Document *> docs) {
        printer.print(docs);
    }

    void scan(std::vector<Document *> docs) {
        scanner.scan(docs);
    }
};

//这样就把接口分离了,用户可以自主选择需要的接口

