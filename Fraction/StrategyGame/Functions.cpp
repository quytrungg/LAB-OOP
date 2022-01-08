#include "Header.h"

Soldier::Soldier() {
    this->HP = 0;
    this->ATK = 0;
}

void Visitor::selectAttack(Soldier* s) {
    if (typeid(*s) == typeid(Swordman)) {
        attack(*((Swordman*)s));
    }
    else if (typeid(*s) == typeid(Knight)) {
        attack(*((Knight*)s));
    }
    else if (typeid(*s) == typeid(Spikeman)) {
        attack(*((Spikeman*)s));
    }
    else return;
}

Swordman::Swordman(int hp, int atk): Soldier(hp, atk){}

void Swordman::attack(Swordman& s) {
    s.hitBy(*this);
    if (s.isAlive()) this->hitBy(s);
}

void Swordman::attack(Knight& k) {
    k.hitBy(*this);
    if (k.isAlive()) this->hitBy(k);
}

void Swordman::attack(Spikeman& s) {
    s.hitBy(*this);
    if (s.isAlive()) this->hitBy(s);
}

void Swordman::hitBy(Swordman& s) {
    this->sethp(HP - s.getatk());
}

void Swordman::hitBy(Knight& k) {
    this->sethp(HP - k.getatk() - 10);
}

void Swordman::hitBy(Spikeman& s) {
    this->sethp(HP - s.getatk());
}

void Swordman::attackSoldier(Soldier* s) {
    if (this->isAlive()) this->selectAttack(s);
}

std::string Swordman::displaySoldier() {
    std::stringstream ss;
    ss << "Swordman (HP: " << HP << " ATK: " << ATK << ")";
    return ss.str();
}

Knight::Knight(int hp, int atk): Soldier(hp, atk) {}

void Knight::attack(Swordman& s) {
    s.hitBy(*this);
    if (s.isAlive()) this->hitBy(s);
}

void Knight::attack(Knight& k) {
    k.hitBy(*this);
    if (k.isAlive()) this->hitBy(k);
}

void Knight::attack(Spikeman& s) {
    s.hitBy(*this);
    if (s.isAlive()) this->hitBy(s);
}

void Knight::hitBy(Swordman& s) {
    this->sethp(HP - s.getatk());
}

void Knight::hitBy(Knight& k) {
    this->sethp(HP - k.getatk());
}

void Knight::hitBy(Spikeman& s) {
    this->sethp(HP - s.getatk() - 25);
}

void Knight::attackSoldier(Soldier* s) {
    if (this->isAlive()) this->selectAttack(s);
}

std::string Knight::displaySoldier() {
    std::stringstream ss;
    ss << "Knight (HP: " << HP << " ATK: " << ATK << ")";
    return ss.str();
}

Spikeman::Spikeman(int hp, int atk): Soldier(hp, atk) {}

void Spikeman::attack(Swordman& s) {
    s.hitBy(*this);
    if (s.isAlive()) this->hitBy(s);
}

void Spikeman::attack(Knight& k) {
    k.hitBy(*this);
    if (k.isAlive()) this->hitBy(k);
}

void Spikeman::attack(Spikeman& s) {
    s.hitBy(*this);
    if (s.isAlive()) this->hitBy(s);
}

void Spikeman::hitBy(Swordman& s) {
    this->sethp(HP - s.getatk() - 12);
}

void Spikeman::hitBy(Knight& k) {
    this->sethp(HP - k.getatk());
}

void Spikeman::hitBy(Spikeman& s) {
    this->sethp(HP - s.getatk());
}

void Spikeman::attackSoldier(Soldier* s) {
    if(this->isAlive()) this->selectAttack(s);
}

std::string Spikeman::displaySoldier() {
    std::stringstream ss;
    ss << "Spikeman (HP: " << HP << " ATK: " << ATK << ")";
    return ss.str();
}

void Player::displayPieces() {
    for (int i = 0; i < this->pieces().size(); i++) {
        std::cout << this->pieces()[i]->displaySoldier() << " ";
    }
}

bool SwordmanRule::satisfaction(Player p) {
    int count = 0;
    for (int i = 0; i < p.pieces().size(); i++) {
        count += (typeid(*p.pieces()[i]) == typeid(Swordman));
    }
    return count == 3;
}

