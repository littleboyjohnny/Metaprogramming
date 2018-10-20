#include <iostream>
#include <vector>
#include <cstring>
#include <exception>

class WrongPattern: public std::exception
{
    const char* what() const throw() { return "Exception: wrong pattern.\n"; }
};

class interfaceA;

class interfaceB;

class interfaceC;

class interfaceA {
protected:
    int infoA;
    int idA;
public:
    void setInfoA(int info) {
        infoA = info;
    }

    int getInfoA() {
        return infoA;
    }

    virtual void request() = 0;
    virtual void request(int idB) = 0;
    virtual void update(int info) = 0;
    virtual void makeSubscribtion(int idB) = 0;
};

class interfaceB {
protected:
    bool stateReady = true;
    int infoB;
    int idB;
public:
    void setInfoB(int info) {
        infoB = info;
    }

    int getInfoB() {
        return infoB;
    }

    void setState(bool state) {
        stateReady = state;
    }

    bool getState() {
        return stateReady;
    }

    virtual void respond(interfaceA* a) = 0;
    virtual void respond(int idB, interfaceA* a) = 0;
    virtual void subscribe(int idB, interfaceA* a) = 0;
};

class interfaceC {
public:
    virtual void notifySubsrcibersOfB(int idB, int info)  = 0;
    virtual void subsrcibeFromB(int idB, interfaceA* a) = 0;
};



class A : public interfaceA {
    interfaceB* obj;
public:
    A(int id, interfaceB* obj) {
        this->obj = obj;
        this->idA = id;
    }

    void request() {
        obj->respond(this);
    }

    void request(int idB) {
        obj->respond(idB, this);
    }

    void update(int info) {
        this->setInfoA(info);
    }

    void makeSubscribtion(int idB) {
        obj->subscribe(idB, this);
    }

    void printInfo() {
        std::cout << "InfoA is " << infoA << std::endl;
    }
};

class B : public interfaceB {
    interfaceC* obj;
public:
    B(int id, interfaceC* obj) {
        this->obj = obj;
        this->idB = id;
    }

    void respond(interfaceA* a) {
        a->update(this->infoB);
    }

    void respond(int idB, interfaceA* a) {
        if (this->idB == idB)
            a->update(this->infoB);
    }

    void notifySubscribers(int info) {
        obj->notifySubsrcibersOfB(idB, info);
    }

    void subscribe(int idB, interfaceA* a) {
        obj->subsrcibeFromB(idB, a);
    }

    void printInfo() {
        std::cout << "InfoB is " << infoB << std::endl;
    }
};

template<char Type>
class Soup : public interfaceB, public interfaceC {
    std::vector<std::pair<int, interfaceA*>> subscribersA;
    std::vector<interfaceB*> obectsB;
public:
    Soup() {}

    void addB(interfaceB* b) {
        obectsB.push_back(b);
    }

    // Proxy section
    void respond(interfaceA* a) {
        if (Type == 'p') {
            if (obectsB[0]->getState()) {
                obectsB[0]->respond(a);
            }
        } else {
            throw new WrongPattern();
        }
    }
    // ================
    // Mediator section
    void respond(int idB, interfaceA* a) {
        if (Type == 'm') {
            for (int i = 0; i < obectsB.size(); i++) {
                obectsB[i]->respond(idB, a);
            }
        } else {
            throw new WrongPattern();
        }
    }
    // ================
    // Observer section
    void subscribe(int idB, interfaceA* a) {
        if (Type == 'o')
            subscribersA.push_back(std::make_pair(idB, a));
        else {
            throw new WrongPattern();
        }
    }

    void notifySubsrcibersOfB(int idB, int info) {
        if (Type == 'o')
            for (int i = 0; i < subscribersA.size(); i++) {
                if (subscribersA[i].first == idB)
                    subscribersA[i].second->update(info);
            }
        else {
            throw new WrongPattern();
        }
    }

    void subsrcibeFromB(int idB, interfaceA* a) {
        if (Type == 'o')
            this->subscribe(idB, a);
        else {
            throw new WrongPattern();
        }
    }
    // ================
};

/*
template<>
class Soup<0> {

};
*/
int main() {
    //const char s = 'p';
    /* //PROXY CHECK
    Soup<'p'>* patterns;
    patterns = new Soup<'p'>();
    A* a = new A(1, patterns);
    B* b = new B(1, patterns);
    patterns->addB(b);
    b->setInfoB(42);
    a->request();
    a->printInfo();
    */
    /* //MEDIATOR CHECK
    Soup<'m'>* patterns;
    patterns = new Soup<'m'>();
    A* a = new A(1, patterns);
    B* b1 = new B(1, patterns);
    B* b2 = new B(2, patterns);
    B* b3 = new B(3, patterns);
    patterns->addB(b1);
    patterns->addB(b2);
    patterns->addB(b3);
    b1->setInfoB(11);
    b2->setInfoB(12);
    b3->setInfoB(13);
    a->request(2);
    a->printInfo();
     */
    //OBSERVER CHECK
    Soup<'o'>* patterns;
    patterns = new Soup<'o'>();
    A* a1 = new A(1, patterns);
    A* a2 = new A(2, patterns);
    B* b1 = new B(1, patterns);
    B* b2 = new B(2, patterns);
    B* b3 = new B(3, patterns);
    patterns->addB(b1);
    patterns->addB(b2);
    patterns->addB(b3);
    b1->setInfoB(11);
    b2->setInfoB(12);
    b3->setInfoB(13);
    a1->makeSubscribtion(2);
    a2->makeSubscribtion(2);
    b2->notifySubscribers(22);
    a1->printInfo();
    a2->printInfo();
    return 0;
}