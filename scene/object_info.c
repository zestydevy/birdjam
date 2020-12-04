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
#include "../models/static/objects/mailbox/model_mailbox.h"
#include "../models/static/nest/model_nest.h"
#include "../models/static/objects/baldtree/model_baldtree.h"
#include "../models/static/objects/baldhooktree/model_baldhooktree.h"
#include "../models/static/objects/deadtree/model_deadtree.h"
#include "../models/static/objects/tire/model_tire.h"
#include "../models/static/objects/toaster/model_toaster.h"
#include "../models/static/objects/plank/model_plank.h"
#include "../models/static/objects/trashcan/model_trashcan.h"
#include "../models/static/objects/pot/model_pot.h"
#include "../models/static/objects/bush/model_bush.h"
#include "../models/static/objects/lamp/model_lamp.h"

/* Object info */
/* Mesh, Name, Type, MeshCol, (Size), (Offset), Mass, Value */
const struct TObjectData gObjectDataList[] = 
{
    {0, "null", 0, false, 0.0f, 0.0f, 0.0f, 0.0f, 0},
    {cube_Cube_mesh, "Cube", 1, false, 213.0f, 213.0f, 213.0f, 1.0f, 1},
    {balloon_Balloon_mesh, "Balloon", 0, false, 150.0f, 150.0f, 150.0f, 0.1f, 5},
    {lunchtable_Table_mesh, "Lunch Table", 1, true, 130.0f, 130.0f, 130.0f, SIZE_LAYER1, 20},
    {chair_Chair_mesh, "Chair", 1, true, 800.0f, 800.0f, 800.0f, SIZE_LAYER1, 15},
    {basket_Basket_mesh, "Basket", 1, false, 380.0f, 380.0f, 380.0f, 1.0f, 10},
    {beer_Beer_mesh, "Drink", 0, false, 380.0f, 380.0f, 380.0f, 0.5f, 5},
    {noodle_Noodle_mesh, "Pool Toy", 0, false, 106.0f, 106.0f, 106.0f, 0.75f, 10},
    {melon_Melon_mesh, "Melon", 0, false, 213.0f, 213.0f, 213.0f, 1.0f, 5},
    {apple_Apple_mesh, "Apple", 0, false, 170.0f, 170.0f, 170.0f, 0.5f, 0},
    {balloon_deflated_Balloon_Deflated_mesh, "Balloon", 0, false, 20.0f, 20.0f, 20.0f, 0.1f, 5},
    {beehive_Beehive_mesh, "Beehive", 0, false, 106.0f, 106.0f, 106.0f, 1.0f, 8},
    {bills_Bills_mesh, "Money", 0, false, 60.0f, 60.0f, 60.0f, 0.3f, 20},
    {card_Cube_mesh, "Card", 0, false, 213.0f, 213.0f, 213.0f, 0.3f, 2},
    {flower_Head_mesh, "Flower", 1, false, 30.0f, 60.0f, 30.0f, 0.1f, 3},
    {necklace_Necklace_mesh, "Necklace", 0, false, 213.0f, 213.0f, 213.0f, 0.25f, 25},
    {ring_Ring_mesh, "Ring", 0, false, 106.0f, 106.0f, 106.0f, 0.25f, 20},
    {zedball_Zedball_mesh, "Soccer Ball", 0, false, 250.0f, 250.0f, 250.0f, 1.0f, 10},
    {stick_Stick1_mesh, "Stick", 0, false, 106.0f, 106.0f, 106.0f, 0.1f, 1},
    {table_Table_mesh, "Table", 1, true, 250.0f, 250.0f, 250.0f, SIZE_LAYER1, 20},
    {cat_Cat_mesh, "Cat", 0, false, 372.0f, 372.0f, 372.0f, 2.0f, 50},
    {chicken_Chicken_mesh, "Chicken", 0, false, 292.0f, 292.0f, 292.0f, 0.9f, 30},
    {critic_Critic_mesh, "Human", 1, false, 200.0f, 926.0f, 200.0f, 4.0f, 100},
    {n64_N_mesh, "Grocery Logo N", 1, true, 212.0f, 212.0f, 212.0f, SIZE_LAYER1, 50},
    {store_e_E_mesh, "Grocery Logo E", 1, true, 212.0f, 212.0f, 50.0f, SIZE_LAYER1, 30},
    {store_b_B_mesh, "Grocery Logo B", 1, true, 212.0f, 212.0f, 50.0f, SIZE_LAYER1, 30},
    {steppingstone_SteppingStone_mesh, "Path", 1, true, 150.0f, 30.0f, 150.0f, SIZE_LAYER1, 10},
    {fence_Fence_mesh, "Fence", 0, true, 273.0f, 273.0f, 273.0f, SIZE_LAYER2, 30},
    {trunk_Trunk_mesh, "Tree Trunk", 0, true, 106.0f, 106.0f, 106.0f, SIZE_LAYER2, 5},
    {leaves_Leaves_mesh, "Tree Leaves", 0, false, 106.0f, 106.0f, 106.0f, 7.5f, 5},
    {branch_Branch_mesh, "Tree Branch", 0,  true,106.0f, 106.0f, 106.0f, SIZE_LAYER2, 5},
    {roots_Roots_mesh, "Tree Roots", 0, true, 127.0f, 127.0f, 127.0f, SIZE_LAYER2, 5},
    {mailbox_Mailbox_mesh, "Mailbox", 1, true, 170.0f, 298.0f, 170.0f, SIZE_LAYER1, 5},
    {nest_Nest_mesh, "Nest", 2, 213.0f, false, 127.0f, 213.0f, 1000.0f, 0},
    {treedead_Tree_Dead_mesh, "Dead Tree", 0, true, 106.0f, 106.0f, 106.0f, SIZE_LAYER2, 5},
    {tree2_bald_Tree_Bald_mesh, "Tree", 0, true, 106.0f, 106.0f, 106.0f, SIZE_LAYER2, 5},
    {tree1_bald_TreeBald_mesh, "Tree", 0, true, 106.0f, 106.0f, 106.0f, SIZE_LAYER2, 5},
    {tire_Tire_mesh, "Car Tire", 0,  true, 213.0f, 213.0f, 213.0f, SIZE_LAYER1, 15},
    {toaster_Toaster_mesh, "Old Toaster", 0,  false, 298.0f, 298.0f, 298.0f, 2.5f, 15},
    {plank_Plank_mesh, "2x4", 0,  true, 1550.0f, 1550.0f, 1550.0f, SIZE_LAYER1, 5},
    {trashcan_TrashCan_mesh, "Trash Can", 0,  true, 319.5f, 319.5f, 319.5f, SIZE_LAYER1, 10},
    {pot_Pot_mesh, "Ceramic Pot", 0,  false, 170.5f, 170.5f, 170.5f, 2.0, 5},
    {bush_Bush_mesh, "Bush", 0,  true, 404.5f, 404.5f, 404.5f, SIZE_LAYER2, 20},
    {lamp_Lamp_mesh, "Lamp", 1,  false, 127.8f, 681.6f, 127.8f, 15.0f, 30},
};