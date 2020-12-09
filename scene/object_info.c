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
#include "../models/static/avgn/model_avgn.h"
#include "../models/static/woman/model_woman.h"
#include "../models/static/child/model_child.h"
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
#include "../models/static/objects/car/model_car.h"
#include "../models/static/objects/goal/model_goal.h"

/* Object info */
/* Mesh, Name, Type, MeshCol, (Size), (Offset), Mass, Value */
const struct TObjectData gObjectDataList[] = 
{
    {0, 0, "null", 0, false, 0.0f, 0.0f, 0.0f, SIZE_IMPOSSIBLE, 0, DRAWDIST_EIGHTH},
    {0, cube_Cube_mesh, "Cube", 1, false, 213.0f, 213.0f, 213.0f, SIZE_MED, 0.0f, DRAWDIST_ALWAYS},
    {0, balloon_Balloon_mesh, "Balloon", 0, false, 150.0f, 150.0f, 150.0f, SIZE_TINY, 0.0f, DRAWDIST_ALWAYS},
    {0, lunchtable_Table_mesh, "Lunch Table", 1, true, 130.0f, 130.0f, 130.0f, SIZE_LAYER1, 0.0f, DRAWDIST_HALF},
    {0, chair_Chair_mesh, "Chair", 1, true, 800.0f, 800.0f, 800.0f, SIZE_LAYER1, 0.0f, DRAWDIST_HALF},
    {0, basket_Basket_mesh, "Basket", 1, false, 380.0f, 380.0f, 380.0f, SIZE_MED, 0.0f, DRAWDIST_QUARTER},
    {0, beer_Beer_mesh, "Drink", 0, false, 380.0f, 380.0f, 380.0f, SIZE_SMALL, 0.0f, DRAWDIST_EIGHTH},
    {0, noodle_Noodle_mesh, "Pool Toy", 0, true, 500.0f, 500.0f, 500.0f, SIZE_MAN, 1000.0f, DRAWDIST_QUARTER},
    {0, melon_Melon_mesh, "Melon", 0, false, 213.0f, 213.0f, 213.0f, SIZE_MED, 0.0f, DRAWDIST_QUARTER},
    {0, apple_Apple_mesh, "Apple", 0, false, 200.0f, 200.0f, 200.0f, SIZE_SMALL, 0.0f, DRAWDIST_EIGHTH},
    {0, balloon_deflated_Balloon_Deflated_mesh, "Balloon", 0, false, 20.0f, 20.0f, 20.0f, SIZE_SMALL, 0.0f, DRAWDIST_EIGHTH},
    {0, beehive_Beehive_mesh, "Beehive", 0, false, 120.0f, 120.0f, 120.0f, SIZE_MED, 0.0f, DRAWDIST_QUARTER},
    {0, bills_Bills_mesh, "Money", 0, false, 60.0f, 60.0f, 60.0f, SIZE_JEWELRY, 0.0f, DRAWDIST_QUARTER},
    {0, card_Cube_mesh, "Card", 0, false, 213.0f, 213.0f, 213.0f, SIZE_JEWELRY, 0.0f, DRAWDIST_EIGHTH},
    {mat_flower_Flower_f3d, flower_Head_mesh_tri_0, "Flower", 1, true, 30.0f, 60.0f, 30.0f, SIZE_SMALL, 0.0f, DRAWDIST_HALF},
    {0, necklace_Necklace_mesh, "Necklace", 0, true, 250.0f, 250.0f, 250.0f, SIZE_JEWELRY, 0.0f, DRAWDIST_QUARTER},
    {0, ring_Ring_mesh, "Ring", 0, true, 150.0f, 150.0f, 150.0f, SIZE_JEWELRY, 0.0f, DRAWDIST_EIGHTH},
    {0, zedball_Zedball_mesh, "Soccer Ball", 0, false, 250.0f, 250.0f, 250.0f, SIZE_MED, 0.0f, DRAWDIST_QUARTER},
    {0, stick_Stick1_mesh, "Stick", 0, true, 175.0f, 175.0f, 175.0f, SIZE_TINY, 0.0f, DRAWDIST_HALF},
    {0, table_Table_mesh, "Table", 1, true, 250.0f, 250.0f, 250.0f, SIZE_LAYER1, 0.0f, DRAWDIST_HALF},
    {mat_cat_Material_f3d, cat_Cat_mesh_tri_0, "Cat", 0, false, 450.0f, 450.0f, 450.0f, SIZE_ANIMAL, 50, DRAWDIST_HALF},
    {mat_chicken_Chicken_f3d, chicken_Chicken_mesh_tri_0, "Chicken", 0, false, 292.0f, 292.0f, 292.0f, SIZE_ANIMAL, 0.0f, DRAWDIST_HALF},
    {mat_critic_Material_f3d, critic_Critic_mesh_tri_0, "Human", 1, false, 200.0f, 926.0f, 200.0f, SIZE_MAN, 0.0f, DRAWDIST_HALF},
    {mat_avgn_Material_f3d, avgn_AVGN_mesh_tri_0, "Human", 1, false, 200.0f, 926.0f, 200.0f, SIZE_MAN, 0.0f, DRAWDIST_HALF},
    {mat_woman_Material_f3d, woman_Woman_mesh_tri_0, "Human", 1, false, 200.0f, 926.0f, 200.0f, SIZE_MAN, 0.0f, DRAWDIST_HALF},
    {mat_child_Material_f3d, child_Child_mesh_tri_0, "Human", 1, false, 200.0f, 926.0f, 200.0f, SIZE_MAN, 0.0f, DRAWDIST_HALF},
    {0, n64_N_mesh, "Grocery Logo N", 1, true, 212.0f, 212.0f, 212.0f, SIZE_LAYER2, 0.0f, DRAWDIST_THREEQUARTERS},
    {0, store_e_E_mesh, "Grocery Logo E", 1, true, 212.0f, 212.0f, 50.0f, SIZE_LAYER2, 0.0f, DRAWDIST_QUARTER},
    {0, store_b_B_mesh, "Grocery Logo B", 1, true, 212.0f, 212.0f, 50.0f, SIZE_LAYER2, 0.0f, DRAWDIST_QUARTER},
    {0, steppingstone_SteppingStone_mesh, "Path", 0, true, 150.0f, 150.0f, 150.0f, SIZE_LAYER2, 10000.0f, DRAWDIST_HALF},
    {0, fence_Fence_mesh, "Fence", 0, true, 273.0f, 273.0f, 273.0f, SIZE_LAYER3, 50000.0f, DRAWDIST_THREEQUARTERS},
    {0, trunk_Trunk_mesh, "Tree Trunk", 0, true, 106.0f, 106.0f, 106.0f, SIZE_LAYER2, 0.0f, DRAWDIST_ALWAYS},
    {mat_world_leaves_f3d, leaves_Leaves_mesh_tri_0, "Tree Leaves", 0, false, 106.0f, 106.0f, 106.0f, SIZE_MASSIVE, 0.0f, DRAWDIST_ALWAYS},
    {0, branch_Branch_mesh, "Tree Branch", 0,  true,106.0f, 106.0f, 106.0f, SIZE_LAYER2, 0.0f, DRAWDIST_ALWAYS},
    {0, roots_Roots_mesh, "Tree Roots", 0, true, 127.0f, 127.0f, 127.0f, SIZE_LAYER2, 0.0f, DRAWDIST_HALF},
    {0, mailbox_Mailbox_mesh, "Mailbox", 1, true, 170.0f, 298.0f, 170.0f, SIZE_LAYER1, 0.0f, DRAWDIST_HALF},
    {0, nest_Nest_mesh, "Nest", 2, 213.0f, false, 127.0f, 213.0f, SIZE_IMPOSSIBLE, 0.0f, DRAWDIST_ALWAYS},
    {0, treedead_Tree_Dead_mesh, "Dead Tree", 0, true, 106.0f, 256.0f, 106.0f, SIZE_LAYER3, 0.0f, DRAWDIST_THREEQUARTERS},
    {0, tree2_bald_Tree_Bald_mesh, "Tree", 0, true, 106.0f, 106.0f, 106.0f, SIZE_LAYER3, 100000.0f, DRAWDIST_THREEQUARTERS},
    {0, tree1_bald_TreeBald_mesh, "Tree", 0, true, 106.0f, 106.0f, 106.0f, SIZE_LAYER3, 200000.0f, DRAWDIST_THREEQUARTERS},
    {0, tire_Tire_mesh, "Car Tire", 0,  false, 213.0f, 213.0f, 213.0f, SIZE_LAYER1, 0.0f, DRAWDIST_THREEQUARTERS},
    {0, toaster_Toaster_mesh, "Old Toaster", 0,  false, 298.0f, 298.0f, 298.0f, SIZE_LARGE, 0.0f, DRAWDIST_HALF},
    {0, plank_Plank_mesh, "2x4", 0,  true, 1550.0f, 1550.0f, 1550.0f, SIZE_LAYER2, 0.0f, DRAWDIST_THREEQUARTERS},
    {mat_trashcan_sm64_material, trashcan_TrashCan_mesh_tri_0, "Trash Can", 0,  true, 319.5f, 319.5f, 319.5f, SIZE_LAYER1, 0.0f, DRAWDIST_THREEQUARTERS},
    {mat_trashcan_sm64_material, trashcan_TrashCan_mesh_tri_0, "Trash Can", 0,  false, 319.5f, 319.5f, 319.5f, SIZE_LAYER1, 0.0f, DRAWDIST_HALF},
    {0, pot_Pot_mesh, "Ceramic Pot", 0,  false, 170.5f, 170.5f, 170.5f, SIZE_LARGE, 0.0f, DRAWDIST_HALF},
    {0, bush_Bush_mesh, "Bush", 0,  true, 404.5f, 404.5f, 404.5f, SIZE_LAYER3, 0.0f, DRAWDIST_ALWAYS},
    {0, lamp_Lamp_mesh, "Lamp", 1,  false, 127.8f, 681.6f, 127.8f, SIZE_GIANT, 0.0f, DRAWDIST_THREEQUARTERS},
    {mat_car_car_f3d, car_Car_mesh_tri_0, "Car", 0,  true, 660.5f, 660.5f, 660.5f, SIZE_LAYER2, 0.0f, DRAWDIST_THREEQUARTERS},
    {0, goal_Goal_mesh, "Soccer Goal", 1,  true, 101.0f, 59.64f, 30.8f, SIZE_LAYER2, 0.0f, DRAWDIST_THREEQUARTERS},
};