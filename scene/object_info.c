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
    {0, cube_Cube_mesh, "Cube", 1, false, 213.0f, 213.0f, 213.0f, SIZE_MED, 100, DRAWDIST_ALWAYS},
    {0, balloon_Balloon_mesh, "Balloon", 0, false, 150.0f, 150.0f, 150.0f, SIZE_TINY, 6, DRAWDIST_ALWAYS},
    {0, lunchtable_Table_mesh, "Lunch Table", 1, true, 130.0f, 130.0f, 130.0f, SIZE_LAYER1, 130, DRAWDIST_HALF},
    {mat_chair_Table_f3d, chair_Chair_mesh_tri_0, "Chair", 1, true, 800.0f, 800.0f, 800.0f, SIZE_LAYER1, 85, DRAWDIST_HALF},
    {0, basket_Basket_mesh, "Basket", 1, false, 380.0f, 380.0f, 380.0f, SIZE_MED, 30, DRAWDIST_QUARTER},
    {mat_beer_sm64_material, beer_Beer_mesh_tri_0, "Drink", 0, false, 380.0f, 380.0f, 380.0f, SIZE_SMALL, 10, DRAWDIST_EIGHTH},
    {mat_noodle_poolnoodle_f3d, noodle_Noodle_mesh_tri_0, "Pool Toy", 0, true, 2130.0f, 2130.0f, 2130.0f, SIZE_MAN, 120, DRAWDIST_QUARTER},
    {mat_melon_melon_f3d, melon_Melon_mesh_tri_0, "Melon", 0, false, 213.0f, 213.0f, 213.0f, SIZE_MED, 30, DRAWDIST_QUARTER},
    {0, apple_Apple_mesh, "Apple", 0, false, 200.0f, 200.0f, 200.0f, SIZE_SMALL, 15, DRAWDIST_EIGHTH},
    {0, balloon_deflated_Balloon_Deflated_mesh, "Balloon", 0, false, 20.0f, 20.0f, 6, SIZE_SMALL, 0.0f, DRAWDIST_EIGHTH},
    {mat_beehive_Beehive_f3d, beehive_Beehive_mesh_tri_0, "Beehive", 0, false, 120.0f, 120.0f, 120.0f, SIZE_MED, 60, DRAWDIST_QUARTER},
    {0, bills_Bills_mesh, "Money", 0, false, 60.0f, 60.0f, 60.0f, SIZE_JEWELRY, 20, DRAWDIST_QUARTER},
    {0, card_Cube_mesh, "Card", 0, false, 213.0f, 213.0f, 213.0f, SIZE_JEWELRY, 10, DRAWDIST_EIGHTH},
    {mat_flower_Flower_f3d, flower_Head_mesh_tri_0, "Flower", 1, true, 30.0f, 60.0f, 30.0f, SIZE_SMALL, 8, DRAWDIST_HALF},
    {mat_ring_Material_001_f3d, necklace_Necklace_mesh_tri_0, "Necklace", 0, true, 250.0f, 250.0f, 250.0f, SIZE_JEWELRY, 12, DRAWDIST_QUARTER},
    {mat_ring_Material_001_f3d, ring_Ring_mesh_tri_0, "Ring", 0, true, 150.0f, 150.0f, 150.0f, SIZE_JEWELRY, 10, DRAWDIST_EIGHTH},
    {0, zedball_Zedball_mesh, "Soccer Ball", 0, false, 250.0f, 250.0f, 250.0f, SIZE_MED, 32, DRAWDIST_QUARTER},
    {mat_trunk_trunk_f3d, stick_Stick1_mesh_tri_0, "Stick", 0, true, 175.0f, 175.0f, 175.0f, SIZE_TINY, 7, DRAWDIST_HALF},
    {mat_chair_Table_f3d, table_Table_mesh_tri_0, "Table", 1, true, 250.0f, 250.0f, 250.0f, SIZE_LAYER1, 120, DRAWDIST_HALF},
    {mat_cat_Material_f3d, cat_Cat_mesh_tri_0, "Cat", 0, false, 450.0f, 450.0f, 450.0f, SIZE_ANIMAL, 75, DRAWDIST_HALF},
    {mat_chicken_Chicken_f3d, chicken_Chicken_mesh_tri_0, "Chicken", 0, false, 292.0f, 292.0f, 292.0f, SIZE_ANIMAL, 75, DRAWDIST_HALF},
    {0, critic_Critic_mesh, "Human", 1, false, 200.0f, 900.0f, 200.0f, SIZE_MAN, 200, DRAWDIST_HALF},
    {0, avgn_AVGN_mesh, "Human", 1, false, 200.0f, 900.0f, 200.0f, SIZE_MAN, 200, DRAWDIST_HALF},
    {mat_woman_Material_f3d, woman_Woman_mesh_tri_0, "Human", 1, false, 200.0f, 900.0f, 200.0f, SIZE_MAN, 200, DRAWDIST_HALF},
    {mat_child_Material_f3d, child_Child_mesh_tri_0, "Human", 1, false, 200.0f, 900.0f, 200.0f, SIZE_MAN, 200, DRAWDIST_HALF},
    {0, n64_N_mesh, "Grocery Logo N", 1, true, 212.0f, 212.0f, 212.0f, SIZE_LAYER2, 640, DRAWDIST_THREEQUARTERS},
    {0, store_e_E_mesh, "Grocery Logo E", 1, true, 212.0f, 212.0f, 50.0f, SIZE_LAYER2, 400, DRAWDIST_QUARTER},
    {0, store_b_B_mesh, "Grocery Logo B", 1, true, 212.0f, 212.0f, 50.0f, SIZE_LAYER2, 400, DRAWDIST_QUARTER},
    {mat_steppingstone_steppingstone_f3d, steppingstone_SteppingStone_mesh_tri_0, "Path", 0, true, 150.0f, 150.0f, 150.0f, SIZE_LAYER2, 387, DRAWDIST_HALF},
    {mat_fence_fence_f3d, fence_Fence_mesh_tri_0, "Fence", 0, true, 273.0f, 273.0f, 273.0f, SIZE_LAYER3, 667, DRAWDIST_THREEQUARTERS},
    {mat_trunk_trunk_f3d, trunk_Trunk_mesh_tri_0, "Tree Trunk", 0, true, 106.0f, 106.0f, 106.0f, SIZE_LAYER2, 784, DRAWDIST_ALWAYS},
    {mat_leaves_leaves_f3d, leaves_Leaves_mesh_tri_0, "Tree Leaves", 0, false, 106.0f, 106.0f, 106.0f, SIZE_MASSIVE, 520, DRAWDIST_ALWAYS},
    {mat_trunk_trunk_f3d, branch_Branch_mesh_tri_0, "Tree Branch", 0,  true,106.0f, 106.0f, 106.0f, SIZE_LAYER2, 300, DRAWDIST_ALWAYS},
    {mat_trunk_trunk_f3d, roots_Roots_mesh_tri_0, "Tree Roots", 0, true, 127.0f, 127.0f, 127.0f, SIZE_LAYER2, 100, DRAWDIST_HALF},
    {0, mailbox_Mailbox_mesh, "Mailbox", 1, true, 170.0f, 298.0f, 170.0f, SIZE_LAYER1, 95, DRAWDIST_HALF},
    {0, nest_Nest_mesh, "Nest", 2, 213.0f, false, 127.0f, 213.0f, SIZE_IMPOSSIBLE, 0, DRAWDIST_ALWAYS},
    {mat_trunk_trunk_f3d, treedead_Tree_Dead_mesh_tri_0, "Dead Tree", 0, true, 106.0f, 256.0f, 106.0f, SIZE_LAYER3, 1002, DRAWDIST_THREEQUARTERS},
    {mat_trunk_trunk_f3d, tree2_bald_Tree_Bald_mesh_tri_0, "Tree", 0, true, 106.0f, 106.0f, 106.0f, SIZE_LAYER3, 1200, DRAWDIST_THREEQUARTERS},
    {mat_trunk_trunk_f3d, tree1_bald_TreeBald_mesh_tri_0, "Tree", 0, true, 106.0f, 106.0f, 106.0f, SIZE_LAYER3, 1150, DRAWDIST_THREEQUARTERS},
    {mat_tire_tire_f3d, tire_Tire_mesh_tri_0, "Car Tire", 0,  false, 213.0f, 213.0f, 213.0f, SIZE_LAYER1, 80, DRAWDIST_THREEQUARTERS},
    {0, toaster_Toaster_mesh, "Old Toaster", 0,  false, 298.0f, 298.0f, 298.0f, SIZE_LARGE, 50, DRAWDIST_HALF},
    {mat_trunk_trunk_f3d, plank_Plank_mesh_tri_0, "2x4", 0,  true, 1550.0f, 1550.0f, 1550.0f, SIZE_LAYER2, 400, DRAWDIST_THREEQUARTERS},
    {mat_trashcan_sm64_material, trashcan_TrashCan_mesh_tri_0, "Trash Can", 0,  true, 319.5f, 319.5f, 319.5f, SIZE_LAYER1, 101, DRAWDIST_THREEQUARTERS},
    {mat_trashcan_sm64_material, trashcan_TrashCan_mesh_tri_0, "Trash Can", 0,  false, 319.5f, 319.5f, 319.5f, SIZE_LAYER1, 101, DRAWDIST_HALF},
    {0, pot_Pot_mesh, "Ceramic Pot", 0,  false, 170.5f, 170.5f, 170.5f, SIZE_LARGE, 80, DRAWDIST_HALF},
    {0, bush_Bush_mesh, "Bush", 0,  true, 404.5f, 404.5f, 404.5f, SIZE_LAYER3, 4120, DRAWDIST_ALWAYS},
    {0, lamp_Lamp_mesh, "Lamp", 1,  false, 127.8f, 681.6f, 127.8f, SIZE_GIANT, 300, DRAWDIST_THREEQUARTERS},
    {mat_car_car_f3d, car_Car_mesh_tri_0, "Car", 0,  true, 660.5f, 660.5f, 660.5f, SIZE_LAYER2, 885, DRAWDIST_THREEQUARTERS},
    {0, goal_Goal_mesh, "Soccer Goal", 1,  true, 101.0f, 59.64f, 30.8f, SIZE_LAYER2, 950, DRAWDIST_THREEQUARTERS},
};