#include <iostream>
#include <cstring>

using namespace std;

// ����������� ����� ��� ���������� ��������
class Herbivore 
{
protected:
    int weight;  // ��� �����������
    bool alive;  // ����� �� ��������

public:
    Herbivore(int w) : weight(w), alive(true) {}
    virtual ~Herbivore() {}

    virtual void eatGrass() = 0;  // ����� ������ �����
    int getWeight() const { return weight; }
    bool isAlive() const { return alive; }
    void die() { alive = false; }
};

// ����������� ����� ��� ��������
class Carnivore 
{
protected:
    int power;  // ���� �������

public:
    Carnivore(int p) : power(p) {}
    virtual ~Carnivore() {}

    virtual void eat(Herbivore* herbivore) = 0;  // ����� ������ ����������
    int getPower() const { return power; }
};
// ����� ��� �������� ���
class Wildebeest : public Herbivore 
{
public:
    Wildebeest(int w) : Herbivore(w) {}

    void eatGrass() override 
    {
        if (alive) {
            weight += 10;  // ���������� ������ ����� � �������� ���
            cout << "Wildebeest eats grass, weight: " << weight << endl;
        }
    }
};

// ����� ��� ������
class Bison : public Herbivore 
{
public:
    Bison(int w) : Herbivore(w) {}

    void eatGrass() override {
        if (alive) {
            weight += 10;  // ���������� ������ ����� � �������� ���
            cout << "Bison eats grass, weight: " << weight << endl;
        }
    }
};
// ����� ��� ����
class Lion : public Carnivore 
{
public:
    Lion(int p) : Carnivore(p) {}

    void eat(Herbivore* herbivore) override {
        if (herbivore->isAlive()) {
            if (power > herbivore->getWeight()) {
                power += 10;  // ���� ���� ������ ���� �����������
                herbivore->die();
                cout << "Lion eats herbivore, power: " << power << endl;
            }
            else {
                power -= 10;  // ���� ���� ������, �� ������ ����
                cout << "Lion tried to eat herbivore but failed, power: " << power << endl;
            }
        }
        else {
            cout << "Lion can't eat, herbivore is already dead." << endl;
        }
    }
};

// ����� ��� �����
class Wolf : public Carnivore 
{
public:
    Wolf(int p) : Carnivore(p) {}

    void eat(Herbivore* herbivore) override 
    {
        if (herbivore->isAlive()) {
            if (power > herbivore->getWeight()) {
                power += 10;  // ���� ���� ������ ���� �����������
                herbivore->die();
                cout << "Wolf eats herbivore, power: " << power << endl;
            }
            else {
                power -= 10;  // ���� ���� ������, �� ������ ����
                cout << "Wolf tried to eat herbivore but failed, power: " << power << endl;
            }
        }
        else {
            cout << "Wolf can't eat, herbivore is already dead." << endl;
        }
    }
};
// ����������� ����� ��� �����������
class Continent 
{
public:
    virtual Herbivore* createHerbivore() = 0;
    virtual Carnivore* createCarnivore() = 0;
};

// ����� ������
class Africa : public Continent {
public:
    Herbivore* createHerbivore() override 
    {
        return new Wildebeest(50);  // ������� �������� ���
    }

    Carnivore* createCarnivore() override 
    {
        return new Lion(60);  // ������� ����
    }
};

// ����� �������� �������
class NorthAmerica : public Continent 
{
public:
    Herbivore* createHerbivore() override 
    {
        return new Bison(70);  // ������� ������
    }

    Carnivore* createCarnivore() override 
    {
        return new Wolf(50);  // ������� �����
    }
};
// ����� ��� ���� ��������
class AnimalWorld 
{
private:
    Herbivore* herbivores[2];
    Carnivore* carnivores[2];
    int herbivoreCount;
    int carnivoreCount;

public:
    AnimalWorld(Continent* continent1, Continent* continent2) 
    {
        herbivoreCount = 0;
        carnivoreCount = 0;

        // ������� �� ������ ����������� � ������� ��� ���� �����������
        herbivores[herbivoreCount++] = continent1->createHerbivore();
        carnivores[carnivoreCount++] = continent1->createCarnivore();

        herbivores[herbivoreCount++] = continent2->createHerbivore();
        carnivores[carnivoreCount++] = continent2->createCarnivore();
    }

    ~AnimalWorld() {
        for (int i = 0; i < herbivoreCount; i++) 
        {
            delete herbivores[i];
        }
        for (int i = 0; i < carnivoreCount; i++) 
        {
            delete carnivores[i];
        }
    }

    void mealsHerbivores() 
    {
        for (int i = 0; i < herbivoreCount; i++) 
        {
            herbivores[i]->eatGrass();  // ���������� ������ �����
        }
    }

    void nutritionCarnivores()
    {
        for (int i = 0; i < carnivoreCount; i++) 
        {
            carnivores[i]->eat(herbivores[i]);  // ������� �������� �� ����������
        }
    }
};
int main() 
{
    // ������� ��� �������� � ������ � �������� �������
    Africa africa;
    NorthAmerica northAmerica;
    AnimalWorld world(&africa, &northAmerica);


    // ���������� ������ �����
    world.mealsHerbivores();

    // ������� �������� �� ����������
    world.nutritionCarnivores();

    return 0;
}
