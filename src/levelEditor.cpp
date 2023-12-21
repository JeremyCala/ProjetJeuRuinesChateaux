#include<curses.h>
#include<fstream>
#include"levelEditor.h"
#include"screener.h"

bool levelEditor::createLevel(const screener &S, int numLevel) const
{
    /* Créer un nouveau niveau */

    bool validLevel = false; //le niveau n'est pas valide
    S.initCreateLevel();
    S.showCreateLevel();
    S.moveCursor(50,15);
    int x, y;
    while (!validLevel) //tant que le niveau n'est pas valide
    {
        S.getCursorPos(x,y); //récupère les coordonnées du curseur dans x et y
        S.blockInput(); //empeche l'affichage des saisies non désirées

        if(x<S.length() && y<S.width()) //si on est dans la fenetre de création
        {
            char choice = getch();
            switch (choice)
            {
                case '\n': //sauvegarde
                    validLevel = isvalidLevel(S); // verifie si le niveau est valide
                    if (!validLevel)
                    {
                        S.showSaveError(); //message d'erreur
                        S.moveCursor(x,y); //replace le curseur
                    }
                    break;
                case 27:  //echap
                    return false;
                case 'z': //haut
                    if (y>1)
                        S.moveCursor(x,y-1);
                    break;
                case 'q': //gauche
                    if (x>1)
                        S.moveCursor(x-1,y);
                    break;
                case 'd': //droite
                    if (x<S.length()-2)
                        S.moveCursor(x+1,y);
                    break;
                case 'x': //bas
                    if (y<S.width()-2)
                        S.moveCursor(x,y+1);
                    break;
                case '@': //aventurier
                    if (x<S.length()-1)
                        S.print(x,y,"@");
                    break;
                case 'S': //monstre voyant
                    if (x<S.length()-1)
                        S.print(x,y,"S");
                    break;
                case 'M': //montre aveugle
                    if (x<S.length()-1)
                        S.print(x,y,"M");
                    break;  
                case '.': //sol
                    if (x<S.length()-1)
                        S.print(x,y,".");
                    break; 
                case '#': //mur
                    if (x<S.length()-1)
                        S.print(x,y,"#");
                    break;  
                case 'A': //amulette
                    if (x<S.length()-1)
                        S.print(x,y,"A");
                    break;
                case 'E': //sortie
                    if (x<S.length()-1)
                        S.print(x,y,"E");
                    break;
            }
        }
    }

    saveLevel(numLevel); //sauvegarde du niveau
    return true;
}

bool levelEditor::isvalidLevel(const screener &S) const
{
    /*Vérifie la présence d'un seul aventurier, d'une seule amulette et d'une seule sortie*/

    int adventurerCpt = 0;
    int amuletCpt = 0;
    int exitCpt = 0;
    
    for(int i = 1; i < S.width()-1; ++i)
        for(int j = 1; j < S.length()-1; ++j)
        {
            switch (S.getChar(j,i)) // caractère en (j,i)
            {
                case '@':
                    if (++adventurerCpt>1) //si c'est le 2ème aventurier
                        return false;
                    break;
                case 'A':
                    if (++amuletCpt>1) //si c'est la 2ème amulette
                        return false;
                    break;
                case 'E':
                    if (++exitCpt>1) //si c'est la 2ème sortie
                        return false;
                    break;
            }
        }

    return true;
}

void levelEditor::saveLevel(int numLevel) const
{
    /* Sauvegarde le niveau dans un fichier de nom numLevel.txt */
}