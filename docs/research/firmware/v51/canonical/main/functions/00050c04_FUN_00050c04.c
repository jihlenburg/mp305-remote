/* Address: 00050c04; name: FUN_00050c04; body bytes: 16 */

bool FUN_00050c04(undefined4 param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = FUN_00050c14();
  return (uVar1 & param_2) != 0;
}

