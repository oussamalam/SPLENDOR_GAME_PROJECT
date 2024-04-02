#include "player.h"
#include <stdlib.h>
#include <stdio.h>
#define PLAYER_MAX_TOKENS 10

// Fonction pour initialiser un joueur les tokens on les initialise a 00000 et points de victoires a 0

void init_player(struct player_t *play)
{

    // unsigned int tok0[MAX_COLORS]={0,0,0,0,0};

    play->victory_points_of_player = 0;
    play->num_tokens = 0;
    play->num_builders = 0;
    for (int i = 0; i < PLAYER_MAX_TOKENS; ++i)
    {
        for (int j = 0; j < MAX_COLORS; ++j)
            play->tokens[i].c[j] = 0;
    }
    for (int j = 0; j < MAX_COLORS; ++j)
    {
        play->colors_global_tok[j] = 0;
        play->colors_global_buil[j] = 0;
    }
    for (int l = 0; l < MAX_COLORS; ++l)
    {
         for (int j = 0; j < PLAYER_MAX_TOKENS; ++j)
             play->colors_global_tok[l] += play->tokens[j].c[l];
    }

    // for (int j = 0; j < NUM_COLORS; ++j)
    // {
    //     if (play->builders[j] != NULL)
    //         play->colors_global_buil[play->builders[j]->provides.c] += play->builders[j]->provides.n;
    // }
}

int voisins(struct point p, struct point L[4]) // cherche les voisins de p dans le plateau
{
    struct point point0;
    point0.i = 0;
    point0.j = 0;
    for (int f = 0; f < 4; ++f)
    {
        L[f] = point0; //    L={{0,0},{0,0},{0,0},{0,0}}
    }
    int m = 0; // la valeur retourné(=nombres de voisins de p  qui est <=4)
    int i = p.i;
    int j = p.j;

    if (j - 1 > 0) // voisin gauche
    {
        L[0].i = i;
        L[0].j = j - 1;
        m += 1;
    }
    if (j + 1 < 4) // voisin droite
    {
        L[1].i = i;
        L[1].j = j + 1;
        m += 1;
    }
    if (i + 1 < 4) // voisin  bas
    {
        L[2].i = i + 1;
        L[2].j = j;
        m += 1;
    }
    if (i - 1 > 0) // voisin haut
    {
        L[3].i = i - 1;
        L[3].j = j;
        m += 1;
    }
    return m;
}

