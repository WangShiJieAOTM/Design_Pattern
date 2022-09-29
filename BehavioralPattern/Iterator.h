/***
 * Iterator:迭代器模式
 * 在不暴露集合底层的表示形式的情况下遍历集合中的所有元素
*/
#include <iostream>
#include <string>
#include <vector>

//C++ 有自己的迭代器实现，它与标准库定义的不同泛型容器一起工作。
template<typename T, typename U>
class Iterator {
public:
    typedef typename std::vector<T>::iterator iter_type;

    Iterator(U *p_data, bool reverse = false) : m_p_data_(p_data) {
        m_it_ = m_p_data_->m_data_.begin();
    }

    void First() {
        m_it_ = m_p_data_->m_data_.begin();
    }

    void Next() {
        m_it_++;
    }

    bool IsDone() {
        return (m_it_ == m_p_data_->m_data_.end());
    }

    iter_type Current() {
        return m_it_;
    }

private:
    U *m_p_data_;
    iter_type m_it_;
};

//Generic CollectionsContainers 提供了一种或多种方法来检索新的迭代器实例，与集合类兼容。
template<class T>
class Container {
    friend class Iterator<T, Container>;
public:
    void Add(T a) {
        m_data_.push_back(a);
    }

    Iterator<T, Container> *CreateIterator() {
        return new Iterator<T, Container>(this);
    }

private:
    std::vector<T> m_data_;
};

class Data {
public:
    Data(int a = 0) : m_data_(a) {}

    void set_data(int a) {
        m_data_ = a;
    }

    int data() {
        return m_data_;
    }

private:
    int m_data_;
};

//客户端代码可能知道也可能不知道具体迭代器或集合类，对于此实现，容器是通用的，因此您可以与 int 或自定义类一起使用
void ClientCode() {
    std::cout << "________________Iterator with int______________________________________" << std::endl;
    Container<int> cont;

    for (int i = 0; i < 10; i++) {
        cont.Add(i);
    }

    Iterator<int, Container<int>> *it = cont.CreateIterator();
    for (it->First(); !it->IsDone(); it->Next()) {
        std::cout << *it->Current() << std::endl;
    }

    Container<Data> cont2;
    Data a(100), b(1000), c(10000);
    cont2.Add(a);
    cont2.Add(b);
    cont2.Add(c);

    std::cout << "________________Iterator with custom Class______________________________" << std::endl;
    Iterator<Data, Container<Data>> *it2 = cont2.CreateIterator();
    for (it2->First(); !it2->IsDone(); it2->Next()) {
        std::cout << it2->Current()->data() << std::endl;
    }
    delete it;
    delete it2;
}

int main() {
    ClientCode();
    return 0;
}