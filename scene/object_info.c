#include "object_info.h"

#include "../models/static/cube/model_cube.h"
#include "../models/static/objects/balloon/model_balloon.h"
#include "../models/static/objects/lunchtable/model_lunchtable.h"
#include "../models/static/objects/chair/model_chair.h"
#include "../models/static/objects/basket/model_basket.h"
#include "../models/static/objects/beer/model_beer.h"
#include "../models/static/objects/noodle/model_noodle.h"
#include "../models/static/objects/melon/model_melon.h"
#include "../models/static/objects/apple/model_apple.h"
#include "../models/static/objects/balloon_deflated/model_balloondeflated.h"
#include "../models/static/objects/beehive/model_beehive.h"
#include "../models/static/objects/bills/model_bills.h"
#include "../models/static/objects/card/model_card.h"
#include "../models/static/objects/flower/model_flower.h"
#include "../models/static/objects/necklace/model_necklace.h"
#include "../models/static/objects/ring/model_ring.h"
#include "../models/static/objects/soccer/model_soccer.h"
#include "../models/static/objects/stick/model_stick.h"
#include "../models/static/objects/table/model_table.h"
#include "../models/static/cat/model_cat.h"
#include "../models/static/chicken/model_chicken.h"
#include "../models/static/critic/model_critic.h"
#include "../models/static/objects/n64/model_n64.h"
#include "../models/static/objects/store_b/model_storeb.h"
#include "../models/static/objects/store_e/model_storee.h"
#include "../models/static/objects/steppingstone/model_steppingstone.h"
#include "../models/static/objects/fence/model_fence.h"
#include "../models/static/objects/trunk/model_trunk.h"
#include "../models/static/objects/leaves/model_leaves.h"
#include "../models/static/objects/branch/model_branch.h"
#include "../models/static/objects/roots/model_roots.h"

/* Object info */
/* Mesh, Name, Type, (Size), (Offset), Mass, Value */
const struct TObjectData gObjectDataList[] = 
{
    {0, "null", 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0},
    {cube_Cube_mesh, "Cube", 1, 213.0f, 213.0f, 213.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1},
    {balloon_Balloon_mesh, "Balloon", 0, 150.0f, 150.0f, 150.0f, 0.0f, 0.0f, 0.0f, 0.1f, 5},
    {lunchtable_Table_mesh, "Lunch Table", 1, 130.0f, 130.0f, 130.0f, 0.0f, 106.0f, 0.0f, 0.75f, 20},
    {chair_Chair_mesh, "Chair", 1, 800.0f, 800.0f, 800.0f, 0.0f, 0.0f, 0.0f, 0.75f, 15},
    {basket_Basket_mesh, "Basket", 1, 380.0f, 380.0f, 380.0f, 0.0f, 0.0f, 0.0f, 0.5f, 10},
    {beer_Beer_mesh, "Drink", 0, 380.0f, 380.0f, 380.0f, 0.0f, 0.0f, 0.0f, 0.5f, 5},
    {noodle_Noodle_mesh, "Pool Toy", 0, 106.0f, 106.0f, 106.0f, 0.0f, 0.0f, 0.0f, 0.25f, 10},
    {melon_Melon_mesh, "Melon", 0, 213.0f, 213.0f, 213.0f, 0.0f, 213.0f, 0.0f, 0.5f, 5},
    {apple_Apple_mesh, "Apple", 0, 170.0f, 170.0f, 170.0f, 0.0f, 170.0f, 0.0f, 0.5f, 0},
    {balloon_deflated_Balloon_Deflated_mesh, "Balloon", 0, 20.0f, 20.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.1f, 5},
    {beehive_Beehive_mesh, "Beehive", 0, 106.0f, 106.0f, 106.0f, 0.0f, 106.0f, 0.0f, 0.5f, 8},
    {bills_Bills_mesh, "Money", 0, 60.0f, 60.0f, 60.0f, 0.0f, 50.0f, 0.0f, 0.3f, 8},
    {card_Cube_mesh, "Card", 0, 213.0f, 213.0f, 213.0f, 0.0f, 213.0f, 0.0f, 0.3f, 2},
    {flower_Head_mesh, "Flower", 0, 60.0f, 60.0f, 60.0f, 0.0f, 266.0f, 0.0f, 0.1f, 3},
    {necklace_Necklace_mesh, "Necklace", 0, 213.0f, 213.0f, 213.0f, 0.0f, 0.0f, 0.0f, 0.25f, 25},
    {ring_Ring_mesh, "Ring", 0, 106.0f, 106.0f, 106.0f, 0.0f, 0.0f, 0.0f, 0.25f, 20},
    {zedball_Zedball_mesh, "Soccer Ball", 0, 250.0f, 250.0f, 250.0f, 0.0f, 250.0f, 0.0f, 0.25f, 10},
    {stick_Stick1_mesh, "Stick", 0, 106.0f, 106.0f, 106.0f, 0.0f, 0.0f, 0.0f, 0.2f, 1},
    {table_Table_mesh, "Table", 1, 250.0f, 250.0f, 250.0f, 0.0f, 213.0f, 0.0f, 0.75f, 20},
    {cat_Cat_mesh, "Cat", 0, 372.0f, 372.0f, 372.0f, 0.0f, 372.0f, 0.0f, 1.5f, 50},
    {chicken_Chicken_mesh, "Chicken", 0, 292.0f, 292.0f, 292.0f, 0.0f, 292.0f, 0.0f, 1.1f, 30},
    {critic_Critic_mesh, "Human", 1, 200.0f, 926.0f, 200.0f, 0.0f, 926.0f, 0.0f, 2.0f, 100},
    {n64_N_mesh, "Grocery Logo N", 1, 212.0f, 212.0f, 212.0f, 0.0f, 0.0f, 0.0f, 0.8f, 50},
    {store_e_E_mesh, "Grocery Logo E", 1, 212.0f, 212.0f, 50.0f, 106.0f, 106.0f, 0.0f, 0.75f, 30},
    {store_b_B_mesh, "Grocery Logo B", 1, 212.0f, 212.0f, 50.0f, 106.0f, 106.0f, 0.0f, 0.75f, 30},
    {steppingstone_SteppingStone_mesh, "Path", 1, 150.0f, 30.0f, 150.0f, 0.0f, 0.0f, 0.0f, 0.6f, 10},
    {fence_Fence_mesh, "Fence", 0, 273.0f, 273.0f, 273.0f, 276.0f, 276.0f, 0.0f, 1.0f, 30},
    {trunk_Trunk_mesh, "Tree Trunk", 0, 106.0f, 106.0f, 106.0f, 0.0f, 0.0f, 0.0f, 2.0f, 5},
    {leaves_Leaves_mesh, "Tree Leaves", 0, 106.0f, 106.0f, 106.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5},
    {branch_Branch_mesh, "Tree Branch", 0, 106.0f, 106.0f, 106.0f, 0.0f, 0.0f, 0.0f, 1.1f, 5},
    {roots_Roots_mesh, "Tree Roots", 0, 127.0f, 127.0f, 127.0f, 0.0f, 0.0f, 0.0f, 1.0f, 5}
};