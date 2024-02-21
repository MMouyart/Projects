#include <iostream>
#include <fstream>
#include "graphe.h"
#include "sommet.h"
#include <string>
#include <algorithm>
#include <math.h>
#include "arc.h"
#include <vector>
#include <list>
#include <stack>

struct Donne
{
    int x, y;
};


Graphe::Graphe(std::string nom_fich1) ///Constructeur qui va créer le graphe à partir du fichier
{
    int idS, coordX, coordY;
    char nom;
    int e,s,idA;
    Arc a;
    std::ifstream fichier (nom_fich1);
    Sommet* s1;
    fichier>>m_orient; ///lecture et enregisrement de l'orientation et de l'ordre
    fichier>>m_ordre;

    for(int i=0; i<m_ordre; i++) ///enregistrement des sommets avec leurs caractéristiques (ID, Nom, Coordonnées)
    {
        fichier>>idS;
        fichier>>nom;
        fichier>>coordX;
        fichier>>coordY;
        s1=new Sommet(idS, nom, coordX, coordY); ///ajout du nouveau sommet dans le vecteur de Sommet du graphe
        m_sommets.push_back(s1);
    }

    fichier>>m_nbA; ///lecture à la fin du nombre d'arêtes

    for(int k=0; k<m_nbA; k++)
    {
        fichier>>idA; ///lecture procéduriale sans pondération d'abord
        fichier>>e; ///lecure des deux sommets liés à cette arête
        fichier>>s;
        a.idA=idA;
        a.e=e;
        a.p=1;
        a.s=s;
        m_arcs.push_back(a);
        m_sommets[e]->ajouterSucc(m_sommets[s]); ///lecture des noms, poids (initialisé à 1) et enregistrement
///ajout de la nouvelle arête dans le vecteur d'arêtes de notre graph
        if(!m_orient)
            m_sommets[s]->ajouterSucc(m_sommets[e]); ///si il y aune orientation, alors on ajoute le succeseur au premier sommet
    }
}




void Graphe::lire2(std::string nom_fich2)///Méthode qui ajoute une pondération
{
    std::ifstream fichier (nom_fich2);
    fichier>>m_nbA;
    int id,p;
    for(int i=0; i<m_nbA; i++) ///on enregistre toutes les arêtes en lisant les ID et les poids
    {
        fichier>>id;
        fichier>>p;
        for(int j=0; j<m_nbA; j++) ///on parcourt notre vecteur d'arêtes et dès qu'on retrove l'arête dont on doit charge le poids, alors on change le poids de l'arête déjà enregistrée
        {
            if(id == m_arcs[j].idA)
            {
                m_arcs[j].p = p;
            }
        }
    }
}




void Graphe::dessinGraphe() ///Dessine le graphe au format SVG
{
    Svgfile dessin;

	Donne position[m_ordre];
    int couleur;

    for(int i=0 ; i < m_ordre ; i++)
	{
	    couleur = 0;
		for(auto succ : m_sommets[i]->getSuccesseurs())
			couleur++;

		position[i].x = m_sommets[i]->getCoordX() * 100 ;  ///normalisation des coordonnées pour pouvoir les afficher dans l'écran (les coordonnées vont devoir être modifiées)

		position[i].y = m_sommets[i]->getCoordY() * 100 ;

		if(couleur == 0) ///dessin des arêtes si pas d'orientation (dessins de simples lignes sans sens)
			dessin.addDisk(position[i].x,  position[i].y, 7, "black");

		else if(couleur == 1)
			dessin.addDisk(position[i].x,  position[i].y, 7, "blue");

		else if(couleur == 2)
			dessin.addDisk(position[i].x,  position[i].y, 7, "red");

		else if(couleur == 3)
			dessin.addDisk(position[i].x,  position[i].y, 7, "green");

		else if(couleur == 4)
			dessin.addDisk(position[i].x,  position[i].y, 7, "orange");

		else if(couleur == 5)
			dessin.addDisk(position[i].x,  position[i].y, 7, "yellow");

		else if(couleur == 6)
			dessin.addDisk(position[i].x,  position[i].y, 7, "cyan");

		else
			dessin.addDisk(position[i].x, position[i].y, 7, "purple");
	}


	for(int i= m_nbA - 1; i >= 0 ; i--)
	{
		if(m_orient == 0)
        {
			dessin.addLine(position[m_arcs[i].e].x, position[m_arcs[i].e].y, position[m_arcs[i].s].x, position[m_arcs[i].s].y, "black");
        }



	else ///dessin des arêtes si orientation
		{
			dessin.addLine(position[m_arcs[i].s].x, position[m_arcs[i].s].y, position[m_arcs[i].e].x, position[m_arcs[i].e].y, "black");
			///Mettre le triangle
		}



		if(m_arcs[i].p != 0)
			dessin.addText((position[m_arcs[i].s].x + position[m_arcs[i].e].x)/2, (position[m_arcs[i].s].y + position[m_arcs[i].e].y)/2, m_arcs[i].p, "black");


	}


}


