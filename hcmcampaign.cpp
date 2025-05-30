#include "hcmcampaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
////////////////////////////////////////////////////////////////////////

// 3.6
Position::Position(int r, int c)
    : r(r), c(c)
{}

Position::Position(const string &str_pos) {
    string str = str_pos;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ' && (str[i] < '0' || str[i] > '9')) str[i] = ' ';
    }
    stringstream ss(str);
    if (!(ss >> r >> c)) r = c = 0;
}

int Position::getRow() const {
    return r;
}

int Position::getCol() const {
    return c;
}

void Position::setRow(int r) {
    this -> r = r;
}

void Position::setCol(int c) {
    this -> c = c;
}

string Position::str() const {
    return "(" + to_string(r) + ", " + to_string(c) + ")";
}

double Position::distance(const Position& a, const Position& b) {
        return hypot((a.r - b.r), (a.c - b.c));
}
//

// 3.1 
Unit::Unit(int quantity, int weight, const Position &pos)
    : quantity(quantity), weight(weight), pos(pos)
{}

Unit::~Unit() {};

Position Unit::getCurrentPosition() const {
    return pos;
}
//

// 3.2
Vehicle::Vehicle(int quantity, int weight, const Position pos, VehicleType vehicleType)
    : quantity(quantity), weight(weight), pos(pos), vehicleType(vehicleType)
{}

VehicleType Vehicle::getVehicleType() const{
    return vehicleType;
}
int Vehicle::getquantity() const{
    return quantity;
}
int Vehicle::getweight() const{
    return weight;
}
int Vehicle::getAttackScore() override {
    return ((int)vehicleType*304 + quantity*weight) / 30;
}
string Vehicle::str() override {
    string vehicleTypestr;
    switch(vehicleType) {
        case 0 : vehicleTypestr = "TRUCK"; break;
        case 1 : vehicleTypestr = "MORTAR"; break;
        case 2 : vehicleTypestr = "ANTIAIRCRAFT"; break;
        case 3 : vehicleTypestr = "ARMOREDCAR"; break;
        case 4 : vehicleTypestr = "APC"; break;
        case 5 : vehicleTypestr = "ARTILLERY"; break;
        case 6 : vehicleTypestr = "TANK"; break;
        default : vehicleTypestr = "UNKNOWN"; break;
    }

    return "Vehicle[vehicleType=" + vehicleTypestr + 
            ", quantity=" + to_string(quantity) + 
            ", weight=" + to_string(weight) + 
            ", pos=" + pos + "]";
}
//
// 3.3
bool checkPerfectSquares(int n) {
    int i = sqrt(n);
    return i*i == n;
}

int personalNumber(int n) {
    do {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        n = sum;
    } while (n >= 10);
    return n;
}
 
Infantry::Infantry(int quantity, int weight, const Position pos, InfantryType infantryType)
    : quantity(quantity), weight(weight), pos(pos), infantryType(infantryType)
{}

InfantryType Infantry::getinfantryType() const{
    return infantryType;
}
int Infantry::getquantity() const{
    return quantity;
}
int Infantry::getweight() const{
    return weight;
}
int Infantry::getAttackScore() override {
    int score = (int)infantryType*56 + quantity*weight;
    if (infantryType == 4 && checkPerfectSquares(weight)) score += 75;
    score = score + 22;
    if (personalNumber(score) > 7) score = score + quantity*weight*(0.2);
    else if (personalNumber(score) < 3) score = score - quantity*weight*(0.1);
    return score;
}
string Infantry::str() override {
    string infantryTypestr;
    switch(infantryType) {
        case 0 : infantryTypestr = "SNIPER"; break;
        case 1 : infantryTypestr = "ANTIAIRCRAFTSQUAD"; break;
        case 2 : infantryTypestr = "MORTARSQUAD"; break;
        case 3 : infantryTypestr = "ENGINEER"; break;
        case 4 : infantryTypestr = "SPECIALFORCES"; break;
        case 5 : infantryTypestr = "REGULARINFANTRY"; break;
        default : infantryTypestr = "UNKNOWN"; break;
    }

    return "Infantry[infantryType=" + infantryTypestr + 
            ", quantity=" + to_string(quantity) + 
            ", weight=" + to_string(weight) + 
            ", pos=" + pos + "]";
}
//

