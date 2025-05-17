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
        if (str[i] == '(' || str[i] == ')' || str[i] == ',') str[i] = ' ';
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
//

// 3.1 
Unit::Unit(int quantity, int weight, const Position pos)
    : quantity(quantity), weight(weight), pos(pos)
{}

Unit::~Unit() {};

Position Unit::getCurrentPosition() const {
    return pos;
}
//

// 3.2
Vehicle::Vehicle(int quantity, int weight, const Position pos, VehicleType vehicleType)
    : Unit(quantity, weight, pos)
{
    this->vehicleType = vehicleType;
}

VehicleType Vehicle::getVehicleType() const{
    return vehicleType;
}
int Vehicle::getquantity() const{
    return quantity;
}
int Vehicle::getweight() const{
    return weight;
}
int Vehicle::getAttackScore() {
    return ceil((1.0 * (int)vehicleType*304 + quantity*weight) / 30);
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
            ", pos=" + pos.str() + "]";
}
//

// 3.3
bool Infantry::checkPerfectSquares(int n) {
    int i = sqrt(n);
    return i*i == n;
}

int Infantry::personalNumber(int n) {
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
    : Unit(quantity, weight, pos)
{
    this->infantryType = infantryType;
}

InfantryType Infantry::getinfantryType() const{
    return infantryType;
}
int Infantry::getquantity() const{
    return quantity;
}
int Infantry::getweight() const{
    return weight;
}
int Infantry::getAttackScore()  {
    int score = (int)infantryType*56 + quantity*weight;
    if (infantryType == SPECIALFORCES && checkPerfectSquares(weight)) score += 75;
    score = score + 4;
    if (personalNumber(score) > 7) quantity = ceil(1.2 * quantity);
    else if (personalNumber(score) < 3) quantity = quantity - ceil(0.1 * quantity);
    return (int)infantryType*56 + quantity*weight + ((infantryType == SPECIALFORCES && checkPerfectSquares(weight)) ? 75 : 0);
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
            ", pos=" + pos.str() + "]";
}
//

// 3.5

//
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////