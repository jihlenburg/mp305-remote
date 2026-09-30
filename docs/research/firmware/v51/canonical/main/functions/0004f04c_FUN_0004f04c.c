/* Address: 0004f04c; name: FUN_0004f04c; body bytes: 40 */

uint FUN_0004f04c(uint param_1)

{
  undefined4 uVar1;
  undefined2 local_8;
  undefined1 uStack_6;
  
  if (param_1 < 0x13) {
    local_8 = *(undefined2 *)(&DAT_0007a2b5 + param_1 * 3);
    uStack_6 = (&DAT_0007a2b7)[param_1 * 3];
  }
  else {
    uVar1 = FUN_0004029c();
    local_8 = (undefined2)uVar1;
    uStack_6 = (undefined1)((uint)uVar1 >> 0x10);
  }
  return (uint)CONCAT12(uStack_6,local_8);
}

