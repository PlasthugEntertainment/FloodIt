/**
 *	@file		game.h
 *
 *	@author		TEXIER Aur�lien
 *
 *	@version	1.0
 *
 *	@brief		Fichier g�rant le jeu d'innondation dans un graphe.
 *
 *	@details	Ce fichier d�clare les structures et fonctions utiles pour cr�er un jeu d'innondation dans un graphe.
 */

#ifndef _GAME_H_
#define _GAME_H_

#include "utils.h"

#define NB_MAX_COLOR		6

						////////////////////////////////////
						///     STRUCTURES UTILISEES     ///
						////////////////////////////////////

typedef struct sNode node;

/**
 *	@brief	Structure repr�sentant les listes d'adjacences.
 */
typedef struct sList
{
	node *			m_node;				/**< Pointeur vers le noeud voisin.										*/
	struct sList *	m_next;				/**< Pointeur vers le noeud de liste suivant.							*/
}list;

/**
 *	@brief	Structure repr�sentant un noeud de graphe.
 */
struct sNode
{
	char			m_colorIndex;		/**< Le num�ro de la couleur appliquer sur le noeud.					*/

	char			m_nbNeighbours;		/**< Le nombre de voisin du noeud.										*/
	list *			m_neighbours;		/**< La liste des voisins (Liste d'adjacence).							*/

	int				m_visited;			/**< Flag pouvant servir � savoir si un noeud a �t� parcouru.			*/
};

/**
 *	@brief	Structure repr�sentant un plateau de jeu.
 */
typedef struct sBoard
{
	node **			m_graph;			/**< Tableau contenant les noeuds du graphe (tableau � 1 dimension)		*/
	unsigned int	m_size;				/**< Nombre de noeud composant le graphe.								*/
}board;

/**
 *	@brief	Structure repr�sentant le jeu.
 */
typedef struct sGame
{
	board *			m_board;			/**< Plateau du jeu.													*/
	board *			m_reducedBoard;		/**< Plateau du jeu apr�s r�duction.									*/
	
	unsigned char	m_size;				/**< Taille du jeu.														*/

	unsigned char	m_nbColor;			/**< Nombre de couleurs utilis�es dans la partie.						*/
	color *			m_colors;			/**< Liste des couleurs utilis�es.										*/

	unsigned char	m_nbMoves;			/**< Nombre de mouvements effectu�s par le joueur.						*/
} game;



				////////////////////////////////////////////////////
				///         FONCTIONS CONCERNANT LE JEU          ///
				////////////////////////////////////////////////////

/**
 *	@brief	Fonction permettant d'allouer et d'initialiser le jeu.
 *	
 *	@param	p_size	Taille du plateau.
 *	@param	p_nbColor	Nombre de couleur utiliser pour la partie.
 *
 *	@return	Le jeu allou� et initialis�.
 */
game * CreateGame(unsigned char p_size, unsigned char p_nbColor);

/**
 *	@brief Fonction permettant de lib�rer le jeu.
 *	
 *	@param	p_game		Jeu � d�sallouer. 
 */
void FreeGame(game * p_game);



				////////////////////////////////////////////////////
				///        FONCTIONS CONCERNANT LE PLATEAU       ///
				////////////////////////////////////////////////////

/**
 *	@brief	Fonction permettant de r�duire un plateau.
 *			Le r�sultat est envoy� via un param�tre sortant pass� par adresse qui est allou� dans la fonction (Attention aux fuites m�moires).
 *
 *	@param	p_boardIn[IN]		Plateau � r�duire.
 *	@param	p_boardOut[OUT]		Plateau r�duit.
 */
int ReduceBoard(board * p_boardIn, board ** p_boardOut);

/**
 *	@brief	Fonction permettant de copier un plateau.
 *
 *	@param	p_board			Plateau � copier.
 *
 *	@return	Le plateau copi�
 */
board * CopyBoard(board * p_board);

/**
 *	@brief	Fonction permettant de comparer deux plateaux.
 *
 *	@return	1 si les plateau sont identiques,
 *			0 sinon.
 */
int SameBoards(board * p_board1, board * p_board2);

/**
*	@brief	Fonction permettant d'appliquer une couleur au plateau � la fa�on du pot de peinture de Paint.
*
*	@param	p_node				Pointeur sur le noeud du plateau.
*	@param	p_targetColor		Couleur de la premi�re case en haut � gauche du plateau.
*	@param	p_replacementColor	Couleur � appliquer sur le plateau.
*/
void FloodFill(node * p_node, unsigned char p_targetColor, unsigned char p_replacementColor);

/**
 *	@brief	Fonction permettant d'appliquer une couleur au plateau.
 *
 *	@param	p_board			Pointeur sur le plateau.
 *	@param	p_colorIndex	Couleur � appliquer sur le plateau.
 */
void ApplyColor(board ** p_board, unsigned char p_colorIndex);

/**
 *	@brief	Fonction permettant de savoir si le plateau est fini.
 *			La fonction se basera sur un plateau r�duit.
 *
 *	@param	p_board			Plateau r�duit.
 *
 *	@return	1 si le plateau est fini
 *			0 sinon
 */
int IsFinished(board * p_board);

/**
 *	@brief	Fonction permettant de lib�rer un plateau.
 *	
 *	@param	p_board		Plateau � d�sallouer. 
 */
void FreeBoard(board * p_board);



				////////////////////////////////////////////////////
				///        FONCTIONS CONCERNANT LE GRAPHE        ///
				////////////////////////////////////////////////////

/**
 *	@brief	Fonction permettant de v�rifier si deux noeuds de graphe sont voisins.
 *	
 *	@return	1 si les noeuds sont voisins,
 *			0 sinon.
 */
int IsNeighbours(node * p_node1, node *p_node2);

/**
 *	@brief	Fonction permettant de lib�rer un graphe.
 *	
 *	@param	p_graph		Graphe � d�sallouer. 
 */
void FreeGraph(node ** p_graph, unsigned int p_size);



				////////////////////////////////////////////////////
				/// FONCTIONS CONCERNANT LES LISTES D'ADJACENCES ///
				////////////////////////////////////////////////////

/**
 *	@brief	Fonction permettant d'ajouter un noeud � une liste d'adjacence (Fonction r�cursive).
 *
 *	@param	p_list		Liste d'adjacence.
 *	@param	p_node		Noeud de liste � ajouter.
 *
 *	@return	liste d'adjacence modifier.
 */
list * AddNodeList(list * p_list, node * p_node);

/**
 *	@brief	Fonction permettant de r�cup�rer la t�te de la liste d'adjacence.
 *
 *	@param	p_list		Pointeur sur la liste d'adjacence.
 *
 *	@return Pointeur sur le noeud de liste extrait.
 */
list * PopList(list ** p_list);

/**
 *	@brief	Fonction permettant de lib�rer une liste d'adjacence.
 *
 *	@param	p_list		Liste d'adjacence � d�sallouer.
 */
void FreeList(list * p_list);

#endif