// Fonction pour qu'un joueur prenne des jetons
void pick_tokens(struct player_t *player, struct token_in_market market[5][5]) // la liste tokens contient just les 3positions dans la market des 3tokens a picker
{
    struct token_t token_zero = {{0, 0, 0, 0, 0}};
    // problème s'il reste moins de 3 tokens sur le plateau non ?
    int etat=0;
    while ((etat=0) && (player->num_tokens < PLAYER_MAX_TOKENS))

    {
        int a = genererNombreAleatoire(0, 4);
        int b = genererNombreAleatoire(0, 4);
        int j = 0;
        while (j < PLAYER_MAX_TOKENS)
        {
            if ((token_equals(player->tokens[j], token_zero) == 1) && (market[a][b].etat == 1))
            {
                player->tokens[j] = market[a][b].token;
                etat=1;
                // peut être créer une fonction ça serait plus facile jsp
                player->colors_global_tok[market[a][b].a] += market[a][b].n;
                remove_token_from_market(market[a][b].token, market);
                // token_display(player->tokens[j], "  -");
                j++;
                etat++;
                // on a picker un
                struct point p1 = {a, b};
                struct point L1[4];
                int m1 = voisins(p1, L1);
                if (m1 != 0 && j < PLAYER_MAX_TOKENS && etat < 3)
                {
                    int r1 = genererNombreAleatoire(0, m1 - 1);
                    int c = L1[r1].i; // abscice du voisin choisi aleatoirement
                    int d = L1[r1].j; // son ordonné
                    player->tokens[j + 1] = notre_market[c][d].token;
                    player->colors_global_tok[market[c][d].a] += market[a][b].n;
                    //token_display(player->tokens[j + 1], "  -");
                    etat++;

                    // token_display(player->tokens[j + 1], "  -")
                    j++;
                    // on a pické deux pour le moment
                    struct point p2 = {a, b};
                    struct point L2[4];
                    int m2 = voisins(p2, L2);
                    if (m2 != 0 && j < PLAYER_MAX_TOKENS && etat < 3)
                    {
                        int r2 = genererNombreAleatoire(0, m2 - 1);
                        int e = L2[r2].i;
                        int f = L2[r2].j;
                        player->tokens[j + 1] = notre_market[e][d].token;
                        player->colors_global_tok[market[c][f].a] += market[a][b].n;
                        remove_token_from_market(market[e][f].token, market);
                        // token_display(player->tokens[j + 1], "  -");
                        j++;
                        etat++;
                        // on a pické trois tokens pour le moment  on sort de la boucle
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break; // on sort de la boucle si un token n'a pas de voisins
                }
            }
            else
                j++;
        }
    }
    player->num_tokens += 2;
}

// Fonction pour qu'un joueur embauche un architecte (builder)
void hire_builder(struct player_t *player, struct builder_t *builder, struct guild_t *guild)
{
    player->builders[player->num_builders] = builder;
    player->victory_points_of_player += builder->points;
    unsigned int num1=builder->requires.c; //le couleur du requires
    unsigned int num2=0;
    for(unsigned int i=0;i<num_builders();i++)
    {
        if(player->builders[i]->provides.c==num1)
        {
            num2+=player->builders[i]->provides.n;
        }
    }
    for(int l=0;l<PLAYER_MAX_TOKENS;l++)
    {
        if(num2!=0 && player->tokens[l].c[num1]!=0)
        {
            num2-=player->tokens[l].c[num1];
            remetre_token_in_market(player->tokens[l],notre_market);

        }
    }
    remove_builder_from_guild(builder, guild);
    player->num_builders++;
}

int possible(struct player_t *player, struct piles_t *pile, struct guild_t *guild)
{
    int p = 0;
    for (int i = 0; i < MAX_BUILDERS_AVAILABLE_PER_LVL; i++)
    {
        // problème ça fait un builder de couleur noire je crois 
        enum color_t o;
        if (pile->pile1.disponible[i] != NULL)
            o = pile->pile1.disponible[i]->requires.c;
        else {
            o=0;
        }
        unsigned int num = player->colors_global_tok[o] + player->colors_global_buil[o];
        // Pour la pile 1 , pb de comparaison ce ne sont pas les mêmes éléments
        if (pile->pile1.disponible[i] != NULL)
        {
            if (num > pile->pile1.disponible[i]->requires.n)
            {
                hire_builder(player, pile->pile1.disponible[i], guild);
                pile->pile1.disponible[i] = NULL;
                available_shop(pile,1);
                ++p;
                return p;
            }
        }
    }
        for (int j = 0; j < MAX_BUILDERS_AVAILABLE_PER_LVL; j++)
        {

            enum color_t o;
        if (pile->pile2.disponible[j] != NULL)
            o = pile->pile2.disponible[j]->requires.c;
        else{ 
            o=0;
        }
            unsigned int num = player->colors_global_tok[o] + player->colors_global_buil[o];
            // Pour la pile 2
            if (pile->pile2.disponible[j] != NULL)
            {
                if (num > pile->pile2.disponible[j]->requires.n)
                {
                    hire_builder(player, pile->pile2.disponible[j], guild);
                    if (pile->pile1.size > 0)
                    {

                        pile->pile2.disponible[j] = NULL;
                        pile->pile2.disponible[j] = pile->pile2.level[pile->pile2.size - 1];
                        pile->pile2.size -= 1;
                        return p;
                    }
                }
            }
        }
    
    return p;
}

struct builder_t *builder_shop(struct builder_t *builders[MAX_BUILDERS], unsigned int n)
{
    int k = genererNombreAleatoire(0, n);
    return builders[k];
}

void make_tab(enum color_t c, unsigned int color[NUM_COLORS])
{
    for (unsigned int i = 0; i < NUM_COLORS; ++i)
    {
        if (i == c)
            color[i] = 2;
        else
            color[i] = 0;
    }
}
// Ici, on suppose que le player peut acheter mais on va déterminer si le coût d'achat est optimal ou non . On considère qu'il est optimal
// si on ne perd pas de partie de la couleur. On ne prend pas en compte les provides pour l'instant
int opti_cost(struct builder_t *builder, struct player_t *player)
{

    /* dans un premier temps les tokens sont monochromes on pourra faire une boucle pour vérifier que les autres couleurs
    ont une valeur nulle ou non plus tard  pour éviter de gaspiller des couleurs*/
    if (player->colors_global_tok[builder->requires.c] == builder->requires.n)
        return 1; // ici ça sera vrai dès qu'on peut acheter même uniquement avec des tokens donc pas opti
    else if (player->colors_global_tok[builder->requires.c] > builder->requires.n && builder->requires.n % 2 != 0)
    {
        int comp = 0;
        int simp = 0;
        unsigned int f_token[NUM_COLORS];
        make_tab(builder->requires.c, f_token);
        struct token_t token_c = create_complex_token(f_token);
        struct token_t token_s = create_simple_token(builder->requires.c);
        for (unsigned int i = 0; i < player->num_tokens; ++i)
        {
            comp += token_equals(player->tokens[i], token_c);
            simp += token_equals(player->tokens[i], token_s);
            if (comp % 2 == 0 && simp == 0)
                return 0;
            else
                return 1;
        }
    }
    return 0;
}