///détermine si le graphe est connexe, recoit le sommet de départ pour le BFS et renvoit 1 si le graphe est connexe est 0 sinon
int Graphe::connexe(int num_s0)
{
    /// déclaration de la file
    std::list<int> file;

    /// pour le marquage
    std::vector<int> couleurs((int)m_sommets.size(),0);///0 c'est non visité

    ///pour noter les prédécesseurs : on note les numéros des prédécesseurs (on pourrait stocker des pointeurs sur ...)
    std::vector<int> preds((int)m_sommets.size(),-1);

    ///étape initiale : on enfile et on marque le sommet initial
    couleurs[num_s0]=1;
    file.push_back(num_s0);

    ///tant que la file n'est pas vide
    while(!file.empty())
    {
        ///on défile le prochain sommet
        num_s0 = file.front(); ///Pas sur pour le num_S0
        file.pop_front();



        ///pour chaque successeur du sommet défilé
        for(auto succ : m_sommets[num_s0]->getSuccesseurs())


        {

                 if( couleurs[succ->getNum()] != 1)  ///s'il n'est pas marqué
                 {

                    couleurs[succ->getNum()] = 1;  ///on le marque
                    preds[succ->getNum()]=num_s0;   ///on note son prédecesseur (=le sommet défilé)
                    /// preds[succ->getNum()]=num_s0;
                    file.push_back(succ->getNum());  ///on le met dans la file
               }
        }

    }

    int compteur = 1;
    for(int i=0; i< (int) m_sommets.size(); i++)
    {
        for(int j=0; j< (int) preds.size(); j++)
        {
            if(preds[j] == m_sommets[i]->getNum())
            {
                compteur++;
            }
        }
    }
    if(compteur == (int) m_sommets.size())
    {
        return 1;
    }
    else
    {
        return 0;
    }

}


void Graphe::centraliteDegre() ///Calcul l'indice centralite de degré
{

    for(int i=0 ; i < m_ordre ; i++)
    {
        m_sommets[i]->setDegre(0) ; ///on initialise au début le degré à 0
        m_sommets[i]->setDegre(0) ;
        for( auto succ :  m_sommets[i]->getSuccesseurs())
        {
            m_sommets[i]->setDegre(m_sommets[i]->getDegre()+1);///on parcourt les sommets adjacents et à chaque fois on augmente le degré
        }
        m_sommets[i]->setDegreN( (float) m_sommets[i]->getDegre() / (m_ordre-1)); ///on initialise le degré en le divisant par (ordre-1)
    }

}


