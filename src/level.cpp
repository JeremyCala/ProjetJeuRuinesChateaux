#include<iostream>
#include<fstream>
#include<sstream>
#include<curses.h>
#include<cmath>
#include"level.h"

level::level(): d_amulet{false} {}

void level::initLevel(const string &fileName)
{
    /* Initialise le niveau n°fileName */

    std::ifstream file("level/"+fileName); //Ouvre le fichier
    char type;

    d_player = adventurer{100,10,10,10};

    if (file.is_open()) {

        std::string ligne;

        while (std::getline(file, ligne)) //Tant que le fichier n'est pas fini
        {
            std::istringstream iss(ligne); //Récupère la ligne
            char type;
            iss >> type; //récupère le premier caractère de la ligne (le type)
            int x, y;
            switch (type) {
                case 'R': { // Si la ligne correspond à une salle
                    int length, width;
                    iss >> x >> y >> length >> width;
                    d_rooms.push_back(room{x,y,length,width});
                    break;
                }
                case '@': { // Si la ligne correspond à l'aventurier
                    iss >> x >> y;
                    d_player.setPos(x, y);
                    break;
                }
                case 'S': { // Si la ligne correspond à un monstre voyant
                    iss >> x >> y;
                    d_monsters.push_back(std::make_unique<sightMonster>(50,10,0.9,x,y));
                    break;
                }
                case 'M': { // Si la ligne correspond à un monstre aveugle
                    iss >> x >> y;
                    d_monsters.push_back(std::make_unique<monster>(20,10,0.9,x,y));
                    break;
                }
                case 'A': { // Si la ligne correspond à l'amulette
                    iss >> x >> y;
                    d_posAmulet = position{x,y};
                    d_amulet = false;
                    break;
                }
                case 'E': { // Si la ligne correspond à la sortie
                    iss >> x >> y;
                    d_exit = position{x,y};
                    break;
                }
                case '$': { // Si la ligne correspond à un tas de pièce
                    iss >> x >> y;
                    d_coins.push_back(position{x,y});
                    break;
                }
                default:
                    std::cerr << "Type de ligne non reconnu : " << type << std::endl;
                    break;
            }
        }
        
        file.close();
    } else {
        std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
    }

    d_amulet = false;
    d_endLevel = false;
}

adventurer level::getPlayer() const
{
    return d_player;
}

int level::getNbRooms() const
{
    return d_rooms.size();
}

room level::getRoom(int n) const
{
    return d_rooms[n];
}

int level::getNbMonsters() const
{
    return d_monsters.size();
}

const std::unique_ptr<monster>& level::getMonster(int n) const
{
    return d_monsters[n];
}

int level::coinsPileNumber() const
{
    return d_coins.size();
}

position level::coinsPile(int n) const
{
    return d_coins[n];
}

position level::getposAmulet() const 
{
    return d_posAmulet;
}

bool level::getAmulet() const 
{
    return d_amulet;
}

position level::getposExit() const
{
    return d_exit;
}

bool level::endLevel() const
{
    return d_endLevel;
}

bool level::gameOver() const
{
    return d_player.getHp()==0;
}

void level::moveAdventurer(int x, int y)
{
    /* Déplace l'aventurier en fonction de l'obstacle rencontré */

    switch (mvinch(d_player.getY() + y, d_player.getX() + x))
    {
    case '.':
    case 'M': //Un monstre ou une case vide
        d_player.move(x,y);
        break;

    case 'A': //Amulette
        d_amulet = true;
        d_player.move(x,y);
        break;

    case 'E': //Sortie
        d_player.move(x,y);
        if (d_amulet == true) //Si l'aventurier possède l'amulette il gagne
        {
            d_endLevel = true;
            clear();
        }
        break;
    case '$': //Tas de pièce
        d_player.move(x,y);
        d_player.increasePurse(10);
        removeCoins(d_player.getX(), d_player.getY()); //Supprime le tas
        break;
    
    default:
        break;
    }
}

void level::updateMonsterPosition(const position &oldPos, const position &newPos)
{
    /* Actualise la position du monstre pour éviter les collisions entre les monstres */
    mvprintw(oldPos.getY(), oldPos.getX(),".");
    mvprintw(newPos.getY(), newPos.getX(),"M");
    refresh();    
    noecho();
}

void level::monsterPlayerFight(tabMonster::iterator& m) 
{
    /* Gère les interactions de combat entre les monstres et le player */

    if ((*m)->getX() == d_player.getX() && (*m)->getY() == d_player.getY()) //Si il y a combat
    {
        d_player.attacked((*m)->attack()); //Aventurier attaque monstre
        (*m)->attacked(d_player.attack()); //Monstre attaqué par aventurier
        d_player.loseSword(); //Perd un point de solidité d'épée

        if (!(*m)->alive()) //Si le monstre est mort
        {
            d_player.kill((*m)->getStrength()); //L'aventurier récupère des stats
            m = d_monsters.erase(m); //Le monstre est supprimé
        } 
        else
            ++m;
    } 
    else 
        ++m;
}

void level::moveMonsters()
{   
    /* Gère les déplacements des monstres ainsi que les combats */

    for(auto monsterIterator = d_monsters.begin(); monsterIterator != d_monsters.end();)
    {
        position old = (*monsterIterator)->getPos();
        (*monsterIterator)->move(d_player.getX(),d_player.getY()); //Le monstre bouge selon la position de l'aventurier
        updateMonsterPosition(old,(*monsterIterator)->getPos());
        monsterPlayerFight(monsterIterator);
    }
}

std::unique_ptr<monster> level::getClosestMonster() const
{
    /* Retourne le monstre à au plus d'une case du player */

    int distmin = 2;
    int indmin = -1;
    for (int i=0; i<getNbMonsters(); ++i)
    {
        int dist = sqrt(pow(d_monsters[i]->getX() - d_player.getX(),2) 
                 + pow(d_monsters[i]->getY() - d_player.getY(),2)); //distance entre monstre et player
        if (dist<distmin)
        {
            distmin = dist;
            indmin = i;
        }
    }
    if (distmin<=1)
        return std::make_unique<monster>(*d_monsters[indmin]);
    else
        return nullptr;
}

void level::removeCoins(int x, int y)
{
    /* Supprime le tas de pièce à la position (x,y) */

    for (auto it = d_coins.begin(); it != d_coins.end(); ++it) {
        if (it->getX() == x && it->getY() == y) {
            d_coins.erase(it);
            break; // Sortir de la boucle une fois que l'élément est supprimé
        }
    }
}

void level::clear()
{
    /*Reinitialise le level en vidant les rooms, les monstres et les tas de pièces*/

    d_monsters.clear();
    d_rooms.clear();
    d_coins.clear();
}