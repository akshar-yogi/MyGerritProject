#define XYZE

///////////////////////////////////////////////////////////////////////////////

#ifdef XYZE

#include <iostream>
#include <string>
#include <cstring>

// Abstract base class as it contains pure virtual functions. It can not be 
// instantiated.
struct IMyInterface { 
    virtual ~IMyInterface() = default; // Virtual destructor
    virtual std::string Id() const = 0; // Pure virtual function
    virtual void Id(const std::string&) {}; // Not a pure virtual function
};

// Derived class using virtial inheritance and public member access specifier
class MyClass : public virtual IMyInterface {
private:
    MyClass() = delete; // Explicitly deleted constructor
    MyClass(const MyClass&) = delete; // Deleted copy constructor
    MyClass& operator=(const MyClass&) = delete; // Deleted assignment operator

public:
    explicit MyClass(const std::string& id)
        : _id(id)
    {
    }
    ~MyClass() override = default;

public:
    std::string Id() const override
    {
        return (_id);
    }
    void Id(const std::string& id) override
    {
        std::cout << id << "\n";
        _id = id;
    }
    bool operator==(const MyClass& other) const { // Operator overloading
        if (strcasecmp(Id().c_str(), other.Id().c_str()) == 0) { // compare ignoring case
            return true;
        } else {
            return false;
        }
    }
    // Factory method to create singleton
    static MyClass& Create()
    {
        static MyClass instance("DefaultString");
        return instance;
    }

private:
    std::string _id;
};

int main()
{
    // Object creation / Operator overloading
    {
        MyClass mc1("MyString");
        std::cout << mc1.Id() << "\n";

        MyClass mc2("mystring");
        if (mc1 == mc2) { // Operator overloading
            std::cout << "Strings are same\n";
        } else {
            std::cout << "Strings are not same\n";
        }
    }

    // Using Factory method to create singleton
    {
        MyClass& mc = MyClass::Create();
        std::cout << mc.Id() << "\n";
    }

    return (0);
}

#endif