void Graphe::vecteurPropre()///Calcul indice vecteur propre
{ ///C'est exactement l'algorithme décris dans le cahier des charges
    float deltaLambda= 1;   ///float Lambda=0;   C’est la variable qui vaut la somme des carrés des degrés des 			voisins d’un sommet le tout à la racine cf. l’algo au dessus qui est dans le cahier des 		charges du projet
    float Lambda=0; /// float deltaLambda= 1;  Définis la variation de Lambda si celui-ci varie à moins de 		0.00001 près l’algorithme se termine
    float stokage=0;    ///float stokage=0;  C’est une variable de stokage qui va permettre de calculer Lambda
  		///float degre[m_ordre];   C’est le degré d’un sommet[i],  CVP (si )
    		///float degreAjouter[m_ordre]; C’est la somme des degrés des sommets adjacents à un sommet[i]

    float degre[m_ordre];
    float degreAjouter[m_ordre];

    for(int i=0 ; i < m_ordre ; i++)
    {
///On met tous les degrAjouter (=c(si )) à 0 et les degre à 1 (=CVP (si ))
        degre[i] = 1;
        degreAjouter[i]=0;

    }

    while((Lambda - 0.00001 )>  deltaLambda ||( Lambda + 0.00001) < deltaLambda ) ///Tant que Lambda varie de 0.00001 près
    {
       deltaLambda =Lambda;
        for(int i=0 ; i < m_ordre ; i++)
        {
            degreAjouter[i]=0;
            stokage=0;
        } ///- La première condition determine les adjacences du sommet S en cherchant dans la 		structure arc si le numéro du sommet actuel correspond au numéro de départ d’un arc 		(ligne 265 et 266)

        for(int i=0 ; i < m_ordre ; i++)
        {
            for( int j=0 ; j < m_nbA ; j++)
            {
                if( i == m_arcs[j].e)
                    degreAjouter[i] = degre[m_arcs[j].s] +  degreAjouter[i];

                if(!m_orient)
                    if( i == m_arcs[j].s)
                        degreAjouter[i] = degre[m_arcs[j].e] + degreAjouter[i];
            }
        }


        for(int i=0 ; i < m_ordre ; i++)
        {
            stokage = degreAjouter[i]*degreAjouter[i] + stokage;
        }
        Lambda=sqrt(stokage);


        for(int i=0 ; i < m_ordre ; i++)
        {
            degre[i] = degreAjouter[i] / Lambda;
        }
    }

   for(int i=0 ; i < m_ordre ; i++)
   {

       m_sommets[i]->setVectPropre(degre[i]);

   }
}





int Graphe::minDistance(int dist[], bool sptSet[])///Pour Djikstra calcul la distance min
{

    int minDistance = INT_MAX, min_index;

    for (int i = 0; i < m_ordre; i++)
        if (sptSet[i] == false && dist[i] <= minDistance)
            minDistance = dist[i], min_index = i;

    return min_index;
}





void Graphe::djikstra( int source, int dist[]) ///L'algorithme de Djikstra tel qu'il est donné dans le cours sauf avec une matrice d'adjacences
{
    ///SErt pour la proxomité et l'intermediarité


    int matrice[m_ordre][m_ordre];
    float prox=0;


    for(int i=0 ; i < m_ordre ; i++) /// ON initialise la matrice d'adjacences
        for( int j=0 ; j < m_ordre ; j++)
            matrice[i][j]=0;


    for( int j=0 ; j < m_nbA ; j++) /// remplit la matrice d'adjacences en lui affectant les poids
    {
            matrice[m_arcs[j].e][m_arcs[j].s] =  m_arcs[j].p;

            if(!m_orient)
                matrice[m_arcs[j].s][m_arcs[j].e] =  m_arcs[j].p;
    }


    ///NOUS AVONS PRIS SUR INTERNET QUELQUES LIGNES DE CODES, BIEN ENTENDU LA SOURCE EST EXPLICITEE DANS LE RENDU

    bool sptSet[m_ordre];

    for (int i = 0; i < m_ordre; i++) ///On met les distances des sommets à l'inf et on met on met tous les sommets à "non visités"
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[source] = 0; ///la distance initiale du sommet  vaut 0

    for (int j = 0; j < m_ordre - 1; j++)
    {
        int u = minDistance(dist, sptSet); ///On selectionne le sommet ayant la + petite distance au sommet initial
        sptSet[u] = true; /// On met que l'on a visité ce sommet


        for (int i = 0; i < m_ordre; i++)
            if(!sptSet[i] && matrice[u][i] && dist[u] != INT_MAX && dist[u] + matrice[u][i] < dist[i]) ///Pour l'ensemble des succeseurs non marqués
            { ///Si le chemin est plus court
                dist[i] = dist[u] + matrice[u][i]; ///On met à jour la distance du sommet i
            }

    }


    for(int i=0; i < m_ordre ; i++)///Si un sommet est isolé il est mit à 0
    {
         if(dist[i]== INT_MAX)
            dist[i]=0;
    }




    for(int i=0; i < m_ordre ; i++) ///On fait la somme des distance d'un sommet initial aux autres pour l'indice de proximité
    {
        prox = dist[i] + prox;
    }



    if(prox == 0)
        m_sommets[source]->setCentralProx(0.000000) ;

    else
    {
        m_sommets[source]->setCentralProx((float)1.00000/prox) ;
        m_sommets[source]->setCentralProx(1.00001 *  m_sommets[source]->getCentralProx()) ;
    }





}