void SwordmanRule::applyPieces(Player p) {
    if (!this->satisfaction(p)) return;
    else for (int i = 0; i < p.pieces().size(); i++) p.pieces()[i]->setatk(p.pieces()[i]->getatk() * 3);
}

bool KnightRule::satisfaction(Player p) {
    int count = 0;
    for (int i = 0; i < p.pieces().size(); i++) {
        count += (typeid(*p.pieces()[i]) == typeid(Knight));
    }
    return count == 3;
}

void KnightRule::applyPieces(Player p) {
    if (!this->satisfaction(p)) return;
    else for (int i = 0; i < p.pieces().size(); i++) p.pieces()[i]->setatk(p.pieces()[i]->getatk() * 2);
}

bool SpikemanRule::satisfaction(Player p) {
    int count = 0;
    for (int i = 0; i < p.pieces().size(); i++) {
        count += (typeid(*p.pieces()[i]) == typeid(Spikeman));
    }
    return count == 3;
}

void SpikemanRule::applyPieces(Player p) {
    if (!this->satisfaction(p)) return;
    else for (int i = 0; i < p.pieces().size(); i++) {
        p.pieces()[i]->setatk(p.pieces()[i]->getatk() * 5);
        p.pieces()[i]->sethp(p.pieces()[i]->gethp() * 2);
    }
}

Game::Game() {
    this->rules.push_back(new SwordmanRule());
    this->rules.push_back(new KnightRule());
    this->rules.push_back(new SpikemanRule());
    this->turns = 0;
}

void Game::startGame() {
    RandomIntegerGenerator _rng;
    for (int i = 0; i < 3; ++i) {
        int temp = _rng.next(0, 2);
        switch (temp) {
        case 0:
            this->red.pieces().push_back(new Swordman(SWHP, SWATK));
            break;
        case 1:
            this->red.pieces().push_back(new Knight(KNHP, KNATK));
            break;
        case 2:
            this->red.pieces().push_back(new Spikeman(SPHP, SPATK));
            break;
        }
    }
    for (int i = 0; i < 3; ++i) {
        int temp = _rng.next(0, 2);
        switch (temp) {
        case 0:
            this->blue.pieces().push_back(new Swordman(SWHP, SWATK));
            break;
        case 1:
            this->blue.pieces().push_back(new Knight(KNHP, KNATK));
            break;
        case 2:
            this->blue.pieces().push_back(new Spikeman(SPHP, SPATK));
            break;
        }
    }
    this->applyRules(this->red);
    this->applyRules(this->blue);
}

void Game::playGame() {
    RandomIntegerGenerator _rng;
    int temp = _rng.next(0, 1), count = 0;
    do{
        int redturn = _rng.next(0, 2), blueturn = _rng.next(0, 2);
        if (temp % 2 == 0) {
            this->red.pieces()[redturn]->attackSoldier(this->blue.pieces()[blueturn]);
            //this->blue.pieces()[blueturn]->attackSoldier(this->red.pieces()[redturn]);
        }
        else if (temp % 2 == 1) {
            this->blue.pieces()[blueturn]->attackSoldier(this->red.pieces()[redturn]);
            //this->red.pieces()[redturn]->attackSoldier(this->blue.pieces()[blueturn]);
        }
        temp++;
        count++;
        if (count == 2) {
            this->turns++;
            count = 0;
        }
    } while (this->turns < 3);
}

void Game::displayGame() {
    std::cout << "After " << this->turns << " turns,\n";
    std::cout << "Red team: ";
    this->red.displayPieces();
    std::cout << "\nBlue team: ";
    this->blue.displayPieces();
    std::cout << "\n";
    if (this->checkWin() == 1) {
        std::cout << "";
    }
    else if (this->checkWin() == -1) {
        std::cout << "";
    }
    else std::cout << "";
}

void Game::applyRules(Player p) {
    for (int i = 0; i < this->rules.size(); i++) {
        if (this->rules[i]->satisfaction(p)) this->rules[i]->applyPieces(p);
    }
}

int Game::checkWin() {
    int check = 0;
    for (auto i : this->red.pieces()) {
        check += i->isAlive();
    }
    if (check == 0) return 1; //blue team wins
    check = 0;
    for (auto i : this->blue.pieces()) {
        check += i->isAlive();
    }
    if (check == 0) return -1; //red team wins
    return 0;
}