// 3.5
UnitList::UnitList(int capacity) 
    : head(nullptr), size(0), capacity(capacity) 
{
    if (isSpecial(S)) capacity = 12;
    else capacity = 8;
}

bool UnitList::insert(Unit *unit) {
    if (!unit) return false;
    // Vehicles
    if (unit->isVehicle()) {
        Vehicle *v = static_cast<Vehicle*>(unit);
        Node *cur = head;
        while (cur) {
            if (cur->unit->isVehicle()) {
                Vehicle *curv = static_cast<Vehicle*>(cur->unit);
                if (curv->getvehicleType() == v->getvehicleType()) {
                    curv->quantity += v->quantity;
                    delete unit;
                    return true;
                }
            }
            cur = cur->next;
        }
        if (size >= capacity) {
            delete unit;
            return false;
        }
        Node *newNode = new Node(unit);
        if (!head) head = newNode;
        else {
            Node *tail = head;
            while (tail->next) tail = tail->next;
            tail->next = newNode;
        }
        ++size;
        return true;
    }
    // Infantry
    else if (unit->isInfantry()) {
        Infantry *i = static_cast<Infantry*>(unit);
        Node *cur = head;
        while (cur) {
            if (cur->unit->isInfantry()) {
                Infantry *curi = static_cast<Infantry*>(cur->unit);
                if (curi->getinfantryType() == i->getinfantryType()) {
                    curi->quantity += i->quantity;
                    delete unit;
                    return true;
                }
            }
            cur = cur->next;
        }
        if (size >= capacity) {
            delete unit;
            return false;
        }
        Node *newNode = new Node(unit);
        head = newNode;
        ++size;
        return true;
    }
    delete unit;
    return false;
}

bool UnitList::isContain(VehicleType vehicleType) {
    Node *cur = head;
    while (cur) {
        if (cur->unit->isVehicle()) {
            Vehicle *v = static_cast<Vehicle*>(cur->unit);
            if (v->getvehicleType() == vehicleType) {
                return true;
            }
        }
        cur = cur->next;
    }
    return false;
}

bool UnitList::isContain(InfantryType infantryType) {
    Node *cur = head;
    while (cur) {
        if (cur->unit->IsInfantry()) {
            Infantry *i = static_cast<Infantry*>(cur->unit);
            if (i->getinfantryType() == infantryType) {
                return true;
            }
        }
        cur = cur->next;
    }
    return false;
}

bool UnitList::isSpecial(int S) {
    int primes[] = {2, 3, 5, 7};
    for (int  n : primes) {
       int sum = 0, term = 1; 
       while (sum < S) {
            sum += term;
            if (sum == S) return true;
            term *= n;
       }
    }
    return false;
}

string UnitList::str() {
    int countV = 0;
    int countI = 0;
    string unitListStr = "";
    Node *cur = head;

    while (cur) {
        if (cur->unit->isVehicle()) countV++;
        else if (cur->unit->isInfantry()) countI++;

        if (!unitListStr.empty()) {
            unitListStr += ",";
        }
        unitListStr += cur->unit->str();

        cur = cur->next;
    }

    return "UnitList[count_vehicle=" + to_string(countV) +
           ";count_infantry=" + to_string(countI) +
           ";<" + unitListStr + ">]";
}
//

// 3.4
Army::Army(const Unit **unitArray, int size, string name, BattleField *battleField)
    : LF(0), EXP(0), name(name), battleField(battleField)
{
    unitList = new UnitList(size);
    for (int i = 0; i < size; ++i) {
        if(unitArray[i]) {
            unitList->insert(unitArray[i]);
            if (unitarray[i]->isVehicle()) LF += unitArray[i]->getAttackScore();
            else EXP += unitArray[i]->getAttackScore();
        }
    }
}
//

// 3.7
TerrainElement::TerrainElement(){};
TerrainElement::~TerrainElement(){};


//
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
