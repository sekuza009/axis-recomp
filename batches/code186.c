/* batch 185 (lifted/grp137-139.c: split so the calls among these go through their native addresses, where the
   tests stub them): armc_40e5d0 (an armour-centre session: the lobby player made, his parts given, the actor
   reset), the main page / part screen frames armc_41d600 / armc_41d8a0 (the mech turned by the cursor:
   armc_rotateFromCursor, stubbed: it builds C++ objects under an SEH frame the lifter does not handle yet), their
   wrappers armc_41dfe0 / armc_41e010 / armc_41dfb0 and menuState700_armCenter, callees stubbed */
#include "lifted/grp137.c"
#include "lifted/grp138.c"
#include "lifted/grp139.c"
LIFT_PLAIN(armc_40e5d0, 40e5d0)
LIFT_PLAIN(armc_41d600, 41d600)
LIFT_PLAIN(armc_41d8a0, 41d8a0)
LIFT_PLAIN(armc_41dfe0, 41dfe0)
LIFT_PLAIN(armc_41e010, 41e010)
LIFT_PLAIN(armc_41dfb0, 41dfb0)
LIFT_PLAIN(menuState700_armCenter, 41e040)
