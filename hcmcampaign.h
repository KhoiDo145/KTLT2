/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 2
 * Programming Fundamentals Spring 2025
 * Date: 02.02.2025
 */

// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_HCM_CAMPAIGN_H_
#define _H_HCM_CAMPAIGN_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class Unit;
class UnitList;
class Army;
class TerrainElement;

class Vehicle;
class Infantry;

class LiberationArmy;
class ARVN;

class Position;

class Road;
class Mountain;
class River;
class Urban;
class Fortification;
class SpecialZone;

class BattleField;

class HCMCampaign;
class Configuration;

enum VehicleType
{
    TRUCK,
    MORTAR,
    ANTIAIRCRAFT,
    ARMOREDCAR,
    APC,
    ARTILLERY,
    TANK
};
enum InfantryType
{
    SNIPER,
    ANTIAIRCRAFTSQUAD,
    MORTARSQUAD,
    ENGINEER,
    SPECIALFORCES,
    REGULARINFANTRY
};

class Army
{
protected:
    int LF, EXP;
    string name;
    UnitList *unitList;
    BattleField *battleField;

public:
    Army(Unit **unitArray, int size, string name, BattleField *battleField);
    virtual void fight(Army *enemy, bool defense = false) = 0;
    virtual string str() const = 0;
};

class Position
{
private:
    int r, c;

public:
    Position(int r = 0, int c = 0);
    Position(const string &str_pos); // Example: str_pos = "(1,15)"
    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
    double distance(const Position& a, const Position& b);
    string str() const; // Example: returns "(1,15)"
};

class Unit
{
protected:
    int quantity, weight;
    Position pos;

public:
    Unit(int quantity, int weight, Position pos);
    virtual ~Unit();
    virtual int getAttackScore() = 0;
    virtual bool isVehicleType() const { return false; }
    virtual bool isInfantryType() const { return false; }
    Position getCurrentPosition() const;
    virtual string str() const = 0;
    virtual bool isVehicle() const { return false; }
    virtual bool isInfantry() const { return false; }
};

class UnitList 
{
private:
    int capacity;
    // TODO
    Node* head;
    int size;
public:
    UnitList(int capacity);
    bool insert(Unit *unit);                   // return true if insert successfully
    bool isContain(VehicleType vehicleType);   // return true if it exists
    bool isContain(InfantryType infantryType); // return true if it exists
    string str() const override;
    // TODO
    bool isSpecial(int n);
    struct Node {
        Unit  *unit;
        Node *next;
        Node(Unit* u) : unit(u), next(nullptr) {}
    };
};

class TerrainElement
{
public:
    TerrainElement();
    ~TerrainElement();
    virtual void getEffect(Army *army) = 0;
};

class Road : public TerrainElement 
{
public:
    void getEffect(Army *army) override;
};

class Mountain : public TerrainElement 
{
public:
    void getEffect(Army *army) override;
};

class River : public TerrainElement 
{
public:
    void getEffect(Army *army) override;
};

class Urban : public TerrainElement 
{
public:
    void getEffect(Army *army) override;
};

class Fortification : public TerrainElement 
{
public:
    void getEffect(Army *army) override;
};

class SpecialZone : public TerrainElement 
{
public:
    void getEffect(Army *army) override;
};

class BattleField
{
private:
    int n_rows, n_cols;
    // TODO
public:
    BattleField(int n_rows, int n_cols, vector<Position *> arrayForest,
                vector<Position *> arrayRiver, vector<Position *> arrayFortification,
                vector<Position *> arrayUrban, vector<Position *> arraySpecialZone);
    ~BattleField();
};

class HCMCampaign
{
private:
    Configuration *config;
    BattleField *battleField;
    LiberationArmy *liberationArmy;
    ARVN *ARVN;

public:
    HCMCampaign(const string &config_file_path);
    void run();
    string printResult();
};

class Vehicle : public Unit
{
private: 
    VehicleType vehicleType;
public:
    Vehicle(int quantity, int weight, const Position pos, VehicleType VehicleType);
    VehicleType getvehicleType() const;
    int getquantity() const;
    int getweight() const;
    string str() const override;
    int getAttackScore() override;
    bool isVehicle() const override { return true; }
};

class Infantry : public Unit
{
private: 
    InfantryType infantryType;
public:
    Infantry(int quantity, int weight, const Position pos, InfantryType infantryType);
    InfantryType getinfantryType() const;
    int getquantity() const;
    int getweight() const;
    int getAttackScore() override;
    string str() const override;
    bool checkPerfectSquares(int n);
    int personalNumber(int n);
    bool isInfantry() const override { return true; }
};

#endif
