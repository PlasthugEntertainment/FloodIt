#include "game.h"

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
game * CreateGame(unsigned char p_size, unsigned char p_nbColor)
{
	game * result = NULL;

	// 1. Allocation de la m�moire
	result->m_board = (board*)calloc(p_size, sizeof(board));
	result->m_board->m_graph = (node**)calloc(p_size * p_size, sizeof(node*));
	for (unsigned char i = 0; i < p_size * p_size; i++)
	{
		result->m_board->m_graph[i] = (node*)calloc(1, sizeof(node));
	}
	result->m_reducedBoard = (board*)calloc(p_size, sizeof(board));
	result->m_colors = (color*)calloc(p_nbColor, sizeof(color));

	// 2. Initialisation des donn�es et des voisins
	result->m_nbMoves = 0;
	result->m_nbColor = p_nbColor;
	result->m_size = p_size;
	result->m_board->m_size = p_size * p_size;

	for (unsigned char i = 0; i < p_nbColor; i++)
	{
		result->m_colors[i].r = (float)(i / p_nbColor) * 255;
		result->m_colors[i].g = (float)(i / p_nbColor) * 255;
		result->m_colors[i].b = (float)(i / p_nbColor) * 255;
	}

	for (unsigned char i = 0; i < p_size; i++)
	{
		result->m_board->m_graph[i]->m_colorIndex = rand() % p_nbColor;
	}

	return result;
}

/**
 *	@brief Fonction permettant de lib�rer le jeu.
 *
 *	@param	p_game		Jeu � d�sallouer.
 */
void FreeGame(game * p_game)
{
	free(p_game->m_colors);
	FreeBoard(p_game->m_board);
	FreeBoard(p_game->m_reducedBoard);
	free(p_game);
}



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
int ReduceBoard(board * p_boardIn, board ** p_boardOut)
{
	// TODO ...
	// 1. Recherche du nombre de noeud du graphe r�duit

	// 2. Cr�ation du graphe r�duit

	return 1;
}
/**
 *	@brief	Fonction permettant de copier un plateau.
 *
 *	@param	p_board			Plateau � copier.
 *
 *	@return	Le plateau copi�
 */

board * CopyBoard(board * p_board)
{
	board * result = NULL;
	result->m_size = p_board->m_size;

	for (unsigned int i = 0; i < p_board->m_size; i++)
	{
		result->m_graph[i] = p_board->m_graph[i];
	}

	return result;
}

/**
 *	@brief	Fonction permettant de comparer deux plateaux.
 *
 *	@return	1 si les plateau sont identiques,
 *			0 sinon.
 */
int SameBoards(board * p_board1, board * p_board2)
{
	if (p_board1->m_size != p_board2->m_size)
		return 0;

	for (unsigned int i = 0; i < p_board1->m_size; i++)
	{
		if (p_board1->m_graph[i] != p_board2->m_graph[i])
			return 0;
	}

	return 1;
}

/**
 *	@brief	Fonction permettant d'appliquer une couleur au plateau.
 *
 *	@param	p_board			Pointeur sur le plateau.
 *	@param	p_colorIndex	Couleur � appliquer sur le plateau.
 */
void ApplyColor(board ** p_board, unsigned char p_colorIndex)
{
	// TODO ...
}

/**
 *	@brief	Fonction permettant de savoir si le plateau est fini.
 *			La fonction se basera sur un plateau r�duit.
 *
 *	@param	p_board			Plateau r�duit.
 *
 *	@return	1 si le plateau est fini
 *			0 sinon
 */
int IsFinished(board * p_board)
{
	char buff_porc_poulet_poulet = p_board->m_graph[0]->m_colorIndex;

	for (unsigned int i = 1; i < p_board->m_size; i++)
	{
		if (p_board->m_graph[i]->m_colorIndex != buff_porc_poulet_poulet)
			return 0;
	}

	return 1;
}

/**
 *	@brief	Fonction permettant de lib�rer un plateau.
 *
 *	@param	p_board		Plateau � d�sallouer.
 */
void FreeBoard(board * p_board)
{
	FreeGraph(p_board->m_graph, p_board->m_size);
}



				////////////////////////////////////////////////////
				///        FONCTIONS CONCERNANT LE GRAPHE        ///
				////////////////////////////////////////////////////

/**
 *	@brief	Fonction permettant de v�rifier si deux noeuds de graphe sont voisins.
 *
 *	@return	1 si les noeuds sont voisins,
 *			0 sinon.
 */
int IsNeighbours(node * p_node1, node *p_node2)
{
	list * buff_list = p_node1->m_neighbours;
	for (char i = 0; i < p_node1->m_nbNeighbours; i++)
	{
		if (buff_list->m_node == p_node2)
			return 1;
		else
			buff_list = buff_list->m_next;
	}

	return 0;
}

/**
 *	@brief	Fonction permettant de lib�rer un graphe.
 *
 *	@param	p_graph		Graphe � d�sallouer.
 */
void FreeGraph(node ** p_graph, unsigned int p_size)
{
	for (unsigned int i = 0; i < p_size; i++)
	{
		FreeList(p_graph[i]->m_neighbours);
		free(p_graph[i]);
	}
	free(p_graph);
}



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
list * AddNodeList(list * p_list, node * p_node)
{
	if (!p_list)
	{
		list * newNode = (list *)malloc(sizeof(list));
		newNode->m_next = NULL;
		newNode->m_node = p_node;
		return newNode;
	}

	p_list->m_next = AddNodeList(p_list->m_next, p_node);
	return p_list;
}

/**
 *	@brief	Fonction permettant de r�cup�rer la t�te de la liste d'adjacence.
 *
 *	@param	p_list		Pointeur sur la liste d'adjacence.
 *
 *	@return Pointeur sur le noeud de liste extrait.
 */
list * PopList(list ** p_list)
{
	list * result = NULL;

	if (!p_list || !*p_list)
		return NULL;

	result = *p_list;
	*p_list = (*p_list)->m_next;
	result->m_next = NULL;

	return result;
}

/**
 *	@brief	Fonction permettant de lib�rer une liste d'adjacence.
 *
 *	@param	p_list		Liste d'adjacence � d�sallouer.
 */
void FreeList(list * p_list)
{
	if (!p_list)
		return;

	if (p_list->m_next)
		FreeList(p_list->m_next);

	free(p_list);
}
