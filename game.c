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
 *	@return	Le jeu alloué et initialisé.
 */
game * CreateGame(unsigned char p_size, unsigned char p_nbColor)
{
	game * result = NULL;

	// 1. Allocation de la mémoire
	result->m_board = (board*)calloc(p_size, sizeof(board));
	result->m_board->m_graph = (node**)calloc(p_size * p_size, sizeof(node*));
	for (unsigned char i = 0; i < p_size * p_size; i++)
	{
		result->m_board->m_graph[i] = (node*)calloc(1, sizeof(node));
	}
	result->m_reducedBoard = (board*)calloc(p_size, sizeof(board));
	result->m_colors = (color*)calloc(p_nbColor, sizeof(color));

	// 2. Initialisation des données et des voisins
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
 *	@brief Fonction permettant de libérer le jeu.
 *
 *	@param	p_game		Jeu à désallouer.
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
 *	@brief	Fonction permettant de réduire un plateau.
 *			Le résultat est envoyé via un paramètre sortant passé par adresse qui est alloué dans la fonction (Attention aux fuites mémoires).
 *
 *	@param	p_boardIn[IN]		Plateau à réduire.
 *	@param	p_boardOut[OUT]		Plateau réduit.
 */
int ReduceBoard(board * p_boardIn, board ** p_boardOut)
{
	// TODO ...
	// 1. Recherche du nombre de noeud du graphe réduit

	// 2. Création du graphe réduit

	return 1;
}
/**
 *	@brief	Fonction permettant de copier un plateau.
 *
 *	@param	p_board			Plateau à copier.
 *
 *	@return	Le plateau copié
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
 *	@param	p_colorIndex	Couleur à appliquer sur le plateau.
 */
void ApplyColor(board ** p_board, unsigned char p_colorIndex)
{
	// TODO ...
}

/**
 *	@brief	Fonction permettant de savoir si le plateau est fini.
 *			La fonction se basera sur un plateau réduit.
 *
 *	@param	p_board			Plateau réduit.
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
 *	@brief	Fonction permettant de libérer un plateau.
 *
 *	@param	p_board		Plateau à désallouer.
 */
void FreeBoard(board * p_board)
{
	FreeGraph(p_board->m_graph, p_board->m_size);
}



				////////////////////////////////////////////////////
				///        FONCTIONS CONCERNANT LE GRAPHE        ///
				////////////////////////////////////////////////////

/**
 *	@brief	Fonction permettant de vérifier si deux noeuds de graphe sont voisins.
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
 *	@brief	Fonction permettant de libérer un graphe.
 *
 *	@param	p_graph		Graphe à désallouer.
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
 *	@brief	Fonction permettant d'ajouter un noeud à une liste d'adjacence (Fonction récursive).
 *
 *	@param	p_list		Liste d'adjacence.
 *	@param	p_node		Noeud de liste à ajouter.
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
 *	@brief	Fonction permettant de récupérer la tête de la liste d'adjacence.
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
 *	@brief	Fonction permettant de libérer une liste d'adjacence.
 *
 *	@param	p_list		Liste d'adjacence à désallouer.
 */
void FreeList(list * p_list)
{
	if (!p_list)
		return;

	if (p_list->m_next)
		FreeList(p_list->m_next);

	free(p_list);
}