void Graphe::afficher()///AFFICHE LE graphe en console
{
    int k=0;
    std::cout<<"nombre de sommet : "<<m_ordre<<std::endl;
    for(int k=0; k<m_ordre; k++)
    {
        std::cout<<"Sommet : "<<m_sommets[k]->getNum();
        std::cout<<"   Nom : "<<m_sommets[k]->getNom();
        std::cout<<"   Coord : "<<m_sommets[k]->getCoordX();
        std::cout<<" "<<m_sommets[k]->getCoordY();
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"nombre d'aretes : "<<m_nbA<<std::endl;

    for(int u=0; u<m_nbA; u++)
    {
        std::cout<<"arete : "<<m_arcs[u].idA<<"  entree : "<<m_arcs[u].e<<"  sortie : "<<m_arcs[u].s<<"  poids : "<<m_arcs[u].p<<std::endl;
    }

    std::cout<<std::endl;
    k=connexe(k); ///Pour savoir si il est connexe

    if(k == 1) { std::cout<<" Le graphe est connexe"<<std::endl;}
    if(k == 0) { std::cout<<" Le graphe n'est pas connexe"<<std::endl;}
}





void Graphe::comparerIndice(std::ofstream &ofs)///Compare les indices avant et apres supression d'une arrete
{
    system("cls");
    std::cout<<" Les nouveauxs indices de centralite :"<<std::endl;
    std::cout<<std::endl;
    central(ofs); ///
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<" Les ancienn indices de centralite :"<<std::endl;
    std::cout<<"Sommet    Degre    Degre-N     VectPropre      Proximite     Proximite-N     Centralité     Centralité-N" << std::endl;
    for(int k=0; k<m_ordre;k++)
    {

        std::cout<<m_sommets[k]->getNum() << "          " <<m_sommets[k]->getAncienDegre()<< "         ";
        if(m_sommets[k]->getAncienCentralProx() == 0) ///Si un sommet est isolé il sera mis à 0
        {
            std::cout<< "0.00" ;
            std::cout<< "      "<< "0.000000" ;
            std::cout<<"        " <<"0.000000" << "      "<< "0.000000" << "         "<<"0.00000"<<"      "<<"0.00000"<<std::endl;
        }

        else ///Sinon
        {
            std::cout<<m_sommets[k]->getAncienDegreN() ;
            std::cout<< "      "<< m_sommets[k]->getAncienVectPropre() ;
            std::cout<<"        " << m_sommets[k]->getAncienCentralProx() << "      "<< m_sommets[k]->getAncienCentralProx() * (m_ordre-1);
             std::cout<<"         "<< m_sommets[k]->getAncienIntermediarite()<<"      "<< m_sommets[k]->getAncienIntermediarite()/(m_ordre * m_ordre - 3*m_ordre + 2)<<std::endl;
        }

    }

}




void Graphe::indiceSauvegarde()///Sauvegarde les anciens indices dans des variables
{
    for(int i = 0; i<m_ordre; i++)
    {

        m_sommets[i]->setAncienCentralProx(m_sommets[i]->getCentralProx());
        m_sommets[i]->setAncienDegre(m_sommets[i]->getDegre());
        m_sommets[i]->setAncienDegreN(m_sommets[i]->getDegreN());
        m_sommets[i]->setAncienIntermediarite(m_sommets[i]->getIntermediarite());
        m_sommets[i]->setAncienVectPropre(m_sommets[i]->getVectPropre());
    }
}



void Graphe::central(std::ofstream &ofs)///Affiche tous les indices de centralité
{
    int dist[m_ordre];

    centraliteDegre();
    vecteurPropre();
    for(int i=0; i<m_ordre;i++)
        djikstra(i, dist);

    intermediarite();



    std::cout<<"Sommet    Degre    Degre-N     VectPropre      Proximite     Proximite-N     Centralité    Centralité-N" << std::endl;
    for(int k=0; k<m_ordre;k++)
    { m_sommets[k]->setCentralite(m_sommets[k]->getCentralProx() * (m_ordre-1),m_sommets[k]->getIntermediarite()/(m_ordre * m_ordre - 3*m_ordre + 2));
ofs<<"Sommet    Degre    Degre-N     VectPropre      Proximite     Proximite-N     Centralité    Centralité-N\n" ;

        std::cout<<m_sommets[k]->getNum() << "          " <<m_sommets[k]->getDegre()<< "         ";
        if(m_sommets[k]->getCentralProx() == 0) ///Si un sommet est isolé il sera mis à 0
        {
            std::cout<< "0.00" ;
            std::cout<< "      "<< "0.000000" ;
            std::cout<<"        " <<"0.000000" << "      "<< "0.000000" << "         "<<"0.00000"<<"      "<<"0.00000"<<std::endl;
        ofs<<m_sommets[k]->getNum() ;ofs<<"0.00"; ofs<<"      0.000000";
        ofs<<"        0.000000";ofs<<"      0.000000";ofs<<"         0.00000";ofs<<"      0.00000";ofs<<"\n";
        ofs<<"\n\nLa valeur finale de centralite du sommet ";ofs<<m_sommets[k]->getNom();ofs<<" vaut: ";ofs<<"0";ofs<<"\n";
        ofs<<"\n";ofs<<"\n";}

        else ///Sinon
        {
            std::cout<<m_sommets[k]->getDegreN() ;
            std::cout<< "      "<< m_sommets[k]->getVectPropre() ;
            std::cout<<"        " << m_sommets[k]->getCentralProx() << "      "<< m_sommets[k]->getCentralProx() * (m_ordre-1);
             std::cout<<"         "<< m_sommets[k]->getIntermediarite()<<"      "<< m_sommets[k]->getIntermediarite()/(m_ordre * m_ordre - 3*m_ordre + 2)<<std::endl;
        std::cout<<"\n\nLa valeur finale de centralite du sommet "<<m_sommets[k]->getNom()<<" vaut: "<<m_sommets[k]->getCentralite()<<std::endl;

        ofs<<m_sommets[k]->getNum() ;
        ofs<< "           " ;
        ofs<<m_sommets[k]->getDegre();
        ofs<<"             ";
        ofs<<m_sommets[k]->getDegreN();
        ofs<<"                  ";
        ofs<<m_sommets[k]->getVectPropre() ;
        ofs<<"      ";
        ofs<<m_sommets[k]->getCentralProx();
        ofs<<"      ";
        ofs<<m_sommets[k]->getCentralProx() * (m_ordre-1);
        ofs<<m_sommets[k]->getIntermediarite();
        ofs<<"       ";
        ofs<<m_sommets[k]->getIntermediarite()/(m_ordre * m_ordre - 3*m_ordre + 2);
        ofs<<"\n";
        ofs<<"\n\nLa valeur finale de centralite du sommet ";ofs<<m_sommets[k]->getNom();ofs<<" vaut: ";ofs<<m_sommets[k]->getCentralite();
        ofs<<"\n";
        ofs<<"\n";


        /*std::cout<<"    Degre  : "<< m_sommets[k]->getDegre()<< "    Degre normalise : "<<  m_sommets[k]->getDegreN();
        std::cout<<"    Degre  : "<< m_sommets[k]->getDegre()<< "    Degre normalise : "<<  m_sommets[k]->getDegreN();
        std::cout<<"    VectPropre : "<<m_sommets[k]->getVectPropre();
        std::cout<<"    Proximite Norma : "<<m_sommets[k]->getCentralProx() * (m_ordre-1);
        std::cout << std::endl;*/
    }

    }ofs.close();}




void Graphe::suppArrete(int num, std::string nom_fich1, std::string nom_fich2) ///Supprime une arrete en sauvegarrdant le fichier pour le supprimer et le réecrire avec les modifications nécessaire
{


    if(num > m_ordre)
    {
        std::cout<<"Cette arrete n'existe pas"<<std::endl;
    }
    else
    {

        ///Pour le fichier de topologie :
        int blindage = 0;
        int idS, coordX, coordY;
        char nom;
        int e,s,idA,ligne=0;
        std::ifstream fichier(nom_fich1);
        fichier>>m_orient;
        ligne++;
        fichier>>m_ordre;
        ligne++;
        for(int i=0; i<m_ordre; i++)
        {
            ligne++;
            fichier>>idS;
            fichier>>nom;
            fichier>>coordX;
            fichier>>coordY;

        }

        fichier>>m_nbA;
        ligne++;
        int ligneVrai;
        for(int k=0; k<m_nbA; k++)
        {
            ligne++;
            fichier>>idA;
            if(idA == num)
            {
                ligneVrai = ligne;
                blindage = 1;///Si l'arrete à supprimer existe
            }
            fichier>>e;
            fichier>>s;

        }


        if(blindage == 1)///Si l'arrete à supprimer existe
        {
            m_nbA = m_nbA - 1;
            suppLigneGraphe(nom_fich1, ligneVrai); ///Methode qui modifie le ficheir graphe
        }


        ///Pour le fichier de pondération :

        std::ifstream fichier2(nom_fich2);
        int ligne2 = 0;
        int ligneVrai2;
        fichier2>>m_nbA;
        m_nbA = m_nbA - 1;
        ligne2++;
        int id,p;
        for(int i=0; i<m_nbA; i++)
        {
            ligne2++;
            fichier2>>id;
            if(id == num)
            {
                ligneVrai2 = ligne2;
            }
            fichier2>>p;

        }
        if(blindage == 1)///Si l'arrete à supprimer existe
            suppLignePoids(nom_fich2, ligneVrai2);///On appel la méthode qui modifiera le fichier pondé

    }
}



void Graphe::suppLigneGraphe(std::string nom_fich, int ligneVrai)  ///trouvé sur internet avec lien dans le rapport
{ ///réecris le fichier graphe à l'identique exepté qu'il change le nombre d'arrete et supprime la ligne de l'arrete modifier dans le fichier graphe
    std::string Fich2 = ""; //Variable contenant le texte à réécrire dans le fichier
    std::ifstream fichier( nom_fich);
    std::string variableConvesrtion = std::to_string(m_nbA)  ;



    if (fichier) //Si le fichier est trouvé
    {
        std::string Fich;
        int ligne = 0;
        while (std::getline(fichier, Fich)) //on parcours le fichier et on initialise line à la ligne actuelle
        {
            ligne++;
            if(ligne == m_ordre + 3)
            Fich2 += variableConvesrtion + "\n";

            else///On multiplie par 1.00001 pour applique plusieurs décimales
                if(ligne != ligneVrai) //Si la ligne atteinte est différente de la ligne à supprimer...
                    Fich2 += Fich + "\n"; //On ajoute le contenu de la ligne dans le contenu à réécrire
        }
    }
    fichier.close(); //On ferme le fichier en lecture

    std::ofstream fichier2(nom_fich); //On ouvre ce même fichier en écriture
    fichier2 << Fich2; //On écris le texte dedans
    fichier2.close(); //et on ferme le fichier
}




void Graphe::suppLignePoids(std::string nom_fich, int ligneVrai)  ///trouvé sur internet avec lien dans le rapport
{///réecris le fichier poids à l'identique exepté qu'il change le nombre d'arrete et supprime la ligne de l'arrete modifier dans le fichier poids
    std::string Fich2 = ""; //Variable contenant le texte à réécrire dans le fichier
    std::ifstream fichier( nom_fich);
    std::string variableConvesrtion = std::to_string(m_nbA)  ;



    if (fichier) //Si le fichier est trouvé
    {
        std::string Fich;
        int ligne = 0;
        while (std::getline(fichier, Fich)) //on parcours le fichier et on initialise line à la ligne actuelle
        {
            ligne++;
            if(ligne == 1)
            Fich2 += variableConvesrtion + "\n";

            else
                if(ligne != ligneVrai) //Si la ligne atteinte est différente de la ligne à supprimer...
                    Fich2 += Fich + "\n"; //On ajoute le contenu de la ligne dans le contenu à réécrire
        }
    }
    fichier.close(); //On ferme le fichier en lecture

    std::ofstream fichier2(nom_fich); //On ouvre ce même fichier en écriture
    fichier2 << Fich2; //On écris le texte dedans
    fichier2.close(); //et on ferme le fichier
}



void Graphe::intermediarite() ///Fonction calculant l'indice d'intermediarité
{
    int tab[m_ordre];
    int tabCentre[m_ordre];
    int centraliteDeJ[m_ordre]= {0};




    for(int i =0 ; i < m_ordre ; i++)  ///Algo principal n*n*n
    {
        djikstra(i, tab);  ///calcul du PCC entra sommet A et B
        for(int j =0; j < m_ordre; j++)
        {
            djikstra(j, tabCentre); ///PCC entre sommet B et C
            for(int k=0; k<m_ordre;k++)
            {
                if(tab[j] + tabCentre[k] == tab[k]) ///Si PCC(A,B)+PCC(B,C)=PCC(A,C) alors le sommet B est intermédiaire
                    centraliteDeJ[j]++;
            }
        }
    }

    for(int i=0; i<m_ordre;i++)
    {
        m_sommets[i]->setIntermediarite((float)1.00001 * centraliteDeJ[i]) ;  ///On multiplie par 1.00001 pour applique plusieurs décimales

    }
}

